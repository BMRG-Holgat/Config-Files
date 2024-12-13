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


#include "myDefinitions.h"
#include "myTurnouts.h"
#include "myTurnoutAliases.h"
#include "myTurnoutPairs.h"
#include "mySignals.h"
#include "mySignalAliases.h"
#include "mySensors.h"
#include "myStartupSequence.h"
#include "myRoster.h"
#include "myRoutes.h"



//JMRI_SENSOR(300,18)
//JMRI_SENSOR(318,16) //BOARD 1
//JMRI_SENSOR(362,62) //BOARD 2
//JMRI_SENSOR(424,62) //BOARD 3
//JMRI_SENSOR(486,62) //Board 4
//JMRI_SENSOR(548,62) //Board 5
//JMRI_SENSOR(610,62) //Board 6
//JMRI_SENSOR(734,62) //Board 8
//JMRI_SENSOR(796,62) //BOARD 9

AUTOMATION(43,"TRACK A TEST")
RESERVE(1)
FWD(40)
  AT(322)
  FREE(5)
  PRINT("FREED 5")
  IFCLOSED(UGS_T2_H)
    THROW(UGS_T2_H)
  ENDIF
  RED(SIG_A1)
    AT(322)
    FON(2)
    AFTER(322)
    FOFF(2)    
FOLLOW(44)

SEQUENCE(44)
  AT(308)
  DELAY(500)
  STOP 
  DELAYRANDOM(10000,15000)
  RESERVE(2)
  GREEN(SIG_A1)
  FON(4)
  DELAY(500)
  FOFF(4)
  DELAY(300)
  FON(3)
  DELAY(300)
  FOFF(3)
  FWD(40)
FOLLOW(45)

SEQUENCE(45)
PRINT("AT 45)")
 AFTER(308)
 RED(SIG_A1)
 SPEED(70)
 PRINT("FREE 1")
 FREE(1)
FOLLOW(46)

SEQUENCE(46)
AT(525)
AMBER(SIG_A1)
AFTER(704)
RESERVE(3)
FREE(2)
GREEN(123)
FOLLOW(47)

SEQUENCE(47)
AT(828)
RESERVE(4)
FREE(3)
SPEED(40)
FOLLOW(48)

SEQUENCE(48)
AT(721)
RESERVE(5)
FREE(4)
FOLLOW(49)

SEQUENCE(49)
SPEED(40)
 AT(482)
 STOP
DONE 


//Standard Signal sequences
//Track A
AUTOSTART SEQUENCE(22)
  blockSequence(SIG_A1,396,525,772)
  FOLLOW(22)
AUTOSTART SEQUENCE(23)
  blockSequence(SIG_A2,525,772,828)
  FOLLOW(23)
AUTOSTART SEQUENCE(24)
  blockSequence(SIG_A3,772,828,721)
  FOLLOW(24)
//Track B
AUTOSTART SEQUENCE(25)
  IFCLOSED(510)
    blockSequence(SIG_B1,395,523,764)
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

/*
AUTOSTART ROUTE(60,"SIG TEST")
   AFTER(818)
    IFGREEN(SIG_F3)
        RED(SIG_F3)
    ENDIF
    DELAY(10000)
    AMBER(SIG_F3)
    DELAY(10000)
    GREEN(SIG_F3) 
FOLLOW(60)

AUTOSTART SEQUENCE(61)
    AFTER(825)
    IFAMBER(SIG_B3)
        DELAY(5000)
        GREEN(SIG_B3)
    ENDIF
DONE

*/
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
      rag(272), rag(262));
    StringFormatter::lcd2(4,4,
      F("D:     %c  %c  %c"),
      rag(129), rag(276), rag(288));
    StringFormatter::lcd2(4,5,
      F("E:        %c     %c"),
      rag(188), rag(259));
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