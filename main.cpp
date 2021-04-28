#include <iostream>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <chrono>

using namespace std;

#include "particle.cpp"


int main()
{   
    double dy = 1; double dx = 3; double sx = 0;
    int size;int elapsed;
    int x = 1000;int y = 600;
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(x, y), "Particle collison", sf::Style::Close);

    vector<Particle> particles;
    for(int i = 0; i < 200; i++)particles.push_back(Particle(x, y, particles));


    // particles[0].pos = {300, 300};
    // particles[0].radius = 10;
    // particles[0].v_ = {0.5, 0};


    // particles[1].pos = {900, 300};
    // particles[1].radius = 20;
    // particles[1].v_ = {-0.5, 0};


    while(window.isOpen())
    {
        window.clear(sf::Color::Black);

        size = particles.size();
        auto start = chrono::system_clock::now();
        for(int j = 0; j < 100; j++)
        {   
            for(int i = 0; i < size; i++)
            {   
                particles[i].collision(particles);
            }
            for(int i = 0; i < size; i++)
            {   
                particles[i].update_position(x, y, 100);
            }
        }
        auto end = chrono::system_clock::now();
        cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

        for(int i = 0; i < size; i++)
        {
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


