/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:35:52 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/22 16:24:15 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h> // if printf not used remove it
# include <dirent.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

int	main()
{
	DIR	*dir = opendir(".");
	if (!dir)
		return (printf("error\n"));
	struct dirent	*entity;
	entity = readdir(dir);
	while (entity)
	{
		printf("%d-->%s\n",entity->d_reclen, entity->d_name);
		entity = readdir(dir);
	}
	
	closedir(dir);
}
