/*
** myx_draw_rect.c for myx in /home/aslafy_z/rendu/MUL_2013_wolf3d
**
** Made by
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Jan  7 15:04:20 2014
** Last update Sun Jan 12 02:58:43 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

void	myx_draw_rect(t_image *image, t_cd *min, t_cd *size, int color)
{
  t_cd	pos;

  pos.y = min->y;
  while (pos.y < min->y + size->y)
    {
      pos.x = min->x;
      while (pos.x < min->x + size->x)
	{
	  myx_pixel_put(image, pos.x, pos.y, color);
	  pos.x++;
	}
      pos.y++;
    }
}
