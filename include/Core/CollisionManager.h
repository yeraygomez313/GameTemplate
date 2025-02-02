#pragma once

#include <Core/BulletManager.h>
#include <Core/EnemyManager.h>
#include <Core/PowerUpManager.h>
#include <Core/SoundManager.h>
#include <Gameplay/Player.h>
#include <vector>

class CollisionManager
{
public:
    CollisionManager(Player* player, EnemyManager* enemyManager, BulletManager* bulletManager, PowerUpManager* powerUpManage, SoundManager& soundManager);

    void update(uint32_t deltaMilliseconds);

private:
    Player* m_player;
    EnemyManager* m_enemyManager;
    BulletManager* m_bulletManager;
    PowerUpManager* m_powerUpManager;
    SoundManager& m_soundManager;
};