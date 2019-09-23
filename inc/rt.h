#ifndef		__RT_H__
# define	__RT_H__

# include	<unistd.h>
# include	<pthread.h>
# include	<string.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	"my.h"
# include	"myx.h"
# include	"error.h"

# define	CHESSPLANE_SIZE		10
# define	RATIO_REFLEX	        50

typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned int		uint32_t;

enum light_type
  {
    L_DIFFUSE = 0,
    L_AMBIENT,
    L_SPOT
  };

typedef struct s_core		t_core;
typedef struct s_threads	t_threads;
typedef struct s_thd		t_thd;
typedef struct s_o_shapes	t_o_shapes;
typedef struct s_o_mods		t_o_mods;
typedef struct s_plights	t_plights;
typedef struct s_pobjects	t_pobjects;
typedef struct s_pmods		t_pmods;
typedef struct s_pscreen	t_pscreen;
typedef struct s_pcams		t_pcams;
typedef struct s_color		t_color;
typedef struct s_env		t_env;

struct			__attribute__((packed)) s_color
{
  uint8_t		r;
  uint8_t		g;
  uint8_t		b;
  uint8_t		a;
};

struct			__attribute__((packed)) s_pcams
{
  char			*name;
  struct s_cdd		pos;
  struct s_cdd		rot;
  struct s_pcams	*prev;
  struct s_pcams	*next;
};

struct			__attribute__((packed)) s_pscreen
{
  char			*name;
  struct s_cd		size;
};

struct			__attribute__((packed)) s_plights
{
  enum light_type	type;
  struct s_cdd		pos;
  double		coef;
  unsigned int		color;
  struct s_plights	*prev;
  struct s_plights	*next;
};

struct			__attribute__((packed)) s_pobjects
{
  struct s_o_shapes	*type;
  struct s_cdd		pos;
  struct s_cdd		rot;
  struct s_cdd		lim;
  unsigned int		ray[2];
  unsigned int		color;
  double		shine;
  struct s_pmods	*mods;
  struct s_pobjects	*prev;
  struct s_pobjects	*next;
};

struct			__attribute__((packed)) s_pmods
{
  struct s_o_mods	*type;
  struct s_pobjects	*obj;
  unsigned int		enabled;
  double		coef;
  struct s_pmods	*prev;
  struct s_pmods	*next;
};

struct			__attribute__((packed)) s_env
{
  double		k;
  struct s_cdd		pos;
  struct s_cdd		pnt;
  struct s_cdd		norm;
  struct s_cdd		cam_pos;
  struct s_cdd		vect;
  int			reflex;
};

struct			__attribute__((packed)) s_threads
{
  unsigned int		nbr;
  pthread_t		*pth;
  pthread_mutex_t	mutx;
  int			**pix;
  char			*state;
};

struct			__attribute__((packed)) s_thd
{
  int			id;
  struct s_core		*core;
};

struct			__attribute__((packed)) s_core
{
  char			*file;
  unsigned int		thdnb;
  unsigned int		antia;
  int			preview;
  char			*export;
  struct s_screen	*myx;
  struct s_pscreen	screen;
  struct s_pmods	*mods;
  struct s_pcams	*cams;
  struct s_pcams	*curr_cam;
  struct s_plights	*lights;
  struct s_pobjects	*objects;
  struct s_o_shapes	*o_shapes;
  struct s_o_mods	*o_mods;
  struct s_threads	threads;
  struct s_image	*loading;
};

typedef double	(*t_calc_inter)(struct s_env *, struct s_pobjects *);
typedef int	(*t_calc_normal)(struct s_env *, struct s_pobjects *);
typedef int	(*t_calc_mod)(struct s_env *, struct s_pobjects *,
			      struct s_pmods *, struct s_color *);

struct			__attribute__((packed)) s_o_shapes
{
  char			*name;
  t_calc_inter		inter;
  t_calc_normal		normal;
  struct s_o_shapes	*prev;
  struct s_o_shapes	*next;
};

struct			__attribute__((packed)) s_o_mods
{
  char			*name;
  t_calc_mod		mod;
  struct s_o_mods	*prev;
  struct s_o_mods	*next;
};

t_core		*g_core;

# include	"protos.h"

#endif
