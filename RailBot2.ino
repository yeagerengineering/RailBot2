/*
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
//#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <SD.h>

//Pin definitions
//Digital
#define SD_CS 24
#define RF_CS 22
#define RF_CSN 23
<<<<<<< HEAD

#define MOTOR_2 25
#define MOTOR_1 26
#define MOTOR_EN 13
#define MAX_SPEED 240
=======
#define MOTOR_1 25
#define MOTOR_2 26

//Analog
#define MOTOR_EN 15

//Other definitions
#define MAX_SPEED 255
>>>>>>> ab7fbbb96b7a35d5052d3733bbe5005d823f4da0

//Global Variables
const uint64_t pipe = 0xF0F0F0F0D2LL; // Define the transmit pipe
long count;
long countIncrement;
<<<<<<< HEAD
long loopCount;

/*-----( Declare objects )-----*/
RF24 radio(RF_CS,RF_CSN); // Create a Radio

//play with stop condition
void move (int dir) {
=======
RF24 radio(RF_CS,RF_CSN); // Create a Radio




  
 //Set up all required I/O and global variables
void setup()   /****** SETUP: RUNS ONCE ******/
  {
    //115200 baud for laser
    Serial.begin(115200);
  
  
    //Initialize the SD card
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
    analogWrite(MOTOR_EN, 0);
  
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
     digitalWrite(MOTOR_1, LOW);
     digitalWrite(MOTOR_2, HIGH);
  } else {
      digitalWrite(MOTOR_1, HIGH);
      digitalWrite(MOTOR_2, LOW);
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
   analogWrite(MOTOR_EN, motorSpeed);
   
       /*
=======
     //Speed down in the exact opposite fashion as above
     while (count < (currentCount + countIncrement)) {
      
>>>>>>> ab7fbbb96b7a35d5052d3733bbe5005d823f4da0
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
  
<<<<<<< HEAD
  while ((count < currentCount + countIncrement - 5)){
    delay(1);
  }
  
  Serial.println("Braking");

    if (dir == 1) {
      digitalWrite(MOTOR_1, HIGH);
    } else {
       digitalWrite(MOTOR_1, LOW);
     }
     
=======
    //Cause the H-bridge to brake the motor
    digitalWrite(MOTOR_1, LOW);
>>>>>>> ab7fbbb96b7a35d5052d3733bbe5005d823f4da0
    analogWrite(MOTOR_EN, 255);
    
    delay(50);
    
    //Set motor back to the forward direction and disable it
    analogWrite(MOTOR_EN, 0);
<<<<<<< HEAD
    
    if (dir == 1) {
      digitalWrite(MOTOR_1, LOW);
    } else {
      digitalWrite(MOTOR_1, HIGH);   
    }
   
   Serial.print(count - currentCount);
=======
    digitalWrite(MOTOR_1, HIGH);   
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


=======
}  
>>>>>>> ab7fbbb96b7a35d5052d3733bbe5005d823f4da0

//ISR for the rotary encoder
//Increments the counter variable by 1 every time it is triggered on both the rising
//and falling edge of the signal. This translates into 16 interrupts per rotation of the 
//disc. With a 1 5/8 diameter wheel, this equals 0.38" per interrupt
void countInt() {
  count++;
<<<<<<< HEAD
 // Serial.print("Count = ");
 //Serial.println(count);
=======
  
  //For testing only
  Serial.print("Count = ");
  Serial.println(count);
>>>>>>> ab7fbbb96b7a35d5052d3733bbe5005d823f4da0
}


