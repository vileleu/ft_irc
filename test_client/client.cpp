/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:38:13 by vico              #+#    #+#             */
/*   Updated: 2022/03/10 13:49:46 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h> // socket()
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_addr() htons()
#include <unistd.h> // close()

int		main(void)
{
	int	socketClient;

	socketClient = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in	addrClient;

	addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(15000);

	connect(socketClient, (const sockaddr *)&addrClient, sizeof(addrClient));
	std::cout << "client connecté au serveur" << std::endl;

	close(socketClient);
	return 0;
}