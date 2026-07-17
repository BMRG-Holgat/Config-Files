/*
* myTrackB.h
* Add in the routes for trackD only
*
* V 0.1.0
*           290 - 294 Free yard tracks
*           295 - 299 Reserve yard tracks
*           289 Auto Park
*           1201 - Auto parking AUTOMATIC
*           1202 - Around we go
*           1221 - Track 1
*           1222 - Track 2
*           1223 - Track 3
*           1224 - Track 4
*           1225 - Track 5
*           1230 - Breaktime Select
*           1231 - Break time
*
*/



//Release Block when loco is removed from track
SEQUENCE(250) //Disable routes
   ROUTE_DISABLED(1202)
//    ROUTE_DISABLED(1203)
    ROUTE_DISABLED(1221)
    ROUTE_DISABLED(1222)
    ROUTE_DISABLED(1223)
    ROUTE_DISABLED(1224)
    ROUTE_DISABLED(1225)
    ROUTE_DISABLED(1230)
    ROUTE_DISABLED(1231)
   RETURN
DONE

SEQUENCE(251) //Enable routes
   ROUTE_ACTIVE(1202)
//    ROUTE_ACTIVE(1203)
    ROUTE_ACTIVE(1221)
    ROUTE_ACTIVE(1222)
    ROUTE_ACTIVE(1223)
    ROUTE_ACTIVE(1224)
    ROUTE_ACTIVE(1225)
    ROUTE_ACTIVE(1230)
    ROUTE_ACTIVE(1231)
    RETURN
DONE


AUTOMATION(1201,"B: Park Train")  
    ROUTE_HIDDEN(1201) 
    CALL(254)
    ROUTE_ACTIVE(1201)   
DONE

AUTOMATION(1202,"B: Around we go")
    CALL(250)
    FON(0)
    PRINT("Calling 200")
    CALL(200)
    PRINT("Calling 201")
    CALL(201)
    PRINT("Calling 202")
    CALL(202)
    PRINT("Calling 203")
    CALL(203)
    PRINT("Calling 204")
    CALL(204)
    PRINT("Sequence 290")
SEQUENCE(290)
    PRINT("Calling 205")
    CALL(205)
    PRINT("Calling 206")
    CALL(206)
    PRINT("Calling 207")
    CALL(207)
    PRINT("Calling 208")
    CALL(208)
    PRINT("Calling 209")
    CALL(209)
    PRINT("Calling 210")
    CALL(210)
    PRINT("Calling 211")
    CALL(211)
    PRINT("Calling Park")
    CALL(254)
    FOFF(0)
    PRINT("Ended")
    IF(autoRunning_B)
        RETURN 
    ENDIF
DONE   

AUTOMATION(1203,"B: B TO A")
    CALL(200)
    CALL(201)
    CALL(212)
    CALL(213)
    CALL(214)
    FOLLOW(1103)
DONE

SEQUENCE(200) 
    IFRESERVE(B_B1) //Reserve Block 1
        IFTHROWN(9001)
            CLOSE(9001) //close turnouts A - B
        ENDIF
        IFTHROWN(9026)
            CLOSE(9026) //close turnouts B - A
        ENDIF 
    ELSE
        FOLLOW(200)
    ENDIF 
    SPEED(30)
    AT(CD_S1_B)
    IFLOCO(SoundLoco)
        FON(1)
    ENDIF
    SAVE_SPEED
    PRINT("SAVE_SPEED 200")
    RETURN
DONE


SEQUENCE(201) //Progress to Block2    
    CALL(253)
    CALL(251)
    AT(CD_S1_B1)
    SAVE_SPEED
    PRINT("SAVE_SPEED 201")
    RETURN
DONE

SEQUENCE(212)
    RESERVE(B_B2) //Reserve Next block
        IFRESERVE(A_B2)
            RED(SIG_A1)
            RESERVE(A_B3)
            IFTHROWN(9004)
                CLOSE(9004) //close turnouts A->B
            ENDIF
            IFCLOSED(9007)
                THROW(9007) //close turnouts B->A   
            ENDIF
            SPEED(30)
        ELSE
            RED(SIG_B1)
            SAVE_SPEED
            DELAY(5000)
            PRINT("SAVE_SPEED AT WAIT_WHILE_RED 202")
            START_SHARED(215)
