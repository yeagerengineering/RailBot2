/*****************************************************************************

    File Overview:
    
    Authors:
    Delivery Date:
    
    File Name:  RailBot.ino
    
 *****************************************************************************
 $LOG$
 *****************************************************************************
 $NOTES$
 *****************************************************************************
 $REFERENCES$
 *****************************************************************************/

/*-----( ARDUINO MEGA2650 PIN CONFIGURATION )-----*/

/* LASER - UNI-T

*/


/* Radio Modules - nRF24L01
  Modules See:
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
   Questions: terry@yourduino.com
*/

/*-----( Import needed libraries )-----*/
#include <SPI.h>       // SPI bus Library
#include <SD.h>        // SD Library
#include "RF24.h"      // RF Module Library
#include "printf.h"    // RF Printf Library
#include "nRF24L01.h"  // RF Module Definitions

/*-----( Pin Definitions )-----*/
// Digital Components
#define SD_CS_P 24         // SD Chip Select (out) => pin24
#define RF_CS_P 22         // RF Chip Select (out) => pin22
#define RF_CSN_P 23        // RF_ (out) => pin23
#define LASER_ON_P = 7;    // Laser on (out) pin+7
#define LASER_OFF_P = 8;   // Laser off (out) => pin8

// Analong Components
#define MOTOR_A_P 25      // PWM A (out) => pin25
#define MOTOR_B_P 26      // PWM B (out) => pin26
#define MOTOR_EN_P 13     // Motor enable => pin13
#define MAX_SPEED 255     // Motor max PWM (count)

/*-----( Global Variables )-----*/
//const uint64_t pipe = 0xF0F0F0F0D2LL; // Define the transmit pipe
long count;                             // Current number of interrupts from encoder
long countIncrement;
long loopCount;

/*-----( Instantiate Radio )-----*/
RF24 radio(RF_CS_P,RF_CSN_P); // Create a Radio

/*
  Setup: Set up all required I/O and global variables
*/
void setup()
  {
    //115200 baud for laser
    Serial.begin(115200);
  
    //Initialize the SD card
    Serial.println("Initializing SD card...");
  
    if(SD.begin(SD_CS_P)){
       Serial.println("SD card initialized successfully.\n");
    }
  
    //Set up rotary encoder interrupt
    count = 0;
    attachInterrupt(2, countInt, CHANGE);
  
    //Set up motor pins
    pinMode(MOTOR_A_P, OUTPUT);
    pinMode(MOTOR_B_P, OUTPUT);
    pinMode(MOTOR_EN_P, OUTPUT);
 
    digitalWrite(MOTOR_A_P, HIGH);
    digitalWrite(MOTOR_B_P, LOW);
    analogWrite(MOTOR_EN_P, 0);
  
    //RF Initialization
    printf_begin();
    radio.begin();
    Serial.println("RF Module information:");
    radio.printDetails();
  
  }//--(end setup )---


//The magic occurs here
void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{ 
  
}//--(end main loop )---


//-- USER FUNCTIONS 

//This function moves the robot the distance represented by the value in
//countIncrement. This variable will be set during the initialization
//based on the increment distance configured by the user before starting the survey.
//The idea of this function is to speed up to MAX_SPEED in a controlled fashion
//instead of instantly going to MAX_SPEED. The motor speed will increase up to a 
//max of MAX_SPEED until it has traversed half the required distance, and then will
//begin to slow back down to a stop for the second half.

//NOTE: play with delay values and while loop conditions once motor is functional
void move () {
>>>>>>> ab7fbbb96b7a35d5052d3733bbe5005d823f4da0
  
  //save the current position
  long currentCount = count;
  
  int motorSpeed = 0;
  
<<<<<<< HEAD
  
  if (dir == 1){
     digitalWrite(MOTOR_A_P, LOW);
     digitalWrite(MOTOR_B_P, HIGH);
  } else {
      digitalWrite(MOTOR_A_P, HIGH);
      digitalWrite(MOTOR_B_P, LOW);
  }
  
  //Serial.println("Speeding up");
  
   while (count < (currentCount + countIncrement - 20)) {
=======
   //speed up until half of the distance is traversed
   while (count < (currentCount + countIncrement / 2)) {
>>>>>>> ab7fbbb96b7a35d5052d3733bbe5005d823f4da0
      
     analogWrite(MOTOR_EN, motorSpeed);
     
     if(motorSpeed + 30 > MAX_SPEED){
       motorSpeed = MAX_SPEED;
     } else {
       motorSpeed+=30;
     }
     delay(300);
 
     }
    

<<<<<<< HEAD
   //Serial.println("Slowing speed.");
   
   motorSpeed = 200;
   analogWrite(MOTOR_EN_P, motorSpeed);
   
       /*
=======
     //Speed down in the exact opposite fashion as above
     while (count < (currentCount + countIncrement)) {
      
>>>>>>> ab7fbbb96b7a35d5052d3733bbe5005d823f4da0
       analogWrite(MOTOR_EN_P, motorSpeed);
     
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
  
<<<<<<< HEAD
  while ((count < currentCount + countIncrement - 5)){
    delay(1);
  }
  
  Serial.println("Braking");

    if (dir == 1) {
      digitalWrite(MOTOR_A_P, HIGH);
    } else {
       digitalWrite(MOTOR_A_P, LOW);
     }
     
=======
    //Cause the H-bridge to brake the motor
    digitalWrite(MOTOR_A_P, LOW);
>>>>>>> ab7fbbb96b7a35d5052d3733bbe5005d823f4da0
    analogWrite(MOTOR_EN_P, 255);
    
    delay(50);
    
    //Set motor back to the forward direction and disable it
    analogWrite(MOTOR_EN_P, 0);
<<<<<<< HEAD
    
    if (dir == 1) {
      digitalWrite(MOTOR_A_P, LOW);
    } else {
      digitalWrite(MOTOR_A_P, HIGH);   
    }
   
   Serial.print(count - currentCount);
=======
    digitalWrite(MOTOR_A_P, HIGH);   
>>>>>>> ab7fbbb96b7a35d5052d3733bbe5005d823f4da0
  
    return;
  
<<<<<<< HEAD
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
  pinMode(MOTOR_A_P, OUTPUT);
  pinMode(MOTOR_B_P, OUTPUT);
  pinMode(MOTOR_EN_P, OUTPUT);
 
  digitalWrite(MOTOR_A_P, HIGH);
  digitalWrite(MOTOR_B_P, LOW);
  digitalWrite(MOTOR_EN_P, LOW);
  
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


=======
}  
>>>>>>> ab7fbbb96b7a35d5052d3733bbe5005d823f4da0

//ISR for the rotary encoder
//Increments the counter variable by 1 every time it is triggered on both the rising
//and falling edge of the signal. This translates into 16 interrupts per rotation of the 
//disc. With a 1 5/8 diameter wheel, this equals 0.38" per interrupt
void countInt(){
  count++;
}


