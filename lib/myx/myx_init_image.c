/*
** myx_init_image.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Dec  3 18:10:38 2013 Zadkiel Aslafy-Aharonian
** Last update Fri May  9 14:55:52 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

t_image		*myx_init_image()
{
  t_image	*image;

  if ((image = malloc(sizeof(t_image))) == NULL)
    return (NULL);
  image->data = NULL;
  image->ptr = NULL;
  image->y = 0;
  image->x = 0;
  image->bpp = 0;
  image->sizeline = 0;
  image->endian = 0;
  return (image);
}
