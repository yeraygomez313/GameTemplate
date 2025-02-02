#include <Core/AssetManager.h>
#include <Core/BulletManager.h>
#include <Core/World.h>
#include <cstdlib>
#include <ctime>
#include <Gameplay/Player.h>
#include <Gameplay/SimpleEnemy.h>
#include <Render/SFMLOrthogonalLayer.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <tmxlite/Map.hpp>
#include <vector>


World::~World()
{
	m_simpleEnemyPool.release(*m_simpleEnemy);

    delete m_enemy;
    delete m_layerZero;
    delete m_layerOne;
    delete m_layerTwo;
    delete m_map;
    delete m_player;
    delete m_simpleEnemy;
	delete m_collisionManager;
}

void World::spawnEnemies(int count)
{
    constexpr float millisecondsToSeconds = 1 / 1000.f;
    sf::Texture* bulletTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Bullet/bullet.png");
    sf::Texture* simpleEnemyTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/simpleenemy.png");
    sf::Texture* simpleEnemyNoMovementTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/simpleenemyNoMovement.png");
    sf::Texture* simpleEnemyTeleportTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/simpleenemyTeleportation.png");

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < count; ++i)
    {
        SimpleEnemy::SimpleEnemyDescriptor simpleEnemyDescriptor;
        float randomX = 100.f + static_cast<float>(std::rand() % 1720);
        simpleEnemyDescriptor.position = { randomX, (150.f + (i * 100)) };

        int randomType = std::rand() % 3;
        switch (randomType)
        {
        case 0:
            simpleEnemyDescriptor.texture = simpleEnemyTexture;
            simpleEnemyDescriptor.enemyType = SimpleEnemy::Type::MOVING_SHOOTER;
            simpleEnemyDescriptor.speed = { 150.f * millisecondsToSeconds * m_enemySpeedMultiplier, 0.f };
            simpleEnemyDescriptor.direction = { (std::rand() % 2 == 0) ? -1.0f : 1.0f, 0.f };
            simpleEnemyDescriptor.tileWidth = 80.f;
            simpleEnemyDescriptor.tileHeight = 80.f;
            break;
        case 1:
            simpleEnemyDescriptor.texture = simpleEnemyNoMovementTexture;
            simpleEnemyDescriptor.enemyType = SimpleEnemy::Type::STATIC_SHOOTER;
            simpleEnemyDescriptor.speed = { 0.f, 0.f };
            simpleEnemyDescriptor.direction = { 0.f, 0.f };
            simpleEnemyDescriptor.tileWidth = 128.f;
            simpleEnemyDescriptor.tileHeight = 128.f;
            break;
        case 2:
            simpleEnemyDescriptor.texture = simpleEnemyTeleportTexture;
            simpleEnemyDescriptor.enemyType = SimpleEnemy::Type::TELEPORTER;
            simpleEnemyDescriptor.speed = { 0.f, 0.f };
            simpleEnemyDescriptor.direction = { 0.f, 0.f };
            simpleEnemyDescriptor.tileWidth = 128.f;
            simpleEnemyDescriptor.tileHeight = 128.f;
            break;
        }

        
        simpleEnemyDescriptor.bulletTexture = bulletTexture;
        simpleEnemyDescriptor.bulletManager = &m_bulletManager;

        SimpleEnemy& simpleEnemy = m_simpleEnemyPool.get();
        if (simpleEnemy.init(simpleEnemyDescriptor))
        {
            m_enemyManager.addEnemy(&simpleEnemy);
        }
    }
}

void World::addScore(int points)
{
    m_score += points;
    m_uiManager.updateScore(m_score);
}

void World::spawnPowerUp() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    PowerUp::Type type = static_cast<PowerUp::Type>(std::rand() % 3); // 0: SpeedBoost, 1: DamageBoost, 2: Shield
    float randomX = 100.f + static_cast<float>(std::rand() % 1720);
    float randomY = 100.f + static_cast<float>(std::rand() % 800);

    m_powerUpManager.spawnPowerUp(sf::Vector2f(randomX, randomY), type, m_powerUpTextures[static_cast<int>(type)]);
}

