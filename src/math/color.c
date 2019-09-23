#include "rt.h"

void	color_swaprgb(t_color *rgb)
{
  int	tmp;

  tmp = rgb->b;
  rgb->b = rgb->r;
  rgb->r = tmp;
}

void	color_hextorgb(int color, t_color *rgb)
{
  rgb->r = (color >> 16) & 0xFF;
  rgb->g = (color >> 8) & 0xFF;
  rgb->b = color & 0xFF;
}

int	color_rgbtohex(t_color *rgb)
{
  return (((rgb->r & 0xff) << 16) + ((rgb->g & 0xff) << 8)
	  + (rgb->b & 0xff));
}
