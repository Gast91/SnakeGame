#include "Snake.h"

// Default Constructor - Params: Window size, scale in terms of window size and starting direction (optional)
Snake::Snake(unsigned int windowSize, unsigned int scale, sf::Vector2f dir) : constraints(windowSize), direction(dir), SIZE(windowSize / scale)
{
	snakeBody[0] = { windowSize / 2.0f, windowSize / 2.0f };
	model.setSize({ SIZE, SIZE });
	model.setFillColor(sf::Color::White);
}
// Checks if the snake head has hit the edge of the screen or a body part
bool Snake::isDead(bool (*distance)(sf::Vector2f, sf::Vector2f, float))
{
	if (snakeLength > 0)  // If body parts exist check if head is colliding with them
	{
		for (int i = 1; i < snakeLength; i++)
		{
			if (distance(snakeBody.front(), snakeBody.at(i), SIZE))
				return true;
		}
	}
	// Check if out of bounds (window size)
	return (snakeBody.front().x < 0.0f || snakeBody.front().x > constraints - SIZE ||
			snakeBody.front().y < 0.0f || snakeBody.front().y > constraints - SIZE);
}
// Returns the current world position of the head
sf::Vector2f Snake::getPosition() const
{
	return snakeBody.front();
}
// Changes the direction of the snake head if the head is not already going along that axis
void Snake::changeDirection(sf::Vector2f &dir)
{
	if ((dir == NORTH  || dir == SOUTH) && direction.y == 0.0f)       // If not already moving vertically
		direction = dir;
	else if ((dir == WEST || dir == EAST) && direction.x == 0.0f)     // If not already moving horizontally
		direction = dir;
}
// Increases snake's length and updates the position of the new segment
void Snake::grow()
{
	snakeLength++;
	if (snakeLength >= snakeBody.size()) snakeBody.resize(snakeBody.size() + 50);
	snakeBody[snakeLength] = snakeBody[snakeLength - 1];
}
// Updates the positions of the snake's segments and moves the head
void Snake::update()
{	
	// Every snake segment apart from the head, gets the position of its predecessor
	for (int i = snakeLength; i > 0; i--)
		snakeBody[i] = snakeBody[i - 1];
	// Move the snake head by it's size in a certain direction
	snakeBody.front() += (SIZE * direction);
}
// Resets the snake to it's initial state
void Snake::reset()
{
	snakeLength = 0;
	snakeBody[0] = { constraints / 2.0f, constraints / 2.0f };  // Back to the middle
	direction = EAST;
}
// Draws the snake model
void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (int i = 0; i <= snakeLength; i++)
	{
		// Model represents this segment now
		model.setPosition(snakeBody.at(i));
		target.draw(model);
	}
}