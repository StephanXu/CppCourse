#include <iostream>
#include <cmath>
#include <vector>

const float m = 2;

class Solid
{
public:
    virtual float Volume() const = 0;
    virtual float Weight() const
    {
        return Volume() * m;
    };
};

class Cube : public Solid
{
public:
    explicit Cube(float a, float b, float h) : a_(a), b_(b), h_(h) {}
    float Volume() const
    {
        return a_ * b_ * h_;
    }

private:
    float a_, b_, h_;
};

class Sphere : public Solid
{
public:
    explicit Sphere(float r) : r_(r) {}

    float Volume() const
    {
        return 4 / 3 * M_PI * std::pow(r_, 3);
    }

private:
    float r_;
};

class Cylinder : public Solid
{
public:
    explicit Cylinder(float r, float h) : r_(r), h_(h) {}
    float Volume() const
    {
        return M_PI * r_ * r_ * h_;
    }

private:
    float r_, h_;
};

int main()
{
    std::vector<Solid *> solid;
    solid.push_back(new Cube(5, 5, 6));
    solid.push_back(new Sphere(4));
    solid.push_back(new Cylinder(3, 9));

    float weight = 0;
    for (std::vector<Solid *>::iterator it = solid.begin();
         it != solid.end();
         it++)
    {
        weight += (*it)->Weight();
        delete *it;
    }
    std::cout << "Total: " << weight << std::endl;
}