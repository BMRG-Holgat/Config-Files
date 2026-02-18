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
    ROUTE_DISABLED(402)
    ROUTE_DISABLED(1402)
   RETURN
DONE

SEQUENCE(451) //Enable routes
    ROUTE_ACTIVE(402)
    ROUTE_ACTIVE(1402)
RETURN
DONE

/*
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
*/
//Manually activate the auto park sequence
AUTOMATION(489,"D: Auto Park") 
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
    AT(CD_F2_D1) 
    DELAY(3000)
    ESTOP
    FREE(D_B6)
    STASH(TD1)
    SCREEN(4,6,"")
    RETURN
ENDIF 
IFNOT(CD_F2_D2) 
    RESERVE(D_B8)
    SCREEN(2,2,"Block D8 Reserved")
    THROW(9131)
    FWD(20) 
    AT(CD_F2_D2) 
    DELAY(2000)
    ESTOP
    FREE(D_B6)
    STASH(TD2)
    SCREEN(4,6,"")
    RETURN
ENDIF 
IFNOT(CD_F2_D3) 
    RESERVE(D_B9)
    SCREEN(2,3,"Block D9 Reserved")
    THROW(9132)
    FWD(20) 
    AT(CD_F2_D3) 
    DELAY(1000)
    ESTOP
    FREE(D_B6)
    STASH(TD3)
    SCREEN(4,6,"")
    RETURN
ENDIF 
IFNOT(CD_F2_D4) 
    RESERVE(D_B10)
    SCREEN(2,4,"Block D10 Reserved")
    THROW(9133)
    FWD(20) 
    AT(CD_F2_D4) 
    DELAY(750)
    ESTOP
    FREE(D_B6)
    STASH(TD4)
    SCREEN(4,6,"")
    RETURN
ENDIF 
IFNOT(CD_F2_D5) 
    RESERVE(D_B11)
    SCREEN(2,5,"Block D11 Reserved")
    CLOSE(9133)
    FWD(20) 
    AT(CD_F2_D5) 
    DELAY(750)
    ESTOP
    FREE(D_B6)
    STASH(TD5)
    SCREEN(4,6,"")
    RETURN
ENDIF 
DONE

AUTOMATION(402, "D: Around We Go Manual") //Leave yard to Station not stopping
    ROUTE_HIDDEN(402)
    IFRESERVE(D_B1) //Reserve Station block
        IFTHROWN(9002)
            CLOSE(9002) //close turnouts D-C
        ENDIF
        FWD(20) //Move forward Speed 30
    ELSE
        FOLLOW(402)
    ENDIF
    AT(CD_S1_D)
FOLLOW(403)

SEQUENCE(403)
    ROUTE_ACTIVE(402)
    DELAY(3000)
FOLLOW(404)

SEQUENCE(404)   
    IFRESERVE(D_B2) //Reserve Next block
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
    ELSE
        WAIT_WHILE_RED(SIG_D1)
        FOLLOW(404)
    ENDIF
    AT(CD_S2_D)
FOLLOW(405)

SEQUENCE(405) //Progress to Block2
    SAVE_SPEED
    IFRESERVE(D_B3) //Reserve Next block
        IFAMBER(SIG_D2) 
            SPEED(10)
            SAVE_SPEED
        ENDIF 
        RED(SIG_D1)
    ELSE
        AT(CD_S4_D)
        WAIT_WHILE_RED(SIG_D2)
        FOLLOW(405)
    ENDIF
    RESTORE_SPEED
    FREE(D_B1)
    AT(CD_S5_D)
FOLLOW(406)

SEQUENCE(406)
    SAVE_SPEED
    RED(SIG_D2)
    AT(CD_S6_D) 
FOLLOW(407)

SEQUENCE(407) //Progress to Block3
    IFRESERVE(D_B4) //Reserve Next block
        AMBER(SIG_D1)
        FREE(D_B2)
    IFTHROWN(9021)
        CLOSE(9021) // prevent route A-D
    ENDIF
    ELSE
        AT(CD_S7_D)
        SAVE_SPEED
        WAIT_WHILE_RED(SIG_D3)
        FOLLOW(407)
    RESTORE_SPEED
    AT(CD_S8_D)
