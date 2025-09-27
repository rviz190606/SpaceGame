#include "Plane.hpp"
#include <bits/stdc++.h>

Plane::Plane(float s, float b, sf::Texture &t)
{
    speed = s;
    bomb_time = b;
    plane_sprite.setTexture(t);
    plane_sprite.setScale(0.1, 0.1);
    height = 80 + (std::rand() % (120 - 80 + 1));
    pos = (-340) + (std::rand() % ((-300) - (-340) + 1));
    plane_sprite.setPosition(pos, height);
}
void Plane::bomb(std::vector<Bullet> &plane_bullets, const sf::Vector2f& playerPos)
{
    if (plane_clock.getElapsedTime().asSeconds() > bomb_time)
    {
        sf::Vector2f dir = playerPos - plane_sprite.getPosition();
        float len = sqrt(dir.x * dir.x + dir.y * dir.y);
        dir /= len; 
        plane_bullets.push_back(Bullet(plane_sprite.getPosition(), speed*dir, 0));
        plane_clock.restart();
    }
}
void Plane::update(float dt)
{
    plane_sprite.move(sf::Vector2f(speed * dt, 0.f));
}