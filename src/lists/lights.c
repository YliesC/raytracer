#include "rt.h"

void		lights_free(t_plights *node)
{
  if (!node)
    return ;
  if (node->next)
    lights_free(node->next);
  free(node);
}

int		lights_add(t_plights **node, t_plights *data)
{
  t_plights     *tmp;
  t_plights     *new;

  if ((new = malloc(sizeof(t_plights))) == NULL)
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
