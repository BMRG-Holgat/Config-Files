/*
* track F basic route definitions
*
* V 0.0.1
*           600 Roundy
*           601 Holgate
*/



//Leave staging yard and proceed to bridge
//AUTOSTART SEQUENCE(201)
// ALLOW 2 TRAINS TO CIRCULATE
 //Leave staging yard and proceed to bridge
  

//Leave staging yard and proceed to bridge 
AUTOMATION(600,"F: Roundy" )
    ROUTE_HIDDEN(600)
    RESERVE(F_B1) //exit storage to bridge
        IFTHROWN(9025)
            CLOSE(9025)
        ENDIF
    FWD(30)
    AT(CD_S9_F)
FOLLOW(602)

AUTOMATION(601,"F: Holgate" )
    ROUTE_HIDDEN(601)
    SET(61)
    FOLLOW(600)
DONE 

//Proceed to holgate access
SEQUENCE(602)
    STOPRES(F_B2,202) //exit storage to bridge
    IFTHROWN(9022) //Close E-> F turnout
        CLOSE(9022)
    ENDIF
    FREE(F_B6) // Free last storage block    
    AT(CD_S9_F1) // current detector board 9 before Holgate
FOLLOW(603)

//Proceed to board 4 gantry
SEQUENCE(603)
IF(61) //If Holgate access route set
    THROW(DGS_T3_A__HS_T6_A)
    CALL(701)
    ROUTE_ACTIVE(601)
    RESET(61)
    IFTHROWN(9031)
        CLOSE(9031)
        FREE(F_B1)
        FREE(F_B2)
    ENDIF
    DONE
ENDIF
    IFTHROWN(DGS_T3_A__HS_T6_A) //Close turnout Holgate access
        CLOSE(DGS_T3_A__HS_T6_A)
    ENDIF
    IFAMBER(SIG_F2)
        SPEED(30) // reduce speed to 40
    ENDIF
    AT(CD_S5_F) // current detector board 5 before board 4 gantry
FOLLOW(604)

//Proceed to board 4 gantry
SEQUENCE(604)
STOPRES(F_B3,604) //Proceed to board 4 gantry
    FREE(F_B1) // Free bridge block
    IFTHROWN(9028)
        CLOSE(9028)
    ENDIF
    AT(CD_S3_F) // current detector board 3
FOLLOW(205)

//Proceed to board S2-F2 storage
SEQUENCE(05)    
    RESERVE(F_B4) //Reserve F B4
    FREE(F_B2) // Free bridge approach block
    IFTHROWN(9027)
        CLOSE(9027)
    ENDIF
    AT(CD_F2_F) // current detector board 2 rear
FOLLOW(606)

//Proceed to board 5-8
SEQUENCE(606)
    RESERVE(F_B5) //Reserve F B8-6
    FREE(F_B3)
    SPEED(20)
    AT(CD_F5_F) // current detector board 5
 FOLLOW(207)

//Proceed to board 5-8
SEQUENCE(607)    
    RESERVE(F_B6) //Reserve F B8-6
    SPEED(20)
    FREE(F_B4)
    AT(CD_F8_F) // current detector board 8
    STOP 
DONE

