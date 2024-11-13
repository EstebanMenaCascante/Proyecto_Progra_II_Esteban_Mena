#include "FileManager.h"

void FileManager::saveRoutesToFile(const RouteList& routeList, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error al abrir el archivo para guardar las rutas" << std::endl;
        return;
    }

    Route* currentRoute = routeList.getHead();
    while (currentRoute != nullptr) {
        outFile << currentRoute->name << std::endl;

        Node* currentNode = currentRoute->headNode;
        while (currentNode != nullptr) {
            outFile << "Point: " << currentNode->name << "," << currentNode->position.x << "," << currentNode->position.y << std::endl;
            currentNode = currentNode->next;
        }
        outFile << "END_ROUTE" << std::endl;  // Marcar el final de una ruta
        currentRoute = currentRoute->next;
    }

    outFile.close();
}

void FileManager::loadRoutesFromFile(RouteList& routeList, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error al abrir el archivo para cargar las rutas" << std::endl;
        return;
    }

    std::string line, routeName;
    float x, y;
    while (std::getline(inFile, line)) {
        // Comprobar si la línea es el inicio de una nueva ruta
        if (line.substr(0, 6) == "Route:") {
            routeName = line.substr(7);  // Obtener el nombre de la ruta
            routeList.addRoute(routeName);  // Añadir la ruta al listado

        }
        else if (line.substr(0, 6) == "Point:") {
            // Leer las coordenadas y el nombre del punto
            std::istringstream iss(line.substr(7));
            std::string pointName;
            iss >> pointName >> x >> y;

            // Añadir el punto a la ruta actual
            routeList.addPointToRoute(routeName, sf::Vector2f(x, y), pointName);
        }
        else if (line == "END_ROUTE") {
            // Final de la ruta actual, pasar a la siguiente
            routeName.clear();
        }
    }

    inFile.close();
    std::cout << "Rutas cargadas exitosamente desde el archivo " << filename << std::endl;
}
