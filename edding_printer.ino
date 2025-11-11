/*
      Homemade Plotter Painting Device
      (C) 2025 Martin Grabsch
      contact me: martin.grabsch@gmail.com
      or visit my blog: https://ljupkamartin.blogspot.com
*/
#include <Stepper.h>
//#include <LedControl.h>
//#include <IRremote.h>
//#include <LiquidCrystal.h> 
#include <Servo.h>
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

#define STEPS 250
#define WALZE_STEPS 20

// set the speed in rpm
#define MOTOR_RPM 5
#define MAX_OUTPUT_LENGTH 102400

Stepper stepper(STEPS, 4, 6, 5, 7);
Stepper walze(STEPS, 1, 13, 11, 12);


// insert your images bitmap data here (0 is black and 1 is white)
const char graphic1[] PROGMEM = {"11110000111");
const char graphic2[] PROGMEM = {"111111"};


int motorSpeed = 95;
int stepSpeed = 250;
int stepsToPaper = 20;
int motorStepsCounter = 0;

Servo servo;
int penPositionInitial = 90;
int penPositionActive =  152;
int penPositionDeactive =  130;
int penPositionSide =  90;
int penPosition = 90;
int lineLength = 391;
int lineBackLength = lineLength-290;
int outputIndex = 0;

boolean emergencyStop = false;
ArduinoLEDMatrix matrix;

void setup() {
  Serial.begin(9600);
  matrix.begin();

  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  const char text[] = "";
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText();

  matrix.endDraw();

  delay(2000);
  // put your setup code here, to run once:
  servo.attach(9);
  // drive pen holder to paper
  stepper.setSpeed(motorSpeed);
  stepper.step(-stepsToPaper);

  walze.setSpeed(70);
  //walze.step(5000);
  // flip pen to paper
  //penToReactive();
  //penToDeactive();
}

void loop() {
  // put your main code here, to run repeatedly:
  // execute automatic actions
  if (emergencyStop == false){
    //quadrat();
    
 //   dreieck();
 // paintAlex();
    paintDemo1();
    paintDemo2();
   Serial.println("loop: ");
   Serial.println("loop: ");
  }
  
  //walze.step(500);
}



void penToTarget(){
  if (penPosition < penPositionActive)
  for(penPosition = penPositionInitial; penPosition < penPositionActive; penPosition++)    
  {  
    if (emergencyStop == false){                              
    servo.write(penPosition);           
    delay(5);       
    }
  } 
  if (penPosition > penPositionActive)
  for(penPosition = penPositionInitial; penPosition > penPositionActive; penPosition--)    
  {  
    if (emergencyStop == false){                              
    servo.write(penPosition);           
    delay(5);       
    }
  } 
}

void penToDeactive(){
  if (penPosition < penPositionDeactive)
  for(penPosition = penPositionActive; penPosition < penPositionDeactive; penPosition++)    
  {         
    if (emergencyStop == false){                       
    servo.write(penPosition);           
    delay(7); 
    }      
  } 
  if (penPosition > penPositionDeactive)
  for(penPosition = penPositionActive; penPosition > penPositionDeactive; penPosition--)    
  {    
    if (emergencyStop == false){                            
    servo.write(penPosition);           
    delay(7);  
    }     
  } 
}

void penToReactive(){
  if (penPosition < penPositionActive)
  for(penPosition = penPositionDeactive; penPosition < penPositionActive; penPosition++)    
  { if (emergencyStop == false){                               
      servo.write(penPosition);           
      delay(7);       
    }
  } 
  if (penPosition > penPositionActive)
  for(penPosition = penPositionDeactive; penPosition > penPositionActive; penPosition--)    
  {   
    if (emergencyStop == false){                             
    servo.write(penPosition);           
    delay(7);       
    }
  } 
}

void penToSide(){
  for(penPosition = penPositionActive; penPosition > penPositionSide; penPosition--)    
  {                                
    servo.write(penPosition);           
    delay(50);       
  } 
}

