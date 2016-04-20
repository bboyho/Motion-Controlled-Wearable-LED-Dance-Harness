//MinionAccelerometer.ino
//v1.0
//By: Ho Yun "Bobby" Chan (Worm Tank Crew, Block 1750)
//April 20, 2016
//Sparkfun Electronis Inc.

/*Description: This code will be used to control the 12V LED strips
attached to a dancer's custom strap using an n-channel MOSFET for a
performance with Streetside Studio's bboys/bgirls.

Values calibrated using Earth's gravity when accelerometer at rest.
Depending on what accelerometer is used, change the global variable
calibration_M and calibrationADXL335() for that specific accelerometer. 

-------Accelerometer Mode = 1 -------
Features
1.) xAxis
Standing = LED on
Upside down = LED Blinking

2.) yAxis
On the left or right side= LED off

3.) zAxis
On stomach or back = LED fading */

//Code Inspired By:
//bildr ADXL335Example, by Adam Meyer and bildr.org Team
//[ http://bildr.org/2011/04/sensing-orientation-with-the-adxl335-arduino/ ]
//[ http://bildr.org/2012/03/rfp30n06le-arduino/ ]
//Arduino Fade Example, by David A. Mellis and Tom Igoe
//[ http://www.arduino.cc/en/Tutorial/Fading ]

//set analog read pins
const int xPin = 2;//x=A0
const int yPin = 1;//y=A1
const int zPin = 0;//z=A2

//read the analog values from the accelerometer
int xRead = analogRead(xPin);
int yRead = analogRead(yPin);
int zRead = analogRead(zPin);

//Calibration 
int calibration_M = 1; //this is used to calibrate the different accelerometers, change depending on what you are calibrating
//default calibration values for quick test of the adapter board
int xUp = 605;
int xDown = 411;
int yUp = 607;
int yDown = 409;
int zUp = 610;
int zDown = 425;

//delay for blinking
int t = 50;

//LED
int ledStatus = 13; //on board LED for testing
int ledFade = 11; //pin to control N-channel mosfet and LEDs.

void setup() {
  //for testing, init serial monitor
  Serial.begin(9600);
  Serial.println("Start Reading Accelerometer");

  //function for calibrating accelerometers
  calibrationADXL335();

  // initialize the digital pin as an output.
  pinMode(ledStatus, OUTPUT);
  for (int i = 0; i < 3; i++) {
    //blink 3 times
    digitalWrite(ledStatus, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(50);               // wait for a second
    digitalWrite(ledStatus, LOW);   // turn the LED off by making the voltage LOW
    delay(50);               // wait for a second
  }

  //initialize pin as an output
  pinMode(ledFade, OUTPUT);
}

void loop() {

  //Read accelerometer axes using through the ADC
  //Note: Check description at top for results based on Accelerometer Mode's Features
  xRead = analogRead(xPin);
  Serial.print("Analog xPin (A0) = ");
  Serial.println(xRead);
  yRead = analogRead(yPin);
  Serial.print("Analog yPin (A1) = ");
  Serial.println(yRead);
  zRead = analogRead(zPin);
  Serial.print("Analog zPin (A2) = ");
  Serial.println(zRead);

  //-------Accelerometer Mode = 1 -------
  //X-X-X-X-X-X-X | READ xAxis | X-X-X-X-X-X-X
  //LEDs ON
  if (xRead > xUp) {
    //Note: When standing (xAxis pointing up or slightly tilted), it's ~600-604 at REST
    //           ...Other values are outside of this boundary, therefore it will not affect this case
    digitalWrite(ledFade, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  //LEDs Blinking
  if (xRead < xDown) {
    //Note: When upside down (xAxis pointing down or slightly tilted), it's ~399-411 at REST
    //           ...Other values are outside of this boundary, therefore it will not affect this case
    digitalWrite(ledFade, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(t);               // wait for a a few milliseconds
    digitalWrite(ledFade, LOW);    // turn the LED off by making the voltage LOW
    delay(t);               // wait for a a few milliseconds
  }
  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  //Y-Y-Y-Y-Y-Y-Y | Read yAxis | Y-Y-Y-Y-Y-Y-Y
  //LEDs OFF
  if (yRead > yUp || yRead < yDown ) {
    //Note: When on left side (yAxis), it's ~607-612 at REST
    //Note: When on right side (YAxis), it's ~395-409 at REST
    //           ...Other values are outside of this boundary, therefore it will not affect this case
    digitalWrite(ledFade, LOW);    // turn the LED off by making the voltage LOW
  }
  //yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy

  //Z-Z-Z-Z-Z-Z-Z | read xAxis | Z-Z-Z-Z-Z-Z-Z
  //
  if (zRead > zUp || zRead < zDown) {
    //fadeIn example from Arduino Fade Example Code

    //Note: When on back (zAxis pointing up or tilted), it's ~ 610-618 at REST
    //Note: When on stomach (zAxis pointing down or tilted), it's ~ 410-425 at REST
    //           ...Other values are outside of this boundary, therefore it will not affect this case
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      // sets the value (range from 0 to 255):
      analogWrite(ledFade, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(10);
    }
    //fadeOut
    // fade out from max to min in increments of 5 points:
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      // sets the value (range from 0 to 255):
      analogWrite(ledFade, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(10);
    }
  }
  //zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz

}

void calibrationADXL335() {
  //function to calibrate ADXL335 accelerometers due to manufacturing tolerances
  //read the values sent through the Arduino serial monitor to determine the values 
  //when calibrating. adjust the values accordingly. the values in the brackets are
  //the min/max values used for the condition statements
  if (calibration_M = 1) {
    xUp = 585;      //xRead > xUp, ...~ [585]-607 at REST
    xDown = 436;    //xRead < xDown, it's ~405-[436] at REST
    yUp = 601;      //yRead > yUp, it's ~[601]-615 at REST
    yDown = 419;    //yRead < yDown, it's ~404-[419] at REST
    zUp = 616;      //zRead > zUp, it's ~[616]-642 at REST
    zDown = 440;    //zRead < zDown, it's ~410-[440] at REST
  }
  else {
    //default calibration_M = 0
    //default calibration for quick test of the adapter board
    xUp = 605;    //xRead > xUp, it's~[600]-604 at REST
    xDown = 411;  //xRead < xDown, it's ~399-[411] at REST
    yUp = 607;    //yRead > yUp, it's ~[607]-612 at REST
    yDown = 409;  //yRead < yDown, it's ~395-[409] at REST
    zUp = 610;    //zRead > zUp, it's ~[610]-618 at REST
    zDown = 425;  //zRead < zDown, it's ~ 410-[425] at REST
  }

}

