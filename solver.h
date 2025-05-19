#ifndef SOLVER_H
#define SOLVER_H

#include "particle.h"
#include "constants.h"

class Solver
{
public:
    Solver() = default; // TODO: abändern so das die framerate übergeben werden kann also step_dt

    Particle& addObject(sf::Vector2f position, float radius, sf::Color color);

    void update();

    void setGravity(sf::Vector2f g);

    void setFramerate(float frame_rate);

    std::vector<Particle>& getObjects();

    int getNumberOfObjects();

    void setBoundary(sf::Vector2f position, float radius);

    sf::Vector3f getBoundary();

private:
    std::vector<Particle> m_objects;

    sf::Vector2f boundary_center {420.0f, 420.0f};
    float boundary_radius {100.0f};
    int m_sub_steps {16};


    sf::Vector2f m_gravity {0.0f, constants::gravity};
    float m_step_dt {1.0f / 60}; // soll durch den constructor gesetzt werden können oder durch eine Funktion

    void apply_gravity();

    void applyBoundary();

    void updateObjects (float step_dt);

    void checkCollisions();
};

#endif