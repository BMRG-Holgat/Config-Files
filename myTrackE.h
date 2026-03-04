/*
* myTrackE.h
* Add in the routes for trackD only
*
* V 0.1.0
*           590 - 594 Free yard tracks
*           595 - 599 Reserve yard tracks
*           501 - Park Train
*           502 Around We Go
*           1501 - Park Train

*
*
*/

SEQUENCE(550) //Disable routes
    ROUTE_DISABLED(1502)
    ROUTE_DISABLED(1503)
    ROUTE_DISABLED(1521)
    ROUTE_DISABLED(1522)
    ROUTE_DISABLED(1523)
    ROUTE_DISABLED(1524)
    ROUTE_DISABLED(1525)
   RETURN
DONE

SEQUENCE(551) //Enable routes
    ROUTE_ACTIVE(1502)
    ROUTE_ACTIVE(1503)
    ROUTE_ACTIVE(1521)
    ROUTE_ACTIVE(1522)
    ROUTE_ACTIVE(1523)
    ROUTE_ACTIVE(1524)
    ROUTE_ACTIVE(1525)
    RETURN
DONE

AUTOMATION(1501,"E: Park Train")
    ROUTE_HIDDEN(1501)
    CALL(552)
    ROUTE_ACTIVE(1501)
DONE

AUTOMATION(1502,"E: Around we go")
    CALL(550)
    FON(0)
    PRINT("Calling 500")
    CALL(500) //Leave yard
    PRINT("Calling 501")
    CALL(501) // Approach bridge
    PRINT("Calling 502")
    CALL(502) //Reserve Block 2 and wait for signal
    PRINT("Calling 503")
    CALL(503) //Reserved block 2
    PRINT("Calling 504")
    CALL(504) //Check signal
    PRINT("Calling 505")
    CALL(505) //Approach gantry 2
    PRINT("Calling 506")
    CALL(506) //Bypass station
    PRINT("Calling 507")
    CALL(507)
    FOFF(1)
    PRINT("Calling 508")
    CALL(508)
    PRINT("Calling 509")
    CALL(509)
    PRINT("Calling 510")
    CALL(510)
    PRINT("Calling 552 Autopark")
    CALL(552)
    FOFF(0)
    PRINT("Ended")
    IF(autoRunning_E)
        RETURN 
    ENDIF
DONE

AUTOMATION(1503,"E: To the Station")
    CALL(550)
    FON(0)
    PRINT("Calling 500")
    CALL(500) //Leave yard
    PRINT("Calling 501")
    CALL(501) // Approach bridge
    PRINT("Calling 502")
    CALL(502) //Reserve Block 2 and wait for signal
    PRINT("Calling 503")
    CALL(503)
    PRINT("Calling 511")
    CALL(511) //Reserved block 2
    PRINT("Calling 505")
    CALL(505) //Approach gantry 2
    PRINT("Calling 506")
    CALL(506)
    PRINT("Calling 512")
    CALL(512) //Station route 
    PRINT("Calling 513")
    CALL(513) //Station Stop   
    PRINT("Calling 514")
    CALL(514)
    FOFF(1)
    PRINT("Calling 508")
    CALL(508)
    PRINT("Calling 509")
    CALL(509)
    PRINT("Calling 510")
    CALL(510)
    PRINT("Calling 552 Autopark")
    CALL(552)
    FOFF(0)
    PRINT("Ended")
    IF(autoRunning_E)
        RETURN 
    ENDIF
DONE

SEQUENCE(1504)  //Around we go station  switching
    CALL(550)
    FON(0)
    PRINT("Calling 500")
    CALL(500) //Leave yard
    PRINT("Calling 501")
    CALL(501) // Approach bridge
    PRINT("Calling 502")
    CALL(502) //Reserve Block 2 and wait for signal
    PRINT("Calling 503")
    CALL(503) //Reserved block 2
    IF(CHOOSE_STN)
        UNLATCH(CHOOSE_STN)
        PRINT("Calling 504")
        CALL(504) //Check signal
    ELSE
        LATCH(CHOOSE_STN)
        PRINT("Calling 510")
        CALL(510)
    ENDIF
    PRINT("Calling 505")
    CALL(505) //Approach gantry 2  
  IF(CHOOSE_STN)
    PRINT("Calling 506")
    CALL(506) //Bypass station
    PRINT("Calling 507")
    CALL(507)
  ELSE
    PRINT("Calling 511")
    CALL(511)
  ENDIF
    FOFF(1)
    PRINT("Calling 508")
    CALL(508)
    PRINT("Calling 509")
    CALL(509)
    PRINT("Calling 552 Autopark")
    CALL(552)
    FOFF(0)
    PRINT("Ended")
    IF(autoRunning_E)
        RETURN 
    ENDIF
DONE

SEQUENCE(500)
    IFRESERVE(E_B1)
        IFTHROWN(9024)
            CLOSE(9024)
        ENDIF
    ELSE 
        FOLLOW(500)
    ENDIF
    SPEED(20)
    AT(CD_F9_E)
    RETURN 
DONE

