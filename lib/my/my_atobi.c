#include <math.h>

static int	my_charstr_base(char *src, char to_find)
{
  int		i;
  int		result;

  i = 0;
  result = 0;
  while (src && src[i])
    {
      if (src[i] == to_find)
	result = result + 1;
      i = i + 1;
    }
  if (result != 1)
    return (0);
  return (1);
}

static int	my_getposin_base(char *src, char to_find)
{
  int		i;

  i = 0;
  while (src && src[i])
    {
      if (src[i] == to_find)
	return (i);
      i = i + 1;
    }
  return (0);
}

static int	my_atobi_calc(char *str, int i, int neg, char *base)
{
  int		result;
  int		len;
  int		pos;
  int		j;

  len = 0;
  result = 0;
  j = 0;
  while (str[i + len])
    {
      if (!my_charstr_base(base, str[i + len]))
	return (0);
      len++;
    }
  len--;
  while (len >= 0)
    {
      pos = my_getposin_base(base, str[i + j]);
      result += (pos * pow(my_strlen(base), len));
      j = j + 1;
      len = len - 1;
    }
  return ((neg) ? -result : result);
}

int	my_atobi(char *str, char *base)
{
  int	i;
  int	neg;

  i = 0;
  neg = 0;
  if (my_strlen(str) == 0 || my_strlen(base) == 0)
    return (0);
  while (str[i] == '+' || str[i] == '-')
    {
      if (str[i] == '-')
	neg = ((neg == 0) ? 1 : 0);
      i++;
    }
  return (my_atobi_calc(str, i, neg, base));
}
