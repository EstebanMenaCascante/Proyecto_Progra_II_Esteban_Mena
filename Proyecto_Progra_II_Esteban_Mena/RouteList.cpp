#include "RouteList.h"

RouteList::RouteList() : head(nullptr) {}

RouteList::~RouteList() {
    Route* currentRoute = head;
    while (currentRoute != nullptr) {
        PointNode* currentPoint = currentRoute->head;
        while (currentPoint != nullptr) {
            PointNode* tempPoint = currentPoint;
            currentPoint = currentPoint->next;
            delete tempPoint;
        }
        Route* tempRoute = currentRoute;
        currentRoute = currentRoute->next;
        delete tempRoute;
    }
}

void Route::addPoint(Vector2f position) {
    PointNode* newPoint = new PointNode(position);
    newPoint->next = head;
    head = newPoint;
}

void Route::drawPoints(RenderWindow& window) const {
    PointNode* current = head;
    CircleShape pointShape(5);
    pointShape.setFillColor(Color::Red);

    while (current != nullptr) {
        pointShape.setPosition(current->position);
        window.draw(pointShape);
        current = current->next;
    }
}

void RouteList::addRoute(const string& routeName) {
    Route* newRoute = new Route(routeName);
    newRoute->next = head;
    head = newRoute;
}

void RouteList::addPointToRoute(const string& routeName, Vector2f position) {
    Route* current = head;
    while (current != nullptr) {
        if (current->name == routeName) {
            current->addPoint(position);
            return;
        }
        current = current->next;
    }
    cout << "Ruta " << routeName << " no encontrada." << endl;
}

void RouteList::drawRoutes(RenderWindow& window) const {
    Route* current = head;
    while (current != nullptr) {
        current->drawPoints(window);
        current = current->next;
    }
}