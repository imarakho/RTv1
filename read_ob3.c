/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ob2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 18:28:16 by imarakho          #+#    #+#             */
/*   Updated: 2017/05/26 18:28:17 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_col(t_trace *tr)
{
	free(tr->rd->str);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "red:"))
		init_col(tr, 'r');
	else
		free(tr->rd->str);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "green:"))
		init_col(tr, 'g');
	else
		free(tr->rd->str);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "blue:"))
		init_col(tr, 'b');
	else
		free(tr->rd->str);
}

void		init_col(t_trace *tr, char c)
{
	int i;

	i = -1;
	free(tr->rd->str);
	while (++i < tr->rd->ob)
	{
		get_next_line(tr->rd->fd, &tr->rd->str);
		if (c == 'r')
			tr->o[i]->mt.difs.red = atof(tr->rd->str);
		else if (c == 'g')
			tr->o[i]->mt.difs.green = atof(tr->rd->str);
		else if (c == 'b')
			tr->o[i]->mt.difs.blue = atof(tr->rd->str);
		free(tr->rd->str);
	}
}

void		init_pos_2(t_trace *tr, char c, char o)
{
	int i;

	i = -1;
	free(tr->rd->str);
	while (++i < tr->rd->ob)
	{
		get_next_line(tr->rd->fd, &tr->rd->str);
		c == 'x' && o == 'p' ? tr->o[i]->pos.x = ft_atoi(tr->rd->str) : 0;
		c == 'y' && o == 'p' ? tr->o[i]->pos.y = ft_atoi(tr->rd->str) : 0;
		if (c == 'z' && o == 'p')
			tr->o[i]->pos.z = ft_atoi(tr->rd->str);
		else if (c == 'x' && o == 'n')
			tr->o[i]->norm.x = atof(tr->rd->str);
		else if (c == 'y' && o == 'n')
			tr->o[i]->norm.y = atof(tr->rd->str);
		else if (c == 'z' && o == 'n')
			tr->o[i]->norm.z = atof(tr->rd->str);
		else if (c == 'x' && o == 'f')
			tr->o[i]->figdir.x = atof(tr->rd->str);
		else if (c == 'y' && o == 'f')
			tr->o[i]->figdir.y = atof(tr->rd->str);
		else if (c == 'z' && o == 'f')
			tr->o[i]->figdir.z = atof(tr->rd->str);
		free(tr->rd->str);
	}
}

void		init_pos(t_trace *tr)
{
	free(tr->rd->str);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "x:"))
		init_pos_2(tr, 'x', 'p');
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "y:"))
		init_pos_2(tr, 'y', 'p');
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "z:"))
		init_pos_2(tr, 'z', 'p');
}

void		init_angle(t_trace *tr)
{
	int i;

	i = -1;
	free(tr->rd->str);
	while (++i < tr->rd->ob)
	{
		get_next_line(tr->rd->fd, &tr->rd->str);
		if (tr->o[i]->id == 'n')
			tr->o[i]->angle = ft_atoi(tr->rd->str) * RAD;
		free(tr->rd->str);
	}
}
