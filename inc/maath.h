#ifndef		__RT_MATH__
# define	__RT_MATH__

# include	<math.h>
# include	<complex.h>
# include	"myx.h"

# ifndef	M_PI
#  define	M_PI		3.1415926
# endif
# define	SQ(x)		((x) * (x))
# define	EPSILON		0.0000001
# define	RAD(a)		(M_PI * (a) / 180.0f)
# define	STRTOHEX(s)	(my_atobi((s), "0123456789abcdef"))

typedef struct		s_solver
{
  double		a;
  double		b;
  double		c;
  double		d;
  double		e;
  double complex	x[4];
}			t_solver;

void		math_invtranslate(t_cdd *, t_cdd *, t_cdd *);
void		math_invrotate(t_cdd *, t_cdd *, t_cdd *);
void		math_rotate(t_cdd *, t_cdd *, t_cdd *);
double		math_dot(t_cdd *, t_cdd *);
void		math_normalize(t_cdd *, t_cdd *);
double		math_interpolate(double start, double end, double lamda);
void		math_cddcpy(t_cdd *dest, t_cdd *src);
void		solve_init(t_solver *s);
double		solve_diff(int n, t_solver *s);
int		solve_two(t_solver *s);
int		solve_three(t_solver *s);

#endif
