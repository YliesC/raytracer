#ifndef			__RT_ERROR__
# define		__RT_ERROR__

# include		<errno.h>

# define VTOI		(int)(size_t)

# define E_PREFIX	"rt: "
# define E_NOMEM	E_PREFIX"malloc: out of memory\n"
# define E_OPEN		E_PREFIX"open: %s: %s\n"
# define E_SYNTAX	E_PREFIX"Syntax error in %s\n"
# define E_ERROR	E_PREFIX"An error appened, exiting...\n"

# define E_PARSE	"parser: "
# define E_PARSE_NOOBJ  E_PARSE"Map must contain object(s)\n"
# define E_PARSE_NOPRO	E_PARSE"%s values aren't provided for object %s\n"

void			*puterr(void *ret, char *fmt, ...);

#endif
