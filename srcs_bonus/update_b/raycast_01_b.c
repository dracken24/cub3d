/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:43:17 by nadesjar          #+#    #+#             */
/*   Updated: 2022/11/01 20:15:41 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cube3d_bonus.h"

void	ft_check_side_hit(t_game *game, t_ray *ray)
{
	if (ray->side_d.x < ray->side_d.y)
	{
		ray->side_d.x += ray->delta_d.x;
		ray->map.x += ray->step.x;
		ray->side = 0;
		if (game->world_map[ray->map.x][ray->map.y] == '2')
			game->see_door = 1;
		if (game->world_map[ray->map.x][ray->map.y] == 'Z')
			game->see_enemy = 1;
		if (ray->step.x >= 0)
			ray->side = 2;
	}
	else
	{
		ray->side_d.y += ray->delta_d.y;
		ray->map.y += ray->step.y;
		ray->side = 1;
		if (game->world_map[ray->map.x][ray->map.y] == '2')
			game->see_door = 1;
		if (game->world_map[ray->map.x][ray->map.y] == 'Z')
			game->see_enemy = 1;
		if (ray->step.y >= 0)
			ray->side = 3;
	}
}

static void	ft_raycast_hit(t_game *game, t_ray *ray, t_enemy *enemy)
{
	bool	hit;

	(void)enemy;
	hit = false;
	while (!hit)
	{
		ft_check_side_hit(game, ray);
		if (game->world_map[ray->map.x][ray->map.y] == '2')
		{
			game->door_mapx = ray->map.x;
			game->door_mapy = ray->map.y;
		}
		if (game->world_map[ray->map.x][ray->map.y] == 'Z')
		{
			// printf("BB\n");
			game->enemy_mapx = ray->map.x;
			game->enemy_mapy = ray->map.y;
		}
		if (game->world_map[ray->map.x][ray->map.y] == '1'
				|| game->world_map[ray->map.x][ray->map.y] == '7')
			hit = true;
	}
}

void	ft_ray_init(t_game *game, t_ray *ray, t_ply *player)
{
	(void)game;
	ray->camerax = 2 * ray->pos.x / ray->pos.y - 1;
	ray->raydir.x = player->dir.x + player->plane.x * ray->camerax;
	ray->raydir.y = player->dir.y + player->plane.y * ray->camerax;
	ray->map.x = (int)(player->pos.x);
	ray->map.y = (int)(player->pos.y);
	ray->delta_d.x = 1e30;
	if (ray->raydir.x)
		ray->delta_d.x = fabs(1 / ray->raydir.x);
	ray->delta_d.y = 1e30;
	if (ray->raydir.y)
		ray->delta_d.y = fabs(1 / ray->raydir.y);
	if (ray->raydir.x < 0)
	{
		ray->step.x = -1;
		ray->side_d.x = (player->pos.x - ray->map.x) * ray->delta_d.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_d.x = (ray->map.x + 1.0 - player->pos.x) * ray->delta_d.x;
	}
}

void	ft_raycast_loop(t_game *game, t_ray *ray, t_ply *player)
{
	game->save_ply = player;
	game->save_ray = ray;
	ft_ray_init(game, ray, player);
	if (ray->raydir.y < 0)
	{
		ray->step.y = -1;
		ray->side_d.y = (player->pos.y - ray->map.y) * ray->delta_d.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_d.y = (ray->map.y + 1.0 - player->pos.y) * ray->delta_d.y;
	}
}

void	ft_raycast(t_game *game)
{
	t_ray	*ray;
	t_ply	*player;
	t_enemy	*enemy;

	ray = game->ray;
	ray->pos.x = 0;
	ray->mouse_y = game->ct.last_y;
	ray->pos.y = SCREENW;
	player = game->player;
	enemy = &game->enemy0;
	game->ct.face = rand();
	game->ct.face %= 1000;
	if (ft_wait3(12) == true)
		game->ct.light00 = game->ct.face;
	game->scale_floorx = -1;
	while (ray->pos.x <= ray->pos.y + 1)
	{
		game->scale_floorx++;
		// printf("%d\n", ++i);
		ft_raycast_loop(game, ray, player);
		ft_raycast_hit(game, ray, enemy);
		ft_raycast_suite(game, ray);
		ray->pos.x += PRECISION;
	}
}
