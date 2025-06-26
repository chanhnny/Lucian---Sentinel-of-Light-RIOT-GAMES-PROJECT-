#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void loadTexture(const std::string& file);
    void update(float dt);
    void handleInput();
    void applyGravity(float dt);
    void jump();
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    void stopFalling(float groundY);
    sf::Vector2f getFrameSize() const;
    void land();

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f velocity;
    bool isOnGround;

    float moveSpeed;
    float jumpStrength;
    float gravity;

    int currentFrame;
    float frameTime;       // Time per frame
    float frameTimer;      // Time accumulator

    enum class Action { Idle, Run, Jump, Shoot };
    Action currentAction;

    void updateFrameRect();
};