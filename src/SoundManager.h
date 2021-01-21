#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

enum GameSound {EAT, DEATH};    // Type of sound to play

class SoundManager : public sf::Drawable
{
private:
	static const float sclOffset, volumePreset;
	static const char* eatFileName, *deathFileName, *soundTextureFile, *noSoundTextureFile;
	bool eatSoundLoaded = false, deathSoundLoaded = false, muted, disabled = false;
	sf::Texture soundTexture, noSoundTexture;
	sf::Sprite soundSprite;
	sf::SoundBuffer eatBuffer, deathBuffer;
	sf::Sound eatSound, deathSound;
public:
	SoundManager(unsigned int windowSize, unsigned int scale, bool mute = false);
	void toggle();
	void changeVolume(float &v);
	bool isClicked(sf::Vector2f &mouse) const;
	void play(GameSound s);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};