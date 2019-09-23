#include "rt.h"
#include "maath.h"

static void	set_vector(t_env *env, t_env *tmp, t_plights *light)
{
  t_cdd		e;
  t_cdd		l;

  e.x = (env->cam_pos.x + env->k * env->vect.x);
  e.y = (env->cam_pos.y + env->k * env->vect.y);
  e.z = (env->cam_pos.z + env->k * env->vect.z);
  l.x = light->pos.x - e.x;
  l.y = light->pos.y - e.y;
  l.z = light->pos.z - e.z;
  tmp->cam_pos = e;
  tmp->vect = l;
}

static int	set_color(t_color *color, t_pmods *mod, double k)
{
  color->r = color->r * ((!mod->coef) ? k : mod->coef);
  color->g = color->g * ((!mod->coef) ? k : mod->coef);
  color->b = color->b * ((!mod->coef) ? k : mod->coef);
  return (0);
}

int		mod_shadow(t_env *env, t_pobjects *obj,
			   t_pmods *mod, t_color *color)
{
  t_plights	*light;
  t_pobjects	*tmp;
  double	k;
  t_env		tmp_env;

  light = g_core->lights;
  while (light)
    {
      set_vector(env, &tmp_env, light);
      tmp = g_core->objects;
      while (tmp)
	{
	  if (tmp != obj)
	    {
	      k = tmp->type->inter(&tmp_env, tmp);
	      if (k > EPSILON && k < 1)
		return (set_color(color, mod, k));
	    }
	  tmp = tmp->next;
	}
      light = light->next;
    }
  return (0);
}
