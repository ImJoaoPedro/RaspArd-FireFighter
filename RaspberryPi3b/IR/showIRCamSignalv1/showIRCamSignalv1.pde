
import processing.serial.*;
int nbOfHorizontalLines = 20;
int nbOfVerticalLines = 20;

int lf = 10;    // Linefeed in ASCII
String myString = null;
Serial myPort;  // The serial port

boolean[][] rects; // twodimensional array, think rows and columns

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
      int flame = 0;
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
        
        flame = output[8];
        println(output);
      } catch (ArrayIndexOutOfBoundsException e) {
        println("Gone Bananas");
        e.printStackTrace();
      }
      
      background(0);
      stroke(0,255,0);
    
      float distanceBetweenHorizontalLines = (float)height/nbOfHorizontalLines;
      float distanceBetweenVerticalLines = (float)width/nbOfVerticalLines;
    
      for(int i = 0; i < nbOfHorizontalLines; i++)
      {
        line(0, i*distanceBetweenHorizontalLines, width, i*distanceBetweenHorizontalLines);
    
      }
    
      for(int i = 0; i < nbOfVerticalLines; i++)
      {
        line (i*distanceBetweenVerticalLines,0,i*distanceBetweenVerticalLines, height);
      }
      //if (flame >=50){
        ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
        fill(255, 0, 0);  // Set fill to white
        ellipse(xx, yy, 10, 10);
        ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
        fill(0, 255, 0);  // Set fill to white
        ellipse(ww, zz, 10, 10);
        
        ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
        fill(0, 0, 255);  // Set fill to white
        ellipse(xxx, yyy, 10, 10);
        ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
        fill(255);  // Set fill to white
        ellipse(www, zzz, 10, 10);
      //}
    }
}
