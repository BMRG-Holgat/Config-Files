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
*           1401 - park train
*           1402 - Around we go
*           1403 - Station Stop
*           1404 - Change to Track B
*           1405 - Change to Track A
*           1421 - Track 1
*           1422 - Track 2
*           1423 - Track 3
*           1424 - Track 4
*           1425 - Track 5
*           1430 - Breaktime Select
*           1431 - Breaktime
*
*/



SEQUENCE(450) //Disable routes
SCREEN(2,0,"Automation running")
SCREEN(3,0,"Automation running")
    ROUTE_DISABLED(1401)
    ROUTE_DISABLED(1402)
    ROUTE_DISABLED(1403)
    ROUTE_DISABLED(1404)
    ROUTE_DISABLED(1405)
    ROUTE_DISABLED(1421)
    ROUTE_DISABLED(1422)
    ROUTE_DISABLED(1423)
    ROUTE_DISABLED(1424)
    ROUTE_DISABLED(1425)
    ROUTE_DISABLED(1430)
    ROUTE_DISABLED(1431)
   RETURN
DONE

SEQUENCE(451) //Enable routes
    ROUTE_ACTIVE(1401)
    ROUTE_ACTIVE(1402)
    ROUTE_ACTIVE(1403)
    ROUTE_ACTIVE(1404)
    ROUTE_ACTIVE(1404)
    ROUTE_ACTIVE(1421)
    ROUTE_ACTIVE(1422)
    ROUTE_ACTIVE(1423)
    ROUTE_ACTIVE(1424)
    ROUTE_ACTIVE(1425)
    ROUTE_ACTIVE(1430)
    ROUTE_ACTIVE(1431)
RETURN
DONE

AUTOMATION(1401,"D: Park Train") 
    ROUTE_HIDDEN(1401)
    CALL(454)
    ROUTE_ACTIVE(1401)
DONE

AUTOMATION(1402, "D: Around We Go") //Leave yard to Station not stopping
    CALL(450)
    FON(0)
    PRINT("Calling 400")
    CALL(400)
    PRINT("Calling 401")
    CALL(401)
    PRINT("Calling 402")
    CALL(402)
    PRINT("Calling 403")
    CALL(403)
    PRINT("Calling 404")
    CALL(404)
    PRINT("Calling 405")
    CALL(405)
    PRINT("Calling 406")
    CALL(406)
    PRINT("Calling 420")
    CALL(420)
    PRINT("Calling 407")
    CALL(407)
    SEQUENCE(1408)
    FOFF(1)
    PRINT("Calling 408")
    CALL(408)
    PRINT("Calling 409")
    CALL(409)
    PRINT("Calling 410")
    CALL(410)
    CALL(454) //Auto Park at end of route   
    FOFF(0)
    PRINT("D: Ended")
    IF(autoRunning_D)
        RETURN
    ENDIF
DONE

AUTOMATION(1403, "D: Station Stop") //Leave yard to Station not stopping
    CALL(450)
    FON(0)
    PRINT("Calling 400")
    CALL(400)
    PRINT("Calling 411")
    CALL(411) //Wait at S1D to simulate stopping at station
    PRINT("Calling 401")
    CALL(401)
    PRINT("Calling 402")
    CALL(402)
    PRINT("Calling 403")
    CALL(403)
    PRINT("Calling 404")
    CALL(404)
    PRINT("Calling 405")
    CALL(405)
    PRINT("Calling 406")
    CALL(406)
    PRINT("Calling 420")
    CALL(420)
    PRINT("Calling 407")
    CALL(407)
    FOFF(1)
    PRINT("Calling 408")
    CALL(408)
    PRINT("Calling 409")
    CALL(409)
    PRINT("Calling 410")
    CALL(410)
    CALL(454) //Auto Park at end of route   
    FOFF(0)
    PRINT("D: Ended")
    IF(autoRunning_D)
        RETURN
    ENDIF
DONE

