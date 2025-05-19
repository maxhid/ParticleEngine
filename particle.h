#ifndef PARTICLES_H
#define PARTICLES_H

#include <SFML/Graphics.hpp>

class Particle
{
  public:
    Particle(sf::Vector2f position, float radius, sf::Color color);

    sf::CircleShape shape;
    sf::Vector2f position_old;
    sf::Vector2f position_current;
    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    sf::Color m_color;

    float m_radius;

    void update(float deltaTime);
    void accelerate(sf::Vector2f a);
    void setVelocity(sf::Vector2f v, float dt);
    void addVelocity(sf::Vector2f v, float dt);
    sf::Vector2f getVelocity();

    void gravityUpdate(float deltaTime);

    void draw(sf::RenderWindow& window) const;

    float getRadius();
    sf::Vector2f getCurrentPosition();


    // bool isAlive() const;

  private:
    // sf::CircleShape shape;
    // sf::Vector2f position_old;
    // sf::Vector2f position_current;
    // sf::Vector2f acceleration;
    // sf::Vector2f velocity;

    // float m_radius;
    // float lifetime;
};

#endif