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
//#include "IO_HALDisplay.h"

#include "DCC.h"



//HAL(EXIOExpander,800,18,0x65)
//HAL(EXIOExpander,858,16,{I2CMux_0,SubBus_3,0x25})// Houses on Board 3
//HAL(EXIOExpander,300, 18, {I2CMux_0,SubBus_3,0x69}) // Board 1

//HAL(EXIOExpander,362, 62, {I2CMux_0,SubBus_3,0x61}) // Board 2
//HAL(EXIOExpander,424, 62, {I2CMux_0,SubBus_3,0x62}) // Board 3
HAL(EXIOExpander,432, 62, {I2CMux_0,SubBus_3,0x63}) // Board 4 
//HAL(EXIOExpander,734, 62, {I2CMux_0,SubBus_4,0x67}) // Board 8
//HAL(EXIOExpander,916, 62, {I2CMux_0,SubBus_4,0x68}) // Board 9 

HAL(MCP23017,318,16,{I2CMux_0,SubBus_3,0x26}) //Board 1
HAL(MCP23017,400,16,{I2CMux_0,SubBus_3,0x27}) //Board 3
HAL(MCP23017,416,16,{I2CMux_0,SubBus_3,0x24}) //Board 3 //signals & street lights
HAL(MCP23017,500,16,{I2CMux_0,SubBus_1,0x27}) //Board 5
HAL(MCP23017,600,16,{I2CMux_0,SubBus_4,0x27}) // Board 6
HAL(MCP23017,700,16,{I2CMux_0,SubBus_4,0x26}) // Board 7
HAL(MCP23017,716,16,{I2CMux_0,SubBus_4,0x25}) // Board 7
HAL(MCP23017,800,16,{I2CMux_0,SubBus_4,0x23}) // Board 8 
HAL(MCP23017,900,16,{I2CMux_0,SubBus_4,0x24}) // Board 9
HAL(PCA9685,120, 16, {I2CMux_0,SubBus_3,0x40}) // Board 1
HAL(PCA9685,184, 16, {I2CMux_0,SubBus_3,0x43}) // Board 4 turnout and signals
HAL(PCA9685,264, 16, {I2CMux_0,SubBus_3,0x45}) // Board 4 (signals?)
HAL(PCA9685,280, 16, {I2CMux_0,SubBus_4,0x47}) // Board 7 Signals
HAL(PCA9685,248, 16, {I2CMux_0,SubBus_4,0x42}) // Board 9
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
#include "mySensors.h"
#include "myRoutes.h"
#include "myAutoClose.h"




//Automations
//Standard Signal sequences
//Track A
AUTOSTART SEQUENCE(22)
  blockSequence(SIG_A1,BD_S2_A,BD_S6_A,BD_F8_A)
  FOLLOW(22)
AUTOSTART SEQUENCE(23)
  blockSequence(SIG_A2,BD_S4_A,BD_F8_A,828)
  FOLLOW(23)
AUTOSTART SEQUENCE(24)
  blockSequence(SIG_A3,BD_S8_A,828,721)
  FOLLOW(24)
//Track B
AUTOSTART SEQUENCE(25)
  IFCLOSED(510)
    blockSequence(SIG_B1,BD_S2_B,BD_S6_B,764)
  ENDIF
  FOLLOW(25)
AUTOSTART SEQUENCE(26)
  blockSequence(SIG_B2,BD_S4_B,764,832)
  FOLLOW(26)
AUTOSTART SEQUENCE(27)
  blockSequence(SIG_B3,BD_S8_B,832,508)
  FOLLOW(27)
//Track C
AUTOSTART SEQUENCE(28)
  blockSequence(SIG_C2,451,319,386)
  FOLLOW(28)
AUTOSTART SEQUENCE(29)
  blockSequence(SIG_C3,770,451,319)
  FOLLOW(29)
//Track D
AUTOSTART SEQUENCE(30)
  blockSequence(SIG_D1,BD_S2_D,BD_S6_D,817)
  FOLLOW(30)
AUTOSTART SEQUENCE(31)
  blockSequence(SIG_D2,BD_S4_D,766,830)
  FOLLOW(31)
AUTOSTART SEQUENCE(32)
  blockSequence(SIG_D3,BD_S8_D,830,668)
  FOLLOW(32)
//Track E
AUTOSTART SEQUENCE(33)
  blockSequence(SIG_E2,BD_S3_E,BD_F4_E,BD_F4_E)
  FOLLOW(33)
AUTOSTART SEQUENCE(34)
  blockSequence(SIG_E3,BD_S9_E,BD_S3_E,BD_F4_E)
  FOLLOW(34)
//Track F
AUTOSTART SEQUENCE(35)
  blockSequence(SIG_F2,BD_S4_F,BD_F5_F,BD_F5_F)
  FOLLOW(35)
AUTOSTART SEQUENCE(36)
  blockSequence(SIG_F3,BD_S9_F,BD_S4_F,SNS_UGS_B3)
  FOLLOW(36)
//Holgate exit signal
//AUTOSTART SEQUENCE(37)
 // IFTHROWN(DGS_T2_A__HS_T1_E)
ONBUTTON(BD_S4_F)
  RED(SIG_H1)
 DONE 
 // ENDIF
//FOLLOW(37)

//Set SIG_E3 to Red E->Holgate
ONBUTTON(BD_S9_F)
  IFTHROWN(9030)
    RED(SIG_E3)
  ENDIF
DONE

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
      rag(416));
)
ENDIF 
DELAY(5000)
FOLLOW(77)



AUTOSTART SEQUENCE(180)
  ROUTE_HIDDEN(989)
  ROUTE_HIDDEN(990)
  ROUTE_HIDDEN(991)
  ROUTE_HIDDEN(992)
DONE

//include track automations
#include "myTrackA.h"
#include "myTrackF.h"
 

//Show Sensors
//JMRI_SENSOR(300,18) //BOARD 1 exio
JMRI_SENSOR(318,16) //BOARD 1 mcp
JMRI_SENSOR(362,62) //BOARD 2
JMRI_SENSOR(400,16) //BOARD 3
//JMRI_SENSOR(416,16) //Board 3 signal
//JMRI_SENSOR(432,62) //Board 4
//JMRI_SENSOR(500,16) //Board 5
//JMRI_SENSOR(600,16) //Board 6
//JMRI_SENSOR(700,16) //Board 7
//JMRI_SENSOR(716,16) //Board 7
JMRI_SENSOR(800,16) //Board 8
JMRI_SENSOR(900,16) //BOARD 9