#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "bullet.hpp"


class Plane
{
public:
    Plane(float s, float b, sf::Texture t);
    void bomb(std::vector<Bullet> &plane_bullets);
    void update(float dt);
private:
    sf::Sprite plane_sprite;
    sf::Clock plane_clock;
    float speed;
    float bomb_time;


}
