/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecalg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 22:59:37 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/25 18:36:18 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/linalg.h"

t_vec		*new_vector(double x, double y, double z)
{
	t_vec *result;

	if (!(result = malloc(sizeof(t_vec))))
		exit(EXIT_FAILURE);
	result->x = x;
	result->y = y;
	result->z = z;
	result->product_by_scalar = self_multiplication_by_scalar;
	result->magnitude = magnitude;
	result->destroy = vector_destructor;
	return (result);
}

double		magnitude(t_vec *self)
{
	return (sqrt(pow(self->x, 2.0) + pow(self->y, 2.0) + pow(self->z, 2.0)));
}

void		self_multiplication_by_scalar(t_vec *self, double scalar)
{
	self->x = (self->x) * scalar;
	self->y = (self->y) * scalar;
	self->z = (self->z) * scalar;
}

void		vector_destructor(t_vec *vector)
{
	free(vector);
}

double		sc_mult(t_vec *vec1, t_vec *vec2)
{
	return ((vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->z * vec2->z));
}
