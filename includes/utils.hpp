/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:58:56 by vico              #+#    #+#             */
/*   Updated: 2022/06/30 02:09:55 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <sys/socket.h> // socket()
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_addr() htons()
#include <unistd.h> // close()
#include <netdb.h> // gethostbyname()
#include <string>
#include <stdlib.h> // exit()
#include <sys/select.h> // select()
#include <cstdlib> // atoi()
#include <vector>
#include <sys/types.h>
#include <string.h> // memset
#include <sstream>
#include <map>
#include "define.hpp"

std::string		deleteChar(std::string modif, char c);
std::string		replaceChar(std::string modif, char origin, char replace);

#endif