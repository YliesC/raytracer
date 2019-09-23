#include "rt.h"

void	math_invtranslate(t_cdd *new, t_cdd *eye, t_cdd *pos)
{
  new->x = eye->x - pos->x;
  new->y = eye->y - pos->y;
  new->z = eye->z - pos->z;
}
