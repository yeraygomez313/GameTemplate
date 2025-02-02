#pragma once

#include <Gameplay/SimpleEnemy.h>
#include <memory>
#include <vector>

class EnemyManager
{
public:
    void addEnemy(SimpleEnemy* enemy);
    void removeInactiveEnemies();
    void update(uint32_t deltaMilliseconds);
    void render(sf::RenderWindow& window);
    std::vector<SimpleEnemy*>& getActiveEnemies();

    ObjectPool<SimpleEnemy, 6>* m_enemyPool = nullptr;

    size_t getEnemyCount() const { return m_activeEnemies.size(); }

    void clearEnemies();

private:
    std::vector<SimpleEnemy*> m_activeEnemies;
};
