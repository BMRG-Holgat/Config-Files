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

//HAL(EXIOExpander,800,18,0x65)
/*HAL(MCP23017,318,16,{I2CMux_0,SubBus_3,0x26})
//HAL(EXIOExpander,858,16,{I2CMux_0,SubBus_3,0x25})// Houses on Board 3
//HAL(EXIOExpander,300, 18, {I2CMux_0,SubBus_3,0x69}) // Board 1
HAL(EXIOExpander,362, 62, {I2CMux_0,SubBus_3,0x61}) // Board 2
HAL(EXIOExpander,424, 62, {I2CMux_0,SubBus_3,0x62}) // Board 3
HAL(EXIOExpander,486, 62, {I2CMux_0,SubBus_3,0x63}) // Board 4 
/*
/*
HAL(EXIOExpander,548, 62, {I2CMux_0,SubBus_1,0x65}) // Board 5
HAL(EXIOExpander,610, 62, {I2CMux_0,SubBus_4,0x65}) // Board 6  
HAL(EXIOExpander,672, 62, {I2CMux_0,SubBus_4,0x66}) // Board 7
HAL(EXIOExpander,734, 62, {I2CMux_0,SubBus_4,0x67}) // Board 8
HAL(EXIOExpander,796, 62, {I2CMux_0,SubBus_4,0x68}) // Board 9 
*/
HAL(PCA9685,120, 16, {I2CMux_0,SubBus_3,0x40}) // Board 1
HAL(PCA9685,184, 16, {I2CMux_0,SubBus_3,0x43}) // Board 4 turnout and signals
HAL(PCA9685,264, 16, {I2CMux_0,SubBus_3,0x45}) // Board 4 (signals?)
HAL(PCA9685,280, 16, {I2CMux_0,SubBus_4,0x47}) // Board 7 Signals
HAL(PCA9685,248, 16, {I2CMux_0,SubBus_4,0x42}) // Board 9
//I2CDFPlayer::create(1st vPin,vPins,I2C address,UART{0|1},AM{0|1});
//HAL(I2CDFPlayer,1000, 4, {I2CMux_0,SubBus_3,0x4D}, 0)

HAL(HALDisplay<OLED>,3,{I2CMux_0,SubBus_1,0x3C},128,64)
HAL(HALDisplay<OLED>,2,{I2CMux_0,SubBus_1,0x3D},128,64)
HAL(HALDisplay<OLED>,4,{I2CMux_0,SubBus_0,0x3D},128,64)

  // Update displays with loco numbers and direction
//Shows current 8 locos running and direction on 2 screens


#include "myDefinitions.h"
#include "myBlocks.h"
#include "myTurnouts.h"
#include "myTurnoutAliases.h"
#include "myTurnoutPairs.h"
#include "mySignals.h"
#include "mySignalAliases.h"
#include "mySensors.h"
#include "myStartupSequence.h"
#include "myRoster.h"
#include "myRoutes.h"
#include "myBlockReserves.h"



//include track automations
#include "myTrackA.h"
AUTOSTART SEQUENCE(180)
  ROUTE_HIDDEN(989)
  ROUTE_HIDDEN(990)
  ROUTE_HIDDEN(991)
  ROUTE_HIDDEN(992)
DONE
//JMRI_SENSOR(300,18) //BOARD 1 exio
//JMRI_SENSOR(318,16) //BOARD 1 mcp
//JMRI_SENSOR(362,62) //BOARD 2
//JMRI_SENSOR(424,62) //BOARD 3
//JMRI_SENSOR(486,62) //Board 4
//JMRI_SENSOR(548,62) //Board 5
//JMRI_SENSOR(610,62) //Board 6
//JMRI_SENSOR(672,62) //Board 7
//JMRI_SENSOR(734,62) //Board 8
//JMRI_SENSOR(796,62) //BOARD 9



//Standard Signal sequences
//Track A
AUTOSTART SEQUENCE(22)
  blockSequence(SIG_A1,402,525,773)
  FOLLOW(22)
AUTOSTART SEQUENCE(23)
  blockSequence(SIG_A2,525,773,828)
  FOLLOW(23)
AUTOSTART SEQUENCE(24)
  blockSequence(SIG_A3,773,828,721)
  FOLLOW(24)
