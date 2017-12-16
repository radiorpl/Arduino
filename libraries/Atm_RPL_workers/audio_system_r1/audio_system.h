#pragma once

/*
//r0-2audio library
AudioControlSGTL5000     sgtl5000_1;     //xy=744,575
AudioPlaySdWav           playSdWav1;     //xy=394,289
AudioPlaySdWav           playSdWav2;     //xy=398,385
AudioMixer4              mixer1;         //xy=594,297
AudioMixer4              mixer2;         //xy=591,395
AudioOutputI2S           i2s1;           //xy=824,334
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord3(playSdWav2, 0, mixer2, 2);
AudioConnection          patchCord4(playSdWav2, 1, mixer2, 3);
AudioConnection          patchCord5(mixer2, 0, i2s1, 1);
AudioConnection          patchCord6(mixer1, 0, i2s1, 0);
//AudioControlSGTL5000     sgtl5000_1;     //xy=744,575
*/

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=394,289
AudioPlaySdWav           playSdWav2;     //xy=398,385
AudioMixer4              mixer2;         //xy=568,393
AudioMixer4              mixer1;         //xy=575,263
AudioMixer4              mixer4;         //xy=760,403
AudioMixer4              mixer3;         //xy=765,263
AudioOutputI2S           i2s1;           //xy=925,326
/*
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord3(playSdWav2, 0, mixer2, 2);
AudioConnection          patchCord4(playSdWav2, 1, mixer2, 3);
AudioConnection          patchCord5(mixer2, 0, mixer4, 0);
AudioConnection          patchCord6(mixer1, 0, mixer3, 0);
AudioConnection          patchCord7(mixer4, 0, i2s1, 1);
AudioConnection          patchCord8(mixer3, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=744,575
*/
// GUItool: end automatically generated code