#include <Bot.hpp>

Bot::Bot() {}

Bot::Bot(int port, std::string password, std::string ch): isAuth_(false), port_(port), password_(password), nick_("Mr.Bot"), channelName_(ch), auth_counter_(1){}

Bot::~Bot(){}

/**
 * @brief bot start func
 */
void Bot::start() {
	this->setupBotSocket();
	this->createPoll();
	std::cout << BLU << "-----------CONNECTED-----------" << RES << std::endl;

	sendMessage(bot_sd_, CAP_MESSAGE, 0);

	while (1)	{
		receive();
		execute();
		sleep(1);
	}
}
/**
 * @brief  recv message from irc server
 */
void Bot::receive() {
	char message[MSG_MAX] = {0};

	if (auth_counter_ < 2 && isAuth_ == false) {
		std::cerr << RED << "[ERR] Password Incorrect" << RES << std::endl;
		sendMessage(bot_sd_, "QUIT :leaving\r\n", 0);
	}

	std::cout << BLU << "--------Waiting Message--------" << RES << std::endl;
	ssize_t bytes = recv(bot_sd_, message, sizeof(message), 0);
	if (bytes < 0)
		throw std::exception();

	std::cout << "--------RECEIVE Message--------" << std::endl;
	std::cout << "client : " << message << std::endl;
	std::cout << "-------------------------------" << std::endl;

	int i = 0;
	while (message[i] != ' ' && message[i] != '\r')
		i++;
	while (message[i] == ' ' && message[i] != '\r')
		i++;
	while (message[i] != '\r' && message[i] != '\n') {
		message_.push_back(message[i]);
		i++;
	}
	std::cout << "ParsedMessage: [" << message_ << "]" << std::endl;
	auth_counter_ += 1;
}

/**
 * @brief
 */
void Bot::execute() {

	if (find(message_, "CAP") == 1)
		authorize();
	else if (find(message_, "NICK") == 1){
		if (isAuth_ == false) {
			sendMessage(bot_sd_, "CAP END\r\n", 0);
			isAuth_ = true;
		}
	}
	message_.clear();
}

/**
 * @brief Pass server authentication
 */
void Bot::authorize() {
	sendMessage(bot_sd_, PASS_MESSAGE(password_), 0);
	sendMessage(bot_sd_, NICK_MESSAGE(nick_), 0);
	sendMessage(bot_sd_, USER_MESSAGE(nick_, "*", "*", nick_), 0);
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
 * @brief to create polling method corresponding to the num of fds (include server socket fd)
 * @param sockfd An indication of which fd for which PollMethod to create
 *
 */
void Bot::createPoll() {
	pollfd_.fd = bot_sd_;
	pollfd_.events = POLLIN;
	pollfd_.revents = 0;
}
