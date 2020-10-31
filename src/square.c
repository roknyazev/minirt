/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:50:42 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/25 19:55:16 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/objects.h"

t_square		*new_square(
		t_vec *pos, t_vec *norm, t_color *color, double side_size)
{
	t_square *result;

	if (!(result = malloc(sizeof(t_square))))
		exit(EXIT_FAILURE);
	result->pos = pos;
	result->normal_vector = norm;
	result->side_size = side_size;
	result->color = color;
	result->intersection = square_intersection;
	result->get_normal = get_square_normal;
	result->destroy = square_destructor;
	return (result);
}

t_vec			*get_square_normal(t_square *self)
{
	t_vec *result;

	result = new_vector(
			self->normal_vector->x,
			self->normal_vector->y,
			self->normal_vector->z);
	return (result);
}

double			square_intersection(t_vec *o, t_vec *d, t_square *square)
{
	double	t;
	t_vec	*p;
	t_vec	*e1;
	t_vec	*e2;
	t_vec	*tmp;

	if ((t = plane_intersection(o, d, (t_plane *)square)) >= 1e100)
		return (t);
	p = new_vector(0, 0, 0);
	p = vec_sum(o, multiplication_by_scalar(d, t, p), p);
	vec_diff(p, square->pos, p);
	tmp = new_vector(1e-100, 1, 1e-100);
	e1 = cross_product(tmp, square->normal_vector);
	tmp->destroy(tmp);
	e1->product_by_scalar(e1, 1. / e1->magnitude(e1));
	if (fabs(sc_mult(e1, p)) >= square->side_size / 2.)
		t = 1e100;
	e2 = cross_product(square->normal_vector, e1);
	e2->product_by_scalar(e2, 1. / e2->magnitude(e2));
	if (fabs(sc_mult(e2, p)) >= square->side_size / 2.)
		t = 1e100;
	p->destroy(p);
	e1->destroy(e1);
	e2->destroy(e2);
	return (t);
}

void			square_destructor(t_square *self)
{
	self->normal_vector->destroy(self->normal_vector);
	self->color->destroy(self->color);
	self->pos->destroy(self->pos);
	free(self);
}
