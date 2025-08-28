/*
* myTrackD.h
* Add in the routes for trackD only
*
* V 0.1.0
* AroundWeGo
*
*/

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
    FWD(10) 
    AT(BD_F2_D1) ESTOP
    FREE(D_B6)
    RETURN
ENDIF 
IFNOT(BD_F2_D2) 
    RESERVE(D_B8)
    THROW(9131)
    FWD(10) 
    AT(BD_F2_D2) ESTOP
    FREE(D_B6)
    RETURN
ENDIF 
IFNOT(BD_F2_D3) 
    RESERVE(D_B9)
    THROW(9132)
    FWD(10) 
    AT(BD_F2_D3) ESTOP
    FREE(D_B6)
    RETURN
ENDIF 
IFNOT(BD_F2_D4) 
    RESERVE(D_B10)
    THROW(9133)
    FWD(10) 
    AT(BD_F2_D4) ESTOP
    FREE(D_B6)
    RETURN
ENDIF 
IFNOT(BD_F2_D5) 
    RESERVE(D_B11)
    CLOSE(9133)
    FWD(10) 
    AT(BD_F2_D5) ESTOP
    FREE(D_B6)
    RETURN
ENDIF 
DONE

AUTOMATION(402, "D: Around We Go") //Leave yard to Station not stopping
    RESERVE(D_B1) //Reserve Station block
    CLOSE(9002) //close turnouts D-C
    FWD(30) //Move forward Speed 30
    AT(BD_S1_D)
    RESERVE(D_B2) //Reserve Next block
    //Ensure route is set
    CLOSE(9005)//ensure route is set
    CLOSE(9008)
    CLOSE(9009)
    CLOSE(9010)
    CALL(400) //Release the Staging Yard Block
    AT(BD_S2_D)
FOLLOW(403)

SEQUENCE(403) //Progress to Block2
    RESERVE(D_B3) //Reserve Next block
    FWD(50) //Increase speed
    AT(BD_S4_D)
    FREE(D_B1)
    AT(BD_S6_D)
FOLLOW(404)

SEQUENCE(404) //Progress to Block3
    RESERVE(D_B4) //Reserve Next block
    FREE(D_B2)
    CLOSE(9021) // prevent route A-D
    AT(BD_S8_D)
FOLLOW(405)

SEQUENCE(405) //Progress to Block4
    RESERVE(D_B5) //Reserve Next block
    CLOSE(9024) // prevent route E-C
    AT(BD_F9_B)
FOLLOW(406)

SEQUENCE(406) //Progress to Block5
    RESERVE(D_B6) //Reserve Next block
    FREE(D_B3)
    AT(BD_F7_D)
FOLLOW(407)

SEQUENCE(407)
    FREE(D_B4)
    AT(BD_F6_D)
FOLLOW(408)

SEQUENCE(408)
    FREE(D_B5)
    CALL(401)
DONE

AUTOMATION(410, "D: Pick'em up") //Leave yard to Station not stopping
    RESERVE(D_B1) //Reserve Station block
    CLOSE(9002) //close turnouts D-C
    FWD(30) //Move forward Speed 30
    AT(BD_S1_D)
    STOP 
    RANDOMDELAY(10000,15000)
    RESERVE(D_B2) //Reserve Next block
    CALL(411)
    //Ensure route is set
    CLOSE(9005)//ensure route is set
    CLOSE(9008)
    CLOSE(9009)
    CLOSE(9010)
    FWD(20)
    CALL(400) //Release the Staging Yard Block
    AT(BD_S2_D)
FOLLOW(403)

SEQUENCE(411)
    FON(4)
    DELAY(300)
    FOFF(4)
    DELAY(300)
    RETURN 
DONE

//ALMOST THERE
