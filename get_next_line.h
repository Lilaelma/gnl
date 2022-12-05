#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct  s_list
{
    char            *content;
    struct s_list   *next;
}               t_list;

char	*get_next_line(int fd);
void	read_and_add_to_list(int fd, t_list **liste);
int		find_newline(t_list *liste);
t_list	*get_last_element(t_list *liste);
void	create_line(t_list *liste, char **line);
int		ft_strlen(const char *str);
void	free_t_list(t_list *liste);

#endif