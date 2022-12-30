#include <Server.hpp>

void Server::signal_setup() {

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGPIPE, SIG_IGN);
}
