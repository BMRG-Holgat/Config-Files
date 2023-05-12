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

// Start routines for track B Fiddle Yard

SEQUENCE(BYard_EXIT)
    RESERVE(UMF_FY_Ex)
    FWD(10)
FOLLOW(STN_ByPass)

SEQUENCE(STN_ByPass)
    IFTHROWN(UGS_T6_A__FYUG_T10_E) //Board 2 lane cross fyard
        trackChange(UGS_T6_A__FYUG_T10_E,UMF_T15_E__UGS_T6_A)
    ENDIF
    RESERVE(UMF_BK1_1_STN_App)
    RESERVE(UMF_BK2_1_STN_Ex)
    IFTHROWN(UGS_T2_E__DFM_T1_A)
        trackChange(UGS_T2_E__DFM_T1_A,UFM_T1_A__UGS_T2_E)
    ENDIF
   //Wait for clear signal 
    IFRED(SIG_B1)
        FWD(0)
    ELSE
        RESERVE(UMF_BK3_2_BA_App)
        IFAMBER(SIG_B1)           
            FWD(30)
        ENDIF 
        IFGREEN(SIG_B1)
            FWD(50)
        ENDIF
    ENDIF
FOLLOW(STN_Exit_TB)

SEQUENCE(STN_Exit_TB)
    //Clear Double slip
    IFTHROWN(UFM_T2_E__DMF_T2_A)
        CLOSE(UFM_T2_E__DMF_T2_A)
    ENDIF
    IFTHROWN(DMF_T2_E__UGS_T1_A)
        CLOSE(DMF_T2_E__UGS_T1_A)
    ENDIF
    RESERVE(UMF_BK4_BB__BD_3_Hold) 
    RESERVE(UMF_BK5_4__6_Hold)
    GREEN(SIG_B2)
    RESERVE(UMF_BK8_7_App)
    IFRED(SIG_B3)
        FWD(50)
    ELSE 
        IFAMBER(SIG_B3)
            FWD(60)
        ENDIF
    ELSE
        FWD(80)
    ENDIF 
FOLLOW(SSlip_App)

SEQUENCE(SSlip_App)
    // use bd to detect entry to slip area
    
    IFRED(SIG_B3)
        FWD(0)
    ELSE 
        RESERVE(UMF_BK9_8_App)
        FREE(UMF_BK1_1_STN_App)
        FREE(UMF_BK2_1_STN_Ex)
        GREEN(SIG_B3)
        AMBER(SIG_B1)
    ENDIF


FOLLOW(BYard_Ladder_T1_A)