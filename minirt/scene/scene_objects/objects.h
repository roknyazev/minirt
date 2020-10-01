/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 23:54:16 by wrudy             #+#    #+#             */
/*   Updated: 2020/09/29 23:05:52 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_OBJECTS_H
#define MINIRT_OBJECTS_H

#include "linalg/linalg.h"
#include "canvas/canvas.h"

/*
** class sphere
*/
typedef	struct	s_sphere
{
	t_vector	*pos;
	t_color		*color;
	double		diameter;
	double 		specular;
	double		reflective;
	t_vector	*(* get_normal)(struct s_sphere *self, t_vector *intersection_point);
	double 		(* intersection)(t_vector *o, t_vector *d, struct s_sphere *sphere);
	void 		(* destroy)(struct s_sphere *self);
}				t_sphere;

t_sphere		*new_sphere(t_vector *pos, t_color *color, double d, double s, double r);
t_vector		*get_normal_vector(struct s_sphere *self, t_vector *intersection_point);
double			sphere_intersection(t_vector *o, t_vector *d, t_sphere *sphere);
void 			sphere_destructor(t_sphere *self);

/*
** class plane
*/
typedef struct s_plane
{

}				t_plane;

/*
** square
*/
typedef struct s_square
{

}				t_square;

/*
** class cylinder
*/
typedef struct s_cylinder
{

}				t_cylinder;

/*
** class triangle
*/
typedef struct s_triangle
{

}				t_triangle;

/*
** class object
*/
typedef struct s_object
{
	int 		exist;
	double		t;
	t_color		*color;
	t_vector	*normal_vec;
	double 		specular;
	double 		reflect;
	void 		(* destroy)(struct s_object *self);
}				t_object;

t_object	*new_object();
void 		object_destructor(t_object *self);
#endif
