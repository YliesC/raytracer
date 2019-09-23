#include "rt.h"
#include "maath.h"

int		mod_reflexion(t_env *env, t_pobjects *obj,
			      t_pmods *mod, t_color *color)
{
  double	t;
  t_cdd		v;
  t_cdd		n;
  t_cdd		r;
  t_color	rgb_ref;
  t_env		tmp_env;

  if (env->reflex == RATIO_REFLEX)
    return (0);
  math_normalize(&v, &env->vect);
  math_normalize(&n, &env->norm);
  t = math_dot(&v, &n);
  r.x = v.x - (2 * n.x * t);
  r.y = v.y - (2 * n.y * t);
  r.z = v.z - (2 * n.z * t);
  memset(&tmp_env, 0, sizeof(t_env));
  tmp_env.cam_pos = env->pnt;
  tmp_env.vect = r;
  tmp_env.reflex = env->reflex + 1;
  color_hextorgb(rt_get_color(g_core, &tmp_env, obj), &rgb_ref);
  color->r = rgb_ref.r * mod->coef + color->r * (1.0f - mod->coef);
  color->g = rgb_ref.g * mod->coef + color->g * (1.0f - mod->coef);
  color->b = rgb_ref.b * mod->coef + color->b * (1.0f - mod->coef);
  return (0);
}
