//Autoclose thurnouts based on non automations

//Southbound trains
//scenic track A

//Track A -> B
ONBUTTON(BD_S5_B)
    IFTHROWN(UFM_T2_A__UGS_T3_E)
        CLOSE(9004)
    ENDIF
DONE

// Track B->A
ONBUTTON(BD_S6_A)
    IFTHROWN(UGS_T4_A__UMF_T3_E)
        CLOSE(9007)
    ENDIF
DONE

//Track D->A
ONBUTTON(BD_S6_A)
    IFTHROWN(UGS_T4_A__UMF_T3_E)
        CLOSE(9009)
    ENDIF
DONE

//Track D->B
ONBUTTON(BD_S6_B)
    IFTHROWN(DMF_T3_E__UFM_T4_A)
        CLOSE(9008)
    ENDIF
DONE

ONBUTTON(BD_S6_B) 
    IFTHROWN(UFM_T5_A__UMF_T3_E)
        CLOSE(9010)
    ENDIF
DONE 

ONBUTTON(BD_S4_HA) 
    IFCLOSED(HS_T4_A__HS_T5_E)
        IFCLOSED(HS_T5_A__HS_T6_E)
            IFCLOSED(HS_T6_A__DGS_T3_E)
                IFTHROWN(DGS_T3_A__HS_T6_A)
                    CLOSE(DGS_T3_A__HS_T6_A)
                 ENDIF 
            ENDIF 
        ENDIF
    ENDIF 
DONE 

ONBUTTON(BD_S4_HB) 
    IFTHROWN(HS_T4_A__HS_T5_E)
        IFCLOSED(HS_T5_A__HS_T6_E)
            IFCLOSED(HS_T6_A__DGS_T3_E)
                IFTHROWN(DGS_T3_A__HS_T6_A)
                    CLOSE(DGS_T3_A__HS_T6_A)
                 ENDIF 
            ENDIF 
        ENDIF
    ENDIF 
DONE

ONBUTTON(BD_S4_HC) 
    IFTHROWN(HS_T5_A__HS_T6_E)
        IFCLOSED(HS_T6_A__DGS_T3_E)
            IFTHROWN(DGS_T3_A__HS_T6_A)
                CLOSE(DGS_T3_A__HS_T6_A)
            ENDIF 
        ENDIF 
    ENDIF
DONE 

ONBUTTON(BD_S4_HD) 
    IFTHROWN(HS_T6_A__DGS_T3_E)
        IFTHROWN(DGS_T3_A__HS_T6_A)
            CLOSE(DGS_T3_A__HS_T6_A)
        ENDIF
    ENDIF
DONE

ONBUTTON(SNS_UGS_B3)
    IFTHROWN(DGS_T2_A__HS_T1_E)
        CLOSE(9028)
    ENDIF
DONE