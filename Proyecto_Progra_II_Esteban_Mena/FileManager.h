#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include "RouteList.h"
#include "Node.h"
#include "Route.h"

class FileManager {
public:
    static void saveRoutesToFile(const RouteList& routeList, const std::string& filename);
    static void loadRoutesFromFile(RouteList& routeList, const std::string& filename, sf::RenderWindow& window, sf::Font& font);
};

