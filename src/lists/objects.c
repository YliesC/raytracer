#include "rt.h"

void		objects_free(t_pobjects *node)
{
  if (!node)
    return ;
  if (node->next)
    objects_free(node->next);
  free(node);
}

int		objects_add(t_pobjects **node, t_pobjects *data)
{
  t_pobjects	*tmp;
  t_pobjects	*new;

  if ((new = malloc(sizeof(t_pobjects))) == NULL)
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
