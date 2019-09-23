#include "rt.h"
#include "bmp.h"

static int	bmp_malloc_pixels(t_bmpfile *bmp)
{
  uint32_t	x;
  uint32_t	y;

  if ((bmp->pixels = malloc(sizeof(t_color *) * bmp->dib.width)) == NULL)
    return (-1);
  x = 0;
  while (x < bmp->dib.width)
    {
      if ((bmp->pixels[x] = malloc(sizeof(t_color)
				   * bmp->dib.height)) == NULL)
	return (-1);
      y = 0;
      while (y < bmp->dib.height)
	{
	  bmp->pixels[x][y].r = 255;
	  bmp->pixels[x][y].g = 255;
	  bmp->pixels[x][y].b = 255;
	  bmp->pixels[x][y].a = 0;
	  y++;
	}
      x++;
    }
  return (0);
}

t_bmpfile	*bmp_create(uint32_t width, uint32_t height)
{
  t_bmpfile	*result;
  uint32_t	bytes_per_line;

  if ((result = malloc(sizeof(t_bmpfile))) == NULL)
    return (NULL);
  memset(result, 0, sizeof(t_bmpfile));
  result->header.magic[0] = 'B';
  result->header.magic[1] = 'M';
  result->dib.header_sz = 40;
  result->dib.width = width;
  result->dib.height = height;
  result->dib.nplanes = 1;
  result->dib.depth = 32;
  result->dib.hres = DEFAULT_DPI_X;
  result->dib.vres = DEFAULT_DPI_Y;
  result->dib.compress_type = BI_RGB;
  bytes_per_line = (int)ceil(4 * result->dib.width);
  if (bytes_per_line % 4 != 0)
    bytes_per_line += 4 - bytes_per_line % 4;
  result->dib.bmp_bytesz = bytes_per_line * result->dib.height;
  result->header.offset = 14 + result->dib.header_sz + 0;
  result->header.filesz = result->header.offset + result->dib.bmp_bytesz;
  if (bmp_malloc_pixels(result) < 0)
    return (NULL);
  return (result);
}

void		bmp_destroy(t_bmpfile *bmp)
{
  uint32_t	x;

  x = 0;
  while (x < bmp->dib.width)
    free(bmp->pixels[x++]);
  free(bmp->pixels);
  bmp->pixels = NULL;
  free(bmp);
}

bool		bmp_set_pixel(t_bmpfile *bmp, uint32_t x,
			      uint32_t y, t_color pixel)
{
  if ((x >= bmp->dib.width) || (y >= bmp->dib.height))
    return (FALSE);
  bmp->pixels[x][y] = pixel;
  return (TRUE);
}
