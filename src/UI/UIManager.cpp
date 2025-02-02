#include "UI/UIManager.h"
#include <iostream>

UIManager::UIManager()
{
}

bool UIManager::init()
{
    if (!m_font.loadFromFile("../data/Fonts/8bit16.ttf"))
    {
        std::cerr << "Error al cargar la fuente!" << std::endl;
        return false;
    }

    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(30);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition(50.f, 10.f);
    m_scoreText.setString("Score: 0");

    m_startMessage.setFont(m_font);
    m_startMessage.setCharacterSize(50);
    m_startMessage.setFillColor(sf::Color::White);
    m_startMessage.setPosition(600.f, 400.f);
    m_startMessage.setString("");

    if (!m_alienTexture.loadFromFile("../data/Images/Enemies/alien.png"))
    {
        std::cerr << "Error al cargar la imagen!" << std::endl;
        return false;
    }

    m_alienSprite.setTexture(m_alienTexture);
    m_alienSprite.setPosition(10.f, 10.f);
	m_alienSprite.setScale(.6f, .6f);

    if (!m_shipTexture.loadFromFile("../data/Images/Enemies/ship.png"))
    {
        std::cerr << "Error al cargar la segunda imagen!" << std::endl;
        return false;
    }

    m_shipSprite.setTexture(m_shipTexture);
    m_shipSprite.setPosition(300.f, 700.f);

    return true;
}

void UIManager::updateScore(int score)
{
    m_scoreText.setString("Score: " + std::to_string(score));
}

void UIManager::updateStartMessage(const std::string& message)
{
    m_startMessage.setString(message);
}

void UIManager::render(sf::RenderWindow& window)
{
    if (m_mainMenu)
    {
        window.draw(m_startMessage);
        window.draw(m_alienSprite);

        window.draw(m_shipSprite);
    }
	else if (m_gameOver)
	{
		window.draw(m_startMessage);
	}
    else
    {
        window.draw(m_scoreText);
    }
}

void UIManager::resetUIManager() {
    m_mainMenu = true;
    m_gameOver = false;
    m_scoreText.setString("Score: " + std::to_string(0));
}
