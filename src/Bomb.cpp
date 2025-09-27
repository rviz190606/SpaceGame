#include "Bomb.hpp"
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

Bomb:: Bomb(sf::Vector2f pos, sf::Vector2f vel)
{
    speed = vel;
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(pos);
    bombclock.restart();
}

void Bomb::update(float dt)
{
    shape.move(speed * dt);
}

void Bomb::explode()
{
    if(exploded)return;
    exploded = true;
    shape.setRadius(70.f);
    bombclock.restart();
    

}