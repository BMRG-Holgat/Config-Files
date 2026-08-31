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
*       1110 - Around we Go
*       1111 - Station Stop
*       1112 - Change to B North
*       1113 - Change to B South
*       1114 - Change to D South
*       1120 - Run Track A
*/

//Disable Routes
SEQUENCE(150) //Disable routes
    SCREEN(2,0,"Automation running")
    SCREEN(3,0,"Automation running")
    ROUTE_DISABLED(1110)
    ROUTE_DISABLED(1111)
    ROUTE_DISABLED(1112)
    ROUTE_DISABLED(1113)
//    ROUTE_DISABLED(1114)
    ROUTE_DISABLED(1120)
    ROUTE_DISABLED(140)
    ROUTE_DISABLED(141)
   RETURN
DONE

SEQUENCE(151) //Enable routes
    ROUTE_ACTIVE(1110)
    ROUTE_ACTIVE(1111)
    ROUTE_ACTIVE(1112)
    ROUTE_ACTIVE(1113)
//    ROUTE_ACTIVE(1114)
    ROUTE_ACTIVE(1120)
    ROUTE_ACTIVE(140)
    ROUTE_ACTIVE(141)
    RETURN
DONE

//inital starting positions
AUTOMATION(140,"A: Start Pos 2")
ROUTE_HIDDEN(140)
RESERVE(A_B7)
SCREEN(3,7,"A_B7 Reserved")
FWD(15)
CALL(119)
DONE


AUTOMATION(141,"A: Start Pos 3")
ROUTE_HIDDEN(141)
RESERVE(A_B6)
SCREEN(3,6,"A_B6 Reserved")
FWD(15)
CALL(117)
RETURN
DONE


//Track A from yard

AUTOMATION(1120,"A: Run Track A")
    IFSTASH(TA)
            PICKUP_STASH(TA)
            FON(0)
//            FON(1)
        ELSE    
            FOLLOW(1120)
        ENDIF
    CALL(1110)
DONE

AUTOMATION(1110,"A: Around we go")
    CALL(150)
    FON(0)
    PRINT("CALL 110")
    CALL(110)
    CALL(151)
    PRINT("CALL 111")
    CALL(111)
    PRINT("CALL 112")
    SEQUENCE(130)
    CALL(112)
    SEQUENCE(1131)
    PRINT("CALL 113")
    CALL(113)
    PRINT("CALL 114")
    CALL(114)
    PRINT("CALL 115")
    CALL(115)
    PRINT("CALL 116")
    CALL(116)
    PRINT("CALL 117")
    CALL(117)
    PRINT("CALL 118")
    CALL(118)
    PRINT("CALL 119")
    CALL(119)
    PRINT("Ended track A")
DONE

AUTOMATION(1111,"A: Station STOP")
    PRINT("Call 110")
    CALL(110)
    RED(720)
    RED(740)
    PRINT("Call 120")
    CALL(120)
    GREEN(720)
    GREEN(740)
    FOLLOW(130)
    SCREEN(2,1,"")
    SCREEN(3,1,"")
    PRINT("Ended A Station")

DONE

AUTOMATION(1112,"A: Scenic A to B N")
    CALL(150)
    FON(0)
    PRINT("CALL 110")
    CALL(110)
    CALL(151)
    PRINT("CALL 121")
    CALL(121)
    FOLLOW(1291)

DONE

AUTOMATION(1113,"A Scenic A to B S")
    CALL(150)
    FON(0)
    PRINT("Call 110")
    CALL(110)
    PRINT("Call 151")
    CALL(151)
    PRINT("Call 111")
    CALL(111)
    PRINT("Call 112")
    CALL(112)
    PRINT("Call 122")
    FOLLOW(291)

DONE

SEQUENCE(110)
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
        FOLLOW(110)
    ENDIF
    FWD(20)
    AT(CD_S1_A)
    IFLOCO(SoundLoco)
        FON(1)
    ENDIF
    FREE(A_B7)
    AT(CD_S1_AA)
    SAVE_SPEED
    RETURN
DONE

SEQUENCE(111)
    IFRESERVE(A_B2)
        IFTHROWN(9004)
            CLOSE(9004)
        ENDIF 
        IFTHROWN(9007)
            CLOSE(9007)
        ENDIF
    ELSE
        STOP
        WAIT_WHILE_RED(SIG_A1)
        FOLLOW(111)
    ENDIF
    IFAMBER(SIG_A1)
        SPEED(AMBER_SPEED)
    ELSE
        RESTORE_SPEED
    ENDIF
    AT(CD_S2_A)
    SAVE_SPEED
    RETURN
