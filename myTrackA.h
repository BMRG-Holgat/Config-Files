/*
* myTrackA.h
*
* Sequences for Track A
* Up Goods Slow
*
* V. 0.0.1
*  Setup basics
*  All Sequences start from Board 1 and end on Board 2
*
* V 0.1.0
* First single loop created
* All basic sequences created
*
*/
/*
//initsl starting positions
AUTOMATION(140,"A: Start Pos 2")
ROUTE_HIDDEN(140)
RESERVE(A_B7)
SCREEN(3,7,"A_B7 Reserved")
FWD(15)
FOLLOW(51)

AUTOMATION(141,"A: Start Pos 3")
ROUTE_HIDDEN(141)
RESERVE(A_B6)
SCREEN(3,6,"A_B6 Reserved")
FWD(15)
FOLLOW(50)
*/

//Track A from yard

AUTOMATION(100,"A: Run Track A")
    IFSTASH(TA)
            PICKUP_STASH(TA)
            FON(0)
            FON(1)
        ELSE    
            FOLLOW(100)
        ENDIF
    FOLLOW(1100)
DONE

AUTOMATION(1100,"A: Around We Go Auto")
    IFRESERVE(A_B1)
        IFTHROWN(9026)
            CLOSE(9026)
        ENDIF
        IFTHROWN(9001)
            CLOSE(9001)
        ENDIF
        IFCLOSED(UGS_T2_H)
            THROW(UGS_T2_H)
        ENDIF
    ELSE 
        FOLLOW(1100)
    ENDIF
    FWD(20)
    AT(CD_S1_A)
    FON(1)
    FREE(A_B7)
    AT(CD_S1_AA)
FOLLOW(1101)

SEQUENCE(1101)
    IFRESERVE(A_B2)
        IFTHROWN(9004)
            CLOSE(9004)
        ENDIF 
        IFTHROWN(9007)
            CLOSE(9007)
        ENDIF
    ELSE
        WAIT_WHILE_RED(SIG_A1)
        FOLLOW(1101)
    ENDIF
    IFAMBER(SIG_A1)
        SPEED(20)
    ELSE
        SPEED(30)
    ENDIF
    AT(CD_S2_A)
FOLLOW(1102)

SEQUENCE(1102)
    RED(SIG_A1)
    IFRESERVE(A_B3)
        SPEED(30)
    ELSE
        AT(CD_S3_A) 
        WAIT_WHILE_RED(SIG_A2)
        FOLLOW(1102)
    ENDIF
    IFAMBER(SIG_A2)
        SPEED(20)
    ELSE 
        SPEED(30)
    ENDIF
    AFTER(CD_S3_A)
        FREE(A_B1)
    AT(CD_S5_A)
FOLLOW(1103)

SEQUENCE(1103)
    RED(SIG_A2)
    IFRESERVE(A_B4)
        IFTHROWN(UGS_T5_E__UFM_T6_A)
            CLOSE(9020)
            CLOSE(9021)
        ENDIF
    ELSE
        AT(CD_S7_A)
        WAIT_WHILE_RED(SIG_A3)
        FOLLOW(1103)
    ENDIF
    AT(CD_S8_A)
FOLLOW(1104)

SEQUENCE(1104)
    RED(SIG_A3)
    AMBER(SIG_A1)
    FREE(A_B2)
    IFRESERVE(A_B5)
        IFTHROWN(9023)
            CLOSE(9023)
        ENDIF
    ELSE
        AT(CD_S9_A)
        WAIT_WHILE_RED(SIG_A4)
        FOLLOW(1104)
    ENDIF
    IFAMBER(SIG_A4)
        SPEED(20)
    ELSE
        SPEED(30)
    ENDIF
    AT(CD_S9_A1)
FOLLOW(1105)

SEQUENCE(1105)
    RED(SIG_A4)
    AMBER(SIG_A2)
    FREE(A_B3)
    GREEN(SIG_A1)
    FOFF(1)
    AT(CD_F7_A)
FOLLOW(1106)

SEQUENCE(1106)
    AMBER(SIG_A3)
    GREEN(SIG_A2)
    FREE(A_B4)
    RESERVE(A_B6)
    FREE(A_B5)
    SPEED(20)
    AT(CD_F6_A)
FOLLOW(1107)

SEQUENCE(1107)
    AMBER(SIG_A4) 
    GREEN(SIG_A3)
    AT(CD_F4_A)
FOLLOW(1108)

SEQUENCE(1108)
    RESERVE(A_B7)
    FREE(A_B6)
    SPEED(20) 
    GREEN(SIG_A4)
    AT(CD_F2_A)
FOLLOW(1109)

SEQUENCE(1109) 
    STOP
    FOFF(0)
    STASH(TA)
DONE



