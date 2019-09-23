#include "my.h"

char	*my_strdup(char *src)
{
  char	*dest;

  dest = malloc((my_strlen(src) + 1) * sizeof(char));
  if (dest)
    my_strcpy(dest, src);
  return (dest);
}
