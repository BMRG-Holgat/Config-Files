

/*
   As posted on web page - uses modified board
  DCC Booster using the 43 amp H-Bridge from eBay & Amazon
*/
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;
#include<EEPROM.h>
int LED = 13; // LED to blink when DCC packets are sent in loop
int PowerOn = 3; // pin to turn booster on/off
int Pot1 = 1; // max current pot
int Pot2 = 2; // max temperature pot
float PotReading = 0;
float TmpPotReading = 0;
int CurrentPin = 0;
int CurrentPinReading = 0;
int SetPotFlag = 0;
float version = 3.4;
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR    0x27 // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
LiquidCrystal_I2C  lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);
unsigned long time;
unsigned long now;
long cAverage = 0;
int avgTimes = 400;
int lastAverage = 0;
int resetFlag = 0;
float percentage = 0;
int temp1 = 0;
float tempC = 0;
int CurrentAdjustValue = 300; // adjust based on current Scale resistor value
void setup() {
  delay(500);
  pinMode(LED, OUTPUT);
  pinMode(PowerOn, OUTPUT );
  lcd.begin (16, 2); //  LCD is 16 characters x 2 lines
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);  // Switch on the backlight
  lcd.home (); // go home
  Serial.begin (115200);
  lcd.setCursor(0, 0);
  lcd.print("DCC Booster");
  lcd.setCursor(0, 1);
  lcd.print("5-05-21 - v");
  lcd.print(version, 1);
  Serial.print("5-09-2021  version  ");  Serial.println(version, 1);
  delay(1000);
  lcd.clear();
  delay(500);
  now = millis();
  Serial.print("Locating devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();
  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(insideThermometer, 9);
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC);
  Serial.println();
}
// NOTE:  about 0.014 amps / digit of reading with 10K resistor on sense line
void loop() {
  sensors.requestTemperatures(); // Send the command to get temperatures
  printTemperature(insideThermometer); // Use a simple function to print out the data
  PotReading = analogRead(Pot1);
  PotReading = PotReading / 100;
  TmpPotReading = analogRead(Pot2);
  TmpPotReading = TmpPotReading / 10;
  lcd.setCursor(0, 1);
  lcd.print("TMP");
  lcd.print (DallasTemperature::toFahrenheit(tempC), 0); // Converts tempC to Fahrenheit
  int temptemp = (DallasTemperature::toFahrenheit(tempC));
  lcd.print("/");
  lcd.print(TmpPotReading + 100, 0);
  lcd.print((char)223);
  lcd.print(" ");
  if (temptemp > TmpPotReading + 100) {
    Serial.println("TEMPERATURE FAULT ! ! !");
    lcd.setCursor(0, 1);     lcd.print("T FAULT!");
  }
  lcd.setCursor(8, 0);
  lcd.print("MaxA=");
  lcd.print(PotReading, 1);
  showPercentage();
  resetFlag++;
  if (resetFlag >= 100) {
    resetFlag = 0;
  }
  cAverage = 0;
  for (int xx = 0; xx < avgTimes ; xx++) {
    //CurrentPinReading = analogRead(CurrentPin);
    if (CurrentPinReading >= 1000) {
      Serial.print("Value = "); Serial.print(CurrentPinReading);
      Serial.println("   STOPPPPPPPPPPPPPPPPPPPPPPING");
      turnPowerOff();
    }
    CurrentPinReading = analogRead(CurrentPin);
    cAverage = cAverage + CurrentPinReading;
  }
  CurrentPinReading = cAverage / avgTimes;
  Serial.print("raw current ");  Serial.print(CurrentPinReading);
  turnPowerOn();
  lastAverage = CurrentPinReading; // keep for compare & print
  Serial.print("   Current = ");   Serial.println(CurrentPinReading - CurrentAdjustValue); // gives near zero with filter & 100K pull down
}  //END LOOP
void showPercentage() {
  percentage = (CurrentPinReading - CurrentAdjustValue ) / PotReading; // was 0.014
  percentage = percentage * 2;
  if (percentage < -0) {
    percentage = 0;
  }
  if (millis() - now >= 500)   // only update LCD every 1/2 second to limit flicker
  {
    lcd.setCursor(11, 1);
    lcd.print(percentage, 1);
    lcd.print("%  ");
    now = millis();
  }
  if (percentage > 90) turnPowerOff();
}
void turnPowerOff() {
  digitalWrite(PowerOn, LOW);
  lcd.setCursor(0, 0);
  lcd.print("OFF-5sec");
  lcd.print("OFF");
  delay(35000);
  turnPowerOn();
  lcd.setCursor(0, 0);
  lcd.print("               ");
}
void turnPowerOn() {
  digitalWrite(PowerOn, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("PWR On");
}
void printTemperature(DeviceAddress deviceAddress) {
  tempC = sensors.getTempC(deviceAddress);
  if (tempC == DEVICE_DISCONNECTED_C)
  {
    Serial.println("Error: Could not read temperature data");
    return;
  }
  Serial.print("Temp C: "); Serial.print(tempC); Serial.print(" Temp F: "); Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
}
// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
