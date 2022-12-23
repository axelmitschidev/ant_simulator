#include <list>
#include <vector>
#include <iostream>
#include <random>

#include "constants.hpp"
#include "Ant.hpp"
#include "Food.hpp"
#include "AntHill.hpp"

int main()
{
    std::mt19937 generator(time(nullptr));
    std::uniform_real_distribution<double> distributionFood(-20, 20);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ant Simulator");
    window.setFramerateLimit(60);

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
    AntHill anthill(-200, -200);

    std::vector<Ant> ants;

    std::list<Pheromone> pheromones;

    std::list<Food> foods;

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
                        pheromones.push_back(Pheromone(mousePos.x - 6, mousePos.y - 6, -1, 'h'));
                    }
                    if (event.key.code == sf::Keyboard::F) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        for (size_t i = 0; i < 10; i++) {
                            foods.push_back(Food((mousePos.x - 6) + distributionFood(generator), (mousePos.y - 6) + distributionFood(generator)));
                        }
                    }
                    if (event.key.code == sf::Keyboard::H) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        for (size_t i = 0; i < POPULATION; i++) {
                            anthill = AntHill(mousePos.x-100, mousePos.y-100);
                            ants.push_back(Ant(mousePos.x, mousePos.y, i));
                        }
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
        pheromones.remove(Pheromone(0, 0, -1, 'f'));
        for (size_t i = 0; i < ants.size(); i++) ants[i].update(&pheromones, &foods, &anthill);

        //draw
        window.clear(sf::Color::White);
        for (auto it = pheromones.begin(); it != pheromones.end(); ++it) it->draw(window);
        for (size_t i = 0; i < ants.size(); i++) ants[i].draw(window);
        for (auto it = foods.begin(); it != foods.end(); ++it) it->draw(window);
        anthill.draw(window);
        window.draw(fpsText);
        window.display();
    }
    
    return 0;
}
