#include "vectors.cpp"
#include <unordered_set>

using namespace std;

class Particle {
    public:
        Vector pos;
        Vector v;
        Vector v_;
        double radius = 0; Vector center;
        unordered_set<int> collisions;

    Particle(int x_size, int y_size, vector<Particle> all)
    {
        bool overlap = true;
        while(overlap)
        {
            pos[0] = rand() % x_size;
            pos[1] = rand() % y_size;

            while(radius == 0){radius = rand() % 20 + 5;}
            center = pos + (Vector (cos(45), sin(45)) * radius);
            overlap = check_overlap(all);
        }

        v[0] = rand() % 10 - 5;
        v[1] = rand() % 10 - 5;
        v_ = v;
        
    }


    bool check_overlap(vector<Particle> all)
    {
        for(Particle particle : all)
        {
            if((pow(particle.center[0] - center[0], 2) + pow(particle.center[1] - center[1], 2)) <= particle.radius + radius)return true;
        }
        return false;
    }


    void update_position(int x_size, int y_size, double delta)
    {  
        v = v_;
        pos = pos + v / delta;
        center = pos + (Vector (cos(45), sin(45)) * radius); 

        if (center[0] - radius < 0) {pos[0] += - (center[0] - radius) / 2; v_[0] = -v[0];}
        if (center[1] - radius < 0) {pos[1] += - (center[1] - radius) / 2; v_[1] = -v[1];}

        if (x_size < center[0] + radius){pos[0] -= 2 * (center[0] + radius - x_size); v_[0] = -v[0];}
        if (y_size < center[1] + radius){pos[1] -= 2 * (center[1] + radius - y_size); v_[1] = -v[1];}

    }


    void collision(vector<Particle>& all)
    {   int i = 0;
        bool in;
        for(Particle& particle : all)
        {   i += 1;
            in = collisions.find(i) != collisions.end();

            if(&particle != this && (((particle.center[0] - center[0]) * (particle.center[0] - center[0])) + ((particle.center[1] - center[1]) * (particle.center[1] - center[1]))) <= (particle.radius + radius) * (particle.radius + radius))
            {   
                collisions.insert(i);
                if(!in)
                {   
                    double d;
                    double m1 = radius;
                    double m2 = particle.radius;

                    double k1 = (m1 - m2) / (m1 + m2);
                    double k2 = (2 * m2) / (m1 + m2);


                    Vector b = center * (-1) + particle.center;b = b / b.length();

                    Vector a = Vector(b[1], -b[0]);

                    Vector vn = b * (v * b); Vector vn1 = b * (particle.v * b);

                    Vector vt = a * (v * a);

                    vn = vn * k1 + vn1 * k2;
                    v_ = vn + vt;
                }

            }else{if(in){collisions.erase(i);}}
        }
    }


    sf::CircleShape draw()
    {   
        sf::CircleShape shape(radius);
        shape.setFillColor(sf::Color(255, 255, 255));
        shape.setPosition(pos[0], pos[1]);
        return shape;
    }
};