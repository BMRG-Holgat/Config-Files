/*
* myTrackC.h
* Add in the routes for trackD only
*
* V 0.1.0
*           390 - 394 Free yard tracks
*           395 - 399 Reserve yard tracks
*           301 - Auto Park
*           302 Around We Go
*           389 - Manual Auto Park
*
*/

SEQUENCE(350) //Disable routes
   ROUTE_DISABLED(302)
   ROUTE_DISABLED(1302)
   RETURN
DONE

SEQUENCE(351) //Enable routes
    ROUTE_ACTIVE(302)
    ROUTE_ACTIVE(1302)

RETURN
DONE


//Release Block when loco is removed from track
ROUTE(390,"C: Clear Track 1")
    ROUTE_HIDDEN(390)
    ROUTE_ACTIVE(395)
    FREE(C_B7)
    CLEAR_STASH(TC1) 
DONE
ROUTE(391,"C: Clear Track 2")
    ROUTE_HIDDEN(391)
    ROUTE_ACTIVE(396)
    FREE(C_B8)
    CLEAR_STASH(TC2) 
DONE
ROUTE(392,"C: Clear Track 3")
    ROUTE_HIDDEN(392)
    ROUTE_ACTIVE(397)
    FREE(C_B9)
    CLEAR_STASH(TC3)
DONE
ROUTE(393,"C: Clear Track 4")
    ROUTE_HIDDEN(393)
    ROUTE_ACTIVE(398)
    FREE(C_B10)
    CLEAR_STASH(TC4)
DONE
ROUTE(394,"C: Clear Track 5")
    ROUTE_HIDDEN(394)
    ROUTE_ACTIVE(399)
    FREE(C_B11)
    CLEAR_STASH(TC5)
DONE

//Set reserves for locos in yard to prevent other locos entering
ROUTE(395,"C: Load Track 1") //Auto park the train in the yard
    ROUTE_HIDDEN(395)
    ROUTE_ACTIVE(390)
    RESERVE(C_B7)
DONE
ROUTE(396,"C: Load Track 2") //Auto park the train in the yard
    ROUTE_HIDDEN(396)
    ROUTE_ACTIVE(391)
    RESERVE(C_B8)
DONE
ROUTE(397,"C: Load Track 3") //Auto park the train in the yard
    ROUTE_HIDDEN(397)
    ROUTE_ACTIVE(392)
    RESERVE(C_B9)
DONE
ROUTE(398,"C: Load Track 4") //Auto park the train in the yard
    ROUTE_HIDDEN(398)
    ROUTE_ACTIVE(393)
    RESERVE(C_B10)
DONE
ROUTE(399,"C: Load Track 5") //Auto park the train in the yard
    ROUTE_HIDDEN(399)
    ROUTE_ACTIVE(394)
    RESERVE(C_B11)
DONE 

//Manually activate the auto park sequence
AUTOMATION(389,"C: Manual Auto Park")   
    ROUTE_HIDDEN(389)
    CALL(301)
    ROUTE_ACTIVE(389)
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(300) //Release Parked Block dependant on turnout thrown
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


//Auto Park Sequence
SEQUENCE(301)
IFNOT(CD_F8_C1) 
    RESERVE(C_B6)
    SCREEN(2,1,"Block C6 Reserved")
    CLOSE(9123)
    FWD(20) 
    AT(CD_F8_C1)
    DELAY(3000) ESTOP
    FREE(C_B5)
    SCREEN(4,5,"")
    STASH(TC1)
    RETURN
ENDIF 
IFNOT(CD_F8_C2) 
    RESERVE(C_B7)
    SCREEN(2,2,"Block C7 Reserved")
    THROW(9123)
    FWD(20) 
    AT(CD_F8_C2) 
    DELAY(2000) ESTOP
    FREE(C_B5)
    SCREEN(4,5,"")
    STASH(TC2)
    RETURN
ENDIF 
IFNOT(CD_F8_C3) 
    RESERVE(C_B8)
    SCREEN(2,3,"Block C8 Reserved")
    THROW(9122)
    FWD(20) 
    AT(CD_F8_C3)
    DELAY(1600) ESTOP
    FREE(C_B5)
    SCREEN(4,5,"")
    STASH(TC3)
    RETURN
ENDIF 
IFNOT(CD_F8_C4) 
    RESERVE(C_B9)
    SCREEN(2,4,"Block C9 Reserved")
    THROW(9121)
    FWD(20) 
    AT(CD_F8_C4)
    DELAY(600) ESTOP
    FREE(C_B5)
    SCREEN(4,5,"")
    STASH(TC4)
    RETURN
