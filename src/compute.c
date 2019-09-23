#include "rt.h"
#include "maath.h"

static void	exec_effect(t_core *core, t_pobjects *obj,
			    t_env *env, t_color *rgb)
{
  t_pmods	*mod;
  t_o_mods	*o_mod;

  o_mod = core->o_mods;
  while (o_mod)
    {
      mod = core->mods;
      while (mod)
	{
	  if (mod->type == o_mod && mod->enabled && o_mod->mod)
	    o_mod->mod(env, obj, mod, rgb);
	  mod = mod->next;
	}
      mod = obj->mods;
      while (mod)
	{
	  if (mod->type == o_mod && mod->enabled && o_mod->mod)
	    o_mod->mod(env, obj, mod, rgb);
	  mod = mod->next;
	}
      o_mod = o_mod->next;
    }
}

static int	rt_apply_effects(t_env *env, t_pobjects *obj,
				 t_core *core)
{
  t_color	rgb;

  if (!core->mods)
    return (obj->color);
  obj->type->normal(env, obj);
  color_hextorgb(obj->color, &rgb);
  exec_effect(core, obj, env, &rgb);
  return (color_rgbtohex(&rgb));
}

int		rt_get_color(t_core *core, t_env *env,
			     t_pobjects *ignore)
{
  t_pobjects    *get;
  t_pobjects    *tmp;
  double	ks;
  double	k;
  int		first;

  k = -1;
  ks = -1;
  first = 1;
  get = NULL;
  tmp = core->objects;
  while (tmp)
    {
      if (ignore != tmp)
	if ((k = tmp->type->inter(env, tmp)) > EPSILON &&
	    ((first) || (!first && k < ks)))
	  {
	    ks = k;
	    get = tmp;
	    first = 0;
	  }
      tmp = tmp->next;
    }
  env->k = ks;
  return ((get) ? (rt_apply_effects(env, get, core)) : (0));
}
