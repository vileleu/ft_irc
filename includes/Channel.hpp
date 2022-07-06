/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 03:06:20 by vico              #+#    #+#             */
/*   Updated: 2022/07/06 03:42:07 by vico             ###   ########.fr       */
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
	std::string				_mode;
	std::string				_modeparams;

	public:

	std::vector<Client *>	_users;
	std::vector<Client *>	_ops;

	Channel(const std::string &name, Client *creator);
	~Channel();

	std::string				pref(std::string name);

	std::string				getName() const;
	std::string				getTopic() const;
	std::string				getMode() const;
	std::string				getModeparams() const;
	void					setTopic(const std::string &topic);
	void					addUser(Client *client, bool op);
	bool					removeUser(Client *client);
	bool					isOp(Client *client);
	void					removeOp(Client *client);
	void					addMode(char mode, std::string params);
};

#endif
