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
    Route();

    void addPoint(Vector2f position, string pointName);
    void drawPoints(RenderWindow& window, Font& font) const;
    void drawColorPalette(sf::RenderWindow& window);
    Color handleColorSelection(sf::Vector2i mousePos);
    void applyColorToPoints(sf::Color color);
    void processEvents(sf::RenderWindow& window, sf::Event& event);
   
};