SEQUENCE(501)
    CALL(553)
    CALL(551)
    IFLOCO(SoundLoco) 
        FON(1)
    ENDIF
    IFRED(SIG_E4)
        SPEED(20)
    ENDIF
    AT(CD_S9_E)
    SAVE_SPEED
    RETURN 
DONE

SEQUENCE(502)
    IFRESERVE(E_B2)
        IFTHROWN(9022)
            CLOSE(9022)
        ENDIF
        IFAMBER(SIG_E4)
            SPEED(38)
        ENDIF
        IFGREEN(SIG_E4)
            SPEED(45)
        ENDIF
    ELSE 
        WAIT_WHILE_RED(SIG_E4)
        FOLLOW(502)
    ENDIF
    AT(CD_S9_E1)
    SAVE_SPEED
    RETURN 
DONE

SEQUENCE(503) //Bypass station
    RED(SIG_E4)
    AT(CD_S6_E)    
    RETURN 
DONE

SEQUENCE(504)
    THROW(9003)
    RESTORE_SPEED
    IFRED(SIG_E2)
        SPEED(35)
        PRINT("speed 30")
    ENDIF
    AT(CD_S5_E)
    RETURN
DONE

SEQUENCE(505)
    IFRED(SIG_E2)
        SPEED(30)
        PRINT("speed 20")
    ENDIF
    RETURN 
DONE

SEQUENCE(506)
    IFRESERVE(E_B3)
        FREE(E_B1)
        IFTHROWN(9011)
            CLOSE(9011)
        ENDIF
        IFTHROWN(9006)
            CLOSE(9006)
        ENDIF
        RESTORE_SPEED
    ELSE 
    PRINT("B3 Reserved, should be waiting")
        AT(CD_S4_E)
        WAIT_WHILE_RED(SIG_E2)
        FOLLOW(506)
    ENDIF
    IFAMBER(SIG_E2)
        SPEED(38)
        PRINT("speed 30")
    ENDIF
    AT(CD_S3_E)
    SAVE_SPEED
    RETURN 
DONE

SEQUENCE(507)
    RED(SIG_E2)
    IFRESERVE(E_S_B4)
    RESTORE_SPEED
    ELSE 
        FOLLOW(506)
    ENDIF
    AT(CD_F2_E)
    RETURN 
DONE

SEQUENCE(508)
    IFRESERVE(E_B5)
        AMBER(SIG_E4)
        FREE(E_B2)
        RESTORE_SPEED
    ELSE 
        ESTOP
        FOLLOW(507)
    ENDIF
    AT(CD_F3_E)
    RETURN 
DONE

SEQUENCE(509)
    AMBER(SIG_E2)
    IFRED(SIG_E4)
    ELSE
        GREEN(SIG_E4)
    ENDIF
    FREE(E_B3)
    IFTHROWN(9003)
        FREE(E_S_B4)
        CLOSE(9003)
    ELSE 
        FREE(E_B4)
    ENDIF 
    AT(CD_F4_E)
    RETURN 
DONE

SEQUENCE(510)
    GREEN(SIG_E2)
    RETURN 
DONE

SEQUENCE(511) //Station route
    RED(SIG_E4)
    RESTORE_SPEED
    IFRED(SIG_E2)
        SPEED(30)
        PRINT("speed 30")
    ENDIF
    AT(CD_S4_E)
    SAVE_SPEED
    RETURN 
DONE
        
SEQUENCE(512)
    RED(SIG_E2)
    IFRESERVE(E_B4)
    RESTORE_SPEED
    SPEED(28)
    ELSE 
        FOLLOW(512)
    ENDIF
    AT(CD_S1_E)
    RETURN 
DONE

SEQUENCE(513)
    SAVE_SPEED
    FREE(E_B2)
    AMBER(SIG_E4)
    FREE(E_B3)
    GREEN(SIG_E2)
    DELAY(4500)
    STOP
    FREE(E_B3)
    DELAYRANDOM(10000,20000)
    IFLOCO(SoundLoco)
        FON(6)
        DELAY(750)
        FOFF(6)
        FON(4)
        DELAY(750)
        FOFF(4)
        DELAY(13000)
        FON(10)
        DELAY(750)
        FOFF(10)
    ENDIF
    RETURN
DONE 

SEQUENCE(514)
    IFRESERVE(E_B3)
    PRINT("I got B3")
    RED(SIG_E2)
        IFTHROWN(9003)
            CLOSE(9003)
        ENDIF
        RESTORE_SPEED
    ELSE
        STOP
        FOLLOW(513)
    ENDIF
    AT(CD_F2_E)
    RETURN
DONE




    //Auto Park Sequence
SEQUENCE(552)
IFNOT(CD_F8_E1) 
    RESERVE(E_B6)
    CLOSE(9141)
    FWD(30) 
    AT(CD_F8_E1) 
    DELAY(1500)
    ESTOP
    FREE(E_B5)
    STASH(TE1)
    RETURN
