/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:05:35 by imarakho          #+#    #+#             */
/*   Updated: 2017/03/31 17:53:46 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		check_color(t_trace *tr, double *t)
{
	int k;

	k = -1;
	while (++k < tr->rd->ob)
	{
		if (id_idef(tr, &tr->lg[tr->a->i]->l_r, t, k))
		{
			tr->a->shad = 1;
			break ;
		}
	}
	if (!tr->a->shad)
	{
		tr->a->lambr = vector_dot(&tr->lg[tr->a->i]->l_r.dir,
		&tr->o[OB]->norm) * tr->a->coef;
		tr->a->lambr += pow(tr->a->lambr, 27);
		tr->a->col.red += tr->a->lambr * tr->o[OB]->mt.difs.red;
		tr->a->col.green += tr->a->lambr * tr->o[OB]->mt.difs.green;
		tr->a->col.blue += tr->a->lambr * tr->o[OB]->mt.difs.blue;
	}
}

static void		light_handling(t_trace *tr)
{
	double	t;

	tr->a->i = -1;
	while (++tr->a->i < tr->rd->l)
	{
		tr->lg[tr->a->i]->dist =
		vector_sub(&tr->lg[tr->a->i]->pos, &tr->a->newst);
		if (vector_dot(&tr->o[OB]->norm, &tr->lg[tr->a->i]->dist) <= 0.0f)
			continue ;
		t = vector_mod(&tr->lg[tr->a->i]->dist);
		if (t <= 0.0f)
			continue ;
		vector_set(&tr->lg[tr->a->i]->l_r.start, &tr->a->newst);
		tr->lg[tr->a->i]->l_r.dir =
		vector_scale(&tr->lg[tr->a->i]->dist, 1 / t);
		tr->a->shad = 0;
		check_color(tr, &t);
	}
}

static void		vect_in(t_trace *tr)
{
	tr->a->scaled = vector_scale(&tr->r->dir, tr->d->t);
	tr->a->newst = vector_add(&tr->r->start, &tr->a->scaled);
	if (tr->o[OB]->id == 's')
	{
		tr->o[OB]->norm = vector_sub(&tr->a->newst, &tr->o[OB]->pos);
		tr->o[OB]->norm = vector_normal(&tr->o[OB]->norm);
	}
	else if (tr->o[OB]->id == 'c')
	{
		tr->a->tmp = vector_sub(&tr->a->newst, &tr->o[OB]->pos);
		tr->ray = vector_scale(&tr->o[OB]->figdir,
		vector_dot(&tr->a->tmp, &tr->o[OB]->figdir));
		tr->a->tmp = vector_sub(&tr->a->tmp, &tr->ray);
		tr->o[OB]->norm = vector_normal(&tr->a->tmp);
	}
	else if (tr->o[OB]->id == 'n')
	{
		tr->a->tmp = vector_sub(&tr->a->newst, &tr->o[OB]->pos);
		tr->ray = vector_scale(&tr->o[OB]->figdir,
		vector_cos(&tr->a->tmp, &tr->o[OB]->figdir));
		tr->o[OB]->norm = vector_sub(&tr->a->tmp, &tr->ray);
		tr->a->scaled = vector_mult(&tr->a->tmp, &tr->o[OB]->norm);
		tr->o[OB]->norm = vector_mult(&tr->a->scaled, &tr->a->tmp);
		tr->o[OB]->norm = vector_normal(&tr->o[OB]->norm);
	}
}

static void		level_handling(t_trace *tr)
{
	while ((tr->a->coef > 0.0) && (tr->a->lvl < 15))
	{
		OB = -1;
		tr->a->i = -1;
		while (++tr->a->i < tr->rd->ob)
			id_idef(tr, tr->r, &tr->d->t, tr->a->i) ? OB = tr->a->i : 0;
		if (OB == -1)
			break ;
		vect_in(tr);
		tr->a->i = -1;
		if (tr->mv->f_lght == 1)
			light_handling(tr);
		else
		{
			tr->a->col.red = (255 * tr->o[OB]->mt.difs.red);
			tr->a->col.green = (255 * tr->o[OB]->mt.difs.green);
			tr->a->col.blue = (255 * tr->o[OB]->mt.difs.blue);
		}
		tr->a->coef *= tr->o[OB]->mt.refl;
		tr->r->start = tr->a->newst;
		tr->ray = vector_scale(&tr->o[OB]->norm, 2.0f
		* vector_dot(&tr->r->dir, &tr->o[OB]->norm));
		tr->r->dir = vector_sub(&tr->r->dir, &tr->ray);
		tr->a->lvl++;
	}
}

void			ray_tracer(t_trace *tr)
{
	tr->a->y = -1;
	tr->a->i = -1;
	proj_init(tr);
	while (++tr->a->y < WIN_H)
	{
		tr->a->x = -1;
		while (++tr->a->x < WIN_W)
		{
			start_init(tr);
			tr->d->t = 200000.0f;
			tr->r->dir.x = ((2.0 * ((double)tr->a->x + 0.5)
			/ (double)WIN_W - 1.0) * ((double)WIN_W /
			(double)WIN_H) * (double)tan(30 * RAD));
			tr->r->dir.y = (2.0 * ((double)tr->a->y + 0.5)
			/ (double)WIN_H - 1.0) * (double)tan(30 * RAD);
			tr->r->dir.z = 1;
			tr->r->dir = vector_normal(&tr->r->dir);
			move(tr);
			level_handling(tr);
			ft_draw_pixel(tr->a->x, tr->a->y, tr);
		}
	}
}
