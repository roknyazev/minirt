/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 22:09:27 by wrudy             #+#    #+#             */
/*   Updated: 2020/09/25 20:16:59 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_SCENE_H
#define MINIRT_SCENE_H

#include "scene_objects/objects.h"
#include "linalg/linalg.h"
#include "canvas/canvas.h"

/*
** class light
*/
typedef struct s_light
{
	t_vector	*pos;
	t_color		*color;
	double		brightness;
	void 		(* destroy)(struct s_light *self);
}				t_light;

t_light			*new_light(t_vector *pos, t_color *color, double brightness);
void 			light_destructor(t_light *self);

/*
** class ambient light
*/
typedef struct	s_amblight
{
	double		ratio;
	t_color		*color;
	void 		(* destroy)(struct s_amblight *self);
}				t_amblight;

t_amblight		*new_amblight(t_color *color, double ratio);
void 			amblight_destructor(t_amblight *self);

/*
** class camera
*/
typedef struct	s_camera
{
	t_vector	*pos;
	t_vector	*orient;
	double 		fov;
	double		distance_to_viewport;
	void 		(* destroy)(struct s_camera *self);
}				t_camera;

t_camera		*new_camera(t_vector *pos, t_vector *orient, double fov, int width);
void 			camera_destructor(t_camera *self);

/*
** class scene
*/
typedef struct	s_scene
{
	int 		resolution_x;
	int 		resolution_y;

	t_light		**light;
	int 		lights_count;

	t_amblight	*ambient_light;

	t_camera	**camera;
	int 		camera_count;

	/* objects */
	t_sphere	**sphere;
	int 		sphere_count;
	void 		(* destroy)(struct s_scene *self);
}				t_scene;

t_scene			*new_scene(char *path);
void 			scene_destructor(t_scene *self);
#endif
