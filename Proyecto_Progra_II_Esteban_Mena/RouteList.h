// RouteList.h
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Node.h"
#include "Route.h"
#include <cstdlib>
#include <ctime>

class RouteList {
private:
    Route* headRoute;

public:
    RouteList();
    ~RouteList();
    void addRoute(const string& routeName);
    void addPointToRoute(const string& routeName, Vector2f position, string namePoint);
    void drawRoutes(RenderWindow& window, Font& font, bool isModifi) const;
    void drawRoutesNames(RenderWindow& window, Font& font);
    void deletePoint(string& _name, string& _point, bool isMod);
    void deleteNearPoint(const string& routeName, Vector2f positiones, bool IsMood);
    string searchRoute(string& nameRoute);
    void deleteRoute(const string& routeName);
    Route* getHead() const;
};