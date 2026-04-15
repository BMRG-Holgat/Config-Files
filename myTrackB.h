/*
* myTrackB.h
* Add in the routes for trackD only
*
* V 0.1.0
*           290 - 294 Free yard tracks
*           295 - 299 Reserve yard tracks
*           289 Auto Park
*           1200 - Breaktime Select
*           1231 - Break time
*           1202 - Around we go
*           1221 - Track 1
*           1222 - Track 2
*           1223 - Track 3
*           1224 - Track 4
*           1225 - Track 5
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
    RETURN
DONE


AUTOMATION(1201,"B: Park Train")  
    ROUTE_HIDDEN(1201) 
    CALL(252)
    ROUTE_ACTIVE(1201)   
DONE

AUTOMATION(1202,"B: Around we go")
    CALL(250)
    FON(0)
    CALL(200)
    CALL(201)
    CALL(202)
    CALL(203)
    CALL(204)
SEQUENCE(290)
    CALL(205)
    CALL(206)
    CALL(207)
    CALL(208)
    CALL(209)
    CALL(210)
    CALL(211)
    CALL(252)
    FOFF(0)
    PRINT("Ended")
    IF(autoRunning_B)
        RETURN 
    ENDIF
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
    RETURN
DONE


SEQUENCE(201) //Progress to Block2    
    CALL(253)
    CALL(251)
    AT(CD_S1_B1)
    SPEED(45)
    SAVE_SPEED
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
            SPEED(35)
        ENDIF
    ELSE
        DELAY(4000)
        WAIT_WHILE_RED(SIG_B1)
        FOLLOW(202)
    ENDIF    
    AT(CD_S2_B)
    IFGREEN(SIG_B1)
        RESTORE_SPEED
    ENDIF
    RETURN
DONE

SEQUENCE(203) //Progress to Block 3
    RED(SIG_B1)
    IFRESERVE(B_B3) //Reserve Next block
        IFAMBER(SIG_B2)
            SPEED(35)
        ENDIF
    ELSE
       IF(CD_S3_B)
            WAIT_WHILE_RED(SIG_B2)
       ENDIF
      FOLLOW(203)
    ENDIF    
    AT(CD_S4_B)
    FREE(B_B1)
    IFGREEN(SIG_B2)
        RESTORE_SPEED
    ENDIF   
    RETURN
DONE

SEQUENCE(204)
    AT(CD_S5_B)
    IFTHROWN(9004)
        CLOSE(9004) // close turnouts A->B
    ENDIF
    RED(SIG_B2)   
    IFRED(SIG_B3)
        SPEED(15)
    ENDIF
    IFAMBER(SIG_B3)
        SPEED(25)
    ENDIF
    IFGREEN(SIG_B3)
        RESTORE_SPEED
    ENDIF
    AT(CD_S6_B)
    RETURN
DONE

SEQUENCE(205) //Progress to Block4
    IFRESERVE(B_B4) //Reserve Next block
        IFGREEN(SIG_B3)
            RESTORE_SPEED
        ENDIF
        IFTHROWN(9020)
            CLOSE(9020) // prevent route A-B
            CLOSE(9021) // prevent route A-D
        ENDIF
        IFAMBER(SIG_B3)
            SPEED(35)
        ELSE
            RESTORE_SPEED
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
        ELSE
            RESTORE_SPEED
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
    GREEN(SIG_B2)
    AMBER(SIG_B3)
    AT(CD_F7_B)
    RETURN
DONE

SEQUENCE(210) //Progress to Block6
    RESERVE(B_B6) //Reserve Next block
    FREE(B_B4) //Free previous block
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
SEQUENCE(252)
IFNOT(CD_F2_B1) 
    RESERVE(B_B7)
    SCREEN(2,1,"Block B7 Reserved")
    CLOSE(9110)
    FWD(PARKING) 
    AT(CD_F4_B1)
    SPEED(Reduced_Parking)
    AT(CD_F2_B1)
    DELAY(2000)
    ESTOP
    FREE(B_B6)
    SCREEN(4,6,"")
    STASH(TB1)
    RETURN
ENDIF 
IFNOT(CD_F2_B2) 
    RESERVE(B_B8)
    SCREEN(2,2,"Block B8 Reserved")
    THROW(9111)
    FWD(PARKING) 
    AT(CD_F4_B2)
    SPEED(Reduced_Parking) 
    AT(CD_F2_B2) 
    DELAY(1500)
    ESTOP
    FREE(B_B6)
    SCREEN(4,6,"")
    STASH(TB2)
    RETURN
ENDIF 
IFNOT(CD_F2_B3) 
    RESERVE(B_B9)
    SCREEN(2,3,"Block B9 Reserved")
    THROW(9112)
    FWD(PARKING) 
    AT(CD_F4_B3)
    SPEED(Reduced_Parking)
    AT(CD_F2_B3) 
    DELAY(500)
    ESTOP
    FREE(B_B6)
    SCREEN(4,6,"")
    STASH(TB3)
    RETURN
ENDIF 
IFNOT(CD_F3_B4) 
    RESERVE(B_B10)
    SCREEN(2,4,"Block B10 Reserved")
    THROW(9113)
    FWD(PARKING) 
    AT(CD_F4_B4)
    SPEED(Reduced_Parking)
    AT(CD_F3_B4) 
    DELAY(500)
    ESTOP
    FREE(B_B6)
    SCREEN(4,6,"")
    STASH(TB4)
    RETURN
ENDIF 
IFNOT(CD_F3_B5) 
    RESERVE(B_B11)
    SCREEN(2,5,"Block B11 Reserved")
    CLOSE(9113)
    FWD(PARKING) 
    AT(CD_F4_B1)
    SPEED(Reduced_Parking) 
    AT(CD_F3_B5) 
    DELAY(500)
    ESTOP
    FREE(B_B6)
    SCREEN(4,6,"")
    STASH(TB5)
    RETURN
ENDIF 
DONE

/*

AUTOMATION(213,"B: Station Stop Manual") //Station Stop
    CALL(250)
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
        FOLLOW(213)
    ENDIF
    AT(CD_S1_A)
FOLLOW(214)

SEQUENCE(214) //Stop at station
    CALL(251)
    STOP
    CALL(200)
    DELAYRANDOM(10000,15000)
FOLLOW(215)

SEQUENCE(215) //Release turnout block and set turnouts for return to A
    IFRESERVE(B_B2)
        IFRESERVE(A_B2) //reserve Block 2
            IFCLOSED(9004)
                THROW(9004) //close turnouts A->B
            ENDIF
        ENDIF
        IFTHROWN(9007)
            CLOSE(9007) //close turnouts B->A
        ENDIF
        GREEN(SIG_B1)
    ELSE
        RED(SIG_A1) //Set signal to red if block 2 not free
        STOP
        FOLLOW(215)
    ENDIF
    AT(CD_S2_A)
FOLLOW(216)

SEQUENCE(216)
    RED(SIG_A1)
    FREE(A_B1)
    IFTHROWN(9026)
        CLOSE(9026) //close turnouts B->A 
    ENDIF
FOLLOW(205)
    
// Start of main FULL AUTOMATIONS for track B

AUTOMATION(1213,"B: Station Stop Auto") //Station Stop
    CALL(250)
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
        FWD(20)
    ELSE
        FOLLOW(1213)
    ENDIF
    AT(CD_S1_AA)
    SAVE_SPEED
FOLLOW(1214)

SEQUENCE(1214) //Stop at station
    CALL(251)
    IFLOCO(89,90)
        FON(1)
    ENDIF
    DELAY(3000)
    STOP
    CALL(200)
    FREE(B_B1)
    IFLOCO(89,90)
        FON(8)
    ENDIF
    DELAYRANDOM(10000,15000)
    IFLOCO(89,90)
        DELAY(500)
        FON(4)
        DELAY(19000)
        FOFF(4)
        DELAY(500)
        FON(10)
        DELAY(500)
        FOFF(10)
    RESTORE_SPEED
FOLLOW(1215)

SEQUENCE(1215) //Release turnout block and set turnouts for return to A
    IFRESERVE(B_B2)
        IFRESERVE(A_B2) //reserve Block 2
            IFCLOSED(9004)
                THROW(9004) //close turnouts A->B
            ENDIF
        ENDIF
        IFTHROWN(9007)
            CLOSE(9007) //close turnouts B->A
        ENDIF
        GREEN(SIG_B1)
    ELSE
        RED(SIG_A1) //Set signal to red if block 2 not free
        WAIT_WHILE_RED(SIG_A1)
        FOLLOW(1215)
    ENDIF
    AT(CD_S2_A)
FOLLOW(1216)

SEQUENCE(1216)
    SPEED(45)
    RED(SIG_A1)
    FREE(A_B1)
    FREE(A_B2)
    IFTHROWN(9026)
        CLOSE(9026) //close turnouts B->A 
    ENDIF
    SAVE_SPEED
FOLLOW(1205)
*/

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


/*
//Suggested improvements for track selection
//select different route depending on reserve status of blocks
IFRESERVEB_B2) FOLLOW(1213) ENDIF
DELAY(.....) 
IFRESERVEB_B2) FOLLOW(1213) ENDIF
/// had two goes .. no banana
DONE
SEQUENCE1213)
.... carry on with block reserved


HAL(Bitmap,777,1)

RESET(777)
BITMAP_OR(777,5)  // start counter at 5

SEQUENCE(xxxx)
  IFRESERVE(yyyy) FOLLOW(zzzz) DONE
  DELAY(1000)
  BITMAP_DEC(777)
  IF(777) FOLLOW(xxxx)
  // no banana
  DONE
SEQUENCE(zzzz)
  // Have banana 
*/


ROUTE(1200,"B: Breaktime Select") //Select whether to run auto or not
    IF(autoSelected_B)
        UNLATCH(autoSelected_B)
        ROUTE_HIDDEN(1231)
        ROUTE_CAPTION(1300,"Enable")
    ELSE
        LATCH(autoSelected_B)
        ROUTE_ACTIVE(1231)
        ROUTE_CAPTION(1300,"Disable")
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


