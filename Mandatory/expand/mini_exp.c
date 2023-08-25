/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:27:01 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/25 04:28:40 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int    valid_key(int c)
{
    if ((c >= 65 && c <= 90)
        || (c >= 97 && c < 123)
        || (c >= '0' && c <= '9')
        || c == '_')
        return (0);
    return (1);
}

char    *get_value(char *string)
{
    int i = 0;
    int j = 0;
    char *str;
    int flag;
    char* value ="vrai frerro";

    while (string[i])
    {
        if (string[i] == '$')
        {
            while (valid_key(string[++i]) == 0)
                j++;
            if (j != 0)
            {
                //get value and join it using memory functions carefull need to terminate them or use calloc better overall
                // str = ft_calloc(i-j,1);
                // ft_memcpy(str,string,i-j-1);
                // ft_strjoin(str,value);
                // ft_strdup(string); //befor $ and join with value of $key then 
                // j = 0;
            }
        }
        i++;
    }
    printf(" i == %d and j == %d \n",i,j);
}

int expand(t_token *tokens)
{
    t_token *arrow = tokens;

    while (arrow)
    {
        printf("tokken is  = %s => type \"%d\"\n",arrow->content,arrow->type);
        if (arrow->type == WORD || arrow->type == DOUBLE_QUOT)
        {
            if (arrow->type == DOUBLE_QUOT)
            {
                arrow->content = ft_strtrim(arrow->content,"\""); // freee
                get_value(arrow->content);
            }
        }
        else if (arrow->type == SINGLE_QUOT)
        {
            arrow->content = ft_strtrim(arrow->content,"'"); //free using tmp
        }
        printf("tok after  = %s\n",arrow->content);
        arrow = arrow->forward;
    }
}