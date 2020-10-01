/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 07:48:47 by wrudy             #+#    #+#             */
/*   Updated: 2020/09/27 07:58:21 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINIRT_RAYTRACE_H
#define MINIRT_RAYTRACE_H
#include "../canvas/canvas.h"
#include "../linalg/linalg.h"
#include "../scene/scene.h"

t_color		*raytrace(int canvas_x, int canvas_y, t_scene *scene, int selected_camera);
t_vector	*ray_direction(int cx, int cy, t_scene *scene, int selected_camera);
t_vector	*intersection(t_scene *scene, t_object *object, t_vector *o, t_vector *d);

#endif
