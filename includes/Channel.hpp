/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 03:06:20 by vico              #+#    #+#             */
/*   Updated: 2022/07/09 16:02:36 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "utils.hpp"
#include "Client.hpp"

class Channel
{
	private:

	std::string					_name;
	std::string					_topic;
	std::string					_mode;
	std::vector<std::string>	_modeparams;
	std::string					_key;
	bool						_moderated;
	bool						_invite;
	bool						_tops;
	unsigned int				_limit;

	public:

	std::vector<Client *>		_users;
	std::vector<Client *>		_ops;
	std::vector<std::string>	_banmask;

	Channel(const std::string &name, Client *creator);
	~Channel();

	std::string				pref(std::string name);

	std::string				getName() const;
	std::string				getKey() const;
	bool					getModerated() const;
	bool					getInvite() const;
	bool					getTops() const;
	unsigned int			getLimit() const;
	std::string				getTopic() const;
	std::string				getMode() const;
	std::string				getModeparams();

	void					setKey(const std::string &key);
	void					setModerated(const bool &mode);
	void					setInvite(const bool &mode);
	void					setTops(const bool &tops);
	void					setLimit(const unsigned int &limit);
	void					setTopic(const std::string &topic);

	void					addUser(Client *client, bool op);
	bool					removeUser(Client *client);
	bool					isOp(Client *client);
	void					removeOp(Client *client);

	void					addMode(char mode, std::string params);
	void					removeMode(char mode);
};

#endif
