/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:21:04 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/25 18:46:08 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	int_with_sp(t_flag *flag, t_scene *scn, t_vec *o, t_vec *d)
{
	int		i;
	double	solution;
	double	t;
	int		result_i;

	i = 0;
	t = flag->t;
	result_i = -1;
	while (i < scn->sp_count)
	{
		solution = scn->sphere[i]->intersection(o, d, scn->sphere[i]);
		if (solution < t)
		{
			t = solution;
			result_i = i;
		}
		i++;
	}
	if (result_i >= 0)
	{
		flag->type = 's';
		flag->t = t;
		flag->index = result_i;
	}
}

void	int_with_pl(t_flag *flag, t_scene *scn, t_vec *o, t_vec *d)
{
	int		i;
	double	solution;
	double	t;
	int		result_i;

	i = 0;
	t = flag->t;
	result_i = -1;
	while (i < scn->pl_count)
	{
		solution = scn->plane[i]->intersection(o, d, scn->plane[i]);
		if (solution < t)
		{
			t = solution;
			result_i = i;
		}
		i++;
	}
	if (result_i >= 0)
	{
		flag->type = 'p';
		flag->t = t;
		flag->index = result_i;
	}
}

void	int_with_cy(t_flag *flag, t_scene *scn, t_vec *o, t_vec *d)
{
	int		i;
	double	solution;
	double	t;
	int		result_i;

	i = 0;
	t = flag->t;
	result_i = -1;
	while (i < scn->cy_count)
	{
		solution = scn->cylinder[i]->intersection(o, d, scn->cylinder[i]);
		if (solution < t)
		{
			t = solution;
			result_i = i;
		}
		i++;
	}
	if (result_i >= 0)
	{
		flag->type = 'c';
		flag->t = t;
		flag->index = result_i;
	}
}

void	int_with_sq(t_flag *flag, t_scene *scn, t_vec *o, t_vec *d)
{
	int		i;
	double	solution;
	double	t;
	int		result_i;

	i = 0;
	t = flag->t;
	result_i = -1;
	while (i < scn->sq_count)
	{
		solution = scn->square[i]->intersection(o, d, scn->square[i]);
		if (solution < t)
		{
			t = solution;
			result_i = i;
		}
		i++;
	}
	if (result_i >= 0)
	{
		flag->type = 'q';
		flag->t = t;
		flag->index = result_i;
	}
}

void	int_with_tr(t_flag *flag, t_scene *scn, t_vec *o, t_vec *d)
{
	int		i;
	double	solution;
	double	t;
	int		result_i;

	i = 0;
	t = flag->t;
	result_i = -1;
	while (i < scn->tr_count)
	{
		solution = scn->triangle[i]->intersection(o, d, scn->triangle[i]);
		if (solution < t)
		{
			t = solution;
			result_i = i;
		}
		i++;
	}
	if (result_i >= 0)
	{
		flag->type = 't';
		flag->t = t;
		flag->index = result_i;
	}
}
