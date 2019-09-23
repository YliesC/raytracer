/*
** myx_color_rgb.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Dec  3 18:12:24 2013 Zadkiel Aslafy-Aharonian
** Last update Tue Dec  3 18:12:40 2013 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

t_color		*myx_color_rgb(int cmp)
{
  t_color	*color;

  if ((color = malloc(sizeof(t_color))) == NULL)
    return (NULL);
  color->cmp = cmp;
  color->r = (cmp >> 16) & 0xFF;
  color->g = (cmp >> 8) & 0xFF;
  color->b = cmp & 0xFF;
  return (color);
}
