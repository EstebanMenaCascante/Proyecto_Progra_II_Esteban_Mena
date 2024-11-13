// RouteList.h
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Node.h"
#include "Route.h"

class RouteList {
private:
    Route* headRoute;

public:
    RouteList();
    ~RouteList();
    void addRoute(const string& routeName);
    void addPointToRoute(const string& routeName, Vector2f position, string namePoint);
    void drawRoutes(RenderWindow& window, Font& font) const;
    void deletePoint(string& _name, string& _point);
    void deleteNearPoint(const string& routeName, Vector2f positiones);
    string searchRoute(string& nameRoute);
    Route* getHead() const;
};