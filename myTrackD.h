/*
* myTrackD.h
* Add in the routes for trackD only
*
* V 0.1.0
* AroundWeGo
*
*/
//Release Block when loco is removed from track
ROUTE(490,"D: Track 1 Clear")
    FREE(D_B7)
DONE
ROUTE(491,"D: Track 2 Clear")
    FREE(D_B8)
DONE
ROUTE(492,"D: Track 3 Clear")
    FREE(D_B9)
DONE
ROUTE(493,"D: Track 4 Clear")
    FREE(D_B10)
DONE
ROUTE(494,"D: Track 5 Clear")
    FREE(D_B11)
DONE

//Set reserves for locos in yard to prevent other locos entering
ROUTE(495,"D: Track 1 Loaded") //Auto park the train in the yard
    RESERVE(D_B7)
DONE
ROUTE(496,"D: Track 2 Loaded") //Auto park the train in the yard
    RESERVE(D_B8)
DONE
ROUTE(497,"D: Track 3 Loaded") //Auto park the train in the yard
    RESERVE(D_B9)
DONE
ROUTE(498,"D: Track 4 Loaded") //Auto park the train in the yard
    RESERVE(D_B10)
DONE
ROUTE(499,"D: Track 5 Loaded") //Auto park the train in the yard
    RESERVE(D_B11)
DONE 

//Manually activate the auto park sequence
AUTOMATION(489,"D: Manual Auto Park")   
    CALL(401)
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(400) //Release Parked Block dependant on turnout thrown
    IFCLOSED(9135) //Track FD1
        FREE(D_B7)
        RETURN
    ENDIF
    IFTHROWN(9136) //Track FD2
        FREE(D_B8)
        RETURN
    ENDIF
    IFTHROWN(9137) //Track FD3
        FREE(D_B9)
        RETURN
    ENDIF
    IFTHROWN(9138) //Track FD4
        FREE(D_B10)
        RETURN
    ENDIF
    IFCLOSED(9139) //Track FD5
        FREE(D_B11)
        RETURN
    ENDIF
DONE

//Auto Park Sequence
SEQUENCE(401)
IFNOT(BD_F2_D1) 
    RESERVE(D_B7)
    CLOSE(9130)
    FWD(20) 
    AT(BD_F2_D1) ESTOP
    FREE(D_B6)
    RETURN
ENDIF 
IFNOT(BD_F2_D2) 
    RESERVE(D_B8)
    THROW(9131)
    FWD(20) 
    AT(BD_F2_D2) ESTOP
    FREE(D_B6)
    RETURN
ENDIF 
IFNOT(BD_F2_D3) 
    RESERVE(D_B9)
    THROW(9132)
    FWD(20) 
    AT(BD_F2_D3) ESTOP
    FREE(D_B6)
    RETURN
ENDIF 
IFNOT(BD_F2_D4) 
    RESERVE(D_B10)
    THROW(9133)
    FWD(20) 
    AT(BD_F2_D4) ESTOP
    FREE(D_B6)
    RETURN
ENDIF 
IFNOT(BD_F2_D5) 
    RESERVE(D_B11)
    CLOSE(9133)
    FWD(20) 
    AT(BD_F2_D5) ESTOP
    FREE(D_B6)
    RETURN
ENDIF 
DONE

AUTOMATION(402, "D: Around We Go") //Leave yard to Station not stopping
    LATCH(AUTO_D)
    RESERVE(D_B1) //Reserve Station block
    IFTHROWN(9002)
        CLOSE(9002) //close turnouts D-C
    ENDIF
    FWD(30) //Move forward Speed 30
    AT(BD_S1_D)
FOLLOW(403)

SEQUENCE(403)
        IFRED(SIG_D1)
        STOP
        FOLLOW(403)
    ENDIF   
FOLLOW(404)

SEQUENCE(404)   
    RESERVE(D_B2) //Reserve Next block
    //Ensure route is set
    IFTHROWN(9005)
        CLOSE(9005)//ensure route is set
    ENDIF
    IFTHROWN(9008)
        CLOSE(9008)
    ENDIF
    IFTHROWN(9009)
        CLOSE(9009)
    ENDIF
    IFTHROWN(9010)
        CLOSE(9010)
    ENDIF
    SPEED(50) //Maybe too fast
    CALL(400) //Release the Staging Yard Block
    AT(BD_S2_D)
FOLLOW(405)

SEQUENCE(405) //Progress to Block2
    RESERVE(D_B3) //Reserve Next block
    RED(SIG_D1)
    FWD(50) //Increase speed
    AT(BD_S4_D)
    FREE(D_B1)
    AT(BD_S5_D)
FOLLOW(406)

SEQUENCE(406)
    RED(SIG_D2)
    AT(BD_S6_D) 
FOLLOW(407)

SEQUENCE(407) //Progress to Block3
 IFRED(SIG_D3)
    SPEED(20)
    AT(BD_S7_D)
    STOP
    FOLLOW(407)
 ENDIF
 IFAMBER(SIG_D3)
    SPEED(30)
ELSE
    SPEED(50)
ENDIF
    RESERVE(D_B4) //Reserve Next block
    AMBER(SIG_D1)
    FREE(D_B2)
    IFTHROWN(9021)
        CLOSE(9021) // prevent route A-D
    ENDIF
    AT(BD_S8_D)
FOLLOW(408)

SEQUENCE(408) //Progress to Block4
    RESERVE(D_B5) //Reserve Next block
    RED(SIG_D3)
    IFTHROWN(9024)
        CLOSE(9024) // prevent route E-C
    ENDIF
FOLLOW(409)

SEQUENCE(409)
    IFRED(SIG_D4)
        AT(BD_S9_D)
        STOP
        FOLLOW(409)
    ENDIF
    IFAMBER(SIG_D4)
        SPEED(30)
    ENDIF
    AT(BD_F9_D)
FOLLOW(410)

SEQUENCE(410) //Progress to Block5
    RESERVE(D_B6) //Reserve Next block
    RED(SIG_D4)
    GREEN(SIG_D1)
    AMBER(SIG_D2)
    FREE(D_B3)
    AT(BD_F7_D)
FOLLOW(411)

SEQUENCE(411)
    AMBER(SIG_D4)   
    AMBER(SIG_D3)
    GREEN(SIG_D2)
    FREE(D_B4)
    AT(BD_F6_D)
FOLLOW(412)

SEQUENCE(412)
    GREEN(SIG_D4)
    GREEN(SIG_D3)    
    FREE(D_B5)
    CALL(401)
    FOFF(0)
    UNLATCH(AUTO_D)
DONE

AUTOMATION(414, "D: Pick'em up") //Leave yard to Station and wait
    RESERVE(D_B1) //Reserve Station block
    IFTHROWN(9002)
        CLOSE(9002) //close turnouts D-C
    ENDIF
    FWD(30) //Move forward Speed 30
    AT(BD_S1_D)
    STOP 
    DELAYRANDOM(10000,15000)
    CALL(415)
FOLLOW(403)

SEQUENCE(415)
    FON(4)
    DELAY(300)
    FOFF(4)
    DELAY(300)
    RETURN 
DONE

//ALMOST THERE
