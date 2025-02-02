#include <Core/SoundManager.h>
#include <iostream>

SoundManager* SoundManager::s_instance{ nullptr };

SoundManager::~SoundManager() {
	delete s_instance;
}

SoundManager* SoundManager::getInstance() {
	if (s_instance == nullptr) {
		std::cout << "SoundManager not instanced\n";
	}
	return s_instance;
}

bool SoundManager::init() {
	s_instance = this;

	m_buttonPressedBuffer = sf::SoundBuffer();
	m_buttonPressedBuffer.loadFromFile("../Data/Sounds/buttonPressed.wav");

	m_bulletBoostBuffer = sf::SoundBuffer();
	m_bulletBoostBuffer.loadFromFile("../Data/Sounds/bulletBoost.wav");

	m_deathBuffer = sf::SoundBuffer();
	m_deathBuffer.loadFromFile("../Data/Sounds/death.wav");

	m_gameOverBuffer = sf::SoundBuffer();
	m_gameOverBuffer.loadFromFile("../Data/Sounds/gameOver.wav");

	m_shieldBoostBuffer = sf::SoundBuffer();
	m_shieldBoostBuffer.loadFromFile("../Data/Sounds/shieldBoost.wav");

	m_shootBuffer = sf::SoundBuffer();
	m_shootBuffer.loadFromFile("../Data/Sounds/shoot.wav");

	m_speedBoostBuffer = sf::SoundBuffer();
	m_speedBoostBuffer.loadFromFile("../Data/Sounds/speedBoost.wav");

	m_startGameBuffer = sf::SoundBuffer();
	m_startGameBuffer.loadFromFile("../Data/Sounds/startGame.wav");

	return true;
}

void SoundManager::playSound(const sf::SoundBuffer& buffer) {
	// Clean up stopped sounds
	cleanupSounds();

	// Add a new sound to the list
	m_activeSounds.emplace_back(std::make_unique<sf::Sound>());

	// Set its buffer and play it
	m_activeSounds[m_activeSounds.size() - 1]->setBuffer(buffer);
	m_activeSounds[m_activeSounds.size() - 1]->setVolume(100.0f);
	m_activeSounds[m_activeSounds.size() - 1]->play();
}

void SoundManager::cleanupSounds() {
	
	m_activeSounds.erase(
		std::remove_if(
			m_activeSounds.begin(),
			m_activeSounds.end(),
			[](const std::unique_ptr<sf::Sound>& sound) {
				return sound->getStatus() == sf::Sound::Stopped;
			}
		),
		m_activeSounds.end()
	);
}
