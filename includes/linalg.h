/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linalg.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 21:37:41 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/26 17:20:24 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_LINALG_H
# define MINIRT_LINALG_H

# include "stdlib.h"
# include "math.h"

/*
** class vector
*/
typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
	void		(* product_by_scalar)(struct s_vector *self, double scalar);
	double		(* magnitude)(struct s_vector *self);
	void		(* destroy)(struct s_vector *self);
}				t_vec;

t_vec			*new_vector(double x, double y, double z);
void			self_multiplication_by_scalar(t_vec *self, double scalar);
double			magnitude(t_vec *self);
void			vector_destructor(t_vec *vector);

double			sc_mult(t_vec *vec1, t_vec *vec2);
t_vec			*vec_sum(t_vec *vec1, t_vec *vec2, t_vec *buf);
t_vec			*vec_diff(t_vec *vec1, t_vec *vec2, t_vec *buf);
t_vec			*multiplication_by_scalar(
		t_vec *vec, double scalar, t_vec *buf);
t_vec			*cross_product(t_vec *u, t_vec *v);
#endif
