#ifndef STAR_H
#define STAR_H

	#include <SFML/Graphics.hpp>

	class Star
	{
		public:
			Star(sf::Vector2f position, sf::Vector2f velocity, double mass);
			Star();
			
			void update(double elapsedTime, std::vector<Star>& stars, double gravitationalConstant, int starID);
			void draw(sf::RenderWindow* targetWindow);
		
		private:
			sf::Vector2f position;
			sf::Vector2f velocity;
			double mass;
			sf::Vertex point;
	};

#endif