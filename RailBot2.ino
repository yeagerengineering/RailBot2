
/* YourDuinoStarter Example: nRF24L01 Receive Joystick values

 - WHAT IT DOES: Receives data from another transceiver with
   2 Analog values from a Joystick or 2 Potentiometers
   Displays received values on Serial Monitor
 - SEE the comments after "//" on each line below
 - CONNECTIONS: nRF24L01 Modules See:
 http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   
 - V1.00 11/26/13
   Based on examples at http://www.bajdi.com/
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <SD.h>

#define SD_CS 24
#define RF_CS 22
#define RF_CSN 23

#define MOTOR_2 25
#define MOTOR_1 26
#define MOTOR_EN 13
#define MAX_SPEED 240

//NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xF0F0F0F0D2LL; // Define the transmit pipe
long count;
long countIncrement;
long loopCount;

/*-----( Declare objects )-----*/
RF24 radio(RF_CS,RF_CSN); // Create a Radio

//play with stop condition
void move (int dir) {
  
  long currentCount = count;
  
  int motorSpeed = 0;
  
  
  if (dir == 1){
     digitalWrite(MOTOR_1, LOW);
     digitalWrite(MOTOR_2, HIGH);
  } else {
      digitalWrite(MOTOR_1, HIGH);
      digitalWrite(MOTOR_2, LOW);
  }
  
  //Serial.println("Speeding up");
  
   while (count < (currentCount + countIncrement - 20)) {
      
     analogWrite(MOTOR_EN, motorSpeed);
     
     if(motorSpeed + 30 > MAX_SPEED){
       motorSpeed = MAX_SPEED;
     } else {
       motorSpeed+=30;
     }
     delay(300);
 
     }
    

   //Serial.println("Slowing speed.");
   
   motorSpeed = 200;
   analogWrite(MOTOR_EN, motorSpeed);
   
       /*
       analogWrite(MOTOR_EN, motorSpeed);
     
       if (motorSpeed - 15 < 0) {
         motorSpeed = 0;
       } else {
         Serial.println("Slowing down");
         motorSpeed -= 15;
       }
       
       delay(100);
 
     }
     */
 
  //Serial.println("Waiting");
  
  while ((count < currentCount + countIncrement - 5)){
    delay(1);
  }
  
  Serial.println("Braking");

    if (dir == 1) {
      digitalWrite(MOTOR_1, HIGH);
    } else {
       digitalWrite(MOTOR_1, LOW);
     }
     
    analogWrite(MOTOR_EN, 255);
    
    delay(50);
    
    analogWrite(MOTOR_EN, 0);
    
    if (dir == 1) {
      digitalWrite(MOTOR_1, LOW);
    } else {
      digitalWrite(MOTOR_1, HIGH);   
    }
   
   Serial.print(count - currentCount);
  
  return;
  
}

  void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(115200);
  
  Serial.println("Initializing SD card...");
  
  if(SD.begin(SD_CS)){
     Serial.println("SD card initialized successfully.\n");
  }
  
  //Set up rotary encoder interrupt
  count = 0;
  attachInterrupt(2, countInt, CHANGE);
  
  //Set up motor pins
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(MOTOR_EN, OUTPUT);
 
  digitalWrite(MOTOR_1, HIGH);
  digitalWrite(MOTOR_2, LOW);
  digitalWrite(MOTOR_EN, LOW);
  
  //RF Initialization
  printf_begin();
  radio.begin();
  Serial.println("RF Module information:");
  radio.printDetails();
  
  loopCount = 0;
  countIncrement = 50;
  
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{ 
  delay(500);
  
  move(0);
  
  delay(500);
  
  move(1);
  
}//--(end main loop )---



void countInt() {
  count++;
 // Serial.print("Count = ");
 //Serial.println(count);
}

/*-----( Declare User-written Functions )-----*/

//NONE
//*********( THE END )***********



