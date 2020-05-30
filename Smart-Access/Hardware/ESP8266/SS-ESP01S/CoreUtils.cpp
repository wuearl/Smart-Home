/*
 * CoreUtils.cpp
 * Developed by Muhammad Ajmal P
 * Contact me @ ajumalp@gmail.com
 * https://owner.erratums.com
 * Date created: 19-Jan-2019
 */

#include "CoreUtils.h"

/*--------------------------------------------------------------------------------------------------------------------*/
/********************************************** Global Functions Starting *********************************************/
/*--------------------------------------------------------------------------------------------------------------------*/

int writeToMem(int addrStart, String data) {
  int iAddr;
  for (iAddr = addrStart; iAddr < addrStart + data.length(); iAddr++) {
    char chr = data.charAt(iAddr - addrStart);
    EEPROM.write(iAddr, chr);
  }

  EEPROM.write(iAddr, '\r');
  EEPROM.commit();
  delay(100);
  return iAddr;
}

String readFromMem(int wordIndex) {
  String result = "";
  int iCntr = 1;
  boolean bFound = false;

  for (int iAddr = 0; iAddr < EEPROM.length(); iAddr++) {
    char chr = char(EEPROM.read(iAddr));
    bFound = iCntr == wordIndex;
    if (chr == '\r') {
      if (bFound) return result;
      iCntr++;
    } else if (bFound) {
      result += chr;
    }
  }

  return "";
}

/*--------------------------------------------------------------------------------------------------------------------*/
/********************************************** Global Functions Ending ***********************************************/
/*--------------------------------------------------------------------------------------------------------------------*/

EDelay::EDelay() {
  EDelay(0);
}

EDelay::EDelay(unsigned long delayInMilliSec) {
  FDelay = delayInMilliSec;
  FLastMillis = 0;
  FStop = false;
}

unsigned long EDelay::getDelay() {
  return FDelay;
}

void EDelay::setDelay(unsigned long delayInMilliSec) {
  FDelay = delayInMilliSec;
}

bool EDelay::isStopped() {
  return FStop;
}

void EDelay::stop() {
  FStop = true;
}

void EDelay::restart() {
  FLastMillis = millis();
  FStop = false;
}

bool EDelay::canContinue() {
  if (isStopped()) return true;

  if (millis() - FLastMillis < FDelay) return false;
  FLastMillis = millis();

  return true;
}
