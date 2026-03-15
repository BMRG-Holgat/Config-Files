/*
* myTrackC.h
* Add in the routes for trackD only
*
* V 0.1.0
*           390 - 394 Free yard tracks
*           395 - 399 Reserve yard tracks
*           301 - Auto Park
*           1300 - Breaktime Select
*           1301 - Break time
*           1302 Around We Go
*           1321 - Track 1
*           1322 - Track 2
*           1323 - Track 3
*           1324 - Track 4
*           1325 - TRack 5
*
*/

SEQUENCE(350) //Disable routes
   ROUTE_DISABLED(1321)
   ROUTE_DISABLED(1322)
   ROUTE_DISABLED(1323)
   ROUTE_DISABLED(1324)
   ROUTE_DISABLED(1325)
   ROUTE_DISABLED(1302)
   RETURN
DONE

SEQUENCE(351) //Enable routes
    ROUTE_ACTIVE(1321)
    ROUTE_ACTIVE(1322)
    ROUTE_ACTIVE(1323)
    ROUTE_ACTIVE(1324)
    ROUTE_ACTIVE(1325)
    ROUTE_ACTIVE(1302)

RETURN
DONE

//Manually activate the auto park sequence
AUTOMATION(1301,"C: Park Train")   
    ROUTE_HIDDEN(1301)
    CALL(352)
    ROUTE_ACTIVE(1301)
DONE

AUTOMATION(1302,"C: Around we go")
    CALL(350)
    FON(0)
    PRINT("Calling 300")
    CALL(300) //Leave yard
    PRINT("Calling 301")
    CALL(301) // Approach bridge
    PRINT("Calling 302")
    CALL(302) //Reserve Block 2 and wait for signal
    PRINT("Calling 303")
    CALL(303) //Reserved block 2
    PRINT("Calling 304")
    CALL(304) //Check signal
    PRINT("Calling 305")
    CALL(305) //Approach gantry 2       
    PRINT("Calling 306")
    CALL(306) //Bypass station
    FOFF(1)
    PRINT("Calling 307")    
    CALL(307)
    PRINT("Ended")
    FOFF(0)
    IF(autoRunning_C)
        RETURN 
    ENDIF
DONE

AUTOMATION(1303,"C: Change to E")
    CALL(350)
    FON(0)
    PRINT("Calling 300")
    CALL(300) //Leave yard
    PRINT("Calling 301")
    CALL(301) // Approach bridge
    PRINT("Calling 302")
    CALL(302) //Reserve Block 2 and wait for signal
    PRINT("Calling 303")
    CALL(303) //Reserved block 2
    PRINT("Calling 304")
    CALL(304) //Check signal
    PRINT("Calling 305")
    CALL(305) //Approach gantry 2       
    PRINT("Calling 306")
    CALL(306) //Bypass station
    FOFF(1)
    PRINT("Calling 507")    
    CALL(507)
    PRINT("Calling 508")
    CALL(508)
    PRINT("Calling 509")
    CALL(509)
    PRINT("Calling 552 Autopark")
    CALL(552)
    FOFF(0)
    PRINT("Ended")
    IF(autoRunning_C)
        RETURN 
    ENDIF
DONE





//Auto Park Sequence
SEQUENCE(352)
IFNOT(CD_F8_C1) 
    RESERVE(C_B6)
    CLOSE(9123)
    RESTORE_SPEED 
    AT(CD_F8_C1)
    DELAY(3000) ESTOP
    FREE(C_B5)
    STASH(TC1)
    RETURN
ENDIF 
IFNOT(CD_F8_C2) 
    RESERVE(C_B7)
    THROW(9123)
    RESTORE_SPEED 
    AT(CD_F8_C2) 
    DELAY(2000) ESTOP
    FREE(C_B5)
    STASH(TC2)
    RETURN
ENDIF 
IFNOT(CD_F8_C3) 
    RESERVE(C_B8)
    THROW(9122)
    RESTORE_SPEED 
    AT(CD_F8_C3)
    DELAY(1600) ESTOP
    FREE(C_B5)
    STASH(TC3)
    RETURN
ENDIF 
IFNOT(CD_F8_C4) 
    RESERVE(C_B9)
    THROW(9121)
    RESTORE_SPEED 
    AT(CD_F8_C4)
    DELAY(600) ESTOP
    FREE(C_B5)
    STASH(TC4)
    RETURN
