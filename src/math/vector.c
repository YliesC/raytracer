#include "maath.h"

double		math_interpolate(double start, double end, double lamda)
{
  return (start * (1.0 - lamda) + end * lamda);
}

void		math_normalize(t_cdd *dest, t_cdd *src)
{
  double	t;

  t = (sqrt(pow(src->x, 2) + pow(src->y, 2) + pow(src->z, 2)));
  dest->x = src->x / t;
  dest->y = src->y / t;
  dest->z = src->z / t;
}

double		math_dot(t_cdd *v1, t_cdd *v2)
{
  double	n1;
  double	n2;

  n1 = (sqrt(pow(v1->x, 2) + pow(v1->y, 2) + pow(v1->z, 2)));
  n2 = (sqrt(pow(v2->x, 2) + pow(v2->y, 2) + pow(v2->z, 2)));
  if (n1 * n2 == 0)
    return (0);
  return ((v1->x * v2->x) + (v1->z * v2->y) + (v1->z * v2->z));
}

void		math_cddcpy(t_cdd *dest, t_cdd *src)
{
  dest->x = src->x;
  dest->y = src->y;
  dest->z = src->z;
}
