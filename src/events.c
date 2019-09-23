#include "events.h"
#include "rt.h"

int	event_next_cam(t_core *core)
{
  if (!core->curr_cam->next)
    return (-1);
  core->curr_cam = core->curr_cam->next;
  printf("Switching to next camera : %s\n",
	 core->curr_cam->name);
  thread_go(core);
  myx_flip(core->myx);
  return (0);
}

int	event_prev_cam(t_core *core)
{
  if (!core->curr_cam->prev)
    return (-1);
  core->curr_cam = core->curr_cam->prev;
  printf("Switching to previous camera : %s\n",
	 core->curr_cam->name);
  thread_go(core);
  myx_flip(core->myx);
  return (0);
}

int	event_go_left(t_core *core)
{
  core->curr_cam->pos.y += 100;
  thread_go(core);
  myx_flip(core->myx);
  return (0);
}

int		rt_events(int keycode, void *param)
{
  t_core	*core;

  core = (t_core *)param;
  if (keycode == XK_p)
    return (event_prev_cam(core));
  if (keycode == XK_n)
    return (event_next_cam(core));
  if (keycode == XK_Escape)
    exit(0);
  if (keycode == XK_Left)
    return (event_go_left(core));
  if (keycode == XK_Right)
    return (event_go_right(core));
  if (keycode == XK_Up)
    return (event_go_up(core));
  if (keycode == XK_Down)
    return (event_go_down(core));
  if (keycode == XK_KP_Add)
    return (event_zoom(core));
  if (keycode == XK_KP_Subtract)
    return (event_unzoom(core));
  return (0);
}
