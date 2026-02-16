// ************* OLED JL Display Track mA Amperage  **************** //
// by Herb Morton    [Ash]                          March 23, 2025 
//    Colin Murdoch  [ColinM] 

//  Inside your config.h file First edit OLED max char rows set to 17
// #define MAX_CHARACTER_ROWS 17

// myAutomation.h
// Reporting power status and mA for each track on the LCD
AUTOSTART DELAY(5000) 
 ROUTE(238, "Resume/Pause JL Display")
 IF(Latch_default)
  IF(Latch_Power) 
    UNLATCH(Latch_Power)
     ROUTE_CAPTION(238, "Paused") ROUTE_INACTIVE(238)
     PRINT("Pause JL Display")
      SCREEN(2, 8, "Track status paused")
      SCREEN(2, 9, "")
      SCREEN(2,10, "")   // several blank lines as needed
      SCREEN(2,11, "")
      SCREEN(2,12, "")
      SCREEN(2,13, "")
      SCREEN(2,14, "")
      SCREEN(2,15, "")
      SCREEN(2,16, "")
    DONE ENDIF
  LATCH(Latch_Power) 
   ROUTE_CAPTION(238, "Running") ROUTE_ACTIVE(238)
    PRINT("Resume JL Display")
   FOLLOW(237)
  SEQUENCE(237)
   PARSE("<JL 2 1>")  // screen 0  start on line 8
    PRINT("\n")
    DELAY(3000)
  IF(Latch_Power) FOLLOW(237) ENDIF
ENDIF
  DONE
// ************ End OLED JL Display Track mA Amperage ************** //