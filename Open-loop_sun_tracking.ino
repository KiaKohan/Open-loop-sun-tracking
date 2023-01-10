#include <Adafruit_ADS1X15.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Time.h>
#include <Wire.h>
#include "RTClib.h"
#include <TimeLib.h>
#include <Stepper.h>
#include <SPI.h>
#include <SD.h>
#include <OneWire.h>
#include <DallasTemperature.h>

Adafruit_ADS1115 ads1115;

const int stepsPerRevolution = 6400; 
const int chipSelect = 53;

File dataFile;
// initialize the stepper library on pins 8 through 11:
Stepper StepperDown(stepsPerRevolution, 4,5);
Stepper StepperUp(stepsPerRevolution, 2,3);
#define ONE_WIRE_BUS 22
#define RELAY1  32
#define RELAY2  34
#define RELAY3  36
#define RELAY4  38
#define RELAY5  40
#define RELAY6  37
#define RELAY7  35
#define RELAY8  33
#define RELAY9  39
RTC_DS1307 rtc;
#define ONE_WIRE_BUS 22

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
OneWire oneWire(ONE_WIRE_BUS);


// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
uint8_t sensor4[8] = { 0x28, 0xAA, 0xB2, 0x58, 0x4A, 0x14, 0x01, 0x57 };
uint8_t sensor33[8] = { 0x28, 0xAA, 0x06, 0xCA, 0x4A, 0x14, 0x01, 0xE1 };
uint8_t sensor5[8] = { 0x28, 0xAA, 0x5E, 0xC4, 0x4A, 0x14, 0x01, 0x5F };
uint8_t sensor35[8] = { 0x28, 0x92, 0x9E, 0x45, 0x92, 0x07, 0x02, 0x00 };
uint8_t sensor34[8] = { 0x28, 0x50, 0x3C, 0x79, 0xA2, 0x00, 0x03, 0xF5 };
uint8_t sensor8[8] = { 0x28, 0x17, 0x09, 0x45, 0x92, 0x0D, 0x02, 0x00 };
uint8_t sensor7[8] = { 0x28, 0xAA, 0x30, 0x50, 0x4B, 0x14, 0x01, 0xA8 };
uint8_t sensor6[8] = { 0x28, 0xAA, 0x9A, 0x94, 0x4A, 0x14, 0x01, 0xBA };
uint8_t sensor9[8] = { 0x28, 0x2E, 0x86, 0x45, 0x92, 0x07, 0x02, 0x38 };

void setup() {
  Serial.begin(9600);
  sensors.begin();
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(RELAY5, OUTPUT);
  pinMode(RELAY6, OUTPUT);
  pinMode(RELAY7, OUTPUT);
  pinMode(RELAY8, OUTPUT);
  pinMode(RELAY9, OUTPUT);
  StepperDown.setSpeed(40);
  StepperUp.setSpeed(10);
  ads1115.setGain(GAIN_TWOTHIRDS);
  // initialize the serial port:

  while (!Serial); // for Leonardo/Micro/Zero

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
     //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to`
  // output, even if you don't use it:
  pinMode(SS, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1) ;
  }
  Serial.println("card initialized.");
  
  // Open up the file we're going to log to!
  dataFile = SD.open("18june.txt", FILE_WRITE);
  if (! dataFile) {
    Serial.println("error opening datalog.txt");
    // Wait forever since we cant write data
    while (1) ;
  }

 Serial.print("Current3");
 Serial.print("\t");
 Serial.print("Voltage3");
 Serial.print("\t");
 Serial.print("Current4");
 Serial.print("\t");
 Serial.print("Voltage4");
 Serial.print("\t");
 Serial.print("Current5");
 Serial.print("\t");
 Serial.print("Voltage5");
 Serial.print("\t");
 Serial.print("Current6");
 Serial.print("\t");
 Serial.print("Voltage6");
 Serial.print("\t");
 Serial.print("Temp33");
 Serial.print("\t");
 Serial.print("Temp34");
 Serial.print("\t");
 Serial.print("Temp35");
 Serial.print("\t");
 Serial.print("Temp4");
 Serial.print("\t");
 Serial.print("Temp5");
 Serial.print("\t");
 Serial.print("Temp6");
 Serial.print("\t");
 Serial.print("Temp7");
 Serial.print("\t");
 Serial.print("Temp8");
 Serial.print("\t");
 Serial.print("Temp9");
 Serial.print("\t");
 Serial.println("Time");
 dataFile.print("Current3");
 dataFile.print("\t");
 dataFile.print("Voltage3");
 dataFile.print("\t");
 dataFile.print("Current4");
 dataFile.print("\t");
 dataFile.print("Voltage4");
 dataFile.print("\t");
 dataFile.print("Current5");
 dataFile.print("\t");
 dataFile.print("Voltage5");
 dataFile.print("\t");
 dataFile.print("Current6");
 dataFile.print("\t");
 dataFile.print("Voltage6");
 dataFile.print("\t");
 dataFile.print("Temp33");
 dataFile.print("\t");
 dataFile.print("Temp34");
 dataFile.print("\t");
 dataFile.print("Temp35");
 dataFile.print("\t");
 dataFile.print("Temp4");
 dataFile.print("\t");
 dataFile.print("Temp5");
 dataFile.print("\t");
 dataFile.print("Temp6");
 dataFile.print("\t");
 dataFile.print("Temp7");
 dataFile.print("\t");
 dataFile.print("Temp8");
 dataFile.print("\t");
 dataFile.print("Temp9");
 dataFile.print("\t");
 dataFile.println("Time");
}
  int Hour, Minute, Second, n, sign, steps1=200, steps2=118;
  double delta, w, Ys, tetha, phi, tetha1=53.85, Ys1=-94.65;
