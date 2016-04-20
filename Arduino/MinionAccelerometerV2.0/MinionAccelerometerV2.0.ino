//MinionAccelerometerV2.0
//v2.0
//By: Ho Yun "Bobby" Chan (Worm Tank Crew, Block 1750)
//April 12, 2016
//Sparkfun Electronis Inc.

/*Description: This code will be used to control the 12V LED strips
attached to a dancer's custom strap using an n-channel MOSFET for a
performance with Streetside Studio's bboys/bgirls.

Values calibrated using Earth's gravity when accelerometer at rest.

-------Accelerometer Mode = 1 -------
1.) xAxis
Standing = LED on
Upside down = LED Blinking

2.) yAxis
On the left or right side= LED off

3.) zAxis
On stomach or back = LED fading */

//Code Inspired By:
//bildr Example, by Adam Meyer and bildr.org Team
//[ http://bildr.org/2011/04/sensing-orientation-with-the-adxl335-arduino/ ]
//Arduino Fade Example, by David A. Mellis and Tom Igoe
//[ http://www.arduino.cc/en/Tutorial/Fading ] 

//set analog read pins
const int xPin = 0;//x=A0
const int yPin = 1;//y=A1
const int zPin = 2;//z=A2

//read the analog values from the accelerometer
int xRead = analogRead(xPin);
int yRead = analogRead(yPin);
int zRead = analogRead(zPin);

//delay for blinking
int t = 50;

//LED
int led = 13; //on board LED for testing
int ledFade = 11;

void setup() {
  //for testing, init serial monitor
  Serial.begin(9600);
  Serial.println("Start Reading Accelerometer");

  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);

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
  if (xRead > 605) {
    //Note: When standing (xAxis pointing up or slightly tilted), it's ~600-604 at REST
    //           ...Other values are outside of this boundary, therefore it will not affect this case
    digitalWrite(ledFade, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  //LEDs Blinking
  if (xRead < 411) {
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
  if (yRead > 607 || yRead < 409 ) {
    //Note: When on left side (yAxis), it's ~607-612 at REST
    //Note: When on right side (YAxis), it's ~395-409 at REST
    //           ...Other values are outside of this boundary, therefore it will not affect this case
    digitalWrite(ledFade, LOW);    // turn the LED off by making the voltage LOW
  }
  //yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy

  //Z-Z-Z-Z-Z-Z-Z | read xAxis | Z-Z-Z-Z-Z-Z-Z
  //
  if (zRead > 610 || zRead < 425) {
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


