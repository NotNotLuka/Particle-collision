#ifndef VECTORX 
#define VECTORX 

#include <cmath>

using namespace std;

class Vector{
    private:
        double coordinates[2];
    public:
        Vector(double x = 0, double y = 0)
        {
            coordinates[0] = x;
            coordinates[1] = y;
        }

        double length()
        {
            return sqrt(coordinates[0] * coordinates[0] + coordinates[1] * coordinates[1]);
        }

        double& operator[](int i)
        {
            return coordinates[i];
        }

        Vector operator+(Vector two)
        {
            return {coordinates[0] + two[0], coordinates[1] + two[1]};
        }

        Vector operator*(double n)
        {
            return {coordinates[0] * n, coordinates[1] * n};
        }

        Vector operator/(double n)
        {
            return {coordinates[0] / n, coordinates[1] / n};
        }

        double operator*(Vector b)
        {
            return coordinates[0] * b[0] + coordinates[1] * b[1];
        }

};

#endif