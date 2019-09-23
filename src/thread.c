#include "rt.h"

int		thread_join(t_core *core)
{
  unsigned int	i;

  i = 0;
  while (i < core->threads.nbr)
    {
      if (pthread_join(core->threads.pth[i], NULL))
	return (VTOI puterr((void *)-1, E_PREFIX" %s\n",
			    strerror(errno)));
      i++;
    }
  return (0);
}

int		thread_cancel(t_core *core)
{
  unsigned int	i;

  i = 0;
  while (i < core->threads.nbr)
    {
      if (pthread_cancel(core->threads.pth[i]))
	return (VTOI puterr((void *)-1, E_PREFIX" %s\n",
			    strerror(errno)));
      i++;
    }
  return (0);
}

int		thread_start(int n, t_core *core)
{
  t_thd		*thd;
  int		i;

  i = 0;
  while (i < n)
    {
      if (!(thd = malloc(sizeof(t_thd))))
	{
	  thread_cancel(core);
	  return (VTOI puterr((void *)-1, E_NOMEM));
	}
      thd->core = core;
      thd->id = i;
      if (pthread_create(&core->threads.pth[i], NULL,
			 thread_onstart, (void *)thd))
	{
	  thread_cancel(core);
	  return (VTOI puterr((void *)-1, E_PREFIX" %s\n",
			      strerror(errno)));
	}
      core->threads.nbr++;
      i++;
    }
  return (0);
}

int		thread_fill_range(int n, t_core *core)
{
  int		i;
  int		p;
  int		r;

  r = ((core->screen.size.x * core->screen.size.y) / n) - 1;
  p = 0;
  i = 0;
  while (i < n)
    {
      if (!(core->threads.pix[i] = malloc(sizeof(int) * 2)))
	return (VTOI puterr((void *)-1, E_NOMEM));
      core->threads.pix[i][0] = p;
      core->threads.pix[i][1] = p + r;
      p += r + 1;
      i++;
    }
  return (0);
}

int		thread_init(int n, t_core *core)
{
  if (n <= 0)
    return (VTOI puterr((void *)-1, E_PREFIX"not correct nb of thread\n"));
  memset(&core->threads, 0, sizeof(t_threads));
  core->threads.nbr = 0;
  if (!(core->threads.pth = malloc(sizeof(pthread_t) * n)) ||
      !(core->threads.pix = malloc((sizeof(int) * n * 2))) ||
      !(core->threads.state = malloc(sizeof(char) * n)))
    return (VTOI puterr((void *)-1, E_NOMEM));
  memset(core->threads.pth, 0, sizeof(pthread_t) * n);
  memset(core->threads.pix, 0, sizeof(int) * n);
  memset(core->threads.state, 0, sizeof(char) * n);
  pthread_mutex_init(&core->threads.mutx, NULL);
  thread_fill_range(n, core);
  return (0);
}
