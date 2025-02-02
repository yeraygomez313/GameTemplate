#pragma once

#include <Core/SoundManager.h>
#include <Gameplay/Bullet.h>
#include <Utils/ObjectPool.h>
#include <vector>

class BulletManager
{
public:
    BulletManager() = default;

    void spawnBullet(const sf::Vector2f& position, const sf::Vector2f& direction, sf::Texture* texture, float speed, bool isFriendly);

    std::vector<Bullet*>& getBullets();

    void update(float deltaMilliseconds);

    void render(sf::RenderWindow& window);

    ObjectPool<Bullet, 50> m_bulletPool;

    void clearBullets();

    bool playSound = false;

private:

    std::vector<Bullet*> m_bullets;
};
