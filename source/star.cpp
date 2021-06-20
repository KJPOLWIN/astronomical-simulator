#include <SFML/Graphics.hpp>
#include "star.h"
#include <cmath>

	#include <iostream>

Star::Star(sf::Vector2f position, sf::Vector2f velocity, double mass)
	: position{ position },
	  velocity{ velocity },
	  mass{ mass },
	  point{ sf::Vertex(position, sf::Color::White) }
{
	
}

Star::Star()
	: position{ sf::Vector2f(0.0f, 0.0f) },
	  velocity{ sf::Vector2f(0.0f, 0.0f) },
	  mass{ 0.0 },
	  point{ sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::White) }
{
	
}

void Star::update(double elapsedTime, std::vector<Star>& stars, double gravitationalConstant, int starID)
{
	sf::Vector2f delta{ sf::Vector2f() };
	double distance{ 0.0 };
	double force{ 0.0 };
	
	int id{ 0 };
	for( auto& star : stars )
	{
		if(id != starID)
		{
			delta = sf::Vector2f(star.position.x - position.x, star.position.y - position.y);
			distance = sqrt(delta.x * delta.x + delta.y * delta.y);
			force = (gravitationalConstant * mass * star.mass) / (distance * distance);
		
			velocity.x += ((delta.x / distance) * force) / mass * elapsedTime;
			velocity.y += ((delta.y / distance) * force) / mass * elapsedTime;
		
			std::cout << "force: " << force << "\n";
			std::cout << "distance: " << distance << "\n";
		}
		++id;
	}
	
	position += velocity;
	point.position = position;
}

void Star::draw(sf::RenderWindow* targetWindow)
{
	targetWindow->draw(&point, 1, sf::Points);
}