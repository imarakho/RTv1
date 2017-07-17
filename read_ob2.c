/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ob2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 18:34:34 by imarakho          #+#    #+#             */
/*   Updated: 2017/05/26 19:57:02 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			init_refl(t_trace *tr)
{
	int i;

	i = -1;
	free(tr->rd->str);
	while (++i < tr->rd->ob)
	{
		get_next_line(tr->rd->fd, &tr->rd->str);
		tr->o[i]->mt.refl = atof(tr->rd->str);
		free(tr->rd->str);
	}
}

void			init_mt(t_trace *tr)
{
	free(tr->rd->str);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "difs:"))
		ft_col(tr);
	else
		free(tr->rd->str);
	get_next_line(tr->rd->fd, &tr->rd->str);
	if (ft_strequ(tr->rd->str, "refl:"))
		init_refl(tr);
	else
		free(tr->rd->str);
}

t_vect			vector_scale(t_vect *v, double s)
{
	t_vect res;

	res.x = v->x * s;
	res.y = v->y * s;
	res.z = v->z * s;
	return (res);
}
