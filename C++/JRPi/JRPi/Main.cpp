#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"
#include <time.h>
#include <sstream>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

using namespace std;

string ts(int i)
{
	std::stringstream ss;
	ss << i;
	return ss.str();
}

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
			return ts(i);
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
	string day = ts(theTime->tm_mday);
	int month = theTime->tm_mon;

	string hr = ts(theTime->tm_hour);
	string min = ts(theTime->tm_min);
	string second = ts(theTime->tm_sec);
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
	vector<string> v;
	v.push_back("7");
	v.push_back("8");
	v.push_back("25");
	v.push_back("24");
	v.push_back("23");
	v.push_back("18");
	LCD lcd(v, 16, 2);
	lcd.init();
	long double t = time(0);
	long double pt = t;
	long double tt = t;
	lcd.message(dateTime(), 0);
	lcd.message("IP: " + ipAddr(), 1);
	while(true)
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
	}

	lcd.clear();
	lcd.unExport();

    return 0;
}