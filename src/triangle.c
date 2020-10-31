/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:50:10 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/25 20:02:38 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/objects.h"

t_triangle		*new_triangle(t_vec *p1, t_vec *p2, t_vec *p3, t_color *color)
{
	t_triangle	*result;
	t_vec		*e1;
	t_vec		*e2;

	if (!(result = malloc(sizeof(t_triangle))))
		exit(EXIT_FAILURE);
	result->pos = p1;
	result->color = color;
	e1 = new_vector(0, 0, 0);
	e2 = new_vector(0, 0, 0);
	vec_diff(p2, p1, e1);
	vec_diff(p3, p1, e2);
	result->e1 = e1;
	result->e2 = e2;
	p2->destroy(p2);
	p3->destroy(p3);
	result->normal_vector = NULL;
	result->normal_vector = get_triangle_normal(result);
	result->get_normal = get_triangle_normal;
	result->intersection = triangle_intersection;
	result->destroy = triangle_destructor;
	return (result);
}

t_vec			*get_triangle_normal(t_triangle *self)
{
	t_vec *result;

	if (self->normal_vector == NULL)
	{
		result = cross_product(self->e1, self->e2);
		result->product_by_scalar(result, 1. / result->magnitude(result));
	}
	else
		result = new_vector(
				self->normal_vector->x,
				self->normal_vector->y,
				self->normal_vector->z);
	return (result);
}

static void		u(t_triangle *triangle, int flag, t_vec *u)
{
	t_vec	*tmp1;
	t_vec	*tmp2;
	t_vec	abc;
	double	dd;

	abc.x = sc_mult(triangle->e1, triangle->e1);
	abc.y = sc_mult(triangle->e1, triangle->e2);
	abc.z = sc_mult(triangle->e2, triangle->e2);
	dd = abc.x * abc.z - abc.y * abc.y;
	tmp1 = new_vector(0, 0, 0);
	tmp2 = new_vector(0, 0, 0);
	if (flag == 0)
	{
		multiplication_by_scalar(triangle->e1, abc.z / dd, tmp1);
		multiplication_by_scalar(triangle->e2, abc.y / dd, tmp2);
	}
	else
	{
		multiplication_by_scalar(triangle->e2, abc.x / dd, tmp1);
		multiplication_by_scalar(triangle->e1, abc.y / dd, tmp2);
	}
	vec_diff(tmp1, tmp2, u);
	tmp1->destroy(tmp1);
	tmp2->destroy(tmp2);
}

double			triangle_intersection(t_vec *o, t_vec *d, t_triangle *tr)
{
	double	t;
	t_vec	*ub;
	t_vec	*ug;
	t_vec	*r;

	if ((t = plane_intersection(o, d, (t_plane *)tr)) >= 1e100)
		return (t);
	r = new_vector(0, 0, 0);
	r = multiplication_by_scalar(d, t, r);
	r = vec_sum(o, r, r);
	vec_diff(r, tr->pos, r);
	ub = new_vector(0, 0, 0);
	ug = new_vector(0, 0, 0);
	u(tr, 0, ub);
	u(tr, 1, ug);
	if (sc_mult(ub, r) < 0 || sc_mult(ug, r) < 0)
		t = 1e100;
	if ((1 - sc_mult(ub, r) - sc_mult(ug, r)) < 0)
		t = 1e100;
	ub->destroy(ub);
	ug->destroy(ug);
	r->destroy(r);
	return (t);
}

void			triangle_destructor(t_triangle *self)
{
	self->normal_vector->destroy(self->normal_vector);
	self->color->destroy(self->color);
	self->pos->destroy(self->pos);
	self->e1->destroy(self->e1);
	self->e2->destroy(self->e2);
	free(self);
}
