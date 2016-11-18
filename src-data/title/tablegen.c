#include <stdint.h>
#include <stdio.h>

uint8_t offset[12][12];
uint8_t buffer[144];

int main() {
   FILE *file = fopen("../../data/title/scaling.lut", "wb");
   
   uint8_t pos = 0;
   for (int xhi = 0; xhi < 3; xhi++)
   for (int yhi = 0; yhi < 3; yhi++)
   for (int ylo = 0; ylo < 4; ylo++)
   for (int xlo = 0; xlo < 4; xlo++) {
      int x = xlo + xhi * 4;
      int y = ylo + yhi * 4;
      offset[x][y] = pos;
      pos++;
   }
   
   for (int scale = 1; scale <= 12; scale++) {
      for (int y = 0; y < 12; y++)
      for (int x = 0; x < 12; x++) {
         uint8_t value = 0xFF;
         int factor = (scale << 16) / 12;
         int realx = ((x - 6) << 16) / factor + 6;
         int realy = ((y - 6) << 16) / factor + 6;
         
         if (realx >= 0 && realx < 12 && realy >= 0 && realy < 12)
            value = offset[realx][realy];
         
         uint8_t *dest = &buffer[offset[x][y]];
         *dest = value;
      }
      
      fwrite(buffer, 1, 144, file);
   }
   
   fclose(file);
   return 0;
}
