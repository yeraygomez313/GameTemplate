#include <Gameplay/SimpleEnemy.h>
#include <SFML/Window/Keyboard.hpp>

bool SimpleEnemy::init(const SimpleEnemyDescriptor& SimpleEnemyDescriptor)
{
	m_speed = SimpleEnemyDescriptor.speed;
	m_bulletSpeed = SimpleEnemyDescriptor.bulletSpeed;
	m_bulletTexture = SimpleEnemyDescriptor.bulletTexture;
	m_bulletManager = SimpleEnemyDescriptor.bulletManager;

	m_direction = SimpleEnemyDescriptor.direction;
	m_enemyType = SimpleEnemyDescriptor.enemyType;


	m_sprite.setRotation(180.f);

	return Enemy::init(SimpleEnemyDescriptor);
}

void SimpleEnemy::update(float deltaMilliseconds)
{
	m_timeSinceLastShot += deltaMilliseconds;

	switch (m_enemyType)
	{
	case Type::MOVING_SHOOTER:
		m_position.x += (m_direction.x * m_speed.x * deltaMilliseconds);
		if (m_sprite.getPosition().x - m_sprite.getGlobalBounds().width <= 0)
			m_direction.x = 1.0f;
		else if (m_sprite.getPosition().x >= 1920.f)
			m_direction.x = -1.0f;
		break;

	case Type::STATIC_SHOOTER:
		break;

	case Type::TELEPORTER:
		m_timeSinceLastTeleport += deltaMilliseconds;
		if (m_timeSinceLastTeleport >= m_teleportCooldown)
		{
			m_timeSinceLastTeleport = 0.f;
			teleport();
		}
		break;
	}

	if (m_timeSinceLastShot >= m_shootCooldown)
	{
		m_timeSinceLastShot = 0.f;
		shoot();
	}

	Enemy::update(deltaMilliseconds);
}

void SimpleEnemy::shoot()
{
	m_bulletManager->spawnBullet({m_sprite.getPosition().x - 70, m_sprite.getPosition().y}, sf::Vector2f(0.f, 1.f), m_bulletTexture, 600.f, true);
}

void SimpleEnemy::teleport()
{
	float randomX = 100.f + static_cast<float>(std::rand() % 1720);
	float randomY = 100.f + static_cast<float>(std::rand() % 500);

	m_position = { randomX, randomY };
	m_sprite.setPosition(m_position);
}