AUTOMATION(1404, "D: Change to Track B") //Leave yard to Station not stopping
    CALL(450)
    FON(0)
    PRINT("Calling 400")
    CALL(400)
    PRINT("Calling 401")
    CALL(401)
    PRINT("Calling 412")
    CALL(412)
    PRINT("Calling 413")
    CALL(413)
    PRINT("Calling 414")
    SCREEN(2,5,"")
    SCREEN(3,2,"B: (D-B) Switched")
    CALL(414)
    //Changed to Track B at this point
DONE

AUTOMATION(1405,"D: Change to Track A")
SCREEN(3,3,"D: Change to A")
SCREEN(3,1,"A:")
SCREEN(3,2,"B:")
SCREEN(2,5,"D: Change to A")
    CALL(450)
    FON(0)
    PRINT("Calling 400")
    CALL(400)
    PRINT("Calling 401")
    CALL(401)
    PRINT("Calling 415")
    CALL(415)
    PRINT("Calling 416")
    CALL(416)
    PRINT("Caling 417")
    CALL(417)
    SCREEN(2,5,"")
    SCREEN(2,1,"A: (D-A) Switched")
    SCREEN(3,3,"")
    SCREEN(3,1,"A: (D-A) Switched")
    PRINT("Following 1131")
    FOLLOW(1131)
DONE


//Auto Park Sequence
SEQUENCE(454)
    IFSTASH(TD1)
        FOLLOW(455)
    ELSE
        IFRESERVE(D_B7)
            SCREEN(3,5,"Loading Track 1")
            SCREEN(2,5,"Loading Track D1")
            CLOSE(9130)
            FWD(PARKING)
            AT(CD_F2_D1)
            ESTOP
            FREE(D_B6)
            STASH(TD1)
            SCREEN(3,5,"")
            SCREEN(2,5,"")
            RETURN
        ENDIF
    ENDIF
DONE

//Track 2
SEQUENCE(455)
    IFSTASH(TD2)
        FOLLOW(456)
    ELSE
        IFRESERVE(D_B8)
            SCREEN(3,5,"Loading Track 2")
            SCREEN(2,5,"Loading Track D2")
            THROW(9131)
            FWD(PARKING)
            AT(CD_F2_D2)
            ESTOP
            FREE(D_B6)
            STASH(TD2)
            SCREEN(3,5,"")
            SCREEN(2,5,"")
            RETURN
        ENDIF
    ENDIF
DONE

//Track3
SEQUENCE(456)
    IFSTASH(TD3)
        FOLLOW(457)
    ELSE
        IFRESERVE(D_B9)
            SCREEN(3,5,"Loading Track 3")
            SCREEN(2,5,"Loading Track D3")
            THROW(9132)
            FWD(PARKING)
            AT(CD_F2_D3)
            ESTOP
            FREE(D_B6)
            STASH(TD3)
            SCREEN(3,5,"")
            SCREEN(2,5,"")
            RETURN
        ENDIF
    ENDIF
DONE

//Track 4
SEQUENCE(457)
    IFSTASH(TD4)
        FOLLOW(458)
    ELSE
        IFRESERVE(D_B10)
            SCREEN(3,5,"Loading Track 4")
            SCREEN(2,5,"Loading Track D4")
            THROW(9133)
            FWD(PARKING)
            AT(CD_F2_D4)
            ESTOP
            FREE(D_B6)
            STASH(TD4)
            SCREEN(3,5,"")
            SCREEN(2,5,"")
            RETURN
        ENDIF
    ENDIF
DONE

//Track 5
SEQUENCE(458)
    IFSTASH(TD5)
        SCREEN(3,5,"Yard D full!")
        SCREEN(2,5,"Yard D Full")
        ESTOP
        FOLLOW(454)
    ELSE
        IFRESERVE(D_B11)
            SCREEN(3,5,"Loading Track 5")
            SCREEN(2,5,"Loading Track D5")
            CLOSE(9133)
            FWD(PARKING)
            AT(CD_F2_D5)
            ESTOP
            FREE(D_B6)
            STASH(TD5)
            SCREEN(3,5,"")
            SCREEN(2,5,"")
            RETURN
        ENDIF
    ENDIF
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(453) //Release Parked Block dependant on turnout thrown
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
        CLEAR_STASH(TD5)
        RETURN
    ENDIF
