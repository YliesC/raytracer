#include "rt.h"
#include "maath.h"

int		thread_go(t_core *core)
{
  if (thread_init(core->thdnb, core) < 0)
    return (-1);
  if (thread_fill_range(core->thdnb, core) < 0)
    return (-1);
  if (thread_start(core->thdnb, core) < 0)
    return (-1);
  if (!core->preview && loading(core) < 0)
    return (-1);
  if (thread_join(core) < 0)
    return (-1);
  if (core->preview)
    export_bmp("/tmp/preview.bmp", core);
  if (core->export && core->export[0])
    export_bmp(core->export, core);
  return (0);
}

int		main(int ac, char **av)
{
  t_core	core;

  if (rt_init(&core, ac, av) < 0)
    return (VTOI puterr((void *)1, E_ERROR));
  if (thread_go(&core) < 0)
    return (VTOI puterr((void *)1, E_ERROR));
  if (!core.preview)
    {
      myx_flip(core.myx);
      mlx_loop(core.myx->mlx);
    }
  rt_free(&core);
  return (0);
}
