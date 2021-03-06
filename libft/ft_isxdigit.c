/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xdigit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:23:56 by imarakho          #+#    #+#             */
/*   Updated: 2016/11/30 18:26:08 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_xisdigit(int c)
{
	if ((c >= 'A' && c <= 'F') || (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}
