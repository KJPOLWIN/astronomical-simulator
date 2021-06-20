#include "star.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <random>
#include <ctime>

int main()
{
	std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	
	
    sf::RenderWindow window(sf::VideoMode(800, 600), "Astronomical simulator");
	window.setFramerateLimit(60);
	
	
	constexpr double gravitationalConstant{ 1000.0 };
	int starNumber{ 25 };
	
	
	double minMass{ 1 };
	double maxMass{ 10 };
	
	std::uniform_real_distribution randomMass{ minMass, maxMass };
	
	double minVelocity{ -0.3 };
	double maxVelocity{ 0.3 };
	
	std::uniform_real_distribution randomVelocity{ minVelocity, maxVelocity };
	
	std::uniform_real_distribution randomX{ 0.0, 800.0 };
	std::uniform_real_distribution randomY{ 0.0, 600.0 };
	
	auto stars{ std::vector<Star>() };
	
	for(int iii{ 0 }; iii < starNumber; ++iii)
	{
		stars.push_back( Star(sf::Vector2f(randomX(mersenne), randomY(mersenne)), 
							  sf::Vector2f(randomVelocity(mersenne), randomVelocity(mersenne)), 
							  randomMass(mersenne)) );
	}

	sf::Clock clock{ sf::Clock() };
	double elapsedTime{ 0.0 };

	sf::Event event;

    while (window.isOpen())
    {
		elapsedTime = clock.restart().asSeconds();
		
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
		
		int id{ 0 };
		for( auto& star : stars )
		{
			star.update(elapsedTime, stars, gravitationalConstant, id);
			++id;
		}
		
		window.clear();
		
		for( auto& star : stars )
		{
			star.draw(&window);
		}
		
		window.display();
    }

    return 0;
}