/*
* myTrackB.h
* Add in the routes for trackD only
*
* V 0.1.0
* AroundWeGo
*
*/
//Release Block when loco is removed from track
ROUTE(290,"B: Track 1 Clear")
    FREE(D_B7)
DONE
ROUTE(291,"B: Track 2 Clear")
    FREE(D_B8)
DONE
ROUTE(292,"B: Track 3 Clear")
    FREE(D_B9)
DONE
ROUTE(293,"B: Track 4 Clear")
    FREE(D_B10)
DONE
ROUTE(294,"B: Track 5 Clear")
    FREE(D_B11)
DONE

//Set reserves for locos in yard to prevent other locos entering
ROUTE(295,"B: Track 1 Loaded") //Auto park the train in the yard
    RESERVE(D_B7)
DONE
ROUTE(296,"B: Track 2 Loaded") //Auto park the train in the yard
    RESERVE(D_B8)
DONE
ROUTE(297,"B: Track 3 Loaded") //Auto park the train in the yard
    RESERVE(D_B9)
DONE
ROUTE(298,"B: Track 4 Loaded") //Auto park the train in the yard
    RESERVE(D_B10)
DONE
ROUTE(299,"B: Track 5 Loaded") //Auto park the train in the yard
    RESERVE(D_B11)
DONE 

//Manually activate the auto park sequence
AUTOMATION(289,"B: Manual Auto Park")   
    CALL(201)
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(200) //Release Parked Block dependant on turnout thrown
    IFCLOSED(9115) //Track FD1
        FREE(B_B7)
        RETURN
    ENDIF
    IFTHROWN(9116) //Track FD2
        FREE(B_B8)
        RETURN
    ENDIF
    IFTHROWN(9117) //Track FD3
        FREE(B_B9)
        RETURN
    ENDIF
    IFTHROWN(9118) //Track FD4
        FREE(B_B10)
        RETURN
    ENDIF
    IFCLOSED(9118) //Track FD5
        FREE(B_B11)
        RETURN
    ENDIF
DONE

//Auto Park Sequence
AUTOMATION(201,"B: Auto Park")
IFNOT(BD_F2_B1) 
    RESERVE(B_B7)
    CLOSE(9110)
    FWD(20) 
    AT(BD_F2_B1) ESTOP
    FREE(B_B6)
    RETURN
ENDIF 
IFNOT(BD_F2_B2) 
    RESERVE(B_B8)
    THROW(9111)
    FWD(20) 
    AT(BD_F2_B2) ESTOP
    FREE(B_B6)
    RETURN
ENDIF 
IFNOT(BD_F2_B3) 
    RESERVE(B_B9)
    THROW(9112)
    FWD(20) 
    AT(BD_F2_B3) ESTOP
    FREE(B_B6)
    RETURN
ENDIF 
IFNOT(BD_F3_B4) 
    RESERVE(B_B10)
    THROW(9113)
    FWD(20) 
    AT(BD_F3_B4) ESTOP
    FREE(D_B6)
    RETURN
ENDIF 
IFNOT(BD_F3_B5) 
    RESERVE(D_B11)
    CLOSE(9113)
    FWD(20) 
    AT(BD_F3_B5) ESTOP
    FREE(D_B6)
    RETURN
ENDIF 
DONE


// Start of main AUTOMATIONS for track B
AUTOMATION(202, "B: Around We Go") //Leave yard 
    LATCH(AUTO_B)
    RESERVE(B_B1) //Reserve Station block
    IFTHROWN(9001)
        CLOSE(9001) //close turnouts B-A
    ENDIF
    FWD(30) //Move forward Speed 30
    AT(BD_S1_B) //At Block 1
FOLLOW(203)

SEQUENCE(203) //Progress to Block2    
    RESERVE(B_B2) //Reserve Next block
    IFRED(SIG_B1)
        STOP
        FOLLOW(203)
    ENDIF
    IFAMBER(SIG_B1)
        SPEED(30)
    ENDIF
    IFGREEN(SIG_B1)
        SPEED(60)
    ENDIF
    AT(BD_S2_B)
FOLLOW(204)

SEQUENCE(204) //Progress to Block3
    RESERVE(B_B3) //Reserve Next block
    RED(SIG_B1)

    DONE //TEMP ENDING POINT

    