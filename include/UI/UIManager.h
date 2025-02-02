#pragma once
#include <SFML/Graphics.hpp>

class UIManager
{
public:
    UIManager();

    bool init();

    void updateScore(int score);

    void updateStartMessage(const std::string& message);

    void render(sf::RenderWindow& window);

    void resetUIManager();

	bool m_mainMenu = true;
	bool m_gameOver = false;

private:
    sf::Font m_font;
    sf::Text m_scoreText;
    sf::Text m_startMessage;
    sf::Texture m_alienTexture;
    sf::Sprite m_alienSprite;
    sf::Texture m_shipTexture;
    sf::Sprite m_shipSprite;
};
