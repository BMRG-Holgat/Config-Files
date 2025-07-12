//Autoclose thurnouts based on non automations

//Southbound trains
//scenic track A

//Track A -> B
AUTOSTART SEQUENCE(140)
    AT(BD_S5_B)
    IFTHROWN(UFM_T2_A__UGS_T3_E)
        CLOSE(9004)
    ENDIF
FOLLOW(140)

// Track B->A
AUTOSTART SEQUENCE(141)
    AT(BD_S6_A)
    IFTHROWN(UGS_T4_A__UMF_T3_E)
        CLOSE(9007)
    ENDIF
FOLLOW(141)

//Track D->A
AUTOSTART SEQUENCE(142)
    AT(BD_S6_A)
    IFTHROWN(UGS_T4_A__UMF_T3_E)
        CLOSE(9009)
    ENDIF 
FOLLOW(142)

//Track D->B
AUTOSTART SEQUENCE(143)
    AT(BD_S6_B)
    IFTHROWN(DMF_T3_E__UFM_T4_A)
        CLOSE(9008)
    ENDIF 
FOLLOW(143)

AUTOSTART SEQUENCE(144)
    AT(BD_S6_B) 
    IFTHROWN(UFM_T5_A__UMF_T3_E)
        CLOSE(9010)
    ENDIF
FOLLOW(144)

AUTOSTART SEQUENCE(145)
    AT(BD_S4_HA) 
    IFCLOSED(HS_T4_A__HS_T5_E)
        IFCLOSED(HS_T5_A__HS_T6_E)
            IFCLOSED(HS_T6_A__DGS_T3_E)
                IFTHROWN(DGS_T3_A__HS_T6_A)
                    CLOSE(DGS_T3_A__HS_T6_A)
                 ENDIF 
            ENDIF 
        ENDIF
    ENDIF 
FOLLOW(145)

AUTOSTART SEQUENCE(146)
    AT(BD_S4_HB) 
    IFTHROWN(HS_T4_A__HS_T5_E)
        IFCLOSED(HS_T5_A__HS_T6_E)
            IFCLOSED(HS_T6_A__DGS_T3_E)
                IFTHROWN(DGS_T3_A__HS_T6_A)
                    CLOSE(DGS_T3_A__HS_T6_A)
                 ENDIF 
            ENDIF 
        ENDIF
    ENDIF 
FOLLOW(146)

AUTOSTART SEQUENCE(147)
    AT(BD_S4_HC) 
        IFTHROWN(HS_T5_A__HS_T6_E)
            IFCLOSED(HS_T6_A__DGS_T3_E)
                IFTHROWN(DGS_T3_A__HS_T6_A)
                    CLOSE(DGS_T3_A__HS_T6_A)
                 ENDIF 
            ENDIF 
        ENDIF
FOLLOW(147)

AUTOSTART SEQUENCE(148)
    AT(BD_S4_HD) 
        IFTHROWN(HS_T6_A__DGS_T3_E)
                IFTHROWN(DGS_T3_A__HS_T6_A)
                    CLOSE(DGS_T3_A__HS_T6_A)
                 ENDIF 
            ENDIF
FOLLOW(148)

AUTOSTART SEQUENCE(149)
    IFTHROWN(DGS_T2_A__HS_T1_E)
        AT(406)
        CLOSE(9028)
    ENDIF
FOLLOW(149)