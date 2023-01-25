/*
* myTrackA.h
*
* Sequences for Track A
*
* V. 0.0.1
*  Setup basics
*/

//Fiddle yard hold sequence

SEQUENCE(USG_BK11__USG_BK12)
 //insert BO detection here
    RESERVE(USG_BK12_Hold)
    FWD(10)
    AT(USG_SNS_12)
    STOP
    PRINT("STOPPED")
    FREE(USG_BK11_Hold)
    DONE


SEQUENCE(USG_BK10__USG_BK11)
//insert BO detection here
    RESERVE(USG_BK11_Hold)
    FWD(10)
    DELAY(5000)
 //   AT(USG_SNS_11)
 //   STOP
    FREE(USG_BK10_Hold)
    FOLLOW(USG_BK11__USG_BK12)

SEQUENCE(USG_BK9__USG_BK10)
//insert BO detection here
    RESERVE(USG_BK10_Hold)
    FWD(10)
    AT(USG_SNS_10)
    STOP
    FREE(USG_BK9_Hold)
    FOLLOW(USG_BK10__USG_BK11)
//End fiddle yard hold sequence

//Enter fiddle yard B bypass
SEQUENCE(USG_BK8__USG_BK9)
//insert BO detection here
    RESERVE(USG_BK9_Hold)
    FWD(10)
    AT(USG_SNS_9)
    STOP
    FREE(UGS_BK8_BF_App)
    FOLLOW(USG_BK9__USG_BK10)

//Station Approach from A and stop
SEQUENCE(UGS_BK1_ST_App) // seq 600
//insert BO detection here
    IFRESERVE(UGS_BK1_Stn_App)
     IFRESERVE(UGS_BK2_HEAD_1_AA_Ex)
        IFCLOSED(UGS_T1_H)
          THROW(UGS_T1_H)
        ENDIF
      ENDIF
      RESERVE(UGS_STN_Hold)
      FWD(10)
    ENDIF
    //Insert signals here
    AT(USG_SNS_STN)
    STOP
    PRINT("Stopped at station")
    FREE(USG_BK12_Hold)
    DELAYRANDOM(10000, 15000)
    //Insert Signal change here
    FOLLOW(USG_BK2_STN_EX)

//Header line
SEQUENCE(UGS_Head_Entry) //seq 601
//insert BO detection here for station
 //Check BO on header
    RESERVE(UGS_STN_Hold)  
    IFTHROWN(UGS_T1_H) //Header Point
       CLOSE(UGS_T1_H)
       RESERVE(UGS_BK2_HEAD_1_AA_Ex)
       FWD(20)
       AT(USG_Head_End)
       STOP
       FREE(UGS_STN_Hold)
DONE

//Leave Header Line and go back to Fiddle Yard
SEQUENCE(UGS_Head_Exit) // seq 602
    //insert BO detection here for station-Fiddle yard
    IFRESERVE(UGS_STN_Hold)
        CLOSE(UGS_T1_H)
        REV(20)
        AFTER(SNS5_STN_TRN2_APP)
        FREE(UGS_BK2_HEAD_1_AA_Ex)
        STOP
        DELAY(5000)
    ENDIF
    FOLLOW(UGS_BK1_ST_App)

       
//Exit Station Onto board 2
SEQUENCE(USG_BK2_STN_EX) // seq 603
//insert BO detection here for boards 3-8
  IFRESERVE(UGS_BK4_3__8_Hold)
    IFTHROWN(UGS_T2_E__DFM_T1_A)
    //Set Signal Red
      DELAY(5000)
      CLOSE(UGS_T2_E__DFM_T1_A)
      IFTHROWN(UGS_T3_A__UFM_T3_E)
        CLOSE(UGS_T3_A__UFM_T3_E)
      ENDIF
    ENDIF
    FWD(30)
    AT(SNS6_TRN2_STN_EX)
    FWD(50)
    FREE(UGS_BK1_Stn_App)
    FREE(UGS_BK2_HEAD_1_AA_Ex)
    FREE(UGS_STN_Hold)
  ENDIF
  FOLLOW(USG_BK8__USG_BK9)

//Main run to board 9
SEQUENCE(USG_BK8__USG_BK9)
  //Insert BO for board 9    
  IFRESERVE(UGS_BK5_9_Hold)
    IFTHROWN(UGS_T4_E__UFM_T5_A)
      CLOSE(UGS_T4_E__UFM_T5_A)
      FREE(UGS_BK4_3__8_Hold)
    ENDIF
  ELSE
    FWD(30)
    AT(SNS7_MAIN_TRN3_APP)
    STOP
  ENDIF
FOLLOW(USG_BK8__USG_BK9)

// Switch tracks from UGS to UFM
//SEQUENCE(UGS_BK8__UFM_BK9)


//Move Track A into B Fiddle yard
SEQUENCE(UGS__BF_A)
  //insert BO here
  RESERVE(UMF_BK10_9_Hold)
  RESERVE(FB_App)
  trackChange(UGS_T5_E__FYUG_T7_A,UFM_T6_A__UGS_T5_E)
  FWD(10)
  FOLLOW(FYard_Ladder_T1_A)
  
  
DONE

