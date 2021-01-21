#include "Fruit.h"

// Generate a new pseudo random location (not uniformely distributed)
sf::Vector2f Fruit::randomizeLocation()
{
	// Location between 0 and windowSize - fruit size
	int range = constraints - SIZE + 1;
	return { (float)(rand() % range), (float)(rand() % range)};
}
Fruit::Fruit(unsigned int windowSize, unsigned int scale) : constraints(windowSize), SIZE(windowSize / scale)
{
	// Seed rand
	srand(time(NULL));
	// Radius of size (dependent on window size and render scale)
	fruitSprite = sf::CircleShape(SIZE / 2.0f);
	fruitSprite.setFillColor(sf::Color::Red);

	/*texture.loadFromFile("resources/sprites/apple.png");
	texture.setSmooth(true);
	fruitSprite.setTexture(texture);
	fruitSprite.setScale((SIZE + scale) / fruitSprite.getGlobalBounds().width, (SIZE + scale)/ fruitSprite.getGlobalBounds().height);*/
	// Pick a new random location
	fruitSprite.setPosition(randomizeLocation());
}
// Fruit position getter
sf::Vector2f Fruit::getPosition() const
{
	return fruitSprite.getPosition();
}
// Move the fruit after it's been eaten
void Fruit::relocate()
{
	fruitSprite.setPosition(randomizeLocation());
}
// Draw the fruit
void Fruit::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(fruitSprite);
}