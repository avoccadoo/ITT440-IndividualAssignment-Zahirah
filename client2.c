#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int compare_strings(char x[], char y[])
{
	int a = 0;
	while (x[a] == y[a])
	{
		if (x[a] == '\0' || y[a] == '\0')
			break;
		a++;
	}
	if (x[a] == '\0' && y[a] == '\0')
		return 0;
	else 
		return -1;
}

int main()
{
	int clientSocket;
	char buffer [1024];
	struct sockaddr_in serverAdd;
	socklen_t addr_size;
	
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_port = htons(8888);
	serverAdd.sin_addr.s_addr = inet_addr("192.168.56.103");
	memset(serverAdd.sin_zero, '\0', sizeof serverAdd.sin_zero);
	addr_size = sizeof serverAdd;
	
	if (connect(clientSocket, (struct sockaddr *) &serverAdd, addr_size) < 0)
	{
		puts ("FRUITY FAILED TO CONNECT T_T");
	}
	else{
		puts("\nxxxxxxxxxxxxxxxxx HELLO FRUITY xxxxxxxxxxxxxxxxx");
	}
	
	
		
	int exit = 0; 
	while (exit == 0)
	{
		int received = recv(clientSocket, buffer, sizeof buffer -1, 0);
			
			if (received != 1)
			{
				if (compare_strings (buffer, "exit") == -1)
				{
					printf ("Fruity 1: ");
					printf ("%s\n", buffer);
					
					memset (&buffer[0], 0, sizeof(buffer));
				}
				
				else exit = 1;
			}
			else
			{
				printf("Fruity 2: ");
				scanf(" %[^\n]s", buffer);
				
			
				send (clientSocket, buffer, sizeof buffer -1, 0);
				
				if (compare_strings (buffer, "exit") == -1)
				{
					memset (&buffer[0], 0, sizeof (buffer));
				}
				
				else exit = 1;
			}
		
		
	}
	return 0;
}
