/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pongCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 03:02:30 by vico              #+#    #+#             */
/*   Updated: 2022/07/08 12:43:19 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

int		Command::pongCommand(std::string cmd)
{
	std::vector<std::string>	arg(split(cmd, ' '));

	if (arg.size() < 2)
	{
		_to_send.insert(std::make_pair(_who->getSocket(), ERR_NOORIGIN(_who->getHost(), _who->getNickname())));
		return 0;
	}
	_to_send[_who->getSocket()] += ":" + _who->getHost() + " PONG " + arg[1] + "\n";
	return 0;
}
