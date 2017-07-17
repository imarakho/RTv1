/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:31:23 by imarakho          #+#    #+#             */
/*   Updated: 2017/03/30 16:44:44 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		destroy_window(void)
{
	exit(1);
	return (0);
}

void	struct_init(t_trace *tr)
{
	int i;

	tr->a = (t_alg *)ft_memalloc(sizeof(t_alg));
	tr->mv = (t_move *)ft_memalloc(sizeof(t_move));
	tr->m = (t_mlx *)ft_memalloc(sizeof(t_mlx));
	tr->d = (t_discr *)ft_memalloc(sizeof(t_discr));
	tr->r = (t_ray *)ft_memalloc(sizeof(t_ray));
	tr->o = (t_ob **)ft_memalloc(sizeof(t_ob*) * tr->rd->ob + 1);
	tr->o[tr->rd->ob] = NULL;
	i = -1;
	while (++i < tr->rd->ob)
		tr->o[i] = (t_ob *)ft_memalloc(sizeof(t_ob));
}

int		key_func(int key, t_trace *tr)
{
	int a;

	key == 27 ? tr->mv->angle_x += 5 : 0;
	key == 24 ? tr->mv->angle_x -= 5 : 0;
	key == 116 ? tr->mv->angle_y += 5 : 0;
	key == 121 ? tr->mv->angle_y -= 5 : 0;
	if (key == 53)
		exit(1);
	key == 10 ? tr->mv->f_lght *= -1 : 0;
	key == 6 ? tr->mv->move_z += 30 : 0;
	key == 50 ? tr->mv->move_z -= 30 : 0;
	key == 16 ? tr->mv->move_y += 30 : 0;
	if (key == 32)
		tr->mv->move_y -= 30;
	if (key == 7)
		tr->mv->move_x += 30;
	if (key == 8)
		tr->mv->move_x -= 30;
	tr->mv->key = key;
	tr->m->img = mlx_new_image(tr->m->mlx, WIN_W, WIN_H);
	ray_tracer(tr);
	a = mlx_put_image_to_window(tr->m->mlx, tr->m->win, tr->m->img, 0, 0);
	mlx_destroy_image(tr->m->mlx, tr->m->img);
	return (0);
}

void	ft_norm(t_trace *tr)
{
	int i;

	i = -1;
	while (++i < tr->rd->ob)
	{
		if (tr->o[i]->id == 'c' || tr->o[i]->id == 'n')
			tr->o[i]->figdir = vector_normal(&tr->o[i]->figdir);
	}
}

int		main(int argc, char **argv)
{
	t_trace		*tr;
	int			a;

	if (argc != 3)
	{
		ft_putstr("Wrong number of files!\n");
		exit(1);
	}
	tr = (t_trace *)ft_memalloc(sizeof(t_trace));
	tr->rd = (t_read *)ft_memalloc(sizeof(t_read));
	read_obj(tr, argv[1]);
	tr->m->mlx = mlx_init();
	tr->m->win = mlx_new_window(tr->m->mlx, WIN_W, WIN_H, "RTv1");
	tr->m->img = mlx_new_image(tr->m->mlx, WIN_W, WIN_H);
	read_l(tr, argv[2]);
	ft_norm(tr);
	tr->mv->move_z = 0;
	tr->mv->f_lght = 1;
	ray_tracer(tr);
	a = mlx_put_image_to_window(tr->m->mlx, tr->m->win, tr->m->img, 0, 0);
	mlx_destroy_image(tr->m->mlx, tr->m->img);
	mlx_hook(tr->m->win, 2, 0, key_func, tr);
	mlx_hook(tr->m->win, 17, 0, destroy_window, 0);
	mlx_loop(tr->m->mlx);
	return (0);
}
