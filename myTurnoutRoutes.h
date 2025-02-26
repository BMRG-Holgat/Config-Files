/*
myTurnoutRoutes.h 

This file replaces the myTurnoutPairs.h for the fiddle yards only

*/
#define closeIt(turnout) \
    IFTHROWN(turnout) \
        CLOSE(turnout) \
    ENDIF 

#define throwIt(turnout) \
    IFCLOSED(turnout) \
        THROW(turnout) \
    ENDIF 
    

ROUTE(500,"Yard B: 1 Access")
    closeIt(UFM_T9_E__UFM_T10_A)
    ROUTE_CAPTION(500,"Closed")
 DONE   

ROUTE(501,"Yard B: 2 Access")
    throwIt(UFM_T9_E__UFM_T10_A)
    throwIt(UFM_T10_E__UFM_T11_A)
    ROUTE_CAPTION(500,"Thrown")
    ROUTE_CAPTION(501,"Thrown")
    ROUTE_DISABLED(501)
    ROUTE_ACTIVE(500)
 DONE 

ROUTE(502,"Yard B: 3 Access")
 throwIt(UFM_T9_E__UFM_T10_A)
 closeIt(UFM_T10_E__UFM_T11_A)
 throwIt(UFM_T11_E__UFM_T12_A)
 ROUTE_CAPTION(500,"Thrown")
 ROUTE_CAPTION(501,"Closed")
 ROUTE_CAPTION(502,"Thrown")
 ROUTE_DISABLED(502)
 ROUTE_ACTIVE(501)
 ROUTE_ACTIVE(500)
DONE 

ROUTE(503,"Yard B: 4 Access")
 throwIt(UFM_T9_E__UFM_T10_A)
 closeIt(UFM_T10_E__UFM_T11_A)
 closeIt(UFM_T11_E__UFM_T12_A)
 throwIt(UFM_T12)
 ROUTE_CAPTION(500,"Thrown")
 ROUTE_CAPTION(501,"Closed")
 ROUTE_CAPTION(502,"Closed")
 ROUTE_CAPTION(503,"Thrown")
 ROUTE_CAPTION(504,"Thrown")
 ROUTE_DISABLED(503)
 ROUTE_ACTIVE(504)
 ROUTE_ACTIVE(502)
 ROUTE_ACTIVE(501)
 ROUTE_ACTIVE(500)
DONE

ROUTE(504,"Yard B: 5 Access")
    throwIt(UFM_T9_E__UFM_T10_A)
    closeIt(UFM_T10_E__UFM_T11_A)
    closeIt(UFM_T11_E__UFM_T12_A)
    closeIt(UFM_T12)
    ROUTE_CAPTION(500,"Thrown")
    ROUTE_CAPTION(501,"Closed")
    ROUTE_CAPTION(502,"Closed")
    ROUTE_CAPTION(503,"Closed")
    ROUTE_CAPTION(504,"Closed")
    ROUTE_DISABLED(504)
    ROUTE_ACTIVE(503)
    ROUTE_ACTIVE(502)
    ROUTE_ACTIVE(501)
    ROUTE_ACTIVE(500)
DONE

ROUTE(505,"Yard B: 1 Exit")
    closeIt(UFM_T13_E__UFM_T14_A)
    ROUTE_CAPTION(505,"Closed")
DONE

ROUTE(506,"Yard B: 2 Exit")
    throwIt(UFM_T13_E__UFM_T14_A)
    throwIt(UFM_T14_E__UFM_T15_A)
    ROUTE_CAPTION(505,"Thrown")
    ROUTE_CAPTION(506,"Thrown")
DONE

ROUTE(507,"Yard B: 3 Exit")
    throwIt(UFM_T13_E__UFM_T14_A)
    closeIt(UFM_T14_E__UFM_T15_A)
    throwIt(UFM_T15_E__UFM_T16_A)
    ROUTE_CAPTION(505,"Thrown")
    ROUTE_CAPTION(506,"Closed")
    ROUTE_CAPTION(507,"Thrown")
DONE

ROUTE(508,"Yard B: 4 Exit")
    throwIt(UFM_T13_E__UFM_T14_A)
    closeIt(UFM_T14_E__UFM_T15_A)
    closeIt(UFM_T15_E__UFM_T16_A)
    closeIt(UFM_T16_E)
    ROUTE_CAPTION(505,"Thrown")
    ROUTE_CAPTION(506,"Closed")
    ROUTE_CAPTION(507,"Closed")
    ROUTE_CAPTION(508,"Closed")
    ROUTE_CAPTION(509,"Closed")
DONE

ROUTE(509,"Yard B: 5 Exit")
    throwIt(UFM_T13_E__UFM_T14_A)
    closeIt(UFM_T14_E__UFM_T15_A)
    closeIt(UFM_T15_E__UFM_T16_A)
    throwIt(UFM_T16_E)
    ROUTE_CAPTION(505,"Thrown")
    ROUTE_CAPTION(506,"Closed")
    ROUTE_CAPTION(507,"Closed")
    ROUTE_CAPTION(508,"Thrown")
    ROUTE_CAPTION(509,"Thrown")
DONE