#include <X11/Xlib.h>
#include "rt.h"

static int	init_shapes(t_core *core)
{
  if (o_shapes_add(&core->o_shapes, "plane",
		   inter_plane, normal_plane) < 0)
    return (-1);
  if (o_shapes_add(&core->o_shapes, "sphere",
		   inter_sphere, normal_sphere) < 0)
    return (-1);
  if (o_shapes_add(&core->o_shapes, "cylinder",
		   inter_cylinder, normal_cylinder) < 0)
    return (-1);
  if (o_shapes_add(&core->o_shapes, "cone",
		   inter_cone, normal_cone) < 0)
    return (-1);
  if (o_shapes_add(&core->o_shapes, "hyperboloid",
		   inter_hyperboloid, normal_hyperboloid) < 0)
    return (-1);
  return (0);
}

static int	init_mods(t_core *core)
{
  if (o_mods_add(&core->o_mods, "chess", mod_chess) < 0)
    return (-1);
  if (o_mods_add(&core->o_mods, "shining", mod_shining) < 0)
    return (-1);
  if (o_mods_add(&core->o_mods, "light", mod_light) < 0)
    return (-1);
  if (o_mods_add(&core->o_mods, "shadow", mod_shadow) < 0)
    return (-1);
  if (o_mods_add(&core->o_mods, "cell_shading", NULL) < 0)
    return (-1);
  if (o_mods_add(&core->o_mods, "reflexion", mod_reflexion) < 0)
    return (-1);
  if (o_mods_add(&core->o_mods, "filter_negative", filter_neg) < 0)
    return (-1);
  if (o_mods_add(&core->o_mods, "filter_greyscale", filter_gray) < 0)
    return (-1);
  return (0);
}

static int	init_mlx(t_core *core)
{
  if ((core->myx = myx_init(core->screen.size.x, core->screen.size.y,
			    core->screen.name)) == NULL)
    return (-1);
  if (!core->preview)
    {
      if (!XInitThreads())
	return (-1);
      memset(core->myx->image->data, 0xFFFFFF,
	     sizeof(*core->myx->image->data));
      myx_open_win(core->myx);
      mlx_key_hook(core->myx->win, &rt_events, core);
      mlx_expose_hook(core->myx->win, &myx_expose, core->myx);
      myx_flip(core->myx);
    }
  return (0);
}

static int	init_check(t_core *core)
{
  if (!core->cams)
    return (VTOI
	    puterr((void*)-1,
		   E_PREFIX
		   "There is no camera, please provide one at least.\n"));
  core->curr_cam = core->cams;
  return (0);
}

int     rt_init(t_core *core, int ac, char **av)
{
  memset(core, 0, sizeof(*core));
  rt_args(ac, av, core);
  if (init_shapes(core) < 0)
    return (-1);
  if (init_mods(core) < 0)
    return (-1);
  if (rt_parse(core) < 0)
    return (-1);
  if (core->screen.size.x <= 0 || core->screen.size.y <= 0)
    return (VTOI
	    puterr((void*)-1,
		   E_PREFIX"Window size as to be positive.\n"));
  if (init_check(core) < 0)
    return (-1);
  if (init_mlx(core) < 0)
    return (-1);
  g_core = core;
  return (0);
}
