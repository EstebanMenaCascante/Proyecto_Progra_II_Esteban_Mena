#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Node.h"
#include "Route.h"

class RouteList {
private:
    Route* head;

public:
    RouteList();
    ~RouteList();
    void addRoute(const string& routeName);
    void addPointToRoute(const string& routeName, Vector2f position);
    void drawRoutes(RenderWindow& window) const;
};

