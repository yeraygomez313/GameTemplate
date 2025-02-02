#include <Core/World.h>
#include <Gameplay/Player.h>
#include <SFML/Graphics/RenderWindow.hpp>

bool Player::init(const PlayerDescriptor& playerDescriptor)
{
    m_position = playerDescriptor.position;
    m_speed = playerDescriptor.speed;
    m_bulletSpeed = playerDescriptor.bulletSpeed;
    m_bulletTexture = playerDescriptor.bulletTexture;

    if (playerDescriptor.texture)
    {
        m_sprite.setTexture(*playerDescriptor.texture);
        m_sprite.setScale(.5f, .5f);
    }
    else
    {
        return false;
    }
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.f, m_sprite.getLocalBounds().height / 2.f);

    m_sprite.setPosition(m_position);
    return true;
}

void Player::update(float deltaMilliseconds)
{
    m_direction = { 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        m_direction.y = -1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_direction.y = 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_direction.x = -1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_direction.x = 1.f;

    if (m_direction.x != 0.f && m_direction.y != 0.f)
        m_direction *= 0.7071f;

    m_position += m_direction * m_speed * deltaMilliseconds;

    const float windowWidth = 1920.f;
    const float windowHeight = 1080.f;

    float halfWidth = m_sprite.getGlobalBounds().width / 2.f;
    float halfHeight = m_sprite.getGlobalBounds().height / 2.f;

    m_position.x = std::clamp(m_position.x, halfWidth, windowWidth - halfWidth);
    m_position.y = std::clamp(m_position.y, halfHeight, windowHeight - halfHeight);

    m_sprite.setPosition(m_position);
    if (m_isShieldActive)
    {
        m_shieldTimeLeft -= deltaMilliseconds;
        if (m_shieldTimeLeft <= 0.f)
        {
            m_isShieldActive = false;
        }
    }

    m_timeSinceLastShot += deltaMilliseconds;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_timeSinceLastShot >= m_shootCooldown)
    {
        m_timeSinceLastShot = 0.f;
        shoot();
    }
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Player::shoot()
{
    m_bulletManager.spawnBullet({ m_sprite.getPosition().x - 30,  (m_sprite.getPosition().y - 90) }, sf::Vector2f(0.f, -1.f), m_bulletTexture, m_bulletSpeed, false);
}

void Player::increaseSpeed(float amount)
{
    m_speed += amount;
}

void Player::increaseBulletSpeed(float amount)
{
    m_bulletSpeed += amount;
}

void Player::activateShield(float duration)
{
    m_isShieldActive = true;
    m_shieldTimeLeft = duration;
}

void Player::resetToInitialState()
{
    m_position = { 900.f, 900.f };
    m_sprite.setPosition(m_position);
    m_speed = 300.f * 1 / 1000.f;
    m_bulletSpeed = 300.f;
    m_isShieldActive = false;
    m_shieldTimeLeft = 0.f;
	m_hasToBeDestroyed = false;
}
