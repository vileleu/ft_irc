/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 03:06:20 by vico              #+#    #+#             */
/*   Updated: 2022/06/29 23:19:54 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "utils.hpp"
#include "Client.hpp"

class Channel
{
	private:

	std::string				_name;
	std::string				_topic;
	std::vector<Client *>	_users;

	public:

	Channel(const std::string &name);
	~Channel();
};

#endif
