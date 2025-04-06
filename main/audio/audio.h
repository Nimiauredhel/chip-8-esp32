#ifndef AUDIO_H
#define AUDIO_H

#include <stdbool.h>
#include "common.h"
#include "pitches.h"
#include "driver/ledc.h"

void init_audio(void);
void set_audio(uint32_t frequency, uint32_t duty);
void deinit_audio(void);

#endif
