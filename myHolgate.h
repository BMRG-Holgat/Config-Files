/*
* routes for Holgate sidings
*/

ROUTE(100,"F -> H1")
//add reserves
RESERVE(H_T1) //Reserve siding one
    IFTHROWN(9019) // enure tunrout is closed
        CLOSE(9019)
    ENDIF
    AT(BD_S6_HA)
    SPEED(20) //Reduce speed
    AT(BD_S4_HA)
    STOP
DONE




