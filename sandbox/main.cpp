#include "Physics/Vec2.h"
#include "Physics/BoxShape.h"
#include "Physics/CircleShape.h"
#include "Physics/Shape.h"
#include<iostream>
#include<vector>

void printShape(const Shape& shape)
{
    switch (shape.getType())
    {
        case ShapeType::Circle:
            std::cout << "Circle\n";
            break;

        case ShapeType::Box:
            std::cout << "Box\n";
            break;
    }
}

int main()
{
	CircleShape circle(25.0f);
	BoxShape box(100.0f, 50.0f);

	std::cout << "box width: " << box.getWidth() << std::endl;
	
	std::cout << "box height: " << box.getHeight() << std::endl;

	std::cout << "circle radius: " << circle.getRadius() << std::endl;

	
	if(circle.getType() == ShapeType::Circle)
		std::cout << "Circulo esta bien\n";

	if(box.getType() == ShapeType::Box)
		std::cout << "Box ok\n";
	
	
	Shape* shape1 = &circle;
	Shape* shape2 = &box;

	std::cout << "\n POLIMORFISMO \n";

	std::cout << static_cast<int>(shape1->getType()) << '\n';
	std::cout << static_cast<int>(shape2->getType()) << '\n';
	
	std::vector<Shape*> shapes;
	shapes.push_back(&circle);
	shapes.push_back(&box);

	for(Shape* s : shapes)
	{
		printShape(*s);
	}
	return 0;
}


