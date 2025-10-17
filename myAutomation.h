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
HAL(PCA9685,432, 16,{I2CMux_0,SubBus_3,0x42}) // Board 3 House Lights
HAL(MCP23017,500,16,{I2CMux_0,SubBus_3,0x22}) // Board 4
HAL(MCP23017,516,16,{I2CMux_0,SubBus_3,0x21}) //Board 4
HAL(MCP23017,532,16,{I2CMux_0,SubBus_1,0x27}) //Board 5
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

//Testing BITMAPs
//HAL(Bitmap,10,64) //64x32 bitmap at vPin 100

//Included files

#include "myTurnoutAliases.h"
#include "myTurnouts.h"
#include "myTurnoutPairs.h"
#include "mySignalAliases.h"
#include "mySignals.h"
#include "myRoster.h"
#include "myDefinitions.h"
#include "myStartupSequence.h"
#include "myCurrentDetectors.h"
#include "myBlocks.h"
#include "myBlockReserves.h"
#include "myRoutes.h"
#include "myAutoClose.h"
#include "myAutoSignals.h"
#include "myStashAlias.h"

/*
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

//Need to work out how this modification works
 ATTENTION PLEASE- 
devel version 5.5.45 is going to be the last version where the locoTable is stored as an array.
This will affect you if you have STEALTH or STEALTH_GLOBAL code which examines the loco table and cause compilation errors in your myAutomation.h, and dont say you were not warned when STEALTH was invented!


From 5.5.46 onwards, each loco table entry is a separate object and they are chained together in memory. This allows me to hold much more information per slot (for sniffer, momentum, railcom and a few extras I have in mind for speed limits, tuning etc)  without having to reserve RAM in advance for a specific number of locos. This means that on a Mega, the balance between turnouts and locotable is more flexible and automatic  but the overall limit is slightly lower (unless I later add more RAM saving tricks to turnout definitions). The MAX_LOCOS definition no longer does anything because RAM is not allocated in advance, although there is the potential to force the limit if need be. 

STEALTH code that runs through the loco table must use the following type of construct..

 for (auto slot=LocoSlot::getFirst() ;  slot; slot=slot->getNext()) {
    auto locoid=slot->getLoco();
    auto speedCode=slot->getSpeedCode();
     and so on.
 }

Note: as locos are first used, they are added to the start of the list.
Forgetting locos are removed from the list, you don't need to check for zero id etc.

To obtain the slot for a given loco use 
  auto slot=LocoSLot::getSlot(locoid, false);
  if (!slot) ... loco not found. 

Many other LocoSlot fields are available through public getters and setters, please see LocoSlot.h for details.
*/


