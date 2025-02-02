#pragma once

#include <SFML/Graphics.hpp>

class PowerUp {
public:
    enum class Type {
        SpeedBoost,
        DamageBoost,
        Shield
    };

    struct PowerUpDescriptor {
        sf::Vector2f position;
        sf::Texture* texture;
        Type type;
    };

    PowerUp() = default;

    bool init(const PowerUpDescriptor& descriptor);
    void update(float deltaMilliseconds);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    Type getType() const { return m_type; }

private:
    sf::Sprite m_sprite;
    Type m_type;
};
