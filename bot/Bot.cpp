#include <Bot.hpp>

Bot::Bot() {}

Bot::Bot(int port, std::string password, std::string ch): isAuth_(false), port_(port), password_(password), nick_("Mr.Bot"), channelName_(ch), auth_counter_(1), isVoted_(false) {}

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
		sleep(2);
	}
}
/**
 * @brief  recv message from irc server
 */
void Bot::receive() {
	char message[MSG_MAX] = {0};

	if (auth_counter_ == 3 && isAuth_ == false) {
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
	while (message[i] != ' ' && message[i] != '\r' && message[i] != '\n')
		i++;
	while (message[i] == ' ' && message[i] != '\r' && message[i] != '\n')
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
		sendMessage(bot_sd_, "JOIN #" + channelName_ + "\r\n", 0);
	}
	else if (find(message_, "PRIVMSG") == 1) {
		this->parseMessage();
		int pos = find(parsedMessage_, "POLL");
		std::cout << pos << std::endl;
		if (pos == 1)
			this->vote(&parsedMessage_[4]);
		pos = find(parsedMessage_, "NG");
		std::cout << pos << std::endl;
		if (pos == 1)
			this->addNG_Keyword(&parsedMessage_[2]);
	}
	message_.clear();
	parsedMessage_.clear();
}

void Bot::vote(std::string message) {
	int i = 0;
	std::string topic;

	std::cout << "Vote Feature Started" << std::endl;
	std::cout << message << std::endl;
	while ((message[i] == ' ' || message[i] == ':') && message[i] != '\r' && message[i] != '\n')
		i++;

	while (message[i] && message[i] != '\r' && message[i] != '\n') {
		topic.push_back(message[i]);
		i++;
	}

	sendMessage(bot_sd_, VOTE_WELCOME(channelName_), 0);
	sendMessage(bot_sd_, PRIVMSG(channelName_, "\033[32m[  " + topic + "  ]\033[m"), 0);
	sendMessage(bot_sd_, PRIVMSG(channelName_, "------------------------"), 0);
	sendMessage(bot_sd_, PRIVMSG(channelName_, "|           |          |"), 0);
	sendMessage(bot_sd_, PRIVMSG(channelName_, "|  YES [0]  |  NO [0]  |"), 0);
	sendMessage(bot_sd_, PRIVMSG(channelName_, "|           |          |"), 0);
	sendMessage(bot_sd_, PRIVMSG(channelName_, "------------------------"), 0);

	isVoted_ = true;
	topic.clear();
}

void Bot::addNG_Keyword(std::string message) {
	int i = 0;
	std::string keyword;

	while ((message[i] == ' ' || message[i] == ':') && message[i] != '\r' && message[i] != '\n')
		i++;

	while (message[i] && message[i] != '\r' && message[i] != '\n') {
		keyword.push_back(message[i]);
		i++;
	}

	sendMessage(bot_sd_, NG_REGISTERED(channelName_, keyword), 0);
	ng_words_.push_back(keyword);
}

void Bot::parseMessage() {
	int i = 0;

	while (message_[i] != ':' && message_[i] != '\r' && message_[i] != '\n')
		i++;

	i += 1;

	while (message_[i] && message_[i] != '\r' && message_[i] != '\n') {
		parsedMessage_.push_back(message_[i]);
		i++;
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
