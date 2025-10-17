/*
* myTrackC.h
* Add in the routes for trackD only
*
* V 0.1.0
*           390 - 394 Free yard tracks
*           395 - 399 Reserve yard tracks
*           302 Around We Go
*           389 Auto Park
*
*/

SEQUENCE(350) //Disable routes
   ROUTE_DISABLED(302)

   RETURN
DONE

SEQUENCE(351) //Enable routes
    ROUTE_ACTIVE(302)

RETURN
DONE


//Release Block when loco is removed from track
ROUTE(390,"C: Track 1 Clear")
    ROUTE_HIDDEN(390)
    ROUTE_ACTIVE(395)
    FREE(C_B7)
    CLEAR_STASH(TC1) 
DONE
ROUTE(391,"C: Track 2 Clear")
    ROUTE_HIDDEN(391)
    ROUTE_ACTIVE(396)
    FREE(C_B8)
    CLEAR_STASH(TC2) 
DONE
ROUTE(392,"C: Track 3 Clear")
    ROUTE_HIDDEN(392)
    ROUTE_ACTIVE(397)
    FREE(C_B9)
    CLEAR_STASH(TC3)
DONE
ROUTE(393,"C: Track 4 Clear")
    ROUTE_HIDDEN(393)
    ROUTE_ACTIVE(398)
    FREE(C_B10)
    CLEAR_STASH(TC4)
DONE
ROUTE(394,"C: Track 5 Clear")
    ROUTE_HIDDEN(394)
    ROUTE_ACTIVE(399)
    FREE(C_B11)
    CLEAR_STASH(TC5)
DONE

