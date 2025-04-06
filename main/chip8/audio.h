#ifndef AUDIO_H
#define AUDIO_H

#include <stdbool.h>
#include "common.h"
#include "pitches.h"

typedef struct AudioData
{
    int8_t phases[2];
    int8_t dirs[2];
} AudioData_t;

void* init_audio(void);
void set_audio(void *stream, bool active);
void deinit_audio(void *stream);

#endif
