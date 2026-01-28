//Autoclose thurnouts based on non automations

//Southbound trains
//scenic track A

//Track A -> B
ONBUTTON(CD_S3_B)
    IFTHROWN(UFM_T17_E__UGS_T7_A)
        CLOSE(9001)
    ENDIF
DONE
//Track B -> A Rear
ONBUTTON(CD_S2_A)
    IFTHROWN(UFM_T17_E__UGS_T7_A)
        CLOSE(9026)
    ENDIF
DONE

//Track A -> B Scenic
ONBUTTON(CD_S5_B)
    IFTHROWN(UFM_T2_A__UGS_T3_E)
        CLOSE(9004)
    ENDIF
DONE

// Track B->A scenic
ONBUTTON(CD_S7_A)
  IFCLOSED(DMF_T3_E__UFM_T4_A)
    IFTHROWN(UGS_T4_A__UMF_T3_E)
        CLOSE(9007)
    ENDIF
  ENDIF
DONE

//Track D->A
ONBUTTON(CD_S7_A)
    IFTHROWN(DMF_T3_E__UFM_T4_A)
        CLOSE(9009)
    ENDIF
DONE

//Track D->B 1st Set
ONBUTTON(CD_S7_B)
    IFTHROWN(DMF_T3_E__UFM_T4_A)
        CLOSE(9008)
    ENDIF
DONE

//Track D -> B 2nd set
ONBUTTON(CD_S6_B) 
    IFTHROWN(UFM_T5_A__UMF_T3_E)
        CLOSE(9010)
    ENDIF
DONE 

//Track A -> B BOARD 8 
ONBUTTON(CD_F8_B) 
    IFTHROWN(UGS_T5_E__UFM_T6_A)
        CLOSE(9020)
    ENDIF
DONE 

//Track A -> D Board 8
ONBUTTON(CD_F8_D) 
    IFTHROWN(UGS_T5_E__UFM_T6_A)
        CLOSE(9021)
    ENDIF
DONE 


//Track F -> E Board 2
ONBUTTON(CD_F3_E) 
    IFTHROWN(DFM_T3_A__DGS_T1_E)
        CLOSE(9006)
    ENDIF
    IFTHROWN(DGS_T3_A__HS_T6_A)
        CLOSE(DGS_T3_A__HS_T6_A)
    ENDIF
DONE

//Track c -> E Board 2
ONBUTTON(CD_F3_E) 
    IFTHROWN(DMF_T4_E__DFM_T4_A)
        CLOSE(9011)
    ENDIF
DONE

// Holgate Exit Board 3
ONBUTTON(CD_F3_F) 
    IFTHROWN(DGS_T3_A__HS_T6_A)
        CLOSE(9031)
    ENDIF
DONE

//Track E -> F Board 9
ONBUTTON(CD_F5_F) 
    IFTHROWN(DFM_T5_E__DGS_T4_A)
        CLOSE(9022)
    ENDIF
DONE 

//Holgate Track 1 close access
ONBUTTON(CD_S4_HA) 
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
ONBUTTON(CD_S4_HB) 
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
ONBUTTON(CD_S4_HC) 
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
ONBUTTON(CD_S4_HD) 
    IFTHROWN(HS_T6_A__DGS_T3_E)
        IFTHROWN(DGS_T3_A__HS_T6_A)
            IFTHROWN(DFM_T5_E__DGS_T4_A) 
                CLOSE(9030)
            ENDIF
            CLOSE(9031)
        ENDIF
    ENDIF

    
//Holgate Exit auto close
//ONBUTTON(CD_F3_E)
//    IFTHROWN(DGS_T2_A__HS_T1_E)
//        CLOSE(9028)
//    ENDIF
//DONE

// E -> F Stay on F
ONBUTTON(CD_S5_F)
    IFTHROWN(DFM_T5_E__DGS_T4_A)
        CLOSE(9022)
        DELAY(500)
        GREEN(SIG_E4)
    ENDIF 
DONE