/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 15:01:18 by imarakho          #+#    #+#             */
/*   Updated: 2017/03/30 17:26:09 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	min(int a, int b)
{
	return (((a) < (b)) ? (a) : (b));
}

void			ft_draw_pixel(int x, int y, t_trace *tr)
{
	int		a;

	tr->m->bpp = 0;
	tr->m->sizeline = 0;
	tr->m->endian = 0;
	tr->m->imbuf = mlx_get_data_addr(tr->m->img, &tr->m->bpp,
	&tr->m->sizeline, &tr->m->endian);
	a = y * tr->m->sizeline + (x << 2);
	tr->m->imbuf[a] = (unsigned char)min(tr->a->col.blue * 255.0f, 255.0f);
	tr->m->imbuf[a + 1] = (unsigned char)min(tr->a->col.green * 255.0f, 255.0f);
	tr->m->imbuf[a + 2] = (unsigned char)min(tr->a->col.red * 255.0f, 255.0f);
}
