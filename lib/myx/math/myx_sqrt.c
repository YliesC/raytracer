/*
** myx_sqrt.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf/myx
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Dec  3 21:51:42 2013 Zadkiel Aslafy-Aharonian
** Last update Tue Dec  3 22:02:17 2013 Zadkiel Aslafy-Aharonian
*/

double		myx_sqrt(double n)
{
  double	e;
  double	ne;
  int		i;

  ne = n-1;
  e = n;
  i = 0;
  while (e != ne && i != 20)
    {
      e = ne;
      ne = e - (e * e - n) / (2 * e);
      i++;
    }
  return (ne);
}
