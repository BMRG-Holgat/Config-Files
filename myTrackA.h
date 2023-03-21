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

//Station Approach from A and stop

SEQUENCE(UGS_BK1_Stn_App) // seq 600
//Insert Bo detection here for station
  RESERVE(UGS_BK1_STN_App)
  RESERVE(UGS_BK2_HEAD_1_AA_Ex)
  IFCLOSED(UGS_T1_H) //AA
    THROW(UGS_T1_H)
  ENDIF
  RESERVE(UGS_STN_Hold)
  FWD(10)
//Insert signals here
  AT(UGS_SNS_Stn_Stop)
  STOP
  PRINT("Stopped at station")
  FREE(USG_BK12_Hold)
  DELAYRANDOM(10000, 15000)
FOLLOW(USG_BK2_STN_EX)

//Header line
SEQUENCE(UGS_Head_Entry) //seq 601
//insert BO detection here for station
 //Check BO on header
 PRINT("Moving to AA")
    RESERVE(UGS_STN_Hold)  
    IFTHROWN(UGS_T1_H) //Header Point
       CLOSE(UGS_T1_H)
       RESERVE(UGS_BK2_HEAD_1_AA_Ex)
       FWD(20)
       AT(USG_HEAD_Stop)
       STOP
       FREE(UGS_STN_Hold)
DONE

//Leave Header Line and go back to Fiddle Yard
SEQUENCE(UGS_Head_Exit) // seq 602
    //insert BO detection here for station-Fiddle yard
    IFRESERVE(UGS_STN_Hold)
        CLOSE(UGS_T1_H)
        REV(20)
        AFTER(UGS_SNS_TRN_1_App) 
        FREE(UGS_BK2_HEAD_1_AA_Ex)
        STOP
        DELAY(5000)
    ENDIF
    FOLLOW(UGS_BK1_STN_App)

       
//Exit Station Onto board 2
SEQUENCE(USG_BK2_STN_EX) // seq 603
//insert BO detection here for boards 3-8
  RESERVE(UGS_BK4_Stn_Exit)
  PRINT("Moving to AB")
    IFTHROWN(UGS_T2_E__DFM_T1_A) //AB
      CLOSE(UGS_T2_E__DFM_T1_A)
    ENDIF
    //Set signal to green
    FWD(30)
    DELAY(3000)
    //Set signal to red
    AT(UGS_SNS_TRN_2_App)
    FREE(UGS_BK2_HEAD_1_AA_Ex)
  FOLLOW(UGS_BK3_Main)
  

//Main run board 4  Double slip 
SEQUENCE(UGS_BK3_Main) //seq 604
  AFTER(UGS_SNS_TRN_2_App)
  IFRESERVE(UGS_BK4_3__8_Hold)   
    PRINT("Moving to AC")
      IFTHROWN(UGS_T3_A__UFM_T3_E) //AC
      CLOSE(UGS_T3_A__UFM_T3_E)
      ENDIF
    FWD(50)
    FREE(UGS_BK1_STN_App)
  ELSE 
    AT(UGS_SNS_TRN_3_App)
    STOP
    RESERVE(UGS_BK4_3__8_Hold)
    FOLLOW(UGS_BK3_Main)
  ENDIF
FOLLOW(UGS_BK4_BK8_App)

//Board 8 approach
SEQUENCE(UGS_BK4_BK8_App)
  AT(UGS_SNS_TRN_4_App)
  RESERVE(UGS_BK6)
  PRINT("Moving to AD")
  IFTHROWN(UGS_T4_E__UFM_T5_A) //AD
      CLOSE(UGS_T4_E__UFM_T5_A)     
    ENDIF
  FREE(UGS_STN_Hold)
FOLLOW(USG_BK8__USG_BK9)

//Main run to board 9
SEQUENCE(USG_BK8__USG_BK9)
  //Insert BO for board 9    
  PRINT("On Board 9")
  RESERVE(UGS_BK7)  
  AT(UGS_SNS_TRN_4_Ex)
  FREE(UGS_BK4_Stn_Exit) 
  FWD(30)
FOLLOW(USG_BK8__USG_BK9)

//Move Track A into B Fiddle yard
SEQUENCE(UGS__BF_A)
  //insert BO here
  FREE(UGS_BK4_3__8_Hold)
  RESERVE(UMF_BK10_9_Hold)
  RESERVE(FB_App)
  trackChange(UGS_T5_E__FYUG_T7_A,UFM_T6_A__UGS_T5_E)
  FWD(10)
  FOLLOW(FYard_Ladder_T1_A)
  
//Fiddle yard hold sequence

//Enter fiddle yard B bypass
SEQUENCE(USG_BK9_UGS_Store)
//insert BO detection here
    FREE(UGS_BK4_3__8_Hold)
    RESERVE(USG_BK9_Hold)
    AT(UGS_SNS_TRN_5_App)
    STOP
    FREE(UGS_BK8_BF_App)
    FOLLOW(USG_BK9__USG_BK10)

SEQUENCE(USG_BK9__USG_BK10)
//insert BO detection here
    RESERVE(USG_BK10_Hold)
    FWD(10)
    AT(UGS_SNS_Str_1_Stop)
    STOP
    FREE(USG_BK9_Hold)
    FOLLOW(USG_BK10__USG_BK11)

SEQUENCE(USG_BK10__USG_BK11)
//insert BO detection here
    RESERVE(USG_BK11_Hold)
    FWD(10)
    AT(UGS_SNS_Str_2_Stop)
    STOP
    FREE(USG_BK10_Hold)
    FOLLOW(USG_BK11__USG_BK12)


SEQUENCE(USG_BK11__USG_BK12)
 //insert BO detection here
    RESERVE(USG_BK12_Hold)
    FWD(10)
    AT(UGS_SNS_Str_3_Stop)
    STOP
    PRINT("STOPPED")
    FREE(USG_BK11_Hold)
    DONE
//End fiddle yard hold sequence
  
DONE

