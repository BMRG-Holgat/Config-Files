/*
* myTrackF.h
*
* Sequences for Track A
* Up Goods Slow
*
* V. 0.0.1
*  Setup basics
*  All Sequences start from Board 1 and end on Board 2
*/

//Enter fiddle yard B bypass
SEQUENCE(DSG_BK8__DSG_BK9)
//insert BO detection here
    RESERVE(DSG_BK9_Hold)
    FWD(10)
    AT(DSG_SNS_9)
    STOP
    FREE(DGS_BK8_BF_App)
    FOLLOW(DSG_BK9__DSG_BK10)

SEQUENCE(DSG_BK9__DSG_BK10)
//insert BO detection here
    RESERVE(DSG_BK10_Hold)
    FWD(10)
    AT(DSG_SNS_10)
    STOP
    FREE(DSG_BK9_Hold)
    FOLLOW(DSG_BK10__DSG_BK11)

SEQUENCE(DSG_BK10__DSG_BK11)
//insert BO detection here
    RESERVE(DSG_BK11_Hold)
    FWD(10)
    DELAY(5000)
 //   AT(DSG_SNS_11)
 //   STOP
    FREE(DSG_BK10_Hold)
    FOLLOW(DSG_BK11__DSG_BK12)


SEQUENCE(DSG_BK11__DSG_BK12)
 //insert BO detection here
    RESERVE(DSG_BK12_Hold)
    FWD(10)
    AT(DSG_SNS_12)
    STOP
    PRINT("STOPPED")
    FREE(DSG_BK11_Hold)
    DONE
//End fiddle yard hold sequence
  
DONE