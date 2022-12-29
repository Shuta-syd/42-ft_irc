#include <Bot.hpp>

Bot::Bot(){}

Bot::Bot(int port, std::string password):port_(port), password_(password), nick_("FT_BOT") {}

Bot::~Bot(){}

/**
 * @brief bot start func
 */
void Bot::start() {
	this->setupBotSocket();
	this->authorize();
	std::cout << BLU << "------CONNECTED------" << RES << std::endl;

	while (1)	{
		receive(bot_sd_);
	}
}

/**
 * @brief
 */
void Bot::receive(int fd) {
	char message[MSG_MAX] = {0};

	ssize_t bytes = recv(fd, message, sizeof(message), 0);
	if (bytes < 0)
		throw std::exception();
}

/**
 * @brief set up a bot socket
 */
void Bot::setupBotSocket() {
	bot_sd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (bot_sd_ < 0)
		throw std::exception();

	struct sockaddr_in addr;
	bzero(&addr, sizeof(struct sockaddr));
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
	sendMessage(bot_sd_, PASS_MESSAGE(password_), 0);
	sendMessage(bot_sd_, NICK_MESSAGE(nick_), 0);
	sendMessage(bot_sd_, USER_MESSAGE(nick_, "*", "*", nick_), 0);
}
