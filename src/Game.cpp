#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
#include "Plane.hpp"
#include <SFML/Audio.hpp>
#include "Game.hpp"

Game::Game() : window(sf::VideoMode(1000, 800), "my_window")

{
    if (!bgMusic.openFromFile("res/Music/bg.ogg"))
    {
        std::cout << "Could not load music!\n";
    }
    if (!shootBuffer.loadFromFile("res/Music/shoot.wav"))
    {
        std::cout << "Could not load shoot sound!\n";
    }
    shootSound.setBuffer(shootBuffer);
    shootSound.setVolume(100);
    bgMusic.setVolume(80);


    window.setFramerateLimit(60);
    if (!texture.loadFromFile("res/Textures/spaceship.png"))
    {
        std::cout << "didnt load image" << '\n';
    }
    if (!plane_texture.loadFromFile("res/Textures/plane.png"))
    {
        std::cout << "didnt load image" << '\n';
    }
    if (!bg_texture.loadFromFile("res/Textures/background2.png"))
    {
        std::cout << "didnt load image" << '\n';
    }

    if (!font.loadFromFile("res/Fonts/ARCADE.TTF"))
    {
        std::cout << "Could not load font!" << std::endl;
    }
    if (!bomber_texture.loadFromFile("res/Textures/bomber.png"))
    {
        std::cout << "didnt load image" << '\n';
    }
    

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(20.f, 20.f);
    sprite.setTexture(texture);
    background.setTexture(bg_texture);

    hptxt.setFont(font);
    hptxt.setCharacterSize(24);
    hptxt.setFillColor(sf::Color::Yellow);
    hptxt.setPosition(890.f, 20.f);

    gameovertext.setFont(font);
    gameovertext.setCharacterSize(60);
    gameovertext.setFillColor(sf::Color::Yellow);
    gameovertext.setPosition(200.f, 300.f);

    hiscoretxt.setFont(font);
    hiscoretxt.setCharacterSize(24);
    hiscoretxt.setFillColor(sf::Color::Yellow);
    hiscoretxt.setPosition(180.f, 20.f);
    // tgt.setTexture(tgt_texture);
    // tgt.setScale(0.05,0.05);
    // tgt.setPosition(900,400);
    sprite.setScale(0.1, 0.1);
    sprite.setPosition(sf::Vector2f(500.f, 600.f));
    texture.setSmooth(true);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = bg_texture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    background.setScale(scaleX, scaleY);

    sf::Vector2u cannon_size = texture.getSize();
    sprite.setOrigin(cannon_size.x / 2.f, cannon_size.y / 2.f);
    rotation = -90;
    plane_gap = 3;
    bomber_gap = 10;
    plane_speed = 200;
    bomber_speed = 100;
    plane_shoot_gap = 1.7;
    bomber_shoot_gap = 2;
    score = 0;
    hp = 100;
    player_speed = 200;
    hiscore = 0;
    lvl = 0;
    gameovertext.setString("GAME OVER\nPRESS ENTER TO RESTART");
}

void Game::reset()
{
    bullets.clear();
    plane_bullets.clear();
    bombers.clear();
    planes.clear();
    bombs.clear();
    score = 0;
    hp = 100;
    plane_gap = 3;
    bomber_gap = 10;
    plane_speed = 200;
    bomber_speed = 100;
    plane_shoot_gap = 1.7;
    bomber_shoot_gap = 2;
    player_speed = 200;
    lvl = 0;
    bgMusic.setPlayingOffset(sf::seconds(0.f));
    bgMusic.play();
    sprite.setPosition(sf::Vector2f(500.f, 600.f));
    state = GameState::Playing;
}

void Game::gameOver()
{
    state = GameState::GameOver;
    sprite.setColor(sf::Color::Red);
}

