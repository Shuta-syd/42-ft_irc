#include <Bot.hpp>

Bot::Bot(){}

Bot::Bot(int port, std::string password):port_(port), password_(password_), nick_("FT_BOT") {}

Bot::~Bot(){}

/**
 * @brief bot start func
 */
void Bot::start() {
	this->setupBotSocket();
	this->authorize();
	std::cout << BLU << "------CONNECTED------" << RES << std::endl;

	while (1)	{

	}
}

/**
 * @brief set up a bot socket
 */
void Bot::setupBotSocket() {
	bot_sd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (bot_sd_ < 0)
		throw std::exception();

	struct sockaddr_in addr;
	bzero(&add, sizeof(struct sockaddr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(port_);

	int ret = connect(bot_sd_, (struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0) {
		close(bot_sd_);
		throw std::exception();
	}
}

/**
 * @brief Pass server authentication
 */
void Bot::authorize() {
	sendMessage(bot_sd_, )
}
