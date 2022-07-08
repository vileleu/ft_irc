/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noticeCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:55:25 by vico              #+#    #+#             */
/*   Updated: 2022/07/08 12:57:05 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

int		Command::noticeCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));

	if (arg.size() > 2)
	{
		for (std::vector<Client *>::iterator client(_clients->begin()); client != _clients->end(); client++)
		{
			if ((*client)->getNickname() == arg[1])
			{
				_to_send[(*client)->getSocket()] += ":" + _who->getHost() + " " + cmd + "\n";
				break ;
			}
		}
	}
	return 0;
}