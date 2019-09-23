/*
** myx_color_cmp.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Dec  3 18:11:56 2013 Zadkiel Aslafy-Aharonian
** Last update Sun Dec  8 12:34:23 2013 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

t_color		*myx_color_cmp(int r, int g, int b)
{
  t_color	*color;

  if ((color = malloc(sizeof(t_color))) == NULL)
    return (NULL);
  color->cmp = ((r << 16) + (g << 8) + b);
  color->r = r;
  color->g = g;
  color->b = b;
  return (color);
}
