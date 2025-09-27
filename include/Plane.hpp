#ifndef PLANE_HPP
#define PLANE_HPP
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Bullet.hpp"


class Plane
{
public:
    Plane(float s, float b, sf::Texture &t);
    void bomb(std::vector<Bullet> &plane_bullets,const sf::Vector2f& playerPos);
    void update(float dt);
    sf::Sprite plane_sprite;
    float height,pos;
private:
    
    sf::Clock plane_clock;
    float speed;
    float bomb_time;


};

#endif