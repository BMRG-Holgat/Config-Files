/* This is an automation example file.
 *  The presence of a file called "myAutomation.h" brings EX-RAIL code into
 *  the command station.
 *  The automation may have multiple concurrent tasks.
 *  A task may 
 *  - Act as a ROUTE setup macro for a user to drive over 
 *  - drive a loco through an AUTOMATION 
 *  - automate some cosmetic part of the layout without any loco.
 *  
 *  At startup, a single task is created to execute the startup sequence.
 *  This task may simply follow a route, or may START  
 *  further tasks (that is.. send a loco out along a route).
 *  
 *  Where the loco id is not known at compile time, a new task 
 *  can be created with the command:
 *  </ START [cab] route> 
 *  
 *  A ROUTE, AUTOMATION or SEQUENCE are internally identical in ExRail terms  
 *  but are just represented differently to a Withrottle user:
 *  ROUTE(n,"name") - as Route_n .. to setup a route through a layout
 *  AUTOMATION(n,"name") as Auto_n .. to send the current loco off along an automated journey
 *  SEQUENCE(n) is not visible to Withrottle.
 *  
 */
HAL_IGNORE_DEFAULTS
//Hal devices and includes
#include "IODeviceList.h"
#include "DCC.h"

HAL(MCP23017,300,16,{I2CMux_0,SubBus_3,0x27}) //Board 1
HAL(MCP23017,316,16,{I2CMux_0,SubBus_3,0x26}) //Board 2
HAL(PCA9685,348,16,{I2CMux_0,SubBus_3,0x41}) //Board 2 //Lights & church
HAL(MCP23017,400,16,{I2CMux_0,SubBus_3,0x23}) //Board 3
HAL(MCP23017,416,16,{I2CMux_0,SubBus_3,0x24}) //Board 3 //signals & street lights
HAL(PCA9685,432, 16, {I2CMux_0,SubBus_3,0x42}) // Board 3 House Lights
HAL(MCP23017,500,16,{I2CMux_0,SubBus_3,0x22}) // Board 4
HAL(PCF8575,516,8,{I2CMux_0,SubBus_3,0x21}) //Board 4
HAL(MCP23017,524,16,{I2CMux_0,SubBus_1,0x27}) //Board 5
HAL(MCP23017,600,16,{I2CMux_0,SubBus_4,0x27}) // Board 6
HAL(MCP23017,616,16,{I2CMux_0,SubBus_4,0x26}) //Board 6
HAL(MCP23017,700,16,{I2CMux_0,SubBus_4,0x25}) //Board 7
HAL(MCP23017,800,16,{I2CMux_0,SubBus_4,0x23}) // Board 8 
HAL(MCP23017,900,16,{I2CMux_0,SubBus_4,0x24}) // Board 9


HAL(PCA9685,120, 16, {I2CMux_0,SubBus_3,0x40}) // Board 1
HAL(PCA9685,184, 16, {I2CMux_0,SubBus_3,0x43}) // Board 4 turnout and signals
HAL(PCA9685,264, 16, {I2CMux_0,SubBus_3,0x45}) // Board 4 (signals?)
HAL(PCA9685,280, 16, {I2CMux_0,SubBus_4,0x47}) // Board 7 Signals
HAL(PCA9685,248, 16, {I2CMux_0,SubBus_4,0x42}) // Board 9
HAL(PCA9685,136, 16, {I2CMux_0,SubBus_4,0x41}) // Board 9
//I2CDFPlayer::create(1st vPin,vPins,I2C address,UART{0|1},AM{0|1});
//HAL(I2CDFPlayer,1000, 4, {I2CMux_0,SubBus_3,0x4D}, 0)

HAL(HALDisplay<OLED>,3,{I2CMux_0,SubBus_3,0x3C},132,64)
HAL(HALDisplay<OLED>,2,{I2CMux_0,SubBus_1,0x3C},132,64)
HAL(HALDisplay<OLED>,4,{I2CMux_0,SubBus_4,0x3C},132,64)

//Included files

#include "myTurnoutAliases.h"
#include "myTurnouts.h"
#include "myTurnoutPairs.h"
#include "mySignalAliases.h"
#include "mySignals.h"
#include "myRoster.h"
#include "myDefinitions.h"
#include "myStartupSequence.h"
#include "myBlockDetectors.h"
#include "myBlocks.h"
#include "myBlockReserves.h"
#include "myRoutes.h"
#include "myAutoClose.h"

