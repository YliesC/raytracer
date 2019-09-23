char	*my_strlowcase(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] >= 'A' && str[i] <= 'Z')
	str[i] = 'a' + (str[i] - 'A');
      i++;
    }
  return (str);
}