void penToInitial(){
  for(penPosition = penPositionActive; penPosition > penPositionInitial; penPosition--)    
  {     
    if (emergencyStop == false){                                  
    servo.write(penPosition);           
    delay(50);  
    }     
  } 
}

void moveRight(int pixels){
  if (emergencyStop == false){       
  int steps = pixels * 12;
  stepper.step(-steps);
  }
}

void moveLeft(int pixels){
  if (emergencyStop == false){       
  int steps = pixels * 50;
  stepper.step(steps);
  }
}

void rowDown(int rows){
  if (emergencyStop == false){       
  int steps = rows * 25;
  walze.step(-steps);
  }
}

void rowUp(int rows){
  if (emergencyStop == false){       
  int steps = rows * 35;
  walze.step(steps);
  }
}

void prepareUp(){
  penToDeactive();
  int rows = 7;
  if (emergencyStop == false){       
  int steps = rows * 100;
  walze.step(steps);
  }
}

void prepareUp2(){
  int rows = 7;
  if (emergencyStop == false){       
  int steps = rows * 100;
  walze.step(steps);
  }
}

void prepareDown(){
  penToDeactive();
  int rows = 5;
  if (emergencyStop == false){       
  int steps = rows * 100;
  walze.step(-steps);
  }
}


void prepareDown2(){
    int rows = 5;
  if (emergencyStop == false){       
  int steps = rows * 100;
  walze.step(-steps);
  }
}

void dreieck(){
  prepareUp2();
  penToReactive();
  diagonalUp(10);
  prepareDown2();
  prepareDown2();
  diagonalDown(9);
  moveLeft(20);
  penToDeactive();
  emergencyStop=true;
}

// zeichnet ein quadrat am linken rand
void quadrat(){
  moveRight(20);
  prepareUp2();
  penToReactive();
  rowUp(20);
  moveRight(10);
  prepareDown2();
  rowDown(20);
  moveLeft(10);
  penToDeactive();
  moveLeft(20);
  emergencyStop=true;
}

void paintDemo1(){
  
 char buffer[10]; // text anzeige
  Serial.println("start paint1Demo");
  int position = 0;
  int cursorCounter = 0;
  int lineCounter = 0;
  prepareDown();
  prepareDown();
  for (int i=0; i<sizeof(steve1); i++) { 
  char element = pgm_read_word_near(steve1 + i);

  Serial.println(element);
  //checkIR();
  penToDeactive();
  //checkIR();
  moveRight(1);
  //position = position + 1;

//  if (position > 10 && position < 15){
//     penPositionActive =  146;
//  }
//  if (position > 15){
//     penPositionActive =  145;
//  }
//  if (position <=10){
//     penPositionActive =  147;
//  }
//   if (position > 30){
//     penPositionActive =  143;
//  }
//  if (position > 53 && position <= 58){
//     penPositionActive =  140;
//  }
//  if (position > 58 && position <= 69){
//     penPositionActive =  139;
//  }
//  if (position > 69 && position){
//     penPositionActive =  137;
//  }
  //checkIR();
  if (element == '1'){
    delay(5);
  } else {
    penToReactive();
    //penToDeactive();
    //penToReactive();
  }
  cursorCounter = cursorCounter + 1;



  itoa(lineCounter, buffer, 10); // Konvertiert den Integer in einen String (Basis 10)
 matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(buffer);
   matrix.endText();
   
  if (cursorCounter == lineLength){
  // next line
  // move pen to start
  lineCounter++;
  cursorCounter = 0;
  penToDeactive();
  penToDeactive();
  rowDown(1);
  moveLeft(lineBackLength);
  //moveRight(20);
  }
  }
  penToDeactive();
  emergencyStop=false;
}


