/*
Routes for Track A
*/

AUTOMATION(10,"Track A Stn circuit")
    CALL(AA_Approach)
    PRINT("Returned UGS_Hold_Ex")
    CALL(UGS_AB_App)
    PRINT("Returned UGS_AB_App")
    CALL(UGS_STN_App)
    PRINT("Returned UGS_STN_App")
    CALL(UGS_STN_Hold)
    PRINT("Returned UGS_STN_Hold")
    //CALL(UGS_STN_Ex)
    //CALL(UGS_Sig_Test)
    //CALL(UGS_AD_App)
    //CALL(UGS_Main_Run)
    //CALL(UGS_AE_App)
    //CALL(UGS_AE_Ex)
    //CALL(Set_Signals)
    //CALL(UGS_AF_App)
    UNLATCH(10)
    //FOLLOW(UGS_BK9__UGS_BK10)
