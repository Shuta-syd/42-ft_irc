#include <sys/socket.h>
#include <poll.h>
#include <libc.h>

int main(int argc, char const *argv[])
{
	char buf[255];
	int counter = 0;
	struct pollfd mypoll;

	bzero(&mypoll, sizeof(mypoll));
	mypoll.fd = 0;
	mypoll.events = POLLIN;

	printf("Type in your name:\n");

	int pollNum = -100;
	while (1)
	{
		pollNum = poll(&mypoll, 1, 1000);
		if (pollNum > 0)
		{
			if (mypoll.revents & POLLIN)
			{
				read(0, buf, sizeof(buf));
				printf("Hello %s", buf);
				break;
			}
		}
		else
			counter++;
	}

	printf("pollNum: %d It took you %d ms to type in your name", pollNum ,counter * 100);
	return 0;
}
