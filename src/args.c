#include <getopt.h>
#include "rt.h"

static int	usage(char *prog)
{
  fprintf(stderr, "usage: %s [-t thread_number>0] map_file.json\n", prog);
  exit(0);
  return (0);
}

int		rt_args(int argc, char **argv, t_core *core)
{
  int		c;
  extern char	*optarg;
  extern int	optind;
  extern int	opterr;
  char		*prog;

  prog = argv[0];
  core->thdnb = 1;
  while ((c = getopt(argc , argv, "t:")) != -1)
    {
      if (c == 't')
	core->thdnb = (atoi(optarg) <= 0) ? usage(prog) : atoi(optarg);
      else if (c == '?')
	usage(prog);
    }
  if (optind >= argc)
    usage(prog);
  core->file = my_strdup(argv[optind]);
  return (0);
}
