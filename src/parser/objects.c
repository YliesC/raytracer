#include "rt.h"
#include "maath.h"
#include "parson.h"

static t_o_shapes	*get_obj(char *name, t_o_shapes *shapes)
{
  while (shapes)
    {
      if (!strcmp(name, shapes->name))
	{
	  free((void *)name);
	  return (shapes);
	}
      shapes = shapes->next;
    }
  free((void *)name);
  return (NULL);
}

static int		set_cdd(t_cdd *cdd, JSON_Array *arr, char *t, char *o)
{
  if (!arr || !cdd)
    return (VTOI puterr((void *)-1, E_PARSE_NOPRO, t, o));
  cdd->x = json_array_get_number(arr, 0);
  cdd->y = json_array_get_number(arr, 1);
  cdd->z = json_array_get_number(arr, 2);
  return (0);
}

static int		set_data(JSON_Object *obj, t_pobjects *set)
{
  char			*tmp;

  set_cdd(&set->rot, json_object_get_array(obj, "rotation"),
	  "rotation", set->type->name);
  set->ray[0] = json_object_get_number(obj, "radius1");
  set->ray[1] = json_object_get_number(obj, "radius2");
  set->shine = json_object_get_number(obj, "shine");
  tmp = (char *)json_object_get_string(obj, "color");
  set->color = (my_strlen(tmp) > 1) ?
    STRTOHEX(my_strlowcase(&tmp[1])) : 0xFFFFFF;
  return (0);
}

int			parse_objects(JSON_Array *objects, t_core *core)
{
  JSON_Object		*obj;
  t_pobjects		set;
  unsigned int		i;
  char			*tmp;

  if (json_array_get_count(objects) <= 0)
    return (VTOI puterr((void *)-1, E_PARSE_NOOBJ));
  i = -1;
  while (++i < json_array_get_count(objects))
    {
      memset(&set, 0, sizeof(set));
      obj = json_array_get_object(objects, i);
      tmp = (char *)json_object_get_string(obj, "type");
      if (!((set.type = get_obj(strdup(tmp), core->o_shapes)) == NULL ||
	    set_cdd(&set.pos, json_object_get_array(obj, "position"),
		    "position", set.type->name) < 0))
	{
	  set_data(obj, &set);
	  if (parse_mods(json_object_get_array(obj, "mods"),
			 &set.mods, core->o_mods) < 0 ||
	      objects_add(&core->objects, &set) < 0)
	    return (-1);
	}
    }
  return (0);
}
