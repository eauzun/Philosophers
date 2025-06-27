/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:48:53 by emuzun            #+#    #+#             */
/*   Updated: 2025/06/26 19:48:54 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

exit_app(const char *msg, int error_flag, t_sim sim)
{
	if(error_flag == 1)
	{
		printf(RED "%s", msg);
		exit(EXIT_FAIURE)
	}
}