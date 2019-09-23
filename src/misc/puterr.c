#include <stdio.h>
#include <stdarg.h>
#include "rt.h"

void		*puterr(void *ret, char *fmt, ...)
{
  va_list	ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  return (ret);
}
