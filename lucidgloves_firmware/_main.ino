
// CITATION! ALL THE FIRMWARE IS HEAVILY BASED OFF OF LUCIDGLOVES FIRMWARE BY LUCIDVRTECH - FARIS FAKHOURI
#define ALWAYS_CALIBRATING CALIBRATION_LOOPS == -1

#define CALIB_OVERRIDE false
#if USING_CALIB_PIN && COMMUNICATION == COMM_SERIAL && PIN_CALIB == 0 && !CALIB_OVERRIDE
  #error "You can't set your calibration pin to 0 over usb. You can calibrate with the BOOT button when using bluetooth only. Set CalibOverride to true to override this."
#endif

ICommunication* comm;
int loops = 0;
void setup() {
  #if COMMUNICATION == COMM_SERIAL
    comm = new SerialCommunication();
  #elif COMMUNICATION == COMM_BTSERIAL
    comm = new BTSerialCommunication();
  #endif  
  comm->start();

  setupInputs();

  #if USING_FORCE_FEEDBACK
    setupServoHaptics();  
    setupVibrationMotors(); // setting up vibration motors
  #endif
  
}

void loop() {
  if (comm->isOpen()){
    #if USING_CALIB_PIN
    bool calibButton = getButton(PIN_CALIB) != INVERT_CALIB;
    if (calibButton)
      loops = 0;
    #else
    bool calibButton = false;
    #endif
    
    bool calibrate = false;
    if (loops < CALIBRATION_LOOPS || ALWAYS_CALIBRATING){
      calibrate = true;
      loops++;
    }
    
    int* fingerPos = getFingerPositions(calibrate, calibButton);
    
  

    comm->output(
    encode(fingerPos,
           0,    // dummy joyX
           0,    // dummy joyY
           false,// joyClick
           false,// trigger
           false,// A
           false,// B
           false,// grab
           false,// pinch
           calibButton,
           false // menu
    )
  );

  

#if USING_FORCE_FEEDBACK
  // 1) get live tracking of glove position (0–1000)
  int mirrorLimits[5];
  for (int i = 0; i < 5; i++) {
    mirrorLimits[i] = fingerPos[i] * 1000 / ANALOG_MAX;
  }

  // 2) define per-finger control pins
  struct { byte pin; int idx; } btnMap[5] = {
    { PIN_LIMIT_THUMB_BTN,  THUMB_IND  },
    { PIN_LIMIT_INDEX_BTN,  INDEX_IND  },
    { PIN_LIMIT_MIDDLE_BTN, MIDDLE_IND },
    { PIN_LIMIT_RING_BTN,   RING_IND   },
    { PIN_LIMIT_PINKY_BTN,  PINKY_IND  }
  };

  // 3) determine haptic behavior for each finger
  int hapticLimits[5];
  for (int j = 0; j < 5; j++) {
    int i = btnMap[j].idx;
    bool pressed = getButton(btnMap[j].pin);
    if (pressed) {
      // While pressed, lock the glove at the current flexion (prevent closing more)
      hapticLimits[i] = 1000 - mirrorLimits[i];
    } else {
      // When released, return glove to "open" (fully relaxed)
      hapticLimits[i] = 0;  // or 1000 if your servos are reversed
    }
  }

  // 4) apply behavior
  writeServoHaptics(hapticLimits);   // Glove feedback
  writeHandServos(mirrorLimits);     // Robot hand tracking

  // Vibration Motors and Intensity: Hopefully the implementation works lol 
  int vibeIntensity = 0;
  for (int i =0; i < 5; i++) {
    if (hapticLimits[i] > 0) {
      vibeIntensity = 100; // If the motor is very strong amke it like from (80 - 100 - 120 - 180), 100 good test start 
      break;
    }
  }
  writeVibrationMotor(vibeIntensity);
  
  
#endif

    delay(LOOP_TIME);
  }
}
