#include "ScoreDisplay.h"

ScoreDisplay::ScoreDisplay(unsigned int windowSize, unsigned int scale) : charSize( windowSize / scale)
{
	// Try to load the font, disable score display if it cannot be loaded
	if (!font.loadFromFile((fontFile)))
	{
		disabled = true;
		return;
	}
	// Set font
	scoreText.setFont(font);
	// Character size if dependent on window size and scale
	scoreText.setCharacterSize(charSize);
	// Anchored to the top left
	scoreText.setPosition(0.0f, 0.0f);
	// Update score text to base text + current score
	updateDisplay();
}
// Update score text to base text + current score
void ScoreDisplay::updateDisplay()
{
	if (!disabled) scoreText.setString(baseText + std::to_string(score));
}
// Resets score
void ScoreDisplay::reset()
{ 
	score = 0; 
	updateDisplay();
}
// Draw the text on the screen
void ScoreDisplay::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (!disabled) target.draw(scoreText);
}
// Operator ++ overload
void ScoreDisplay::operator ++(int)
{
	score++;
	updateDisplay();
}