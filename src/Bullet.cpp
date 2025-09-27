
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Bullet.hpp"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f vel, float team)
{
    speed = vel;
    shape.setRadius(5.f);
    if(team == 0)shape.setFillColor(sf::Color::Red);
    else shape.setFillColor(sf::Color::Blue);
    shape.setPosition(pos);
}

void Bullet::update(float dt)
{
    shape.move(speed * dt);
}