DONE


SEQUENCE(400)//Leave yard to Station not stopping
    IFRESERVE(D_B1) //Reserve Station block
        CLOSE(9002) //close turnouts D-C
        FWD(StartSpeed) //Move forward Speed 30
    ELSE
        FOLLOW(400)
    ENDIF
    AT(CD_S1_D)
    SAVE_SPEED
    RETURN 
DONE

SEQUENCE(401)
    CALL(451)
    CALL(453) //Release parked block
    IFLOCO(SoundLoco) 
        FON(1)
    ENDIF 
    DELAY(2000)
RETURN 
DONE    

SEQUENCE(402)   
    IFRESERVE(D_B2) // Reserve Block 2
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
        DELAY(2000)
        WAIT_WHILE_RED(SIG_D1)
        FOLLOW(402)
    ENDIF
    IFAMBER(SIG_D1)
        SPEED(23)
    ELSE
        SPEED(35) //Maybe too fast
    ENDIF
    AT(CD_S2_D)
    RED(SIG_D1)
    SAVE_SPEED
    RETURN 
DONE    

SEQUENCE(403) //Reserve Block 3
    IFRESERVE(D_B3) //Reserve Next block
        PRINT("Reserved D_B3... 403")
        IFAMBER(SIG_D2)
            SPEED(35)
            PRINT("Set speed 35 IFAMBER 403")
        ENDIF
        IFGREEN(SIG_D2)
            SPEED(45)
            SAVE_SPEED
            RESTORE_SPEED
            PRINT("RESTORE_SPEED IF GREEN 403")
        ENDIF
    ELSE 
        IF(CD_S3_D)
            PRINT("is SIG_D2 still red?")
            WAIT_WHILE_RED(SIG_D2)
        ENDIF
        FOLLOW(403)
    ENDIF
    AT(CD_S4_D)
    RED(SIG_D2)
    FREE(D_B1)
    SCREEN(4,1,"")
    RETURN 
DONE    

SEQUENCE(404)
    AT(CD_S5_D)
    IFRED(SIG_D3)
        SPEED(22)
        PRINT("SET SPEED 15 IFRED 404")
    ENDIF
    IFAMBER(SIG_D3)
        SPEED(25)
        PRINT("SET SPEED IFAMBER 404")
    ENDIF
    IFGREEN(SIG_D3)
        RESTORE_SPEED
        PRINT("RESTORE_SPEED IFGREEN 404")
    ENDIF
    AT(CD_S6_D)
     IFRED(SIG_D3)
        SPEED(15)
    ENDIF
    RETURN
/*    IFRED(SIG_D3)
        SPEED(20)
    ENDIF
    IFAMBER(SIG_D3)
        SPEED(23)
    ELSE
        SPEED(35) 
        SAVE_SPEED
    ENDIF
    RETURN */
DONE

SEQUENCE(405) //Progress to Block3
    IFRESERVE(D_B4)
        IFGREEN(SIG_D3)
            RESTORE_SPEED 
            PRINT("Restore Speed IFGREEN 405")
        ENDIF
        IFAMBER(SIG_D3)
            SPEED(AMBER_SPEED)
        ENDIF
        IFTHROWN(9021)
            CLOSE(9021)
        ENDIF 
    ELSE 
        AT(CD_S7_D)
        WAIT_WHILE_RED(SIG_D3)
        FOLLOW(405)
    ENDIF 
    AT(CD_S8_D)
    RETURN 
DONE    

SEQUENCE(406) //Progress to Block 5
PRINT("SEQ 406")
    RED(SIG_D3)
    FREE(D_B2)
    AMBER(SIG_D1)
    RETURN
DONE

SEQUENCE(420)
    IFRESERVE(D_B5)
        IFTHROWN(9024)
            CLOSE(9024)
        ENDIF
        RESTORE_SPEED
    ELSE 
        AT(CD_S9_D1)
        WAIT_WHILE_RED(SIG_D4)
        FOLLOW(420)
    ENDIF
    RESTORE_SPEED
    AT(CD_S9_D)
    RETURN 
