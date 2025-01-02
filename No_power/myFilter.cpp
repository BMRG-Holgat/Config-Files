//  myFilter.cpp  to enable use of DCC accessory commands from JMRI Lights table to DCC++EX pins/vpins
//                -- note the overlap in DCC addresses 

/* Kept now on github https://github.com/BMRG-Holgat/Config-Files.git
*/
//  updated to remove accessory status in <s> command
//  <c> reports pincounts for analog pins A2, A3, A4, A5

#include "Arduino.h"
#include "DCC.h"          \\ 4 lines added with <s> cmd
#include "DCCWaveform.h"
#include "GITHUB_SHA.h"
#include "version.h"
#include "IODevice.h"
void myFilter(Print * stream, byte & opcode, byte & paramCount, int16_t p[]) {

    int adr;
    byte subadr;
    byte id;
    byte activate;

  (void)stream;  // prevent compiler warning about unused params

//  converting <a adr subadr iFlag> to EXRAIL VPIN SET/RESET

    if (opcode=='a' ) {  // this filter will change <a> cmds with lin adr - see switch-case
      // this 'if' section is a partial repeat of the code in DCCESParser.cpp
      //  -- to convert linear address into adr subadr
      if (paramCount==2) { // <a LINEARADDRESS ACTIVATE>
          adr=(p[0] - 1) / 4 + 1;
          subadr=(p[0] - 1)  % 4;
          activate=p[1];        
      } else  { // <a ADDRESS SUBADDRESS ACTIVATE>
          adr=p[0];
          subadr=p[1];
          activate=p[2];        
      } 

      id=(adr -1)*4; // change adr subadr back into lin adr
      id=id+subadr+1;

      switch (id)
      {
      case 22 ... 49:
      case 164 ... 195:  
         IODevice::write(id, activate);   // this does the EXRAIL SET/RESET
         opcode = '\0';
         DIAG(F("turn a %d %d %d into new-Z %d %d"), adr, subadr, activate, id, activate);
         break;

      default:
         DIAG(F("retain a %d %d %d linearID %d"),  adr, subadr, activate, id);
       }
      // DIAG(F("opcode % %d %d %d "), opcode,  adr, subadr, activate);
      //  opcode=0 will fall through to the parser and let it handle it
    }
//  ===== end of opcode 'a'

    if (opcode=='s' ) {  // this filter will change <s> cmd to remove the status for accessories
      //  StringFormatter::send(stream, F("<p%d>\n"), DCCWaveform::mainTrack.getPowerMode() == POWERMODE::ON);
        StringFormatter::send(stream, F("<iDCC-EX V-%S / %S / %S G-%S>\n"), F(VERSION), F(ARDUINO_TYPE), DCC::getMotorShieldName(), F(GITHUB_SHA));
        opcode = '\0';
    }
//  ===== end of opcode 's'

    if (opcode=='c' ) {
//      DIAG(F("A2 %d"), IODevice::readAnalogue(56));
//      DIAG(F("A3 %d"), IODevice::readAnalogue(57));
//      DIAG(F("A4 %d"), IODevice::readAnalogue(58));
//      DIAG(F("A5 %d"), IODevice::readAnalogue(59));
      DIAG(F("A2-A5 %d %d %d %d"), IODevice::readAnalogue(56), IODevice::readAnalogue(57), IODevice::readAnalogue(58), IODevice::readAnalogue(59));

        opcode = '\0';
    }
//  ===== end of opcode 'c'
    
}  // end of myFilter