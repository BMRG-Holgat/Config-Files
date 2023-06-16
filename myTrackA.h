/*
* myTrackA.h
*
* Sequences for Track A
* Up Goods Slow
*
* V. 0.0.1
*  Setup basics
*  All Sequences start from Board 1 and end on Board 2
*/

//Exit track A fiddle yard
SEQUENCE(UGS_FY_Ex_App)
  IFTHROWN(UGS_T6_A__FYUG_T10_E)
    trackChange(UGS_T6_A__FYUG_T10_E,UMF_T15_E__UGS_T6_A)
  ENDIF
FOLLOW(UGS_FY_Ex)

SEQUENCE(UGS_FY_Ex)
  RESERVE(UGS_FY_Exit)
  FWD(40)
  AT(SNS1_MAIN_TRN1_APP)
  IFCLOSED(UGS_T6_A__FYUG_T10_E)
    FREE(USG_BK12_Hold)
  ELSE 
    FREE(UMF_FY_Ex)
  ENDIF
FOLLOW(UGS_BK1_ST_App)

//Station Approach and stop
SEQUENCE(UGS_BK1_ST_App) // seq 600
//insert BO detection here
IF(BD_S1_A) // Board 1 AA turnout approach block detector
RESERVE(UGS_BK1_Stn_App)
PRINT("UGS_BK1_Stn_App Reserved!")
  RED(SIG_A1) // Set signals to red
    IFCLOSED(UGS_T1_H)
      THROW(UGS_T1_H)
    ENDIF
      RESERVE(UGS_STN_Hold)
      FWD(40)
    
    AT(USG_SNS_STN)
    DELAY(2000)
    STOP
    PRINT("Stopped at station")
    FREE(UGS_FY_Exit)
    FOLLOW(USG_BK2_STN_EX)
ENDIF

//Header line
SEQUENCE(UGS_Head_Entry) //seq 601
//insert BO detection here for station
 //Check BO on header
 IF(-BD_S1_HE)
  IF(-BD_S2_HE)
    RESERVE(UGS_STN_Hold)  
    IFTHROWN(UGS_T1_H) //Header Point
       CLOSE(UGS_T1_H)
    ENDIF
       RESERVE(UGS_BK2_HEAD_1_AA_Ex)
       FWD(20)
       AT(USG_Head_End)
       STOP
       FREE(UGS_STN_Hold)
  ENDIF
 ENDIF
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
PRINT("BOARD 2-3 SEQ")
  DELAYRANDOM(10000, 15000)
  RESERVE(UGS_BK4_3__8_Hold)
    IFTHROWN(UGS_T2_E__DFM_T1_A)
      CLOSE(UGS_T2_E__DFM_T1_A)
      IFTHROWN(UGS_T3_A__UFM_T3_E)
        CLOSE(UGS_T3_A__UFM_T3_E)
      ENDIF
    ENDIF
    GREEN(SIG_A1)
    FWD(50)
    AT(SNS6_TRN2_STN_EX)
    RED(SIG_A1)
    FWD(70)
    FREE(UGS_BK1_Stn_App)
    FREE(UGS_BK2_HEAD_1_AA_Ex)
    FREE(UGS_STN_Hold)
  FOLLOW(USG_BK8__USG_BK9)

//Main run to board 9
SEQUENCE(USG_BK8__USG_BK9)
PRINT("BOARD 8 SEQ")
  //Insert BO for board 9    
  RESERVE(UGS_BK5_9_Hold)
    IFTHROWN(UGS_T4_E__UFM_T5_A)
      CLOSE(UGS_T4_E__UFM_T5_A)     
    ENDIF
  AT(SNS7_MAIN_TRN3_APP)
  AMBER(SIG_A1)
  FWD(30)
  FREE(UGS_BK4_3__8_Hold)
  
FOLLOW(USG_BK9__USG_FY_App)

// Switch tracks from UGS to UFM
//SEQUENCE(UGS_BK8__UFM_BK9)
//To Be done

//Move Track A into B Fiddle yard
SEQUENCE(UGS__BF_A)
  //insert BO here
  RESERVE(UMF_BK10_9_Hold)
  RESERVE(FB_App)
  trackChange(UGS_T5_E__FYUG_T7_A,UFM_T6_A__UGS_T5_E)
  FWD(10)
  FOLLOW(BYard_Ladder_T1_A)
  
//Fiddle yard hold sequence

//Enter fiddle yard A storage chain
SEQUENCE(USG_BK9__USG_FY_App)
PRINT("BOARD 9 SEQ")
//insert BO detection here
    RESERVE(USG_BK9_Hold)
    FWD(10)
    AT(USG_SNS_9)
    STOP
    GREEN(SIG_A1)
    PRINT("Holding in BK 9")
    FREE(UGS_BK5_9_Hold)
    FOLLOW(USG_BK9__USG_BK10)

SEQUENCE(USG_BK9__USG_BK10)
//insert BO detection here
    RESERVE(USG_BK10_Hold)
    FWD(10)
    AT(USG_SNS_10)
    STOP
    PRINT("Holding in BK 10")
    FREE(USG_BK9_Hold)
    FOLLOW(USG_BK10__USG_BK11)

SEQUENCE(USG_BK10__USG_BK11)
//insert BO detection here
    RESERVE(USG_BK11_Hold)
    FWD(10)
    AT(USG_SNS_11)
    STOP
    PRINT("Holding in BK 11")
    FREE(USG_BK10_Hold)
    FOLLOW(USG_BK11__USG_BK12)


SEQUENCE(USG_BK11__USG_BK12)
 //insert BO detection here
    RESERVE(USG_BK12_Hold)
    FWD(10)
    AT(USG_SNS_12)
    STOP
    PRINT("STOPPED")
    FREE(USG_BK11_Hold)
    DONE
//End fiddle yard hold sequence
  
DONE