ENDIF 
IFNOT(CD_F8_E2) 
    RESERVE(E_B7)
    THROW(9141)
    FWD(30) 
    AT(CD_F8_E2)
    DELAY(1000)
    ESTOP
    FREE(E_B5)
    STASH(TE2)
    RETURN
ENDIF 
IFNOT(CD_F8_E3) 
    RESERVE(E_B8)
    THROW(9142)
    FWD(30) 
    AT(CD_F8_E3) 
    DELAY(500)
    ESTOP
    FREE(E_B5)
    STASH(TE3)
    RETURN
ENDIF 
IFNOT(CD_F7_E4) 
    RESERVE(E_B9)
    THROW(9143)
    FWD(30) 
    AT(CD_F7_E4) 
    DELAY(250)
    ESTOP
    FREE(E_B5)
    STASH(TE4)
    RETURN
ENDIF 
IFNOT(CD_F7_E5) 
    RESERVE(E_B10)
    CLOSE(9144)
    FWD(30) 
    AT(CD_F7_E5)
    DELAY(250)
    ESTOP
    FREE(E_B5)
    STASH(TE5)
    RETURN
ENDIF 
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(553) //Release Parked Block dependant on turnout thrown
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

//Automatic train choice
AUTOMATION(1521,"E: Run Track 1") //Auto Track 1
   CALL(550)
   IFSTASH(TE1)
        CLOSE(9145) //Close exit to allow roundy
        PICKUP_STASH(TE1)
        FON(0)
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF 
    IF(CHOOSE_STN)
        UNLATCH(CHOOSE_STN)
        FOLLOW(1502)
    ELSE
        LATCH(CHOOSE_STN)
        FOLLOW(1503)
    ENDIF
   IF(autoRunning_E)
    RETURN
   ENDIF 
DONE

AUTOMATION(1522,"E: Run Track 2") //Auto Track 2
   CALL(550)
   IFSTASH(TE2)
        THROW(9146) 
        PICKUP_STASH(TE2)
      FON(0)
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF
    IF(CHOOSE_STN)
        UNLATCH(CHOOSE_STN)
        FOLLOW(1502)
    ELSE
        LATCH(CHOOSE_STN)
        FOLLOW(1503)
    ENDIF
   IF(autoRunning_E)
    RETURN
   ENDIF 
DONE

AUTOMATION(1523,"E: Run Track 3") //Auto Track 3
   CALL(550)
   IFSTASH(TE3)
     THROW(9147) 
     PICKUP_STASH(TE3)
     FON(0)
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF
    IF(CHOOSE_STN)
        UNLATCH(CHOOSE_STN)
        FOLLOW(1502)
    ELSE
        LATCH(CHOOSE_STN)
        FOLLOW(1503)
    ENDIF
   IF(autoRunning_E)
    RETURN
   ENDIF 
DONE

AUTOMATION(1524,"E: Run Track 4") //Auto Track 4
   CALL(550)
   IFSTASH(TE4)
      THROW(9148) 
      PICKUP_STASH(TE4)
      FON(0)
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF
    IF(CHOOSE_STN)
        UNLATCH(CHOOSE_STN)
        FOLLOW(1502)
    ELSE
        LATCH(CHOOSE_STN)
        FOLLOW(1503)
    ENDIF
   IF(autoRunning_E)
    RETURN
   ENDIF 
DONE

AUTOMATION(1525,"E: Run Track 5") //Auto Track 5
   CALL(550)
   IFSTASH(TE5)
     CLOSE(9148) 
     PICKUP_STASH(TE5)
     FON(0)
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF
    IF(CHOOSE_STN)
        UNLATCH(CHOOSE_STN)
        FOLLOW(1502)
    ELSE
        LATCH(CHOOSE_STN)
        FOLLOW(1503)
    ENDIF
   IF(autoRunning_E)
    RETURN
   ENDIF 
DONE

ROUTE(1500,"E: Breaktime Select") //Select whether to run auto or not
    IF(autoSelected_E)
        UNLATCH(autoSelected_E)
        ROUTE_HIDDEN(1531)
        ROUTE_CAPTION(1500,"Enable")
    ELSE
        LATCH(autoSelected_E)
        ROUTE_ACTIVE(1531)
        ROUTE_CAPTION(1500,"Disable")
    ENDIF
DONE

//Automatic Running
AUTOMATION(1531,"E: Break time")
PRINT("At start of auto selection for E")
    SCREEN(2,7,"Yard E Automatic")
    SCREEN(3,7,"Yard E Automatic")
    SCREEN(4,7,"Yard E Automatic")
IF(autoSelected_E)
    LATCH(autoRunning_E) //Full auto Track E
    ROUTE_DISABLED(1531)
    ROUTE_CAPTION(1531,"RUNNING") 
    RANDOM_CALL(1521,1522,1523,1524,1525)
    FOLLOW(1531)
ELSE
    ROUTE_ACTIVE(1531)
    ROUTE_CAPTION(1531,"STOPPED")
    SCREEN(2,7,"")
    SCREEN(3,7,"")
    SCREEN(4,7,"")
    UNLATCH(autoRunning_E) //Full auto Track E
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

