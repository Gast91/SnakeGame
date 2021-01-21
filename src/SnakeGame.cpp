#include "Snake.h"
#include "Fruit.h"
#include "ScoreDisplay.h"
#include "SoundManager.h"

unsigned int WINDOW_SIZE = 400;        // Window dimensions (Window is always square)
const unsigned int SCALE = 20;         // Rendered objects are "SCALE" times smaller than "WINDOW_SIZE"

// Movement Keys - General Controls
const sf::Keyboard::Key UP = sf::Keyboard::W;
const sf::Keyboard::Key DOWN = sf::Keyboard::S;
const sf::Keyboard::Key LEFT = sf::Keyboard::A;
const sf::Keyboard::Key RIGHT = sf::Keyboard::D;
const sf::Keyboard::Key ESC = sf::Keyboard::Escape;
const sf::Keyboard::Key MUTE = sf::Keyboard::M;
const sf::Mouse::Button CLICK = sf::Mouse::Button::Left;

inline bool calcDistance(sf::Vector2f f1, sf::Vector2f f2, float radius)
{
	return (f1.x - f2.x) * (f1.x - f2.x) + (f1.y - f2.y) * (f1.y - f2.y) < radius * radius;
}

int main(int argc, char *argv[])
{
	if (argc == 2)   // path and size of window are the only acceptable parameters, ignore if there are more
	{
		int parseArgs = atoi(argv[argc - 1]);                          // Parse window size as an int
		if (!(!parseArgs || parseArgs <= 0)) WINDOW_SIZE = parseArgs;  // Assign new window size only if it's an int and it's not negative
	}
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Snake Game", sf::Style::Close);
	sf::Event event;
	// If iconImg exists load it as the title bar's icon
	sf::Image iconImg;
	if (iconImg.loadFromFile("resources/sprites/snakeIcon.png"))
		window.setIcon(30, 30, iconImg.getPixelsPtr());

	window.setFramerateLimit(10);

	Snake snake(WINDOW_SIZE, SCALE);
	Fruit fruit(WINDOW_SIZE, SCALE);
	ScoreDisplay scoreDisplay(WINDOW_SIZE, SCALE);
	SoundManager sound(WINDOW_SIZE, SCALE, true);

	while (window.isOpen())
	{	
		if (!window.hasFocus()) continue;
		window.clear();
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case ESC:
					window.close();
					break;
				case UP:
					snake.changeDirection(NORTH);
					break;
				case DOWN:
					snake.changeDirection(SOUTH);
					break;
				case LEFT:
					snake.changeDirection(WEST);
					break;
				case RIGHT:
					snake.changeDirection(EAST);
					break;
				case MUTE:
					sound.toggle();
					break;
				default:
					break;
				}
				break;
			case sf::Event::MouseWheelScrolled:
				sound.changeVolume(event.mouseWheelScroll.delta);
				break;
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(CLICK) && sound.isClicked(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					sound.toggle();
				break;
			default:
				break;
			}
		}
		
		snake.update();

		if (snake.isDead(calcDistance))
		{
			sound.play(DEATH);
			snake.reset();
			scoreDisplay.reset();
		}
		else if (calcDistance(snake.getPosition(), fruit.getPosition(), WINDOW_SIZE / SCALE))
		{
			sound.play(EAT);
			fruit.relocate();
			snake.grow();
			scoreDisplay++;
		}
		window.draw(sound);
		window.draw(snake);
		window.draw(fruit);
		window.draw(scoreDisplay);
		window.display();
	}
	return 0;
}

//TODO: Sfml Textures - Sprites                  -- BONUS
//TODO: Use Iterators?                           -- MAYBE