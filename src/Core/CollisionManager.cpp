#include "Core/CollisionManager.h"
#include <Gameplay/Bullet.h>
#include <Gameplay/PowerUp.h>
#include <Gameplay/SimpleEnemy.h>

CollisionManager::CollisionManager(Player* player, EnemyManager* enemyManager, BulletManager* bulletManager, PowerUpManager* powerUpManager, SoundManager& soundManager)
    : m_player(player), m_enemyManager(enemyManager), m_bulletManager(bulletManager), m_powerUpManager(powerUpManager), m_soundManager(soundManager)
{
}

void CollisionManager::update(uint32_t deltaMilliseconds)
{
    auto& activeEnemies = m_enemyManager->getActiveEnemies();
    auto& activeBullets = m_bulletManager->getBullets();
    auto& activePowerUps = m_powerUpManager->getPowerUps();

    for (auto bullet = activeBullets.begin(); bullet != activeBullets.end(); )
    {
        if (!m_player->m_hasToBeDestroyed && m_player->m_isShieldActive == false && (*bullet)->isBulletFriendly() && m_player->getBounds().intersects((*bullet)->getBounds()))
        {
			m_bulletManager->m_bulletPool.release(**bullet);
            bullet = activeBullets.erase(bullet);
			m_player->m_hasToBeDestroyed = true;
            m_soundManager.deathSound();
        }
        else
        {
            ++bullet;
        }
    }
    
    for (auto enemy = activeEnemies.begin(); enemy != activeEnemies.end(); )
    {
        SimpleEnemy* currentEnemy = *enemy;
        bool enemyHit = false;

        for (auto bullet = activeBullets.begin(); bullet != activeBullets.end(); )
        {
            if (!(*bullet)->isBulletFriendly() && currentEnemy->getBounds().intersects((*bullet)->getBounds()))
            {
                m_bulletManager->m_bulletPool.release(**bullet);
                bullet = activeBullets.erase(bullet);
                enemyHit = true;
                m_soundManager.deathSound();
                break;
            }
            else
            {
                ++bullet;
            }
        }

        if (enemyHit)
        {
			m_enemyManager->m_enemyPool->release(*currentEnemy);
            enemy = activeEnemies.erase(enemy);
        }
        else
        {
            ++enemy;
        }
    }

    for (auto powerUp = activePowerUps.begin(); powerUp != activePowerUps.end(); )
    {
        if (m_player->getBounds().intersects((*powerUp)->getBounds()))
        {
            PowerUp::Type type = (*powerUp)->getType();

            switch (type) {
            case PowerUp::Type::SpeedBoost:
                m_player->increaseSpeed(50.0f * (1 / 1000.f));
                m_soundManager.speedBoostSound();
                break;
            case PowerUp::Type::DamageBoost:
                m_player->increaseBulletSpeed(50.0f);
                m_soundManager.bulletBoostSound();
                break;
            case PowerUp::Type::Shield:
                m_player->activateShield(10000.f);
                m_soundManager.shieldBoostSound();
                break;
            }

            m_powerUpManager->m_powerUpPool.release(**powerUp);
            powerUp = activePowerUps.erase(powerUp);
        }
        else
        {
            ++powerUp;
        }
    }
}