//Track B
AUTOSTART SEQUENCE(25)
  IFCLOSED(510)
    blockSequence(SIG_B1,403,629,764)
  ENDIF
  FOLLOW(25)
AUTOSTART SEQUENCE(26)
  blockSequence(SIG_B2,523,764,832)
  FOLLOW(26)
AUTOSTART SEQUENCE(27)
  blockSequence(SIG_B3,764,832,508)
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
  blockSequence(SIG_D1,398,519,817)
  FOLLOW(30)
AUTOSTART SEQUENCE(31)
  blockSequence(SIG_D2,519,766,830)
  FOLLOW(31)
AUTOSTART SEQUENCE(32)
  blockSequence(SIG_D3,766,830,668)
  FOLLOW(32)
//Track E
AUTOSTART SEQUENCE(33)
  blockSequence(SIG_E2,476,417,526)
  FOLLOW(33)
AUTOSTART SEQUENCE(34)
  blockSequence(SIG_E3,767,476,417)
  FOLLOW(34)
//Track F
AUTOSTART SEQUENCE(35)
  blockSequence(SIG_F2,527,380,483)
  FOLLOW(35)
AUTOSTART SEQUENCE(36)
  blockSequence(SIG_F3,768,527,380)
  FOLLOW(36)



AUTOMATION(53,"D: Mainline")
RESERVE(51)
FWD(30)
AT(304)
PRINT("REACHED 304")
RESERVE(52) //Reserve D 2&3
SPEED(50)
AT(398)
FREE(56)
RESERVE(53) //reserve D 4-7
FREE(51)
AT(817)
RESERVE(54) //Reserve D 9 
FREE(52)
AT(830)
RESERVE(55) //Reserve 8-6
FREE(43)
PRINT("REACHED 830")
SPEED(40)
AT(668)
  SPEED(1)
DONE


AUTOMATION(54,"D PARK")
SPEED(30)
IFCLOSED(UMF_T5_E__UMF_T6_A)
  AT(FYD_SNS2_T1_M)
  FREE(54)
  RESERVE(56)
  PRINT("FYD_SNS2_T1_M")
  SPEED(20)
  AT(FYD_SNS1_T1_F)
  FREE(55)
  PRINT("Y1 SENSOR")
  STOP 
ENDIF 
IFTHROWN(UMF_T6_E__UMF_T7_A)
  AT(FYD_SNS1_T2_F)
  PRINT("Y2 SENSOR")
  STOP 
ENDIF 
IFTHROWN(UMF_T7_E__UMF_T8_A)
  AT(FYD_SNS1_T3_F)
  PRINT("Y3 SENSOR")
  STOP 
ENDIF 
FOFF(0)
DONE


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
SCREEN(4,0,"Gantry 1  4  7  9")
STEALTH( 
    StringFormatter::lcd2(4,1,
      F("A:     %c  %c  %c"),
      rag(123), rag(272), rag(280));
    StringFormatter::lcd2(4,2,
      F("B:     %c  %c  %c"),
      rag(126), rag(268), rag(284));
    StringFormatter::lcd2(4,3,
      F("C:        %c     %c"),
      rag(272), rag(248));
    StringFormatter::lcd2(4,4,
      F("D:     %c  %c  %c"),
      rag(129), rag(276), rag(288));
    StringFormatter::lcd2(4,5,
      F("E:        %c     %c"),
      rag(188), rag(252));
    StringFormatter::lcd2(4,6,
      F("F:        %c     %c"),
      rag(192), rag(256));
    StringFormatter::lcd2(4,7,
      F("H:       %c"),
      rag(468));
)
ENDIF 
DELAY(5000)
FOLLOW(77)

/*StringFormatter::lcd2(2,3,
      F("B: %c   %c   %c"),
      rag(321), rag(507), rag(687));
    StringFormatter::lcd2(2,4,
      F("C:      %c   %c"),
      rag(510), rag(834));
    StringFormatter::lcd2(2,5,
      F("D: %c   %c   %c"),
      rag(324), rag(513), rag(731));
    StringFormatter::lcd2(2,6,
      F("E:      %c   %c"),
      rag(516), rag(831));
    StringFormatter::lcd2(2,7,
      F("F:      %c   %c"),
      rag(519), rag(828);
    StringFormatter::lcd2(2,8,
      F("H: %c"),
      rag(468));*/

