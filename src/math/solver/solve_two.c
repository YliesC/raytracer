/*
** solver.c for rt in /home/aslafy_z/rendu/MUL_2013_rtracer/src/math
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Thu Apr 17 20:33:46 2014 Zadkiel Aslafy-Aharonian
** Last update Fri Jun 13 15:34:43 2014 Zadkiel Aslafy-Aharonian
*/

#include "maath.h"

int		solve_two(t_solver *s)
{
  double	d;

  d = pow(s->b, 2) - 4.0f * s->a * s->c;
  if (d >= 0)
    {
      s->x[0] = (-s->b - sqrt(d)) / (2.0f * s->a) + I * 0;
      s->x[1] = (-s->b + sqrt(d)) / (2.0f * s->a) + I * 0;
      return (2);
    }
  return (0);
}
