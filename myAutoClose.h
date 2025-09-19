//Autoclose thurnouts based on non automations

//Southbound trains
//scenic track A

//Track A -> B
ONBUTTON(BD_S3_B)
    IFTHROWN(UFM_T17_E__UGS_T7_A)
        CLOSE(9001)
    ENDIF
DONE
//Track B -> A Rear
ONBUTTON(BD_S2_A)
    IFTHROWN(UFM_T17_E__UGS_T7_A)
        CLOSE(9026)
    ENDIF
DONE

//Track A -> B Scenic
ONBUTTON(BD_S5_B)
    IFTHROWN(UFM_T2_A__UGS_T3_E)
        CLOSE(9004)
    ENDIF
DONE

// Track B->A scenic
ONBUTTON(BD_S7_A)
  IFCLOSED(DMF_T3_E__UFM_T4_A)
    IFTHROWN(UGS_T4_A__UMF_T3_E)
        CLOSE(9007)
    ENDIF
  ENDIF
DONE

//Track D->A
ONBUTTON(BD_S7_A)
    IFTHROWN(DMF_T3_E__UFM_T4_A)
        CLOSE(9009)
    ENDIF
DONE

//Track D->B 1st Set
ONBUTTON(BD_S7_B)
    IFTHROWN(DMF_T3_E__UFM_T4_A)
        CLOSE(9008)
    ENDIF
DONE

//Track D -> B 2nd set
ONBUTTON(BD_S6_B) 
    IFTHROWN(UFM_T5_A__UMF_T3_E)
        CLOSE(9010)
    ENDIF
DONE 

//Track A -> B BOARD 8 
ONBUTTON(BD_F8_B) 
    IFTHROWN(UGS_T5_E__UFM_T6_A)
        CLOSE(9020)
    ENDIF
DONE 

//Track A -> D Board 8
ONBUTTON(BD_F8_D) 
    IFTHROWN(UGS_T5_E__UFM_T6_A)
        CLOSE(9021)
    ENDIF
DONE 

//Holgate Track 1 close access
ONBUTTON(BD_S4_HA) 
    IFCLOSED(HS_T4_A__HS_T5_E)
        IFCLOSED(HS_T5_A__HS_T6_E)
            IFCLOSED(HS_T6_A__DGS_T3_E)
                IFTHROWN(DGS_T3_A__HS_T6_A)
                    IFTHROWN(DFM_T5_E__DGS_T4_A) 
                        CLOSE(9030)
                    ENDIF
                    CLOSE(9031)
                 ENDIF 
            ENDIF 
        ENDIF
    ENDIF 
DONE 

//Holgate Track 2 close access
ONBUTTON(BD_S4_HB) 
    IFTHROWN(HS_T4_A__HS_T5_E)
        IFCLOSED(HS_T5_A__HS_T6_E)
            IFCLOSED(HS_T6_A__DGS_T3_E)
                IFTHROWN(DGS_T3_A__HS_T6_A)
                    IFTHROWN(DFM_T5_E__DGS_T4_A) 
                        CLOSE(9030)
                    ENDIF
                    CLOSE(9031)
                 ENDIF 
            ENDIF 
        ENDIF
    ENDIF 
DONE

//Holgate track 3 close access
ONBUTTON(BD_S4_HC) 
    IFTHROWN(HS_T5_A__HS_T6_E)
        IFCLOSED(HS_T6_A__DGS_T3_E)
            IFTHROWN(DGS_T3_A__HS_T6_A)
               IFTHROWN(DFM_T5_E__DGS_T4_A) 
                    CLOSE(9030)
                ENDIF
                CLOSE(9031)
            ENDIF 
        ENDIF 
    ENDIF
DONE 

//Holgate track 4 autoclose access
ONBUTTON(BD_S4_HD) 
    IFTHROWN(HS_T6_A__DGS_T3_E)
        IFTHROWN(DGS_T3_A__HS_T6_A)
            IFTHROWN(DFM_T5_E__DGS_T4_A) 
                CLOSE(9030)
            ENDIF
            CLOSE(9031)
        ENDIF
    ENDIF

    
//Holgate Exit auto close
//ONBUTTON(BD_F3_E)
//    IFTHROWN(DGS_T2_A__HS_T1_E)
//        CLOSE(9028)
//    ENDIF
//DONE

// E -> F Stay on F
ONBUTTON(BD_S5_F)
    IFTHROWN(DFM_T5_E__DGS_T4_A)
        CLOSE(9022)
        DELAY(500)
        GREEN(SIG_E3)
    ENDIF 
DONE