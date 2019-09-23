#include "rt.h"

int	event_go_right(t_core *core)
{
  core->curr_cam->pos.y -= 100;
  thread_go(core);
  myx_flip(core->myx);
  return (0);
}

int	event_go_up(t_core *core)
{
  core->curr_cam->pos.z += 100;
  thread_go(core);
  myx_flip(core->myx);
  return (0);
}

int	event_go_down(t_core *core)
{
  core->curr_cam->pos.z -= 100;
  thread_go(core);
  myx_flip(core->myx);
  return (0);
}

int	event_zoom(t_core *core)
{
  core->curr_cam->pos.x += 100;
  thread_go(core);
  myx_flip(core->myx);
  return (0);
}

int	event_unzoom(t_core *core)
{
  core->curr_cam->pos.x -= 100;
  thread_go(core);
  myx_flip(core->myx);
  return (0);
}
