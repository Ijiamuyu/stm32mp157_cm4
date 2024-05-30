#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int main(void) {
  volatile uint32_t addr = 0x10020000;
  *(uint32_t *)addr = 0x20240530;

  while (1) {
  }
  return 0;
}
