/*
 * FARIS FAKHOURI VERSION
 * Heavily Based on LucidGloves repo from LucasVRTech. Huge props to him!
 * https://github.com/LucidVR/lucidgloves
 * Edited firmware to work with robotic hand
 */

#include "AdvancedConfig.h"

//This is the configuration file, main structure in _main.ino
//CONFIGURATION SETTINGS:
#define COMMUNICATION COMM_BTSERIAL //Which communication protocol to use COMM_BTSERIAL
//serial over USB
  #define SERIAL_BAUD_RATE 115200
  
//serial over Bluetooth
  #define BTSERIAL_DEVICE_NAME "lucidgloves-right"

//ANALOG INPUT CONFIG
#define FLIP_POTS  false  //Flip values from potentiometers (for fingers!) if they are backwards

//Gesture enables, make false to use button override
#define TRIGGER_GESTURE true
#define GRAB_GESTURE    true
#define PINCH_GESTURE   true

// Vibration motors stuff - MIGHT NEED TO ADJUST
#define PIN_VIB_MAIN 13



//BUTTON INVERT
//If a button registers as pressed when not and vice versa (eg. using normally-closed switches),
//you can invert their behaviour here by setting their line to true.
//If unsure, set to false
#define INVERT_A false
#define INVERT_B false
#define INVERT_JOY false
#define INVERT_MENU false
#define INVERT_CALIB false
//These only apply with gesture button override:
#define INVERT_TRIGGER false
#define INVERT_GRAB false
#define INVERT_PINCH false


//joystick configuration
#define JOYSTICK_BLANK true //make true if not using the joystick
#define JOY_FLIP_X false
#define JOY_FLIP_Y false
#define JOYSTICK_DEADZONE 10 //deadzone in the joystick to prevent drift (in percent)

#define NO_THUMB false //If for some reason you don't want to track the thumb

#define USING_CALIB_PIN true //When PIN_CALIB is shorted (or it's button pushed) it will reset calibration if this is on.

#define USING_FORCE_FEEDBACK true //Force feedback haptics allow you to feel the solid objects you hold
#define SERVO_SCALING false //dynamic scaling of servo motors

#if defined(ESP32)
  //(This configuration is for ESP32 DOIT V1 so make sure to change if you're on another board)
  #define PIN_PINKY     32
  #define PIN_RING      33
  #define PIN_MIDDLE    25
  #define PIN_INDEX     26
  #define PIN_THUMB     27
  
  #define PIN_CALIB     18 //button for recalibration (You can set this to GPIO0 to use the BOOT button, but only when using Bluetooth.)
  //#define DEBUG_LED 2
  #define PIN_PINKY_MOTOR     19  //used for force feedback
  #define PIN_RING_MOTOR      18 //^ swap to 16-2
  #define PIN_MIDDLE_MOTOR    4 //^
  #define PIN_INDEX_MOTOR     15 //^
  #define PIN_THUMB_MOTOR     12 //^
  //#define PIN_MENU_BTN        1 //

  #define PIN_LIMIT_THUMB_BTN  2 //36
  #define PIN_LIMIT_INDEX_BTN   0 //39
  #define PIN_LIMIT_MIDDLE_BTN  34
  #define PIN_LIMIT_RING_BTN    35
  #define PIN_LIMIT_PINKY_BTN   14

  // DEFINE ROBO HAND SERVOS

  #define PIN_PINKY_HAND_MOTOR     5
  #define PIN_RING_HAND_MOTOR      23
  #define PIN_MIDDLE_HAND_MOTOR    22
  #define PIN_INDEX_HAND_MOTOR     21
  #define PIN_THUMB_HAND_MOTOR     19


#endif
