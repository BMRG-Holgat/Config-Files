/*
* myTrackD.h
* Add in the routes for trackD only
*
* V 0.2.0
*           490 - 494 Free yard tracks
*           495 - 499 Reserve yard tracks
*           416 Change to Track B
*
* V 0.1.0
*           402 AroundWeGo
*           414 Pick'em up
*           489 Auto Park
*
*/
SEQUENCE(450) //Disable routes
 /*  ROUTE_DISABLED(202)
   ROUTE_DISABLED(1202)
   ROUTE_DISABLED(1211)
   ROUTE_DISABLED(1222)
   ROUTE_DISABLED(1223)
   ROUTE_DISABLED(1224)
   ROUTE_DISABLED(1225)
*/
   RETURN
DONE

SEQUENCE(451) //Enable routes
/*
    ROUTE_ACTIVE(202)
    ROUTE_ACTIVE(211)
    ROUTE_ACTIVE(1202)
    ROUTE_ACTIVE(1211)
    ROUTE_ACTIVE(1222)
    ROUTE_ACTIVE(1223)
    ROUTE_ACTIVE(1224)
    ROUTE_ACTIVE(1225)
*/
RETURN
DONE


//Release Block when loco is removed from track
ROUTE(490,"D: Track 1 Clear")
    ROUTE_HIDDEN(490)
    ROUTE_ACTIVE(495)
    FREE(D_B7)
DONE
ROUTE(491,"D: Track 2 Clear")
    ROUTE_HIDDEN(491)
    ROUTE_ACTIVE(496)
    FREE(D_B8)
DONE
ROUTE(492,"D: Track 3 Clear")
    ROUTE_HIDDEN(492)
    ROUTE_ACTIVE(497)
    FREE(D_B9)
DONE
ROUTE(493,"D: Track 4 Clear")
    ROUTE_HIDDEN(493)
    ROUTE_ACTIVE(498)
    FREE(D_B10)
DONE
ROUTE(494,"D: Track 5 Clear")
    ROUTE_HIDDEN(494)
    ROUTE_ACTIVE(499)
    FREE(D_B11)
DONE