void Game::run()
{
    bgMusic.setLoop(true);
    bgMusic.play();

    while (window.isOpen())
    {

        float dt = clk.restart().asSeconds();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        if (state == GameState::Playing)
        {
            if (score / 300 > lvl)
            {
                plane_gap -= 0.1;
                bomber_gap -= 0.1;
                plane_speed += 10;
                bomber_speed += 10;
                plane_shoot_gap -= 0.05;
                bomber_shoot_gap -= 0.04;
                lvl = score / 300;
                if (score < 500)
                    hp = std::min(100, hp + 10);
                else if (score < 1000)
                    hp = std::min(100, hp + 20);
                else
                    hp = std::min(100, hp + 30);
                player_speed += 10;
            }
            // User Inputs
            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            //     player_speed = 200;
            // else
            //     player_speed = 200;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&&sprite.getPosition().x>-10)
                sprite.move(sf::Vector2f(-player_speed * dt, 0.f * dt));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&sprite.getPosition().x<1010)
                sprite.move(sf::Vector2f(player_speed * dt, 0.f * dt));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sprite.getPosition().y > 600)
                sprite.move(sf::Vector2f(0.f * dt, (-1)*player_speed * dt));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sprite.getPosition().y < 800)
                sprite.move(sf::Vector2f(0.f * dt, player_speed * dt));
            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            // {
            //     sprite.rotate(30 * dt);
            //     rotation += 30 * dt;
            // }
            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
            // {
            //     sprite.rotate(-30 * dt);*
            //     rotation -= (30 * dt);
            // }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                if (bullet_timer.getElapsedTime().asSeconds() > 0.3)
                {
                    bullet_timer.restart();
                    shootSound.play(); 
                    bullets.push_back(Bullet(sprite.getPosition() + sf::Vector2f(0.f, 0.f), sf::Vector2f(cos(rotation * 3.14 / 180) * 500.f, sin(rotation * 3.14 / 180) * 500.f), 1));
                }
            }

            if (plane_timer.getElapsedTime().asSeconds() > plane_gap)
            {
                plane_timer.restart();
                planes.push_back(Plane(plane_speed, plane_shoot_gap, plane_texture));
            }
            if (bomber_timer.getElapsedTime().asSeconds() > bomber_gap)
            {

                bomber_timer.restart();
                bombers.push_back(Bomber(bomber_speed, bomber_shoot_gap, bomber_texture));
            }

            for (auto &b : bullets)
            {
                b.update(dt);
            }
            for (auto &b : plane_bullets)
            {
                b.update(dt);
            }
            for (auto &b : bombs)
            {
                if (!b.exploded)
                    b.update(dt);
            }
            auto new_end = std::remove_if(bombs.begin(), bombs.end(), [&](const Bomb &b)
                                          { return b.bombclock.getElapsedTime().asSeconds() > 0.1 && b.exploded; });

            bombs.erase(new_end, bombs.end());
            for (auto &p : planes)
            {
                p.bomb(plane_bullets, sprite.getPosition());
                p.update(dt);
            }
            for (auto &p : bombers)
            {
                p.bomb(bombs);
                p.update(dt);
            }
            auto ne = std::remove_if(bullets.begin(), bullets.end(), [](const Bullet &b)
                                     { return (abs(b.shape.getPosition().x) > 1000 || abs(b.shape.getPosition().y) > 1000); });

            bullets.erase(ne, bullets.end());
            auto at = std::remove_if(planes.begin(), planes.end(), [](const Plane &p)
                                     { return (abs(p.plane_sprite.getPosition().x) > 1000 || abs(p.plane_sprite.getPosition().y) > 1000); });
            planes.erase(at, planes.end());
            auto ner = std::remove_if(plane_bullets.begin(), plane_bullets.end(), [](const Bullet &b)
                                      { return (abs(b.shape.getPosition().x) > 1000 || abs(b.shape.getPosition().y) > 1000); });
            plane_bullets.erase(ner, plane_bullets.end());
            auto per = std::remove_if(bombs.begin(), bombs.end(), [](const Bomb &b)
                                      { return (abs(b.shape.getPosition().x) > 1000 || abs(b.shape.getPosition().y) > 1000); });
            bombs.erase(per, bombs.end());

            auto pera = std::remove_if(bombers.begin(), bombers.end(), [](const Bomber &b)
                                       { return (abs(b.bomber_sprite.getPosition().x) > 1000 || abs(b.bomber_sprite.getPosition().y) > 1000); });
            bombers.erase(pera, bombers.end());

            for (size_t i = 0; i < plane_bullets.size(); i++)
            {
                if (plane_bullets[i].shape.getGlobalBounds().intersects(sprite.getGlobalBounds()))
                {
                    plane_bullets.erase(plane_bullets.begin() + i);
                    hp -= 20;
                }
            }
            for (size_t i = 0; i < bombs.size(); i++)
            {
                if (bombs[i].shape.getGlobalBounds().intersects(sprite.getGlobalBounds()) && !bombs[i].exploded)
                {
                    bombs[i].explode();
                    hp -= 30;
                }
            }
            for (auto &b : bombs)
            {
                if (b.shape.getPosition().y > 600)
                    b.explode();
            }

            for (size_t i = 0; i < planes.size(); i++)
            {
                for (size_t j = 0; j < bullets.size(); j++)
                {
                    if (planes[i].plane_sprite.getGlobalBounds().intersects(bullets[j].shape.getGlobalBounds()))
                    {
                        bullets.erase(bullets.begin() + j);
                        planes.erase(planes.begin() + i);
                        score += 100;
                    }
                }
            }
            for (size_t i = 0; i < bombers.size(); i++)
            {
                for (size_t j = 0; j < bullets.size(); j++)
                {
                    if (bombers[i].bomber_sprite.getGlobalBounds().intersects(bullets[j].shape.getGlobalBounds()))
                    {
                        bullets.erase(bullets.begin() + j);
                        bombers.erase(bombers.begin() + i);
                        score += 200;
                    }
                }
            }
            for (size_t i = 0; i < bombs.size(); i++)
            {
                for (size_t j = 0; j < bullets.size(); j++)
                {
                    if (bombs[i].shape.getGlobalBounds().intersects(bullets[j].shape.getGlobalBounds()))
                    {
                        bombs[i].explode();
                    }
                }
            }

            text.setString("Score: " + std::to_string(score));
            hptxt.setString("HP: " + std::to_string(hp));
            hiscoretxt.setString("Highscore: " + std::to_string(hiscore));
            if (hp <= 0)
            {
                state = GameState::GameOver;
                bgMusic.stop();
                hiscore = std::max(hiscore, score);
            }
        }
        else if (state == GameState::GameOver)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                reset();
            }
        }

        // Draw
        window.clear(sf::Color::Black);
        window.draw(background);
        if (state == GameState::Playing)
        {

            window.draw(text);
            window.draw(hptxt);
            window.draw(hiscoretxt);
            for (auto b : bullets)
            {
                window.draw(b.shape);
            }
            for (auto b : plane_bullets)
            {
                window.draw(b.shape);
            }
            for (auto b : bombs)
            {
                window.draw(b.shape);
            }
            for (auto &p : planes)
            {
                window.draw(p.plane_sprite);
            }
            for (auto &p : bombers)
            {
                window.draw(p.bomber_sprite);
            }
            window.draw(sprite);
        }
        else
        {
            window.draw(gameovertext);
        }
        window.display();

        // End of Draw
    }
}
