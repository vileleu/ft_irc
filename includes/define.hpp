/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:39:18 by vico              #+#    #+#             */
/*   Updated: 2022/07/09 18:58:19 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_HPP
#define DEFINE_HPP

/*
**  ↓ COMMANDS REPLIES ↓
*/

#define RPL_WELCOME(host, nick) ":" + host + " 001 " + nick + " :Bienvenue chakal " + host + "\n"

#define RPL_AWAY(host, nick, n, msg) ":" + host + " 301 " + nick + " " + n + " :" + msg + "\n"

#define RPL_CHANNELMODEIS(host, nick, channel, mode, modeparams) ":" + host + " 324 " + nick + " " + channel + " " + mode + " " + modeparams + "\n"

#define RPL_NOTOPIC(host, nick, channel) ":" + host + " 331 " + nick + " " + channel + " :No topic is set\n"

#define RPL_TOPIC(host, nick, channel, topic) ":" + host + " 332 " + nick + " " + channel + " :" + topic + "\n"

#define RPL_INVITING(host, nick, channel, n) ":" + host + " 341 " + nick + " " + channel + " " + n + "\n"

#define RPL_NAMREPLY(host, nick, channel) ":" + host + " 353 " + nick + " = " + channel + " :"

#define RPL_ENDOFNAMES(host, nick, channel) ":" + host + " 366 " + nick + " " + channel + " :End of NAMES list\n"

#define RPL_BANLIST(host, nick, channel, mask) ":" + host + " 367 " + nick + " " + channel + " " + mask + "\n"

#define RPL_ENDOFBANLIST(host, nick, channel) ":" + host + " 368 " + nick + " " + channel + " :End of channel ban list\n"

/*
**  ↓ ERRORS REPLIES ↓
*/

#define ERR_NOSUCHNICK(host, nick, n) ":" + host + " 401 " + nick + " " + n + " :No such nick/channel\n"

#define ERR_NOSUCHCHANNEL(host, nick, channel) ":" + host + " 403 " + nick + " " + channel + " :No such channel\n"

#define ERR_CANNOTSENDTOCHAN(host, nick, channel) ":" + host + " 404 " + nick + " " + channel + " :Cannot send to channel\n"

#define ERR_NOORIGIN(host, nick) ":" + host + " 409 " + nick + " :No origin specified\n"

#define ERR_NOTEXTTOSEND(host, nick) ":" + host + " 412 " + nick + " :No text to send\n"

#define ERR_ERRONEUSNICKNAME(host, nick, n) ":" + host + " 432 " + nick + " " + n + " :Erroneous nickname\n"

#define ERR_NICKNAMEINUSE(host, nick, n) ":" + host + " 433 " + nick + " " + n + " :Nickname is already in use\n"

#define ERR_USERNOTINCHANNEL(host, nick, n, channel) ":" + host + " 441 " + nick + " :" + n + " " + channel + " :They aren't on that channel\n"

#define ERR_NOTONCHANNEL(host, nick, channel) ":" + host + " 442 " + nick + " " + channel + " :You're not on that channel\n"

#define ERR_USERONCHANNEL(host, nick, user, channel) ":" + host + " 443 " + nick + " " + user + " " + channel + " :is already on channel\n"

#define ERR_NOTREGISTERED(host, nick) ":" + host + " 451 " + nick + " :You have not registered\n"

#define ERR_NEEDMOREPARAMS(host, nick, command) ":" + host + " 461 " + nick + " " + command + " :Not enough parameters\n"

#define ERR_PASSWDMISMATCH(host, nick) ":" + host + " 464 " + nick + " :Password incorrect\n"

#define ERR_CHANNELISFULL(host, nick, channel) ":" + host + " 471 " + nick + " " + channel + " :Cannot join channel (+l)\n"

#define ERR_UNKNOWNMODE(host, nick, channel, char) ":" + host + " 472 " + nick + " " + char + " :is unknown mode char to me for " + channel + "\n"

#define ERR_INVITEONLYCHAN(host, nick, channel) ":" + host + " 473 " + nick + " " + channel + " :Cannot join channel (+i)\n"

#define ERR_BANNEDFROMCHAN(host, nick, channel) ":" + host + " 474 " + nick + " " + channel + " :Cannot join channel (+b)\n"

#define ERR_BADCHANNELKEY(host, nick, channel) ":" + host + " 475 " + nick + " " + channel + " :Cannot join channel (+k)\n"

#define ERR_CHANOPRIVSNEEDED(host, nick, channel) ":" + host + " 482 " + nick + " " + channel + " :You're not channel operator\n"

#endif
