#include <Command.hpp>

/**
 * @brief request to start listening to the specific channel
 *
 * JOIN (<channel> *(',' <channel>) [<key> *(',' <key>)]) / "0"
 *
 * ex) JOIN #foo,&bar fubar
 */
void JOIN(Client &client, const std::vector<std::string> &params)
{

}
