#include <iostream>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;

#include "particle.cpp"


int main()
{   
    int size;
    int elapsed;
    int x = 1000;
    int y = 600;
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(x, y), "Particle collison", sf::Style::Close);

    vector<Particle> particles;
    for(int i = 0; i < 100; i++)particles.push_back(Particle(x, y, particles));

    while(window.isOpen())
    {
        window.clear(sf::Color::Black);
        
        elapsed = clock.getElapsedTime().asMilliseconds();
        if(10 < elapsed)clock.restart();
        size = particles.size();
        for(int i = 0; i < size; i++)
        {
            if(10 < elapsed){particles[i].update_position(x, y);}
            sf::CircleShape shape = particles[i].draw();
            window.draw(shape);
        }
        


        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:break;
            }
           
        }
        
        window.display();
    }
    return 0;
}


