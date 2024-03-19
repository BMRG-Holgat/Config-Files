/* This should be mySetup file for turnouts
*
* Kept now on github https://github.com/BMRG-Holgat/Config-Files.git
*
*/
SETUP("<D DIAG ON>");
SETUP("<0>"); // tracks off at startup
SETUP("<D CMD 1>"); // can be set to ON for testing in the serial monitor
SETUP("<D EXRAIL ON>");
SETUP("<=A MAIN>");
SETUP("<=B MAIN>");
SETUP("<=C NONE>");
SETUP("<=D MAIN>");

//code to test sensors 
/*
for(uint16_t p = 164; p < 180; p++){
   Sensor::create(p, p, 1);
}
*/
// or use an array for specific sensors
/*
uint16_t DIO_vpins[] = {183, 185, 186, 187, 191, 193, 194, 195};
for(uint8_t p = 0; p < sizeof DIO_vpins / sizeof DIO_vpins[0]; p++){
   Sensor::create(DIO_vpins[p], DIO_vpins[p], 1);
}
*/
for(uint16_t p = 566; p < 591; p++){
   Sensor::create(p, p, 1);
}
//uint16_t DIO_vpins[] = {596, 598, 600, 601, 602, 603, 604, 605, 606, 607 608, 609};
//for(uint8_t p = 0; p < sizeof DIO_vpins / sizeof DIO_vpins[0]; p++){
//   Sensor::create(DIO_vpins[p], DIO_vpins[p], 1);
//}
