/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:48:42 by imarakho          #+#    #+#             */
/*   Updated: 2017/05/26 20:05:22 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect		vector_mult(t_vect *v1, t_vect *v2)
{
	t_vect res;

	res.x = v1->x * v2->x;
	res.y = v1->y * v2->y;
	res.z = v1->z * v2->z;
	return (res);
}

double		vector_cos(t_vect *v, t_vect *v1)
{
	return (vector_dot(v, v1) / (vector_mod(v) * vector_mod(v1)));
}

t_vect		vector_norm(t_vect *r, t_vect *start)
{
	t_vect		v;
	double		len;
	t_vect		res;

	v = vector_sub(r, start);
	len = vector_mod(&v);
	res = vector_div(&v, len);
	return (res);
}

t_vect		vector_normal(t_vect *v)
{
	double	len;
	t_vect	res;

	len = vector_mod(v);
	res = vector_div(v, len);
	return (res);
}

void		vector_set(t_vect *n, t_vect *v)
{
	n->x = v->x;
	n->y = v->y;
	n->z = v->z;
}
