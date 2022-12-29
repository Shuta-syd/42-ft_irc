#include <Bot.hpp>

int main(int argc, char const *argv[])
{
	if (argc == 4) {
		int port = atoi(argv[1]);
		std::string password(argv[2]);
		std::string channelName(argv[3]);
		Bot IrcBot(port, password, channelName);

		try {
			// signal(SIGINT, QUIT());
			IrcBot.start();
		}
		catch(const std::exception& e) {
			std::cerr << "ERROR:" << e.what() << std::endl;
		}
	} else {
		std::cerr << "[Usage] ./ircbot [Port] [Password] [TargetChannel]" << std::endl;
		return 1;
	}
}
