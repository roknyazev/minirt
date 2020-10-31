/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:31:01 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/26 19:48:40 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_lenght + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_pixels_into_image(t_scene *scene, t_canvas *canvas, t_data img)
{
	int	i;
	int	j;
	int c;

	i = 0;
	while (i < scene->res_x)
	{
		j = 0;
		while (j < scene->res_y)
		{
			c = canvas->get_pixel(canvas, i, j)->in_hex
					(canvas->get_pixel(canvas, i, j));
			my_mlx_pixel_put(&img, i, j, c);
			j++;
		}
		i++;
	}
}

int		keypress(int key, t_rt *rt)
{
	t_canvas *canvas;

	if (key == KEY_TAB)
	{
		if (rt->scene->cam_count > 1)
		{
			rt->scene->selected_camera_index++;
			if (rt->scene->selected_camera_index >= rt->scene->cam_count)
				rt->scene->selected_camera_index = 0;
			canvas = render(rt->scene, rt->scene->selected_camera_index);
			put_pixels_into_image(rt->scene, canvas, rt->img);
			mlx_put_image_to_window(
					rt->mlx.mlx, rt->mlx.win, rt->img.img, 0, 0);
			canvas->destroy(canvas);
		}
		else
			write(1, "There is only one camera", 25);
	}
	if (key == KEY_ESC)
		exit(0);
	return (1);
}

int		red_cross_click(int check)
{
	if (check)
		exit(0);
	return (1);
}
