#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "RouteList.h"
#include "FileManager.h"

using namespace std;
using namespace sf;

void centerTextInRectangle(Text& text, const RectangleShape& rectangle) {
    FloatRect textBounds = text.getLocalBounds();
    FloatRect rectBounds = rectangle.getGlobalBounds();
    text.setPosition(
        rectBounds.left + (rectBounds.width / 2.f) - (textBounds.width / 2.f),
        rectBounds.top + (rectBounds.height / 2.f) - (textBounds.height / 2.f) - textBounds.top
    );
}



int main()
{
    RenderWindow window(VideoMode(1800, 1000), "Destinos Magicos");

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/background.jpg"))
    {
        cout << "Error cargando la imagen de fondo" << endl;
        return -1;
    }

    Sprite background(backgroundTexture);

    Font font;
    if (!font.loadFromFile("font/DS_Celtic-2.ttf"))
    {
        cout << "Error cargando la fuente" << endl;
        return -1;
    }

    Font font1;
    if (!font1.loadFromFile("font/MorrisRoman-Black.ttf"))
    {
        cout << "Error cargando la fuente" << endl;
        return -1;
    }

    Font font2;
    if (!font2.loadFromFile("font/tolkien.ttf"))
    {
        cout << "Error cargando la fuente" << endl;
        return -1;
    }

    Text title("Destinos Magicos", font, 80);
    title.setFillColor(sf::Color::White);

    RectangleShape titleBox(sf::Vector2f(800, 100));
    titleBox.setFillColor(sf::Color(0, 0, 0, 150)); 
    titleBox.setPosition((window.getSize().x - titleBox.getSize().x) / 2, 200);
    centerTextInRectangle(title, titleBox); 

    bool menu = true;
    bool about = false;
    bool map = false;

    bool mainMenu = true;
    bool insertMenu = false;
    bool editMenu = false;

    Text aboutButton("Acerca de", font2, 40);
    Text mapButton("Mostrar Mapa", font2, 40);
    Text exitButton("Salir", font2, 40);

    Text returnButton("Regresar", font2, 20);

    Text returnAboutButton("Regresar", font2, 40);

    Text addPointButton("Agregar Punto", font2, 35);
    Text changeColorButton("Elija un Color", font2, 35);
    Text deletePointButton("Eliminar Punto", font2, 35);

    Text insertButton("Insercion", font2, 40);
    Text editButton("Edicion", font2, 40);
    Text deleteButton("Borrar", font2, 40);

    Text addRouteButton("Agregar Ruta", font2, 40);

    Text saveRouteButton("Guardar", font2, 20);
    Text chargeRouteButton("Cargar Rutas", font2, 40);


    returnButton.setFillColor(Color::Black);
    addPointButton.setFillColor(Color::Black);
    changeColorButton.setFillColor(Color::Black);
    deletePointButton.setFillColor(Color::Black);

    insertButton.setFillColor(Color::Black);
    editButton.setFillColor(Color::Black);
    deleteButton.setFillColor(Color::Black);

    addRouteButton.setFillColor(Color::Black);
    saveRouteButton.setFillColor(Color::Black);
    chargeRouteButton.setFillColor(Color::Black);

    RectangleShape insertBox(Vector2f(250, 75));
    insertBox.setPosition(1430, 300);
    insertBox.setFillColor(Color::White);
    centerTextInRectangle(insertButton, insertBox);

    RectangleShape editBox(Vector2f(250, 75));
    editBox.setPosition(1430, 400);
    editBox.setFillColor(Color::White);
    centerTextInRectangle(editButton, editBox);

    RectangleShape deleteBox(Vector2f(250, 75));
    deleteBox.setPosition(1430, 500);
    deleteBox.setFillColor(Color::White);
    centerTextInRectangle(deleteButton, deleteBox);

   
    RectangleShape addRouteBox(Vector2f(250, 75));
    addRouteBox.setPosition(1430, 100);
    addRouteBox.setFillColor(Color::White);
    centerTextInRectangle(addRouteButton, addRouteBox);

    RectangleShape addPointBox(Vector2f(250, 75));
    addPointBox.setPosition(1430, 150);
    addPointBox.setFillColor(Color::White);
    centerTextInRectangle(addPointButton, addPointBox);
    
    RectangleShape chargeBox(Vector2f(250, 75));
    chargeBox.setPosition(1430, 450);
    chargeBox.setFillColor(Color::White);
    centerTextInRectangle(chargeRouteButton, chargeBox);

    RectangleShape changeColorBox(Vector2f(250, 65));
    changeColorBox.setPosition(1430, 200);
    changeColorBox.setFillColor(Color::White);
    centerTextInRectangle(changeColorButton, changeColorBox);

    RectangleShape deletePointBox(Vector2f(250, 75));
    deletePointBox.setPosition(1430, 350);
    deletePointBox.setFillColor(Color::White);
    centerTextInRectangle(deletePointButton, deletePointBox);
    
    RectangleShape returnAboutBox(Vector2f(150, 55));
    returnAboutBox.setFillColor(sf::Color(0, 0, 0, 150));
    returnAboutBox.setPosition(50, 10);
    centerTextInRectangle(returnAboutButton, returnAboutBox);

    RectangleShape returnBox(Vector2f(85, 30));
    returnBox.setFillColor(Color::White);
    returnBox.setPosition(1300, 10);
    centerTextInRectangle(returnButton, returnBox);

    sf::RectangleShape aboutBox(sf::Vector2f(400, 60));
    aboutBox.setFillColor(sf::Color(0, 0, 0, 150));
    aboutBox.setPosition((window.getSize().x - aboutBox.getSize().x) / 2, 500);
    centerTextInRectangle(aboutButton, aboutBox);

    sf::RectangleShape mapBox(sf::Vector2f(400, 60));
    mapBox.setFillColor(sf::Color(0, 0, 0, 150));
    mapBox.setPosition((window.getSize().x - mapBox.getSize().x) / 2, 600);
    centerTextInRectangle(mapButton, mapBox);

    sf::RectangleShape exitBox(sf::Vector2f(400, 60));
    exitBox.setFillColor(sf::Color(0, 0, 0, 150));
    exitBox.setPosition((window.getSize().x - exitBox.getSize().x) / 2, 700);
    centerTextInRectangle(exitButton, exitBox);

    sf::RectangleShape saveBox(sf::Vector2f(85, 30));
    saveBox.setFillColor(Color::White);
    saveBox.setPosition(1300, 100);
    centerTextInRectangle(saveRouteButton, saveBox);
    

    sf::Music music;
    if (!music.openFromFile("The Hobbit_LOTR_Sound_of_The_Shire.ogg")) {
        cerr << "Error al cargar la música\n";
        return -1;
    }

    music.setVolume(30.0f);
    music.setLoop(true);
    music.play();

    srand(static_cast<unsigned>(time(nullptr)));
    RouteList routeList;
    Route route;
    Node node;
    string currentRouteName;
    bool addingRoute = false;
    bool addPointsMode = false;
    bool deletePointsMode = false;
    bool colorChose = false;

    bool isModificable = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (aboutBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    sf::RenderWindow aboutWindow(sf::VideoMode(1000, 700), "Acerca de");

                    sf::Sprite aboutBackground(backgroundTexture);
                    aboutBackground.setScale(
                        float(aboutWindow.getSize().x) / backgroundTexture.getSize().x,
                        float(aboutWindow.getSize().y) / backgroundTexture.getSize().y);

                    sf::RectangleShape aboutTextBox(sf::Vector2f(900, 250));
                    aboutTextBox.setFillColor(sf::Color(0, 0, 0, 150));
                    aboutTextBox.setPosition(50, 75);

                    sf::Text projectInfo(
                        "II Proyecto de Programacion\n"
                        "Nombre de la Agencia: Destinos Magicos\n"
                        "Estudiante: Esteban Mena\n"
                        "Profesor: Hairol Romero", font1, 25);
                    projectInfo.setFillColor(sf::Color::White);
                    centerTextInRectangle(projectInfo, aboutTextBox);

                    while (aboutWindow.isOpen())
                    {
                        sf::Event aboutEvent;
                        while (aboutWindow.pollEvent(aboutEvent))
                        {
                            if (aboutEvent.type == sf::Event::Closed)
                                aboutWindow.close();
                        }

                        aboutWindow.clear();
                        aboutWindow.draw(aboutBackground); 
                        aboutWindow.draw(aboutTextBox);  
                        aboutWindow.draw(projectInfo); 
                        aboutWindow.draw(returnAboutBox);
                        aboutWindow.draw(returnAboutButton);

                        while (aboutWindow.pollEvent(event)) {

                            if (event.type == sf::Event::Closed)
                                window.close();

                            if (event.type == sf::Event::MouseButtonPressed){
                                sf::Vector2i mousePos = sf::Mouse::getPosition(aboutWindow);

                                if (returnAboutBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                    aboutWindow.close();
                                }

                            }
                        
                        }

                       
                        aboutWindow.display();

                    }
                }
                if (mapBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    sf::RenderWindow mapWindow(sf::VideoMode(1800, 1000), "Mapa");

                    Texture mapTexture;
                    if (!mapTexture.loadFromFile("images/LOTR_map3.jpg")) {
                        cout << "Error cargando el mapa" << endl;
                        return -1;
                    }
                    Sprite mapSprite(mapTexture);

                    while (mapWindow.isOpen()) {
                        sf::Event mapEvent;
                        while (mapWindow.pollEvent(mapEvent)) {
                            if (mapEvent.type == sf::Event::Closed)
                                mapWindow.close();

                            if (mapEvent.type == sf::Event::MouseButtonPressed) {
                                sf::Vector2i mousePosMap = sf::Mouse::getPosition(mapWindow);

                                if (mainMenu) {
                                    if (insertBox.getGlobalBounds().contains(mousePosMap.x, mousePosMap.y)) {
                                        mainMenu = false;
                                        insertMenu = true;
                                    }
                                    else if (editBox.getGlobalBounds().contains(mousePosMap.x, mousePosMap.y)) {
                                        mainMenu = false;
                                        editMenu = true;
                                    }
                                    else if (deleteBox.getGlobalBounds().contains(mousePosMap.x, mousePosMap.y)) {
                                        string routeNameOpcion;
                                        cout << "Ingrese el la ruta que quiere borrar: ";
                                        cin >> routeNameOpcion;

                                        routeList.searchRoute(routeNameOpcion);
                                        currentRouteName = routeNameOpcion;

                                        routeList.deleteRoute(currentRouteName);

                                    }
                                    else if (returnBox.getGlobalBounds().contains(mousePosMap.x, mousePosMap.y)) {
                                        mapWindow.close();
                                    }
                                }
                                else if (insertMenu) {

                                    if (addRouteBox.getGlobalBounds().contains(mousePosMap.x, mousePosMap.y)) {
                                        cout << "\nIngrese el nombre de la nueva ruta: ";
                                        cin >> currentRouteName;
                                        routeList.addRoute(currentRouteName);      
                                        //isModificable = true;
                                        addPointsMode = true;
                                        colorChose = true;
                                    }
                                    if (chargeBox.getGlobalBounds().contains(mousePosMap.x, mousePosMap.y)) {
                                        cout << "Cargando rutas\n";
                                        FileManager::loadRoutesFromFile(routeList, "route.txt", mapWindow, font);
                                    }
                                    else if (addPointsMode && mapEvent.mouseButton.button == Mouse::Left && mapEvent.mouseButton.x<1293 && mapEvent.mouseButton.y<937) {
                                        Vector2f pointPos = mapWindow.mapPixelToCoords(mousePosMap);
                                        string pointName;
                                        cout << "Ingrese el nombre del punto: ";
                                        cin >> pointName;
                                        routeList.addPointToRoute(currentRouteName, pointPos, pointName);
                                        //isModificable = false;
                                    }
                                    else if (colorChose && mapEvent.mouseButton.button == Mouse::Left && mapEvent.mouseButton.x >= 1430 && mapEvent.mouseButton.x <= 1430 + 250 && mapEvent.mouseButton.y >= 100 && mapEvent.mouseButton.y >= 100 + 65)
                                    {
                                        cout << "Seleccionando color...\n";
                                        RenderWindow paletteWindow(VideoMode(500, 500), "Paleta de Color");

                                        Texture paletteTexture;
                                        if (!paletteTexture.loadFromFile("images/img_colors.png")) {
                                            throw runtime_error("Error al cargar la imagen de la paleta de colores.");
                                        }

                                        Sprite paletteSprite(paletteTexture);
                                        Image paletteImage = paletteTexture.copyToImage();

                                        bool colorSelected = false;  // Variable para controlar la selección del color

                                        while (paletteWindow.isOpen()) {
                                            Event event;
                                            while (paletteWindow.pollEvent(event)) {
                                                if (event.type == Event::Closed) {
                                                    paletteWindow.close();  // Cierra la ventana de la paleta
                                                }
                                                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                                                    Vector2i mousePos = Mouse::getPosition(paletteWindow);

                                                    // Verifica si el clic fue dentro de la imagen de la paleta
                                                    if (mousePos.x >= 0 && mousePos.x < paletteTexture.getSize().x &&
                                                        mousePos.y >= 0 && mousePos.y < paletteTexture.getSize().y) {

                                                        Color selectedColor = paletteImage.getPixel(mousePos.x, mousePos.y);

                                                        // Asigna el color al nodo
                                                        node.color = selectedColor;
                                                        cout << "Color seleccionado!!!\n";

                                                        colorSelected = true;  // Marca que se seleccionó un color
                                                        break;  // Sale del ciclo de eventos
                                                    }
                                                }
                                            }

                                            if (colorSelected) {
                                                paletteWindow.close();  // Cierra la ventana de la paleta si se seleccionó el color
                                            }

                                            paletteWindow.clear(Color::White);
                                            paletteWindow.draw(paletteSprite);
                                            paletteWindow.display();
                                        }
                                    }
                                    else if (saveBox.getGlobalBounds().contains(mousePosMap.x, mousePosMap.y)) {
                                        FileManager::saveRoutesToFile(routeList, "route.txt");
                                        cout << "\nSe ha guardado la ruta\n";
                                    }
                                    else if (returnBox.getGlobalBounds().contains(mousePosMap.x, mousePosMap.y)) {
                                        insertMenu = false;
                                        mainMenu = true;
                                        addPointsMode = false; // Desactivar modo de agregar puntos
                                    }
                                }


                                else if (editMenu) {
                                    if (saveBox.getGlobalBounds().contains(mousePosMap.x, mousePosMap.y)) {
                                        FileManager::saveRoutesToFile(routeList, "route.txt");
                                        cout << "\nSe ha guardado la ruta\n";
                                    }
                                    if (returnBox.getGlobalBounds().contains(mousePosMap.x, mousePosMap.y)) {
                                        editMenu = false;
                                        mainMenu = true;
                                    }
                                    if (addPointBox.getGlobalBounds().contains(mousePosMap.x, mousePosMap.y)) {
                                                
                                        string routeNameOpcion;
                                        cout << "Ingrese el la ruta que quiere editar: ";
                                        cin >> routeNameOpcion;

                                        routeList.searchRoute(routeNameOpcion);
                                        currentRouteName = routeNameOpcion;

                                        if (!routeNameOpcion.empty()) 
                                        {
                                            deletePointsMode = false;
                                            addPointsMode = true;
                                            isModificable = true;
                                        }
                                    }
                                    if (addPointsMode && mapEvent.mouseButton.button == Mouse::Left && mapEvent.mouseButton.x < 1293 && mapEvent.mouseButton.y < 937) {
                                        if (!currentRouteName.empty()) {
                                            Vector2f pointPos = mapWindow.mapPixelToCoords(mousePosMap);
                                            string pointName;
                                            cout << "Ingrese el nombre del punto: ";
                                            cin >> pointName;

                                            // Llama a la función para agregar el punto a la ruta específica
                                            routeList.addPointToRoute(currentRouteName, pointPos, pointName);
                                            cout << "Punto agregado a la ruta " << currentRouteName << ".\n";
                                            isModificable = false;
                                        }
                                        else {
                                            cout << "Error: No se ha seleccionado ninguna ruta.\n";
                                        }
                                    }
                                   
                                    if (deletePointBox.getGlobalBounds().contains(mousePosMap.x, mousePosMap.y)) {
                                        if (deletePointBox.getGlobalBounds().contains(mousePosMap.x, mousePosMap.y)) {
                                            string routeNameOpcion;
                                            cout << "Ingrese la ruta de la que quiere eliminar un punto: ";
                                            cin >> routeNameOpcion;

                                            // Busca la ruta y verifica si existe antes de activar deletePointsMode
                                            if (routeList.searchRoute(routeNameOpcion) != "") {
                                                currentRouteName = routeNameOpcion;
                                                cout << "Ruta encontrada. Puede eliminar puntos.\n";
                                                addPointsMode = false;
                                                deletePointsMode = true;
                                                //isModificable = true;
                                            }
                                            else {
                                                cout << "Ruta no encontrada. Verifique el nombre ingresado.\n";
                                                deletePointsMode = false;
                                            }
                                        }
                                    }
                                    if (deletePointsMode && mapEvent.mouseButton.button == Mouse::Left && mapEvent.mouseButton.x < 1293 && mapEvent.mouseButton.y < 937)
                                    {
                                        Vector2f mousetPos = mapWindow.mapPixelToCoords(mousePosMap);
                                        routeList.deleteNearPoint(currentRouteName, mousetPos, isModificable);
                                        isModificable = false;
                                    }                                    
                                }
                            }
                        }

                        mapWindow.clear();
                        mapWindow.draw(mapSprite);
                        mapWindow.draw(returnBox);
                        mapWindow.draw(returnButton);

                        if (mainMenu) {
                            mapWindow.draw(insertBox); mapWindow.draw(insertButton);
                            mapWindow.draw(editBox); mapWindow.draw(editButton);
                            mapWindow.draw(deleteBox); mapWindow.draw(deleteButton);

                        }
                        else if (insertMenu) {
                            mapWindow.draw(addRouteBox); mapWindow.draw(addRouteButton);
                            mapWindow.draw(saveBox); mapWindow.draw(saveRouteButton);
                            mapWindow.draw(changeColorBox); mapWindow.draw(changeColorButton);
                            mapWindow.draw(chargeBox); mapWindow.draw(chargeRouteButton);
                        }
                        else if (editMenu) {
                            mapWindow.draw(addPointBox); mapWindow.draw(addPointButton);
                           mapWindow.draw(deletePointBox); mapWindow.draw(deletePointButton);
                            mapWindow.draw(saveBox); mapWindow.draw(saveRouteButton);
                        }
                        
                        routeList.drawRoutes(mapWindow, font, isModificable);
                        routeList.drawRoutesNames(mapWindow, font);

                        mapWindow.display();
                    }
                }
                if (exitBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(background);
        
        window.draw(titleBox);
        window.draw(title);
        
        window.draw(aboutBox);
        window.draw(aboutButton);
        
        window.draw(mapBox);
        window.draw(mapButton);
        
        window.draw(exitBox);
        window.draw(exitButton);
        
        window.display();
    }

    return 0;
}