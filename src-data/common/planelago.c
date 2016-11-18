#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DIST 0x100

float deg2rad(float angle) {
   return angle * 180.0f / 3.1415926f;
}

int posx[9];
int posy[9];
int posz[9];

uint8_t xbuf[9*0x100];
uint8_t ybuf[9*0x100];
uint8_t zbuf[9*0x100];

void make_planets(int anim) {
   for (int offset = 0; offset < 3; offset++) {
      float angle = offset * 120.0f + anim * 180.0f / 128.0f;
      posx[0+offset] = MAX_DIST * cos(deg2rad(angle)) + 0.5f;
      posx[4+offset] = MAX_DIST * cos(deg2rad(angle)) + 0.5f;
      posy[0+offset] = MAX_DIST * cos(deg2rad(60.0f)) + 0.5f;
      posy[4+offset] = MAX_DIST * cos(deg2rad(-60.0f)) + 0.5f;
      posz[0+offset] = MAX_DIST * sin(deg2rad(angle)) + 0.5f;
      posz[4+offset] = MAX_DIST * sin(deg2rad(angle)) + 0.5f;
   }
   
   posx[3] = 0;
   posy[3] = -MAX_DIST;
   posz[3] = 0;
   
   posx[7] = 0;
   posy[7] = MAX_DIST;
   posz[7] = 0;
   
   posx[8] = 0;
   posy[8] = 0;
   posz[8] = 0;
}

void process_planets(unsigned offset) {
   offset *= 9;
   
   for (unsigned i = 0; i < 9; i++) {
      xbuf[offset+i] = posx[i];
      ybuf[offset+i] = posy[i];
      zbuf[offset+i] = posz[i];
   }
}

int main() {
   FILE *file = fopen("../../data/common/planelagos.lut", "wb");
   
   for (int i = 0; i < 0x100; i++) {
      make_planets(i);
      process_planets(i);
   }
   
   fwrite(xbuf, 1, 9*0x100, file);
   fwrite(ybuf, 1, 9*0x100, file);
   fwrite(zbuf, 1, 9*0x100, file);
   fclose(file);
   
   return 0;
}
