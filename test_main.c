/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:13:27 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/16 14:27:45 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"

int	main(int argc, char **argv, char **env)
{
	char **arr;
	int i = 0;
		//printf("%s\n", argv[i]);
		arr = split_ignore_quotes(readline("prompt"), ' ');
		while (arr[i] != NULL)
		{
			printf("%s / ", arr[i]);
			i++;
		}
	return (0);
}