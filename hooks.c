/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:40:38 by imarakho          #+#    #+#             */
/*   Updated: 2017/05/18 17:40:39 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	start_camera_x(t_trace *tr)
{
	t_vect tmp;

	tmp.y = tr->r->start.y * cos(tr->mv->angle_x * RAD) -
	tr->r->start.z * sin(tr->mv->angle_x * RAD);
	tmp.z = tr->r->start.z * cos(tr->mv->angle_x * RAD) +
	tr->r->start.y * sin(tr->mv->angle_x * RAD);
	tr->r->start.y = tmp.y;
	tr->r->start.z = tmp.z;
}

void	start_camera_y(t_trace *tr)
{
	t_vect tmp;

	tmp.x = tr->r->start.x * cos(tr->mv->angle_y * RAD) +
	tr->r->start.z * sin(tr->mv->angle_y * RAD);
	tmp.z = -tr->r->start.x * sin(tr->mv->angle_y * RAD) +
	tr->r->start.z * cos(tr->mv->angle_y * RAD);
	tr->r->start.x = tmp.x;
	tr->r->start.z = tmp.z;
}

void	camera_x(t_trace *tr, int x, int y)
{
	t_vect tmp;

	tmp.y = tr->a->proj[y][x].y *
	cos(tr->mv->angle_x * RAD) - sin(tr->mv->angle_x * RAD);
	tmp.z = cos(tr->mv->angle_x * RAD) +
	tr->a->proj[y][x].y * sin(tr->mv->angle_x * RAD);
	tr->a->proj[y][x].y = tmp.y;
	tr->a->proj[y][x].z = tmp.z;
	tmp = vector_norm(&tr->a->proj[y][x], &tr->r->start);
	tr->r->dir.x = tmp.x;
	tr->r->dir.y = tmp.y;
	tr->r->dir.z = tmp.z;
}

void	camera_y(t_trace *tr, int x, int y)
{
	t_vect tmp;

	tmp.x = tr->a->proj[y][x].x *
	cos(tr->mv->angle_y * RAD) - sin(tr->mv->angle_y * RAD);
	tmp.z = -tr->a->proj[y][x].x *
	sin(tr->mv->angle_y * RAD) + cos(tr->mv->angle_y * RAD);
	tr->a->proj[y][x].x = tmp.x;
	tr->a->proj[y][x].z = tmp.z;
	tmp = vector_norm(&tr->a->proj[y][x], &tr->r->start);
	tr->r->dir.x = tmp.x;
	tr->r->dir.y = tmp.y;
	tr->r->dir.z = tmp.z;
}

void	move(t_trace *tr)
{
	if (tr->mv->key == 27 || tr->mv->key == 24)
		camera_x(tr, tr->a->x, tr->a->y);
	if (tr->mv->key == 116 || tr->mv->key == 121)
		camera_y(tr, tr->a->x, tr->a->y);
	return ;
}
