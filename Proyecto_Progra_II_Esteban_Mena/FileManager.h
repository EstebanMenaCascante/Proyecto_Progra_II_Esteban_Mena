#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include "RouteList.h"

class FileManager {
public:
    static void saveRoutesToFile(const RouteList& routeList, const std::string& filename);
    static void loadRoutesFromFile(RouteList& routeList, const std::string& filename);
};