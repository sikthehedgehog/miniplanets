#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t map[0x40][0x20];

int main() {
   for (unsigned x = 0; x < 0x40; x++)
   for (unsigned y = 0; y < 0x20; y++)
      map[x][y] = 0xFF;
   
   for (unsigned x = 0; x < 0x10; x++)
   for (unsigned y = 0; y < 0x08; y++) {
      unsigned realx = x * 4;
      unsigned realy = y * 4;
      
      realx += rand() % 2;
      realy += rand() % 2;
      map[realx][realy] = rand() % 8;
      
      realx = x * 4 + 2;
      realy = y * 4 + 2;
      
      unsigned base = rand() % 16;
      if (base < 4) {
         base = base * 4 + 8;
         
         map[realx+0][realy+0] = base+0;
         map[realx+1][realy+0] = base+1;
         map[realx+0][realy+1] = base+2;
         map[realx+1][realy+1] = base+3;
      }
      
      else if (base < 12) {
         realx += rand() % 2;
         realy += rand() % 2;
         map[realx][realy] = base - 4;
      }
   }
   
   for (unsigned x = 0; x < 0x40; x++)
   for (unsigned y = 0; y < 0x20; y++)
      map[x][y]++;
   
   FILE *file = fopen("background.blob", "wb");
   for (unsigned y = 0; y < 0x20; y++)
   for (unsigned x = 0; x < 0x40; x++) {
      unsigned offset = y >> 1;
      fwrite(&map[(x + offset) & 0x3F][y], 1, 1, file);
      //fwrite(&map[x][y], 1, 1, file);
   }
   fclose(file);
   
   return 0;
}
