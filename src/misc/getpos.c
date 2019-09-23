#include <math.h>
#include "rt.h"

void	get_pos(t_cdd *pos, t_cd *pa, t_core *core, double pad)
{
  pos->x = pa->x % core->screen.size.x
    + (double)(pa->y % (int)sqrt(core->antia)) * pad;
  pos->y = pa->x / core->screen.size.x
    + (double)(pa->y / (int)sqrt(core->antia)) * pad;
}
