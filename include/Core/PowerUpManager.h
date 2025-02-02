#pragma once

#include <Gameplay/PowerUp.h>
#include <Utils/ObjectPool.h>
#include <vector>

class PowerUpManager {
public:
    PowerUpManager() = default;

    void spawnPowerUp(const sf::Vector2f& position, PowerUp::Type type, sf::Texture* texture);
    std::vector<PowerUp*>& getPowerUps();
    void update(float deltaMilliseconds);
    void render(sf::RenderWindow& window);

    ObjectPool<PowerUp, 10> m_powerUpPool;

    void clearPowerUps();

private:
    std::vector<PowerUp*> m_powerUps;
};
