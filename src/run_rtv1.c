/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_rtv1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 18:00:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 17:58:59 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void		run_rtv1(t_scene_data *scene)
{
	SDL_Event	event;

	SDL_Init(SDL_INIT_EVERYTHING);
	scene->window = SDL_CreateWindow(W_TITLE, SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH,
								WIN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	scene->screen_surface = SDL_GetWindowSurface(scene->window);
	draw_all_scene(scene);
	SDL_UpdateWindowSurface(scene->window);
	event_management(scene, &event);
}

t_ray		compute_ray(t_cam camera, t_dot pixel)
{
	t_ray	r;
	float	vertical;
	float	horizontal;

	r.origin = camera.origin;
	vertical = (float)((TOP_BOUND + pixel.y) * STEP);
	horizontal = (float)((LEFT_BOUND + pixel.x) * STEP);
	r.direction = normalize_vector(matrice_mult_vect(camera.basis,
					(t_vector){horizontal, -vertical, -DISTANCE}));
	return (r);
}

t_intersect	find_closest_inter(t_scene_data *scene, t_ray primary_ray)
{
	t_list		*tmp_node;
	t_intersect	tmp_inter;
	t_intersect	closest_inter;

	closest_inter.distance = INFINITY;
	tmp_node = scene->figures;
	while (tmp_node != NULL)
	{
		tmp_inter.fig = tmp_node->content;
		tmp_inter.fig->find_intersection(primary_ray, &tmp_inter);
		if (tmp_inter.distance < closest_inter.distance)
			closest_inter = tmp_inter;
		tmp_node = tmp_node->next;
	}
	return (closest_inter);
}
