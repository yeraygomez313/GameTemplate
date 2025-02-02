#include "Core/EnemyManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

void EnemyManager::addEnemy(SimpleEnemy* enemy)
{
    if (enemy)
    {
        m_activeEnemies.push_back(enemy);
    }
}

void EnemyManager::removeInactiveEnemies()
{
    
}

std::vector<SimpleEnemy*>& EnemyManager::getActiveEnemies()
{
    return m_activeEnemies;
}

void EnemyManager::update(uint32_t deltaMilliseconds)
{
    for (auto* enemy : m_activeEnemies)
    {
        if (enemy)
        {
            enemy->update(deltaMilliseconds);
        }
    }

}

void EnemyManager::render(sf::RenderWindow& window)
{
    for (auto* enemy : m_activeEnemies)
    {
        if (enemy)
        {
            enemy->render(window);
        }
    }
}

void EnemyManager::clearEnemies()
{
    for (auto* enemy : m_activeEnemies)
    {
        if (enemy)
        {
            m_enemyPool->release(*enemy);
        }
    }

    m_activeEnemies.clear();
}
