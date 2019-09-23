/*
** myx_image_blit.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Dec  3 18:13:43 2013 Zadkiel Aslafy-Aharonian
** Last update Sat Jan 11 18:12:11 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

void	myx_image_blit(t_image *src, t_image *dest, int xx, int yy)
{
  t_cd	pos;

  pos.y = 0;
  while (pos.y < src->y)
    {
      pos.x = 0;
      while (pos.x < src->x)
	{
	  dest->data[(yy + pos.y) * dest->x + (xx + pos.x)] =
	    src->data[pos.y * src->x + pos.x];
	  pos.x++;
	}
      pos.y++;
    }
}