ENDIF 
IFNOT(CD_F8_C5) 
    RESERVE(C_B10)
    CLOSE(9120)
    RESTORE_SPEED 
    AT(CD_F8_C5) 
    DELAY(400) ESTOP
    FREE(C_B5)
    STASH(TC5)
    RETURN
ENDIF 
DONE

//Automated drive
SEQUENCE(300) //Leave yard 
    IFRESERVE(C_B1)  
        IFTHROWN(9024)
            CLOSE(9024) //close turnouts E -> C rear
        ENDIF
    ELSE 
        FOLLOW(300)
    ENDIF
    SPEED(20)
    AT(CD_S9_C)
    RETURN
DONE

SEQUENCE(301) //Progress to Block2 
    CALL(353)
    CALL(351)
    IFLOCO(SoundLoco) 
        FON(1) //Sound loco if the train has a sound decoder
    ENDIF
    IFRED(SIG_C4)
        SPEED(20)
    ENDIF
    IFAMBER(SIG_C4)
        SPEED(30)
    ENDIF
    IFGREEN(SIG_C4)
        SPEED(40)
    ENDIF
    AT(CD_S9_C2)
    SAVE_SPEED
    RETURN
DONE


SEQUENCE(302)
    IFRESERVE(C_B2)
        IFTHROWN(9021)  
            CLOSE(9021) //close turnouts A->D
        ENDIF
        SPEED(40)
    ELSE
        WAIT_WHILE_RED(SIG_C4)
        FOLLOW(302)
    ENDIF
    AT(CD_S8_C)
    SAVE_SPEED
    RETURN
DONE

SEQUENCE(303)
    RED(SIG_C4)
    AT(CD_S6_C)
    IFRED(SIG_C2)
        SPEED(30)
    ENDIF
    AT(CD_S5_C)
    IFRED(SIG_C2)
        SPEED(25)
    ENDIF
    IFAMBER(SIG_C2)
        SPEED(30)
        SAVE_SPEED
    ENDIF
    AT(CD_S4_C)
    SAVE_SPEED
    RETURN 
DONE    

SEQUENCE(304) //Progress to Block3
    IFRESERVE(C_B3) //Reserve Next block
        FREE(C_B1)
        IFTHROWN(9011)
            CLOSE(9011) //prevent route C->E
        ENDIF
        IFTHROWN(9010) //prevent route D->B
            CLOSE(9010)
        ENDIF
        IFTHROWN(9005)
            CLOSE(9005) // prevent route C->D
        ENDIF
        RESTORE_SPEED
    ELSE   
        WAIT_WHILE_RED(SIG_C2)
        FOLLOW(304)
    ENDIF
    AT(CD_S3_C)
    RED(SIG_C2)
    AT(CD_F1_C)
    SAVE_SPEED
    RETURN 
DONE    

SEQUENCE(305)
    IFRESERVE(C_B4)
        IFTHROWN(9002)
            CLOSE(9002)
        ENDIF
        FREE(C_B2) 
        AMBER(SIG_C4)
    ELSE
        ESTOP
        FOLLOW(305)
    ENDIF
    RESTORE_SPEED
     AT(CD_F2_C)
    RETURN 
DONE

SEQUENCE(306)
    IFRESERVE(C_B5)
        FOFF(1)
        SPEED(25)
        FREE(C_B3)
        AMBER(SIG_C2)
        IFRED(SIG_C4)
        ELSE
            GREEN(SIG_C4)
        ENDIF
    ELSE
        ESTOP
        FOLLOW(306)
    ENDIF
    AT(CD_F4_C)
    SAVE_SPEED
    RETURN 
DONE    

SEQUENCE(307)
    IFRED(SIG_C2)
    ELSE
        GREEN(SIG_C2)
    ENDIF
    FREE(C_B4)
    SCREEN(4,4,"")
    CALL(352) //Auto Park
    RETURN
DONE

SEQUENCE(308)
    RED(SIG_C2)
    IFRESERVE(E_B3)
        IFCLOSED(9011)
            THROW(9011) //Close C->E if thrown to prevent deadlock
        ENDIF
    ELSE
        AT(CD_S4_C)
        WAIT_WHILE_RED(SIG_C2)
        FOLLOW(308)
    ENDIF   
    RESTORE_SPEED
    RETURN
DONE

SEQUENCE(309)
    AT(CD_S3_H_ext)
    RED(SIG_C2)
    RETURN 
DONE

