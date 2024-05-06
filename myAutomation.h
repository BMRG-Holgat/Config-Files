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


#include "myTurnouts.h"
#include "myTurnoutAliases.h"
#include "myTurnoutPairs.h"
#include "mySignals.h"
#include "mySignalAliases.h"
#include "myDefinitions.h"
#include "myStartupSequence.h"




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

#include "EXRAIL2.h"

STEALTH_GLOBAL(char rag(int16_t sigid) {
    if(RMFT2::isSignal(sigid,SIGNAL_RED)) return 'R';
    if(RMFT2::isSignal(sigid,SIGNAL_AMBER)) return 'A';
    if(RMFT2::isSignal(sigid,SIGNAL_GREEN)) return 'G';
    return 'X';
} 
)

SEQUENCE(77)
IF(Latch_default)
SCREEN(2,0,"Signal Status")
STEALTH( 
    StringFormatter::lcd2(2,1,
      F("A: %c   %c   %c"),
      rag(318), rag(504), rag(714));
    StringFormatter::lcd2(2,2,
      F("B: %c   %c   %c"),
      rag(321), rag(507), rag(687));
    StringFormatter::lcd2(2,3,
      F("C:     %c   %c"),
      rag(510), rag(834));
    StringFormatter::lcd2(2,4,
      F("D: %c   %c   %c"),
      rag(324), rag(513), rag(731));
    StringFormatter::lcd2(2,5,
      F("E:     %c   %c"),
      rag(516), rag(831));
    StringFormatter::lcd2(2,6,
      F("F:     %c   %c"),
      rag(519), rag(828));
    StringFormatter::lcd2(2,7,
      F("H: %c"),
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