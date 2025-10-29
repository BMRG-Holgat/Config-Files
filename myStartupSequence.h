/*myStartupSequence
*
* Kept now on github https://github.com/BMRG-Holgat/Config-Files.git
*
* This file is for reassembly testing of the layout before trains are run
*
*/
ALIAS(BIG_RED_BUTTON,175)
ALIAS(Latch_build,174)
ALIAS(Latch_default,173)
ALIAS(Latch_light,176)
ALIAS(Latch_light_house,180)
ALIAS(Latch_church,177)
ALIAS(Latch_display_3,178)
ALIAS(Latch_display_4,179)
ALIAS(Latch_House_1_Bed,180)
ALIAS(Latch_House_1_2_Bed,181)
ALIAS(autoSelected_B, 200) //Full auto Track B
ALIAS(autoRunning_B, 201) //Full auto Track B
ALIAS(autoSelected_C, 202) //Full auto Track C
ALIAS(autoRunning_C, 203) //Full auto Track B

//Route latches to prevent Signals changing
ALIAS(AUTO_A,210)
ALIAS(AUTO_B,211)
ALIAS(AUTO_C,212)
ALIAS(AUTO_D,213)
ALIAS(AUTO_E,214)
ALIAS(AUTO_F,215)

 ROUTE(997,"System: Rebuild test") //Testing system before starting
 IFNOT(Latch_build)
  IFNOT(Latch_default)
  POWERON
    PRINT("Testing Signals")
    SCREEN(2,0,"")
    SCREEN(2,1,"")
    DELAY(1000)
    signalTest
    DELAY(1000)
    PRINT("Testing Turnouts")
    turnoutTest
    DELAY(5000)
    LATCH(Latch_build)
  ENDIF
ENDIF
DONE

ROUTE(994,"System: Set Default Positions")
  IFNOT(Latch_default)
    SCREEN(2,0,"Setting Defaults")
    SCREEN(3,0,"Setting Defaults")
    SCREEN(4,0,"Setting Defaults")
    turnoutReset
    defaultPosition(UGS_T2_H) 
    defaultPosition(DGS_T4_A__DFM_T5_E) 
    defaultPosition(DGS_T5_A__DFM_T7_E)
    CLOSE(UFM_T4_A__DMF_T3_E)
    defaultPosition(DMF_T13_E__DMF_T12_A) // Set track 1 exit on Yard C.
    defaultPosition(DFM_T15_E__DFM_T14_A) //Set track 1 access on Yard E.
    PRINT("Setting all signals to green") 
    
    GREEN(SIG_A1) 
    GREEN(SIG_B1) 
    GREEN(SIG_D1)
    RED(SIG_H1) 
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
    GREEN(SIG_A4)
    GREEN(SIG_B4)
    GREEN(SIG_D4)
    GREEN(SIG_STN)
    LATCH(Latch_default)
    START(77)
    START(771)
    SCREEN(2,0,"System Ready")
    SCREEN(2,1,"")
    SCREEN(2,2,"") 
    SCREEN(3,0,"System Ready")
    SCREEN(4,0,"System Ready") 
  ELSE 
    SCREEN(2,0,"Defaults already set") 
    SCREEN(3,0,"Defaults already set") 
    SCREEN(4,0,"Defaults already set")  
  ENDIF 
  
DONE

ROUTE(996,"System: Full reset") // Reset all turnouts to closed position
  IFNOT(Latch_default)
    PRINT("Reseting turnouts")
    turnoutReset
    PRINT("All turnouts closed")
    FOLLOW(994)
  ELSE 
    PRINT("Cannot reset layout running")
  ENDIF 
DONE
/*
ROUTE(995,"System: End Session") // end Session setting
  PRINT("Ending Session")
  SCREEN(2,1,"Ending Session") 
  SCREEN(3,1,"Ending Session") 
  SCREEN(4,1,"Ending Session") 
  POWEROFF
  endSession
  UNLATCH(Latch_build)
  UNLATCH(Latch_default)
  PRINT("Shutdown now!")
  SCREEN(2,2,"Completed" )
  SCREEN(2,2,"Start ")
  SCREEN(4,2,"Dismantling")
DONE
*/


AUTOSTART SEQUENCE(998)
  AFTER(BIG_RED_BUTTON)
  START(999)
  DELAY(200)
FOLLOW(998)
 
 
ONOVERLOAD(A)
    LATCH(Latch_display_3)
    SCREEN(3,0,"OVERLOAD")
    SCREEN(3,1,"OVERLOAD District A")
    SCREEN(3,2,"POWER OFF")
    SCREEN(2,0,"OVERLOAD")
    SCREEN(2,1,"OVERLOAD District A")
    SCREEN(2,2,"POWER OFF")
    PRINT("Overload Detected on A - Turn Off Power")
    SET_TRACK(A, NONE)
    ROUTE_INACTIVE(992)
    AFTEROVERLOAD(A)
      SCREEN(3,1,"Restored District A")
      SCREEN(3,2,"  POWER ON")
      SCREEN(2,1,"Restored District A")
      SCREEN(2,2,"  POWER ON")
      PRINT("Overload cleared on District A - Power Restored")
      ROUTE_HIDDEN(992)
      DELAY(2000)
      SCREEN(3,0,"")
      SCREEN(3,1,"")
      SCREEN(3,2,"")
      SCREEN(2,0,"")
      SCREEN(2,1,"")
      SCREEN(2,2,"")
      UNLATCH(Latch_display_3)
DONE

