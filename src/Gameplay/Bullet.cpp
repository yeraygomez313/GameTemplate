#include <Gameplay/Bullet.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

bool Bullet::init(const BulletDescriptor& bulletDescriptor)
{
    if (bulletDescriptor.texture)
    {
        m_sprite.setTexture(*bulletDescriptor.texture);
        m_sprite.setScale(0.2f, 0.2f);
    }
    else
    {
        return false;
    }

    m_position = bulletDescriptor.position;
    m_direction = bulletDescriptor.direction;
    m_speed = bulletDescriptor.speed;
    m_sprite.setPosition(m_position);
	m_isFriendly = bulletDescriptor.isFriendly;
    return true;
}

void Bullet::update(float deltaMilliseconds)
{
    m_position += m_direction * (m_speed * 1 / 1000.f) * deltaMilliseconds;
    m_sprite.setPosition(m_position);
}

void Bullet::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);

    const sf::FloatRect spriteBounds = m_sprite.getGlobalBounds();
}

bool Bullet::isOutOfBounds() const
{
    return m_position.y < 0 || m_position.x > 1920 || m_position.y < 0 || m_position.y > 1080;
}
