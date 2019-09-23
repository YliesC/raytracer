#include "rt.h"

static t_o_mods	*get_mod(char *name, t_o_mods *mods)
{
  while (mods)
    {
      if (!strcmp(name, mods->name))
	{
	  free((void *)name);
	  return (mods);
	}
      mods = mods->next;
    }
  free((void *)name);
  return (NULL);
}

int		parse_mods(JSON_Array *mods, t_pmods **mods_list,
			   t_o_mods *o_mods)
{
  char		*tmp;
  t_pmods	mset;
  JSON_Object	*mod;
  unsigned int	i;

  i = 0;
  while (i < json_array_get_count(mods))
    {
      memset(&mset, 0, sizeof(mset));
      mod = json_array_get_object(mods, i);
      tmp = (char *)json_object_get_string(mod, "name");
      if ((mset.type = get_mod(strdup(tmp), o_mods)))
	{
	  if ((mset.enabled = json_object_get_boolean(mod, "enabled")))
	    {
	      mset.coef = json_object_get_number(mod, "ratio");
	      mset.obj = NULL;
	      if (mods_add(mods_list, &mset) < 0)
		return (-1);
	    }
	}
      i++;
    }
  return (0);
}
