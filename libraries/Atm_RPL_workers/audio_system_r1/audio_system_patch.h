#pragma once
#include "audio_system.h"
#include "audio_system_mix.h"

static AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
static AudioConnection          patchCord2(playSdWav1, 1, mixer1, 1);
static AudioConnection          patchCord3(playSdWav2, 0, mixer2, 2);
static AudioConnection          patchCord4(playSdWav2, 1, mixer2, 3);
static AudioConnection          patchCord5(mixer2, 0, mixer4, 0);
static AudioConnection          patchCord6(mixer1, 0, mixer3, 0);
static AudioConnection          patchCord7(mixer4, 0, i2s1, 1);
static AudioConnection          patchCord8(mixer3, 0, i2s1, 0);