/*
** solve_three.c for rt in /home/aslafy_z/rendu/MUL_2013_rtracer
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Wed Jun  4 21:25:22 2014 Zadkiel Aslafy-Aharonian
** Last update Fri Jun 13 15:34:32 2014 Zadkiel Aslafy-Aharonian
*/

#include "maath.h"

static	int	case_one(t_solver *s, double g, double h)
{
  double	k;
  double	m;
  double	m2;
  double	n;
  double	n2;

  m = (-(g / 2.0f) + (sqrt(h)));
  k = (m < 0) ? -1 : 1;
  m2 = pow((m * k), (1.0f / 3.0f)) * k;
  n = - (g / 2.0f) - sqrt(h);
  k = (n < 0) ? -1 : 1;
  n2 = pow((n * k), (1.0f / 3.0f)) * k;
  s->x[0]= (m2 + n2) - (s->b / (3.0f * s->a));
  s->x[1] = -1.0f * (m2 + n2) / 2 - (s->b / (3.0f * s->a))
    + I * (((m2 - n2) / 2.0f) * pow(3.0f, 0.5));
  s->x[2] = -1.0f * (m2 + n2) / 2 - (s->b / (3.0f * s->a))
    - I * (((m2 - n2) / 2.0f) * pow(3.0f, 0.5));
  return (3);
}

static	int	case_two(t_solver *s, double g, double h)
{
  double	rd;
  double	rc;
  double	theta;
  double	x2b;
  double	x2c;

  rd = sqrt((SQ(g) / 4.0f) - h);
  rc = pow(rd * ((rd < 0) ? -1 : 1), (1.0f / 3.0f)) *
    ((rd < 0) ? -1 : 1);
  theta = acos(-g / (2.0f * rd));
  s->x[0] = 2 * (rc * cos(theta / 3.0f)) - (s->b / (3.0f * s->a));
  x2b = cos(theta / 3);
  x2c = sqrt(3) * sin(theta / 3.0f);
  s->x[1] = ((-rc) * (x2b + x2c)) - (s->b / (3 * s->a));
  s->x[2] = ((-rc) * (x2b - x2c)) - (s->b / (3 * s->a));
  s->x[0] = round(s->x[0] * 1E+14) / 1E+14;
  s->x[1] = round(s->x[1] * 1E+14) / 1E+14;
  s->x[2] = round(s->x[2] * 1E+14) / 1E+14;
  return (3);
}

static	int	case_three(t_solver *s)
{
  double	dans;

  dans = 0;
  if (s->d > 0)
    dans = -(pow((s->d / s->a), (1.0f / 3.0f)));
  else if (s->d < 0)
    dans = pow(((-s->d) / s->a), (1.0f / 3.0f));
  s->x[0] = dans;
  s->x[1] = dans;
  s->x[2] = dans;
  return (3);
}

int		solve_three(t_solver *s)
{
  double	f;
  double	g;
  double	h;

  f = (((3.0f * s->c) / s->a) - ((SQ(s->b) / SQ(s->a)))) / 3.0f;
  g = ((2.0f * ((SQ(s->b) * s->b) / (SQ(s->a) * s->a))
	- (9.0f * s->b * s->c / SQ(s->a))
	+ ((27.0f * (s->d / s->a))))) / 27.0f;
  h = ((SQ(g) / 4.0f) + ((SQ(f) * f) / 27.0f));
  if (h > 0)
    return (case_one(s, g, h));
  else if (h <= 0)
    return (case_two(s, g, h));
  else if ((f + g + h) == 0)
    return (case_three(s));
  return (0);
}
