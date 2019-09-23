#include "rt.h"
#include "parson.h"

static int	set_cdd(t_cdd *cdd, JSON_Array *arr)
{
  if (!arr || !cdd)
    return (VTOI puterr((void *)-1, "missing informations about cams\n"));
  cdd->x = json_array_get_number(arr, 0);
  cdd->y = json_array_get_number(arr, 1);
  cdd->z = json_array_get_number(arr, 2);
  return (0);
}

static int	config_cams(JSON_Array *cams, t_core *core)
{
  const char	*tmp_name;
  t_pcams	cset;
  JSON_Object	*cam;
  unsigned int	i;

  i = 0;
  while (i < json_array_get_count(cams))
    {
      memset(&cset, 0, sizeof(cset));
      cam = json_array_get_object(cams, i);
      tmp_name = json_object_get_string(cam, "name");
      cset.name = strdup(tmp_name);
      free((void *)tmp_name);
      if (set_cdd(&cset.pos, json_object_get_array(cam, "position")) < 0)
	return (-1);
      if (set_cdd(&cset.rot, json_object_get_array(cam, "rotation")) < 0)
	return (-1);
      if (cams_add(&core->cams, &cset) < 0)
	return (-1);
      i++;
    }
  return (0);
}

int		parse_config(JSON_Object *config, t_core *core)
{
  char		*tmp;
  JSON_Object	*screen;
  JSON_Array	*pos;

  screen = json_object_get_object(config, "screen");
  pos = json_object_get_array(screen, "size");
  core->screen.size.x = json_array_get_number(pos, 0);
  core->screen.size.y = json_array_get_number(pos, 1);
  core->preview = json_object_get_boolean(config, "preview");
  core->preview = (core->preview < 0) ? 0 : core->preview;
  tmp = (char *)json_object_get_string(config, "export");
  core->export = (tmp && strlen(tmp) > 4) ? strdup(tmp) : NULL;
  core->antia = json_object_get_number(config, "antialiasing");
  core->antia = (core->antia <= 0) ? 1 : core->antia;
  tmp = (char *)json_object_get_string(screen, "name");
  core->screen.name = strdup(tmp);
  free((void *)tmp);
  if (parse_mods(json_object_get_array(config, "mods"),
		 &core->mods, core->o_mods) < 0)
    return (-1);
  if (config_cams(json_object_get_array(config, "cams"), core) < 0)
    return (-1);
  return (0);
}