#include "DCC.h"
STEALTH_GLOBAL(
  void updateLocoScreen() {
    const byte loco_slots=22;
    static byte current_slot=loco_slots-1;
    static byte shown_speed[loco_slots]; // remember whats already shown
    static bool first_call=true;
    
    if (first_call) {
      first_call=false;
      for (int i=0; i<loco_slots; i++) shown_speed[i]=127;
    }
    
    // switch to next row
    current_slot= (current_slot + 1) % loco_slots;
    auto loco=DCC::speedTable[current_slot].loco;
    if (loco<0) return; // this slot is no longetr used
    if (loco==0) return; // we are beyond the last loco   
    
    auto speed = DCC::speedTable[current_slot].speedCode;
    if (speed== shown_speed[current_slot]) return; // no change in speed
    shown_speed[current_slot] = speed; // remember speed for next time

    auto direction = (speed & 0x80) ? 'F' : 'R';
    speed = speed & 0x7f;
    if (speed > 0) speed = speed - 1; // make it look like JMRI
    StringFormatter::lcd2(2, current_slot+2, F("Loco:%4d %3d %c"), loco, speed, direction);
    if (speed == 0) {
     // Handle stopped loco
     StringFormatter::lcd2(3, current_slot+2, F("Loco:%4d %3d %c"), loco, speed, direction);
     StringFormatter::lcd2(4, current_slot+2, F("Loco:%4d %3d %c"), loco, speed, direction);
   }
  }
)
HAL(UserAddin,updateLocoScreen,500) //Run loco status check every 500mS 



//Automations
//Standard Signal sequences
//Track A
AUTOSTART SEQUENCE(22)
  blockSequence(SIG_A1,BD_S2_A,BD_S6_A,BD_F9_A)
  FOLLOW(22)
AUTOSTART SEQUENCE(23)
  blockSequence(SIG_A2,BD_S5_A,BD_F9_A,BD_F8_A)
  FOLLOW(23)
AUTOSTART SEQUENCE(24)
  blockSequence(SIG_A3,BD_S8_A,BD_F8_A,BD_F7_A)
  FOLLOW(24)
AUTOSTART SEQUENCE(25)
  blockSequence(SIG_A4,BD_F9_A,BD_F7_A,BD_F6_A)
FOLLOW(25)
//Track B
AUTOSTART SEQUENCE(26)
  IFCLOSED(510)
    blockSequence(SIG_B1,BD_S2_B,BD_S6_B,BD_F9_B)
  ENDIF
  FOLLOW(26)
AUTOSTART SEQUENCE(27)
  blockSequence(SIG_B2,BD_S5_B,BD_F9_B,BD_F8_B)
  FOLLOW(27)
AUTOSTART SEQUENCE(28)
  blockSequence(SIG_B3,BD_S8_B,BD_F8_B,BD_F7_B)
  FOLLOW(28)
AUTOSTART SEQUENCE(29)
  blockSequence(SIG_D4,BD_F9_D,BD_F7_D,BD_F6_D)
FOLLOW(29)
//Track C
AUTOSTART SEQUENCE(30)
  blockSequence(SIG_C2,BD_S3_C,BD_F3_C,BD_F4_C)
  FOLLOW(30)
AUTOSTART SEQUENCE(31)
  blockSequence(SIG_C3,BD_S8_C,BD_S3_C,BD_F3_C)
  FOLLOW(31)
//Track D
IFNOT(AUTO_D)
AUTOSTART SEQUENCE(32)
  blockSequence(SIG_D1,BD_S2_D,BD_S6_D,BD_F9_D)
  FOLLOW(32)
AUTOSTART SEQUENCE(33)
  blockSequence(SIG_D2,BD_S5_D,BD_F9_D,BD_F8_D)
  FOLLOW(33)
AUTOSTART SEQUENCE(34)
  blockSequence(SIG_D3,BD_S8_D,BD_F8_D,BD_F7_D)
  FOLLOW(34)
  AUTOSTART SEQUENCE(35)
  blockSequence(SIG_D4,BD_F9_D,BD_F7_D,BD_F6_D)
  FOLLOW(35)
ENDIF
//Track E
AUTOSTART SEQUENCE(36)
  blockSequence(SIG_E2,BD_S3_E,BD_F3_E,BD_F4_E)
  FOLLOW(36)
AUTOSTART SEQUENCE(37)
  blockSequence(SIG_E3,BD_S9_E,BD_S3_E,BD_F3_E)
  FOLLOW(37)
//Track F
AUTOSTART SEQUENCE(38)
  blockSequence(SIG_F2,BD_S4_F,BD_F3_F,BD_F5_F)
  FOLLOW(38)
