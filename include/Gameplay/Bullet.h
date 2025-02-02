#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Bullet
{
public:
    struct BulletDescriptor
    {
        sf::Vector2f position;
        sf::Texture* texture{ nullptr };
        sf::Vector2f direction{ 0.f, -1.f };
        float speed{ .0f };
        bool isFriendly { nullptr };
    };

    Bullet() = default;

    bool init(const BulletDescriptor& bulletDescriptor);

    void update(float deltaMilliseconds);

    void render(sf::RenderWindow& window);

    bool isOutOfBounds() const;

    sf::FloatRect getBounds() const { return m_sprite.getGlobalBounds(); }

	bool isBulletFriendly() { return m_isFriendly; }

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    sf::Vector2f m_direction;
    float m_speed{ .0f };
    bool m_isFriendly;
};
