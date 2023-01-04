/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_boarder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:03:48 by nadesjar          #+#    #+#             */
/*   Updated: 2023/01/04 12:21:45 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/control.h"

void	check_board(t_game *game)
{
	game->ct.error = 1;
	ft_check_double(game);
	if (game->ct.error == -2)
	{
		// free(game->world_map);
		perror("Error, to much/less start spot <NSEW>\n");
		x_quit(game);
	}
	check_boarder_01(game);
	if (game->ct.error == 0)
	{
		// free(game->world_map);
		perror("Error, Boarder not ok\n");
		x_quit(game);
	}
}

void	ft_check_char(t_game *game)
{
	while (game->world_map[game->ct.i][game->ct.k])
	{
		if (game->world_map[game->ct.i][game->ct.k])
			check_direction(game);
		while (game->world_map[game->ct.i][game->ct.k] == ' ')
			game->ct.k++;
		if (game->world_map[game->ct.i][game->ct.k] != CASE_1)
			check_char(game);
		game->ct.k++;
	}
}

void	check_boarder_01(t_game *game)
{
	game->ct.i = -1;
	while (++game->ct.i < game->len.len_y)
	{
		game->ct.k = 0;
		ft_check_char(game);
	}
	ft_change_nsew(game);
}

void	check_char(t_game *game)
{
	if (!ft_check_set(game->world_map[game->ct.i][game->ct.k - 1], "NSEW10"))
		game->ct.error = 0;
	if (!ft_check_set(game->world_map[game->ct.i][game->ct.k + 1], "NSEW10"))
		game->ct.error = 0;
	if (!ft_check_set(game->world_map[game->ct.i - 1][game->ct.k], "NSEW10"))
		game->ct.error = 0;
	if (!ft_check_set(game->world_map[game->ct.i + 1][game->ct.k], "NSEW10"))
		game->ct.error = 0;
}

void	ft_load_texture(t_game *game, char *temp)
{
	if (ft_strncmp(temp, "NO", 2) == 0)
		game->imgs.texture_n.name = ft_strdup(ft_trim_token(temp + 2, ' '));
	else if (ft_strncmp(temp, "SO", 2) == 0)
		game->imgs.texture_s.name = ft_strdup(ft_trim_token(temp + 2, ' '));
	else if (ft_strncmp(temp, "WE", 2) == 0)
		game->imgs.texture_w.name = ft_strdup(ft_trim_token(temp + 2, ' '));
	else if (ft_strncmp(temp, "EA", 2) == 0)
		game->imgs.texture_e.name = ft_strdup(ft_trim_token(temp + 2, ' '));
	else if (ft_strncmp(temp, "F", 1) == 0)
		game->imgs.down.name = ft_strdup(ft_trim_token(temp + 1, ' '));
	else if (ft_strncmp(temp, "C", 1) == 0)
		game->imgs.top.name = ft_strdup(ft_trim_token(temp + 1, ' '));
}
