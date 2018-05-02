#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define Fan 8    //define driver pins
LiquidCrystal_I2C lcd(0x20,16,2);
int speedPin_M1 = 10;     //M1 Speed Control dir
int speedPin_M2 = 6;     //M2 Speed Control esq
int directionPin_M1 = 9;     //M1 Direction Control
int directionPin_M2 = 7;     //M2 Direction Control

void start(){
  lcd.setCursor(3,0);
  lcd.print("I kill FAIA!");
   lcd.setCursor(2,3);
  lcd.print("ISCTEAM");
}

void carStop(){                 //  Motor Stop
  digitalWrite(speedPin_M2,0); 
  digitalWrite(directionPin_M1,LOW);    
  digitalWrite(speedPin_M1,0);   
  digitalWrite(directionPin_M2,LOW);    
}   

void carBack(int leftSpeed,int rightSpeed){         //Move backward
  analogWrite (speedPin_M2,leftSpeed);              //PWM Speed Control
  digitalWrite(directionPin_M1,HIGH);    
  analogWrite (speedPin_M1,rightSpeed);    
  digitalWrite(directionPin_M2,HIGH);
} 

void carAdvance(int leftSpeed,int rightSpeed){       //Move forward
  analogWrite (speedPin_M2,leftSpeed);
  digitalWrite(directionPin_M1,LOW);   
  analogWrite (speedPin_M1,rightSpeed);    
  digitalWrite(directionPin_M2,LOW);
}

void carTurnLeft(int leftSpeed,int rightSpeed){      //Turn Left
  analogWrite (speedPin_M2,leftSpeed);
  digitalWrite(directionPin_M1,LOW);    
  analogWrite (speedPin_M1,rightSpeed);    
  digitalWrite(directionPin_M2,HIGH);
}
void carTurnRight(int leftSpeed,int rightSpeed){      //Turn Right
  analogWrite (speedPin_M2,leftSpeed);
  digitalWrite(directionPin_M1,HIGH);    
  analogWrite (speedPin_M1,rightSpeed);    
  digitalWrite(directionPin_M2,LOW);
}

void setup()
{
  pinMode(Fan,OUTPUT);
  Serial.begin(9600);    //Baudrate: 9600
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
}                          
void loop() 
{ 
  start();
  analogWrite(Fan, 0);
  
  
  if(Serial.available()){
    char val = Serial.read();
    if(val != -1)
    {
      switch(val)
      {
      case 'w'://Move Forward
        carAdvance(250,250);   //move forward in max speed
        break;
      case 's'://Move Backward
        carBack(250,250);   //move back in max speed
        break;
      case 'a'://Turn Left
        carTurnLeft(250,250);
        break;       
      case 'd'://Turn Right
        carTurnRight(250,250);
        break;
      case 'x':
        carStop();
        break;
      }
    }
     
  }
}  