FOLLOW(408)

SEQUENCE(408) //Progress to Block4
    RED(SIG_D3)
    IFRESERVE(D_B5) //Reserve Next block
        IFTHROWN(9024)
            CLOSE(9024) // prevent route E-C
        ENDIF
    ELSE
        AT(CD_S9_D1)
        SAVE_SPEED
        WAIT_WHILE_RED(SIG_D4)
        FOLLOW(408)
    ENDIF
     IFAMBER(SIG_D4)
        SPEED(20)
    ELSE
        SPEED(30)
    ENDIF
    AT(CD_S9_D)
FOLLOW(410)

SEQUENCE(409)
    IFRED(SIG_D4)
        AT(CD_S9_D)
        STOP
        FOLLOW(409)
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


AUTOMATION(1402, "D: Around We Go Auto") //Leave yard to Station not stopping
    CALL(450)
    IFRESERVE(D_B1) //Reserve Station block
    SCREEN(4,1,"D1 RESERVED")
        CLOSE(9002) //close turnouts D-C
        FWD(20) //Move forward Speed 30
    ELSE
        FOLLOW(1402)
    ENDIF
    AT(CD_S1_D)
FOLLOW(1403)

SEQUENCE(1403)
    CALL(451)
    CALL(400)   
    FON(1)
FOLLOW(1404)

SEQUENCE(1404)   
    IFRESERVE(D_B2) // Reserve Block 2
    SCREEN(4,2,"D2 RESERVED")
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
        SPEED(35)
        SAVE_SPEED
    ELSE
        SAVE_SPEED
        WAIT_WHILE_RED(SIG_D1)
        FOLLOW(1404)
    ENDIF
    IFAMBER(SIG_D1)
        SPEED(23)
    ELSE
        SPEED(35) //Maybe too fast
    ENDIF
    AT(CD_S2_D)
FOLLOW(1405)

SEQUENCE(1405) //Reserve Block 3
    RED(SIG_D1)
    IFRESERVE(D_B3) //Reserve Next block
    SCREEN(4,3,"D3 RESERVED")
        RESTORE_SPEED
    ELSE 
        AT(CD_S3_D)
        SAVE_SPEED
        WAIT_WHILE_RED(SIG_D2)
        FOLLOW(1405)
    ENDIF
    AT(CD_S4_D)
    FREE(D_B1)
    SCREEN(4,1,"")
    AT(CD_S5_D)
FOLLOW(1406)

SEQUENCE(1406)
    RED(SIG_D2)
    AT(CD_S6_D) 
    SAVE_SPEED
    IFRED(SIG_D3)
        SPEED(20)
    ENDIF
    IFAMBER(SIG_D3)
        SPEED(23)
    ELSE
        SPEED(35) 
        SAVE_SPEED
    ENDIF
FOLLOW(1407)

SEQUENCE(1407) //Progress to Block3
    IFRESERVE(D_B4)
    SCREEN(4,4,"D4 RESERVED")
    IFTHROWN(9021)
        CLOSE(9021)
    ENDIF 
    ELSE 
        AT(CD_S7_D)
        WAIT_WHILE_RED(SIG_D3)
        FOLLOW(1407)
    ENDIF 
    IFAMBER(SIG_D3)
        SPEED(23)
    ELSE
        RESTORE_SPEED
    ENDIF
    AT(CD_S8_D)
FOLLOW(1408)

SEQUENCE(1408) //Progress to Block 5
    RED(SIG_D3)
    IFRESERVE(D_B5)
    SCREEN(4,5,"D5 RESERVED")
        AMBER(SIG_D1)
        FREE(D_B2)
        SCREEN(4,2,"")
        IFTHROWN(2024)
            CLOSE(2024)
        ENDIF
    ELSE 
        AT(CD_S9_D1)
        PRINT("At Bridge")
        SCREEN(4,8,"At Bridge")
        SAVE_SPEED
        WAIT_WHILE_RED(SIG_D4)
        FOLLOW(1408)
    ENDIF
    RESTORE_SPEED
    AT(CD_S9_D)