ENDIF 
IFNOT(CD_F8_C5) 
    RESERVE(C_B10)
    SCREEN(2,5,"Block C10 Reserved")
    CLOSE(9120)
    FWD(30) 
    AT(CD_F8_C5) 
    DELAY(400) ESTOP
    FREE(C_B5)
    SCREEN(4,5,"")
    STASH(TC5)
    RETURN
ENDIF 
DONE

//Manual drive
AUTOMATION(302,"C: Around We Go Manual") //Leave yard 
    CALL(350)
    RESERVE(C_B1)
    SCREEN(4,1,"Block C1 Reserved")
    IFTHROWN(9024)
        CLOSE(9024) //close turnouts E -> C rear
    ENDIF
    SPEED(30)
    AT(CD_S9_C2)
FOLLOW(303)

SEQUENCE(303) //Progress to Block2 
    IFRESERVE(C_B2) //Reserve Next block
        CALL(300)
        CALL(351)
        SCREEN(4,2,"Block C2 Reserved")
        IFTHROWN(9021)  
            CLOSE(9021) //close turnouts A->D
        ENDIF
    ELSE
        AT(CD_S9_C)
        STOP
        FOLLOW(303)
    ENDIF
    AT(CD_S8_C)
    RED(SIG_C3)
    AT(CD_S6_C)
FOLLOW(304)

SEQUENCE(304) //Progress to Block3
    IFRESERVE(C_B3) //Reserve Next block
    SCREEN(4,3,"Block C3 Reserved")
        FREE(C_B1)
    SCREEN(4,1,"")
        IFTHROWN(9011)
            CLOSE(9011) //prevent route C->E
        ENDIF
        IFTHROWN(9010) //prevent route D->B
            CLOSE(9010)
        ENDIF
        IFTHROWN(9005)
            CLOSE(9005) // prevent route C->D
        ENDIF
    ELSE
        IFAMBER(SIG_C2)
            SPEED(25)
        ELSE
            AT(CD_S4_C)
            STOP
            FOLLOW(304)
        ENDIF
    ENDIF
    AT(CD_S3_C)
    RED(SIG_C2)
    AT(CD_S1_C)
FOLLOW(305)

SEQUENCE(305)
    RESERVE(C_B4)
    SCREEN(4,4,"Block C4 Reserved")
    IFTHROWN(9002)
        CLOSE(9002)
    ENDIF
    FREE(C_B2) 
    AMBER(SIG_C3)
    SCREEN(4,2,"")
    AT(CD_F3_C)
FOLLOW(306)

SEQUENCE(306)
    RESERVE(C_B5)
    SCREEN(4,5,"Block C5 Reserved")
    FREE(C_B3)
    AMBER(SIG_C2)
    GREEN(SIG_C3)
    SCREEN(4,3,"")
    AT(CD_F4_C)
FOLLOW(307)

SEQUENCE(307)
    FREE(C_B4)
    GREEN(SIG_C2)
    SCREEN(4,4,"")
    CALL(301) //Auto Park
    FOFF(0)
DONE

//Automated drive
AUTOMATION(1302,"C: Around We Go Auto") //Leave yard 
    CALL(350)
    IFNOT(autoRunning_C)
        IFRESERVE(C_B1)
            PRINT("Waiting for BLOCK C1")
        ELSE
            FOLLOW(1302)
        ENDIF
    ENDIF
    SCREEN(4,1,"Block C1 Reserved")
    IFTHROWN(9024)
        CLOSE(9024) //close turnouts E -> C rear
    ENDIF
    SPEED(30)
    AT(CD_S9_C2)
    SAVE_SPEED
FOLLOW(1303)

SEQUENCE(1303) //Progress to Block2 
    IFRESERVE(C_B2) //Reserve Next block
        CALL(300)
        CALL(351)
        SCREEN(4,2,"Block C2 Reserved")
        RESTORE_SPEED
    ELSE
        AT(CD_S9_C)
        WAIT_WHILE_RED(SIG_C3)
        FOLLOW(1303)
    ENDIF
    SPEED(40)
    AT(CD_S8_C)
    SAVE_SPEED
FOLLOW(1304)

SEQUENCE(1304)
    IFTHROWN(9021)  
        CLOSE(9021) //close turnouts A->D
        GREEN(SIG_D4)
    ENDIF
    IFTHROWN(9024)
        CLOSE(9024)
        GREEN(SIG_D4)
        FREE(D_B5)
    ENDIF
    RED(SIG_C3)
    AT(CD_S6_C)
    SAVE_SPEED
    IFRED(SIG_C2)
        SPEED(30)
    ENDIF
    AT(CD_S5_C)
    IFRED(SIG_C2)
        SPEED(25)
    ENDIF
FOLLOW(1305)

