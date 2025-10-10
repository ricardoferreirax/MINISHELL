/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 21:27:57 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/10 21:24:53 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/envyan.h"

static void add_value_to_entry(char *export_entry, t_envyan *var, int key_len)
{
    int value_len;
    int i;

    value_len = ft_strlen(var->value);
    i = key_len;
    export_entry[i++] = '=';
    export_entry[i++] = '"';
    ft_strlcpy(export_entry + i, var->value, value_len + 1);
    i += value_len;
    export_entry[i++] = '"';
    export_entry[i] = '\0';
}

static char *create_export_entry(t_envyan *var)
{
    char *export_entry;
    int key_len;
    int value_len;
    int total_len;

    if (!var || !var->key)
        return (NULL);
    key_len = ft_strlen(var->key);
    value_len = 0;
    if (var->value)
        value_len = ft_strlen(var->value);
    total_len = key_len;
    if (var->value)
        total_len += value_len + 3;
    export_entry = malloc(total_len + 1);
    if (!export_entry)
        return (NULL);
    ft_strlcpy(export_entry, var->key, key_len + 1);
    if (var->value)
        add_value_to_entry(export_entry, var, key_len);
    return (export_entry);
}

static int count_export_vars(t_envyan *envyan)
{
    t_envyan *current_var;
    int num_vars;
    int should_skip;

    num_vars = 0;
    current_var = envyan;
    while (current_var)
    {
        should_skip = 0;
        if (current_var->key && ft_strcmp(current_var->key, "_") == 0 && current_var->value != NULL)
            should_skip = 1;
        if (!should_skip)
            num_vars++;
        current_var = current_var->next;
    }
    return (num_vars);
}

int process_export_entry(t_envyan *current, char **export_array, int index)
{
    if (!current || !export_array)
        return (-1);
    if (current->key && ft_strcmp(current->key, "_") == 0 && current->value != NULL)
        return index;
    export_array[index] = create_export_entry(current);
    if (!export_array[index])
        return (-1);
    return (index + 1);
}

void free_export_array(char **array, int filled)
{
    int j;

    j = 0;
    while (j < filled)
    {
        free(array[j]);
        j++;
    }
    free(array);
}

char **create_export_array(t_envyan *head)
{
    int count;
    char **envyan_array;
    int i; 
    int next_i; 
    t_envyan *current; 

    count = count_export_vars(head); 
    envyan_array = malloc(sizeof(char *) * (count + 1));
    if (!envyan_array) 
        return (NULL); 
    current = head; 
    i = 0; 
    while (current) 
    { 
        next_i = process_export_entry(current, envyan_array, i); 
        if (next_i == -1) 
        { 
            free_export_array(envyan_array, i);
            return (NULL); 
        } 
        i = next_i; 
        current = current->next; 
    } 
    envyan_array[i] = NULL; 
    return envyan_array; 
}
