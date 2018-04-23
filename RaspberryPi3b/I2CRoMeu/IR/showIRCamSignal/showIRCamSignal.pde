
import processing.serial.*;

int lf = 10;    // Linefeed in ASCII
String myString = null;
Serial myPort;  // The serial port

void setup() {
  // List all the available serial ports
  println(Serial.list()[2]);
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[2], 9600);
  myPort.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  myString = myPort.readStringUntil(lf);
  myString = null;
  size(800,800);
  //frameRate(30);
}

void draw() {
  background(77);
  //while (myPort.available() > 0) {
    myString = myPort.readStringUntil(lf);
    if (myString != null) {
      int[] output = int (split(myString, ','));
      int xx = 1023;
      int yy = 1023;
      int ww = 1023;
      int zz = 1023;
      int xxx = 1023;
      int yyy = 1023;
      int www = 1023;
      int zzz = 1023;
      println(myString); // display the incoming string
      try {
        xx = output[0];
        yy = output[1];
        
        ww = output[2];
        zz = output[3];
        
        xxx = output[4];
        yyy = output[5];
        
        www = output[6];
        zzz = output[7];
      } catch (ArrayIndexOutOfBoundsException e) {
        e.printStackTrace();
      }
      ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
      fill(255, 0, 0);  // Set fill to white
      ellipse(xx, yy, 20, 20);
      ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
      fill(0, 255, 0);  // Set fill to white
      ellipse(ww, zz, 20, 20);
      
      ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
      fill(0, 0, 255);  // Set fill to white
      ellipse(xxx, yyy, 20, 20);
      ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
      fill(255);  // Set fill to white
      ellipse(www, zzz, 20, 20);

    }
}
