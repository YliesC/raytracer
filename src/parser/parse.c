#include "rt.h"
#include "parson.h"

int		rt_parse(t_core *core)
{
  JSON_Value	*root_value;
  JSON_Object	*root_object;

  if ((root_value = json_parse_file_with_comments(core->file)) == NULL)
    return (VTOI puterr((void*)-1, E_OPEN, core->file, "is not a json file."));
  if (json_value_get_type(root_value) != JSONObject)
    return (VTOI puterr((void*)-1, E_SYNTAX, core->file));
  root_object = json_value_get_object(root_value);
  if (parse_lights(json_object_get_array(root_object, "lights"), core))
    return (-1);
  if (parse_config(json_object_get_object(root_object, "config"), core))
    return (-1);
  if (parse_objects(json_object_get_array(root_object, "objects"), core))
    return (-1);
  return (0);
}
