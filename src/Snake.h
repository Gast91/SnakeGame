#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Direction Definitions
#define NORTH sf::Vector2f{ 0.0f, -1.0f }
#define SOUTH sf::Vector2f{ 0.0f, 1.0f }
#define WEST sf::Vector2f{ -1.0f, 0.0f }
#define EAST sf::Vector2f{ 1.0f, 0.0f }

class Snake : public sf::Drawable
{
private:
	const float SIZE;                    // Snake's model size (Rectangle size)

	int snakeLength = 0;                 // Length of Snake exluding its head - head is 0
	sf::Vector2f direction;              // Direction of movement 
	unsigned int constraints;            // Snake's Constraints (Window Size)

	mutable sf::RectangleShape model;    // Snake's geometry / graphics 
	std::vector<sf::Vector2f> snakeBody = std::vector<sf::Vector2f>(50);   // Snake's previous head positions
public:
	Snake(unsigned int windowSize, unsigned int scale, sf::Vector2f dir = EAST);

	bool isDead(bool(*distance)(sf::Vector2f, sf::Vector2f, float));
	sf::Vector2f getPosition() const;
	void changeDirection(sf::Vector2f &dir);

	void grow();
	void update();
	void reset();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};