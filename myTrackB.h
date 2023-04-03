/*
* myTrackB.h
*
* Sequences for Track B
* Up Mixed Freight
*
* V. 0.0.1
*  Setup basics
*  All Sequences start from Board 1 and end on Board 2
*/

// Start routines for track B
// Sets up from Station app


//Fiddle yard B
//Test ladder Entrance
SEQUENCE(FYard_Ladder_T1_A)
  IFRESERVE(FB_T1_A_Hold)
    closeFiddleYardLadder(UMF_T7_E__UMF_T8_A)
    forwardStop(10,SNS_FB_T1_A)
    FREE(FB_App)
    FOLLOW(FYard_Ladder_T1_E)
  ENDIF
  FOLLOW(FYard_Ladder_T2_A)
  

SEQUENCE(FYard_Ladder_T2_A)
  IFRESERVE(FB_T2_A_Hold)
    throwFiddleYardLadder(UMF_T7_E__UMF_T8_A)
    throwFiddleYardLadder(UFM_T8_E__UMF_T9_A)
    forwardStop(10,SNS_FB_T2_A) 
    FREE(FB_App)
    FOLLOW(FYard_Ladder_T2_E)
  ENDIF
  FOLLOW(FYard_Ladder_T3_A)

  SEQUENCE(FYard_Ladder_T3_A)
  IFRESERVE(FB_T3_A_Hold)
    closeFiddleYardLadder(UFM_T8_E__UMF_T9_A)
    throwFiddleYardLadder(UMF_T9_E__UMF_T10_A)
    forwardStop(10,SNS_FB_T3_A)
    FREE(FB_App) 
    FOLLOW(FYard_Ladder_T3_E)    
  ENDIF 
  FOLLOW(FYard_Ladder_T4_A)
 
  SEQUENCE(FYard_Ladder_T4_A)
  IFRESERVE(FB_T4_A_Hold)
    closeFiddleYardLadder(UMF_T9_E__UMF_T10_A)
    throwFiddleYardLadder(UMF_T10)
    forwardStop(10,SNS_FB_T4_A)
    FREE(FB_App) 
    FOLLOW(FYard_Ladder_T4_E)
  ENDIF 
  FOLLOW(FYard_Ladder_T5_A)

  SEQUENCE(FYard_Ladder_T5_A)
  IFRESERVE(FB_T5_A_Hold)   
    closeFiddleYardLadder(UMF_T10)
    forwardStop(10,SNS_FB_T5_A) 
    FREE(FB_App)
    FOLLOW(FYard_Ladder_T5_E)
  ENDIF

  //Fiddle yard ladder 2nd stage
  SEQUENCE(FYard_Ladder_T1_E)
    RESERVE(FB_T1_E_Hold)
    forwardStop(10,SNS_FB_T1_E)
    FREE(FB_T1_A_Hold)
  DONE

  SEQUENCE(FYard_Ladder_T2_E)
    RESERVE(FB_T2_E_Hold)
    forwardStop(10,SNS_FB_T2_E)
    FREE(FB_T2_A_Hold)
  DONE

  SEQUENCE(FYard_Ladder_T3_E)
    RESERVE(FB_T3_E_Hold)
    forwardStop(10,SNS_FB_T3_E)
    FREE(FB_T3_A_Hold)
  DONE

  SEQUENCE(FYard_Ladder_T4_E)
    RESERVE(FB_T4_E_Hold)
    forwardStop(10,SNS_FB_T4_E)
    FREE(FB_T4_A_Hold)
  DONE

  SEQUENCE(FYard_Ladder_T5_E)
    RESERVE(FB_T5_E_Hold)
    forwardStop(10,SNS_FB_T5_E)
    FREE(FB_T5_A_Hold)
  DONE

//Fiddle yard ladder exit to layout



//Test fiddleyard
SEQUENCE(619)
  RESERVE(FB_App)
  FWD(10)
  FOLLOW(FYard_Ladder_T1_A)