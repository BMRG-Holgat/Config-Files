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
    FREE(USG_BK11_Hold)

SEQUENCE(USG_BK10__USG_BK11)
//insert BO detection here
    RESERVE(USG_BK11_Hold)
    FWD(10)
    AT(USG_SNS_11)
    STOP
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
SEQUENCE(USG_BK1_ST_App)
//insert BO detection here
    IFRESERVE(UGS_STN_Hold)
      IFCLOSED(UGS_T1_H)
        THROW(UGS_T1_H)
      ENDIF
    FWD(10)
    ENDIF
    //Insert signals here
    AT(USG_SNS_STN)
    STOP
    DELAYRANDOM(10000, 15000)
    //Insert Signal change here
    FOLLOW(USG_BK2_STN_EX)

//Header line
SEQUENCE(UGS_Head_Entry)
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
SEQUENCE(UGS_Head_Exit)
    //insert BO detection here for station-Fiddle yard
    IFRESERVE(UGS_STN_Hold)
        CLOSE(UGS_T1_H)
        REV(20)
        AFTER(SNS5_STN_TRN2_APP)
        FREE(UGS_BK2_HEAD_1_AA_Ex)
        STOP
        DELAY(5000)
    ENDIF
    FOLLOW(USG_BK1_ST_App)

       
//Exit Station Onto board 2
SEQUENCE(USG_BK2_STN_EX)
//insert BO detection here for boards 3-8
  RESERVE(UGS_BK4_3__8_Hold)
  IFTHROWN(UGS_T2_E__DFM_T1_A)
    //Set Signal Red
    DELAY(5000)
    CLOSE(UGS_T2_E__DFM_T1_A)
    IFTHROWN(UGS_T3_A__UFM_T3_E)
      CLOSE(UGS_T3_A__UFM_T3_E)
    ENDIF
  ENDIF
  FWD(50)
  AT(SNS6_TRN2_EX)
  FWD(30)
  FREE(UGS_STN_Hold)
  FOLLOW(UGS_BK5_9_Hold)
