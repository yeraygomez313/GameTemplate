#include <Core/PowerUpManager.h>
#include <SFML/Graphics/RenderWindow.hpp>

void PowerUpManager::spawnPowerUp(const sf::Vector2f& position, PowerUp::Type type, sf::Texture* texture) {
    PowerUp::PowerUpDescriptor descriptor;
    descriptor.position = position;
    descriptor.texture = texture;
    descriptor.type = type;

    PowerUp& powerUp = m_powerUpPool.get();
    powerUp.init(descriptor);
    m_powerUps.push_back(&powerUp);
}

std::vector<PowerUp*>& PowerUpManager::getPowerUps() {
    return m_powerUps;
}

void PowerUpManager::update(float deltaMilliseconds) {
}

void PowerUpManager::render(sf::RenderWindow& window) {
    for (auto& powerUp : m_powerUps) {
        powerUp->render(window);
    }
}

void PowerUpManager::clearPowerUps()
{
    for (auto* powerUp : m_powerUps)
    {
        if (powerUp)
        {
            m_powerUpPool.release(*powerUp);
        }
    }

    m_powerUps.clear();
}