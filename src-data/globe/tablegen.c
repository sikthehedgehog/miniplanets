#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

uint8_t xtable[0x4000];
uint8_t ytable[0x4000];
uint8_t otable[0x4000];

int xpos[0x40];
int ypos[0x40];
uint8_t offset[0x40];
uint8_t order[0x40];

void write_uint16(FILE *file, uint16_t value) {
   uint8_t buffer[] = { value >> 8, value };
   fwrite(buffer, 1, 2, file);
}

int sortfunc(const void *ptr1, const void *ptr2) {
   uint8_t id1 = *((uint8_t *) ptr1);
   uint8_t id2 = *((uint8_t *) ptr2);
   
   int dist1 = xpos[id1] * xpos[id1] + ypos[id1] * ypos[id1];
   int dist2 = xpos[id2] * xpos[id2] + ypos[id2] * ypos[id2];
   //int dist1 = abs(xpos[id1] + ypos[id1]);
   //int dist2 = abs(xpos[id2] + ypos[id2]);
   
   if (dist1 > dist2) return 1;
   if (dist1 < dist2) return -1;
   if (id1 > id2) return 1;
   if (id1 < id2) return -1;
   return 0;
}

int main() {
   unsigned pos = 0;
   for (int camy = 0; camy < 0x10; camy++)
   for (int camx = 0; camx < 0x10; camx++) {
      for (unsigned i = 0; i < 0x40; i++) {
         int tilex = (i & 0x07) - 4;
         int tiley = (i >> 3) - 4;
         if (camx & 0x08) tilex++;
         if (camy & 0x08) tiley++;
         
         offset[i] = (tilex & 0x0F) | (tiley & 0x0F) << 4;
         
         xpos[i] = tilex;
         ypos[i] = tiley;
         order[i] = i;
      }
      
      qsort(order, 0x40, sizeof(uint8_t), sortfunc);
      
      for (unsigned i = 0; i < 0x40; i++) {
         float basex = (0x08 + (xpos[i] << 4) - camx) / 64.0f;
         float basey = (0x08 + (ypos[i] << 4) - camy) / 64.0f;
         float sinx = sin(basex * 3.1415926f * 0.5f);
         float siny = sin(basey * 3.1415926f * 0.5f);
         float circx = sinx * sqrt(1.0f - siny * siny * 0.5f);
         float circy = siny * sqrt(1.0f - sinx * sinx * 0.5f);
         
         xpos[i] = (int)(44.0f * circx);
         ypos[i] = (int)(44.0f * circy);
      }
      
      for (unsigned i = 0; i < 0x40; i++) {
         xtable[pos] = xpos[order[i]];
         ytable[pos] = ypos[order[i]];
         otable[pos] = offset[order[i]];
         pos++;
      }
   }
   
   FILE *file = fopen("../../data/globe/table.lut", "wb");
   fwrite(xtable, 1, 0x4000, file);
   fwrite(ytable, 1, 0x4000, file);
   fwrite(otable, 1, 0x4000, file);
   fclose(file);
   
   file = fopen("../../data/globe/objects.lut", "wb");
   for (int objy = -0x40; objy < 0x40; objy++)
   for (int objx = -0x40; objx < 0x40; objx++) {
      float basex = objx / 64.0f;
      float basey = objy / 64.0f;
      float sinx = sin(basex * 3.1415926f * 0.5f);
      float siny = sin(basey * 3.1415926f * 0.5f);
      float circx = sinx * sqrt(1.0f - siny * siny * 0.5f);
      float circy = siny * sqrt(1.0f - sinx * sinx * 0.5f);
      
      int8_t value = (int)(58.0f * circx);
      fwrite(&value, 1, 1, file);
   }
   fclose(file);
   
   return 0;
}
