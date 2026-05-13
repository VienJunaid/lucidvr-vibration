
// CITATION! ALL THE FIRMWARE IS HEAVILY BASED OFF OF LUCIDGLOVES FIRMWARE BY LUCIDVRTECH - FARIS FAKHOURI

#if USING_FORCE_FEEDBACK

#if defined(ESP32)
  #include "ESP32Servo.h"
#else
  #include "Servo.h"
#endif

Servo pinkyServo;
Servo ringServo;
Servo middleServo;
Servo indexServo;
Servo thumbServo;

Servo pinkyHandServo;
Servo ringHandServo;
Servo middleHandServo;
Servo indexHandServo;
Servo thumbHandServo;


void setupServoHaptics(){
  pinkyServo.attach(PIN_PINKY_MOTOR);
  ringServo.attach(PIN_RING_MOTOR);
  middleServo.attach(PIN_MIDDLE_MOTOR);
  indexServo.attach(PIN_INDEX_MOTOR);
  thumbServo.attach(PIN_THUMB_MOTOR);


  pinkyHandServo.attach(PIN_PINKY_HAND_MOTOR);
  ringHandServo.attach(PIN_RING_HAND_MOTOR);
  middleHandServo.attach(PIN_MIDDLE_HAND_MOTOR);
  indexHandServo.attach(PIN_INDEX_HAND_MOTOR);
  thumbHandServo.attach(PIN_THUMB_HAND_MOTOR);

  pinkyServo.write(0);
  ringServo.write(0);
  middleServo.write(0);
  indexServo.write(0);
  thumbServo.write(0);
}

//static scaling, maps to entire range of servo
void scaleLimits(int* hapticLimits, float* scaledLimits){
  for (int i = 0; i < 5; i++){
    scaledLimits[i] = 180.0f - hapticLimits[i] / 1000.0f * 180.0f;
  }
}

//dynamic scaling, maps to the limits calibrated from your finger
void dynScaleLimits(int* hapticLimits, float* scaledLimits){
  //will be refactored to take min and max as an argument

  /* this implementation of dynamic scaling relies on the assumption 
   * that the servo reaches 2/3 of the potentiometer's range, 
   * and that 0 degrees is geared to the start of the potentiometer.
   * Different hardware types may need to handle dynamic scaling differently.
   */
  for (int i = 0; i < sizeof(hapticLimits); i++){
    scaledLimits[i] = hapticLimits[i] / 1000.0f * 180.0f;
  }
}

void writeServoHaptics(int* hapticLimits){
  float scaledLimits[5];
  scaleLimits(hapticLimits, scaledLimits);
  if(hapticLimits[0] >= 0) thumbServo.write(scaledLimits[0]);
  if(hapticLimits[1] >= 0) indexServo.write(scaledLimits[1]);
  if(hapticLimits[2] >= 0) middleServo.write(scaledLimits[2]);
  if(hapticLimits[3] >= 0) ringServo.write(scaledLimits[3]);
  if(hapticLimits[4] >= 0) pinkyServo.write(scaledLimits[4]);
}

void writeHandServos(int* mirrorLimits) {
  float scaled[5];
  scaleLimits(mirrorLimits, scaled);
  if (mirrorLimits[0] >= 0) thumbHandServo.write(scaled[0]);
  if (mirrorLimits[1] >= 0) indexHandServo.write(scaled[1]);
  if (mirrorLimits[2] >= 0) middleHandServo.write(scaled[2]);
  if (mirrorLimits[3] >= 0) ringHandServo.write(scaled[3]);
  if (mirrorLimits[4] >= 0) pinkyHandServo.write(scaled[4]);
}


// Vibration motor software (3/12/2026)
void setupVibrationMotors() {
  pinMode(PIN_VIB_MAIN, OUTPUT);
}

// Vibration Motor Write: Use PWM/LEDC 
/*
  NOTE: you usually can't drive a vibration motor directly from an ESP32 GPIO pin
  May need a transistor or MOSFET
*/
void writeVibrationMotor(int intensity) {
  analogWrite(PIN_VIB_MAIN, intensity);
}




#endif
