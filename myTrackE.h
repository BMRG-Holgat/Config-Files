/*
* myTrackE.h
* Add in the routes for trackD only
*
* V 0.1.0
*           590 - 594 Free yard tracks
*           595 - 599 Reserve yard tracks
*           502 Around We Go
*           589 Auto Park
*
*/
//Release Block when loco is removed from track
ROUTE(590,"E: Track 1 Clear")
    ROUTE_HIDDEN(590)
    ROUTE_ACTIVE(595)
    FREE(E_B7)
DONE
ROUTE(591,"E: Track 2 Clear")
    ROUTE_HIDDEN(591)
    ROUTE_ACTIVE(596)
    FREE(E_B8)
DONE
ROUTE(592,"E: Track 3 Clear")
    ROUTE_HIDDEN(592)
    ROUTE_ACTIVE(597)
    FREE(E_B9)
DONE
ROUTE(593,"E: Track 4 Clear")
    ROUTE_HIDDEN(593)
    ROUTE_ACTIVE(598)
    FREE(E_B10)
DONE
ROUTE(594,"E: Track 5 Clear")
    ROUTE_HIDDEN(594)
    ROUTE_ACTIVE(599)
    FREE(E_B11)
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
AUTOMATION(510,"E: Manual Auto Park")   
    ROUTE_HIDDEN(510)
    CALL(511)
DONE


//Auto Park Sequence
AUTOMATION(511,"E: Auto Park")
    ROUTE_HIDDEN(511)
    CALL(512)
    ROUTE_ACTIVE(511)
DONE

//Auto Park Sequence
SEQUENCE(512)
IFNOT(CD_F8_E1) 
    RESERVE(E_B7)
    CLOSE(9141)
    FWD(50) 
    AT(CD_F8_E1) ESTOP
    FREE(E_B6)
    RETURN
ENDIF 
IFNOT(CD_F8_E2) 
    RESERVE(E_B8)
    THROW(9141)
    FWD(50) 
    AT(CD_F8_E2) ESTOP
    FREE(E_B6)
    RETURN
ENDIF 
IFNOT(CD_F8_E3) 
    RESERVE(E_B9)
    THROW(9142)
    FWD(50) 
    AT(CD_F8_E3) ESTOP
    FREE(E_B6)
    RETURN
ENDIF 
IFNOT(CD_F7_E4) 
    RESERVE(E_B10)
    THROW(9143)
    FWD(50) 
    AT(CD_F7_E4) ESTOP
    FREE(E_B6)
    RETURN
ENDIF 
IFNOT(CD_F7_E5) 
    RESERVE(E_B11)
    CLOSE(9144)
    FWD(50) 
    AT(CD_F7_E5) ESTOP
    FREE(E_B6)
    RETURN
ENDIF 
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(513) //Release Parked Block dependant on turnout thrown
    IFCLOSED(9145) //Track FD1
        FREE(E_B7)
        RETURN
    ENDIF
    IFTHROWN(9146) //Track FD2
        FREE(E_B8)
        RETURN
    ENDIF
    IFTHROWN(9147) //Track FD3
        FREE(E_B9)
        RETURN
    ENDIF
    IFTHROWN(9148) //Track FD4
        FREE(E_B10)
        RETURN
    ENDIF
    IFCLOSED(9148) //Track FD5
        FREE(E_B11)
        RETURN
    ENDIF
DONE




