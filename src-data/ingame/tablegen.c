#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

uint8_t map[0x40][0x20] = {{ 0 }};
uint8_t blob[0x100] = { 0 };

int main() {
   for (int x = 0; x < 0x40; x += 4)
   for (int y = 0; y < 0x20; y += 4) {
      int randomize = (x & 0x04) ^ (y & 0x04);
      int offset_x = randomize ? rand() % 3 : 1;
      int offset_y = randomize ? rand() % 3 : 1;
      map[x + offset_x][y + offset_y] = 1;
   }
   
   for (int x = 0; x < 0x40; x++)
   for (int y = 0; y < 0x20; y++) {
      blob[y << 3 | x >> 3] |= map[x][y] ? 1 << (x & 0x07) : 0;
   }
   
   FILE *file = fopen("../../data/background/tilemap.blob", "wb");
   fwrite(blob, 1, 0x100, file);
   fclose(file);
   
   return 0;
}
