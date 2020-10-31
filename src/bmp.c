/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:43:50 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/24 18:20:15 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bmp.h"

static void				ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

static unsigned char	*file_header(int filesize)
{
	unsigned char	*bmpfileheader;

	if (!(bmpfileheader = (unsigned char*)malloc(14 * sizeof(unsigned char))))
		return (0);
	ft_bzero(bmpfileheader, 14);
	bmpfileheader[0] = 'B';
	bmpfileheader[1] = 'M';
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)((unsigned)filesize >> 8u);
	bmpfileheader[4] = (unsigned char)((unsigned)filesize >> 16u);
	bmpfileheader[5] = (unsigned char)((unsigned)filesize >> 24u);
	bmpfileheader[10] = 54;
	return (bmpfileheader);
}

static unsigned char	*info_header(int width, int height)
{
	unsigned char	*bmpinfoheader;

	if (!(bmpinfoheader = (unsigned char*)malloc(40 * sizeof(unsigned char))))
		return (0);
	ft_bzero(bmpinfoheader, 40);
	bmpinfoheader[0] = 40;
	bmpinfoheader[4] = (unsigned char)(width);
	bmpinfoheader[5] = (unsigned char)((unsigned)width >> 8u);
	bmpinfoheader[6] = (unsigned char)((unsigned)width >> 16u);
	bmpinfoheader[7] = (unsigned char)((unsigned)width >> 24u);
	bmpinfoheader[8] = (unsigned char)(height);
	bmpinfoheader[9] = (unsigned char)((unsigned)height >> 8u);
	bmpinfoheader[10] = (unsigned char)((unsigned)height >> 16u);
	bmpinfoheader[11] = (unsigned char)((unsigned)height >> 24u);
	bmpinfoheader[12] = 1;
	bmpinfoheader[14] = 32;
	return (bmpinfoheader);
}

static int				wt_img(int fd, const unsigned char *img, int w, int h)
{
	int line;

	line = h - 1;
	while (line >= 0)
	{
		if (!write(fd, img + w * line * 4, w * 4))
			return (0);
		line--;
	}
	return (1);
}

int						save_bmp(const unsigned char *img, int w, int h)
{
	int				fd;
	unsigned char	*fileheader;
	unsigned char	*infoheader;

	fd = open("rt.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0755);
	fileheader = file_header(14 + 40 + 3 * w * h);
	write(fd, fileheader, 14);
	free(fileheader);
	infoheader = info_header(w, h);
	write(fd, infoheader, 40);
	free(infoheader);
	if (!wt_img(fd, img, w, h))
		exit(1);
	close(fd);
	exit(0);
}
