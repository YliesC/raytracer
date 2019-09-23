/*
** myx_isometry.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Fri Dec  6 20:05:41 2013 Zadkiel Aslafy-Aharonian
** Last update Sat Jan 11 01:38:46 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

t_cd	*myx_isometry(t_cd *cd, double cte1, double cte2)
{
  int	x2d;
  int	y2d;

  x2d = cte1 * cd->x - cte2 * cd->y;
  y2d = cd->z + (cte1 / 2) * cd->x + (cte2 / 2) * cd->y;
  return (NULL);
}
