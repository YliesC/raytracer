/*
** myx_flip.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Dec  3 18:03:25 2013 Zadkiel Aslafy-Aharonian
** Last update Fri Jun 13 12:39:07 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

void	myx_flip(t_screen *screen)
{
  mlx_put_image_to_window(screen->mlx, screen->win,
			  screen->image->ptr, 0, 0);
}
