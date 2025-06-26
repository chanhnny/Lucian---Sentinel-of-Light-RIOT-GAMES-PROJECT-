#include "EpisodeOne.h"
#include "Player.h"
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
    Player player;
    player.loadTexture("assets/images/lucian-sprite.png");
    float groundY = window.getSize().y - groundHeight;
    float playerHeight = 64.f;  // matches 32 * 2 from sprite.setScale(2.f, 2.f)
    player.setPosition(100, groundY - playerHeight);

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

        // --- Handle input inside player ---
        player.handleInput();

        // --- Update player physics/animation ---
        player.update(dt);

        // --- Collision with ground ---
        float groundLevel = window.getSize().y - groundHeight - player.getFrameSize().y;
        if (player.getPosition().y >= groundLevel) {
            player.setPosition(player.getPosition().x, groundLevel);
            player.land();  // Sets vertical velocity to 0 and flags isOnGround = true
        }

        // --- Clamp to level bounds ---
        float playerRight = player.getPosition().x + player.getFrameSize().x;
        if (player.getPosition().x < 0)
            player.setPosition(0, player.getPosition().y);
        if (playerRight > levelWidth)
            player.setPosition(levelWidth - player.getFrameSize().x, player.getPosition().y);

        // --- Update camera to follow player ---
        float camX = std::max(view.getSize().x / 2.f, player.getPosition().x + player.getFrameSize().x / 2.f);
        camX = std::min(camX, levelWidth - view.getSize().x / 2.f);
        view.setCenter(camX, view.getSize().y / 2.f);
        window.setView(view);

        // --- Draw everything ---
        window.clear();
        window.draw(ground);      // tiled ground
        player.draw(window);      // animated sprite
        window.display();
    }
}