#include<stdio.h>
#include <Wire.h>
int IRsensorAddress = 0xB0;
int slaveAddress;
int ledPin = 13, i,s;
int Ix[4],Iy[4];

boolean ledState = false;
byte data_buf[16];
#define AXISPORT 3
#define FANPORT 8 
int valAxis;
int speedPin_M1 = 5;     //M1 Speed Control
int speedPin_M2 = 6;     //M2 Speed Control
int directionPin_M1 = 4;     //M1 Direction Control
int directionPin_M2 = 7;     //M1 Direction Control

void Write_2bytes(byte d1, byte d2)
{
    Wire.beginTransmission(slaveAddress);
    Wire.write(d1); Wire.write(d2);
    Wire.endTransmission();
}

void readAxis(){
    for (int i=0;i<10;i++)
    {
      valAxis+=analogRead(AXISPORT);delay(2);
    }
     valAxis=valAxis/10;    
     Serial.println(valAxis);
}

void readIRCam(){
  ledState = !ledState;
    if (ledState) { digitalWrite(ledPin,HIGH); } else { digitalWrite(ledPin,LOW); }

    //IR sensor read
    Wire.beginTransmission(slaveAddress);
    Wire.write(0x36);
    Wire.endTransmission();

    Wire.requestFrom(slaveAddress, 16);        // Request the 2 byte heading (MSB comes first)
    for (i=0;i<16;i++) { data_buf[i]=0; }
    i=0;
    while(Wire.available() && i < 16) { 
        data_buf[i] = Wire.read();
        i++;
    }
  
    Ix[0] = data_buf[1];
    Iy[0] = data_buf[2];
    s   = data_buf[3];
    Ix[0] += (s & 0x30) <<4;
    Iy[0] += (s & 0xC0) <<2;

    Ix[1] = data_buf[4];
    Iy[1] = data_buf[5];
    s   = data_buf[6];
    Ix[1] += (s & 0x30) <<4;
    Iy[1] += (s & 0xC0) <<2;

    Ix[2] = data_buf[7];
    Iy[2] = data_buf[8];
    s   = data_buf[9];
    Ix[2] += (s & 0x30) <<4;
    Iy[2] += (s & 0xC0) <<2;

    Ix[3] = data_buf[10];
    Iy[3] = data_buf[11];
    s   = data_buf[12];
    Ix[3] += (s & 0x30) <<4;
    Iy[3] += (s & 0xC0) <<2;

    for(i=0; i<4; i++)
    {
      if (Ix[i] < 1000)
        Serial.print("");
      if (Ix[i] < 100)  
        Serial.print("");
      if (Ix[i] < 10)  
        Serial.print("");
      Serial.print( int(Ix[i]) );
      Serial.print(",");
      if (Iy[i] < 1000)
        Serial.print("");
      if (Iy[i] < 100)  
        Serial.print("");
      if (Iy[i] < 10)  
        Serial.print("");
      Serial.print( int(Iy[i]) );
      if (i<3)
        Serial.print(",");
    }
    Serial.println("");
    delay(15);
}

void spinFan(){
  carStop();
  analogWrite(FANPORT, 255);      
  delay(4000); 
  analogWrite(FANPORT, 0);
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

void setup(){
  pinMode(AXISPORT,INPUT);
  pinMode(FANPORT,OUTPUT);
  slaveAddress = IRsensorAddress >> 1;   // This results in 0x21 as the address to pass to TWI
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      // Set the LED pin as output
  Wire.begin();
  // IR sensor initialize
  Write_2bytes(0x30,0x01); delay(10);
  Write_2bytes(0x30,0x08); delay(10);
  Write_2bytes(0x06,0x90); delay(10);
  Write_2bytes(0x08,0xC0); delay(10);
  Write_2bytes(0x1A,0x40); delay(10);
  Write_2bytes(0x33,0x33); delay(10);
  Serial.println("Dude Start:");
}
void loop(){
char val = Serial.read();
char prevVal;
    if(val != -1)
    {
      switch(val)
      {
      case 'w'://Move Forward
        carAdvance(255,255);
        break;
      case 's'://Move Backward
        carBack(255,255);   //move back in max speed
        break;
      case 'a'://Turn Left
        carTurnLeft(100,100);
        break;       
      case 'd'://Turn Right
        carTurnRight(100,100);
        break;
      case 'x':
        carStop();
        break;
      case '1':
        readAxis();
        break;
      case '2':
        readIRCam();
        break;
      case '3':
        spinFan(); // also stops the car
        break;
      }
    }  
    else val = prevVal;  
} 


