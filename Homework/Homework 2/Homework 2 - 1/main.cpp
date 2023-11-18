#include <iostream>
using namespace std;

/**
 * Base class Shape --> abstract class
 */
class Shape{
protected:
    string name;

public:
    // Constructor
    Shape(const string n): name(n){}

    // Pure virtual function to calculate area
    virtual double area() const = 0;

    // Virtual function to display shape information
    virtual void display() const{
        cout<<"Shape: "<< name << std::endl;
    }
};

/**
 * Derived class CurvedShape --> abstract class
 */
class CurvedShape : public Shape{
public:
    // Constructor
    CurvedShape(const string n) : Shape(n){}

    // Override the display function
    void display() const override {
        Shape::display();
        cout << "Type: Curved" << endl;
    }
};

/**
 * Derived class Circle
 */
class Circle : public CurvedShape {
private:
    double radius; //circle's radius

public:
    // Constructor
    Circle(const string n, double r) : CurvedShape(n), radius(r) {}

    // Override the area function
    double area() const override {
        return 3.14159265 * radius * radius;
    }

    // Override the display function
    void display() const override {
        CurvedShape::display();
        cout << "Radius: " << radius <<"\nArea "<< this->area() << endl;

    }
};

/**
 * Derived class Ellipse
 */
class Ellipse : public CurvedShape{
private:
    double major_axis;
    double minor_axis;

public:
    // Constructor
    Ellipse(const string n, double maj, double min): CurvedShape(n), major_axis(maj), minor_axis(min){};

    // Override the area function
    double area() const override {
        return 3.14159265 * major_axis * minor_axis;
    }

    // Override the display function
    void display() const override {
        CurvedShape::display();
        cout << "Axis: " << major_axis << " " << minor_axis << "\nArea " << this->area() << endl;

    }
};

/**
 * Derived class AngleShape --> abstract class
 */
class AngleShape : public Shape {
public:
    // Constructor
    AngleShape(const string n) : Shape(n){}

    // Override the display function
    void display() const override {
        Shape::display();
        cout << "Type: Angle" << endl;
    }
};

/**
 * Derived class Rectangle
 */
class Rectangle : public AngleShape{
private:
    double base;
    double height;

public:
    // Constructor
    Rectangle(const string n, double b, double h) : AngleShape(n), base(b), height(h) {}

    // Override the area function
    double area() const override {
        return base * height;
    }

    // Override the display function
    void display() const override {
        AngleShape::display();
        cout << "Base: " << base << "\nHeight: " << height << "\nArea: " << this->area() << endl;
    }
};

/**
 * Derived class Triangle
 */
class Triangle : public AngleShape{
private:
    double base;
    double height;

public:
    // Constructor
    Triangle(const string n, double b, double h) : AngleShape(n), base(b), height(h) {}

    // Override the area function
    double area() const override {
        return base * height / 2;
    }

    // Override the display function
    void display() const override {
        AngleShape::display();
        cout << "Base: " << base << "\nHeight: " << height << "\nArea: " << this->area() << endl;
    }
};

/**
 * Derived class Trapezoid
 */
class Trapezoid : public AngleShape{
private:
    double base1;
    double base2;
    double height;

public:
    // Constructor
    Trapezoid(const string n, double b1, double b2, double h) : AngleShape(n), base1(b1), base2(b2), height(h) {}

    // Override the area function
    double area() const override {
        return base1 * base2 * height / 2;
    }

    // Override the display function
    void display() const override {
        AngleShape::display();
        cout << "Base1: " << base1 << "\nBase2: " << base2 <<"\nHeight: " << height << "\nArea: " << this->area() << endl;
    }
};

int main(){

    Circle circle("Circle", 4);
    circle.display();
    circle.area();

    cout<<"\n"<<endl;

    Ellipse ellipse("Ellipse", 5,6);
    ellipse.area();
    ellipse.display();

    cout<<"\n"<<endl;

    Rectangle rectangle("Rectangle", 4,5);
    rectangle.area();
    rectangle.display();

    cout<<"\n"<<endl;

    Triangle triangle("Triangle", 2,3);
    triangle.area();
    triangle.display();

    cout<<"\n"<<endl;

    Trapezoid trapezoid("Trapezoid", 2,3,4);
    trapezoid.area();
    trapezoid.display();
}