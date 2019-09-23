/*
** myx_draw_line.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Dec  3 18:08:56 2013 Zadkiel Aslafy-Aharonian
** Last update Fri Mar 28 16:09:31 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

void		myx_draw_line(t_image *image, t_cd *c1, t_cd *c2, int color)
{
  double	deltaX;
  double	deltaY;
  double	len;
  int		i;
  int		x;
  int		y;

  deltaX = c2->x - c1->x;
  deltaY = c2->y - c1->y;
  len = myx_sqrt((deltaX * deltaX) + (deltaY * deltaY));
  deltaX = deltaX / len;
  deltaY = deltaY / len;
  i = 0;
  while (i < len)
    {
      x = (i * deltaX + c1->x);
      y = (i * deltaY + c1->y);
      myx_pixel_put(image, x, y, color);
      i++;
    }
}
