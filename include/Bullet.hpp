#ifndef BULLET_HPP
#define BULLET_HPP

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet(sf::Vector2f pos, sf::Vector2f vel, float team);
    void update(float dt);
    sf::CircleShape shape;
private:
    
    sf::Vector2f speed;
};
#endif