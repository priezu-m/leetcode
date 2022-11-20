/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leetcode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anon <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:21:25 by anon              #+#    #+#             */
/*   Updated: 2022/11/20 14:41:43 by anon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC optimize("Ofast")
//#pragma GCC diagnostic warning "-Weverything"

#include <alloca.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <strings.h>

#define CAPACITY 1
#define POS 0

typedef struct s_robot_info
{
	int			robot_position;
	int			left_factory_index;
	int			left_factory_position;
	int			left_factory_capacity;
	int			rigth_factory_index;
	int			rigth_factory_position;
	int			rigth_factory_capacity;
	int_fast8_t	left_factory_acceptance;
	int_fast8_t	rigth_factory_acceptance;
	int_fast8_t	choosen_factory;
}t_robot_info;

typedef struct s_petition
{
	int	petitioner;
	int	priority;
}t_petition;

typedef struct s_factory_info
{
	t_petition	*petitions;
	int			petition_number;
	int			capacity;
}t_factory_info;

static inline void			set_robot_positon(t_robot_info *restrict robot_info,
								int *restrict robot, int robot_size);
static inline void			set_factory_capacity(
								t_factory_info *restrict factory_info,
								int *restrict *restrict factory,
								int factory_size);
static inline bool			is_to_the_right(int	*restrict *restrict factory,
								t_robot_info robot_info);
static inline void			find_right_factories(
								t_robot_info *restrict robot_info,
								int robot_size, int *restrict *restrict factory,
								int factory_size);
static inline bool			is_to_the_left(int	*restrict *restrict factory,
								t_robot_info robot_info);
static inline void			find_left_factories(
								t_robot_info *restrict robot_info,
								int robot_size, int *restrict *restrict factory,
								int factory_size);
static inline void			send_petitions(t_robot_info *restrict robot_info,
								int robot_size,
								t_factory_info *restrict factory_info,
								int factory_size);
static inline void			handle_petitions(t_robot_info *restrict robot_info,
								int robot_size,
								t_factory_info *restrict factory_info,
								int factory_size);
static inline long long int	sum_distances(t_robot_info *restrict robot_info,
								int robot_size);
static inline long long int	minimum_total_distance(int *restrict robot,
								int robot_size, int *restrict *restrict factory,
								int factory_size);

static inline void	set_robot_positon(t_robot_info *restrict robot_info,
								int *restrict robot, int robot_size)
{
	int	i;

	i = 0;
	while (i < robot_size)
	{
		robot_info[i].robot_position = robot[i];
		i++;
	}
}

static inline void	set_factory_capacity(
								t_factory_info *restrict factory_info,
								int *restrict *restrict factory,
								int factory_size)
{
	int	i;

	i = 0;
	while (i < factory_size)
	{
		factory_info[i].capacity = factory[i][CAPACITY];
		i++;
	}
}

static inline bool	is_to_the_right(int	*restrict *restrict factory,
						t_robot_info robot_info)
{
	if (factory[robot_info.rigth_factory_index][POS]
			>= robot_info.robot_position)
		return (true);
	return (false);
}

static inline bool	is_to_the_left(int	*restrict *restrict factory,
						t_robot_info robot_info)
{
	if (factory[robot_info.rigth_factory_index][POS]
			<= robot_info.robot_position)
		return (true);
	return (false);
}


static inline void			find_right_factories(
								t_robot_info *restrict robot_info,
								int robot_size, int *restrict *restrict factory,
								int factory_size)
{

	set_factory(&robot_info[0], factory, 0);

}

static inline long long int	minimum_total_distance(int *restrict robot,
		int robot_size, int *restrict *restrict factory, int factory_size)
{
	t_robot_info	*robot_info;
	t_factory_info	*factory_info;

	robot_info = alloca(robot_size * sizeof(t_robot_info));
	factory_info = alloca(factory_size * sizeof(t_factory_info));
	memset(robot_info, 0, robot_size * sizeof(t_robot_info));
	memset(factory_info, 0, factory_size * sizeof(t_factory_info));
	set_robot_positon(robot_info, robot, robot_size);
	set_factory_capacity(factory_info, factory, factory_size);
	find_right_factories(robot_info, robot_size, factory, factory_size);
	find_left_factories(robot_info, robot_size, factory, factory_size);
	send_petitions(robot_info, robot_size, factory_info, factory_size);
	handle_petitions(robot_info, robot_size, factory_info, factory_size);
	return (sum_distances(robot_info, robot_size));
}