FOLLOW(1409)

SEQUENCE(1409)
    RED(SIG_D4)
    GREEN(SIG_D1)
    AMBER(SIG_D2)
    AT(CD_F8_D)
FOLLOW(1410)

SEQUENCE(1410) //Progress to Block5  
    FOFF(1)
    SCREEN(4,8,"")
    RESERVE(D_B6) //Reserve Next block
        SCREEN(4,6,"D6 RESERVED")  
        RESTORE_SPEED  
        FREE(D_B3)
        SCREEN(4,3,"")
    AT(CD_F7_D)
FOLLOW(1411)

SEQUENCE(1411)
    AMBER(SIG_D4)   
    AMBER(SIG_D3)
    GREEN(SIG_D2)
    FREE(D_B4)
    SCREEN(4,4,"")
    AT(CD_F6_D)
FOLLOW(1412)

SEQUENCE(1412)
    GREEN(SIG_D4)
    GREEN(SIG_D3)    
    FREE(D_B5)
    SCREEN(4,5,"")
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
    IFRESERVE(D_B1) //Reserve Station block
    IFTHROWN(9002)
        CLOSE(9002) //close turnouts D-C
    ENDIF
        FWD(30) //Move forward Speed 30
    ELSE
        FOLLOW(416)
    ENDIF
    AT(CD_S1_D)
FOLLOW(417)

SEQUENCE(417)
        WAIT_WHILE_RED(SIG_D1)
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
   IFSTASH(TD1)
//        IFRESERVE(D_B1)
            CLOSE(9135) //Close exit to allow roundy
            PICKUP_STASH(TD1)
            FON(0)
        ELSE
            PRINT("No Train")
            RETURN
        ENDIF
        FOLLOW(1402)
    IF(autoRunning_D)
        RETURN
    ENDIF
 //   ENDIF
DONE

AUTOMATION(1422,"D: Run Track 2") //Auto Track 2
   CALL(450)
   IFSTASH(TD2)
//   IFRESERVE(D_B1)
     THROW(9136) 
     PICKUP_STASH(TD2)
     FON(0)
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF
        FOLLOW(1402)
    IF(autoRunning_D)
        RETURN
    ENDIF
 //   ENDIF
DONE

AUTOMATION(1423,"D: Run Track 3") //Auto Track 3
   CALL(450)
   IFSTASH(TD3)
//    IFRESERVE(D_B1)
     THROW(9137) 
     PICKUP_STASH(TD3)
     FON(0)
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF
        FOLLOW(1402)
    IF(autoRunning_D)
        RETURN
    ENDIF
 //   ENDIF
DONE

AUTOMATION(1424,"D: Run Track 4") //Auto Track 4
   CALL(450)
   IFSTASH(TD4)
//    IFRESERVE(D_B1)
     THROW(9138) 
     PICKUP_STASH(TD4)
     FON(0)
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF
        FOLLOW(1402)
    IF(autoRunning_D)
        RETURN
    ENDIF
 //   ENDIF
DONE

AUTOMATION(1425,"D: Run Track 5") //Auto Track 5
   CALL(450)
   IFSTASH(TD5)
//    IFRESERVE(D_B1)
     CLOSE(9138) 
     PICKUP_STASH(TD5)
     FON(0)
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF
    FOLLOW(1402)
    IF(autoRunning_D)
        RETURN
    ENDIF
//    ENDIF
DONE

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
    SCREEN(2,6,"Yard D Automatic")
    SCREEN(3,6,"Yard D Automatic")
    SCREEN(4,6,"Yard D Automatic")
    RANDOM_FOLLOW(1421,1422,1423,1424,1425)
    PRINT("D: NO TRAIN")
    FOLLOW(1431)
ELSE
    ROUTE_ACTIVE(1431)
    SCREEN(2,6,"")
    SCREEN(3,6,"")
    SCREEN(4,6,"")
    UNLATCH(autoRunning_D) //Full auto Track D
    DONE
ENDIF
DONE