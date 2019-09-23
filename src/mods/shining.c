#include "rt.h"

int		mod_shining(t_env *env, t_pobjects *obj,
			    t_pmods *mod, t_color *color)
{
  t_color	col;
  t_plights	*light;
  double	shine;

  if (obj->shine <= 0 && mod->coef <= 0)
    return (0);
  shine = (obj->shine != 0) ? obj->shine : mod->coef;
  light = g_core->lights;
  while (light)
    {
      color_hextorgb(light->color, &col);
      color->r = color->r * (1.0f - shine) + col.r * shine;
      color->g = color->g * (1.0f - shine) + col.g * shine;
      color->b = color->b * (1.0f - shine) + col.b * shine;
      light = light->next;
    }
  return (0);
}
