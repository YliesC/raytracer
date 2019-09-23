/*
** myx.h for mlx in /home/aslafy_z/rendu/
**
** Made by Zadkiel Aslafy Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Mon Nov 18 15:07:36 2013 Zadkiel Aslafy Aharonian
** Last update Fri Jun 13 15:36:06 2014 Zadkiel Aslafy-Aharonian
*/

#ifndef		__MY_X__
# define	__MY_X__

# include	<stdlib.h>
# include	<mlx.h>

typedef struct	s_image
{
  int		x;
  int		y;
  int		*data;
  void		*ptr;
  int		bpp;
  int		sizeline;
  int		endian;
}		t_image;

typedef struct	s_screen
{
  t_image	*image;
  void		*mlx;
  void		*win;
  int		x;
  int		y;
  char		*title;
}		t_screen;

typedef struct	s_cd
{
  int		x;
  int		y;
  int		z;
}		t_cd;

typedef struct	s_cdd
{
  double	x;
  double	y;
  double	z;
}		t_cdd;

t_image		*myx_image_create(t_screen *screen, int x, int y);
void		myx_image_fill(t_image *image, int color);
void		myx_image_blit(t_image *src, t_image *dest, int x, int y);
void		myx_draw_rect(t_image *image, t_cd *min, t_cd *max, int color);
void		myx_draw_line(t_image *image, t_cd *c1, t_cd *c2, int color);
int		myx_open_win(t_screen *screen);
void		myx_flip(t_screen *screen);
void		myx_pixel_put(t_image *image, int x, int y, int color);
int		myx_pixel_get(t_image *image, int x, int y);
t_screen	*myx_init(int x, int y, char *title);
t_screen	*myx_init_screen();
t_image		*myx_init_image();
void		myx_free(t_screen *screen);
t_cd		*myx_cd(t_cd *cd, int x, int y, int z);
t_cdd		*myx_cdd(t_cdd *cd, double x, double y, double z);
int		myx_expose(void *param);
int		myx_keycode(int keycode, void *param);
double		myx_sqrt(double n);
t_cd		*myx_isometry(t_cd *cd, double cte1, double cte2);

#endif
