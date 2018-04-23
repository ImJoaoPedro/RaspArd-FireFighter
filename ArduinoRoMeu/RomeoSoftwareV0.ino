#define Fan 8    //define driver pins

void setup()
{
  pinMode(Fan,OUTPUT);
  Serial.begin(9600);    //Baudrate: 9600
}                          
void loop() 
{ 
    analogWrite(Fan, 0);
}
