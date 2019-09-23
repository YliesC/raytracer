/*
** filter_neg.c for rt in /home/aslafy_z/rendu/MUL_2013_rtracer
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Sun Jun  8 13:28:15 2014 Zadkiel Aslafy-Aharonian
** Last update Sun Jun  8 15:39:33 2014 Zadkiel Aslafy-Aharonian
*/

#include "rt.h"
#include "maath.h"

int		filter_neg(t_env *env, t_pobjects *obj,
			   t_pmods *mod, t_color *color)
{
  color->r = 255 - color->r;
  color->g = 255 - color->g;
  color->b = 255 - color->b;
  return (0);
}
