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
DONE
ROUTE(391,"C: Track 2 Clear")
    ROUTE_HIDDEN(391)
    ROUTE_ACTIVE(396)
    FREE(C_B8)
DONE
ROUTE(392,"C: Track 3 Clear")
    ROUTE_HIDDEN(392)
    ROUTE_ACTIVE(397)
    FREE(C_B9)
DONE
ROUTE(393,"C: Track 4 Clear")
    ROUTE_HIDDEN(393)
    ROUTE_ACTIVE(398)
    FREE(C_B10)
DONE
ROUTE(394,"C: Track 5 Clear")
    ROUTE_HIDDEN(394)
    ROUTE_ACTIVE(399)
    FREE(C_B11)
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
AUTOMATION(310,"C: Manual Auto Park")   
    ROUTE_HIDDEN(310)
    CALL(311)
DONE


//Auto Park Sequence
AUTOMATION(311,"C: Auto Park")
    ROUTE_HIDDEN(311)
    CALL(312)
    ROUTE_ACTIVE(311)
DONE

//Auto Park Sequence
SEQUENCE(312)
IFNOT(BD_F8_C1) 
    RESERVE(C_B7)
    CLOSE(9123)
    FWD(30) 
    AT(BD_F8_C1) ESTOP
    FREE(C_B6)
    RETURN
ENDIF 
IFNOT(BD_F8_C2) 
    RESERVE(C_B8)
    THROW(9123)
    FWD(30) 
    AT(BD_F8_C2) ESTOP
    FREE(C_B6)
    RETURN
ENDIF 
IFNOT(BD_F8_C3) 
    RESERVE(C_B9)
    THROW(9122)
    FWD(30) 
    AT(BD_F8_C3) ESTOP
    FREE(C_B6)
    RETURN
ENDIF 
IFNOT(BD_F7_C4) 
    RESERVE(C_B10)
    THROW(9121)
    FWD(30) 
    AT(BD_F7_C4) ESTOP
    FREE(C_B6)
    RETURN
ENDIF 
IFNOT(BD_F7_C5) 
    RESERVE(C_B11)
    CLOSE(9120)
    FWD(30) 
    AT(BD_F7_C5) ESTOP
    FREE(C_B6)
    RETURN
ENDIF 
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(313) //Release Parked Block dependant on turnout thrown
    IFCLOSED(9126) //Track FD1
        FREE(C_B7)
        RETURN
    ENDIF
    IFTHROWN(9127) //Track FD2
        FREE(C_B8)
        RETURN
    ENDIF
    IFTHROWN(9128) //Track FD3
        FREE(C_B9)
        RETURN
    ENDIF
    IFTHROWN(9129) //Track FD4
        FREE(C_B10)
        RETURN
    ENDIF
    IFCLOSED(9129) //Track FD5
        FREE(C_B11)
        RETURN
    ENDIF
DONE




