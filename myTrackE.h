/*
* myTrackE.h
* Add in the routes for trackD only
*
* V 0.1.0
*           590 - 594 Free yard tracks
*           595 - 599 Reserve yard tracks
*           501 - Auto Park
*           502 Around We Go
*           589  Manul Auto Park
*
*/

SEQUENCE(550) //Disable routes
   ROUTE_DISABLED(502)
   ROUTE_DISABLED(511)
   ROUTE_DISABLED(1502)
   ROUTE_DISABLED(1511)
   ROUTE_DISABLED(1521)
   ROUTE_DISABLED(1522)
   ROUTE_DISABLED(1523)
   ROUTE_DISABLED(1524)
   ROUTE_DISABLED(1525)
   RETURN
DONE

SEQUENCE(551) //Enable routes
    ROUTE_ACTIVE(502)
    ROUTE_ACTIVE(511)
    ROUTE_ACTIVE(1502)
    ROUTE_ACTIVE(1511)
    ROUTE_ACTIVE(1521)
    ROUTE_ACTIVE(1522)
    ROUTE_ACTIVE(1523)
    ROUTE_ACTIVE(1524)
    ROUTE_ACTIVE(1525)
    RETURN
DONE

//Release Block when loco is removed from track
ROUTE(590,"E: Track 1 Clear")
    ROUTE_HIDDEN(590)
    ROUTE_ACTIVE(595)
    FREE(E_B7)
    CLEAR_STASH(TE1)
DONE
ROUTE(591,"E: Track 2 Clear")
    ROUTE_HIDDEN(591)
    ROUTE_ACTIVE(596)
    FREE(E_B8)
    CLEAR_STASH(TE2)
DONE
ROUTE(592,"E: Track 3 Clear")
    ROUTE_HIDDEN(592)
    ROUTE_ACTIVE(597)
    FREE(E_B9)
    CLEAR_STASH(TE3)
DONE
ROUTE(593,"E: Track 4 Clear")
    ROUTE_HIDDEN(593)
    ROUTE_ACTIVE(598)
    FREE(E_B10)
    CLEAR_STASH(TE4)
DONE
ROUTE(594,"E: Track 5 Clear")
    ROUTE_HIDDEN(594)
    ROUTE_ACTIVE(599)
    FREE(E_B11)
    CLEAR_STASH(TE5)
DONE

