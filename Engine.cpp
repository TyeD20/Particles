#include "Engine.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <cstdlib>
#include <ctime>

using namespace std;

Engine::Engine()
{
    m_Window.create(sf::VideoMode(1440, 1080), "Particles");
}

void Engine::run()
{
    Clock c;
    cout << "Starting Particle unit test....." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x/2, (int)m_Window.getSize().y/2});
    p.unitTests();
    cout << "Unit test complete. Starting engine..." << endl;

    while(m_Window.isOpen())
    {
        Time t = c.restart();
        input();
        update(t.asSeconds());
        draw();
    }
}
void Engine::input()
{
    Event event;

    while(m_Window.pollEvent(event))
    {
        if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_Window.close();
        }

        std::vector<Particle> newParticle;
        
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button ==  Mouse::Left)
        {
            sf::Vector2 mousePosition = sf::Mouse::getPosition(m_Window);

            for (int i = 0; i < 5; i++)
            {
                int num = rand() % 26 + 25;
                newParticle.push_back(Particle(m_Window, num, mousePosition));
            }
        }
        m_particles.insert(m_particles.begin(), newParticle.begin(), newParticle.end());
    }
}

void Engine::update(float dtAsSeconds)
{
    std::vector<Particle>::iterator it;
    
    for(it = m_particles.begin(); it != m_particles.end();)
    {
        if(it->getTTL() > 0.0)
        {
            it->update(dtAsSeconds);
            it++;
        }
        else
        {
            it = m_particles.erase(it);
        }
        }
    
}

void Engine::draw()
{
    m_Window.clear();

    std::vector<Particle>::iterator it;

    for (it = m_particles.begin(); it != m_particles.end(); it++)
    {
        m_Window.draw(*it);
    }

    m_Window.display();
}