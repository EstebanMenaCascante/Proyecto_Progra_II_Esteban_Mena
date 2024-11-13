
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

Color generateRandomColor()
{
    // Genera valores aleatorios para los componentes rojo, verde y azul
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    return sf::Color(r, g, b);
}

void centerTextPoint(Text& text, const RectangleShape& rectangle) {
    FloatRect textBounds = text.getLocalBounds();
    FloatRect rectBounds = rectangle.getGlobalBounds();
    text.setPosition(
        rectBounds.left + (rectBounds.width / 2.f) - (textBounds.width / 2.f),
        rectBounds.top + (rectBounds.height / 2.f) - (textBounds.height / 2.f) - textBounds.top
    );
}

Route::Route(const string& routeName)
{
    name = routeName;
    headNode = nullptr; 
    routeColor = generateRandomColor();

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

bool isModified = false;

sf::Vector2f calculateCatmullRom(float t, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {
    float t2 = t * t;
    float t3 = t2 * t;

    float f1 = -0.5f * t3 + t2 - 0.5f * t;
    float f2 = 1.5f * t3 - 2.5f * t2 + 1.0f;
    float f3 = -1.5f * t3 + 2.0f * t2 + 0.5f * t;
    float f4 = 0.5f * t3 - 0.5f * t2;

    return f1 * p0 + f2 * p1 + f3 * p2 + f4 * p3;
}

void Route::drawPoints(sf::RenderWindow& window, sf::Font& font, bool& isModif) {
    Node* temp = headNode;

    // Cambia el color solo si la ruta fue modificada
    if (isModif) {
        Node* nodeTemp = temp;
        while (nodeTemp) {
            nodeTemp->color = generateRandomColor();
            nodeTemp = nodeTemp->next;
        }
        isModif = false;
    }

    const int segments = 60;

    // Asegurarse de tener al menos dos nodos
    if (temp && temp->next) {
        Node* p0 = temp;
        Node* p1 = temp;
        Node* p2 = temp->next;
        Node* p3 = p2->next ? p2->next : p2;  // Evitar puntero nulo

        // Dibuja el primer segmento extendiendo el primer nodo
        sf::VertexArray catmullRomCurve(sf::LineStrip, segments + 1);
        for (int i = 0; i <= segments; ++i) {
            float t = i / static_cast<float>(segments);
            sf::Vector2f point = calculateCatmullRom(t, p0->position, p1->position, p2->position, p3->position);

            catmullRomCurve[i].position = point;
            catmullRomCurve[i].color = p1->color;
        }
        window.draw(catmullRomCurve);

        // Avanza los punteros
        p0 = p1;
        p1 = p2;
        p2 = p3;
        p3 = p3->next;

        // Dibuja los segmentos intermedios
        while (p3) {
            sf::VertexArray catmullRomCurve(sf::LineStrip, segments + 1);

            for (int i = 0; i <= segments; ++i) {
                float t = i / static_cast<float>(segments);
                sf::Vector2f point = calculateCatmullRom(t, p0->position, p1->position, p2->position, p3->position);

                catmullRomCurve[i].position = point;
                catmullRomCurve[i].color = p1->color;
            }

            window.draw(catmullRomCurve);

            p0 = p1;
            p1 = p2;
            p2 = p3;
            p3 = p3->next;
        }

        // Dibuja el último segmento extendiendo el último nodo
        if (p2 && p3 == nullptr) {
            p3 = p2; // Repetir el último punto

            sf::VertexArray catmullRomCurve(sf::LineStrip, segments + 1);
            for (int i = 0; i <= segments; ++i) {
                float t = i / static_cast<float>(segments);
                sf::Vector2f point = calculateCatmullRom(t, p0->position, p1->position, p2->position, p3->position);

                catmullRomCurve[i].position = point;
                catmullRomCurve[i].color = p1->color;
            }
            window.draw(catmullRomCurve);
        }
    }

    // Redibuja cada punto de la ruta con su color asignado
    temp = headNode;
    while (temp) {
        sf::CircleShape point(10);
        point.setOrigin(5, 5);
        point.setPosition(temp->position);
        point.setFillColor(temp->color);
        window.draw(point);

        sf::Text pointLabel(temp->name, font, 15);
        pointLabel.setPosition(temp->position.x + 10, temp->position.y);
        pointLabel.setFillColor(sf::Color::White);

        sf::RectangleShape pointNameBox(sf::Vector2f(75, 20));
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
            current->addPoint(position, namePoint);
            cout << "Punto añadido a la ruta " << routeName << ": " << namePoint << " en ("
                << position.x << ", " << position.y << ")\n";
            return;
        }
        current = current->next;
    }
    cout << "Ruta " << routeName << " no encontrada." << endl;
}

void RouteList::drawRoutes(RenderWindow& window, Font& font, bool isModifi) const {
    Route* current = headRoute;
    while (current != nullptr) {
        current->drawPoints(window, font,isModifi);
        current = current->next;
    }
}

void RouteList::drawRoutesNames(RenderWindow& window, Font& font) {
    Route* current = headRoute;
    int yOffset = 700;

    while (current != nullptr) {
        // Crear el texto de la ruta
        sf::Text routeText;
        routeText.setFont(font);
        routeText.setString(current->name);
        routeText.setCharacterSize(24);
        routeText.setFillColor(sf::Color::White);
        routeText.setPosition(1450, yOffset);  // Posición inicial en la parte visible de la ventana

        window.draw(routeText);  // Dibujar el texto en la ventana

        yOffset += 30;  // Desplazar hacia abajo para el siguiente nombre de ruta
        current = current->next;  // Avanzar al siguiente nodo
    }
}

void RouteList::deletePoint(string& _name, string& _point, bool isMod) {
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
    
    isMod = true;
}

void RouteList::deleteNearPoint(const string& routeName, Vector2f positiones, bool IsMood) {
    // Encuentra la ruta específica por su nombre
    Route* route = headRoute;
    while (route != nullptr && route->name != routeName) {
        route = route->next;
    }

    // Verifica si la ruta fue encontrada
    if (route == nullptr) {
        cout << "Ruta no encontrada: " << routeName << "\n";
        return;
    }

    // Busca el punto más cercano solo dentro de la ruta especificada
    float minDistanceSquared = numeric_limits<float>::max();
    Node* closestPoint = nullptr;

    Node* point = route->headNode;
    while (point != nullptr) {
        float dx = point->position.x - positiones.x;
        float dy = point->position.y - positiones.y;
        float distanceSquared = dx * dx + dy * dy;

        if (distanceSquared < minDistanceSquared) {
            minDistanceSquared = distanceSquared;
            closestPoint = point;
        }
        point = point->next;
    }

    // Si se encontró el punto más cercano, elimínalo
    if (closestPoint != nullptr) {
        deletePoint(route->name, closestPoint->name, IsMood);
    }
    else {
        cout << "No se encontró ningún punto cercano a eliminar en la ruta especificada.\n";
    }
}


string RouteList::searchRoute(string& nameRoute) {
    Route* curr = headRoute;
    while (curr != nullptr) {
        if (curr->name == nameRoute) {
            return curr->name;
        }
        curr = curr->next;
    }
    cout << "No se encontró la ruta.\n";
    return ""; // Asegura que retorna una cadena vacía si no se encuentra la ruta
}

void Route::assignColorToNodes(sf::Color color) {
    Node* temp = headNode;
    while (temp != nullptr) {
        temp->color = color;
        temp = temp->next;
    }
}

Color Node::getColorNode()
{
    if (head != nullptr) {
        return head->color;  // Devuelve el color solo si la lista no está vacía
    }
    else {
        // Maneja el caso donde headNode es nullptr
        cout << "La lista está vacía.\n";
        return Color::Black;  // O el color que consideres apropiado para el caso
    }
}

void Node::setColorNode(Color pColor)
{
    if (head == nullptr) {
        cout << "Error: La lista de nodos está vacía.\n";
        return;
    }

    Node* temp = head;
    while (temp != nullptr) {
        cout << "Cambiando color del nodo: " << temp->name << endl; // Verifica el nodo
        temp->color = pColor;
        temp = temp->next;
    }
}

void RouteList::deleteRoute(const string& routeName) {
    Route* current = headRoute;
    Route* prev = nullptr;

    // Busca la ruta
    while (current != nullptr) {
        if (current->name == routeName) {
            // Si la ruta es la primera
            if (prev == nullptr) {
                headRoute = current->next;
            }
            else {
                prev->next = current->next;
            }

            // Elimina todos los nodos de la ruta (puntos de la ruta)
            Node* point = current->headNode;
            while (point != nullptr) {
                Node* temp = point;
                point = point->next;
                delete temp;
            }

            // Elimina la ruta en sí
            delete current;
            cout << "Ruta " << routeName << " eliminada correctamente." << endl;
            return;
        }
        prev = current;
        current = current->next;
    }

    // Si la ruta no fue encontrada
    cout << "Ruta " << routeName << " no encontrada." << endl;
}

Route* RouteList::getHead() const {
    return headRoute;
}