//Set reserves for locos in yard to prevent other locos entering
ROUTE(595,"E: Track 1 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(595)
    ROUTE_ACTIVE(590)
    RESERVE(E_B7)
DONE
ROUTE(596,"E: Track 2 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(596)
    ROUTE_ACTIVE(591)
    RESERVE(E_B8)
DONE
ROUTE(597,"E: Track 3 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(597)
    ROUTE_ACTIVE(592)
    RESERVE(E_B9)
DONE
ROUTE(598,"E: Track 4 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(598)
    ROUTE_ACTIVE(593)
    RESERVE(E_B10)
DONE
ROUTE(599,"E: Track 5 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(599)
    ROUTE_ACTIVE(594)
    RESERVE(E_B11)
DONE 


//Manually activate the auto park sequence
AUTOMATION(589,"E: Manual Auto Park")   
    ROUTE_HIDDEN(589)
    CALL(501)
    ROUTE_ACTIVE(589)
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(500) //Release Parked Block dependant on turnout thrown
    IFCLOSED(9145) //Track FD1
        FREE(E_B6)
        SCREEN(2,1,"")
        CLEAR_STASH(TE1)
        RETURN
    ENDIF
    IFTHROWN(9146) //Track FD2
        FREE(E_B7)
        SCREEN(2,2,"")
        CLEAR_STASH(TE2)
        RETURN
    ENDIF
    IFTHROWN(9147) //Track FD3
        FREE(E_B8)
        SCREEN(2,3,"")
        CLEAR_STASH(TE3)
        RETURN
    ENDIF
    IFTHROWN(9148) //Track FD4
        FREE(E_B9)
        SCREEN(2,4,"")
        CLEAR_STASH(TE4)
        RETURN
    ENDIF
    IFCLOSED(9148) //Track FD5
        FREE(E_B10)
        SCREEN(2,5,"")
        CLEAR_STASH(TE5)
        RETURN
    ENDIF
DONE


//Auto Park Sequence
SEQUENCE(501)
IFNOT(CD_F8_E1) 
    RESERVE(E_B6)
    SCREEN(2,1,"Block B6 Reserved")
    CLOSE(9141)
    FWD(20) 
    AT(CD_F8_E1) ESTOP
    FREE(E_B5)
    SCREEN(4,5,"")
    RETURN
ENDIF 
IFNOT(CD_F8_E2) 
    RESERVE(E_B7)
    SCREEN(2,2,"Block B7 Reserved")
    THROW(9141)
    FWD(50) 
    AT(CD_F8_E2) ESTOP
    FREE(E_B5)
    SCREEN(4,5,"")
    RETURN
ENDIF 
IFNOT(CD_F8_E3) 
    RESERVE(E_B8)
    SCREEN(2,3,"Block B8 Reserved")
    THROW(9142)
    FWD(50) 
    AT(CD_F8_E3) ESTOP
    FREE(E_B5)
    SCREEN(4,5,"")
    RETURN
ENDIF 
IFNOT(CD_F7_E4) 
    RESERVE(E_B9)
    SCREEN(2,4,"Block B9 Reserved")
    THROW(9143)
    FWD(50) 
    AT(CD_F7_E4) ESTOP
    FREE(E_B5)
    SCREEN(4,5,"")
    RETURN
ENDIF 
IFNOT(CD_F7_E5) 
    RESERVE(E_B10)
    SCREEN(2,5,"Block B10 Reserved")
    CLOSE(9144)
    FWD(50) 
    AT(CD_F7_E5) ESTOP
    FREE(E_B5)
    SCREEN(4,5,"")
    RETURN
ENDIF 
DONE


//Start of main AUTOMATIONS for Track E
//Manual Round run
AUTOMATION(502,"E: Around We Go Manual")
   CALL(550)
    IFNOT(autoRunning_E)
        IFRESERVE(E_B1)
            PRINT("Waiting for Block E1")
        ELSE
            FOLLOW(502)
        ENDIF
    ENDIF
    SCREEN(4,1,"Block E1 Reserved")
    IFTHROWN(9025)
        CLOSE(9025)
    ENDIF
    IFTHROWN(9024)
        CLOSE(9024)
    ENDIF
    AT(CD_F9_E)
    SAVE_SPEED
FOLLOW(503)

SEQUENCE(503)
    CALL(500)
    CALL(551)
    AT(CD_S9_E)
    SAVE_SPEED
FOLLOW(504)

SEQUENCE(504)
    IFRESERVE(E_B2)
        SCREEN(4,2,"Block E2 Reserved")
        IFTHROWN(9022)
            CLOSE(9022)
        ENDIF
    ELSE
        WAIT_WHILE_RED(SIG_E4)
        FOLLOW(504)
    ENDIF
    AT(CD_S9_E1)
    SAVE_SPEED
FOLLOW(505)

SEQUENCE(505)
    RED(SIG_E4)
    AT(CD_S6_E)
    SAVE_SPEED
    IFNOT(E_STN)
        CALL(507)
    ENDIF
    AT(CD_S5_E) 
FOLLOW(506)

SEQUENCE(506)
    IFRESERVE(E_B3)
        SCREEN(4,3,"Block E3 Reserved")
        FREE(E_B1)
        SCREEN(4,1,"")
        IFTHROWN(9011)
            CLOSE(9011)
        ENDIF
        IFTHROWN(9006)
            CLOSE(9006)
        ENDIF
        RESTORE_SPEED
    ELSE
        AT(CD_S4_E)
        WAIT_WHILE_RED(SIG_E2)
        FOLLOW(506)
    ENDIF
    AT(CD_S3_E)
    RED(SIG_E2)
    SAVE_SPEED
    IFTHROWN(9003)
        RESERVE(E_S_B4)
        SCREEN(4,4,"Block E_S_4 Reserved")
    ENDIF
    AT(CD_F3_E)
FOLLOW(509)

SEQUENCE(507) //ByPass Station
    IFCLOSED(9003)
        THROW(9003)
    ENDIF
RETURN

SEQUENCE(509)
    RESERVE(E_B5)
    IFTHROWN(9003)
        FREE(E_S_B4)
        SCREEN(2,4,"")
    ENDIF
    SCREEN(4,5,"Block E5 Reserved")
    AMBER(SIG_E4)
    FREE(E_B2)
    SCREEN(4,2,"")
    AT(CD_F4_E)
FOLLOW(510)

SEQUENCE(510)
    AMBER(SIG_E2)
    GREEN(SIG_E4)
    FREE(E_B3)
    IFTHROWN(9003)
        CLOSE(9003)
    ENDIF
    SCREEN(4,3,"")
    DELAY(2000)
    GREEN(SIG_E2)
    FREE(E_B4)
    SCREEN(4,4,"")
    CALL(501)
    FOFF(0)
    IF(autoRunning_E)
        RETURN
    ENDIF
DONE

//Stop Station
AUTOMATION(511,"E: Station")
    LATCH(E_STN)
    FOLLOW(502)
DONE

//Automatic round run
AUTOMATION(1502,"E: Around We Go Auto")
    CALL(550)
    IFNOT(autoRunning_E)
        IFRESERVE(E_B1)
            PRINT("Waiting for Block E1")
        ELSE
            FOLLOW(1502)
        ENDIF
    ENDIF
    SCREEN(4,1,"Block E1 Reserved")
    IFTHROWN(9025)
        CLOSE(9025)
    ENDIF
    IFTHROWN(9024)
        CLOSE(9024)
    ENDIF
    SPEED(20)
    AT(CD_F9_E)
    SAVE_SPEED
FOLLOW(1503)

SEQUENCE(1503)
    CALL(500)
    CALL(551)
    IFRED(SIG_E4) 
        SPEED(20)
    ENDIF
    AT(CD_S9_E)
    SAVE_SPEED
FOLLOW(1504)

SEQUENCE(1504)
    IFRESERVE(E_B2)
        SCREEN(4,2,"Block E2 Reserved")
        IFTHROWN(9022)
            CLOSE(9022)
        ENDIF
        IFAMBER(SIG_E4)
            SPEED(35)
        ELSE
            SPEED(45)
        ENDIF
    ELSE
        WAIT_WHILE_RED(SIG_E4)
        FOLLOW(1504)
    ENDIF
    AT(CD_S9_E1)
    SAVE_SPEED
FOLLOW(1505)

SEQUENCE(1505)
    RED(SIG_E4)
    AT(CD_S6_E)
    SAVE_SPEED
    IFNOT(E_STN)
        CALL(507)
    ENDIF
    IFRED(SIG_E2)
        SPEED(30)
    ENDIF
    AT(CD_S5_E) 
    IFRED(SIG_E2)
        SPEED(20)
    ENDIF
FOLLOW(1506)

SEQUENCE(1506)
    IFRESERVE(E_B3)
        SCREEN(4,3,"Block E3 Reserved")
        FREE(E_B1)
        SCREEN(4,1,"")
        IFTHROWN(9011)
            CLOSE(9011)
        ENDIF
        IFTHROWN(9006)
            CLOSE(9006)
        ENDIF
        RESTORE_SPEED
    ELSE
        AT(CD_S4_E)
        WAIT_WHILE_RED(SIG_E2)
        FOLLOW(1506)
    ENDIF
    IFAMBER(SIG_E2)
        SPEED(25)
    ELSE
        SPEED(40)
    ENDIF
    AT(CD_S3_E)
    RED(SIG_E2)
    SAVE_SPEED
    IFTHROWN(9003)
        RESERVE(E_S_B4)
        SCREEN(4,4,"Block E_S_4 Reserved")
    ENDIF
    AT(CD_F3_E)
FOLLOW(1509)

SEQUENCE(1507) //ByPass Station
    IFCLOSED(9003)
        THROW(9003)
    ENDIF
RETURN

SEQUENCE(1509)
    RESERVE(E_B5)
    UNLATCH(E_STN)
    IFTHROWN(9003)
        FREE(E_S_B4)
        SCREEN(2,4,"")
    ENDIF
    SCREEN(4,5,"Block E5 Reserved")
    AMBER(SIG_E4)
    FREE(E_B2)
    SCREEN(4,2,"")
    AT(CD_F4_E)
FOLLOW(1510)

SEQUENCE(1510)
    AMBER(SIG_E2)
    GREEN(SIG_E4)
    FREE(E_B3)
    IFTHROWN(9003)
        CLOSE(9003)
    ENDIF
    SCREEN(4,3,"")
    DELAY(2000)
    GREEN(SIG_E2)
    FREE(E_B4)
    SCREEN(4,4,"")
    CALL(501)
    FOFF(0)
    IF(autoRunning_E)
        RETURN
    ENDIF
DONE

//Stop Station
AUTOMATION(1511,"E: Station Auto")
    LATCH(E_STN)
    FOLLOW(1502)
    UNLATCH(E_STN)
DONE
    
// Change to track C
AUTOMATION(1512,"E: Move to C")
    IFRESERVE(C_B1)
        RESERVE(E_B1)
        RESERVE(D_B5)
        IFCLOSED(9024)
            THROW(9024)
            RED(SIG_D4)
        ENDIF
    ELSE
        FOLLOW(1512)
    ENDIF
    FWD(30)
    AT(CD_S9_C2)
    SAVE_SPEED
    FREE(E_B1)
    FREE(D_B5)
FOLLOW(1303)

//Automatic train choice
AUTOMATION(1521,"E: Run Track 1") //Auto Track 1
   CALL(550)
   IFSTASH(TE1)
    IFRESERVE(E_B1)
        CLOSE(9145) //Close exit to allow roundy
        PICKUP_STASH(TE1)
        FON(0)
    ELSE
        FOLLOW(1521)
    ENDIF 
    FOLLOW(1502)
   IF(autoRunning_E)
    RETURN
   ENDIF 
   ENDIF
DONE

AUTOMATION(1522,"E: Run Track 2") //Auto Track 2
   CALL(550)
   IFSTASH(TE2)
    IFRESERVE(E_B1)
        THROW(9146) 
        PICKUP_STASH(TE2)
      FON(0)
    ELSE
        FOLLOW(1522)
    ENDIF
    FOLLOW(1502)
   IF(autoRunning_E)
    RETURN
   ENDIF 
   ENDIF
DONE

AUTOMATION(1523,"E: Run Track 3") //Auto Track 3
   CALL(550)
   IFSTASH(TE3)
    IFRESERVE(E_B1)
     THROW(9147) 
     PICKUP_STASH(TE3)
     FON(0)
    ELSE
     FOLLOW(1523)
    ENDIF
    FOLLOW(1502)
   IF(autoRunning_E)
    RETURN
   ENDIF 
   ENDIF
DONE

AUTOMATION(1524,"E: Run Track 4") //Auto Track 4
   CALL(550)
   IFSTASH(TE4)
     IFRESERVE(E_B1)
      THROW(9148) 
      PICKUP_STASH(TE4)
      FON(0)
    ELSE
      FOLLOW(1524)
    ENDIF
    FOLLOW(1502)
   IF(autoRunning_E)
    RETURN
   ENDIF 
   ENDIF
DONE

AUTOMATION(1525,"E: Run Track 5") //Auto Track 5
   CALL(550)
   IFSTASH(TE5)
    IFRESERVE(E_B1)
     CLOSE(9148) 
     PICKUP_STASH(TE5)
     FON(0)
    ELSE
     FOLLOW(1525)
    ENDIF
    FOLLOW(1502)
   IF(autoRunning_E)
    RETURN
   ENDIF 
   ENDIF
DONE

ROUTE(1500,"E: Breaktime Select") //Select whether to run auto or not
    IF(autoSelected_E)
        UNLATCH(autoSelected_E)
        ROUTE_HIDDEN(1531)
    ELSE
        LATCH(autoSelected_E)
        ROUTE_ACTIVE(1531)
    ENDIF
DONE

//Automatic Running
AUTOMATION(1531,"E: Break time")
PRINT("At start of auto selection for E")
IF(autoSelected_E)
    LATCH(autoRunning_E) //Full auto Track E
    ROUTE_DISABLED(1531)
    ROUTE_CAPTION(1531,"RUNNING")
    RANDOM_CALL(1521,1522,1523,1524,1525)
    PRINT("E: NO TRAIN")
    FOLLOW(1531)
ELSE
    ROUTE_ACTIVE(1531)
    UNLATCH(autoRunning_C) //Full auto Track B
    DONE
ENDIF
DONE   


AUTOMATION(1532,"E: Holgate")
    CALL(550)
    IFNOT(autoRunning_E)
        IFRESERVE(E_B1)
            PRINT("Waiting for Block E1")
        ELSE
            FOLLOW(1532)
        ENDIF
    ENDIF
    SCREEN(4,1,"Block E1 Reserved")
    IFTHROWN(9024)
        CLOSE(9024)
    ENDIF
    SPEED(20)
    AT(CD_F9_E)
    SAVE_SPEED
    FOLLOW(1533)

SEQUENCE(1533)
    IFRESERVE(F_B2)
        THROW(9030)
        SPEED(30) 
    ELSE
        AT(CD_S9_E)
        STOP
        FOLLOW(1533)
    ENDIF
    AT(CD_S9_F1)
    RED(SIG_E4)
FOLLOW(701)






    FOLLOW(701)