AUTOSTART SEQUENCE(39)
  blockSequence(SIG_F3,BD_S9_F1,BD_S4_F,BD_F3_F)
  FOLLOW(39)
//Holgate exit signal
//AUTOSTART SEQUENCE(37)
 // IFTHROWN(DGS_T2_A__HS_T1_E)
ONBUTTON(BD_S4_F)
  RED(SIG_H1)
 DONE 
 // ENDIF
//FOLLOW(37)

//Set SIG_E3 to Red E->Holgate
//ONBUTTON(BD_S9_F)
//  IFTHROWN(9030)
//    RED(SIG_E3)
//  ENDIF
//DONE

//Set SIG_F3 to Red F->Holgate
ONBUTTON(BD_S9_F)
  IFTHROWN(9031)
    RED(SIG_F3)
  ENDIF
DONE

//Set SIG_E3 to Red E->F
ONBUTTON(BD_S9_F)
  IFTHROWN(9022)
    RED(SIG_E3)
  ENDIF 
DONE
//Dispay signal status
#include "EXRAIL2.h"

STEALTH_GLOBAL(char rag(int16_t sigid) {
    if(RMFT2::isSignal(sigid,SIGNAL_RED)) return 'R';
    if(RMFT2::isSignal(sigid,SIGNAL_AMBER)) return 'Y';
    if(RMFT2::isSignal(sigid,SIGNAL_GREEN)) return 'G';
    return 'X';
} 
)

SEQUENCE(77)
IF(Latch_default)
SCREEN(2,0,"Gantry 1  4  7  9")
STEALTH( 
    StringFormatter::lcd2(2,1,
      F("A:     %c  %c  %c"),
      rag(123), rag(272), rag(280));
    StringFormatter::lcd2(2,2,
      F("B:     %c  %c  %c"),
      rag(126), rag(268), rag(284));
    StringFormatter::lcd2(2,3,
      F("C:        %c     %c"),
      rag(272), rag(248));
    StringFormatter::lcd2(2,4,
      F("D:     %c  %c  %c"),
      rag(129), rag(276), rag(288));
    StringFormatter::lcd2(2,5,
      F("E:        %c     %c"),
      rag(188), rag(252));
    StringFormatter::lcd2(2,6,
      F("F:        %c     %c"),
      rag(192), rag(256));
    StringFormatter::lcd2(2,7,
      F("H:       %c"),
      rag(429));
)
ENDIF 
DELAY(5000)
FOLLOW(77)



AUTOSTART SEQUENCE(180)
  ROUTE_HIDDEN(989)
  ROUTE_HIDDEN(990)
  ROUTE_HIDDEN(991)
  ROUTE_HIDDEN(992)
  //hide all yard clear buttons on boot
  //YARD B
  ROUTE_HIDDEN(290)
  ROUTE_HIDDEN(291)
  ROUTE_HIDDEN(292)
  ROUTE_HIDDEN(293)
  ROUTE_HIDDEN(294)
  //YARD D
  ROUTE_HIDDEN(490)
  ROUTE_HIDDEN(491)
  ROUTE_HIDDEN(492)
  ROUTE_HIDDEN(493)
  ROUTE_HIDDEN(494)

DONE

//include track automations
//#include "myTrackA.h"
//#include "myTrackF.h"
#include "myTrackB.h"
#include "myTrackD.h"
//#include "myTrackE.h"
#include "mySidingRoutes.h"

//Show Sensors
//JMRI_SENSOR(300,16) //BOARD 1 exio
//JMRI_SENSOR(348,16) //BOARD 1 mcp
//JMRI_SENSOR(300,32) //BOARD 2
//JMRI_SENSOR(400,32) //BOARD 3
//JMRI_SENSOR(500,16) //Board 3 signal
//JMRI_SENSOR(524,16)
//JMRI_SENSOR(600,32) //Board 4
//JMRI_SENSOR(700,16) //Board 5
//JMRI_SENSOR(600,32) //Board 6
//JMRI_SENSOR(700,16) //Board 7
//JMRI_SENSOR(716,16) //Board 7
//JMRI_SENSOR(800,16) //Board 8
//JMRI_SENSOR(900,16) //BOARD 9

/*
It's going yo be something like this: ( for loco 777) 
```cpp
STEALTH(
 auto task=loopTask;
  while(task) {
        if (task->loco==777) {
            task->kill(F("KILL"));
            break;
          }
        task=task->next;
        if (task==loopTask) break;
   }
)
   
*/