void paintDemo2(){
  
 char buffer[10]; // text anzeige
  Serial.println("start paint1Demo");
  int position = 0;
  int cursorCounter = 0;
  int lineCounter = 0;
  prepareDown();
  prepareDown();
  for (int i=0; i<sizeof(steve2); i++) { 
  char element = pgm_read_word_near(steve2 + i);

  Serial.println(element);
  //checkIR();
  penToDeactive();
  //checkIR();
  moveRight(1);
  //position = position + 1;

//  if (position > 10 && position < 15){
//     penPositionActive =  146;
//  }
//  if (position > 15){
//     penPositionActive =  145;
//  }
//  if (position <=10){
//     penPositionActive =  147;
//  }
//   if (position > 30){
//     penPositionActive =  143;
//  }
//  if (position > 53 && position <= 58){
//     penPositionActive =  140;
//  }
//  if (position > 58 && position <= 69){
//     penPositionActive =  139;
//  }
//  if (position > 69 && position){
//     penPositionActive =  137;
//  }
  //checkIR();
  if (element == '0'){
    delay(5);
  } else {
    penToReactive();
    //penToDeactive();
    //penToReactive();
  }
  cursorCounter = cursorCounter + 1;



  itoa(lineCounter, buffer, 10); // Konvertiert den Integer in einen String (Basis 10)
 matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(buffer);
   matrix.endText();
   
  if (cursorCounter == lineLength){
  // next line
  // move pen to start
  lineCounter++;
  cursorCounter = 0;
  penToDeactive();
  penToDeactive();
  rowDown(1);
  moveLeft(lineBackLength);
  //moveRight(20);
  }
  }
  penToDeactive();
  emergencyStop=true;
}



void diagonalUp(int steps){
  for (int i=0; i<steps; i++){
  moveRight(1);
  rowUp(3);
  }
}

void diagonalDown(int steps){
  for (int i=0; i<steps; i++){
  moveRight(1);
  rowDown(3);
  }
}

void paintAlex(){
  // letter A
  int moveCounter = 0;
  prepareUp();
  penToReactive();
  for (int i=0; i<7; i++){
  moveCounter++;
  moveRight(1);
  rowUp(5);
  }
  rowDown(5);
  penToReactive();
  for (int i=0; i<8; i++){
  moveCounter++;
  moveRight(1);
  rowDown(5);
  }
  penToDeactive();
  moveLeft(moveCounter);
  moveCounter = 0;

  prepareUp();
  rowUp(15);
  moveRight(2);
  moveCounter = 2;
  penToReactive();
  for (int i=0; i<10; i++){
    moveRight(1);
    moveCounter++;
  }
  penToDeactive();
  penToDeactive();
  prepareDown();
  rowDown(22);
  moveLeft(moveCounter);
  moveCounter = 0;

  // letter L
  // start at position 22
  prepareUp();
  moveRight(22);
  moveCounter = moveCounter + 22;
  penToReactive();
  moveRight(10);
  moveLeft(10);
  rowUp(38);
  penToDeactive();
  prepareDown();
  rowDown(45);
  moveLeft(moveCounter);

  // letter E
  // start at position 35
  moveCounter = 0;
  prepareUp();
  moveRight(35);
  moveCounter = moveCounter + 35;
  penToReactive();
  moveRight(10);
  moveLeft(10);
  rowUp(35);
  rowDown(24);
  moveRight(10);
  moveLeft(10);
  rowUp(26);
  moveRight(10);
  moveLeft(10);
  penToDeactive();
  prepareDown();
  rowDown(43);
  moveLeft(moveCounter);

  //  letter X at position 47
  moveLeft(5);
  moveRight(52);
  moveCounter = moveCounter + 50;
  moveCounter = 0;
  prepareUp();
  penToReactive();
  for (int i=0; i<8; i++){
  moveCounter++;
  moveRight(1);
  rowUp(5);
  }
  penToDeactive();
  moveLeft(moveCounter);
  moveCounter = 0;
  prepareDown();
  penToReactive();
  for (int i=0; i<10; i++){
  moveCounter++;
  moveRight(1);
  rowDown(5);
  }
  penToDeactive();
  moveLeft(moveCounter);
  moveLeft(59);
  
  emergencyStop = true;
  }


 
