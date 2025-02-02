#pragma once

#include <Core/BulletManager.h>
#include <Gameplay/Enemy.h>


class SimpleEnemy : public Enemy
{
public:

	enum class Type
	{
		MOVING_SHOOTER,
		STATIC_SHOOTER,
		TELEPORTER
	};

	struct SimpleEnemyDescriptor : EnemyDescriptor
	{
		sf::Vector2f speed{ 0.f, .0f };
		sf::Texture* bulletTexture{ nullptr };
		float bulletSpeed{ 300.f };
		BulletManager* bulletManager{ nullptr };
		sf::Vector2f direction{ 0.f, .0f };
		Type enemyType{ Type::MOVING_SHOOTER };
	};

	bool init(const SimpleEnemyDescriptor& enemyDescriptor);

	void update(float deltaMilliseconds) override;


private:

	void shoot();
	void teleport();

	sf::Texture* m_bulletTexture{ nullptr };
    float m_bulletSpeed{ 300.f };

	BulletManager* m_bulletManager{ nullptr };


	sf::Vector2f m_direction{ .0f, .0f };
	sf::Vector2f m_speed{ .0f, .0f };

	float m_shootCooldown{ 5000.f };
	float m_timeSinceLastShot{ 0.f };

	Type m_enemyType{ Type::MOVING_SHOOTER };
	float m_teleportCooldown{ 3000.f };
	float m_timeSinceLastTeleport{ 0.f };
};