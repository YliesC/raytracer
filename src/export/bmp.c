#include "rt.h"
#include "bmp.h"

int		export_bmp(const char *filename, t_core *core)
{
  t_bmpfile	*bmp;
  t_cd		pos;
  t_color	rgb;
  int		color;

  bmp = bmp_create(core->screen.size.x, core->screen.size.y);
  pos.y = 0;
  while (pos.y < core->screen.size.y)
    {
      pos.x = 0;
      while (pos.x < core->screen.size.x)
	{
	  color = myx_pixel_get(core->myx->image, pos.x, pos.y);
	  color_hextorgb(color, &rgb);
	  color_swaprgb(&rgb);
	  bmp_set_pixel(bmp, pos.x, pos.y, rgb);
	  pos.x++;
	}
      pos.y++;
    }
  if (!bmp_save(bmp, filename))
    return (printf("rt: cannot save file\n"));
  bmp_destroy(bmp);
  return (0);
}
