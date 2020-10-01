/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 20:07:04 by wrudy             #+#    #+#             */
/*   Updated: 2020/09/22 20:19:49 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_light			*new_light(t_vector *pos, t_color *color, double brightness)
{
	t_light *result;

	if (!(result = malloc(sizeof(t_light))))
		return NULL;
	result->pos = pos;
	result->color = color;
	result->brightness = brightness;
	result->destroy = light_destructor;
	return (result);
}

void 			light_destructor(t_light *self)
{
	self->color->destroy(self->color);
	self->pos->destroy(self->pos);
	free(self);
}

t_amblight		*new_amblight(t_color *color, double ratio)
{
	t_amblight *result;

	if (!(result = malloc(sizeof(t_amblight))))
		return (NULL);
	result->color = color;
	result->ratio = ratio;
	result->destroy = amblight_destructor;
	return (result);
}

void 			amblight_destructor(t_amblight *self)
{
	self->color->destroy(self->color);
	free(self);
}