//            WAIT_WHILE_RED(SIG_B1)
            FOLLOW(212)
        ENDIF    
    AT(CD_S2_B)
    RETURN      
DONE

SEQUENCE(213)
    RED(SIG_B1)
    RETURN
DONE

SEQUENCE(214)
    AT(CD_S4_A)
    DELAY(1000)
    RED(SIG_A2)
    AT(CD_S6_A)
    RESTORE_SPEED
    CLOSE(9007)
    FREE(B_B2)
    RETURN
DONE

SEQUENCE(215)
    WAIT_WHILE_RED(SIG_B1)
    RETURN
DONE

SEQUENCE(202) //Progress to Block2
    IFRESERVE(B_B2) //Reserve Next block
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
        IFAMBER(SIG_B1)
            PRINT("SAVE_SPEED IFAMBER 202")
            SPEED(35)
            SAVE_SPEED
        ENDIF
    ELSE
        AT(CD_S1_B1)
        SAVE_SPEED
        PRINT("SAVE_SPEED AT WAIT_WHILE_RED 202")
        WAIT_WHILE_RED(SIG_B1)
        FOLLOW(202)
    ENDIF    
    AT(CD_S2_B)
    RETURN
DONE

SEQUENCE(203) //Progress to Block 3
    RED(SIG_B1)
    IFRESERVE(B_B3) //Reserve Next block
        IFAMBER(SIG_B2)
            SPEED(35)
            PRINT("SET SPEED 35 IFAMBER 203")
        ENDIF
        IFGREEN(SIG_B2)
            SAVE_SPEED
            RESTORE_SPEED
            PRINT("RESTORE_SPEED IFGREEN 203")
        ENDIF
    ELSE
       IF(CD_S3_B)
            WAIT_WHILE_RED(SIG_B2)
       ENDIF
      FOLLOW(203)
    ENDIF    
    AT(CD_S4_B)
    FREE(B_B1)
//    IFGREEN(SIG_B2)
//        RESTORE_SPEED
//    ENDIF   
    RETURN
DONE

SEQUENCE(204)
    AT(CD_S5_B)
    IFTHROWN(9004) //If moved from Track A to Track B close points
        CLOSE(9004) // close turnouts A->B
    ENDIF
    RED(SIG_B2)   
    IFRED(SIG_B3)
        SPEED(22)
        PRINT("SET SPEED 15 IFRED 204")
    ENDIF
    IFAMBER(SIG_B3)
        SPEED(25)
        PRINT("SET SPEED IFAMBER 204")
    ENDIF
    IFGREEN(SIG_B3)
        RESTORE_SPEED
        PRINT("RESTORE_SPEED IFGREEN 204")
    ENDIF
    AT(CD_S6_B)
     IFRED(SIG_B3)
        SPEED(15)
    ENDIF
    RETURN
DONE

SEQUENCE(205) //Progress to Block4
    IFRESERVE(B_B4) //Reserve Next block
        IFGREEN(SIG_B3)
            RESTORE_SPEED
            PRINT("RESTORE_SPEED IFGREEN 205")
        ENDIF
        IFTHROWN(9020)
            CLOSE(9020) // prevent route A-B
            CLOSE(9021) // prevent route A-D
        ENDIF
        IFAMBER(SIG_B3)
            SPEED(35)
            PRINT("SET SPEED 34 IFAMBER 205")
 //       ELSE
 //           RESTORE_SPEED
 //           PRINT("RESTORE_SPEED 205")
        ENDIF
    ELSE
        AT(CD_S7_B)
        WAIT_WHILE_RED(SIG_B3)       
        FOLLOW(205)
    ENDIF   
    AT(CD_S8_B)  
    RETURN
DONE

SEQUENCE(206) //Progress to Block5
    AMBER(SIG_B1)
    FREE(B_B2) //Free previous block
    RED(SIG_B3)
    RETURN
DONE

SEQUENCE(207)
    IFRESERVE(B_B5) //Reserve Next block
        IFTHROWN(9023)
            CLOSE(9023) // prevent route A->B   
        ENDIF
        IFAMBER(SIG_B4)
            SPEED(35)
            PRINT("SET SPEED IFAMBER 207")
        ELSE
            RESTORE_SPEED
            PRINT("RESTORE_SPEED 207")
        ENDIF
    ELSE
        AT(CD_S9_B)
        WAIT_WHILE_RED(SIG_B4)
        FOLLOW(207)
    ENDIF
    AT(CD_F9_B)
    RETURN
