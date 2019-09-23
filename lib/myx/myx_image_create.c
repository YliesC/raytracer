/*
** myx_image_create.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Dec  3 19:54:08 2013 Zadkiel Aslafy-Aharonian
** Last update Sat Jan 11 17:27:40 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

t_image		*myx_image_create(t_screen *screen, int x, int y)
{
  t_image	*image;

  if ((image = myx_init_image()) == NULL)
    return (NULL);
  if (x > 0 && y > 0)
    {
      image->ptr = mlx_new_image(screen->mlx, x, y);
      image->data = (int *) mlx_get_data_addr(image->ptr, &(image->bpp),
					      &(image->sizeline), &(image->endian));
    }
  image->x = x;
  image->y = y;
  return (image);
}
