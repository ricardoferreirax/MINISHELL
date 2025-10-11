/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:37:36 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/11 12:38:00 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/envyan.h"

static int has_numeric_chars(char *s)
{
    int i;

    if (!s || s[0] == '\0')
        return (0);
    i = 0;
    while (s[i])
    {
        if (ft_isdigit((unsigned char)s[i]))
            return (1);
        i++;
    }
    return (0);
}

static int has_only_numbers_with_sign(char *s)
{
    int i;

    if (!s || s[0] == '\0')
        return (0);
    i = 0;
    while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
        i++;
    if (s[i] == '-' || s[i] == '+')
        i++;
    if (!ft_isdigit((unsigned char)s[i]))
        return (0);
    while (s[i])
    {
        if (!ft_isdigit((unsigned char)s[i]))
            return (0);
        i++;
    }
    return (1);
}

int get_shlvl_from_envp(char **envp)
{
    int   i;
    char *val;

    if (!envp)
        return (0);
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
        {
            val = envp[i] + 6;
            if (val[0] == '\0')
                return (1);
            if (!has_numeric_chars(val))
                return (1);
            if (!has_only_numbers_with_sign(val))
                return (1);
            return (ft_atoi(val));
        }
        i++;
    }
    return (0);
}

static int update_shlvl_if_exists(t_envyan **env_list, char *tmp)
{
    t_envyan *current;

    if (!env_list || !tmp)
        return (0);
    current = *env_list;
    while (current)
    {
        if (current->key && ft_strcmp(current->key, "SHLVL") == 0)
        {
            if (current->value)
                free(current->value);
            current->value = ft_strdup(tmp);
            free(tmp);
            return (1);
        }
        current = current->next;
    }
    return (0);
}

t_envyan *process_shlvl(t_envyan **env_list, t_envyan **last, int shlvl)
{
    t_envyan *new_node;
    char     *tmp;

    if (!env_list)
        return (NULL);
    shlvl = shlvl + 1;
    if (shlvl < 0)
        shlvl = 0;
    if (shlvl > 999)
    {
        ft_putendl_fd("Minyanshell: shell level (1000) too high, resetting to 1", 2);
        shlvl = 1;
    }
    tmp = ft_itoa(shlvl);
    if (!tmp)
        return (*env_list);
    if (update_shlvl_if_exists(env_list, tmp))
        return (*env_list);
    new_node = create_envyan_node("SHLVL", tmp);
    free(tmp);
    if (!new_node)
        return (*env_list);
    add_envyan_node(env_list, last, new_node);
    return (*env_list);
}
