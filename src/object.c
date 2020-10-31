/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 19:38:45 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/25 19:31:08 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/objects.h"

t_object	*new_object(void)
{
	t_object *result;

	if (!(result = malloc(sizeof(t_object))))
		exit(EXIT_FAILURE);
	result->exist = 0;
	result->normal_vec = NULL;
	result->color = NULL;
	result->destroy = object_destructor;
	return (result);
}

void		object_destructor(t_object *self)
{
	if (self->normal_vec != NULL && self->exist)
		self->normal_vec->destroy(self->normal_vec);
	free(self);
}

double		choice(double t1, double t2, double t_min, double t_max)
{
	double result;

	result = t_max;
	if (t1 > t_min && t1 < t_max)
		result = t1;
	if (t2 > t_min && t2 < t_max)
		result = t2;
	return (result);
}
