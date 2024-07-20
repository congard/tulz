#ifndef TULZ_ROUTINGKEYLEVEL_H
#define TULZ_ROUTINGKEYLEVEL_H

#include <string>
#include <regex>
#include <variant>

namespace tulz {
using RoutingKeyLevel = std::variant<std::string, std::regex>;
}

#endif //TULZ_ROUTINGKEYLEVEL_H