DONE

SEQUENCE(112)
    RED(SIG_A1)
    IFRESERVE(A_B3)
        RESTORE_SPEED
    ELSE
        AT(CD_S3_A) 
        STOP
        WAIT_WHILE_RED(SIG_A2)
        FOLLOW(112)
    ENDIF
    IFAMBER(SIG_A2)
        SPEED(AMBER_SPEED)
    ELSE 
        RESTORE_SPEED
    ENDIF
    AFTER(CD_S3_A)
        FREE(A_B1)
    AT(CD_S4_A)
    SAVE_SPEED
    DELAY(1000)
    RETURN
DONE

SEQUENCE(113)
    RED(SIG_A2)
    IFRESERVE(A_B4)
        IFTHROWN(UGS_T5_E__UFM_T6_A)
            CLOSE(9020)
            CLOSE(9021)
        ENDIF
    ELSE
        AT(CD_S7_A)
        STOP
        WAIT_WHILE_RED(SIG_A3)
        FOLLOW(113)
    ENDIF
    IFAMBER(SIG_A3)
        SPEED(AMBER_SPEED)
    ELSE 
        RESTORE_SPEED
    ENDIF
    AT(CD_S8_A)
    RETURN
DONE

SEQUENCE(114)
    RED(SIG_A3)
    AMBER(SIG_A1)
    FREE(A_B2)
    IFRESERVE(A_B5)
        IFTHROWN(9023)
            CLOSE(9023)
        ENDIF
    ELSE
        AT(CD_S9_A)
        STOP
        WAIT_WHILE_RED(SIG_A4)
        FOLLOW(114)
    ENDIF
    IFAMBER(SIG_A4)
        SPEED(20)
    ELSE
        RESTORE_SPEED
    ENDIF
    AT(CD_S9_A1)
    RETURN
DONE

SEQUENCE(115)
    RED(SIG_A4)
    AMBER(SIG_A2)
    FREE(A_B3)
    GREEN(SIG_A1)
    FOFF(1)
    AT(CD_F7_A)
    RETURN
DONE

SEQUENCE(116)
    AMBER(SIG_A3)
    GREEN(SIG_A2)
    FREE(A_B4)
    RESERVE(A_B6)
    FREE(A_B5)
    SPEED(20)
    AT(CD_F6_A)
    RETURN
DONE

SEQUENCE(117)
    AMBER(SIG_A4) 
    GREEN(SIG_A3)
    AT(CD_F4_A)
    RETURN
DONE

SEQUENCE(118)
    RESERVE(A_B7)
    FREE(A_B6)
    SPEED(20) 
    GREEN(SIG_A4)
    AT(CD_F2_A)
    RETURN
DONE

SEQUENCE(119) 
    STOP
    FOFF(0)
    STASH(TA)
    RETURN
DONE

SEQUENCE(120)
    //Station STOP
    DELAY(1000)
    STOP 
    IFLOCO(SoundLoco) 
        DELAY(2000)
        FON(1)
        DELAY(500)
        FOFF(1)
    ENDIF
    DELAYRANDOM(10000,25000)
    RETURN
DONE

SEQUENCE(121)
    IFRESERVE(B_B3)
        IFRESERVE(A_B2)
            IFRESERVE(B_B2)
                IFCLOSED(9004)
                    THROW(9004)
                ENDIF 
                IFTHROWN(9007)
                    CLOSE(9007)
                ENDIF
                SPEED(30)
                SAVE_SPEED
            ELSE
                FREE(A_B2)
                FOLLOW(121)
            ENDIF
        ELSE
            FREE(B_B3)
            RED(SIG_A1)
            DELAY(3000)
            STOP
            FOLLOW(121)
        ENDIF
    ELSE
    IFAMBER(SIG_A1)
        SPEED(AMBER_SPEED)
    ELSE
        RESTORE_SPEED
    ENDIF
    AT(CD_S2_A)
    SAVE_SPEED
    RETURN
DONE

SEQUENCE(122) //track A -> B South
    RED(SIG_A2)
    
    RETURN
DONE