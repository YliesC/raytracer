#include "rt.h"

double		loading_get_percent(t_core *core)
{
  unsigned int	i;
  double	s;

  s = 0;
  i = 0;
  while (i < core->threads.nbr)
    {
      s += core->threads.state[i];
      i++;
    }
  return (s / core->threads.nbr);
}

int	loading_get(t_cd *pos, int prct, t_cd *size)
{
  int	xmin;
  int	ymin;
  int	xmax;
  int	ymax;

  xmin = 0;
  ymin = (size->y / 64) * 32;
  xmax = size->x;
  ymax = (size->y / 64) * 33;
  if ((pos->x < xmax && pos->x > xmin)
      && (pos->y < ymax && pos->y > ymin))
    {
      if (pos->x < ((prct * size->x) / 100) && pos->x > 0)
	return (0xFFFFFF);
    }
  return (0);
}

void		loading_put_string(t_core *core, double percent)
{
  char		*str;

  asprintf(&str, "Loading ... %d %%", (int)percent);
  mlx_string_put(core->myx->mlx, core->myx->win,
		 ((core->screen.size.x / 2) -
		  (core->screen.size.x / 20)),
		 ((core->screen.size.y / 2) -
		  (core->screen.size.y / 16)),
		 0xFFFFFF, str);
  free(str);
}

int		loading_loop(t_core *core, double percent, t_image *image)
{
  t_cd		pos;

  loading_put_string(core, percent);
  pos.y = 0;
  while (pos.y < core->screen.size.y)
    {
      pos.x = 0;
      while (pos.x < core->screen.size.x)
	{
	  myx_pixel_put(image, pos.x, pos.y,
			loading_get(&pos, percent, &core->screen.size));
	  pos.x++;
	}
      pos.y++;
    }
  return (0);
}

int		loading(t_core *core)
{
  t_image	*image;
  double	percent;

  if ((image = myx_image_create(core->myx, core->screen.size.x,
				core->screen.size.y)) == NULL)
    return (-1);
  percent = 0;
  myx_image_fill(image, 0);
  while (percent < 100)
    {
      percent = loading_get_percent(core);
      loading_loop(core, percent, image);
      mlx_put_image_to_window(core->myx->mlx, core->myx->win,
			      image->ptr, 0, 0);
    }
  return (0);
}
