#pragma once
#include <SFML/Graphics.hpp>

class ScoreDisplay : public sf::Drawable
{
private:
	unsigned int score = 0;
	const unsigned int charSize;              // Text's character size based on window size and scale
	const char *fontFile = "resources/fonts/arial.ttf";
	const char *baseText = "Score: ";
	bool disabled = false;
	sf::Text scoreText;
	sf::Font font;

	void updateDisplay();
public:
	ScoreDisplay(unsigned int windowSize, unsigned int scale);

	void reset();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void operator ++(int);	
};