SEQUENCE(310)

    RETURN 
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(353) //Release Parked Block dependant on turnout thrown
    IFCLOSED(9126) //Track FD1
        FREE(C_B6)
        SCREEN(2,1,"")
        CLEAR_STASH(TC1)
        RETURN
    ENDIF
    IFTHROWN(9127) //Track FD2
        FREE(C_B7)
        SCREEN(2,2,"")
        CLEAR_STASH(TC2)
        RETURN
    ENDIF
    IFTHROWN(9128) //Track FD3
        FREE(C_B8)
        SCREEN(2,3,"")
        CLEAR_STASH(TC3)
        RETURN
    ENDIF
    IFTHROWN(9129) //Track FD4
        FREE(C_B9)
        SCREEN(2,4,"")
        CLEAR_STASH(TC4)
        RETURN
    ENDIF
    IFCLOSED(9129) //Track FD5
        FREE(C_B10)
        SCREEN(2,5,"")
        CLEAR_STASH(TC5)
        RETURN
    ENDIF
DONE





AUTOMATION(1321,"C: Run Track 1") //Auto Track 1
   CALL(350)
   IFSTASH(TC1)
        CLOSE(9126) //Close exit to allow roundy
        PICKUP_STASH(TC1)
        FON(0)
    ELSE
        PRINT("No Train")
        CALL(351)
        RETURN
    ENDIF 
    FOLLOW(1302)
   IF(autoRunning_C)
    RETURN
   ENDIF 
DONE

AUTOMATION(1322,"C: Run Track 2") //Auto Track 2
   CALL(350)
   IFSTASH(TC2)
        THROW(9127) 
        PICKUP_STASH(TC2)
      FON(0)
    ELSE
        PRINT("No Train")
        CALL(351)
        RETURN
    ENDIF
    FOLLOW(1302)
   IF(autoRunning_C)
    RETURN
   ENDIF 
DONE

AUTOMATION(1323,"C: Run Track 3") //Auto Track 3
   CALL(350)
   IFSTASH(TC3)
     THROW(9128) 
     PICKUP_STASH(TC3)
     FON(0)
    ELSE
        PRINT("No Train")
        CALL(351)
        RETURN
    ENDIF
    FOLLOW(1302)
   IF(autoRunning_C)
    RETURN
   ENDIF 
DONE

AUTOMATION(1324,"C: Run Track 4") //Auto Track 4
   CALL(350)
   IFSTASH(TC4)
      THROW(9129) 
      PICKUP_STASH(TC4)
      FON(0)
    ELSE
      PRINT("No Train")
      CALL(351)
      RETURN
    ENDIF
    FOLLOW(1302)
   IF(autoRunning_C)
    RETURN
   ENDIF 
DONE

AUTOMATION(1325,"C: Run Track 5") //Auto Track 5
   CALL(350)
   IFSTASH(TC5)
     CLOSE(9129) 
     PICKUP_STASH(TC5)
     FON(0)
    ELSE
      PRINT("No Train")
      CALL(351)
      RETURN
    ENDIF
    FOLLOW(1302)
   IF(autoRunning_C)
    RETURN
   ENDIF 
DONE

ROUTE(1300,"C: Breaktime Select") //Select whether to run auto or not
    IF(autoSelected_C)
        UNLATCH(autoSelected_C)
        ROUTE_HIDDEN(1301)
        ROUTE_CAPTION(1300,"Enable")
    ELSE
        LATCH(autoSelected_C)
        ROUTE_ACTIVE(1301)
        ROUTE_CAPTION(1300,"Disable")
    ENDIF
DONE


//Automatic Running
AUTOMATION(1331,"C: Break time")
PRINT("At start of auto selection for C")
    SCREEN(2,5,"Yard C Automatic")
    SCREEN(3,5,"Yard C Automatic")
    SCREEN(4,5,"Yard C Automatic")
IF(autoSelected_C)
    LATCH(autoRunning_C) //Full auto Track C
    ROUTE_DISABLED(1331)
    ROUTE_CAPTION(1331,"RUNNING")
    RANDOM_CALL(1321,1322,1323,1324,1325)
    FOLLOW(1331)
ELSE
    ROUTE_ACTIVE(1331)
    ROUTE_CAPTION(1331,"STOPPED")
    SCREEN(2,5,"")
    SCREEN(3,5,"")
    SCREEN(4,5,"")
    UNLATCH(autoRunning_C) //Full auto Track B
    DONE
ENDIF
DONE