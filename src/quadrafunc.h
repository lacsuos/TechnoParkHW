#pragma once

typedef struct Points
{
  double x;
  double y;
} Point;

typedef enum Solutions
{
  NOT_EXIST,
  UNIQUE,
  INF_N
} Solution;

void find_coeffs(Point *a, Point *b, Point *c, double *alpha, double *beta,
                 double *gamma);