void loop() 
{
  delay(1000);    
  float Current3 = 0;
  float Voltage3 = 0;
  float Current4 = 0;
  float Voltage4 = 0;
  float Current5 = 0;
  float Voltage5 = 0;
  float Current6 = 0;
  float Voltage6 = 0;
  int16_t adc0, adc1, adc2, adc3;
  ads1115.setGain(GAIN_TWOTHIRDS);
  digitalWrite(RELAY1,LOW);
  digitalWrite(RELAY3,LOW);
  digitalWrite(RELAY5,LOW);
  digitalWrite(RELAY7,LOW);
  delay(100);
  digitalWrite(RELAY2,LOW);
  digitalWrite(RELAY4,LOW);
  digitalWrite(RELAY6,LOW);
  digitalWrite(RELAY8,LOW);
  digitalWrite(RELAY9,LOW);
  delay(10000);
 // reading average current
       for(int i = 0; i < 100;)
    {
      adc3 = ads1115.readADC_SingleEnded(0);
      Current3 = Current3 + adc3/32768.000*1.024;
      //if(adc0 !=0)
     // {
        i++;
      //}
      delay(10);

    }
    Current3 = Current3/100.000;
       for(int i = 0; i < 100;)
    {
      adc2 = ads1115.readADC_SingleEnded(1);
      Current4 = Current4 + adc2/32768.000*1.024;
      //if(adc1 !=0)
      //{
        i++;
      //}
      delay(10);

    }
   Current4 = Current4/100.000;
       for(int i = 0; i < 100;)
    {
      adc1 = ads1115.readADC_SingleEnded(2);
      Current5 = Current5 + adc1/32768.000*1.024;
      //if(adc2 !=0)
      //{
        i++;
      //}
      delay(10);
    }
     Current5 = Current5/100.000;
       for(int i = 0; i < 100;)
    {
      adc0 = ads1115.readADC_SingleEnded(3);
      Current6 = Current6 + adc0/32768.000*1.024;
      //if(adc0 !=3)
     // {
        i++;
     // }
      delay(10);
    }
     Current6 = Current6/100.000;
// switching relays to read voltage
  delay(100);
  digitalWrite(RELAY2,HIGH);
  digitalWrite(RELAY4,HIGH);
  digitalWrite(RELAY6,HIGH);
  digitalWrite(RELAY8,HIGH);
  delay(10);
  digitalWrite(RELAY1,LOW);
  digitalWrite(RELAY3,LOW);
  digitalWrite(RELAY5,LOW);
  digitalWrite(RELAY7,LOW);
  digitalWrite(RELAY9,LOW);
  delay(1000);
// reading average voltage
    for(int i = 0; i < 1000;)
    {
      float V = 0;
      V = analogRead(A8);
      Voltage3 = Voltage3 +  V/1024.00 *25.0 ;
      //if (V!=0)
      //{
        i++;
      //}
      delay(1);
    }
     Voltage3 = Voltage3/1000.00;
     for(int i = 0; i < 1000;)
    {
      float V = 0;
      V = analogRead(A9);
      Voltage4 = Voltage4 +  V/1024.00 *25 ;
      //if (V!=0)
      //{
        i++;
      //}
      delay(1);
    }
     Voltage4 = Voltage4/1000.00;
     for(int i = 0; i < 1000;)
    {
      float V = 0;
      V = analogRead(A10);
      Voltage5 = Voltage5 +  V/1024.00 *25 ;
      //if (V!=0)
      //{
        i++;
      //}
      delay(1);
    }
     Voltage5 = Voltage5/1000.00;
     for(int i = 0; i < 1000;)
    {
      float V = 0;
      V = analogRead(A11);
      Voltage6 = Voltage6 +  V/1024.00 *25 ;
      //if (V!=0)
      //{
        i++;
      //}
      delay(1);
    }
     Voltage6 = Voltage6/1000.00;
// reading temperatures and time
    sensors.requestTemperatures();
   float temp33 = sensors.getTempC(sensor33);
   float temp34 = sensors.getTempC(sensor34);
   float temp35 = sensors.getTempC(sensor35);
   float temp4 = sensors.getTempC(sensor4);
   float temp5 = sensors.getTempC(sensor5);
   float temp6 = sensors.getTempC(sensor6);
   float temp7 = sensors.getTempC(sensor7);
   float temp8 = sensors.getTempC(sensor8);
   float temp9 = sensors.getTempC(sensor9);
   DateTime now = rtc.now();
// writing data to file
   Serial.print(Current3,5);
   Serial.print("\t");
   Serial.print(Voltage3,5);
   Serial.print("\t");
   Serial.print(Current4,5);
   Serial.print("\t");
   Serial.print(Voltage4,5);
   Serial.print("\t");
   Serial.print(Current5,5);
   Serial.print("\t");
   Serial.print(Voltage5,5);
   Serial.print("\t");
   Serial.print(Current6,5);
   Serial.print("\t");
   Serial.print(Voltage6,5);
   Serial.print("\t");
   Serial.print(temp33);
   Serial.print("\t");
   Serial.print(temp34);
   Serial.print("\t");
   Serial.print(temp35);
   Serial.print("\t");
   Serial.print(temp4);
   Serial.print("\t");
   Serial.print(temp5);
   Serial.print("\t");
   Serial.print(temp6);
   Serial.print("\t");
   Serial.print(temp7);
   Serial.print("\t");
   Serial.print(temp8);
   Serial.print("\t");
   Serial.print(temp9);
   Serial.print("\t");
   Serial.print(now.hour()); Serial.print(":"); Serial.print(now.minute()); Serial.print(":"); Serial.println(now.second());
   
   dataFile.print(Current3,5);
   dataFile.print("\t");
   dataFile.print(Voltage3,5);
   dataFile.print("\t");
   dataFile.print(Current4,5);
   dataFile.print("\t");
   dataFile.print(Voltage4,5);
   dataFile.print("\t");
   dataFile.print(Current5,5);
   dataFile.print("\t");
   dataFile.print(Voltage5,5);
   dataFile.print("\t");
   dataFile.print(Current6,5);
   dataFile.print("\t");
   dataFile.print(Voltage6,5);
   dataFile.print("\t");
   dataFile.print(temp33);
   dataFile.print("\t");
   dataFile.print(temp34);
   dataFile.print("\t");
   dataFile.print(temp35);
   dataFile.print("\t");
   dataFile.print(temp4);
   dataFile.print("\t");
   dataFile.print(temp5);
   dataFile.print("\t");
   dataFile.print(temp6);
   dataFile.print("\t");
   dataFile.print(temp7);
   dataFile.print("\t");
   dataFile.print(temp8);
   dataFile.print("\t");
    dataFile.print(temp9);
   dataFile.print("\t");
   dataFile.print(now.hour()); dataFile.print(":"); dataFile.print(now.minute()); dataFile.print(":"); dataFile.println(now.second());
   dataFile.flush();
// moving stepper motors every 30 minutes so that panel face toward sun at all time
    if ((now.minute()%30) == 0)
    {
      digitalWrite(RELAY9,HIGH);
      Hour = now.hour();
      Minute = now.minute();
      Second = now.second();
      n = 169;
      delta = ( 23.45 * sin( 360.0 * (284.0+n) /365.0 * 2.0 * 3.14/360.0)) * 2.0 * 3.14/360.0;
      w =(( Hour-13.0 ) * 15.0 + ( Minute-5.0 ) * 15.0/60.0 ) * 2.0 * 3.14/360.0;
      phi = 35.7 * 2.0 * 3.14/360.0;
      tetha = acos(cos(phi)*cos(delta)*cos(w)+sin(phi)*sin(delta));
      if(w>=0) sign = 1;
      if(w<0)  sign = -1;
      Ys = sign*fabs(acos((cos(tetha)*sin(phi)-sin(delta))/(sin(tetha)*cos(phi))));
      tetha = tetha * 360.0/( 2.0*3.14 );
      Ys = Ys * 360.0/( 2.0*3.14 );
      StepperDown.step((Ys-Ys1)*steps1);
      StepperUp.step((tetha-tetha1)*steps2);
      Ys1 = Ys;
      tetha1 = tetha;
      delay(60000);
    } 
}
