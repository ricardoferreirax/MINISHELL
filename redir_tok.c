/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:33:43 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/16 14:33:47 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_redir_type
{
    REDIR_INVALID = -1,  // not a redirection token
    REDIR_IN = 0,
    REDIR_OUT,
    REDIR_APPEND,
    REDIR_HEREDOC,
}   t_redir_type;

t_redir_type token_to_redir_type(char *tok)
{
    if (!tok)
        return (REDIR_INVALID);
    if (tok[0] == '<' && tok[1] == '<' && tok[2] == '\0') // [n] << word
        return (REDIR_HEREDOC);
    if (tok[0] == '>' && tok[1] == '>' && tok[2] == '\0')  // [n] >> word
        return (REDIR_APPEND);
    if (tok[0] == '<' && tok[1] == '\0')  // [n] < word
        return (REDIR_IN);
    if (tok[0] == '>' && tok[1] == '\0')  // [n] > word
        return (REDIR_OUT); 
    return (REDIR_INVALID);
}
