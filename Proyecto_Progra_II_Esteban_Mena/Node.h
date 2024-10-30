#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

struct PointNode {
    Vector2f position;
    PointNode* next;

    PointNode(Vector2f pos) : position(pos), next(nullptr) {}
};

