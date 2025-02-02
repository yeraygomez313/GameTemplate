#include "Gameplay/PowerUp.h"

bool PowerUp::init(const PowerUpDescriptor& descriptor) {
    m_sprite.setTexture(*descriptor.texture);
    m_sprite.setPosition(descriptor.position);
    m_type = descriptor.type;
    return true;
}

void PowerUp::update(float deltaMilliseconds) {
}

void PowerUp::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

sf::FloatRect PowerUp::getBounds() const {
    return m_sprite.getGlobalBounds();
}
