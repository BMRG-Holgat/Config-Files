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
    CALL(301)
    ROUTE_ACTIVE(389)
DONE


//Auto Park Sequence
AUTOMATION(311,"C: Auto Park")
    ROUTE_HIDDEN(311)
    CALL(301)
    ROUTE_ACTIVE(311)
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(300) //Release Parked Block dependant on turnout thrown
    IFCLOSED(9126) //Track FD1
        FREE(C_B7)
        CLEAR_STASH(TC1)
        RETURN
    ENDIF
    IFTHROWN(9127) //Track FD2
        FREE(C_B8)
        CLEAR_STASH(TC2)
        RETURN
    ENDIF
    IFTHROWN(9128) //Track FD3
        FREE(C_B9)
        CLEAR_STASH(TC3)
        RETURN
    ENDIF
    IFTHROWN(9129) //Track FD4
        FREE(C_B10)
        CLEAR_STASH(TC4)
        RETURN
    ENDIF
    IFCLOSED(9129) //Track FD5
        FREE(C_B11)
        CLEAR_STASH(TC5)
        RETURN
    ENDIF
DONE


//Auto Park Sequence
SEQUENCE(301)
IFNOT(CD_F8_C1) 
    RESERVE(C_B7)
    CLOSE(9123)
    FWD(30) 
    AT(CD_F8_C1) ESTOP
    FREE(C_B6)
    STASH(TC1)
    RETURN
ENDIF 
IFNOT(CD_F8_C2) 
    RESERVE(C_B8)
    THROW(9123)
    FWD(30) 
    AT(CD_F8_C2) ESTOP
    FREE(C_B6)
    STASH(TC2)
    RETURN
ENDIF 
IFNOT(CD_F8_C3) 
    RESERVE(C_B9)
    THROW(9122)
    FWD(30) 
    AT(CD_F8_C3) ESTOP
    FREE(C_B6)
    STASH(TC3)
    RETURN
ENDIF 
IFNOT(CD_F7_C4) 
    RESERVE(C_B10)
    THROW(9121)
    FWD(30) 
    AT(CD_F7_C4) ESTOP
    FREE(C_B6)
    STASH(TC4)
    RETURN
ENDIF 
IFNOT(CD_F7_C5) 
    RESERVE(C_B11)
    CLOSE(9120)
    FWD(30) 
    AT(CD_F7_C5) ESTOP
    FREE(C_B6)
    STASH(TC5)
    RETURN
ENDIF 
DONE

AUTOMATION(302,"C: Around We Go") //Leave yard 
    RESERVE(C_B1)
    IFTHROWN(9024)
        CLOSE(9024) //close turnouts E -> C rear
    ENDIF
    SPEED(30)
    AT(CD_S9_C2)
FOLLOW(303)

SEQUENCE(303) //Progress to Block2    
    IFRESERVE(C_B2) //Reserve Next block
        SCREEN(5,2,"Block C2 Reserved")
        IFTHROWN(9021)  
            CLOSE(9021) //close turnouts A->D
        ENDIF
    ELSE
        AT(CD_S9_C)
        STOP
        FOLLOW(303)
    ENDIF
    SPEED(40)
    AT(CD_S7_C)
FOLLOW(304)

SEQUENCE(304) //Progress to Block3
    IFRESERVE(C_B3) //Reserve Next block
    SCREEN(5,3,"Block C3 Reserved")
        IFTHROWN(9005)
            CLOSE(9005) // prevent route C->D
        ENDIF
    ELSE
        AT(CD_S6_C)
        STOP
        FOLLOW(304)
    ENDIF
    SPEED(40)
    AT(CD_F4_C)
DONE