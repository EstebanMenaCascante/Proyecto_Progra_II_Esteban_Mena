#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

void centerTextInRectangle(sf::Text& text, const sf::RectangleShape& rectangle) {
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect rectBounds = rectangle.getGlobalBounds();
    text.setPosition(
        rectBounds.left + (rectBounds.width / 2.f) - (textBounds.width / 2.f),
        rectBounds.top + (rectBounds.height / 2.f) - (textBounds.height / 2.f) - textBounds.top
    );
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1800, 1000), "Destinos Magicos");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.jpg"))
    {
        cout << "Error cargando la imagen de fondo" << endl;
        return -1;
    }

    sf::Sprite background(backgroundTexture);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        cout << "Error cargando la fuente" << endl;
        return -1;
    }

    sf::Text title("Destinos Magicos", font, 80);
    title.setFillColor(sf::Color::White);

    sf::RectangleShape titleBox(sf::Vector2f(800, 100));
    titleBox.setFillColor(sf::Color(0, 0, 0, 150)); 
    titleBox.setPosition((window.getSize().x - titleBox.getSize().x) / 2, 200);
    centerTextInRectangle(title, titleBox); 

    sf::Text aboutButton("Acerca de", font, 40);
    sf::Text mapButton("Mostrar Mapa", font, 40);
    sf::Text exitButton("Salir", font, 40);

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
                        float(aboutWindow.getSize().y) / backgroundTexture.getSize().y
                    );

                    sf::RectangleShape aboutTextBox(sf::Vector2f(900, 250));
                    aboutTextBox.setFillColor(sf::Color(0, 0, 0, 150));
                    aboutTextBox.setPosition(50, 75);

                    sf::Text projectInfo(
                        "II Proyecto de Programacion\n"
                        "Nombre de la Agencia: Destinos Magicos\n"
                        "Estudiante: Esteban Mena\n"
                        "Profesor: Hairol Romero", font, 25);
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
                        aboutWindow.display();

                    }
                }
                if (mapButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    window.close();
                    sf::RenderWindow mapWindow(sf::VideoMode(1800, 1000), "Mapa");
                    sf::Texture mapTexture;
                    if (!mapTexture.loadFromFile("LOTR_map.jpg"))
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
