#include <list>
#include <vector>
#include <iostream>

#include "constants.hpp"
#include "Ant.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ant Simulator");
    window.setFramerateLimit(160);

    sf::Font font;
    if (!font.loadFromFile("resources/fonts/arial.ttf")) {
        std::cerr << "Error loading font file" << std::endl;
        return 1;
    }

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::Black);

    sf::Clock clock;
    sf::Event event;

    std::vector<Ant> ants;
    for (size_t i = 0; i < POPULATION; i++) ants.push_back(Ant(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, i));

    std::list<Pheromone> pheromones;

    while (window.isOpen())
    {
        //event
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed :
                    window.close();
                    break;
                
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) window.close();
                    if (event.key.code == sf::Keyboard::A) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        pheromones.push_back(Pheromone(mousePos.x - 6, mousePos.y - 6, 0));
                    }
                    break;

                default:
                    break;
            }
        }

        //update
        fpsText.setString(std::to_string(static_cast<int>(1.0f / clock.restart().asSeconds())) + " FPS");
        for (auto it = pheromones.begin(); it != pheromones.end(); ++it) {
            it->update();
        };
        pheromones.remove(Pheromone(0, 0, -1));
        for (size_t i = 0; i < ants.size(); i++) ants[i].update(&pheromones);

        //draw
        window.clear(sf::Color::White);
        window.draw(fpsText);
        for (size_t i = 0; i < ants.size(); i++) ants[i].draw(window);
        for (auto it = pheromones.begin(); it != pheromones.end(); ++it) it->draw(window);
        window.display();
    }
    
    return 0;
}
