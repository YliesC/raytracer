#include "rt.h"
#include "maath.h"

double		inter_cylinder(t_env *env, t_pobjects *obj)
{
  t_solver	solver;
  t_cdd		e;
  t_cdd		v;

  math_invtranslate(&e, &env->cam_pos, &obj->pos);
  math_invrotate(&v, &env->vect, &obj->rot);
  solve_init(&solver);
  solver.a = pow(v.x, 2) + pow(v.y, 2);
  solver.b = (e.x * v.x + e.y * v.y) * 2.0f;
  solver.c = pow(e.x, 2) + pow(e.y, 2) - pow(obj->ray[0], 2);
  return (solve_diff(solve_two(&solver), &solver));
}

int		normal_cylinder(t_env *env, t_pobjects *obj)
{
  t_cdd		e;
  t_cdd		v;

  math_invtranslate(&e, &env->cam_pos, &obj->pos);
  math_invrotate(&v, &env->vect, &obj->rot);
  env->pnt.x = e.x + env->k * v.x;
  env->pnt.y = e.y + env->k * v.y;
  env->pnt.z = e.z + env->k * v.z;
  env->norm = env->pnt;
  env->norm.z = 0;
  return (0);
}