SEQUENCE(1305) //Progress to Block3
    IFRESERVE(C_B3) //Reserve Next block
    SCREEN(4,3,"Block C3 Reserved")
        FREE(C_B1)
    SCREEN(4,1,"")
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
        AT(CD_S4_C)
        WAIT_WHILE_RED(SIG_C2)
        FOLLOW(1305)
    ENDIF
    IFAMBER(SIG_C2)
        SPEED(25)
    ELSE
        SPEED(40)
    ENDIF
    AT(CD_S3_C)
    RED(SIG_C2)
    AT(CD_S1_C)
FOLLOW(1306)

SEQUENCE(1306)
    RESERVE(C_B4)
    SPEED(30)
    SCREEN(4,4,"Block C4 Reserved")
    IFTHROWN(9002)
        CLOSE(9002)
    ENDIF
    FREE(C_B2) 
    SCREEN(4,2,"")
    AMBER(SIG_C3)
    AT(CD_F1_C)
    FREE(C_B2)
    AT(CD_F3_C)
FOLLOW(1307)

SEQUENCE(1307)
    RESERVE(C_B5)
    SPEED(25)
    SCREEN(4,5,"Block C5 Reserved")
    FREE(C_B3)
    AMBER(SIG_C2)
    GREEN(SIG_C3)
    SCREEN(4,3,"")
    AT(CD_F4_C)
FOLLOW(1308)

SEQUENCE(1308)
    SPEED(20)
    GREEN(SIG_C2)
    FREE(C_B4)
    SCREEN(4,4,"")
    CALL(301) //Auto Park
    FOFF(0)
    IF(autoRunning_C)
        RETURN
    ENDIF
DONE


AUTOMATION(1321,"C: Run Track 1") //Auto Track 1
   CALL(350)
   IFSTASH(TC1)
    IFRESERVE(C_B1)
        CLOSE(9126) //Close exit to allow roundy
        PICKUP_STASH(TC1)
        FON(0)
    ELSE
        FOLLOW(1321)
    ENDIF 
    FOLLOW(1302)
   IF(autoRunning_C)
    RETURN
   ENDIF 
   ENDIF
DONE

AUTOMATION(1322,"C: Run Track 2") //Auto Track 2
   CALL(350)
   IFSTASH(TC2)
    IFRESERVE(C_B1)
        THROW(9127) 
        PICKUP_STASH(TC2)
      FON(0)
    ELSE
        FOLLOW(1322)
    ENDIF
    FOLLOW(1302)
   IF(autoRunning_C)
    RETURN
   ENDIF 
   ENDIF
DONE

AUTOMATION(1323,"C: Run Track 3") //Auto Track 3
   CALL(350)
   IFSTASH(TC3)
    IFRESERVE(C_B1)
     THROW(9128) 
     PICKUP_STASH(TC3)
     FON(0)
    ELSE
     FOLLOW(1323)
    ENDIF
    FOLLOW(1302)
   IF(autoRunning_C)
    RETURN
   ENDIF 
   ENDIF
DONE

AUTOMATION(1324,"C: Run Track 4") //Auto Track 4
   CALL(350)
   IFSTASH(TC4)
     IFRESERVE(C_B1)
      THROW(9129) 
      PICKUP_STASH(TC4)
      FON(0)
    ELSE
      FOLLOW(1324)
    ENDIF
    FOLLOW(1302)
   IF(autoRunning_C)
    RETURN
   ENDIF 
   ENDIF
DONE

AUTOMATION(1325,"C: Run Track 5") //Auto Track 5
   CALL(350)
   IFSTASH(TC5)
    IFRESERVE(C_B1)
     CLOSE(9129) 
     PICKUP_STASH(TC5)
     FON(0)
    ELSE
     FOLLOW(1325)
    ENDIF
    FOLLOW(1302)
   IF(autoRunning_C)
    RETURN
   ENDIF 
   ENDIF
DONE

ROUTE(1300,"C: Breaktime Select") //Select whether to run auto or not
    IF(autoSelected_C)
        UNLATCH(autoSelected_C)
        ROUTE_HIDDEN(1331)
    ELSE
        LATCH(autoSelected_C)
        ROUTE_ACTIVE(1331)
    ENDIF
DONE


//Automatic Running
AUTOMATION(1331,"C: Break time")
PRINT("At start of auto selection for C")
IF(autoSelected_C)
    LATCH(autoRunning_C) //Full auto Track C
    ROUTE_DISABLED(1331)
    ROUTE_CAPTION(1331,"RUNNING")
    RANDOM_CALL(1321,1322,1323,1324,1325)
    PRINT("C: NO TRAIN")
    FOLLOW(1331)
ELSE
    ROUTE_ACTIVE(1331)
    UNLATCH(autoRunning_C) //Full auto Track B
    DONE
ENDIF
DONE