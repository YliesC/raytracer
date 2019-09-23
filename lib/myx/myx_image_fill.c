/*
** myx_image_fill.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Dec  3 19:52:17 2013 Zadkiel Aslafy-Aharonian
** Last update Sat Jan 11 17:40:54 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

void	myx_image_fill(t_image *image, int color)
{
  t_cd	pos;

  pos.y = 0;
  while (pos.y < image->y)
    {
      pos.x = 0;
      while (pos.x < image->x)
	{
	  myx_pixel_put(image, pos.x, pos.y, color);
	  pos.x++;
	}
      pos.y++;
    }
}
