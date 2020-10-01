/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 19:38:45 by wrudy             #+#    #+#             */
/*   Updated: 2020/09/28 19:11:37 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object	*new_object()
{
	t_object *result;

	if (!(result = malloc(sizeof(t_object))))
		return (NULL);
	result->destroy = object_destructor;
	return (result);
}

void 		object_destructor(t_object *self)
{
	free(self);
}