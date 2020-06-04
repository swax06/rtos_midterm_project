#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<signal.h> 
#include<stdbool.h>
#include<string.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include "server.h"
#include "server_ext.h"

int myRead(int sd, char *buff) {
	int i = 0;
	char c;
	while(i < 256){
		read(sd, &c, 1);
		buff[i] = c;
		i++;
		if(c == '\0'){	
			return 0;
		}
	}
	buff[255] = '\0';
	return 0;
}

int findInd(int sid) {
	int j = 0;
	while(1) {
		if(sid == clients[j] -> sid) {
			break;
		}
		j++;
	}
	return j;
}

void del_entry(int sid){
	int j = findInd(sid);
	while(j < cli) {
		clients[j] -> sid = clients[j + 1] -> sid;
		strcpy(clients[j] -> name,clients[j + 1] -> name);
		j++;
	}

	cli--;
}

void send_names(int sid){
	int j = 0;
	char buff[50],buff1[10];
	write(sid, "\nAll Users:\0",12);
	while(j < cli){
		if(clients[j] -> online){strcpy(buff1, "online");}
		else{strcpy(buff1, "offline");}
		sprintf(buff,"%d: %s (%s)%c", j + 1, clients[j] -> name, buff1, '\0');
		write(sid, buff, strlen(buff) + 1);
		j++;
	}

}
void send_groups(int sid){
	int j = 0, t, i;
	char buff[50];
	while(j < cli){
		if(clients[j] -> sid == sid){
			t = j;
		}
		j++;
	}
	write(sid, "\nyour groups:\0",14);
	j = 0;
	while(j < clients[t] -> g){
		sprintf(buff,"%d: %s%c", j + 1, groups[clients[t] -> gp[i]].name, '\0');
		write(sid,buff,strlen(buff) + 1);
		j++;
		i++;
	}
}
