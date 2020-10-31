/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:44:06 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/25 18:27:49 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BMP_H
# define MINIRT_BMP_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

int						save_bmp(const unsigned char *img, int w, int h);

#endif