DONE    

SEQUENCE(407)
    RED(SIG_D4)
    GREEN(SIG_D1)
    AMBER(SIG_D2)
    FREE(D_B3)
    AT(CD_F8_D)
    RETURN 
DONE    

SEQUENCE(408) //Progress to Block5  
    RESERVE(D_B6) //Reserve Next block 
    RESTORE_SPEED  
    FREE(D_B4)
    GREEN(SIG_D2)
    IFRED(SIG_D4)
    ELSE
    AMBER(SIG_D3)
    ENDIF
    AT(CD_F7_D)
    RETURN 
DONE

SEQUENCE(409)
    AMBER(SIG_D4) 
    FREE(D_B5)  
    GREEN(SIG_D3)    
    AT(CD_F6_D)
    RETURN 
DONE

SEQUENCE(410)
    GREEN(SIG_D4)    
    RETURN
DONE

SEQUENCE(411)
    AT(CD_S1_D)
    STOP
    DELAYRANDOM(10000,15000)
    RETURN
DONE

SEQUENCE(412)
    IFRESERVE(B_B3) //Reserve block 3 on track B
    PRINT("RESERVED B_B3")
        IFRESERVE(C_B3) //Reserve block 2 on track B
        PRINT("RESERVED C_B3")
            IFRESERVE(B_B2)
            PRINT("RESERVED B_B2")
                RESERVE(D_B2) //Reserve Next block    
                //Ensure route is set
                IFTHROWN(9005)
                    CLOSE(9005)//ensure route is set
                ENDIF
                IFCLOSED(9010)
                    THROW(9010)
                ENDIF
                SPEED(30) //Maybe too fast
                SAVE_SPEED
                CALL(453) //Release the Staging Yard Block
            ELSE
                FREE(C_B3)
                FOLLOW(412)
            ENDIF
        ELSE
            FREE(B_B3)
            PRINT("Cleared B_B3")
            RED(SIG_D1)
            DELAY(5000)
            STOP
            FOLLOW(412)
        ENDIF
    ELSE
        RED(SIG_D1)
        DELAY(5000)
        STOP
        PRINT("Awaiting B_B3 reserve 412")
        FOLLOW(412)
    ENDIF
    AT(CD_S2_D)
    RETURN
DONE

SEQUENCE(413) //Progress to Block2
    PRINT("At sq 413")
    RED(SIG_D1)
    AT(CD_S4_B)
    RED(SIG_B2)
    FREE(D_B1)
    AT(CD_S5_B)
    RETURN
DONE    

SEQUENCE(414)
    AT(CD_S6_B)
    RESTORE_SPEED
    CLOSE(9010)
    FREE(D_B2)
    FREE(C_B3)
FOLLOW(290)

SEQUENCE(415)
    IFRESERVE(A_B3) //Reserve block 3 on track B
    PRINT("RESERVED A_B3")
        IFRESERVE(C_B3) //Reserve block 2 on track B
        PRINT("RESERVED C_B3")
            IFRESERVE(B_B2)
            PRINT("RESERVED B_B2")
                IFRESERVE(A_B2)
                PRINT("RESERVED A_B2")
                    RESERVE(D_B2) //Reserve Next block    
                    //Ensure route is set
                    IFCLOSED(9009)
                        THROW(9009)//ensure route is set
                    ENDIF
                    SPEED(30) //Maybe too fast
                    SAVE_SPEED
                    CALL(453) //Release the Staging Yard Block
                ELSE
                    FREE(B_B2)
                    PRINT("Cleared B_B2")
                    RED(SIG_D1)
                    DELAY(5000)
                    STOP
                    FOLLOW(415)
                ENDIF
            ELSE
                FREE(C_B3)
                PRINT("Cleared C_B3")
                RED(SIG_D1)
                DELAY(5000)
                STOP
                FOLLOW(415)
            ENDIF
        ELSE
            FREE(A_B3)
            PRINT("Cleared A_B3")
            RED(SIG_D1)
            DELAY(5000)
            STOP
            FOLLOW(415)
        ENDIF
    ELSE
        RED(SIG_D1)
        DELAY(5000)
        STOP
        PRINT("Awaiting A_B3 reserve 415")
        FOLLOW(415)
    ENDIF
    AT(CD_S2_D)
    RETURN
