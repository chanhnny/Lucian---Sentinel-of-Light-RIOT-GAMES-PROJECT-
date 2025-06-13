#include "EpisodeOne.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void runEpisodeOne(sf::RenderWindow& window, sf::Font& font) {
    // Basic ground
    sf::RectangleShape ground(sf::Vector2f(window.getSize().x, 100));
    ground.setFillColor(sf::Color(50, 50, 80));
    ground.setPosition(0, window.getSize().y - 100);

    // Load character sprite (test rectangle)
    sf::RectangleShape player(sf::Vector2f(60, 80));
    player.setFillColor(sf::Color::Cyan);
    player.setPosition(100, window.getSize().y - 100 - 80); // On top of ground

    // Physics
    sf::Vector2f velocity(0.f, 0.f);
    const float gravity = 1000.f;
    const float moveSpeed = 300.f;
    const float jumpStrength = -600.f;
    bool isOnGround = true;

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Input
        velocity.x = 0.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocity.x = -moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocity.x = moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround) {
            velocity.y = jumpStrength;
            isOnGround = false;
        }

        // Gravity
        velocity.y += gravity * dt;
        player.move(velocity * dt);

        // Collision with ground
        float groundLevel = window.getSize().y - 100 - player.getSize().y;
        if (player.getPosition().y >= groundLevel) {
            player.setPosition(player.getPosition().x, groundLevel);
            velocity.y = 0.f;
            isOnGround = true;
        }

        // Draw
        window.clear();
        window.draw(ground);
        window.draw(player);
        window.display();
    }
}