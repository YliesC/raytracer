/*
** myx_init.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Dec  3 18:09:25 2013 Zadkiel Aslafy-Aharonian
** Last update Sat Jun  7 18:31:33 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

t_screen	*myx_init(int x, int y, char *title)
{
  t_screen	*screen;

  if ((screen = myx_init_screen()) == NULL
      || (screen->mlx = mlx_init()) == NULL)
    {
      write(1, "Fail to init MLX\n", 17);
      exit(1);
    }
  screen->win = NULL;
  screen->x = x;
  screen->y = y;
  screen->title = title;
  screen->image = myx_image_create(screen, x, y);
  return (screen);
}

void	myx_free(t_screen *screen)
{
  if (!screen)
    return ;
  free(screen->image);
  mlx_destroy_window(screen->mlx, screen->win);
  free(screen);
}
