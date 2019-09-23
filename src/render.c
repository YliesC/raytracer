#include "rt.h"
#include "maath.h"

void		*thread_onstart(void *param)
{
  t_thd		*thd;

  thd = param;
  printf("thread %d launched with range %d - %d\n",
	 thd->id, thd->core->threads.pix[thd->id][0],
	 thd->core->threads.pix[thd->id][1]);
  rt_render(thd->id, thd->core->threads.pix[thd->id], thd->core);
  return (NULL);
}

static void	set_vect(t_env *env, t_core *core, t_cdd *pos)
{
  t_cdd		v;

  env->reflex = 0;
  v.x = 1000 - core->curr_cam->pos.x;
  v.y = core->screen.size.x / 2.0f -
    pos->x - core->curr_cam->pos.y;
  v.z = core->screen.size.y / 2.0f -
    pos->y - core->curr_cam->pos.z;
  env->cam_pos = core->curr_cam->pos;
  env->pos = *pos;
  env->vect = v;
  math_rotate(&env->vect, &v, &core->curr_cam->rot);
}

static int	aa_get(int *ctab, int aa)
{
  int		c;

  c = 0;
  c += (ctab[0] / aa) & 0xFF;
  c += ((ctab[1] / aa) & 0xFF) << 8;
  c += ((ctab[2] / aa) & 0xFF) << 16;
  return (c);
}

static void	aa_add(int color, int *ctab)
{
  ctab[0] += (color & 0x0000FF);
  ctab[1] += (color & 0x00FF00) >> 8;
  ctab[2] += (color & 0xFF0000) >> 16;
}

void		rt_render(int tid, int *pix, t_core *core)
{
  t_env		env;
  t_cdd		pos;
  t_cd		pa;
  double	pad;
  int		tab[3];

  pad = 1.0 / sqrt(core->antia);
  pa.x = pix[0];
  while (pa.x < pix[1])
    {
      memset(tab, 0, sizeof(int) * 3);
      pa.y = 0;
      while ((unsigned int)pa.y < core->antia)
	{
	  get_pos(&pos, &pa, core, pad);
	  set_vect(&env, core, &pos);
	  aa_add(rt_get_color(core, &env, NULL), tab);
	  pa.y++;
	}
      myx_pixel_put(core->myx->image, pos.x, pos.y, aa_get(tab, core->antia));
      core->threads.state[tid] = (((double)(pa.x - pix[0])
				   / (double)(pix[1] - pix[0])) * 100.0);
      ++pa.x;
    }
  core->threads.state[tid] = 100;
}
