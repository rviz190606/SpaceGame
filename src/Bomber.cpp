#include "Bomber.hpp"
#include <bits/stdc++.h>

Bomber::Bomber(float s, float b, sf::Texture &t)
{
    speed = s;
    bomb_time = b;
    bomber_sprite.setTexture(t);
    bomber_sprite.setScale(0.1, 0.1);
    height = 190 + ( std::rand() % ( 220 - 190 + 1 ) );
    pos = (-40) + ( std::rand() % ( 0 - (-40) + 1 ) );
    bomber_sprite.setPosition(pos,height);
}
void Bomber::bomb(std::vector<Bomb> &bombs)
{
    if (bomber_clock.getElapsedTime().asSeconds() > bomb_time)
    {
        bombs.push_back(Bomb(bomber_sprite.getPosition(), sf::Vector2f(speed, 500.f)));
        bomber_clock.restart();
    }
}
void Bomber::update(float dt)
{
    bomber_sprite.move(sf::Vector2f(speed * dt, 0.f));
}