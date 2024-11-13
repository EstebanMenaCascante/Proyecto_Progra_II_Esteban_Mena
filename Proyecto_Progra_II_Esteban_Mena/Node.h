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
    string name;
    Color color;
    Node* next;
    Node* prev;

    Node(Vector2f pos, const string& pointName) : position(pos), name(pointName), next(nullptr), prev(nullptr) {}
    Node() : next(nullptr), prev(nullptr) {}

};

