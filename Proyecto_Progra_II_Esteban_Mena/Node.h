#pragma once

//Node.h

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

struct Node {
    Vector2f position;
    Node* head;
    string name;
    Color color;
    Node* next;
    Node* prev;

    Node(Vector2f pos, const string& pointName) : position(pos), name(pointName),color(Color::Red), next(nullptr), prev(nullptr) {}
    Node() : next(nullptr), prev(nullptr) {}
    Color getColorNode();
    void setColorNode(Color pColor);

};

