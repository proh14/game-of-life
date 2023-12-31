/* Copyright (c) 2023 proh14. All rights reserved.
 *
 *   This program is free software: you can redistribute it and/or modify it
 *   under the terms of the GNU General Public License as published by the Free
 *   Software Foundation, either version 3 of the License, or (at your option)
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful, but WITHOUT
 *   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *   FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  this program. If not, see <https://www.gnu.org/licenses/>.
 */

#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#define CLEAR "cls"
#include <windows.h>
#else
#define CLEAR "clear"
#include <unistd.h>
#endif

#define W 30
#define H 30

#define D '.'
#define A '#'

char world[W][H];

void draw();
void evolution();
void prefill();

int main(void) {
  prefill();
  while (1) {
    draw();
    evolution();
    sleep(1);
  }
  return 0;
}
void draw() {
  system(CLEAR);
  for (int i = 0; i < W; i++) {
    for (int j = 0; j < H; j++) {
      printf("%c", world[i][j]);
    }
    printf("\n");
  }
}
void evolution() {
  char new[W][H];
  for (int i = 0; i < W; i++) {
    for (int j = 0; j < H; j++) {
      int lives = 0;
      for (int x = i - 1; x <= i + 1; x++) {
        for (int y = j - 1; y <= j + 1; y++) {
          if (world[(x + W) % W][(y + H) % H] == A) {
            lives++;
          }
        }
      }
      if (world[i][j] == A) {
        lives--;
      }
      if (lives == 3 || (lives == 2 && world[i][j] == A)) {
        new[i][j] = A;
      } else {
        new[i][j] = D;
      }
    }
  }
  for (int i = 0; i < W; i++) {
    for (int j = 0; j < H; j++) {
      world[i][j] = new[i][j];
    }
  }
}

void prefill() {
  srand(time(NULL));
  for (int i = 0; i < W; i++) {
    for (int j = 0; j < H; j++) {
      world[i][j] = rand() < RAND_MAX / 10 ? A : D;
    }
  }
}
