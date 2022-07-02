/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 03:06:20 by vico              #+#    #+#             */
/*   Updated: 2022/07/02 22:56:41 by vico             ###   ########.fr       */
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

	public:

	std::vector<Client *>	_users;
	std::vector<Client *>	_ops;

	Channel(const std::string &name, Client *creator);
	~Channel();

	std::string				pref(std::string name);

	std::string				getName() const;
	std::string				getTopic() const;
	void					setTopic(const std::string &topic);
	void					addUser(Client *client, bool op);
	bool					removeUser(Client *client);
};

#endif
