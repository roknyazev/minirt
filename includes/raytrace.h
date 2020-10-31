/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 07:48:47 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/25 18:46:39 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_RAYTRACE_H
# define MINIRT_RAYTRACE_H
# include "canvas.h"
# include "linalg.h"
# include "scene.h"

typedef struct	s_flag
{
	char		type;
	double		t;
	int			index;
}				t_flag;

t_color			*raytrace(int cnv_x, int cnv_y, t_scene *scene, int cam_ind);
t_vec			*ray_cast(int cx, int cy, t_scene *scene, int camera_index);
t_vec			*intersect(t_scene *scn, t_object *obj, t_vec *o, t_vec *d);
void			int_with_sp(t_flag *flag, t_scene *scn, t_vec *o, t_vec *d);
void			int_with_pl(t_flag *flag, t_scene *scn, t_vec *o, t_vec *d);
void			int_with_cy(t_flag *flag, t_scene *scn, t_vec *o, t_vec *d);
void			int_with_sq(t_flag *flag, t_scene *scn, t_vec *o, t_vec *d);
void			int_with_tr(t_flag *flag, t_scene *scn, t_vec *o, t_vec *d);

#endif
