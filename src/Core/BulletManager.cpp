#include <Core/BulletManager.h>
#include <SFML/Graphics/RenderWindow.hpp>

void BulletManager::spawnBullet(const sf::Vector2f& position, const sf::Vector2f& direction, sf::Texture* texture, float speed, bool isFriendly)
{
    Bullet::BulletDescriptor bulletDescriptor;
    bulletDescriptor.position = position;
    bulletDescriptor.direction = direction;
    bulletDescriptor.texture = texture;
    bulletDescriptor.speed = speed;
	bulletDescriptor.isFriendly = isFriendly;
	

    Bullet& bullet = m_bulletPool.get();
    bullet.init(bulletDescriptor);

    m_bullets.push_back(&bullet);
    playSound = true;
}

std::vector<Bullet*>& BulletManager::getBullets()
{
    return m_bullets;
}

void BulletManager::update(float deltaMilliseconds)
{

    for (auto bullet = m_bullets.begin(); bullet != m_bullets.end(); )
    {
        (*bullet)->update(deltaMilliseconds);
        if ((*bullet)->isOutOfBounds())
        {
            m_bulletPool.release(**bullet);
            bullet = m_bullets.erase(bullet);
        }
        else
        {
            ++bullet;
        }
    }
}

void BulletManager::render(sf::RenderWindow& window)
{
    for (auto& bullet : m_bullets)
    {
		bullet->render(window);
    }
}

void BulletManager::clearBullets()
{
    for (auto* bullet : m_bullets)
    {
        if (bullet)
        {
            m_bulletPool.release(*bullet);
        }
    }

    m_bullets.clear();
}