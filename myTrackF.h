/*
* track F basic route definitions
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
            DELAY(1000)
        ENDIF
    FWD(30)
    AT(BD_S9_F) 
FOLLOW(202)

//Proceed to holgate access
SEQUENCE(202)
    RESERVE(F_B2) //from bridge to holgate access
    IFTHROWN(9022) //Close E-> F turnout
        CLOSE(9022)
    ENDIF
    IFTHROWN(DGS_T3_A__HS_T6_A) //Close turnout Holgate access
        CLOSE(DGS_T3_A__HS_T6_A)
    ENDIF
    FREE(F_B6) // Free last storage block    
    AT(BD_S5_F) // current detector board 5 
FOLLOW(203)

//Proceed to board 4 gantry
SEQUENCE(203)
    RESERVE(F_B3)
    FREE(F_B1) 
    SPEED(50)
    IFAMBER(SIG_F2)
        SPEED(40) // reduce speed to 40
    ENDIF
    AT(BD_S3_F) // current detector board 4 before board 4 gantry
FOLLOW(204)

//Proceed to board 4 gantry
SEQUENCE(204)
    RESERVE(F_B4) //
    FREE(F_B2) // Free bridge block
    IFTHROWN(9028)
        CLOSE(9028)
    ENDIF
    AT(SNS_UGS_B3) // IR detector board 3 rear
FOLLOW(205)

//Proceed to board 4-5 storage
SEQUENCE(205)    
    RESERVE(F_B5) //Reserve F B9
    FREE(F_B3) // Free bridge block
    SPEED(20)
    IFTHROWN(9027)
        CLOSE(9027)
    ENDIF
    AT(SNS_UGS_B5) // IR detector board 5 rear
FOLLOW(206)

//Proceed to board 5-8
SEQUENCE(206)
    RESERVE(F_B6) //Reserve F B8-6
    FREE(F_B4)
    SPEED(20)
    AT(SNS_UGS_B8) // IR detector board 8 rear MAYBE MOVED TO BOARD 9
    STOP    
 DONE