bool World::load()
{
    constexpr float millisecondsToSeconds = 1 / 1000.f;

    m_wave = 1;
    spawnEnemies(2);

	m_uiManager.init();
    m_soundManager.init();

	m_enemyManager.m_enemyPool = &m_simpleEnemyPool;

	m_lastEnemyCount = m_enemyManager.getEnemyCount();

    m_powerUpTextures[0] = AssetManager::getInstance()->loadTexture("../Data/Images/PowerUps/speed.png");
    m_powerUpTextures[1] = AssetManager::getInstance()->loadTexture("../Data/Images/PowerUps/damage.png");
    m_powerUpTextures[2] = AssetManager::getInstance()->loadTexture("../Data/Images/PowerUps/shield.png");


    
    sf::Texture* playerTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Player/player.png");
    
    Player::PlayerDescriptor playerDescriptor;
    playerDescriptor.texture = playerTexture;
    playerDescriptor.bulletTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Bullet/bullet.png");
    playerDescriptor.position = { 900.f, 900.f };
    playerDescriptor.speed = 300.f * millisecondsToSeconds;
    Player* player = new Player(m_bulletManager);
    const bool PlayerInitOk = player->init(playerDescriptor);
    player->setWorld(this);
    m_player = player;

    m_map = new tmx::Map();
    m_map->load("../Data/Levels/space.tmx");
    m_layerZero = new MapLayer(*m_map, 0);
    m_layerOne = new MapLayer(*m_map, 1);
    m_layerTwo = new MapLayer(*m_map, 2);
    m_collisionLayer = new ObjectLayer(*m_map, 3);

	m_collisionManager = new CollisionManager(m_player, &m_enemyManager, &m_bulletManager, &m_powerUpManager, m_soundManager);

	return PlayerInitOk;
}


void World::update(uint32_t deltaMilliseconds)
{
    if (m_isWaitingForStart)
    {
        m_uiManager.updateStartMessage("SPACE SHOOTER\n\n\nPress Enter to Start");

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            m_soundManager.playButtonPressedSound();
            m_soundManager.startGameSound();
            m_isWaitingForStart = false;
			m_uiManager.m_mainMenu = false;
        }
    }
    else if (m_isGameOver)
    {
        m_uiManager.updateStartMessage("GAME OVER\n\n\nScore: " + std::to_string(m_score) + "\n\n\nPress R to Restart");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            m_isGameOver = false;
            m_isWaitingForStart = true;
            m_score = 0;
            m_playerIsAlive = true;
            m_currentWaveSize = 1;
            m_enemySpeedMultiplier = 1.0f;
            m_wave = 1;
            m_hasSpawnedFinalWave = false;
            m_totalEnemiesSpawned = 0;
            m_uiManager.resetUIManager();
			m_player->resetToInitialState();
            m_enemyManager.clearEnemies();
            m_bulletManager.clearBullets();
            m_powerUpManager.clearPowerUps();
            m_lastEnemyCount = m_enemyManager.getEnemyCount();
        }
    }
    else
    {
        m_collisionManager->update(deltaMilliseconds);
        m_bulletManager.update(deltaMilliseconds);

        if (m_bulletManager.playSound)
        {
            m_soundManager.shootSound();
            m_bulletManager.playSound = false;
        }

        if (m_player != nullptr && m_player->m_hasToBeDestroyed)
        {
            m_playerIsAlive = false;
			m_isGameOver = true;
			m_uiManager.m_gameOver = true;
            m_soundManager.gameOverSound();
        }
        if (m_player != nullptr)
        {
            m_player->update(deltaMilliseconds);
        }

        m_enemyManager.update(deltaMilliseconds);

        if (m_lastEnemyCount > m_enemyManager.getEnemyCount())
        {
            m_lastEnemyCount = m_enemyManager.getEnemyCount();
            addScore(100);
        }

        if (m_enemyManager.getEnemyCount() == 0 && m_playerIsAlive)
        {
            if (m_currentWaveSize < 6)
            {
                m_currentWaveSize++;
            }
            else
            {
                m_enemySpeedMultiplier *= 1.1f;
            }

            if (std::rand() % 3 == 0) {
				spawnPowerUp();
            }
            spawnEnemies(m_currentWaveSize);
            m_lastEnemyCount = m_enemyManager.getEnemyCount();
        }
    }
}

void World::render(sf::RenderWindow& window)
{
    if (m_isWaitingForStart)
    {
        window.draw(*m_layerZero);
        window.draw(*m_layerOne);
        window.draw(*m_layerTwo);
        window.draw(*m_collisionLayer);

        m_uiManager.render(window);
    }
	else if (m_isGameOver)
	{
		window.draw(*m_layerZero);
		window.draw(*m_layerOne);
		window.draw(*m_layerTwo);
		window.draw(*m_collisionLayer);
		m_uiManager.render(window);
	}
    else
    {
        window.draw(*m_layerZero);
        window.draw(*m_layerOne);
        window.draw(*m_layerTwo);
        window.draw(*m_collisionLayer);

        m_uiManager.render(window);

        m_bulletManager.render(window);

        if (m_player != nullptr)
        {
            m_player->render(window);
        }
        m_enemyManager.render(window);

        if (m_enemy)
        {
            m_enemy->render(window);
        }

        m_powerUpManager.render(window);
    }

    
}
