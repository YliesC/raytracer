#include "rt.h"
#include "maath.h"

double		inter_plane(t_env *env, t_pobjects *obj)
{
  t_cdd		v;
  t_cdd		e;

  math_invtranslate(&e, &env->cam_pos, &obj->pos);
  math_invrotate(&v, &env->vect, &obj->rot);
  if (v.z != 0)
    return (- (e.z) / (v.z));
  return (-1);
}

int		normal_plane(t_env *env, t_pobjects *obj)
{
  t_cdd		e;
  t_cdd		v;

  math_invtranslate(&e, &env->cam_pos, &obj->pos);
  math_invrotate(&v, &env->vect, &obj->rot);
  env->pnt.x = e.x + env->k * v.x;
  env->pnt.y = e.y + env->k * v.y;
  env->pnt.z = e.z + env->k * v.z;
  env->norm.x = 0;
  env->norm.y = 0;
  env->norm.z = 100;
  return (0);
}
