#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

//#define G 6.67 * pow(10.0, -11.0)
#define G 1.0 //redefing Grav. Constant for simplicity (now i feel like god :D)
#define EARTHMASS 5.972 * pow(10.0, 24.0)
#define EARTHRAD 6.371 * pow(10.0, 6.0)
#define MOONMASS 7.347 * pow(10.0, 22.0)
#define MOONDIST 2.84 * pow(10.0, 8)
#define MOONVEL 1.022 * pow(10.0, 3)
#define MONTH 60.0 * 60.0 * 24.0 * 31

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& v)
{
    //std::cout<<'[';
    for(auto x: v )
    {
        std::cout << x;
        if(x != v[v.size() - 1])
        {
            std::cout << " ";
        }
    }
    //std::cout<<']';
    return os;
}

template<typename T>
class planet
{
    public:
        std::vector<T> pos;
        std::vector<T> vel;
        std::vector<T> a;
        T mass;



        planet(T m, std::vector<T> p, std::vector<T> v, std::vector<T> a) //Constructor
        {
            mass = m;
            pos = p;
            vel = v;
            a = a;
        }

        T distTo(planet<T> A) //returns the dist to another plan
        {
            T dist = std::sqrt(std::pow(std::abs(A.pos[0] - pos[0]),2) + std::pow(std::abs(A.pos[1] - pos[1]),2));
            return dist;
        }

        std::vector<T> ForceOnMe(planet<T> A)
        {
            T absforce = (G * A.mass * mass) / pow(this->distTo(A), 2);
            std::vector<T> richtungsvector = {(A.pos[0] - pos[0]) / distTo(A), (A.pos[1] - pos[1]) / distTo(A)};
            return {absforce * richtungsvector[0], absforce * richtungsvector[1]};
        }

        std::vector<T> ftoa(std::vector<T> force)
        {
            a[0] = force[0]/mass;
            a[1] = force[1]/mass;
            return a;
        }

        int lettimepass(double time, std::vector<T> force)
        {
            pos[0] += vel[0] * time;
            pos[1] += vel[1] * time;

            vel[0] += a[0] * time;
            vel[1] += a[1] * time;

            this->ftoa(force);
            return 0;
        }

};


int main()
{
    //planet<double> earth(EARTHMASS, std::vector<double>{0.0,0.0}, std::vector<double>{0.0,0.0}, std::vector<double>{0.0,0.0});
    //planet<double> moon(MOONMASS, std::vector<double>{MOONDIST,0.0}, std::vector<double>{0.0,MOONVEL}, std::vector<double>{0.0,0.0});

    // Test
    planet<double> a(100, std::vector<double>{-1.0, 0.0}, std::vector<double>{0.0,-1.0}, std::vector<double>{0.0,0.0});
    planet<double> b(1, std::vector<double>{1.0, 0.0}, std::vector<double>{0.0,1.0}, std::vector<double>{0.0,0.0});

    a.a = {0.0, 0.0};
    b.a = {0.0, 0.0};

    std::ofstream myfile("coords.txt", std::ofstream::out | std::ofstream::trunc);

    for(int i = 0; i < 10; i++)
    {
        std::cout << a.pos << "\n";
        std::cout << b.pos << "\n";
        //myfile << a.pos << "\n";
        //myfile << b.pos << "\n"; 
        for(int i = 0; i < 100; i++)
        {
            a.lettimepass(0.01, a.ForceOnMe(b));
            b.lettimepass(0.01, b.ForceOnMe(a));
        }
    }

    myfile.close();

    return 0; 
}