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