//Set reserves for locos in yard to prevent other locos entering
ROUTE(395,"C: Track 1 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(395)
    ROUTE_ACTIVE(390)
    RESERVE(C_B7)
DONE
ROUTE(396,"C: Track 2 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(396)
    ROUTE_ACTIVE(391)
    RESERVE(C_B8)
DONE
ROUTE(397,"C: Track 3 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(397)
    ROUTE_ACTIVE(392)
    RESERVE(C_B9)
DONE
ROUTE(398,"C: Track 4 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(398)
    ROUTE_ACTIVE(393)
    RESERVE(C_B10)
DONE
ROUTE(399,"C: Track 5 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(399)
    ROUTE_ACTIVE(394)
    RESERVE(C_B11)
DONE 

//Manually activate the auto park sequence
AUTOMATION(389,"C: Manual Auto Park")   
    ROUTE_HIDDEN(389)
    CALL(300)
    ROUTE_ACTIVE(389)
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(300) //Release Parked Block dependant on turnout thrown
    IFCLOSED(9126) //Track FD1
        FREE(C_B6)
        CLEAR_STASH(TC1)
        RETURN
    ENDIF
    IFTHROWN(9127) //Track FD2
        FREE(C_B7)
        CLEAR_STASH(TC2)
        RETURN
    ENDIF
    IFTHROWN(9128) //Track FD3
        FREE(C_B8)
        CLEAR_STASH(TC3)
        RETURN
    ENDIF
    IFTHROWN(9129) //Track FD4
        FREE(C_B9)
        CLEAR_STASH(TC4)
        RETURN
    ENDIF
    IFCLOSED(9129) //Track FD5
        FREE(C_B10)
        CLEAR_STASH(TC5)
        RETURN
    ENDIF
DONE


//Auto Park Sequence
SEQUENCE(301)
IFNOT(CD_F8_C1) 
    RESERVE(C_B6)
    CLOSE(9123)
    FWD(30) 
    AT(CD_F8_C1) ESTOP
    FREE(C_B5)
    SCREEN(4,5,"")
    STASH(TC1)
    RETURN
ENDIF 
IFNOT(CD_F8_C2) 
    RESERVE(C_B7)
    THROW(9123)
    FWD(30) 
    AT(CD_F8_C2) ESTOP
    FREE(C_B5)
    SCREEN(4,5,"")
    STASH(TC2)
    RETURN
ENDIF 
IFNOT(CD_F8_C3) 
    RESERVE(C_B8)
    THROW(9122)
    FWD(30) 
    AT(CD_F8_C3) ESTOP
    FREE(C_B5)
    SCREEN(4,5,"")
    STASH(TC3)
    RETURN
ENDIF 
IFNOT(CD_F7_C4) 
    RESERVE(C_B9)
    THROW(9121)
    FWD(30) 
    AT(CD_F7_C4) ESTOP
    FREE(C_B5)
    SCREEN(4,5,"")
    STASH(TC4)
    RETURN
ENDIF 
IFNOT(CD_F7_C5) 
    RESERVE(C_B10)
    CLOSE(9120)
    FWD(30) 
    AT(CD_F7_C5) ESTOP
    FREE(C_B5)
    SCREEN(4,5,"")
    STASH(TC5)
    RETURN
ENDIF 
DONE

//Manual drive
AUTOMATION(302,"C: Around We Go") //Leave yard 
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
    CALL(300)
    CALL(351)
    IFRESERVE(C_B2) //Reserve Next block
        SCREEN(4,2,"Block C2 Reserved")
        IFTHROWN(9021)  
            CLOSE(9021) //close turnouts A->D
        ENDIF
    ELSE
        AT(CD_S9_C)
        STOP
        FOLLOW(303)
    ENDIF
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
    AT(CD_S1_C)
FOLLOW(305)

SEQUENCE(305)
    RESERVE(C_B4)
    SCREEN(4,4,"Block C4 Reserved")
    IFTHROWN(9002)
        CLOSE(9002)
    ENDIF
    FREE(C_B2) 
    SCREEN(4,2,"")
    AT(CD_F3_C)
FOLLOW(306)

SEQUENCE(306)
    RESERVE(C_B5)
    SCREEN(4,5,"Block C5 Reerved")
    FREE(C_B3)
    SCREEN(4,3,"")
    AT(CD_F4_C)
FOLLOW(307)

SEQUENCE(307)
    FREE(C_B4)
    SCREEN(4,4,"")
    CALL(301) //Auto Park
    FOFF(0)
DONE

//Automated drive
AUTOMATION(1302,"C: Around We Go Full") //Leave yard 
    CALL(350)
    RESERVE(C_B1)
    SCREEN(4,1,"Block C1 Reserved")
    IFTHROWN(9024)
        CLOSE(9024) //close turnouts E -> C rear
    ENDIF
    SPEED(30)
    AT(CD_S9_C2)
FOLLOW(1303)

SEQUENCE(1303) //Progress to Block2 
    CALL(300)
    CALL(351)
    IFRESERVE(C_B2) //Reserve Next block
        SCREEN(4,2,"Block C2 Reserved")
        IFTHROWN(9021)  
            CLOSE(9021) //close turnouts A->D
        ENDIF
    ELSE
        AT(CD_S9_C)
        STOP
        FOLLOW(1303)
    ENDIF
    SPEED(40)
    AT(CD_S6_C)
FOLLOW(1304)

SEQUENCE(1304) //Progress to Block3
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
            FOLLOW(1304)
        ENDIF
    ENDIF
    SPEED(40)
    AT(CD_S1_C)
FOLLOW(1305)

SEQUENCE(1305)
    RESERVE(C_B4)
    SCREEN(4,4,"Block C4 Reserved")
    IFTHROWN(9002)
        CLOSE(9002)
    ENDIF
    FREE(C_B2) 
    SCREEN(4,2,"")
    AT(CD_F3_C)
FOLLOW(1306)

SEQUENCE(1306)
    RESERVE(C_B5)
    SCREEN(4,5,"Block C5 Reerved")
    FREE(C_B3)
    SCREEN(4,3,"")
    AT(CD_F4_C)
FOLLOW(1307)

SEQUENCE(1307)
    SPEED(20)
    FREE(C_B4)
    SCREEN(4,4,"")
    CALL(301) //Auto Park
    FOFF(0)
DONE



AUTOMATION(1321,"C: Track 1 roundy") //Auto Track 1
   CALL(350)
   IFSTASH(TC1)
    CLOSE(9126) //Close exit to allow roundy
    PICKUP_STASH(TC1)
    FON(0)
   ENDIF
FOLLOW(302)

AUTOMATION(1322,"C: Track 2 roundy") //Auto Track 2
   CALL(350)
   IFSTASH(TC2)
     THROW(9127) 
     PICKUP_STASH(TC2)
     FON(0)
   ENDIF
FOLLOW(302)

AUTOMATION(1323,"C: Track 3 roundy") //Auto Track 3
   CALL(350)
   IFSTASH(TC3)
     THROW(9128) 
     PICKUP_STASH(TC3)
     FON(0)
   ENDIF
FOLLOW(302)

AUTOMATION(1324,"C: Track 4 roundy") //Auto Track 4
   CALL(350)
   IFSTASH(TC4)
     THROW(9129) 
     PICKUP_STASH(TC4)
     FON(0)
   ENDIF
FOLLOW(302)

AUTOMATION(1325,"C: Track 5 roundy") //Auto Track 5
   CALL(350)
   IFSTASH(TC5)
     CLOSE(9129) 
     PICKUP_STASH(TC5)
     FON(0)
   ENDIF
FOLLOW(302)