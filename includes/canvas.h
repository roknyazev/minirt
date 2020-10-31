/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 00:52:00 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/25 18:29:37 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_CANVAS_H
# define MINIRT_CANVAS_H
# include "linalg.h"

/*
** class color
*/
typedef struct	s_color
{
	t_vec		*rgb_color;
	int			(* in_hex)(struct s_color *self);
	void		(* destroy)(struct s_color *self);
}				t_color;

t_color			*new_color(double r, double g, double b);
int				rgb_hex_transform(t_color *rgb_color);
void			color_destructor(t_color *color);

/*
** class canvas
*/
typedef struct	s_canvas
{
	int			width;
	int			height;
	t_color		**pixel_array;
	void		(* set_pixel)(struct s_canvas *self,
			int x, int y, t_color *color);
	t_color		*(* get_pixel)(struct s_canvas *self, int x, int y);
	void		(* destroy)(struct s_canvas *self);
}				t_canvas;

t_canvas		*new_canvas(int width, int height);
void			set_pixel(struct s_canvas *self, int x, int y, t_color *color);
t_color			*get_pixel(struct s_canvas *self, int x, int y);
void			canvas_destructor(struct s_canvas *self);

#endif
