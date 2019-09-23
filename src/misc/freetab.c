/*
** misc.c for rt in /home/aslafy_z/rendu/MUL_2013_rtracer
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Thu May 29 18:36:42 2014 Zadkiel Aslafy-Aharonian
** Last update Thu May 29 18:38:29 2014 Zadkiel Aslafy-Aharonian
*/

#include "rt.h"

void	rt_freetab(char **tab)
{
  int	i;

  i = 0;
  while (tab && tab[i])
    free(tab[i++]);
  free(tab);
}
