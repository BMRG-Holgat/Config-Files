/*myStartupSequence
*
* Kept now on github https://github.com/BMRG-Holgat/Config-Files.git
*
* This file is for reassembly testing of the layout before trains are run
*
*/
ALIAS(BIG_RED_BUTTON,44)
 
 ROUTE(995,"Test turnouts and signals") //Testing system before starting
 IFNOT(252)
  PRINT("Testing Signals")
  DELAY(1000)
  signalTest
  DELAY(1000)
  PRINT("Testing Turnouts")
  turnoutTest
  DELAY(5000)
  LATCH(252)
  LATCH(254)
ENDIF
DONE

SEQUENCE(501) // Reset all turnouts to closed position
    PRINT("Reseting turnouts")
    turnoutReset
    PRINT("All turnouts closed")
DONE

// Reserve all fiddle yard blocks
AUTOSTART SEQUENCE(998)
 //RESERVE(21)
 //RESERVE(22)
 //RESERVE(23)

DONE

ROUTE(997,"Set Default Positions")
  IFNOT(254)
    defaultPosition(UGS_T1_H)
    defaultPosition(DGS_T4_A__DFM_T5_E)
    LATCH(254)
  ENDIF
DONE

// BIG RED BUTTON!
AUTOSTART SEQUENCE(999)
  AT(BIG_RED_BUTTON)
  PARSE("<!>")
  DELAY(10000)
  FOLLOW(999)


