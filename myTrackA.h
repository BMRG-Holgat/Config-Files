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
SCREEN(2,1,"Leaving Siding")
    RESERVE(A_Exit)
    RESERVE(B_Exit)
    IFTHROWN(9023)
      CLOSE(9023)
      FREE(B_Exit)
    ENDIF
    FWD(40)
    AT(B2_IR_A)
    FREE(A_Hold_Finish)
    DELAY(5000) //Remove
FOLLOW(Station__Header_App)



SEQUENCE(Station__Header_App)
    //Add BD here for station blockage
    IF(BD_S1_AA) //If station occupied take avoiding action.
      CLOSE(UGS_T2_H)
    ENDIF
    IFCLOSED(UGS_T2_H) //AB
    DELAY(5000) //Remove
      FOLLOW(Head_Shunt_Access)
    ELSE 
    DELAY(5000) //Remove
      RED(SIG_A1)
      FOLLOW(Station_App_Stop)
    ENDIF
DONE


SEQUENCE(Head_Shunt_Access)
  RESERVE(Stn_Head_App)
  SPEED(15)
  AT(300) //replace with BD value
  STOP
  FREE(A_Exit)
DONE


SEQUENCE(Station_App_Stop)
SCREEN(2,1,"Arriving at station")
  RESERVE(Station_A)
  AT(BD_S1_AA) //block detector  
  STOP
FOLLOW(Station_Exit)

SEQUENCE(Station_Exit)
SCREEN(2,1,"Leaving Station")
  DELAYRANDOM(10000,20000)
  RESERVE(AC_App)
  IFTHROWN(9004) //AC
    CLOSE(9004)
  ENDIF
  GREEN(SIG_A1)
  FWD(40)
  FREE(Stn_Head_App)
FOLLOW(AC_Approach)

SEQUENCE(AC_Approach)
  IFNOT(BD_S2_A) //Set block detector board 2 take avoiding action
    IFNOT(BD_S3_A) //Set block detector board 3 avoiding action  
        SCREEN(2,1,"Approaching AC")
        PRINT("Approaching AC")
        RESERVE(AD_App)
        IF(BD_S2_A)
          RED(SIG_A1)
        ENDIF
        FREE(Station_A)
        FOLLOW(AD_Approach)
    ELSE
      LATCH(AC_ByPass)
      PRINT("BD_S3 activated")
    ENDIF
  ELSE
   LATCH(AC_ByPass)
   PRINT("BD_S2 activated")
  ENDIF
  IF(AC_ByPass)
  SCREEN(2,1,"ByPassing AC")
    IFCLOSED(9004)
        RESERVE(B_Station_Pass)
        RESERVE(BC_App)
        RED(SIG_B1)
        IFCLOSED(9004)
          THROW(9004)
        ENDIF
        FOLLOW(ByPass_AD_Approach)
    ENDIF
  ENDIF

//Bypass split train detector
SEQUENCE(ByPass_AD_Approach)
  IF(AC_ByPass)
    RESERVE(A_Main)
    SPEED(50)
    IFCLOSED(9007)
      THROW(9007)
    ENDIF  
  ENDIF
FOLLOW(AE_Approach)

SEQUENCE(AD_Approach)
SCREEN(2,1,"Approaching AD")
RESERVE(A_Main)
  IFTHROWN(9007) //Double slip
    CLOSE(9007)  
  ENDIF 
  GREEN(SIG_A2) 
  SPEED(50) 
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
SCREEN(2,1,"Approaching AE")
  AT(BD_S4_A)
  IF(AC_ByPass)
    FREE(B_Station_Pass)
    FREE(BC_App)
    GREEN(SIG_B1)
    UNLATCH(AC_ByPass)
  ENDIF
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
SCREEN(2,1,"Approaching AF")
  AT(BD_S8_A)
  RED(SIG_A3)
  AMBER(SIG_A2)
  GREEN(SIG_A1)
  FREE(AD_App)
  SPEED(40)
  DELAY(5000) //Remove
FOLLOW(Yard_Access)

SEQUENCE(Yard_Access)
SCREEN(2,1,"Yard Access")
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
SCREEN(2,1,"Stopping B7")
    AT(B7_IR_A)
    SCREEN(2,1,"Waiting @ B7")
    GREEN(SIG_A3)
    RESERVE(A_Hold_Mid)
    FREE(A_Main)    
FOLLOW(A_Pos2_Stop)

SEQUENCE(A_Pos2_Stop)
SCREEN(2,1,"Stopping B5")
    AT(B5_IR_A_2)
    SCREEN(2,1,"Waiting @ B5")
    FREE(A_Hold_Start)
    RESERVE(A_Hold_Finish)  
    DELAY(5000) //Remove
FOLLOW(A_Pos3_Stop)

SEQUENCE(A_Pos3_Stop)
SCREEN(2,1,"Stoped B3")
  AT(B3_IR_A)
  STOP 
  FREE(A_Hold_Mid)
DONE

