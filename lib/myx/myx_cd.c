/*
** myx_cords.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Dec  3 18:07:49 2013 Zadkiel Aslafy-Aharonian
** Last update Mon Mar 10 17:14:25 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

t_cd	*myx_cd(t_cd *cd, int x, int y, int z)
{
  cd->x = x;
  cd->y = y;
  cd->z = z;
  return (cd);
}

t_cdd	*myx_cdd(t_cdd *cd, double x, double y, double z)
{
  cd->x = x;
  cd->y = y;
  cd->z = z;
  return (cd);
}
