#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"
#include <time.h>
#include <sstream>
#include "Utils.h"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#include <termios.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

string mon(unsigned int i)
{
	while(i > 12)
	{
		i -= 12;
	}
	switch(i)
	{
		case 1:
			return "Jan";
			break;
		case 2:
			return "Feb";
			break;
		case 3:
			return "Mar";
			break;
		case 4:
			return "Apr";
			break;
		case 5:
			return "May";
			break;
		case 6:
			return "Jun";
			break;
		case 7:
			return "Jul";
			break;
		case 8:
			return "Aug";
			break;
		case 9:
			return "Sep";
			break;
		case 10:
			return "Oct";
			break;
		case 11:
			return "Nov";
			break;
		case 12:
			return "Dec";
			break;
		default:
			return Utils::to_string(i);
	}
}

void check(string &s)
{
	while(s.length() < 2)
	{
		s = "0" + s;
	}
}

string dateTime()
{
	time_t c;
	time(&c);
	struct tm *theTime = localtime(&c);
	string day = Utils::to_string(theTime->tm_mday);
	int month = theTime->tm_mon + 1;

	string hr = Utils::to_string(theTime->tm_hour);
	string min = Utils::to_string(theTime->tm_min);
	string second = Utils::to_string(theTime->tm_sec);
	check(day);
	check(hr);
	check(min);
	check(second);
	string stt;
	stt.append(mon(month)).append(" ").append(day).append("  ").append(hr).append(":").append(min).append(":").append(second);
	return stt;
}

string ipAddr()
{
	int fd;
	struct ifreq ifr;

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	/* I want to get an IPv4 IP address */
	ifr.ifr_addr.sa_family = AF_INET;

	/* I want IP address attached to "eth0" */
	strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

	ioctl(fd, SIOCGIFADDR, &ifr);

	close(fd);

	return inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
}
 
int main(void)
{
    struct termios oldSettings, newSettings;

    tcgetattr(fileno(stdin), &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &newSettings);
	
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 50;

	LCD lcd(7, 8, 25, 24, 23, 18, 2, 16);
	lcd.init();
	long double t = time(0);
	long double pt = t;
	long double tt = t;
	lcd.message(dateTime(), 0);
	lcd.message("IP: " + ipAddr(), 1);
	char c = ' ';
	do
	{
		t = time(0);
		if(t - pt >= 1)
		{
			lcd.message(dateTime(), 0);
			pt = t;
		}
		if(t - tt > 60)
		{
			lcd.message("IP: " + ipAddr(), 1);
			tt = t;
		}

		fd_set set;

        FD_ZERO(&set);
        FD_SET(fileno(stdin), &set);

		int res = select(fileno(stdin) + 1, &set, NULL, NULL, &tv);
		if(res > 0)
		{
			read(fileno(stdin), &c, 1);
		}
	}
	while(c != 'q');

	lcd.~LCD();

	tcsetattr(fileno(stdin), TCSANOW, &oldSettings);

    return 0;
}