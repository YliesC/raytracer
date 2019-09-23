#ifndef		__BMP_RT__
# define	__BMP_RT__

# include	<math.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>

# ifndef	bool
typedef int	bool;
#  define	FALSE	(0)
#  define	TRUE	!FALSE
# endif

# define	DEFAULT_DPI_X	3780
# define	DEFAULT_DPI_Y	3780
# define	DPI_FACTOR	39.37007874015748
# define	BI_RGB		0

typedef struct	s_bmp_header
{
  uint8_t	magic[2];
  uint32_t	filesz;
  uint16_t	creator1;
  uint16_t	creator2;
  uint32_t	offset;
}		t_bmp_header;

typedef struct	s_bmp_dib
{
  uint32_t	header_sz;
  uint32_t	width;
  uint32_t	height;
  uint16_t	nplanes;
  uint16_t	depth;
  uint32_t	compress_type;
  uint32_t	bmp_bytesz;
  uint32_t	hres;
  uint32_t	vres;
  uint32_t	ncolors;
  uint32_t	nimpcolors;
}		t_bmp_dib;

typedef struct	s_bmpfile
{
  t_bmp_header	header;
  t_bmp_dib	dib;
  t_color	**pixels;
  t_color	*colors;
}		t_bmpfile;

t_bmpfile	*bmp_create(uint32_t width, uint32_t height);
void		bmp_destroy(t_bmpfile *bmp);
bool		bmp_set_pixel(t_bmpfile *bmp, uint32_t x,
			      uint32_t y, t_color pixel);
bool		bmp_save(t_bmpfile *bmp, const char *filename);

#endif /* __BMP_RT__ */
