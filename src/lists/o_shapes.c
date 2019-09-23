#include "rt.h"

void		o_shapes_free(t_o_shapes *node)
{
  if (!node)
    return ;
  if (node->next)
    o_shapes_free(node->next);
  free(node->name);
  free(node);
}

int		o_shapes_add(t_o_shapes **node, char *name,
			     t_calc_inter inter, t_calc_normal normal)
{
  t_o_shapes	*tmp;
  t_o_shapes	*new;

  if ((new = malloc(sizeof(t_o_shapes))) == NULL)
    return (VTOI puterr((void *)-1, E_NOMEM));
  memset(new, 0, sizeof(*new));
  new->name = my_strdup(name);
  new->inter = inter;
  new->normal = normal;
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
