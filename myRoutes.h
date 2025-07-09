/*
* myRoute
* for churchbells
*/
//Reset hidden routes
ROUTE(1200,"System: Reset Hidden")
ROUTE_INACTIVE(40)
ROUTE_INACTIVE(41)
DONE

ROUTE(1000,"Main Bells")
   /* PLAYSOUND(10000,0,0,DF_RESET)
    DELAY(2000)
    PLAYSOUND(10000,0,0,DF_FOLDER) // Set folder to 01 player 1 */
    PLAYSOUND(10000,1,30,DF_PLAY)
DONE

ROUTE(1001,"Wedding Peel")
    PLAYSOUND(10000,0,0,DF_RESET)
    DELAY(2000)
    PLAYSOUND(10000,0,02,DF_FOLDER) // Set folder to 01 player 1
    PLAYSOUND(10000,002,30,DF_PLAY)
DONE

ROUTE(1002,"Bells. THe bells")
    SET(10002)
DONE

ROUTE(1003,"More bells")
    SET(10003)
DONE

ROUTE(1004,"Lights: Street")
IFNOT(Latch_light)
    SET(418)
    SET(421)
    SET(422)
    SET(313)
    SET(463)
    LATCH(Latch_light)
ELSE 
    RESET(418)
    RESET(421)
    RESET(422)
    RESET(313)
    RESET(463)
    UNLATCH(Latch_light)
ENDIF 
DONE

ROUTE(1005,"Lights: Church")
IFNOT(Latch_church)
    SET(423)
    LATCH(Latch_church)
ELSE 
    RESET(423)
    UNLATCH(Latch_church)
ENDIF
DONE
