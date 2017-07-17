/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 13:37:31 by imarakho          #+#    #+#             */
/*   Updated: 2017/04/19 13:37:32 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char	square(t_trace *tr, double discr, double *t)
{
	if (discr < 0)
		return (0);
	else
	{
		tr->d->t0 = (-tr->d->b + sqrtf(discr)) / (2 * tr->d->a);
		tr->d->t1 = (-tr->d->b - sqrtf(discr)) / (2 * tr->d->a);
		if (tr->d->t0 < 0.1f && tr->d->t1 < 0.1f)
			return (0);
		else if (tr->d->t0 > tr->d->t1)
			tr->d->t0 = tr->d->t1;
		else if (tr->d->t0 < 0.1f)
			tr->d->t0 = tr->d->t1;
		if ((tr->d->t0 > 0.1f) && (tr->d->t0 <= *t))
		{
			*t = tr->d->t0;
			return (1);
		}
	}
	return (0);
}

char		inter_ray_sphere(t_ray *r, t_ob *s, t_trace *tr, double *t)
{
	t_vect	dist;

	tr->d->a = vector_dot(&r->dir, &r->dir);
	dist = vector_sub(&r->start, &s->pos);
	tr->d->b = 2 * vector_dot(&r->dir, &dist);
	tr->d->c = vector_dot(&dist, &dist) - (s->rad * s->rad);
	return (square(tr, tr->d->b * tr->d->b - 4 * tr->d->a * tr->d->c, t));
}

char		inter_ray_plane(t_trace *tr, t_ob *p, t_ray *r, double *t)
{
	double d;

	d = vector_dot(&p->norm, &r->dir);
	if (d != 0)
	{
		tr->ray = vector_sub(&p->pos, &r->start);
		tr->d->a = vector_dot(&p->norm, &tr->ray);
		tr->d->t0 = tr->d->a / d;
		if (tr->d->t0 > 0.1f && (tr->d->t0 <= *t))
		{
			*t = tr->d->t0;
			return (1);
		}
	}
	return (0);
}

char		inter_ray_cylinder(t_ob *cyl, t_trace *tr, t_ray *r, double *t)
{
	t_vect		delta;
	double		res;
	t_vect		sa;
	t_vect		sb;

	delta = vector_sub(&r->start, &cyl->pos);
	res = vector_dot(&r->dir, &cyl->figdir);
	tr->ray = vector_scale(&cyl->figdir, res);
	sa = vector_sub(&r->dir, &tr->ray);
	res = vector_dot(&delta, &cyl->figdir);
	tr->ray = vector_scale(&cyl->figdir, res);
	sb = vector_sub(&delta, &tr->ray);
	tr->d->a = vector_dot(&sa, &sa);
	tr->d->b = 2 * vector_dot(&sa, &sb);
	tr->d->c = vector_dot(&sb, &sb) - cyl->rad * cyl->rad;
	return (square(tr, tr->d->b * tr->d->b - 4 * tr->d->a * tr->d->c, t));
}

char		inter_ray_cone(t_ob *cn, t_trace *tr, t_ray *r, double *t)
{
	t_vect		delta;
	double		res1;
	double		res2;
	t_vect		sa;
	t_vect		sb;

	delta = vector_sub(&r->start, &cn->pos);
	res1 = vector_dot(&r->dir, &cn->figdir);
	tr->ray = vector_scale(&cn->figdir, res1);
	sa = vector_sub(&r->dir, &tr->ray);
	res2 = vector_dot(&delta, &cn->figdir);
	tr->ray = vector_scale(&cn->figdir, res2);
	sb = vector_sub(&delta, &tr->ray);
	tr->d->a = cos(cn->angle) * cos(cn->angle) * vector_dot(&sa, &sa) -
	sin(cn->angle) * sin(cn->angle) * (res1 * res1);
	tr->d->b = 2 * cos(cn->angle) * cos(cn->angle) * vector_dot(&sa, &sb) -
	2 * sin(cn->angle) * sin(cn->angle) * (res1 * res2);
	tr->d->c = cos(cn->angle) * cos(cn->angle) * vector_dot(&sb, &sb) -
	sin(cn->angle) * sin(cn->angle) * (res2 * res2);
	return (square(tr, tr->d->b * tr->d->b - 4 * tr->d->a * tr->d->c, t));
}
