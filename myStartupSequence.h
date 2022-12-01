/*myStartupSequence
*
* Kept now on github https://github.com/BMRG-Holgat/Config-Files.git
*
* This file is for reassembly testing of the layout before trains are run
*
*/
ALIAS(BIG_RED_BUTTON,44)
/*
AUTOSTART AUTOMATION(1000,"System Test")

 IFNOT(254) //read latch to prevent process running all the while
  IF(31) //Read button press
    LATCH(254) //Set latch
    FOLLOW(500)
  ENDIF
  FOLLOW(1000)
 ENDIF

 DONE
*/ 
 SEQUENCE(500) //Testing system before starting
  PRINT("Testing Signals")
  DELAY(3000)
  signalTest
  DELAY(5000)
  PRINT("Testing Turnouts")
  turnoutTest
  PARSE("<c>")
  DELAY(10000)
  

// BIG RED BUTTON!
AUTOSTART SEQUENCE(999)
  AT(BIG_RED_BUTTON)
  PARSE("<!>")
  DELAY(10000)
  FOLLOW(999)
