#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Node.h"


struct Route {
    string name;
    PointNode* head;
    Route* next;

    Route(const string& routeName) : name(routeName), head(nullptr) {}
    void addPoint(Vector2f position);
    void drawPoints(RenderWindow& window) const;
};


