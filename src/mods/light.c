#include "rt.h"
#include "maath.h"

static double	cell_shading(double cos)
{
  t_pmods	*mod;

  if ((mod = mods_get(g_core->mods, "cell_shading")) == NULL ||
      mod->enabled == 0)
    return (-1);
  if (cos < 0.3)
    return (0.6);
  if (cos < 0.6)
    return (0.8);
  return (1);
}

static double	light_diffuse(t_env *env, t_pobjects *obj,
			      t_plights *light)
{
  t_cdd		l;
  double	nl;
  double	nn;
  double	cos;

  math_invtranslate(&l, &light->pos, &env->pnt);
  nl = sqrt(pow(l.x, 2) + pow(l.y, 2) + pow(l.z, 2));
  nn = sqrt(pow(env->norm.x, 2) + pow(env->norm.y, 2) + pow(env->norm.z, 2));
  cos = nl * nn;
  if (cos > EPSILON)
    cos = (env->norm.x * l.x + env->norm.y *
	   l.y + env->norm.z * l.z) / cos;
  if (cos <= EPSILON || !cos)
    cos = light->coef;
  return (cos);
}

int		mod_light(t_env *env, t_pobjects *obj,
			  t_pmods *mod, t_color *color)
{
  t_plights	*light;
  double	cos;
  int		i;
  double	cell;

  i = 0;
  cos = 0;
  light = g_core->lights;
  while (light)
    {
      cos += light_diffuse(env, obj, light);
      light = light->next;
      i++;
    }
  if (i > 1)
    cos = cos / (double)i;
  if ((cell = cell_shading(cos)) > -1)
    cos = cell;
  color->r = (double)color->r * cos;
  color->g = (double)color->g * cos;
  color->b = (double)color->b * cos;
  return (0);
}
