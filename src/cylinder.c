/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 20:43:36 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/25 19:30:35 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/objects.h"

t_cylinder		*new_cylinder(
		t_vec *pos, t_vec *norm, t_color *clr, double d)
{
	t_cylinder *result;

	if (!(result = malloc(sizeof(t_cylinder))))
		exit(EXIT_FAILURE);
	result->pos = pos;
	norm->product_by_scalar(norm, 1. / (norm->magnitude(norm)));
	result->norm = norm;
	result->diameter = d;
	result->color = clr;
	result->intersection = cylinder_intersection;
	result->get_normal = get_cylinder_normal;
	result->destroy = cylinder_destructor;
	return (result);
}

t_vec			*get_cylinder_normal(t_cylinder *self, t_vec *intersection_p)
{
	t_vec *tmp;
	t_vec *tmp2;
	t_vec *result;

	tmp = new_vector(0, 0, 0);
	tmp = vec_diff(intersection_p, self->pos, tmp);
	tmp2 = cross_product(tmp, self->norm);
	result = cross_product(tmp2, self->norm);
	tmp->destroy(tmp);
	tmp2->destroy(tmp2);
	return (result);
}

static t_vec	*get_abd(t_vec *vec1, t_vec *vec2, t_cylinder *cy)
{
	t_vec	*result;
	double	a;
	double	b;
	double	c;
	double	d;

	result = new_vector(0, 0, 0);
	a = sc_mult(vec1, vec1);
	b = 2 * sc_mult(vec1, vec2);
	c = sc_mult(vec2, vec2) - (cy->diameter / 2.) * (cy->diameter / 2.);
	d = b * b - 4 * a * c;
	result->x = a;
	result->y = b;
	result->z = d;
	return (result);
}

double			cylinder_intersection(t_vec *o, t_vec *d, t_cylinder *cy)
{
	t_vec	*vec1;
	t_vec	*vec2;
	t_vec	*dp;
	t_vec	*abd;
	double	result;

	vec1 = new_vector(0, 0, 0);
	vec2 = new_vector(0, 0, 0);
	vec1 = multiplication_by_scalar(cy->norm, sc_mult(d, cy->norm), vec1);
	vec1 = vec_diff(d, vec1, vec1);
	dp = new_vector(0, 0, 0);
	dp = vec_diff(o, cy->pos, dp);
	vec2 = multiplication_by_scalar(cy->norm, sc_mult(dp, cy->norm), vec2);
	vec2 = vec_diff(dp, vec2, vec2);
	abd = get_abd(vec1, vec2, cy);
	result = choice((-abd->y + sqrt(abd->z)) / (2. * abd->x),
					(-abd->y - sqrt(abd->z)) / (2. * abd->x), 1e-3, 1e100);
	if (abd->z < 0.)
		result = 1e100;
	vec1->destroy(vec1);
	vec2->destroy(vec2);
	dp->destroy(dp);
	abd->destroy(abd);
	return (result);
}

void			cylinder_destructor(t_cylinder *self)
{
	self->norm->destroy(self->norm);
	self->color->destroy(self->color);
	self->pos->destroy(self->pos);
	free(self);
}
