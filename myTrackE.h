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
AUTOMATION(589,"B: Manual Auto Park")   
    CALL(501)
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(500) //Release Parked Block dependant on turnout thrown
    IFCLOSED(9115) //Track FD1
        FREE(E_B7)
        RETURN
    ENDIF
    IFTHROWN(9116) //Track FD2
        FREE(E_B8)
        RETURN
    ENDIF
    IFTHROWN(9117) //Track FD3
        FREE(E_B9)
        RETURN
    ENDIF
    IFTHROWN(9118) //Track FD4
        FREE(E_B10)
        RETURN
    ENDIF
    IFCLOSED(9118) //Track FD5
        FREE(E_B11)
        RETURN
    ENDIF
DONE

//Auto Park Sequence
AUTOMATION(501,"B: Auto Park")
IFNOT(BD_F8_E1) 
    RESERVE(E_B7)
    CLOSE(9110)
    FWD(50) 
    AT(BD_F8_E1) ESTOP
    FREE(E_B6)
    RETURN
ENDIF 
IFNOT(BD_F8_E2) 
    RESERVE(E_B8)
    THROW(9111)
    FWD(50) 
    AT(BD_F8_E2) ESTOP
    FREE(E_B6)
    RETURN
ENDIF 
IFNOT(BD_F8_E3) 
    RESERVE(E_B9)
    THROW(9112)
    FWD(50) 
    AT(BD_F8_E3) ESTOP
    FREE(E_B6)
    RETURN
ENDIF 
IFNOT(BD_F7_E4) 
    RESERVE(E_B10)
    THROW(9113)
    FWD(50) 
    AT(BD_F7_E4) ESTOP
    FREE(E_B6)
    RETURN
ENDIF 
IFNOT(BD_F7_E5) 
    RESERVE(E_B11)
    CLOSE(9113)
    FWD(50) 
    AT(BD_F7_E5) ESTOP
    FREE(E_B6)
    RETURN
ENDIF 
DONE


// Start of main AUTOMATIONS for track B
AUTOMATION(502, "E: Around We Go") //Leave yard 
   ROUTE_DISABLED(502)
    RESERVE(E_B1) //Reserve Station block
    SPEED(50)
    IFTHROWN(9001)
        CLOSE(9001) //close turnouts B-A
    ENDIF
//    FWD(30) //Move forward Speed 30
    AT(BD_S1_E) //At Block 1
FOLLOW(503)

SEQUENCE(503) //Progress to Block2    
ROUTE_ACTIVE(502 )
    RESERVE(E_B2) //Reserve Next block
    IFTHROWN(9004)
        CLOSE(9004) //close turnouts A->B
    ENDIF
    RESERVE(E_B3) //Reserve Next block
    IFTHROWN(9007)
        CLOSE(9007) //close turnouts B->A   
    ENDIF
    IFTHROWN(9008)
        CLOSE(9008) //close turnouts D->B
    ENDIF
    IFTHROWN(9009)
        CLOSE(9009) //close turnouts D->A
    ENDIF
    IFTHROWN(9010)
        CLOSE(9010) //close turnouts D->B
    ENDIF
    IFRED(SIG_E3)
        STOP
        FOLLOW(503)
    ENDIF
    IFAMBER(SIG_E3)
        SPEED(50)
    ENDIF
//    IFGREEN(SIG_E1)
//        SPEED(60)
//    ENDIF
    CALL(500)
    AT(BD_S2_E)
FOLLOW(504)

SEQUENCE(504) //Progress to Block3
    RED(SIG_E3)
    AT(BD_S4_E)
    IFAMBER(SIG_E2)
        SPEED(50) 
    ENDIF
    FREE(E_B1) //Free previous block
    AT(BD_S5_E)
FOLLOW(505)

SEQUENCE(505)
    RED(SIG_E2)
    AT(BD_S6_E) 
FOLLOW(506)

SEQUENCE(506) //Progress to Block4
    IFRED(SIG_E3)
        AT(BD_S7_E)
        STOP
        FOLLOW(506)
    ENDIF
    IFAMBER(SIG_E3)
        SPEED(50)
    ENDIF
//    IFGREEN(SIG_E3)
//        SPEED(60)
//    ENDIF 
AT(BD_S7_E)  
    RESERVE(E_B4) //Reserve Next block
    AMBER(SIG_E1)
    FREE(E_B2)  
    IFTHROWN(9020)
        CLOSE(9020) // prevent route A-B
    ENDIF
    IFTHROWN(9021)
        CLOSE(9021) // prevent route A-D
    ENDIF
    AT(BD_S8_E)
FOLLOW(507)

SEQUENCE(507) //Progress to Block5
    RESERVE(E_B5) //Reserve Next block  
    RED(SIG_E3)
    IFTHROWN(9023)
        CLOSE(9023) // prevent route A->B
    ENDIF 
FOLLOW(508)


SEQUENCE(508) //Progress to Block6
    IFRED(SIG_E4)
        AT(BD_S9_E)
        STOP
        FOLLOW(508)
    ENDIF
    IFAMBER(SIG_E4)
        SPEED(50)
    ENDIF
//    IFGREEN(SIG_E4)
//        SPEED(60)
//    ENDIF
    AT(BD_F7_E)
FOLLOW(509) 

SEQUENCE(509) //Progress to Block7
    RESERVE(E_B6) //Reserve Next block  
//    SPEED(30)
    RED(SIG_E4)
    AMBER(SIG_E2)   
    FREE(E_B3)
    AT(BD_F7_E)
FOLLOW(510)

SEQUENCE(510)
    AMBER(SIG_E4)   
    AMBER(SIG_E3)
    GREEN(SIG_E2)
    FREE(E_B4)
    AT(BD_F6_E)
FOLLOW(511)

SEQUENCE(511)
    GREEN(SIG_E4)   
    GREEN(SIG_E3)
    FREE(E_B5)
    CALL(501)
    FOFF(0)
DONE

    