//Set reserves for locos in yard to prevent other locos entering
ROUTE(495,"D: Track 1 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(495)
    ROUTE_ACTIVE(490)
    RESERVE(D_B7)
DONE
ROUTE(496,"D: Track 2 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(496)
    ROUTE_ACTIVE(491)
    RESERVE(D_B8)
DONE
ROUTE(497,"D: Track 3 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(497)
    ROUTE_ACTIVE(492)
    RESERVE(D_B9)
DONE
ROUTE(498,"D: Track 4 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(498)
    ROUTE_ACTIVE(493)
    RESERVE(D_B10)
DONE
ROUTE(499,"D: Track 5 Loaded") //Auto park the train in the yard
    ROUTE_HIDDEN(499)
    ROUTE_ACTIVE(494)
    RESERVE(D_B11)
DONE 

//Manually activate the auto park sequence
AUTOMATION(489,"D: Manual Auto Park") 
    ROUTE_HIDDEN(489)
    CALL(401)
    ROUTE_ACTIVE(489)
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(400) //Release Parked Block dependant on turnout thrown
    IFCLOSED(9135) //Track FD1
        FREE(D_B7)
        SCREEN(2,1,"")
        CLEAR_STASH(TD1)
        RETURN
    ENDIF
    IFTHROWN(9136) //Track FD2
        FREE(D_B8)
        SCREEN(2,2,"")
        CLEAR_STASH(TD2)
        RETURN
    ENDIF
    IFTHROWN(9137) //Track FD3
        FREE(D_B9)
        SCREEN(2,3,"")
        CLEAR_STASH(TD3)
        RETURN
    ENDIF
    IFTHROWN(9138) //Track FD4
        FREE(D_B10)
        SCREEN(2,4,"")
        CLEAR_STASH(TD4)
        RETURN
    ENDIF
    IFCLOSED(9138) //Track FD5
        FREE(D_B11)
        SCREEN(2,5,"")
        CLEAR_STASH(TB5)
        RETURN
    ENDIF
DONE

//Auto Park Sequence
SEQUENCE(401)
IFNOT(CD_F2_D1) 
    RESERVE(D_B7)
    SCREEN(2,1,"Block D7 Reserved")
    CLOSE(9130)
    FWD(20) 
    AT(CD_F2_D1) ESTOP
    FREE(D_B6)
    SCREEN(4,6,"")
    RETURN
ENDIF 
IFNOT(CD_F2_D2) 
    RESERVE(D_B8)
    SCREEN(2,2,"Block D8 Reserved")
    THROW(9131)
    FWD(20) 
    AT(CD_F2_D2) ESTOP
    FREE(D_B6)
    SCREEN(4,6,"")
    RETURN
ENDIF 
IFNOT(CD_F2_D3) 
    RESERVE(D_B9)
    SCREEN(2,3,"Block D9 Reserved")
    THROW(9132)
    FWD(20) 
    AT(CD_F2_D3) ESTOP
    FREE(D_B6)
    SCREEN(4,6,"")
    RETURN
ENDIF 
IFNOT(CD_F2_D4) 
    RESERVE(D_B10)
    SCREEN(2,4,"Block D10 Reserved")
    THROW(9133)
    FWD(20) 
    AT(CD_F2_D4) ESTOP
    FREE(D_B6)
    SCREEN(4,6,"")
    RETURN
ENDIF 
IFNOT(CD_F2_D5) 
    RESERVE(D_B11)
    SCREEN(2,5,"Block D11 Reserved")
    CLOSE(9133)
    FWD(20) 
    AT(CD_F2_D5) ESTOP
    FREE(D_B6)
    SCREEN(4,6,"")
    RETURN
ENDIF 
DONE

AUTOMATION(402, "D: Around We Go Manual") //Leave yard to Station not stopping
    ROUTE_HIDDEN(402)
    RESERVE(D_B1) //Reserve Station block
    IFTHROWN(9002)
        CLOSE(9002) //close turnouts D-C
    ENDIF
    FWD(20) //Move forward Speed 30
    AT(CD_S1_D)
FOLLOW(403)

SEQUENCE(403)
    ROUTE_ACTIVE(402)
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
//    SPEED(50) //Maybe too fast
    CALL(400) //Release the Staging Yard Block
    AT(CD_S2_D)
FOLLOW(405)

SEQUENCE(405) //Progress to Block2
    RESERVE(D_B3) //Reserve Next block
    IFAMBER(SIG_B2) 
        SPEED(10)
    ENDIF 
    RED(SIG_D1)
//    FWD(50) //Increase speed
    AT(CD_S4_D)
    FREE(D_B1)
    AT(CD_S5_D)
FOLLOW(406)

SEQUENCE(406)
    RED(SIG_D2)
    AT(CD_S6_D) 
FOLLOW(407)

SEQUENCE(407) //Progress to Block3
 IFRED(SIG_D3)
//    SPEED(20)
    AT(CD_S7_D)
    STOP
    FOLLOW(407)
 ENDIF
 IFAMBER(SIG_D3)
    SPEED(10)
ENDIF
    RESERVE(D_B4) //Reserve Next block
    AMBER(SIG_D1)
    FREE(D_B2)
    IFTHROWN(9021)
        CLOSE(9021) // prevent route A-D
    ENDIF
    AT(CD_S8_D)
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
        AT(CD_S9_D)
        STOP
        FOLLOW(409)
    ENDIF
    IFAMBER(SIG_D4)
        SPEED(10)
    ENDIF
    AT(CD_F9_D)
FOLLOW(410)

SEQUENCE(410) //Progress to Block5
    RESERVE(D_B6) //Reserve Next block
    RED(SIG_D4)
    GREEN(SIG_D1)
    AMBER(SIG_D2)
    FREE(D_B3)
    AT(CD_F7_D)
FOLLOW(411)

SEQUENCE(411)
    AMBER(SIG_D4)   
    AMBER(SIG_D3)
    GREEN(SIG_D2)
    FREE(D_B4)
    FREE(D_B5)
    AT(CD_F6_D)
FOLLOW(412)

SEQUENCE(412)
    GREEN(SIG_D4)
    GREEN(SIG_D3)    
//    FREE(D_B5)
    CALL(401)
    FOFF(0)
   
DONE

AUTOMATION(414, "D: Station Stop Manual") //Leave yard to Station and wait
    RESERVE(D_B1) //Reserve Station block
    IFTHROWN(9002)
        CLOSE(9002) //close turnouts D-C
    ENDIF
    FWD(30) //Move forward Speed 30
    AT(CD_S1_D)
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


//Change route to track B
AUTOMATION(416, "D: Change to Track B") //Leave yard to Station not stopping
   
    RESERVE(D_B1) //Reserve Station block
    IFTHROWN(9002)
        CLOSE(9002) //close turnouts D-C
    ENDIF
    FWD(30) //Move forward Speed 30
    AT(CD_S1_D)
FOLLOW(417)

SEQUENCE(417)
        IFRED(SIG_D1)
        STOP
        FOLLOW(417)
    ENDIF
FOLLOW(418) 

SEQUENCE(418)   
    RESERVE(D_B2) //Reserve Next block
    RESERVE(B_B2) //Reserve block 2 on track B
    RESERVE(B_B3) //Reserve block 3 on track B
    RESERVE(C_B3) //Reserve block on track C Subject to change...
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
    IFCLOSED(9010)
        THROW(9010)
    ENDIF
    SPEED(30) //Maybe too fast
    CALL(400) //Release the Staging Yard Block
    AT(CD_S2_D)
FOLLOW(419)

SEQUENCE(419) //Progress to Block2
//    RESERVE(D_B3) //Reserve Next block
    RED(SIG_D1)
    FWD(40) //Increase speed
    AT(CD_S4_B)
    FREE(D_B1)
    AT(CD_S5_B)
FOLLOW(420)

SEQUENCE(420)
    RED(SIG_B2)
    AT(CD_S6_B)
    CLOSE(9010)
    FREE(D_B2)
    FREE(C_B3)
FOLLOW(206)



//ALMOST THERE
AUTOMATION(1421,"D: Run Track 1") //Auto Track 1
   CALL(450)
   IFSTASH(TC1)
    CLOSE(9126) //Close exit to allow roundy
    PICKUP_STASH(TC1)
    FON(0)
   ENDIF
FOLLOW(402)

AUTOMATION(1422,"D: Run Track 2") //Auto Track 2
   CALL(450)
   IFSTASH(TC2)
     THROW(9127) 
     PICKUP_STASH(TC2)
     FON(0)
   ENDIF
FOLLOW(402)

AUTOMATION(1423,"D: Run Track 3") //Auto Track 3
   CALL(450)
   IFSTASH(TC3)
     THROW(9128) 
     PICKUP_STASH(TC3)
     FON(0)
   ENDIF
FOLLOW(402)

AUTOMATION(1424,"D: Run Track 4") //Auto Track 4
   CALL(450)
   IFSTASH(TC4)
     THROW(9129) 
     PICKUP_STASH(TC4)
     FON(0)
   ENDIF
FOLLOW(402)

AUTOMATION(1425,"D: Run Track 5") //Auto Track 5
   CALL(450)
   IFSTASH(TC5)
     CLOSE(9129) 
     PICKUP_STASH(TC5)
     FON(0)
   ENDIF
FOLLOW(402)

ROUTE(1400,"D: Breaktime Select") //Select whether to run auto or not
    IF(autoSelected_D)
        UNLATCH(autoSelected_D)
        ROUTE_HIDDEN(1431)
    ELSE
        LATCH(autoSelected_D)
        ROUTE_ACTIVE(1431)
    ENDIF
DONE


//Automatic Running
AUTOMATION(1431,"D: Break time Run")
IF(autoSelected_D)
    LATCH(autoRunning_D) //Full auto Track D
    ROUTE_DISABLED(1431)
    ROUTE_CAPTION(1431,"RUNNING")
    IFRANDOM(20) CALL(1421) ENDIF FOLLOW(1431) ENDIF
    IFRANDOM(25) CALL(1422) ENDIF FOLLOW(1431) ENDIF
    IFRANDOM(33) CALL(1423) ENDIF FOLLOW(1431) ENDIF
    IFRANDOM(50) CALL(1424) ENDIF FOLLOW(1431) ENDIF
    IFRANDOM(100) CALL(1425) ENDIF FOLLOW(1431) ENDIF
ELSE
    ROUTE_ACTIVE(1431)
    UNLATCH(autoRunning_D) //Full auto Track D
ENDIF
DONE