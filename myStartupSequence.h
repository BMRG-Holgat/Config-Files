/*myStartupSequence
*
* Kept now on github https://github.com/BMRG-Holgat/Config-Files.git
*
* This file is for reassembly testing of the layout before trains are run
*
*/
ALIAS(BIG_RED_BUTTON,44)
 
 ROUTE(995,"System: Startup test") //Testing system before starting
 IFNOT(252)
  PRINT("Testing Signals")
  DELAY(1000)
  signalTest
  DELAY(1000)
  PRINT("Testing Turnouts")
  turnoutTest
  DELAY(5000)
  LATCH(252)
ENDIF
DONE

ROUTE(994,"System: Close all turnouts") // Reset all turnouts to closed position
    PRINT("Reseting turnouts")
    turnoutReset
    PRINT("All turnouts closed")
DONE

ROUTE(993,"System: End Session") // end Session setting
  PRINT("Ending Session")
  POWEROFF
  endSession
  UNLATCH(252)
  UNLATCH(254)
  PRINT("Shutdown now!")
DONE

// Fiddle yard auto turnout select
AUTOSTART SEQUENCE(991)
  AT(50) THROW(9118) DELAY(30000)
FOLLOW(991)

ROUTE(992,"System: Set Default Positions")
  IFNOT(254)
    turnoutReset
    defaultPosition(UGS_T2_H) 
    defaultPosition(DGS_T4_A__DFM_T5_E) 
    defaultPosition(DGS_T5_A__DFM_T7_E)
    defaultPosition(DMF_T6_A__DMF_T7_E) // Set track 1 exit on Yard C.
    defaultPosition(DFM_T15_E__DFM_T14_A) //Set track 1 access on Yard E.
    PRINT("Setting all signals to green") 
    GREEN(SIG_A1) 
    GREEN(SIG_B1) 
    GREEN(SIG_D1) 
    GREEN(SIG_A2) 
    GREEN(SIG_B2) 
    GREEN(SIG_C2) 
    GREEN(SIG_D2) 
    GREEN(SIG_E2) 
    GREEN(SIG_F2) 
    GREEN(SIG_A3) 
    GREEN(SIG_B3) 
    GREEN(SIG_C3) 
    GREEN(SIG_D3) 
    GREEN(SIG_E3) 
    GREEN(SIG_F3)
    LATCH(254)
  ENDIF
DONE

AUTOSTART SEQUENCE(998)
  AFTER(BIG_RED_BUTTON)
  START(999)
  DELAY(200)
FOLLOW(998)

// This resets normal DCC
ROUTE(11, "Set Up DCC on A & B")
        PRINT("Set up DCC on A & B")
        SET_TRACK(A, MAIN)
        SET_TRACK(B, MAIN)
        SET_TRACK(C, MAIN)
    DONE
    
ONOVERLOAD(A)
    LCD(7, "OVERLOAD A - POWEROFF")
    PRINT("Overload Detected on A - Turn Off Power")
    SET_TRACK(A, NONE)
DONE

ONOVERLOAD(B)
    LCD(7, "OVERLOAD B - POWEROFF")
    PRINT("Overload Detected on B - Turn Off Power")
    SET_TRACK(B, NONE)
DONE

ONOVERLOAD(C)
    LCD(7, "OVERLOAD C - POWEROFF")
    PRINT("Overload Detected on C - Turn Off Power")
    SET_TRACK(C, NONE)
DONE

ROUTE(12,"Reset A")
    LCD(7,"")
    SET_TRACK(A, MAIN)
    POWERON
DONE

ROUTE(13,"Reset B")
    LCD(7,"")
    SET_TRACK(B, MAIN)
    POWERON
DONE

ROUTE(14,"Reset C")
    LCD(7,"")
    SET_TRACK(C, MAIN)
    POWERON
DONE


// BIG RED BUTTON!
ROUTE(999,"System: Stop/Resume")
  AFTER(BIG_RED_BUTTON)
    IF(252)
      RESUME
      PRINT("Resuming")
      UNLATCH(252)
      DONE ENDIF   
    PRINT("Paused!")
      LATCH(252)
      PAUSE    
  IF(252) FOLLOW(999) ENDIF DONE


