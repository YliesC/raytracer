#include "rt.h"

void	rt_free(t_core *core)
{
  o_shapes_free(core->o_shapes);
  objects_free(core->objects);
  o_mods_free(core->o_mods);
  lights_free(core->lights);
  if (!core->preview)
    myx_free(core->myx);
}
