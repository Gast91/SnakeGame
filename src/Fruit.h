#pragma once
#include <SFML/Graphics.hpp>

class Fruit : public sf::Drawable
{
private:
	const float SIZE;                // Diameter of fruit based on the window size / scale
	unsigned int constraints;        // Fruit constraints (window size)

	//sf::Sprite fruitSprite;
	//sf::Texture texture;
	sf::CircleShape fruitSprite;     // Fruit's geometry / graphics
	sf::Vector2f randomizeLocation();
public:
	Fruit(unsigned int windowSize, unsigned int scale);

	sf::Vector2f getPosition() const;
	void relocate();
	
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};