#include "Player.h"

Player::Player()
    : velocity(0.f, 0.f),
    isOnGround(true),
    moveSpeed(300.f),
    jumpStrength(-600.f),
    gravity(1000.f),
    currentFrame(0),
    frameTime(0.2f),
    frameTimer(0.f),
    currentAction(Action::Idle)
{
}

void Player::loadTexture(const std::string& file) {
    if (!texture.loadFromFile(file)) {
        throw std::runtime_error("Failed to load player texture");
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 500, 500)); // Adjust if needed
    sprite.setScale(0.4f, 0.4f); // Adjust based on your sprite size
}

void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

void Player::handleInput() {
    velocity.x = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        velocity.x = -moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        velocity.x = moveSpeed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && isOnGround)
        jump();
}

void Player::jump() {
    velocity.y = jumpStrength;
    isOnGround = false;
}

void Player::applyGravity(float dt) {
    velocity.y += gravity * dt;
}

void Player::update(float dt) {
    applyGravity(dt);
    sprite.move(velocity * dt);

    // Choose animation state
    if (!isOnGround)
        currentAction = Action::Jump;
    else if (velocity.x != 0)
        currentAction = Action::Run;
    else
        currentAction = Action::Idle;

    // Animate (if multiple frames later)
    frameTimer += dt;
    if (frameTimer >= frameTime) {
        frameTimer = 0.f;
        currentFrame = (currentFrame + 1) % 1; // only 1 frame per action for now
        updateFrameRect();
    }
}

void Player::stopFalling(float groundY) {
    sprite.setPosition(sprite.getPosition().x, groundY - sprite.getGlobalBounds().height);
    velocity.y = 0.f;
    isOnGround = true;
}

void Player::land() {
    velocity.y = 0.f;
    isOnGround = true;
}

sf::Vector2f Player::getFrameSize() const {
    return sf::Vector2f(
        sprite.getTextureRect().width * sprite.getScale().x,
        sprite.getTextureRect().height * sprite.getScale().y
    );
}

void Player::updateFrameRect() {
    int frameWidth = 500;
    int frameHeight = 500;
    int col = static_cast<int>(currentAction) % 2;
    int row = static_cast<int>(currentAction) / 2;

    sf::IntRect rect(col * frameWidth, row * frameHeight, frameWidth, frameHeight);
    sprite.setTextureRect(rect);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}