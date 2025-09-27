#ifndef Game_HPP
#define Game_HPP
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Plane.hpp"
#include "Bullet.hpp"
#include "Bomb.hpp"
#include <SFML/Audio.hpp>
#include "Bomber.hpp"

enum class GameState { Playing, GameOver };

class Game
{
public:
    Game();
    void run();
    void reset();
    void gameOver();

private:
    
    GameState state = GameState::Playing;
    std::vector<Plane> planes;
    std::vector<Bullet> bullets, plane_bullets;
    std::vector<Bomb> bombs;
    std::vector<Bomber> bombers;
    sf::RenderWindow window;
    sf::Texture texture, tgt_texture, plane_texture, bomber_texture, bg_texture;
    sf::Clock clk, plane_timer, bomber_timer;
    sf::Clock bullet_timer;
    sf::Sprite sprite, plane, background;
    sf::Font font;
    sf::Text text, hptxt,gameovertext,hiscoretxt;
    sf::Vector2u cannon_size;
    float rotation, plane_gap, plane_speed, player_speed, bomber_gap, bomber_speed, plane_shoot_gap, bomber_shoot_gap;
    int score, hp,hiscore,lvl = 0;
    sf::Music bgMusic;   
    sf::Sound shootSound,gosound; 
    sf::SoundBuffer shootBuffer,gobuffer;
};
#endif
