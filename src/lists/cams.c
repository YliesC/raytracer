#include "rt.h"

void		cams_free(t_pcams *node)
{
  if (!node)
    return ;
  if (node->next)
    cams_free(node->next);
  free(node);
}

int		cams_add(t_pcams **node, t_pcams *data)
{
  t_pcams	*tmp;
  t_pcams	*new;

  if ((new = malloc(sizeof(t_pcams))) == NULL)
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
