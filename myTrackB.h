/*
* myTrackB.h
* Add in the routes for trackD only
*
* V 0.1.0
* AroundWeGo
*
*/


//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(200) //Release Parked Block dependant on turnout thrown
    IFCLOSED(9135) //Track FD1
        FREE(B_B7)
        RETURN
    ENDIF
    IFTHROWN(9136) //Track FD2
        FREE(B_B8)
        RETURN
    ENDIF
    IFTHROWN(9137) //Track FD3
        FREE(B_B9)
        RETURN
    ENDIF
    IFTHROWN(9138) //Track FD4
        FREE(B_B10)
        RETURN
    ENDIF
    IFCLOSED(9139) //Track FD5
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