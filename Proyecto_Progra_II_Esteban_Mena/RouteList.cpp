
//RouteList.cpp

#include "RouteList.h"

RouteList::RouteList() : headRoute(nullptr) {}

RouteList::~RouteList() {
    Route* currentRoute = headRoute;
    while (currentRoute != nullptr) {
        Node* currentPoint = currentRoute->headNode;
        while (currentPoint != nullptr) {
            Node* tempPoint = currentPoint;
            currentPoint = currentPoint->next;
            delete tempPoint;
        }
        Route* tempRoute = currentRoute;
        currentRoute = currentRoute->next;
        delete tempRoute;
    }
}

void centerTextPoint(Text& text, const RectangleShape& rectangle) {
    FloatRect textBounds = text.getLocalBounds();
    FloatRect rectBounds = rectangle.getGlobalBounds();
    text.setPosition(
        rectBounds.left + (rectBounds.width / 2.f) - (textBounds.width / 2.f),
        rectBounds.top + (rectBounds.height / 2.f) - (textBounds.height / 2.f) - textBounds.top
    );
}

Route::Route()
{
}

void Route::addPoint(sf::Vector2f position, string pointName) {
   
    Node* newNode = new Node(position, pointName);
    if (!headNode) {
        headNode = newNode;
    }
    else {
        Node* temp = headNode;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void Route::drawPoints(sf::RenderWindow& window, sf::Font& font) const {
    Node* temp = headNode;

    if (temp && temp->next) {
        const int segments = 40;
        const float thickness = 50.0f;

        while (temp->next) {
            Node* next = temp->next;

            for (float offset = -thickness / 2; offset <= thickness / 2; offset += 1.0f) {
                sf::VertexArray smoothCurve(sf::LinesStrip, segments + 1);

                for (int i = 0; i <= segments; ++i) {
                    float t = i / static_cast<float>(segments);
                    float t2 = t * t;
                    float t3 = t2 * t;

                    sf::Vector2f interpolatedPos(
                        (2 * t3 - 3 * t2 + 1) * temp->position.x + (t3 - 2 * t2 + t) * (temp->position.x + 60 + offset) +
                        (-2 * t3 + 3 * t2) * next->position.x + (t3 - t2) * (next->position.x - 60 + offset),

                        (2 * t3 - 3 * t2 + 1) * temp->position.y + (t3 - 2 * t2 + t) * (temp->position.y + 60 + offset) +
                        (-2 * t3 + 3 * t2) * next->position.y + (t3 - t2) * (next->position.y - 60 + offset)
                    );

                    smoothCurve[i].position = interpolatedPos;
                    smoothCurve[i].color = sf::Color::Blue;
                }

                window.draw(smoothCurve);
            }

            temp = temp->next;
        }
    }

    temp = headNode;
    while (temp) {
        sf::CircleShape point(10);
        point.setOrigin(5, 5);
        point.setPosition(temp->position);
        point.setFillColor(sf::Color::Red);
        window.draw(point);

        sf::Text pointLabel(temp->name, font, 15);
        pointLabel.setPosition(temp->position.x + 10, temp->position.y);
        pointLabel.setFillColor(sf::Color::White);

        RectangleShape pointNameBox(Vector2f(75, 20));
        pointNameBox.setFillColor(sf::Color(0, 0, 0, 150));
        pointNameBox.setPosition(temp->position.x + 20, temp->position.y);
        centerTextPoint(pointLabel, pointNameBox);

        window.draw(pointNameBox);
        window.draw(pointLabel);

        temp = temp->next;
    }
}


void RouteList::addRoute(const string& routeName) {
    Route* newRoute = new Route(routeName);
    newRoute->next = headRoute;
    headRoute = newRoute;
}

void RouteList::addPointToRoute(const string& routeName, Vector2f position, string namePoint) {
    Route* current = headRoute;
    while (current != nullptr) {
        if (current->name == routeName) {
            current->addPoint(position,namePoint);
            return;
        }
        current = current->next;
    }
    cout << "Ruta " << routeName << " no encontrada." << endl;
}

void RouteList::drawRoutes(RenderWindow& window, Font& font) const {
    Route* current = headRoute;
    while (current != nullptr) {
        current->drawPoints(window, font);
        current = current->next;
    }
}

void RouteList::deletePoint(string& _name, string& _point) {
    Route* route = headRoute;
    while (route && route->name != _name) {
        route = route->next;
    }
    if (!route) return;
    Node* temp = route->headNode;
    while (temp && temp->name != _point) {
        temp = temp->next;
    }
    if (!temp) return;
    if (temp->prev)temp->prev->next = temp->next;
    if (temp->next)temp->next->prev = temp->prev;
    if (temp == route->headNode)route->headNode = temp->next;
    delete temp;
}

void RouteList::deleteNearPoint(const string& routeName, Vector2f positiones) {
    Route* route = headRoute;
    if (route->name == routeName) 
    {
        if (!headRoute)return;

        float minDistanceSquared = numeric_limits<float>::max();
        Node* closestPoint = nullptr;
        Route* closestRoute = nullptr;


        while (route) {
            Node* point = route->headNode;
            while (point) {
                int dx = point->position.x - positiones.x;
                int dy = point->position.y - positiones.y;
                float distanceSquared = dx * dx + dy * dy;
                if (distanceSquared < minDistanceSquared) {
                    minDistanceSquared = distanceSquared;
                    closestPoint = point;
                    closestRoute = route;
                }
                point = point->next;
            }
            route = route->next;
        }
        if (closestPoint && closestRoute) {
            deletePoint(closestRoute->name, closestPoint->name);
        }
        else {
            cout << "No se encontro ningun punto a eliminar\n";
        }
    }
}

string RouteList::searchRoute(string& nameRoute)
{
    Route* curr = headRoute;
    while (curr != nullptr) {
        if (curr->name == nameRoute) {
           return curr->name;
        }
        curr = curr->next;
    }
    cerr<<"No se encontro la ruta.\n";
}

void Route::drawColorPalette(sf::RenderWindow& window) {
    // Crear una paleta de colores
    sf::RectangleShape redColorBox(sf::Vector2f(50, 50));
    redColorBox.setFillColor(sf::Color::Red);
    redColorBox.setPosition(1450, 300);

    sf::RectangleShape blackColorBox(sf::Vector2f(50, 50));
    blackColorBox.setFillColor(sf::Color::Black);
    blackColorBox.setPosition(1500, 300);

    sf::RectangleShape cyanColorBox(sf::Vector2f(50, 50));
    cyanColorBox.setFillColor(sf::Color::Cyan);
    cyanColorBox.setPosition(1550, 300);

    sf::RectangleShape magentaColorBox(sf::Vector2f(50, 50));
    magentaColorBox.setFillColor(sf::Color::Magenta);
    magentaColorBox.setPosition(1450, 350);

    sf::RectangleShape greenColorBox(sf::Vector2f(50, 50));
    greenColorBox.setFillColor(sf::Color::Green);
    greenColorBox.setPosition(1500, 350);

    sf::RectangleShape blueColorBox(sf::Vector2f(50, 50));
    blueColorBox.setFillColor(sf::Color::Blue);
    blueColorBox.setPosition(1550, 350);

    // Dibujar la paleta
    window.draw(redColorBox);
    window.draw(blackColorBox);
    window.draw(cyanColorBox);
    window.draw(magentaColorBox);
    window.draw(greenColorBox);
    window.draw(blueColorBox);
}

Color Route::handleColorSelection(sf::Vector2i mousePos) 
{
    // Verificar si el clic ocurrió sobre algún color de la paleta
    if (mousePos.x >= 10 && mousePos.x <= 60 && mousePos.y >= 10 && mousePos.y <= 60) {
        return sf::Color::Red;
    }
    if (mousePos.x >= 10 && mousePos.x <= 60 && mousePos.y >= 10 && mousePos.y <= 60) {
        return sf::Color::Black;
    }
    if (mousePos.x >= 10 && mousePos.x <= 60 && mousePos.y >= 10 && mousePos.y <= 60) {
        return sf::Color::Cyan;
    }
    if (mousePos.x >= 70 && mousePos.x <= 120 && mousePos.y >= 10 && mousePos.y <= 60) {
        return sf::Color::Magenta;
    }
    if (mousePos.x >= 70 && mousePos.x <= 120 && mousePos.y >= 10 && mousePos.y <= 60) {
        return sf::Color::Green;
    }
    if (mousePos.x >= 130 && mousePos.x <= 180 && mousePos.y >= 10 && mousePos.y <= 60) {
        return sf::Color::Blue;
    }
    return sf::Color::White;  // No se seleccionó ningún color
}

void Route::applyColorToPoints(sf::Color color) {
    Node* temp = headNode;
    while (temp) {
        temp->color = color;  // Asignar el color a cada punto
        temp = temp->next;
    }
}

void Route::processEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Detectar clic en la paleta de colores
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Color selectedColor = handleColorSelection(mousePos);

            if (selectedColor != sf::Color::White) {
                // Si se seleccionó un color, aplicar ese color a los puntos de la ruta
                applyColorToPoints(selectedColor);
            }
        }
    }
}


Route* RouteList::getHead() const {
    return headRoute;
}
