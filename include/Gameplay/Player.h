#pragma once

#include <Core/BulletManager.h>
#include <Gameplay/Bullet.h>
#include <Gameplay/GameObject.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

class World;

class Player : public GameObject
{
public:

    struct PlayerDescriptor
    {
        sf::Vector2f position;
        sf::Texture* texture{ nullptr };
        sf::Texture* bulletTexture{ nullptr };
        float speed{ .0f };
        float bulletSpeed{ 300.f };
    };

    ~Player() override = default;

    Player(BulletManager& bulletManager) : m_bulletManager(bulletManager) {}

    bool init(const PlayerDescriptor& playerDescriptor);

    sf::FloatRect getBounds() const { return m_sprite.getGlobalBounds(); }

    void update(float deltaMilliseconds) override;
    void render(sf::RenderWindow& window) override;

    void setWorld(World* world) { m_world = world; }

    void setPosition(const sf::Vector2f& position)
    {
        m_sprite.setPosition(position);
    }

    void resetToInitialState();

    void increaseSpeed(float amount);
    void increaseBulletSpeed(float amount);
    void activateShield(float duration);

    bool m_hasToBeDestroyed = false;
    bool m_isShieldActive = false;

private:

    void shoot();

    sf::Sprite m_sprite;
    float m_speed{ .0f };
    sf::Vector2f m_direction{ .0f, .0f };

    sf::Texture* m_bulletTexture{ nullptr };
    float m_bulletSpeed{ 300.f };
    World* m_world{ nullptr };

    BulletManager& m_bulletManager;

    float m_shootCooldown{ 2000.f };
    float m_timeSinceLastShot{ 2000.f };

    float m_shieldTimeLeft{ 0.f };
};