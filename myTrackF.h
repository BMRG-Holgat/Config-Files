/*
* track F basic route definitions
*
* V 0.0.1
*           600 Roundy
*           601 Holgate
*/

SEQUENCE(650) //Disable routes
    ROUTE_DISABLED(1602)
    ROUTE_DISABLED(1603)
   RETURN
DONE

SEQUENCE(651) //Enable routes
    ROUTE_ACTIVE(1602)
    ROUTE_ACTIVE(1603)
    RETURN
DONE



//Leave staging yard and proceed to bridge
//AUTOSTART SEQUENCE(201)
// ALLOW 2 TRAINS TO CIRCULATE
 //Leave staging yard and proceed to bridge
  
 

//Leave staging yard and proceed to bridge 
AUTOMATION(1602,"F: Around we go" )
    CALL(650)
    CALL(600)
    CALL(601)
    CALL(602)
    CALL(603)
    CALL(604)
    CALL(605)
    SEQUENCE(620) //CALL FROM HOGATE
    PRINT("FROM 1700 -> 620")
    PRINT("Call 606")
    CALL(606)
    PRINT("Return 606")
    PRINT("Call 607")
    CALL(607)
    PRINT("Return 607")
    FOFF(1)
    PRINT("Call 608")
    CALL(608)
    PRINT("Return 608")
    PRINT("Call 609")
    CALL(609)
    PRINT("Return 609")
    PRINT("Call 610")
    CALL(610)
    PRINT("Return 610")
    PRINT("CALL 619")
    CALL(619)
    FOFF(0) 
    IF(autoRunning_F)
        RETURN
    ENDIF
DONE

AUTOMATION(1603,"F: Holgate")
    CALL(650)
    CALL(600)
    CALL(611)
    CALL(612)
    CALL(616)
    CALL(617)
    CALL(618)
    CALL(703)
    PRINT("RETURNED NOW WHAT!!!")
DONE



SEQUENCE(600)
    IFRESERVE(F_B1) //exit storage to bridge
        IFTHROWN(9025)
            CLOSE(9025)
        ENDIF
    FWD(30)
    ELSE
        FOLLOW(600)
    ENDIF
    AT(CD_F9_F)
    SAVE_SPEED
    RETURN
DONE
 

//Proceed to holgate access
SEQUENCE(601)
    CALL(651)
     IFLOCO(SoundLoco) 
        FON(1)
    ENDIF
    IFRESERVE(F_B2)
    FREE(F_B6)
        PRINT("FREED 126")
        IFTHROWN(9022)
            CLOSE(9022)
        ENDIF
        IFTHROWN(9031)
            CLOSE(9031)
        ENDIF
        IFAMBER(SIG_F4)
            SPEED(38)
        ENDIF
        IFGREEN(SIG_F4)
            SPEED(45)
        ENDIF
    ELSE
        AT(CD_S9_F)
        WAIT_WHILE_RED(SIG_F4)
        FOLLOW(601)
    ENDIF
    AT(CD_S9_F1)
    SAVE_SPEED
    RETURN
DONE

SEQUENCE(602)
    RED(SIG_F4)
    IFLOCO(SoundLoco)
        FON(2)
        DELAY(1000)
        FOFF(2)
        DELAY(1500)
        FON(2) 
        DELAY(1000)
        FOFF(2)
    ENDIF
    AT(CD_S6_F)
    RETURN
DONE

SEQUENCE(603)
    IFRED(SIG_F2)
        SPEED(35)
        PRINT("speed 35")
    ENDIF
    AT(CD_S5_F)
    RETURN
DONE

  SEQUENCE(604)
    IFRED(SIG_F2)
        SPEED(30)
        PRINT("speed 30")
    ENDIF
    AT(CD_S5_F)
    RETURN 
DONE  

SEQUENCE(605)
    IFRESERVE(F_B3)
        PRINT("RESERVE 123")
        FREE(F_B1)
        PRINT("FREED 121")
        IFTHROWN(9028)
            CLOSE(9028)
        ENDIF
        IFTHROWN(9006)
            CLOSE(9006)
        ENDIF
        IFAMBER(SIG_F2)
            SPEED(38)
        ENDIF
    ELSE
        AT(CD_S4_F)
        WAIT_WHILE_RED(SIG_F2)
        FOLLOW(605)
    ENDIF
    AT(CD_S3_F)
    RETURN
