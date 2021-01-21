#include "SoundManager.h"

const float SoundManager::sclOffset = 10.0f;
const float SoundManager::volumePreset = 20.0f;
const char* SoundManager::eatFileName = "resources/sounds/eat.wav";
const char* SoundManager::deathFileName = "resources/sounds/hiss.wav";
const char* SoundManager::soundTextureFile = "resources/sprites/sound.png";
const char* SoundManager::noSoundTextureFile = "resources/sprites/noSound.png";

SoundManager::SoundManager(unsigned int windowSize, unsigned int scale, bool mute) : muted(mute)
{
	// Try to load the sound files, disable the ones that cannot be loaded
	if (eatBuffer.loadFromFile(eatFileName))
	{ 
		eatSoundLoaded = true;
		eatSound.setBuffer(eatBuffer);
	}	
	if (deathBuffer.loadFromFile(deathFileName))
	{
		deathSoundLoaded = true;
		deathSound.setBuffer(deathBuffer);
	}
	// Set volume preset for both sounds
	eatSound.setVolume(volumePreset);
	deathSound.setVolume(volumePreset);
	// Load Textures - Disable them if one or both do not exist
	if (!soundTexture.loadFromFile(soundTextureFile) || !noSoundTexture.loadFromFile(noSoundTextureFile))
	{
		disabled = true;
		return;
	}
	// Set appropriate sound texture
	muted ? soundSprite.setTexture(noSoundTexture) : soundSprite.setTexture(soundTexture);
	// setScale(NewSize / Old Size) == setSize(NewSize)
	// Scale the sprite to be "scale" times smaller than the window size + an offset
	soundSprite.setScale((windowSize / scale + sclOffset) / soundSprite.getGlobalBounds().width, (windowSize / scale + sclOffset) / soundSprite.getGlobalBounds().height);
	// Anchor the sprite to the bottom right of the screen
	soundSprite.setPosition(windowSize - soundSprite.getGlobalBounds().width, windowSize - soundSprite.getGlobalBounds().height );
}
// Toggle sound on and off and update sound sprites
void SoundManager::toggle()
{
	if (!disabled)
		muted ? soundSprite.setTexture(soundTexture) : soundSprite.setTexture(noSoundTexture);
	muted = !muted;
}
// Increase/Decrease the volume according to the mouse wheel scroll
void SoundManager::changeVolume(float &v)
{
	// std::clamp!!
	float newVolume = eatSound.getVolume() + v;
	// Capped at 100 or 0
	if (newVolume > 100.0f)
		newVolume = 100.0f;
	else if (newVolume < 0.0f)
		newVolume = 0.0f;
	// Update volume for both sounds
	eatSound.setVolume(newVolume);
	deathSound.setVolume(newVolume);
	// Update textures if its not muted but sound volume is 0'
	if ((!muted && newVolume == 0.0f) || (muted && newVolume > 0.0f))    
		toggle();
}
// Checks if mouse position is within the bound of the sprite
bool SoundManager::isClicked(sf::Vector2f &mouse) const
{
	if (disabled) return false;
	sf::FloatRect bounds = soundSprite.getGlobalBounds();
	return bounds.contains(mouse);
}
// Play the designated sound
void SoundManager::play(GameSound s)
{
	if (!muted)
	{
		if (s == EAT && eatSoundLoaded)
			eatSound.play();
		else if (s == DEATH && deathSoundLoaded)
			deathSound.play();
	}
}
// Draw the sprite
void SoundManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (!disabled) target.draw(soundSprite);
}