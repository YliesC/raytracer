#include "rt.h"

void		o_mods_free(t_o_mods *node)
{
  if (!node)
    return ;
  if (node->next)
    o_mods_free(node->next);
  free(node->name);
  free(node);
}

int		o_mods_add(t_o_mods **node, char *name,
			   t_calc_mod mod)
{
  t_o_mods	*tmp;
  t_o_mods	*new;

  if ((new = malloc(sizeof(t_o_mods))) == NULL)
    return (VTOI puterr((void *)-1, E_NOMEM));
  memset(new, 0, sizeof(*new));
  new->name = my_strdup(name);
  new->mod = mod;
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
