#include "rt.h"
#include "maath.h"

double		inter_cone(t_env *env, t_pobjects *obj)
{
  t_solver	solver;
  double	r;
  t_cdd		e;
  t_cdd		v;

  math_invtranslate(&e, &env->cam_pos, &obj->pos);
  math_invrotate(&v, &env->vect, &obj->rot);
  r = SQ(tan(RAD((obj->ray[0] == 90) ? 89 : obj->ray[0])));
  solve_init(&solver);
  solver.a = (SQ(v.x) + SQ(v.y) - (SQ(v.z) * r));
  solver.b = ((2 * v.x * e.x) + (2 * v.y * e.y) - ((2 * v.z * e.z) * r));
  solver.c = (SQ(e.x) + SQ(e.y) - (SQ(e.z) * r));
  return (solve_diff(solve_two(&solver), &solver));
}

int		normal_cone(t_env *env, t_pobjects *obj)
{
  t_cdd		e;
  t_cdd		v;

  math_invtranslate(&e, &env->cam_pos, &obj->pos);
  math_invrotate(&v, &env->vect, &obj->rot);
  env->pnt.x = e.x + env->k * v.x;
  env->pnt.y = e.y + env->k * v.y;
  env->pnt.z = e.z + env->k * v.z;
  env->norm = env->pnt;
  return (0);
}
