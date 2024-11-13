#include "FileManager.h"

void FileManager::saveRoutesToFile(const RouteList& routeList, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error al abrir el archivo para guardar las rutas" << std::endl;
        return;
    }

    Route* currentRoute = routeList.getHead();
    while (currentRoute != nullptr) {
        outFile << "Route: " << currentRoute->name << std::endl;

        Node* currentNode = currentRoute->headNode;
        while (currentNode != nullptr) {
            outFile << "Point: " << currentNode->name << "," << currentNode->position.x << "," << currentNode->position.y << std::endl;
            currentNode = currentNode->next;
        }
        outFile << "END_ROUTE" << std::endl;
        currentRoute = currentRoute->next;
    }

    outFile.close();
}


void FileManager::loadRoutesFromFile(RouteList& routeList, const std::string& filename, sf::RenderWindow& window, sf::Font& font) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error al abrir el archivo para cargar las rutas" << std::endl;
        return;
    }

    std::string line;
    std::string routeName;
    while (std::getline(inFile, line)) {
        std::cout << "Leyendo línea: " << line << std::endl;

        if (line == "END_ROUTE") {
            routeName.clear(); 
        }
        else if (line.rfind("Route: ", 0) == 0) { 
            routeName = line.substr(7); 
            std::cout << "Ruta encontrada: " << routeName << std::endl;
            routeList.addRoute(routeName);
        }
        else if (line.rfind("Point: ", 0) == 0) { 
            std::istringstream iss(line.substr(7));  
            std::string pointName, xStr, yStr;

            
            if (std::getline(iss, pointName, ',') &&
                std::getline(iss, xStr, ',') &&
                std::getline(iss, yStr)) {

                try {
                    float x = std::stof(xStr);
                    float y = std::stof(yStr);
                    routeList.addPointToRoute(routeName, sf::Vector2f(x, y), pointName);
                    std::cout << "Punto añadido a " << routeName << ": " << pointName << " (" << x << ", " << y << ")" << std::endl;
                }
                catch (const std::invalid_argument&) {
                    std::cerr << "Error al convertir las coordenadas a float para el punto: " << pointName << std::endl;
                }
            }
        }
    }

    inFile.close();
    std::cout << "Rutas cargadas exitosamente desde el archivo " << filename << std::endl;
}

