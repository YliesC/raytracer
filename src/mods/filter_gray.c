#include "rt.h"
#include "maath.h"

int		filter_gray(t_env *env, t_pobjects *obj,
			    t_pmods *mod, t_color *color)
{
  int		c;

  c = (color->r + color->r + color->r) / 3;
  c = (c > 255) ? 255 : c;
  color->r = c;
  color->g = c;
  color->b = c;
  return (0);
}
