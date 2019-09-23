/*
** myx_open_win.c for myx in /home/aslafy_z/rendu/MUL_2013_rtracer/lib/myx
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Sat Jun  7 18:29:24 2014 Zadkiel Aslafy-Aharonian
** Last update Sat Jun  7 18:31:18 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

int	myx_open_win(t_screen *screen)
{
  if (!screen)
    return (-1);
  screen->win = mlx_new_window(screen->mlx, screen->x,
			       screen->y, screen->title);
  return (0);
}
