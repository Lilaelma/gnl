#include "get_next_line.h"
#include <stdlib.h>

void	remove_line_in_list(t_list **liste)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;

	clean = (t_list *)malloc(sizeof(t_list));
	if (!liste || !clean)
		return ;
	clean->next = NULL;
	last = get_last_element(*liste);
	i = 0;
	while (last->content[i] != '\0' && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] != '\n')
		i++;
	clean->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (!clean->content)
		return ;
	j = 0;
	while (last->content[i])
		clean->content[j++] = last->content[i++];
	clean->content[j] = '\0';
	free_t_list(*liste);
	*liste = clean;
}

void	take_line(t_list *liste, char **line)
{
	int	i;
	int	j;

	if (!liste)
		return ;
	create_line(liste, line);
	if (!*line)
		return ;
	j = 0;
	while (liste)
	{
		i = 0;
		while (liste->content[i])
		{
			if (liste->content[i] == '\n')
			{
				(*line)[j++] = liste->content[i];
				break ;
			}
			(*line)[j++] = liste->content[i++];
		}
		liste = liste->next;
	}
	(*line)[j] = '\0';
}

void    push_in_list(t_list **liste, char *buffer, int already_read)
{
    t_list  *last;
    t_list  *new;
    int     i;

    new = (t_list *)malloc(sizeof(t_list));
    if (!new)
        return ;
    new->next = NULL;
    new->content = (char *)malloc(sizeof(char) * (already_read + 1));
    if (!new->content)
        return ;
    i = 0;
    while (buffer[i] && i < already_read)
    {
        new->content[i] = buffer[i];
        i++;
    }
    new->content[i] = '\0';
    if (!*liste)
    {
		*liste = new;
		return ;
	}
	last = get_last_element(*liste);
	last->next = new;
}

void    read_and_add_to_list(int fd, t_list **liste)
{
    char    *buffer;
    int     already_read;

    already_read = 1;
    while (find_newline(*liste) && already_read != 0)
    {
        buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if (!buffer)
            return ;
        already_read = (int)read(fd, buffer, BUFFER_SIZE);
        if ((*liste == NULL && already_read == 0) || already_read == -1)
        {
            free(buffer);
            return ;
        }
        buffer[already_read] = '\0';
        push_in_list(liste, buffer, already_read);
        free(buffer);
    }
}

char    *get_next_line(int fd)
{
    static t_list   *liste;
    char            *line;

	liste = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return (NULL);
    read_and_add_to_list(fd, &liste);
	if (!liste)
		return (NULL);
	line = NULL;
	take_line(liste, &line);
	remove_line_in_list(&liste);
	if (line[0] == '\0')
	{
		free_t_list(liste);
		liste = NULL;
		free(line);
		return (NULL);
	}
    return (line);
}