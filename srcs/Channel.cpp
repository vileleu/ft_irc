/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 03:06:08 by vico              #+#    #+#             */
/*   Updated: 2022/06/29 23:26:41 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(const std::string &name) : _name(""), _topic("")
{
	if (name[0] != '&' && name[0] != '#' && name[0] != '+' && name[0] != '!')
	{
		_name.push_back('#');
		_name.insert(1, name);
	}
	else
		_name = name;
	if (_name.size() >= 50)
	{
		std::string::iterator it(_name.begin());
		for (int i(0); i < 50; i++)
		{
			it++;
		}
		_name.erase(it, _name.end());
	}
}

Channel::~Channel()
{
}
