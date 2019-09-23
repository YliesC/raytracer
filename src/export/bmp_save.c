#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "rt.h"
#include "bmp.h"

static int	bmp_write_header(t_bmpfile *bmp, int fd)
{
  if (write(fd, bmp->header.magic, sizeof(bmp->header.magic)) < 0)
    return (-1);
  if (write(fd, &(bmp->header.filesz), sizeof(uint32_t)) < 0)
    return (-1);
  if (write(fd, &(bmp->header.creator1), sizeof(uint16_t)) < 0)
    return (-1);
  if (write(fd, &(bmp->header.creator2), sizeof(uint16_t)) < 0)
    return (-1);
  if (write(fd, &(bmp->header.offset), sizeof(uint32_t)) < 0)
    return (-1);
  return (0);
}

static int	bmp_write_dib(t_bmpfile *bmp, int fd)
{
  if (write(fd, &(bmp->dib.header_sz), sizeof(uint32_t)) < 0)
    return (-1);
  if (write(fd, &(bmp->dib.width), sizeof(uint32_t)) < 0)
    return (-1);
  if (write(fd, &(bmp->dib.height), sizeof(uint32_t)) < 0)
    return (-1);
  if (write(fd, &(bmp->dib.nplanes), sizeof(uint16_t)) < 0)
    return (-1);
  if (write(fd, &(bmp->dib.depth), sizeof(uint16_t)) < 0)
    return (-1);
  if (write(fd, &(bmp->dib.compress_type), sizeof(uint32_t)) < 0)
    return (-1);
  if (write(fd, &(bmp->dib.bmp_bytesz), sizeof(uint32_t)) < 0)
    return (-1);
  if (write(fd, &(bmp->dib.hres), sizeof(uint32_t)) < 0)
    return (-1);
  if (write(fd, &(bmp->dib.vres), sizeof(uint32_t)) < 0)
    return (-1);
  if (write(fd, &(bmp->dib.ncolors), sizeof(uint32_t)) < 0)
    return (-1);
  if (write(fd, &(bmp->dib.nimpcolors), sizeof(uint32_t)) < 0)
    return (-1);
  return (0);
}

static void		bmp_get_row_data(t_bmpfile *bmp, unsigned char *buf,
					 size_t buf_len, uint32_t row)
{
  uint32_t		x;

  if (bmp->dib.width * 4 > buf_len)
    return;
  x = 0;
  while (x < bmp->dib.width)
    {
      memcpy(buf + 4 * x, (uint8_t *)&(bmp->pixels[x][row]), 4);
      x++;
    }
}

bool		bmp_save(t_bmpfile *bmp, const char *filename)
{
  int		fd;
  int		row;
  unsigned char *buf;
  int		bpl;

  if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
    return (FALSE);
  bmp_write_header(bmp, fd);
  bmp_write_dib(bmp, fd);
  bpl = (int)ceil(4 * bmp->dib.width);
  bpl = (bpl % 4 != 0) ? bpl + 4 - bpl % 4 : bpl;
  if ((buf = malloc(bpl)) == NULL)
    return (FALSE);
  row = bmp->dib.height;
  while (row >= 0)
    {
      memset(buf, 0, bpl);
      bmp_get_row_data(bmp, buf, bpl, row);
      if (write(fd, buf, bpl) < 0)
	return (FALSE);
      --row;
    }
  free(buf);
  close(fd);
  return (TRUE);
}
