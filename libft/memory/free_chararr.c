/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_chararr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:46:10 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/28 19:46:44 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void free_chararr(char **arr)
{
    int i;

    if (!arr) return;
    i = 0;
    while (arr[i]) {
        free(arr[i]);
        i++;
    }
    free(arr);
}
