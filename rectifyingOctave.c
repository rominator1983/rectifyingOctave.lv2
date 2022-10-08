#include "lv2/core/lv2.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define URI "http://lv2plug.in/plugins/rectifyingOctave"

typedef enum
{
   GAIN = 0,
   INPUT = 1,
   OUTPUT = 2
} PortIndex;

typedef struct
{
   // Port buffers
   const float *gain;
   const float *input;
   float *output;

   // NOTE: for dc-compensation
   double rollingAverage;
} Distortion;

static LV2_Handle instantiate(const LV2_Descriptor *descriptor,
            double rate,
            const char *bundle_path,
            const LV2_Feature *const *features)
{
   Distortion *distortion = (Distortion *)calloc(1, sizeof(Distortion));

   return (LV2_Handle)distortion;
}

static void connect_port(LV2_Handle instance, uint32_t port, void *data)
{
   Distortion *distortion = (Distortion *)instance;

   switch ((PortIndex)port)
   {
   case GAIN:
      distortion->gain = (const float *)data;
      break;
   case INPUT:
      distortion->input = (const float *)data;
      break;
   case OUTPUT:
      distortion->output = (float *)data;
      break;
   }
}

static void activate(LV2_Handle instance)
{
  Distortion *distortion = (Distortion *)instance;
}

static void run(LV2_Handle instance, uint32_t n_samples)
{
   Distortion *distortion = (Distortion *)instance;

   const float *const input = distortion->input;
   float *const output = distortion->output;

   float sample;
   float tempValue;
   for (uint32_t pos = 0; pos < n_samples; pos++)
   {
      sample = input[pos];

      tempValue = fabs(sample);

      distortion->rollingAverage -= distortion->rollingAverage / 2000.0;
      distortion->rollingAverage += (double)tempValue / (double) 2000.0;

      output[pos] = (tempValue - distortion->rollingAverage) * 1.5;
   }
}

static void deactivate(LV2_Handle instance)
{
}

static void
cleanup(LV2_Handle instance)
{
   free(instance);
}

static const void *
extension_data(const char *uri)
{
   return NULL;
}

static const LV2_Descriptor descriptor = {URI,
   instantiate,
   connect_port,
   activate,
   run,
   deactivate,
   cleanup,
   extension_data};

LV2_SYMBOL_EXPORT const LV2_Descriptor * lv2_descriptor(uint32_t index)
{
   return index == 0 ? &descriptor : NULL;
}