ONOVERLOAD(B)
    LATCH(99)
    LATCH(Latch_display_3)
    LATCH(Latch_display_4)
    SCREEN(2,0,"OVERLOAD")
    SCREEN(2,5, "OVERLOAD Scenic")
    SCREEN(2,6," POWER OFF")
    SCREEN(3,0,"OVERLOAD")
    SCREEN(3,3, "OVERLOAD Scenic")
    SCREEN(3,4," POWER OFF")
    SCREEN(4,0,"OVERLOAD")
    SCREEN(4,3, "OVERLOAD Scenic")
    SCREEN(4,4," POWER OFF")
    PRINT("Overload Detected on Scenic - Turn Off Power")
    SET_TRACK(B, NONE)
    ROUTE_INACTIVE(991)
    AFTEROVERLOAD(B)
      SCREEN(2,5,"Restored Scenic")
      SCREEN(2,6,"   POWER ON")
      SCREEN(3,3,"Restored Scenic")
      SCREEN(3,4,"   POWER ON")
      SCREEN(4,3,"Restored Scenic")
      SCREEN(4,4,"   POWER ON")
      PRINT("Overload cleared on Scenic - Power Restored")
      ROUTE_HIDDEN(991)
      DELAY(2000)
      SCREEN(2,0,"")
      SCREEN(2,5,"")
      SCREEN(2,6,"")
      SCREEN(3,0,"")
      SCREEN(3,3,"")
      SCREEN(3,4,"")
      SCREEN(4,0,"")
      SCREEN(4,3,"")
      SCREEN(4,4,"")
      LATCH(Latch_display_3)
      LATCH(Latch_display_4)
DONE

ONOVERLOAD(C)
    LATCH(Latch_display_4)
    SCREEN(4,0,"OVERLOAD")
    SCREEN(4,1, "OVERLOAD District B ")
    SCREEN(4,2," POWER OFF")
    SCREEN(2,0,"OVERLOAD")
    SCREEN(2,3, "OVERLOAD District B ")
    SCREEN(2,4," POWER OFF")
    PRINT("Overload Detected on District B - Turn Off Power")
    SET_TRACK(C, NONE)
    ROUTE_INACTIVE(990)
    AFTEROVERLOAD(C)
      SCREEN(4,1,"Restored District B")
      SCREEN(4,2,"POWER ON")
      SCREEN(2,3,"Restored District B")
      SCREEN(2,4,"POWER ON")
      PRINT("Overload cleared on District B - Power Restored")
      ROUTE_HIDDEN(990)
      DELAY(2000)
      SCREEN(4,0,"")
      SCREEN(4,1,"")
      SCREEN(4,2,"")
      SCREEN(2,0,"")
      SCREEN(2,3,"")
      SCREEN(2,4,"")
      UNLATCH(Latch_display_4)
DONE

ONOVERLOAD(D)
    SCREEN(2,0,"OVERLOAD")
    SCREEN(2,6, "OVERLOAD Accessory ")
    SCREEN(2,7," POWER OFF")
    SCREEN(3,0,"OVERLOAD")
    SCREEN(3,5, "OVERLOAD Accessory ")
    SCREEN(3,6," POWER OFF")
    SCREEN(4,0,"OVERLOAD")
    SCREEN(4,5, "OVERLOAD Accessory ")
    SCREEN(4,6," POWER OFF")
    PRINT("Overload Detected on Accessory - Turn Off Power")
    SET_TRACK(D, NONE)
    ROUTE_INACTIVE(989)
    AFTEROVERLOAD(D)
      SCREEN(2,6,"Restored Accessory")
      SCREEN(2,7,"POWER ON")
      SCREEN(3,5,"Restored Accessory")
      SCREEN(3,6,"POWER ON")
      SCREEN(4,5,"Restored Accessory")
      SCREEN(4,6,"POWER ON")
      PRINT("Overload cleared on Accessory - Power Restored")
      ROUTE_HIDDEN(989)
      DELAY(2000)
      SCREEN(2,0,"")
      SCREEN(2,6,"")
      SCREEN(2,7,"")
      SCREEN(3,0,"")
      SCREEN(3,5,"")
      SCREEN(3,6,"")
      SCREEN(4,0,"")
      SCREEN(4,5,"")
      SCREEN(4,6,"")
DONE



ROUTE(992,"Power Reset: Reset District A")
    SET_TRACK(A, MAIN)
    SET_POWER(A, ON)
    DELAY(5000)
DONE

ROUTE(991,"Power Reset: Reset Scenic")
    SET_TRACK(B, MAIN)
    SET_POWER(B, ON)
    DELAY(5000)
    UNLATCH(99)
DONE

ROUTE(990,"Power Reset: Reset District B")
    SET_TRACK(C, MAIN)
    SET_POWER(C, ON)
    DELAY(5000)
DONE

ROUTE(989,"Power Reset: Reset Accessory")
    SET_TRACK(D, MAIN)
    SET_POWER(D, ON)
    DELAY(5000)
DONE


ROUTE(987,"System: Signal Test")
  signalTest
DONE

// BIG RED BUTTON!
ROUTE(999,"System: Stop/Resume")
  AFTER(BIG_RED_BUTTON)
    IF(Latch_build)
      RESUME
      SCREEN(2,1,"Resuming")
      SCREEN(3,1,"Resuming")
      SCREEN(4,1,"Resuming")
      UNLATCH(Latch_build)
      DONE 
    ENDIF   
    SCREEN(2,1,"Paused!")
    SCREEN(3,1,"Paused!")
    SCREEN(4,1,"Paused!")
      LATCH(Latch_build)
      PAUSE    
  IF(Latch_build) FOLLOW(999) ENDIF DONE


