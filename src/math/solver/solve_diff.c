/*
** solve_diff.c for rt in /home/aslafy_z/rendu/MUL_2013_rtracer
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Wed Jun  4 21:32:10 2014 Zadkiel Aslafy-Aharonian
** Last update Thu Jun  5 19:27:38 2014 Zadkiel Aslafy-Aharonian
*/
#include <stdio.h>
#include "maath.h"

double		solve_diff(int n, t_solver *s)
{
  int		i;
  int		set;
  double	res;

  res = -1;
  i = 0;
  set = 0;
  if (creal(s->x[0]) != 0 && creal(s->x[0]) != -1.5)
  while (i < n)
    {
      if (cimag(s->x[i]) == 0)
	{
	  if (set == 0 && creal(s->x[i]) > EPSILON)
	    {
	      res = creal(s->x[i]);
	      set = 1;
	    }
	  if (creal(s->x[i]) > EPSILON && creal(s->x[i]) < res)
	    res = creal(s->x[i]);
	}
      ++i;
    }
  return (res);
}
