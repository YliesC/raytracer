/*
** protos.h for rt in /home/aslafy_z/rendu/MUL_2013_rtracer
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Wed Jun  4 20:59:37 2014 Zadkiel Aslafy-Aharonian
** Last update Thu Jun 12 20:28:45 2014 Zadkiel Aslafy-Aharonian
*/

#ifndef		__RT_PROTOS__
# define	__RT_PROTOS__

# include "parson.h"

int	rt_init(t_core *, int, char **);
void	rt_free(t_core *);

int	loading(t_core *);

int	rt_args(int, char **, t_core *);
int	thread_go(t_core *);

void	rt_render(int, int *, t_core *);
int	rt_events(int, void *);

int	rt_get_color(struct s_core *, struct s_env *, struct s_pobjects *);
void	get_pos(t_cdd *, t_cd *, t_core *, double);

int	o_shapes_add(t_o_shapes **, char *, t_calc_inter, t_calc_normal);
void	o_shapes_free(t_o_shapes *);
int	o_mods_add(t_o_mods **, char *, t_calc_mod);
void	o_mods_free(t_o_mods *);

int	lights_add(t_plights **, t_plights *);
void	lights_free(t_plights *);
int	objects_add(t_pobjects **, t_pobjects *);
void	objects_free(t_pobjects *);
int	cams_add(t_pcams **, t_pcams *);
void	cams_free(t_pcams *);
int	mods_add(t_pmods **, t_pmods *);
t_pmods	*mods_get(t_pmods *, char *);
void	mods_free(t_pmods *);

int	mod_light(t_env *, t_pobjects *, t_pmods *, t_color *);
int	mod_shining(t_env *, t_pobjects *, t_pmods *, t_color *);
int	mod_shadow(t_env *, t_pobjects *, t_pmods *, t_color *);
int	mod_chess(t_env *, t_pobjects *, t_pmods *, t_color *);
int	mod_reflexion(t_env *, t_pobjects *, t_pmods *, t_color *);
int	filter_neg(t_env *, t_pobjects *, t_pmods *, t_color *);
int	filter_gray(t_env *, t_pobjects *, t_pmods *, t_color *);

double	inter_sphere(struct s_env *, struct s_pobjects *);
int	normal_sphere(struct s_env *, struct s_pobjects *);
double	inter_plane(struct s_env *, struct s_pobjects *);
int	normal_plane(struct s_env *, struct s_pobjects *);
double	inter_cylinder(struct s_env *, struct s_pobjects *);
int	normal_cylinder(struct s_env *, struct s_pobjects *);
double	inter_cone(struct s_env *, struct s_pobjects *);
int	normal_cone(struct s_env *, struct s_pobjects *);
double	inter_hyperboloid(struct s_env *, struct s_pobjects *);
int	normal_hyperboloid(struct s_env *, struct s_pobjects *);

int	parse_config(JSON_Object *, t_core *);
int	parse_objects(JSON_Array *, t_core *);
int	parse_lights(JSON_Array *, t_core *);
int	parse_mods(JSON_Array *, t_pmods **, t_o_mods *);
int	rt_parse(t_core *);

int	export_bmp(const char *, t_core *);

int	color_rgbtohex(t_color *);
void	color_hextorgb(int, t_color *);
void	color_swaprgb(t_color *);
void	rt_cddcpy(t_cdd *, t_cdd *);

int	thread_init(int, t_core *);
int	thread_fill_range(int, t_core *);
int	thread_start(int, t_core *);
int	thread_cancel(t_core *);
int	thread_join(t_core *);
void	*thread_onstart(void *);

int	event_next_cam(t_core *);
int	event_prev_cam(t_core *);
int	event_go_right(t_core *);
int	event_go_left(t_core *);
int	event_unzoom(t_core *);
int	event_zoom(t_core *);
int	event_go_down(t_core *);
int	event_go_up(t_core *);

#endif
