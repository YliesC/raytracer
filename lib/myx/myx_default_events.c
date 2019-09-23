/*
** myx_default_events.c for myx in /home/aslafy_z/rendu/CPE-2013-BSQ
**
** Made by Zadkiel Aslafy-Aharonian
** Login   <aslafy_z@epitech.net>
**
** Started on  Sun Dec  8 15:43:39 2013 Zadkiel Aslafy-Aharonian
** Last update Fri Mar 28 16:09:50 2014 Zadkiel Aslafy-Aharonian
*/

#include "myx.h"

int		myx_expose(void *param)
{
  t_screen	*screen;

  screen = (t_screen *) param;
  myx_flip(screen);
  return (0);
}

int	myx_keycode(int keycode, void *param)
{
  if (keycode == 65307)
    exit(0);
  return (0);
}
