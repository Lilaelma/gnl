#include "get_next_line.h"

void	free_t_list(t_list *liste)
{
	t_list	*tmp;
	t_list	*next;

	tmp = liste;
	while (tmp)
	{
		free(tmp->content);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	create_line(t_list *liste, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (liste)
	{
		i = 0;
		while (liste->content[i])
		{
			if (liste->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		liste = liste->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

t_list	*get_last_element(t_list *liste)
{
	t_list	*tmp;

	tmp = liste;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	find_newline(t_list *liste)
{
	t_list	*tmp;
	int		i;

	if (!liste)
		return (0);
	tmp = get_last_element(liste);
	i = 0;
	while (tmp->content[i])
	{
		if (tmp->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}