DONE

SEQUENCE(416)
   PRINT("At sq 416")
    RED(SIG_D1)
    AT(CD_S4_A)
    RED(SIG_A2)
    FREE(D_B1)
    AT(CD_S5_A)
    RETURN
DONE  

SEQUENCE(417)
    AT(CD_S6_A)
    RESTORE_SPEED
    CLOSE(9009)
    FREE(D_B2)
    FREE(C_B3)
    FREE(B_B2)
    RETURN
DONE
//    FOLLOW(113) //CHANGE THIS WHEN A IS CONVERTED TO CALL

//ALMOST THERE
AUTOMATION(1421,"D: Run Track 1") //Auto Track 1
PRINT("CALLED 1421")
   CALL(450)
   IFSTASH(TD1)
            CLOSE(9135) //Close exit to allow roundy
            PICKUP_STASH(TD1)
            FON(0)
        ELSE
            PRINT("No Train")
            CALL(451)
            RETURN
        ENDIF
        FOLLOW(1402)
    IF(autoRunning_D)
        RETURN
    ENDIF
DONE

AUTOMATION(1422,"D: Run Track 2") //Auto Track 2
PRINT("CALLED 1422")
   CALL(450)
   IFSTASH(TD2)
     THROW(9136) 
     PICKUP_STASH(TD2)
     FON(0)
    ELSE
        PRINT("No Train")
        CALL(451)
        RETURN
    ENDIF
        FOLLOW(1402)
    IF(autoRunning_D)
        RETURN
    ENDIF
DONE

AUTOMATION(1423,"D: Run Track 3") //Auto Track 3
PRINT("CALLED 1423")
   CALL(450)
   IFSTASH(TD3)
     THROW(9137) 
     PICKUP_STASH(TD3)
     FON(0)
    ELSE
        PRINT("No Train")
        CALL(451)
        RETURN
    ENDIF
        FOLLOW(1402)
    IF(autoRunning_D)
        RETURN
    ENDIF
DONE

AUTOMATION(1424,"D: Run Track 4") //Auto Track 4
PRINT("CALLED 1424")
   CALL(450)
   IFSTASH(TD4)
     THROW(9138) 
     PICKUP_STASH(TD4)
     FON(0)
    ELSE
        PRINT("No Train")
        CALL(451)
        RETURN
    ENDIF
        FOLLOW(1402)
    IF(autoRunning_D)
        RETURN
    ENDIF
DONE

AUTOMATION(1425,"D: Run Track 5") //Auto Track 5
PRINT("CALLED 1425")
   CALL(450)
   IFSTASH(TD5)
     CLOSE(9138) 
     PICKUP_STASH(TD5)
     FON(0)
    ELSE
        PRINT("No Train")
        CALL(451)
        RETURN
    ENDIF
    FOLLOW(1402)
    IF(autoRunning_D)
        RETURN
    ENDIF
DONE

ROUTE(1430,"D: Breaktime Select") //Select whether to run auto or not
    IF(autoSelected_D)
        UNLATCH(autoSelected_D)
        ROUTE_HIDDEN(1431)
        ROUTE_CAPTION(1430,"Enable")
    ELSE
        LATCH(autoSelected_D)
        ROUTE_ACTIVE(1431)
        ROUTE_CAPTION(1430,"Disable")
    ENDIF
DONE


//Automatic Running
AUTOMATION(1431,"D: Break time Run")
IF(autoSelected_D)
    LATCH(autoRunning_D) //Full auto Track D
    ROUTE_DISABLED(1431)
    ROUTE_CAPTION(1431,"RUNNING")
    SCREEN(2,4,"Yard D Automatic")
    SCREEN(3,4,"Yard D Automatic")
    SCREEN(4,4,"Yard D Automatic")
    RANDOM_CALL(1421,1422,1423,1424,1425)
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