DONE

SEQUENCE(208) //Progress to Block6
    RED(SIG_B4)
    AMBER(SIG_B2)
    FREE(B_B3)
    GREEN(SIG_B1)
    AT(CD_F8_B)
    RETURN
DONE

SEQUENCE(209) //Progress to Block6
    FOFF(1)
    FREE(B_B4)
    GREEN(SIG_B2)
    AMBER(SIG_B3)
    AT(CD_F7_B)
    RETURN
DONE

SEQUENCE(210) //Progress to Block6
    RESERVE(B_B6) //Reserve Next block
//    FREE(B_B4) //Free previous block
    GREEN(SIG_B3)
    AMBER(SIG_B4)
    SPEED(35)
    AT(CD_F6_B)
    RETURN
DONE

SEQUENCE(211)
    GREEN(SIG_B4)
    FREE(B_B5)
    RETURN
DONE


//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(253) //Release Parked Block dependant on turnout thrown
    IFCLOSED(9115) //Track FD1
        FREE(B_B7)
        SCREEN(2,1,"")
        CLEAR_STASH(TB1)
        RETURN
    ENDIF
    IFTHROWN(9116) //Track FD2
        FREE(B_B8)
        SCREEN(2,2,"")
        CLEAR_STASH(TB2)
        RETURN
    ENDIF
    IFTHROWN(9117) //Track FD3
        FREE(B_B9)
        SCREEN(2,3,"")
        CLEAR_STASH(TB3)
        RETURN
    ENDIF
    IFCLOSED(9118) //Track FD4
        FREE(B_B10)
        SCREEN(2,4,"")
        CLEAR_STASH(TB4)
        RETURN
    ENDIF
    IFTHROWN(9118) //Track FD5
        FREE(B_B11)
        SCREEN(2,5,"")
        CLEAR_STASH(TB5)
        RETURN
    ENDIF
DONE

//Auto Park Sequence
SEQUENCE(254)
    IFSTASH(TB1)
        FOLLOW(255)
    ELSE
        IFRESERVE(B_B7)
            SCREEN(3,3,"Loading Track 1")
            SCREEN(2,3,"Loading Track B1")
            CLOSE(9110)
            FWD(PARKING)
            AT(CD_F2_B1)
            DELAY(2000)
            ESTOP
            FREE(B_B6)
            STASH(TB1)
            SCREEN(3,3,"")
            SCREEN(2,3,"")
            RETURN
        ENDIF
    ENDIF
DONE

//Track 2
SEQUENCE(255)
    IFSTASH(TB2)
        FOLLOW(256)
    ELSE
        IFRESERVE(B_B8)
            SCREEN(3,3,"Loading Track 2")
            SCREEN(2,3,"Loading Track B2")
            THROW(9111)
            FWD(PARKING)
            AT(CD_F2_B2)
            DELAY(1500)
            ESTOP
            FREE(B_B6)
            STASH(TB2)
            SCREEN(3,3,"")
            SCREEN(2,3,"")
            RETURN
        ENDIF
    ENDIF
DONE

//Track3
SEQUENCE(256)
    IFSTASH(TB3)
        FOLLOW(257)
    ELSE
        IFRESERVE(B_B9)
            SCREEN(3,3,"Loading Track 3")
            SCREEN(2,3,"Loading Track B3")
            THROW(9112)
            FWD(PARKING)
            AT(CD_F2_B3)
            DELAY(500)
            ESTOP
            FREE(B_B6)
            STASH(TB3)
            SCREEN(3,3,"")
            SCREEN(2,3,"")
            RETURN
        ENDIF
    ENDIF
DONE

//Track 4
SEQUENCE(257)
    IFSTASH(TB4)
        FOLLOW(258)
    ELSE
        IFRESERVE(B_B10)
            SCREEN(3,3,"Loading Track 4")
            SCREEN(2,3,"Loading Track B4")
            THROW(9113)
            FWD(PARKING)
            AT(CD_F3_B4)
            DELAY(500)
            ESTOP
            FREE(B_B6)
            STASH(TB4)
            SCREEN(3,3,"")
            SCREEN(2,3,"")
            RETURN
        ENDIF
    ENDIF
