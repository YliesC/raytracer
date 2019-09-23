/*
** myx_init_screen.c for myx in /home/aslafy_z/rendu/MUL_2013_fdf
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Tue Dec  3 18:10:03 2013 Zadkiel Aslafy-Aharonian
** Last update Fri May  9 14:55:58 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

t_screen	*myx_init_screen()
{
  t_screen	*screen;

  if ((screen = malloc(sizeof(t_screen))) == NULL)
    return (NULL);
  screen->mlx = NULL;
  screen->win = NULL;
  screen->image = NULL;
  screen->x = 0;
  screen->y = 0;
  screen->title = NULL;
}
