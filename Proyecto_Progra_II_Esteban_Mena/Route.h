// Route.h
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Node.h"

struct Route {
    string name;
    Node* headNode;
    Route* next;
    Route* prev;

    Route(const string& routeName) : name(routeName), headNode(nullptr) {}

    void addPoint(Vector2f position, string pointName);
    void drawPoints(RenderWindow& window, Font& font) const;
   
};