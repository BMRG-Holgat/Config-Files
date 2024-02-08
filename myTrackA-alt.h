/*
* myTrackA.h
*
* Sequences for Track A
* Up Goods Slow
*
* V. 0.0.1
*  Setup basics
*  All Sequences start from end of storage (Board 3)
*
* V 0.1.0
* First single loop created
* All basic sequences created
*
*/

SEQUENCE(AA_Approach)
  IF(BD_A_B2)
    IFTHROWN(9026)
        CLOSE(9026)
    ENDIF
    RESERVE(A_Store_Ex)
    RED(SIG_A1)
    FWD(15)
  ENDIF
RETURN //follow AB_Approach

SEQUENCE(AB_Approach)
    IF(BD_A_B1a)
        IFTHROWN(9001)
            CLOSE(9001)
        ENDIF
        RESERVE(A_AB_App)
        AT(B1_IR_A)
        FREE(A_Store_1)
//FOLLOW(AB_Emergency)
RETURN

SEQUENCE(AB_Emergency)
    IF(BD_A_B1c)
        CLOSE(UGS_T2_H)
        FOLLOW(AB_Header)
    ELSE
        FOLLOW(A_Station)
    ENDIF
DONE 

SEQUENCE(A_Station)
    IF(BD_A_B1d)
        IFCLOSED(UGS_T2_H)
            THROW(UGS_T2_H)
        ENDIF
        RESERVE(A_STN_App)
        IFRANDOM(50)
            AT(BD_A_B1c)
            STOP
            FOLLOW(A_STN_Hold)
        ELSE 
            FOLLOW(AC_Approach)
        ENDIF 
    ENDIF
DONE

SEQUENCE(A_STN_Hold)
    IF(BD_A_B1d)
        RESERVE(A_AC_App)
        GREEN(SIG_A1)
        DELAYRANDOM(7000,15000)
        FOLLOW(AC_Approach)
    ENDIF
DONE

SEQUENCE(AC_Approach)
    IF(BD_A_B2)
        IF(BD_A_B3)
            IFTHROWN(9004)
                CLOSE(9004)
            ENDIF
            RESERVE(A_AD_App)
            FREE(A_Store_Ex)
            SPEED(40)          
FOLLOW(AD_Approach)

SEQUENCE(AD_Approach)
    IFGREEN(SIG_A1)
        IF(BD_A_B2)
            RED(SIG_A1)
        ENDIF
    ENDIF
    IF(BD_A_B2)
        IFRED(SIG_A2)
            STOP
            FOLLOW(AD_Approach)
        ENDIF
    ELSE
        IFTHROWN(9007)
            CLOSE(9007)
        ENDIF
        IFTHROWN(9009)
            CLOSE(9009)
        ENDIF 
        FREE(A_AB_App)
        FOLLOW(AE_Approach)
    ENDIF
    

SEQUENCE(AD_Exit)
    IF(BD_A_B7)
        IF(BD_A_B6)
            IF(BD_A_B5)
                IF(BD_A_B4)     
                    RESERVE(A_AE_App)
                    IFGREEN(SIG_A2)
                        SPEED(80)
                    ENDIF
                    IFAMBER(SIG_A2)
                        SPEED(60)
                    ENDIF
                    IFNOT(BD_A_B4)
                        RED(SIG_A2)
                        FREE(A_STN_App)
                    ENDIF
                ENDIF
            ENDIF
        ENDIF
    ENDIF
FOLLOW(AE_Approach)

SEQUENCE(AE_Approach)
        AT(BD_A_B6)
        FREE(A_AC_App)
        IFRED(SIG_A3)
            STOP
        ENDIF

                
DONE //move on from here when we get there.