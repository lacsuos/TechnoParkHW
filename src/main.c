#include "quadrafunc.h"
#include <stdio.h>
#include <stdlib.h>

Point input() {
  Point a;
  if (scanf("%lf", &a.x) != 1 || scanf("%lf", &a.y) != 1) {
    printf("Error input! Executing programm... \n");
    exit(1);
  }
  return a;
}

int main(int agrc, char **argv) {
  Point x, y, z;
  printf("Enter point A coordinates: \n");
  x = input();
  printf("Enter point B coordinates:\n");
  y = input();
  printf("Enter point C coordinates:\n");
  z = input();
  double a, b, c;
  find_coeffs(&x, &y, &z, &a, &b, &c);
  return 0;
}
