/*
** mods.c for rt in /home/aslafy_z/rendu/MUL_2013_rtracer/src/lists
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Wed Jun  4 19:28:14 2014 Zadkiel Aslafy-Aharonian
** Last update Fri Jun 13 12:42:58 2014 Zadkiel Aslafy-Aharonian
*/

#include "rt.h"

void		mods_free(t_pmods *node)
{
  if (!node)
    return ;
  if (node->next)
    mods_free(node->next);
  free(node);
}

t_pmods		*mods_get(t_pmods *mods, char *name)
{
  while (mods)
    {
      if (!strcmp(mods->type->name, name))
	return (mods);
      mods = mods->next;
    }
  return (NULL);
}

int		mods_add(t_pmods **node, t_pmods *data)
{
  t_pmods	*tmp;
  t_pmods	*new;

  if ((new = malloc(sizeof(t_pmods))) == NULL)
    return (VTOI puterr((void *)-1, E_NOMEM));
  memcpy(new, data, sizeof(*data));
  if (*node)
    {
      tmp = *node;
      while (tmp->next)
	tmp = tmp->next;
      new->prev = tmp;
      tmp->next = new;
    }
  else
    *node = new;
  return (0);
}