//Automations
//Standard Signal sequences
//Track A
/*AUTOSTART SEQUENCE(22)
  blockSequence(SIG_A1,CD_S2_A,CD_S6_A,CD_F9_A)
  FOLLOW(22)
AUTOSTART SEQUENCE(23)
  blockSequence(SIG_A2,CD_S5_A,CD_F9_A,CD_F8_A)
  FOLLOW(23)
AUTOSTART SEQUENCE(24)
  blockSequence(SIG_A3,CD_S8_A,CD_F8_A,CD_F7_A)
  FOLLOW(24)
AUTOSTART SEQUENCE(25)
  blockSequence(SIG_A4,CD_F9_A,CD_F7_A,CD_F6_A)
FOLLOW(25)

//Track B
AUTOSTART SEQUENCE(26)
    blockSequence(SIG_B1,CD_S2_B,CD_S6_B,CD_F9_B)
  FOLLOW(26)
AUTOSTART SEQUENCE(27)
  blockSequence(SIG_B2,CD_S5_B,CD_F9_B,CD_F8_B)
  FOLLOW(27)
AUTOSTART SEQUENCE(28)
  blockSequence(SIG_B3,CD_S8_B,CD_F8_B,CD_F7_B)
  FOLLOW(28)
AUTOSTART SEQUENCE(29)
  blockSequence(SIG_D4,CD_F9_D,CD_F7_D,CD_F6_D)
FOLLOW(29)


//Track C
AUTOSTART SEQUENCE(30)
  blockSequence(SIG_C2,CD_S3_C,CD_F3_C,CD_F4_C)
  FOLLOW(30)
AUTOSTART SEQUENCE(31)
  blockSequence(SIG_C3,CD_S8_C,CD_S3_C,CD_F3_C)
  FOLLOW(31)

//Track D
AUTOSTART SEQUENCE(32)
  blockSequence(SIG_D1,CD_S2_D,CD_S6_D,CD_F9_D)
  FOLLOW(32)
AUTOSTART SEQUENCE(33)
  blockSequence(SIG_D2,CD_S5_D,CD_F9_D,CD_F8_D)
  FOLLOW(33)
AUTOSTART SEQUENCE(34)
  blockSequence(SIG_D3,CD_S8_D,CD_F8_D,CD_F7_D)
  FOLLOW(34)
  AUTOSTART SEQUENCE(35)
  blockSequence(SIG_D4,CD_F9_D,CD_F7_D,CD_F6_D)
  FOLLOW(35)

//Track E
AUTOSTART SEQUENCE(36)
  blockSequence(SIG_E2,CD_S3_E,CD_F3_E,CD_F4_E)
  FOLLOW(36)
AUTOSTART SEQUENCE(37)
  blockSequence(SIG_E3,CD_S9_E1,CD_S3_E,CD_F3_E)
  FOLLOW(37)

//Track F
AUTOSTART SEQUENCE(38)
  blockSequence(SIG_F2,CD_S3_F,CD_F3_F,CD_F4_F)
  FOLLOW(38)
AUTOSTART SEQUENCE(39)
  blockSequence(SIG_F3,CD_S9_F1,CD_S3_F,CD_F3_F)
  FOLLOW(39)
*/
//Holgate exit signal

ONBUTTON(CD_S4_F)
  RED(SIG_H1)
 DONE 
 

//Set SIG_E3 to Red E->Holgate
//ONBUTTON(CD_S9_F)
//  IFTHROWN(9030)
//    RED(SIG_E3)
//  ENDIF
//DONE

//Set SIG_F3 to Red F->Holgate
ONBUTTON(CD_S9_F)
  IFTHROWN(9031)
    RED(SIG_F3)
  ENDIF
DONE

//Set SIG_E3 to Red E->F
ONBUTTON(CD_S9_F)
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
  //YARD C
  ROUTE_HIDDEN(390)
  ROUTE_HIDDEN(391)
  ROUTE_HIDDEN(392)
  ROUTE_HIDDEN(393)
  ROUTE_HIDDEN(394)
  //YARD D
  ROUTE_HIDDEN(490)
  ROUTE_HIDDEN(491)
  ROUTE_HIDDEN(492)
  ROUTE_HIDDEN(493)
  ROUTE_HIDDEN(494)
  //YARD E
  ROUTE_HIDDEN(590)
  ROUTE_HIDDEN(591)
  ROUTE_HIDDEN(592)
  ROUTE_HIDDEN(593)
  ROUTE_HIDDEN(594)

DONE

//include track automations
#include "myTrackA.h"
#include "myTrackB.h"
#include "myTrackC.h"
#include "myTrackD.h"
#include "myTrackE.h"
#include "myTrackF.h"
#include "mySidingRoutes.h"

//Show Sensors
//JMRI_SENSOR(316,16) //
//JMRI_SENSOR(348,16) //BOARD 1 mcp
//JMRI_SENSOR(300,32) //BOARD 2
//JMRI_SENSOR(400,32) //BOARD 3
//JMRI_SENSOR(516,32) //Board 3 signal
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

/*
#define STOPRES(x) \
IFRESERVE(x) \
ELSE  \
   STOP \
    DELAY(2000)  \
    RESERVE(x) \
  ENDIF
  */