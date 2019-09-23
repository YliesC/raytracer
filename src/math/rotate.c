/*
** rotate.c for rt in /home/aslafy_z/rendu/MUL_2013_rtracer
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Wed Jun  4 20:48:36 2014 Zadkiel Aslafy-Aharonian
** Last update Sun Jun  8 14:33:26 2014 Zadkiel Aslafy-Aharonian
*/

#include "rt.h"
#include "maath.h"

static void	rotate_x(t_cdd *dest, t_cdd *cd, double a)
{
  a = RAD(a);
  dest->x = cd->x;
  dest->y = cd->y * cos(a) + cd->z * (-sin(a));
  dest->z = cd->y * sin(a) + cd->z * cos(a);
}

static void	rotate_y(t_cdd *dest, t_cdd *cd, double a)
{
  a = RAD(a);
  dest->x = cd->x * cos(a) + cd->z * sin(a);
  dest->y = cd->y;
  dest->z = cd->x * (-sin(a)) + cd->z * cos(a);
}

static void	rotate_z(t_cdd *dest, t_cdd *cd, double a)
{
  a = RAD(a);
  dest->x = cd->x * cos(a) + cd->y * (-sin(a));
  dest->y = cd->x * sin(a) + cd->y * cos(a);
  dest->z = cd->z;
}

void	math_rotate(t_cdd *dest, t_cdd *cd, t_cdd *rot)
{
  math_cddcpy(dest, cd);
  if (rot->x != 0)
    rotate_x(dest, cd, rot->x);
  if (rot->y != 0)
    rotate_y(dest, cd, rot->y);
  if (rot->z != 0)
    rotate_z(dest, cd, rot->z);
}

void	math_invrotate(t_cdd *dest, t_cdd *cd, t_cdd *rot)
{
  math_cddcpy(dest, cd);
  if (rot->x != 0)
    rotate_x(dest, cd, -rot->x);
  if (rot->y != 0)
    rotate_y(dest, cd, -rot->y);
  if (rot->z != 0)
    rotate_z(dest, cd, -rot->z);
}
