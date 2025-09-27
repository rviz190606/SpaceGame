#ifndef BOMBER_HPP
#define BOMBER_HPP
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Bomb.hpp"


class Bomber
{
public:
    Bomber(float s, float b, sf::Texture &t);
    void bomb(std::vector<Bomb> &bombs);
    void update(float dt);
    sf::Sprite bomber_sprite;
    float height,pos;
private:
    
    sf::Clock bomber_clock;
    float speed;
    float bomb_time;
    float hp = 200;


};
#endif
