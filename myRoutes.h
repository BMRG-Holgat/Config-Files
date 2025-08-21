/*
* myRoute
* for churchbells
*/
ALIAS(Bridge,348)
ALIAS(B2_Light1,349)
ALIAS(B2_Light2,350)
ALIAS(B2_Light3,351)
ALIAS(B3_Light1,431)
/*
//Reset hidden routes
ROUTE(1200,"System: Reset Hidden")
ROUTE_INACTIVE(40)
ROUTE_INACTIVE(41)
DONE
*/
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
    SET(Bridge)
    SET(B2_Light1)
    SET(B2_Light2)
    SET(B2_Light3)
    SET(B3_Light1)
    LATCH(Latch_light)
ELSE 
    RESET(Bridge)
    RESET(B2_Light1)
    RESET(B2_Light2)
    RESET(B2_Light3)
    RESET(B3_Light1)
    UNLATCH(Latch_light)
ENDIF 
DONE

ROUTE(1014,"Lights: House")
IFNOT(Latch_light_house)
    SET(432)
    SET(433)
    SET(434)
    SET(435)
    LATCH(Latch_light_house)
ELSE 
    RESET(432)
    RESET(433)
    RESET(434)
    RESET(435)
    UNLATCH(Latch_light_house)
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
