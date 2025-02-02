#pragma once

#include <map>
#include <memory>
#include <SFML/Audio.hpp>
#include <vector>


class SoundManager
{
	public:
		static SoundManager* getInstance();

		~SoundManager();

		bool init();

		void playButtonPressedSound() { playSound(m_buttonPressedBuffer); }
		void bulletBoostSound() { playSound(m_bulletBoostBuffer); }
		void deathSound() { playSound(m_deathBuffer); }
		void gameOverSound() { playSound(m_gameOverBuffer); }
		void shieldBoostSound() { playSound(m_shieldBoostBuffer); }
		void shootSound() { playSound(m_shootBuffer); }
		void speedBoostSound() { playSound(m_speedBoostBuffer); }
		void startGameSound() { playSound(m_startGameBuffer); }

	private:
		static SoundManager* s_instance;

		sf::SoundBuffer m_buttonPressedBuffer;
		sf::SoundBuffer m_bulletBoostBuffer;
		sf::SoundBuffer m_deathBuffer;
		sf::SoundBuffer m_gameOverBuffer;
		sf::SoundBuffer m_shieldBoostBuffer;
		sf::SoundBuffer m_shootBuffer;
		sf::SoundBuffer m_speedBoostBuffer;
		sf::SoundBuffer m_startGameBuffer;

		std::vector<std::unique_ptr<sf::Sound>> m_activeSounds;

		void playSound(const sf::SoundBuffer& buffer);

		void cleanupSounds();
};