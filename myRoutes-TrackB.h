/*
Routes for Track A
*/

//Station stop from A move to Track C HST
ROUTE(1,"HST B to Station to B")
    RESERVE(UGS_BK1_Stn_App)
    RESERVE(UGS_BK2_HEAD_1_AA_Ex)
    IFCLOSED(UGS_T6_A__FYUG_T10_E) //Board 2 lane cross
        trackChange(UGS_T6_A__FYUG_T10_E,UMF_T15_E__UGS_T6_A)
    ENDIF
    //set station signal red
    FWD(10)
    AT(SNS2_MAIN_TRN1_EX)
    RESERVE(UGS_STN_Hold)
    //Announce at station.
    AT(USG_SNS_STN)
    FWD(0)
    DELAYRANDOM(10000,15000)
    /*Reserve 3 blocks surrounding points*/
    //Announce at station
    RESERVE(UGS_BK4_Stn_Exit)
    IFCLOSED(UGS_T2_E__DFM_T1_A)
        trackChange(UGS_T2_E__DFM_T1_A,UFM_T1_A__UGS_T2_E)
    ENDIF
    DELAY(3000)
    
    //Set signal green
    
    FWD(30)
    //AT(some-sensor-on-board-4)
    FWD(80)
    AT(SNS_FB_T1_E) // Board 9
    FWD(30)

    FOLLOW(FYard_Ladder_T1_A) //Fiddleyard enterance

    DONE