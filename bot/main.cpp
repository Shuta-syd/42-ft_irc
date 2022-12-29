#include <Bot.hpp>

int main(int argc, char const *argv[])
{
	if (argc == 3) {
		int port = atoi(argv[1]);
		std::string password(argv[2]);
		Bot IrcBot(port, password);

		try {
			IrcBot.start();
		}
		catch(const std::exception& e) {
			std::cerr << "ERROR:" << e.what() << std::endl;
		}
	} else {
		std::cerr << "[Usage] ./ircbot [Port] [Password] " << std::endl;
		return 1;
	}
}
