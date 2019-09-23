/*
** myx_pixel_put.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Dec  3 18:11:22 2013 Zadkiel Aslafy-Aharonian
** Last update Sat Jan 11 17:40:21 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

void	myx_pixel_put(t_image *image, int x, int y, int color)
{
  if (x > 0 && x < image->x
      && y > 0 && y < image->y)
    image->data[y * image->x + x] = color;
}
