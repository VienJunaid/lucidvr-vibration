// CITATION! ALL THE FIRMWARE IS HEAVILY BASED OFF OF LUCIDGLOVES FIRMWARE BY LUCIDVRTECH - FARIS FAKHOURI
// This file is also unused
bool grabGesture(int *flexion){
  return (flexion[PINKY_IND] + flexion[RING_IND] + flexion[MIDDLE_IND] + flexion[INDEX_IND]) / 4 <= ANALOG_MAX/2 ? 0:1;
}

bool pinchGesture(int *flexion){
  return (flexion[INDEX_IND] + flexion[THUMB_IND]) / 2 <= ANALOG_MAX/2 ? 0:1;
}

bool triggerGesture(int *flexion){
  return flexion[INDEX_IND]<=(ANALOG_MAX/2)?0:1;
}
