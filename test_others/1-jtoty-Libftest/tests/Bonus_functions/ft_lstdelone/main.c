/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoty <jtoty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:15:51 by jtoty             #+#    #+#             */
/*   Updated: 2019/12/04 21:08:23 by jtoty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <unistd.h>
#include <string.h>

static void			ft_print_result(char *content)
{
	int		len;

	len = 0;
	while (content[len])
		len++;
	write(1, content, len);
}


static int	nb_free_done;

static void		ft_del(void *content)
{
	free(content);
	nb_free_done++;
}

static t_list		*get_lst_new_elem(void *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

static void			free_memory_and_return(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

static void			free_memory_lst_and_return(t_list *elem)
{
	t_list		*tmp;

	while (elem)
	{
		tmp = elem->next;
		free(elem);
		elem = tmp;
	}
}

static char			**get_content_lst(int size)
{
	char	**tab;
	int		i;
	char	str [] = "abcdef";

	if (!(tab = (char **)malloc(sizeof(*tab) * size + 1)))
		return (0);
	tab[size] = NULL;
	i = 0;
	while (i < size)
	{
		str[0] += i % 25;
		if (!(tab[i] = strdup(str)))
		{
			free_memory_and_return(tab, i - 1);
			return (NULL);
		}
		i++;
	}
	return (tab);
}

static t_list		*get_elem_lst(t_list *begin, char **tab, int i)
{
	t_list		*elem;

	if (!(elem = get_lst_new_elem(tab[i])))
	{
		free_memory_lst_and_return(begin);
		free_memory_and_return(tab, 4);
		return (NULL);
	}
	return (elem);
}

static void			check_lstdelone(t_list *elem)
{
	if (elem)
		ft_print_result(elem->content);
	else
		ft_print_result("NULL");
	write(1, "\n", 1);

}

int					 main(int argc, const char *argv[])
{
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;
	char		**tab;

	if (argc == 1 || (!(tab = get_content_lst(4))))
		return (0);
	elem = NULL;
	if (!(elem = get_elem_lst(elem, tab, 0)))
		return (0);
	if (!(elem2 = get_elem_lst(elem, tab, 1)))
		return (0);
	elem->next = elem2;
	if (!(elem3 = get_elem_lst(elem, tab, 2)))
		return (0);
	elem2->next = elem3;
	if (!(elem4 = get_elem_lst(elem, tab, 3)))
		return (0);
	elem3->next = elem4;
	nb_free_done = 0;
	alarm(5);
	if (atoi(argv[1]) == 1)
	{
		ft_lstdelone(elem3, &ft_del);
		elem3 = NULL;
		elem2->next = NULL;
		check_lstdelone(elem);
		check_lstdelone(elem2);
		check_lstdelone(elem3);
		check_lstdelone(elem4);
		nb_free_done += '0';
		write(1, "nb_free_done = ", 15);
		write(1, &nb_free_done, 1);
		free(tab[3]);
		free_memory_and_return(tab, 1);
		free(elem4);
	}
	else
		free_memory_and_return(tab, 4);
	free_memory_lst_and_return(elem);
	return (0);
}
