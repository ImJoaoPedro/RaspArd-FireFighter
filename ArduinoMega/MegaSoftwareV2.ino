#include <Wire.h>
#define LeftTrigPin 5
#define LeftEchoPin 4
#define RightTrigPin 3
#define RightEchoPin 2
#define LeftLDRPin A0
#define RightLDRPin A1
#define FlameSensorPin A2
#define A_X  A3
#define A_Y  A4

int result[7];

int IRsensorAddress = 0xB0;
//int IRsensorAddress = 0x58;
int slaveAddress;
int ledPin = 13;
boolean ledState = false;
byte data_buf[16];

void Write_2bytes(byte d1, byte d2)
{
    Wire.beginTransmission(slaveAddress);
    Wire.write(d1); Wire.write(d2);
    Wire.endTransmission();
}

void setup()
{
    slaveAddress = IRsensorAddress >> 1;   // This results in 0x21 as the address to pass to TWI
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);      // Set the LED pin as output
    Wire.begin();
    pinMode(LeftTrigPin, OUTPUT);
    pinMode(LeftEchoPin, INPUT);
    pinMode(RightTrigPin, OUTPUT);
    pinMode(RightEchoPin, INPUT);
    pinMode(A_X,INPUT);
    pinMode(A_Y,INPUT);
    // IR sensor initialize
    Write_2bytes(0x30,0x01); delay(10);
    Write_2bytes(0x30,0x08); delay(10);
    Write_2bytes(0x06,0x90); delay(10);
    Write_2bytes(0x08,0xC0); delay(10);
    Write_2bytes(0x1A,0x40); delay(10);
    Write_2bytes(0x33,0x33); delay(10);
    delay(100);
}

void loop()
{
   //out: Right Distance, Left Distance, X flame coordinate, Y flame coordinate, LeftLDRPin,RightLDRPin,FlameSensorPin,Axis X,Axis Y
   String out = "";
   out+= String(getDistance(RightTrigPin,RightEchoPin));out += + ",";
   out+= String(getDistance(LeftTrigPin,LeftEchoPin));out += + ",";
   getCoordinates();
   getAnalogs();

   out+= String(result[1]);out += + ",";
   out+= String(result[2]);out += + ",";
   out+= String(result[3]);out += + ",";
   out+= String(result[4]);out += + ",";
   out+= String(result[5]);out += + ",";
   out+= String(result[6]);out += + ",";
   Serial.println(out);
}

int getDistance(int trigPin, int echoPin){
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if(distance<=0 || distance >= 3000){
    distance = -1;
  }
  return distance;
}

void getCoordinates(){
  int Ix[4];
  int Iy[4];
  int s;
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
    String outString ="";
    for(i=0; i<4; i++)
    {
      if (Ix[i] < 1000)
        outString.concat("");
      if (Ix[i] < 100)
        outString.concat("");
      if (Ix[i] < 10)
        outString.concat("");
      outString.concat( int(Ix[i]) );
      outString.concat(",");
      if (Iy[i] < 1000)
        outString.concat("");
      if (Iy[i] < 100)
        outString.concat("");
      if (Iy[i] < 10)
        outString.concat("");
      outString.concat( int(Iy[i]) );
      if (i<3)
        outString.concat(",");
    }
    outString.concat(",");
    outString.concat(int(analogRead(2)));
    //Serial.println(outString);
    //int output[] = int (strtok(outString,","));

    String input = outString;


    for (int i = input.length(); i > 0 ; i--) {
      if (input.substring(i, i+1) == ",") {
        if(input.substring(0, i).toInt()!=1023){
          result[0] = input.substring(0, i).toInt();
          result[1] = input.substring(i+1).toInt();
        }else{
          result[0] = 0;
          result[1] = 0;
        }
        break;
      }
    }
}

void getAnalogs(){
  int val_x,val_y;
  result[2] = analogRead(LeftLDRPin);
  result[3] = analogRead(RightLDRPin);
  result[4] = analogRead(FlameSensorPin);
   for (int i=0;i<10;i++)
  {
    val_x+=analogRead(A_X);delay(2);
    val_y+=analogRead(A_Y);delay(2);
  }
   result[5] =val_x/10;
   result[6] =val_y/10;
   val_x=0;
   val_y=0;
}
