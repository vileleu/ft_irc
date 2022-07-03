/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pongCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 03:02:30 by vico              #+#    #+#             */
/*   Updated: 2022/07/03 01:09:23 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::pongCommand()
{
	_to_send[_who->getSocket()] += ":" + _who->getHost() + " PONG " + _who->getNickname() + "\n";
}
