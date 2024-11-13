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
    Color routeColor;
    Route* next;
    Route* prev;

    Route(const string& routeName);
    Route();

    void addPoint(Vector2f position, string pointName);
    void drawPoints(sf::RenderWindow& window, sf::Font& font, bool& isModif);
    void assignColorToNodes(sf::Color color);
   
};