#include <ZumoMotors.h>                  // Zumo Motor Library
#include <Pushbutton.h>                  // Push Button Library
#include <QTRSensors.h>                  // Reflectance Sensor Library
#include <ZumoReflectanceSensorArray.h>  // Reflectance Sensor Interpreter Library 

// Orange User LED Define
#define LED 13
 
// This might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1000 // microseconds
  
// These might need to be tuned for different motor types
#define FORWARD_SPEED     200 // 0 is stopped, 400 is full speed

// The Number of unique line sensors
#define NUM_SENSORS 6
 
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12
 

unsigned int  sensor_values [NUM_SENSORS];
unsigned char sensor_digital[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

// Called once at start.
void setup()
{   
  //Serial.begin(9600);
  pinMode(LED, OUTPUT);
  button.waitForButton(); 
}

// After setup() repeat continuosly 
void loop()
{  
  //Read Reflectance Sensors and store in array. 
  sensors.read(sensor_values);
  
  //Serial.println(sensor_values[3]);

  // Convert Analog Values of each sensor to Digital
  for( int i=0; i<NUM_SENSORS; i++){
    if(sensor_values[i] > QTR_THRESHOLD) {
      sensor_digital[i] = 0x01;
    }
    else {
      sensor_digital[i] = 0x00;
    }
  }

  // If any sensor is triggered, Stop.
  if (sensor_digital[0] | sensor_digital[1] | sensor_digital[2] |
      sensor_digital[3] | sensor_digital[4] | sensor_digital[5] )
  {
    pinMode(LED, HIGH);        // Put the Brake Lights On!! 
    motors.setSpeeds(0, 0);    // Stop!! 
    button.waitForButton();    // Wait another button press before continuing.
    pinMode(LED, LOW);         // Brake Lights Off!
  }
  else
  {
    // otherwise, go straight
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
}
