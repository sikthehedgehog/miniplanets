#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_STEPS 0x20
#define NUM_VALUES (0x40 * NUM_STEPS * 2)

int8_t xtable[NUM_VALUES];
int8_t ytable[NUM_VALUES];
uint8_t stable[NUM_VALUES];

int globex[0x40];
int globey[0x40];
int xpos[0x40];
int ypos[0x40];
uint8_t order[0x40];

uint8_t sprites[0x40] = {
   0, 0, 1, 1, 1, 1, 0, 0,
   0, 0, 1, 1, 1, 1, 0, 0,
   1, 1, 0, 0, 0, 0, 1, 1,
   1, 1, 0, 0, 0, 0, 1, 1,
   1, 1, 0, 0, 0, 0, 1, 1,
   1, 1, 0, 0, 0, 0, 1, 1,
   0, 0, 1, 1, 1, 1, 0, 0,
   0, 0, 1, 1, 1, 1, 0, 0
};

void write_uint16(FILE *file, uint16_t value) {
   uint8_t buffer[] = { value >> 8, value };
   fwrite(buffer, 1, 2, file);
}

int sortfunc(const void *ptr1, const void *ptr2) {
   uint8_t id1 = *((uint8_t *) ptr1);
   uint8_t id2 = *((uint8_t *) ptr2);
   
   int dist1 = globex[id1] * globex[id1] + globey[id1] * globey[id1];
   int dist2 = globex[id2] * globex[id2] + globey[id2] * globey[id2];
   //int dist1 = abs(xpos[id1] + ypos[id1]);
   //int dist2 = abs(xpos[id2] + ypos[id2]);
   
   if (dist1 > dist2) return 1;
   if (dist1 < dist2) return -1;
   if (id1 > id2) return 1;
   if (id1 < id2) return -1;
   return 0;
}

int main() {
   for (unsigned i = 0; i < 0x40; i++) {
      int tilex = (i & 0x07) - 4;
      int tiley = (i >> 3) - 4;
      
      globex[i] = tilex;
      globey[i] = tiley;
      order[i] = i;
   }
   
   qsort(order, 0x40, sizeof(uint8_t), sortfunc);
   
   for (unsigned i = 0; i < 0x40; i++) {
      float basex = (0x08 + (globex[i] << 4)) / 64.0f;
      float basey = (0x08 + (globey[i] << 4)) / 64.0f;
      float sinx = sin(basex * 3.1415926f * 0.5f);
      float siny = sin(basey * 3.1415926f * 0.5f);
      float circx = sinx * sqrt(1.0f - siny * siny * 0.5f);
      float circy = siny * sqrt(1.0f - sinx * sinx * 0.5f);
      
      globex[i] = (int)(44.0f * circx);
      globey[i] = (int)(44.0f * circy);
   }
   
   unsigned pos = 0;
   
   for (unsigned step = 0; step < NUM_STEPS; step++) {
      float zpos = 0.5f / ((float) NUM_STEPS / (NUM_STEPS - step)) + 0.5f;
      float scale = zpos * sqrt(zpos);
      
      int pixels = (int)(16.0f * scale + 0.5f);
      int size = (8 - ((pixels + 2) >> 1)) << 1;
      if (size < 0) size = 0;
      
      for (unsigned i = 0; i < 0x40; i++) {
         xtable[pos] = (int)(globex[order[i]] * scale + 0.5f);
         ytable[pos] = (int)(globey[order[i]] * scale + 0.5f);
         stable[pos] = (sprites[order[i]] + size) << 2;
         
         pos++;
      }
   }
   
   for (unsigned step = 0; step < NUM_STEPS; step++) {
      float zpos = 1.5f / ((float) NUM_STEPS / (step + 1)) + 0.5f;
      float scale = zpos * sqrt(zpos);
      
      int pixels = (int)(16.0f * scale + 0.5f);
      int size = (8 - ((pixels + 2) >> 1)) << 1;
      if (size < 0) size = 0;
      
      for (unsigned i = 0; i < 0x40; i++) {
         xtable[pos] = (int)(globex[order[i]] * scale + 0.5f);
         ytable[pos] = (int)(globey[order[i]] * scale + 0.5f);
         ytable[pos] += step & 0x02 ? 2 : -2;
         stable[pos] = (sprites[order[i]] + 8) << 2;
         
         pos++;
      }
   }
   
   FILE *file = fopen("../../data/globe/ending.lut", "wb");
   fwrite(xtable, 1, NUM_VALUES, file);
   fwrite(ytable, 1, NUM_VALUES, file);
   fwrite(stable, 1, NUM_VALUES, file);
   fclose(file);
   
   return 0;
}
