/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:10:21 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/20 12:13:24 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>

//ACTIONS MACROS
# define DEAD " died\n"
# define SLEEP " is sleeping\n"
# define EAT " is eating\n"
# define FORK " has taken a fork\n"
# define THINK " is thinking\n"

//COLORS MACROS
# define RED "\x1b[31m"
# define YELLOW "\x1b[33m"
# define GREEN "\x1b[32m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				eat_n;
	int				eat_stat;
	int				status;
	int				id;
	uint64_t		time_to_die;
	uint64_t		birth_time;
	pthread_t		t1;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				philo_n;
	int				meal_n;
	int				*arr;
	int				size;
	int				dead;
	int				finished;
	int				finished_philos;
	uint64_t		eating_time;
	uint64_t		death_time;
	uint64_t		sleep_time;
	uint64_t		start_time;
	pthread_t		*tid;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printmutex;
	pthread_mutex_t	monitor;
}	t_data;

// INITS
void		init_forks(t_data *data);
void		init_data(t_data *data);
void		init_threads(t_data *data);
void		init_philos(t_data *data);
size_t		substr_numb(char *temp, char c);

// UTILS
void		ft_usleep(uint64_t duration);
void		clean(t_data *data);
void		display_action(char *action, t_philo *p);
void		destroy_forks(t_data *data);
void		color(char *s);
char		**format_input_helper(t_data *data, char *str);
int			ft_atoi_philo(const char *str);
bool		format_input(char **argv, t_data *data);
bool		conversion(const char *str, int *result, int *sign);
bool		alloc_struct(t_data *data);
bool		check_digits(char *s);
bool		handle_input(char *argv[]);
uint64_t	get_time(void);

// LIBFT
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
void		ft_free_array(char **arr);
void		copy(const char *s, char *arr, size_t start, size_t count);
void		ft_putnbr(int n);
void		ft_putnbr_unsigned(unsigned int n);
void		ft_putchar(int c);
void		ft_putstr(char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
char		**word_len(char *temp, char c, char **arr);
char		**ft_split_without_delimiter(char *s);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);

// SIMULATION
void		philo(t_data *data);
void		*routine(void *philo);
void		actions(t_philo *p);
void		drop_forks(t_philo *p);
void		take_forks(t_philo *p);
void		*check_death(void *data);
void		end_sim(t_data *d);
void		*check_finished(void *data);
void		check_finished_helper(t_data *d, int i);
int			check_death_helper(t_data *d, int i);
#endif
