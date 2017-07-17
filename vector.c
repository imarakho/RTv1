/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:15:01 by imarakho          #+#    #+#             */
/*   Updated: 2017/03/30 18:12:10 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect		vector_add(t_vect *v1, t_vect *v2)
{
	t_vect res;

	res.x = v1->x + v2->x;
	res.y = v1->y + v2->y;
	res.z = v1->z + v2->z;
	return (res);
}

t_vect		vector_sub(t_vect *v1, t_vect *v2)
{
	t_vect res;

	res.x = v1->x - v2->x;
	res.y = v1->y - v2->y;
	res.z = v1->z - v2->z;
	return (res);
}

t_vect		vector_div(t_vect *v1, double d)
{
	t_vect res;

	res.x = v1->x / d;
	res.y = v1->y / d;
	res.z = v1->z / d;
	return (res);
}

double		vector_dot(t_vect *v1, t_vect *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

double		vector_mod(t_vect *v)
{
	return (sqrtf(v->x * v->x + v->y * v->y + v->z * v->z));
}
