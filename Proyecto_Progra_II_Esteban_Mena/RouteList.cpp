
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
    while (temp) {
        sf::CircleShape point(10);
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
           return curr->name;  // Se encontró el elemento.
        }
        curr = curr->next;
    }
    cerr<<"No se encontro la ruta.\n";
}



Route* RouteList::getHead() const {
    return headRoute;
}
