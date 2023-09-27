/*
* myTrackA.h
*
* Sequences for Track A
* Up Goods Slow
*
* V. 0.0.1
*  Setup basics
*  All Sequences start from Board 1 and end on Board 2
*
* V 0.1.0
* First single loop created
* All basic sequences created
*
*/


//Exit track A fiddle yard
SEQUENCE(Exit_A_Holding)
SCREEN(3,6,"Leaving Siding")
    RESERVE(A_Exit)
    RESERVE(B_Exit)
    IFTHROWN(9023)
      CLOSE(9023)
    ENDIF
    FWD(40)
    AT(B2_IR_A)
    FREE(A_Hold_Finish)
    DELAY(5000) //Remove
FOLLOW(Station__Header_App)

SEQUENCE(Station__Header_App)
SCREEN(3,6,"Moving to header")
    RESERVE(Stn_Head_App)
    IFTHROWN(9001)
      CLOSE(9001)
    ENDIF
    AT(B1_IR_A) //Board 1
    FREE(A_Exit)
    FREE(B_Exit)
    //Add BD here for station blockage
    //IF(BD_S1_AA) //If station occupied take avoiding action.
    //  CLOSE(UGS_T2_H)
    //ENDIF
    IFCLOSED(UGS_T2_H)
    DELAY(5000) //Remove
      FOLLOW(Head_Shunt_Access)
    ELSE 
    DELAY(5000) //Remove
      FOLLOW(Station_App_Stop)
    ENDIF
DONE

SEQUENCE(Station_App_Stop)
SCREEN(3,6,"Arriving at station")
  RESERVE(Station_A)
  AT(BD_S1_AA)
  RED(SIG_A1)
  DELAY(8000) //delay stopping at station for 8 seconds
  STOP
FOLLOW(Station_Exit)

SEQUENCE(Station_Exit)
SCREEN(3,6,"Leaving Station")
  DELAYRANDOM(10000,20000)
  RESERVE(AC_App)
  GREEN(SIG_A1)
  FWD(40)
  FREE(Stn_Head_App)
  DELAY(5000) // Remove
FOLLOW(AC_Approach)

SEQUENCE(AC_Approach)
  //IF(BD_S2_A) //Set block detector take avoinding action
  /*IFCLOSED(9004)
    RESERVE(B_Station_Pass)
    RESERVE(BC_App)
    THROW(9004)
  ENDIF*/
  SCREEN(3,6,"Approaching AC")
    RESERVE(AD_App)
    IF(BD_S2_A)
      RED(SIG_A1)
    ENDIF
    FREE(Station_A)
    DELAY(5000) // Remove
FOLLOW(AD_Approach)

SEQUENCE(AD_Approach)
SCREEN(3,6,"Approaching AD")
  RESERVE(A_Main)
  GREEN(SIG_A2)
  IFTHROWN(UGS_T4_A__UMF_T3_E)
    CLOSE(UGS_T4_A__UMF_T3_E)
    SPEED(50)
    PRINT("Delayed start")
    DELAY(3000)
  ENDIF
  DELAY(5000) //Remove
FOLLOW(AE_Approach)

SEQUENCE(Exit_A__Station_ByPass_UMF)
//Move to track B to bypass station, 
// and stay on Track B

FOLLOW(B_MAIN_Run)

SEQUENCE(Exit_A__Station_ByPass_UGS)
//Move to track B to bypass station
// then move back to track A

FOLLOW(AE_Approach)

SEQUENCE(AE_Approach)
SCREEN(3,6,"Approaching AE")
  AT(BD_S4_A)
  FREE(AC_App)
  AMBER(SIG_A1)
  RED(SIG_A2)
  GREEN(SIG_A3)
  IFTHROWN(UGS_T5_E__UFM_T6_A)
    CLOSE(UGS_T5_E__UFM_T6_A)
  ENDIF
  SPEED(90)
  DELAY(5000) //Remove
FOLLOW(AF_Approach)

SEQUENCE(AF_Approach)
SCREEN(3,6,"Approaching AF")
  AT(BD_S8_A)
  RED(SIG_A3)
  AMBER(SIG_A2)
  GREEN(SIG_A1)
  FREE(AD_App)
  SPEED(40)
  DELAY(5000) //Remove
FOLLOW(Yard_Access)

SEQUENCE(Yard_Access)
SCREEN(3,6,"Yard Access")
  AT(B9_IR_A)
  IFRESERVE(A_Hold_Start)
  DELAY(10000) //Remove
    CLOSE(9023)
    SPEED(20)
    GREEN(SIG_A2)
    AMBER(SIG_A3)
    DELAY(5000) //Remove
    FOLLOW(A_Pos1_Stop)
  ELSE //Take avoiding action, move to FYard B
    RESERVE(FB_App)
    THROW(9023)
    SPEED(20)
    FREE(A_Main)
    FOLLOW(BYard_Ladder_T1_A)
  ENDIF
  
SEQUENCE(A_Pos1_Stop)
SCREEN(3,6,"Stopping B7")
    AT(B7_IR_A)
    SCREEN(3,7,"Stopped at B7")
    GREEN(SIG_A3)
    RESERVE(A_Hold_Mid)
    FREE(A_Main)    
    DELAY(5000) //Remove
    SCREEN(3,7,"")
FOLLOW(A_Pos2_Stop)

SEQUENCE(A_Pos2_Stop)
SCREEN(3,6,"Stopping B5")
    AT(B5_IR_A_2)
    FREE(A_Hold_Start)
    RESERVE(A_Hold_Finish)  
    DELAY(5000) //Remove
FOLLOW(A_Pos3_Stop)

SEQUENCE(A_Pos3_Stop)
SCREEN(3,6,"Stopping B3")
  AT(B3_IR_A)
  STOP 
  FREE(A_Hold_Mid)
DONE

