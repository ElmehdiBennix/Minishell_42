/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:27:01 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/22 06:46:29 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int    valid_key(int c)
{
    if ((c >= 65 && c <= 90)
        || (c >= 97 && c < 123)
        || (c >= '0' && c <= '9')
        || c == '_') //
        return (0);
    return (1);
}

char    *get_value(char *string , t_mini_data *var) // algor wroking fine need work need to be done to make it understandable
{
    int i = 0;
    int f = 0;
    int j = 0;
    t_expansions exp;
    char *buff;

    exp.new_arg = NULL;
    char *buffer = ft_strdup("");
    while (string[i])
    {
        while (string[i] == '$')
        {
            i++;
            f++;
            if (string[i] == '?')
            {
                i++;
                j++;
            }
            else
            {
                while (valid_key(string[i]) == 0)
                {
                    i++;
                    j++;
                }
            }
            if (j > 0)
            {
                if (f-1 > 0)
                {
                    exp.new_arg = ft_calloc(f,sizeof(char));
                    ft_memcpy(exp.new_arg,string+i-j-f,f-1);
                }
                buff = ft_calloc(j+1,sizeof(char));
                ft_memcpy(buff,string+i-j,j); // might sigf in some cases
                char *x = ft_strjoin(exp.new_arg,value_by_key(var->env_var,buff)); // can the value function
                buffer = ft_strjoin(buffer,x);
                f = 0;
                j = 0;
                exp.new_arg = NULL;
            }
        }
        f++; // need alot of protections but working now
        i++;
    }
    if (f > 0)
    {
        exp.new_arg = ft_calloc(f + 1,sizeof(char)); // not working with spaces
        ft_memcpy(exp.new_arg,string+i-j-f,f); // code managment
    }
    buffer = ft_strjoin(buffer,exp.new_arg);
    // printf("joined == %s§\n",buffer);
    return (buffer);
}

bool expander(t_mini_data *var)
{
    t_token *arrow = var->tokens;

    while (arrow)
    {
        // printf("tokken is  = %s => type \"%d\"\n",arrow->content,arrow->type);
        if (arrow->type == WORD || arrow->type == DOUBLE_QUOT)
        {
            if (arrow->type == DOUBLE_QUOT)
            {
                arrow->content = ft_strtrim(arrow->content,"\""); // freee
            }
            arrow->content = get_value(arrow->content,var);
        }
        else if (arrow->type == SINGLE_QUOT)
        {
            arrow->content = ft_strtrim(arrow->content,"'"); //free using tmp
        }
        // printf("tok after  = %s\n",arrow->content);
        arrow = arrow->forward;
    }
}