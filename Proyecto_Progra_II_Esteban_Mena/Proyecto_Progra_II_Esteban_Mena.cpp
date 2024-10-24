#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

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


    Text aboutButton("Acerca de", font2, 40);
    Text mapButton("Mostrar Mapa", font2, 40);
    Text exitButton("Salir", font2, 40);
    Text returnButton("Regresar", font2, 20);
    Text returnAboutButton("Regresar", font2, 40);


    returnButton.setFillColor(Color::Black);

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

    sf::Music music;
    if (!music.openFromFile("The Hobbit_LOTR_Sound_of_The_Shire.ogg")) {
        cerr << "Error al cargar la música\n";
        return -1;
    }

    music.setVolume(30.0f);
    music.setLoop(true);
    music.play();

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
                if (aboutButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
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

                        //sf::Event event;
                        while (aboutWindow.pollEvent(event)) {

                            if (event.type == sf::Event::Closed)
                                window.close();
                            if (event.type == sf::Event::MouseButtonPressed) {
                                
                                sf::Vector2i mousePos = sf::Mouse::getPosition(aboutWindow);

                                if (returnAboutButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                    aboutWindow.close();
                                }

                            }
                        
                        }

                       
                        aboutWindow.display();

                    }
                }
                if (mapButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {

                    sf::RenderWindow mapWindow(sf::VideoMode(1800, 1000), "Mapa");
                    sf::Texture mapTexture;
                    if (!mapTexture.loadFromFile("images/LOTR_map3.jpg"))
                    {
                        cout << "Error cargando el mapa" << endl;
                        return -1;
                    }
                    sf::Sprite mapSprite(mapTexture);
                    while (mapWindow.isOpen())
                    {
                        sf::Event mapEvent;
                        while (mapWindow.pollEvent(mapEvent))
                        {
                            if (mapEvent.type == sf::Event::Closed)
                                mapWindow.close();
                        }
                        mapWindow.clear();
                        mapWindow.draw(mapSprite);
                        mapWindow.draw(returnBox);
                        mapWindow.draw(returnButton);
                        mapWindow.display();
                    }
                }
                if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
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
