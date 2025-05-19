#include "solver.h"
#include <string>
#include <SFML/Graphics.hpp>

class Renderer 
{
public:
    Renderer(sf::RenderTarget& target);

    void render(Solver& solver) const;

private:
    sf::RenderTarget& m_target;

};