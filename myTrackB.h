/*
* myTrackB.h
* Add in the routes for trackD only
*
* V 0.1.0
*           290 - 294 Free yard tracks
*           295 - 299 Reserve yard tracks
*           202 Around We Go
*           289 Auto Park
*
*/
//Release Block when loco is removed from track
ROUTE(290,"B: Track 1 Clear")
    ROUTE_HIDDEN(290)
    ROUTE_ACTIVE(295)
    FREE(B_B7)
DONE
ROUTE(291,"B: Track 2 Clear")
    ROUTE_HIDDEN(291)
    ROUTE_ACTIVE(296)
    FREE(B_B8)
DONE
ROUTE(292,"B: Track 3 Clear")
    ROUTE_HIDDEN(292)
    ROUTE_ACTIVE(297)
    FREE(B_B9)
DONE
ROUTE(293,"B: Track 4 Clear")
    ROUTE_HIDDEN(293)
    ROUTE_ACTIVE(298)
    FREE(B_B10)
DONE
ROUTE(294,"B: Track 5 Clear")
    ROUTE_HIDDEN(294)
    ROUTE_ACTIVE(299)
    FREE(B_B11)
DONE

//Set reserves for locos in yard to prevent other locos entering
ROUTE(295,"B: Track 1 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(295)
    ROUTE_ACTIVE(290)
    RESERVE(B_B7)
DONE
ROUTE(296,"B: Track 2 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(296)
    ROUTE_ACTIVE(291)
    RESERVE(B_B8)
DONE
ROUTE(297,"B: Track 3 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(297)
    ROUTE_ACTIVE(292)
    RESERVE(B_B9)
DONE
ROUTE(298,"B: Track 4 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(298)
    ROUTE_ACTIVE(293)
    RESERVE(B_B10)
DONE
ROUTE(299,"B: Track 5 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(299)
    ROUTE_ACTIVE(294)
    RESERVE(B_B11)
DONE 

//Manually activate the auto park sequence
AUTOMATION(289,"B: Auto Park")  
    ROUTE_HIDDEN(289) 
    CALL(201)
    ROUTE_ACTIVE(289)   
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
SEQUENCE(201)
IFNOT(CD_F2_B1) 
    RESERVE(B_B7)
    CLOSE(9110)
    FWD(20) 
    AT(CD_F2_B1) ESTOP
    FREE(B_B6)
    RETURN
ENDIF 
IFNOT(CD_F2_B2) 
    RESERVE(B_B8)
    THROW(9111)
    FWD(20) 
    AT(CD_F2_B2) ESTOP
    FREE(B_B6)
    RETURN
ENDIF 
IFNOT(CD_F2_B3) 
    RESERVE(B_B9)
    THROW(9112)
    FWD(20) 
    AT(CD_F2_B3) ESTOP
    FREE(B_B6)
    RETURN
ENDIF 
IFNOT(CD_F3_B4) 
    RESERVE(B_B10)
    THROW(9113)
    FWD(20) 
    AT(CD_F3_B4) ESTOP
    FREE(B_B6)
    RETURN
ENDIF 
IFNOT(CD_F3_B5) 
    RESERVE(B_B11)
    CLOSE(9113)
    FWD(20) 
    AT(CD_F3_B5) ESTOP
    FREE(B_B6)
    RETURN
ENDIF 
DONE


// Start of main AUTOMATIONS for track B
AUTOMATION(202, "B: Around We Go") //Leave yard 
   ROUTE_DISABLED(202)
    RESERVE(B_B1) //Reserve Station block
    SPEED(20)
    IFTHROWN(9001)
        CLOSE(9001) //close turnouts A - B
    ENDIF
    IFTHROWN(9026)
        CLOSE(9026) //close turnouts B - A
    ENDIF   
    AT(CD_S1_B) //At Block 1
FOLLOW(203)

SEQUENCE(203) //Progress to Block2    
    ROUTE_ACTIVE(202 )
    CALL(200)
    AT(CD_S1_B1)
FOLLOW(204)

SEQUENCE(204) //Progress to Block2
    IFRESERVE(B_B2) //Reserve Next block
        PRINT("Block B2 Reserved")
        IFTHROWN(9004)
            CLOSE(9004) //close turnouts A->B
        ENDIF
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
    ELSE
        STOP
        FOLLOW(204)
    ENDIF
    AT(CD_S2_B)
FOLLOW(205)

SEQUENCE(205) //Progress to Block3
    RESERVE(B_B3) //Reserve Next block
    AT(CD_S4_B)
    FREE(B_B1) //Free previous block
    AT(CD_S5_B)
FOLLOW(206)

SEQUENCE(206)
    FREE(B_B2) //Free previous block
    AT(CD_S6_B) 
FOLLOW(207)

SEQUENCE(207) //Progress to Block4
    IFRESERVE(B_B4) //Reserve Next block
        IFTHROWN(9020)
            CLOSE(9020) // prevent route A-B
            CLOSE(9021) // prevent route A-D
        ENDIF
    ELSE
        AT(CD_S7_B)
        STOP
        FOLLOW(207)
    ENDIF
    AT(CD_S9_B)  
FOLLOW(208)

SEQUENCE(208) //Progress to Block5
    IFRESERVE(B_B5) //Reserve Next block
        FREE(B_B3)
        IFTHROWN(9023)
            CLOSE(9023) // prevent route A->B   
        ENDIF
    ELSE
        STOP
        FOLLOW(208)
    ENDIF
    AT(CD_F7_B)
FOLLOW(209)

SEQUENCE(209) //Progress to Block6 
    RESERVE(B_B6) //Reserve Next block  
    FREE(B_B4) //Free previous block
    AT(CD_F6_B)
FOLLOW(210)

SEQUENCE(210)
    FREE(B_B5)
    CALL(201)
    FOFF(0)
DONE


AUTOMATION(211,"B: Station Stop") //Station Stop
    ROUTE_DISABLED(211)
    IFRESERVE(A_B1)
        RESERVE(B_B1) //Reserve Station block  
        IFTHROWN(9001)
            CLOSE(9001) //close turnouts A - B
        ENDIF
        IFCLOSED(9026)
            THROW(9026) //close turnouts B - A
        ENDIF 
        IFCLOSED(UGS_T2_H) //Close Header
            THROW(UGS_T2_H) 
        ENDIF  
        SPEED(20)
    ELSE
        FOLLOW(211) 
    ENDIF
    AT(CD_S1_A)
FOLLOW(212)

SEQUENCE(212) //Stop at station
    STOP
    CALL(200)
    DELAYRANDOM(10000,15000)
FOLLOW(213)

SEQUENCE(213) //Release turnout block and set turnouts for return to A
    IFRESERVE(B_B2)
        IFRESERVE(A_B2) //reserve Block 2
            IFCLOSED(9004)
                THROW(9004) //close turnouts A->B
            ENDIF
        ENDIF
        IFTHROWN(9007)
            CLOSE(9007) //close turnouts B->A
        ENDIF
    ELSE
        STOP
        FOLLOW(213)
    ENDIF
    AT(CD_S2_A)
FOLLOW(214)

SEQUENCE(214)
    FREE(A_B1)
    IFTHROWN(9026)
        CLOSE(9026) //close turnouts B->A 
    ENDIF
FOLLOW(205)
    

