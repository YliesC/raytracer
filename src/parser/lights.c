#include "rt.h"
#include "maath.h"
#include "parson.h"

static int	set_cdd(t_cdd *cdd, JSON_Array *arr)
{
  if (!arr || !cdd)
    return (VTOI puterr((void *)-1, "missing informations light\n"));
  cdd->x = json_array_get_number(arr, 0);
  cdd->y = json_array_get_number(arr, 1);
  cdd->z = json_array_get_number(arr, 2);
  return (0);
}

int		parse_lights(JSON_Array *lights, t_core *core)
{
  JSON_Object	*light;
  t_plights	set;
  char		*color;
  unsigned int	i;

  if (json_array_get_count(lights) <= 0)
    return (VTOI puterr((void*)-1, "There is no lights..."));
  i = 0;
  while (i < json_array_get_count(lights))
    {
      memset(&set, 0, sizeof(set));
      light = json_array_get_object(lights, i);
      set.type = json_object_get_number(light, "type");
      set.coef = json_object_get_number(light, "ratio");
      color = (char *)json_object_get_string(light, "color");
      set.color = (my_strlen(color) > 1) ?
	STRTOHEX(my_strlowcase(&color[1])) : 0xFFFFFF;
      set_cdd(&set.pos, json_object_get_array(light, "position"));
      lights_add(&core->lights, &set);
      i++;
    }
  return (0);
}
