/*
** chess.c for rt in /home/aslafy_z/rendu/MUL_2013_rtracer/src/mods
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Thu Jun  5 01:10:39 2014 Zadkiel Aslafy-Aharonian
** Last update Sun Jun  8 16:01:30 2014 Zadkiel Aslafy-Aharonian
*/

#include "rt.h"

static void	go_black(t_color *color)
{
  color->r = 0;
  color->g = 0;
  color->b = 0;
}

int		mod_chess(t_env *env, t_pobjects *obj,
			  t_pmods *mod, t_color *color)
{
  int		t;
  int		k;

  k = CHESSPLANE_SIZE;
  t = k * 2;
  if ((env->pnt.x >= 0.0 && env->pnt.y >= 0.0)
      || (env->pnt.x < 0.0 && env->pnt.y < 0.0))
    {
      if (((int)abs(env->pnt.x) % t <= k
	   && (int)abs(env->pnt.y) % t <= k)
	  || ((int)abs(env->pnt.x) % t > k
	      && (int)abs(env->pnt.y) % t > k))
	go_black(color);
    }
  else
    {
      if (!(((int)abs(env->pnt.x) % t <= k
	     && (int)abs(env->pnt.y) % t <= k)
	    || ((int)abs(env->pnt.x) % t > k
		&& (int)abs(env->pnt.y) % t > k)))
  	go_black(color);
    }
  return (0);
}
