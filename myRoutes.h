/*
* myRoute
* for churchbells
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