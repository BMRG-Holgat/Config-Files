/*
* myTrackA.h
*
* Sequences for Track A Automated Routes
* Up Goods Slow
*
* V. 0.0.1
*  Setup basics
*  All Sequences start from Board 2 rear and end on Board 9 rear
*/

// Exit Track A Holding Yard
SEQUENCE(UGS_Hold_Ex) //leave holding before track B entry
   IFNOT(BD_F2_A) 
    PRINT("Leave FiddleYard")
        RESERVE(UGS_BK1_AA_App)
        IFTHROWN(UGS_T7_A__UFM_T17_E)
            trackChange(UGS_T7_A__UFM_T17_E,UFM_T17_E__UGS_T7_A)
        ENDIF
        DELAY(2000)
        FWD(20)
    ELSE 
        PRINT("OCCUPIED")
        FOLLOW(UGS_Hold_Ex)
    ENDIF   
RETURN

//Approach station and header
SEQUENCE(UGS_AB_App)  
    IFNOT(BD_F1_A)
        PRINT("Approaching AB")
        RESERVE(UGS_BK2_AB_App)
        IFCLOSED(UGS_T1_E__UFM_T1_A)
            trackChange(UGS_T1_E__UFM_T1_A,UFM_T1_A__UGS_T1_E)
        ENDIF
        AT(UGS_B1_A1) // Trigger Hold release
        FREE(UGS_BK12_Hold) //Allow ladder to move forward on track A.
    ELSE 
        FOLLOW(UGS_AB_App)
    ENDIF
RETURN

//Enter Station
SEQUENCE(UGS_STN_App) 
    IFNOT(BD_S1_A)
        PRINT("Approaching Station")
        RESERVE(UGS_BK3_STN_Hold)
        IFCLOSED(UGS_T2_H)
            THROW(UGS_T2_H)
        ENDIF
    ELSE 
        FOLLOW(UGS_STN_App)
    ENDIF
RETURN

// Proceed to end of platform and stop
SEQUENCE(UGS_STN_Hold) 
    IF(BD_S1_A)
    PRINT("Stopping at station")
        DELAY(2000)
        STOP 
        FREE(UGS_BK1_AA_App) 
    ENDIF
RETURN 

//Station departure sequence
SEQUENCE(UGS_STN_Ex)
    IFNOT(BD_S2_A)
        PRINT("Leaving Station")
        DELAYRANDOM(10000, 15000)
        PRINT("Left Station")
        RESERVE(UGS_BK4_STN_Ex)
        IFTHROWN(UGS_T3_E__UFM_T2_A)
            trackChange(UGS_T3_E__UFM_T2_A,UFM_T2_A__UGS_T3_E)
        ENDIF
    ELSE 
        FOLLOW(UGS_STN_Ex)
    ENDIF 
RETURN

//Set speed depending on signal
SEQUENCE(UGS_Sig_Test)
    PRINT("Testing Signals")
    signalSetTest(SIG_A1,40,60,UGS_Sig_Test)
RETURN 

//Approach AD
SEQUENCE(UGS_AD_App)
    IFNOT(BD_S3_A)
        PRINT("Approaching AD")
        RESERVE(UGS_BK5_AD_App)
        IF(BD_S2_A)
            RED(SIG_A1)
        ENDIF
        IF(BD_S3_A)
            FREE(UGS_BK2_AB_App) 
        ENDIF
    ELSE 
        FOLLOW(UGS_AD_App)
    ENDIF
RETURN

//Main run down boards 4,5,6 & 7
SEQUENCE(UGS_Main_Run)
    IFNOT(BD_S4_A)
        IFNOT(BD_S5_A)
            IFNOT(BD_S6_A)
                IFNOT(BD_S7_A)
                    PRINT("Main Run")
                    RESERVE(UGS_BK6_AE_App)
                    IFTHROWN(UGS_T4_A__UMF_T3_E)
                        trackChange(UGS_T4_A__UMF_T3_E,UFM_T3_E__UGS_T4_A)
                    IF(BD_S4_A)
                        RED(SIG_A2)
                        AMBER(SIG_A1)
                        FREE(UGS_BK3_STN_Hold)
                    ENDIF
                    IF(BD_S6_A)
                        FREE(UGS_BK4_STN_Ex)
                        GREEN(SIG_A1)  
                    ENDIF
                    ELSE 
                        FOLLOW(UGS_Main_Run)
                    ENDIF
                ELSE 
                    FOLLOW(UGS_Main_Run)
                ENDIF
            ELSE 
                FOLLOW(UGS_Main_Run)
            ENDIF
        ELSE 
            FOLLOW(UGS_Main_Run)
        ENDIF
    ELSE 
        FOLLOW(UGS_Main_Run)
    ENDIF   
RETURN 

//Approach AE at speed!
SEQUENCE(UGS_AE_App)
    AT(BD_S6_A)
        IFNOT(BD_S8_A)
            IFNOT(BD_S9_A)
                RESERVE(UGS_BK7_AF_App)               
                GREEN(SIG_A1)
                IFRED(SIG_A3)
                    GREEN(SIG_A3)
                    signalSetTest(SIG_A3,40,60,UGS_AE_App)
                ENDIF
            ELSE 
                RED(SIG_A3)
                STOP
                FOLLOW(UGS_AE_App) 
            ENDIF
        ELSE 
            RED(SIG_A3)
            STOP
            FOLLOW(UGS_AE_App)
        ENDIF
RETURN 

//Exit AE
SEQUENCE(UGS_AE_Ex)
    AT(BD_S7_A)
    RESERVE(UGS_BK8_AF_Ex)
    IFTHROWN(UGS_T5_E__UFM_T6_A)
        trackChange(UGS_T5_E__UFM_T6_A,UFM_T6_A__UGS_T5_E)
    ENDIF
RETURN

//On board 8 do this...
SEQUENCE(Set_Signals)
    AT(BD_S8_A)
    RED(SIG_A3)
    AMBER(SIG_A2)
    RESERVE(UGS_BK9_AF_App)
RETURN

//Approach AF
SEQUENCE(UGS_AF_App)
    AT(BD_S9_A)
    FWD(30)
    IFTHROWN(UGS_T6_E__UFM_T8_A)
        trackChange(UGS_T6_E__UFM_T8_A,UFM_T8_A__UGS_T6_E)
    ENDIF
    AT(UGS_B9_A1)
    STOP
RETURN 







