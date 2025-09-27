#ifndef BOMB_HPP
#define BOMB_HPP
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

class Bomb
{
public:
    Bomb(sf::Vector2f pos, sf::Vector2f vel);
    void update(float dt);
    void explode();
    sf::CircleShape shape;
    bool exploded = false;
    sf::Clock bombclock;

private:
    sf::Vector2f speed;
    
};

#endif