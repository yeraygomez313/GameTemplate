#pragma once

#include <Core/BulletManager.h>
#include <Core/CollisionManager.h>
#include <Core/EnemyManager.h>
#include <Core/PowerUpManager.h>
#include <Core/SoundManager.h>
#include <cstdint>
#include <Gameplay/Bullet.h>
#include <Gameplay/PowerUp.h>
#include <Gameplay/SimpleEnemy.h>
#include <UI/UIManager.h>
#include <Utils/ObjectPool.h>
#include <vector>

class Enemy;
class Player;
class SimpleEnemy;

namespace sf
{
    class RenderWindow;
}

namespace tmx
{
    class Map;
}

class MapLayer;
class ObjectLayer;

class World
{
public:

    ~World();

    bool load();


    void update(uint32_t deltaMilliseconds);
    void render(sf::RenderWindow& window);

	void addScore(int score);
    

private:
    BulletManager m_bulletManager;
	EnemyManager m_enemyManager;
    CollisionManager* m_collisionManager;
	PowerUpManager m_powerUpManager;
	ObjectPool<SimpleEnemy, 6> m_simpleEnemyPool;
    SoundManager m_soundManager;

    bool m_isWaitingForStart = true;
	bool m_isGameOver = false;

    int m_totalEnemiesSpawned = 0;
    int m_wave = 0;
    bool m_hasSpawnedFinalWave = false;

    int m_score{ 0 };
	UIManager m_uiManager;
    size_t m_lastEnemyCount;

    int m_currentWaveSize = 2;
    float m_enemySpeedMultiplier = 1.0f;
    bool m_playerIsAlive = true;

	void spawnEnemies(int count);

    Enemy* m_enemy{ nullptr };
    Player* m_player{ nullptr };
	SimpleEnemy* m_simpleEnemy{ nullptr };

    std::vector<PowerUp> m_powerUps;
    sf::Texture* m_powerUpTextures[3];

    void spawnPowerUp();

    std::vector<Bullet*> m_bullets;

    tmx::Map* m_map{ nullptr };
    MapLayer* m_layerZero{ nullptr };
    MapLayer* m_layerOne{ nullptr };
    MapLayer* m_layerTwo{ nullptr };
    ObjectLayer* m_collisionLayer{ nullptr };
};