DONE

SEQUENCE(606)
    RED(SIG_F2)
    IFRESERVE(F_B4)
    PRINT("RESERVE 124")
        RESTORE_SPEED
    ELSE
        ESTOP
        FOLLOW(606)
    ENDIF
    AT(CD_F1_F)
    RETURN
DONE

SEQUENCE(607)
    IFCLOSED(9028)
        PRINT("9028 CLOSED")
        AMBER(SIG_F4)       
        FREE(F_B2)
        PRINT("FREED 122")
    ENDIF
    IFTHROWN(9027)
        CLOSE(9027)
    ENDIF
    AT(CD_F2_F)
    RETURN
DONE

SEQUENCE(608)
    IFRESERVE(F_B5)
    PRINT("RESERVED 125")
        IFTHROWN(9028)
            CLOSE(9028)
            CALL(751)
        ENDIF
        SPEED(30)
    ELSE
        ESTOP
        FOLLOW(608)
    ENDIF
    AT(CD_F3_F)
    RETURN 
DONE

SEQUENCE(609)
    IFRED(SIG_F4)
    ELSE
        GREEN(SIG_F4)
    ENDIF
    FREE(F_B3)
    PRINT("FREED 123")
    AMBER(SIG_F2)
    AT(CD_F5_F)
    RETURN
DONE

SEQUENCE(610)
    IFRESERVE(F_B6)
    PRINT("RESERVED 126")
        SPEED(30)
        FREE(F_B4)
        PRINT("FREED 124")
        GREEN(SIG_F2)
    ELSE  
        ESTOP
        FOLLOW(610)
    ENDIF
    AT(CD_F8_F)
    RETURN
DONE

SEQUENCE(619)
    FREE(F_B5)
    PRINT("FREED 125")
    ESTOP
    RETURN
DONE
    

SEQUENCE(611)
    CALL(651)
     IFLOCO(SoundLoco) 
        FON(1)
    ENDIF
AT(CD_S9_F)
SAVE_SPEED
RETURN
DONE

SEQUENCE(612)
PRINT("SEQ 612")
    IFSTASH(THA)       
        FOLLOW(613)
    ELSE
        RETURN
    ENDIF
DONE

SEQUENCE(613)
PRINT("SEQ 613")
    IFSTASH(THB)
        FOLLOW(614)
    ELSE
        RETURN
    ENDIF
DONE

SEQUENCE(614)
PRINT("SEQ 614")
    IFSTASH(THC)
        FOLLOW(615)
    ELSE
        RETURN
    ENDIF
DONE

SEQUENCE(615)
PRINT("SEQ 615")
    IFSTASH(THD)
        RED(SIG_F4)
        SCREEN(4,5,"Holgate Full")
        FOLLOW(616)
    ELSE
        RETURN
    ENDIF
DONE

SEQUENCE(616)
PRINT("SEQ 616")
IFRED(SIG_F4)
    WAIT_WHILE_RED(SIG_F4)
    FOLLOW(612)
ELSE 
    RESTORE_SPEED
    RETURN
ENDIF
DONE

SEQUENCE(617)
    IFRESERVE(F_B2)
    FREE(F_B6)
        IFTHROWN(9022)
            CLOSE(9022)
        ENDIF
        IFCLOSED(9031)
            THROW(9031)
        ENDIF
        IFAMBER(SIG_F4)
            SPEED(38)
        ENDIF
        IFGREEN(SIG_F4)
            SPEED(45)
        ENDIF
    ELSE
        DELAY(4000)
        WAIT_WHILE_RED(SIG_F4)
        FOLLOW(614)
    ENDIF
    AT(CD_S9_F1)
    IFLOCO(SoundLoco)
        FON(2)
        DELAY(1000)
        FOFF(2)
        DELAY(1500)
        FON(2) 
        DELAY(1000)
        FOFF(2)
    ENDIF
    SAVE_SPEED
    RETURN
DONE

SEQUENCE(618)
PRINT("615 SETTING RED")
    RED(SIG_F4)
    RETURN
DONE



