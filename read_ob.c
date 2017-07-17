/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 20:49:11 by imarakho          #+#    #+#             */
/*   Updated: 2017/04/20 20:52:48 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_rad(t_trace *tr)
{
	int i;

	i = -1;
	free(tr->rd->str);
	while (++i < tr->rd->ob)
	{
		get_next_line(tr->rd->fd, &tr->rd->str);
		if (tr->o[i]->id != 'n' && tr->o[i]->id != 'p')
			tr->o[i]->rad = ft_atoi(tr->rd->str);
		free(tr->rd->str);
	}
}

void		init_norm(t_trace *tr)
{
	free(tr->rd->str);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "x:"))
		init_pos_2(tr, 'x', 'n');
	else
		free(tr->rd->str);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "y:"))
		init_pos_2(tr, 'y', 'n');
	else
		free(tr->rd->str);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "z:"))
		init_pos_2(tr, 'z', 'n');
	else
		free(tr->rd->str);
}

void		init_fdir(t_trace *tr)
{
	free(tr->rd->str);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "x:"))
		init_pos_2(tr, 'x', 'f');
	else
		free(tr->rd->str);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "y:"))
		init_pos_2(tr, 'y', 'f');
	else
		free(tr->rd->str);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "z:"))
		init_pos_2(tr, 'z', 'f');
	else
		free(tr->rd->str);
}

void		init_obj(t_trace *tr)
{
	while (get_next_line(tr->rd->fd, &tr->rd->str))
	{
		if (ft_strequ(tr->rd->str, "angle:"))
			init_angle(tr);
		else if (ft_strequ(tr->rd->str, "pos:"))
			init_pos(tr);
		else if (ft_strequ(tr->rd->str, "rad:"))
			init_rad(tr);
		else if (ft_strequ(tr->rd->str, "norm:"))
			init_norm(tr);
		else if (ft_strequ(tr->rd->str, "figdir:"))
			init_fdir(tr);
		else if (ft_strequ(tr->rd->str, "mt:"))
			init_mt(tr);
	}
}

void		read_obj(t_trace *tr, char *filename)
{
	tr->rd->fd = open(filename, O_RDONLY);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "ob ammount:"))
	{
		free(tr->rd->str);
		get_next_line(tr->rd->fd, &tr->rd->str);
		tr->rd->ob = ft_atoi(tr->rd->str);
		free(tr->rd->str);
	}
	else
	{
		ft_putstr("Wrong file!\n");
		exit(0);
	}
	struct_init(tr);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "id:"))
		init_id(tr);
	else
		free(tr->rd->str);
	init_obj(tr);
}