DONE

//Track 5
SEQUENCE(258)
    IFSTASH(TB5)
        SCREEN(3,3,"Yard B full!")
        SCREEN(2,3,"Yard B Full")
        ESTOP
        FOLLOW(254)
    ELSE
        IFRESERVE(B_B11)
            SCREEN(3,3,"Loading Track 5")
            SCREEN(2,3,"Loading Track B5")
            CLOSE(9113)
            FWD(PARKING)
            AT(CD_F3_B5)
            DELAY(500)
            ESTOP
            FREE(B_B6)
            STASH(TB5)
            SCREEN(3,3,"")
            SCREEN(2,3,"")
            RETURN
        ENDIF
    ENDIF
DONE



AUTOMATION(1221,"B: Run Track 1") //Auto Track 1
   CALL(250)
   IFSTASH(TB1)
      CLOSE(9115) //Close exit to allow roundy
      PICKUP_STASH(TB1)
      FON(0)
    ELSE
        PRINT("No Train")
        CALL(251)
        RETURN
   ENDIF
   FOLLOW(1202)
   IF(autoRunning_B)
    RETURN
   ENDIF
DONE

AUTOMATION(1222,"B: Run Track 2") //Auto Track 2
   CALL(250)
   IFSTASH(TB2)
     THROW(9116) 
     PICKUP_STASH(TB2)
     FON(0)
    ELSE
        PRINT("No Train")
        CALL(251)
        RETURN
   ENDIF
   FOLLOW(1202)
   IF(autoRunning_B)
    RETURN
   ENDIF
DONE

AUTOMATION(1223,"B: Run Track 3") //Auto Track 3
   CALL(250)
   IFSTASH(TB3)
     THROW(9117) 
     PICKUP_STASH(TB3)
     FON(0)
    ELSE 
        PRINT("No Train")
        CALL(251)
        RETURN
    ENDIF
    FOLLOW(1202)
    IF(autoRunning_B)
        RETURN
    ENDIF
DONE

AUTOMATION(1224,"B: Run Track 4") //Auto Track 4
   CALL(250)
   IFSTASH(TB4)
     CLOSE(9118) 
     PICKUP_STASH(TB4)
     FON(0)
    ELSE 
        PRINT("No Train")
        CALL(251)
        RETURN 
    ENDIF
     FOLLOW(1202)
     IF(autoRunning_B)
        RETURN
     ENDIF
DONE

AUTOMATION(1225,"B: Run Track 5") //Auto Track 5
   CALL(250)
   IFSTASH(TB5) 
     THROW(9118) 
     PICKUP_STASH(TB5)
     FON(0)
   ELSE
        PRINT("No Train")
        CALL(251)
        RETURN
   ENDIF
    FOLLOW(1202)
    IF(autoRunning_B)
        RETURN
     ENDIF
DONE


ROUTE(1230,"B: Breaktime Select") //Select whether to run auto or not
    IF(autoSelected_B)
        UNLATCH(autoSelected_B)
        ROUTE_HIDDEN(1231)
        ROUTE_CAPTION(1230,"Enable")
    ELSE
        LATCH(autoSelected_B)
        ROUTE_ACTIVE(1231)
        ROUTE_CAPTION(1230,"Disable")
    ENDIF
DONE


AUTOMATION(1231,"B: Break time Run")
IF(autoSelected_B)
    LATCH(autoRunning_B) //Full auto Track B
    ROUTE_DISABLED(1231)
    ROUTE_CAPTION(1231,"RUNNING")
    SCREEN(2,4,"Yard B Automatic")
    SCREEN(3,4,"Yard B Automatic")
    SCREEN(4,4,"Yard B Automatic")
    RANDOM_CALL(1221,1222,1223,1224,1225)
    FOLLOW(1231)
ELSE
    ROUTE_ACTIVE(1231)
    SCREEN(2,4,"")
    SCREEN(3,4,"")
    SCREEN(4,4,"")
    UNLATCH(autoRunning_B) //Stop Full auto Track B
    DONE
ENDIF
DONE


