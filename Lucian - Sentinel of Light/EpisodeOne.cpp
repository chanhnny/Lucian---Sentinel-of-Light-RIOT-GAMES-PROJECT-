#include "EpisodeOne.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void runEpisodeOne(sf::RenderWindow& window, sf::Font& font) {
    // Setup level dimensions
    const float levelWidth = 3000.f;  // Example map width

    // Setup view (camera)
    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

    // Brick texture
    sf::Texture brickTexture;
    if (!brickTexture.loadFromFile("assets/images/brick-ground.png")) {
        std::cout << "Failed to load brick texture\n";
        return;
    }
    brickTexture.setRepeated(true);

    // Ground setup
    float groundHeight = window.getSize().y / 3.f;
    sf::RectangleShape ground(sf::Vector2f(levelWidth, groundHeight));
    ground.setTexture(&brickTexture);
    ground.setTextureRect(sf::IntRect(0, 0, levelWidth, groundHeight));
    ground.setPosition(0, window.getSize().y - groundHeight);

    int repeatFactor = 2;
    ground.setTextureRect(sf::IntRect(
        0,
        0,
        window.getSize().x * repeatFactor,
        groundHeight * repeatFactor
    ));

    // Player setup
    sf::RectangleShape player(sf::Vector2f(60, 80));
    player.setFillColor(sf::Color::Cyan);
    player.setPosition(100, window.getSize().y - groundHeight - 80);

    // Physics
    sf::Vector2f velocity(0.f, 0.f);
    const float gravity = 2000.f;
    const float moveSpeed = 300.f;
    const float jumpStrength = -800.f;
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity.x = -moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity.x = moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && isOnGround) {
            velocity.y = jumpStrength;
            isOnGround = false;
        }

        // Gravity and movement
        velocity.y += gravity * dt;
        player.move(velocity * dt);

        // Collision with ground
        float groundLevel = window.getSize().y - groundHeight - player.getSize().y;
        if (player.getPosition().y >= groundLevel) {
            player.setPosition(player.getPosition().x, groundLevel);
            velocity.y = 0.f;
            isOnGround = true;
        }

        // Clamp player to level bounds
        if (player.getPosition().x < 0)
            player.setPosition(0, player.getPosition().y);
        if (player.getPosition().x + player.getSize().x > levelWidth)
            player.setPosition(levelWidth - player.getSize().x, player.getPosition().y);

        // Update camera
        float camX = std::max(view.getSize().x / 2.f, player.getPosition().x + player.getSize().x / 2.f);
        camX = std::min(camX, levelWidth - view.getSize().x / 2.f);
        view.setCenter(camX, view.getSize().y / 2.f);
        window.setView(view);

        // Draw
        window.clear();
        window.draw(ground);
        window.draw(player);
        window.display();
    }
}