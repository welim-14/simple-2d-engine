#include <iostream>
#include "Physics/RigidBody.h"
#include "Physics/Vec2.h"

int main()
{
	// Prueba simple de RigidBody con gravedad


	// Cuerpo con masa 1.0, posición inicial en el origen
	RigidBody body(Vec2::Zero, 1.0f, nullptr); // shape nullptr, no es necesaria una forma para esta prueba

	const float dt = 1.0f / 60.0f; // aprox 60 FPS
	const Vec2 gravity(0.0f, -9.8f);

	std::cout << "Estado inicial -> pos: (" 
	          << body.getPosition().m_x << ", " << body.getPosition().m_y 
	          << ") vel: (" 
	          << body.getVelocity().m_x << ", " << body.getVelocity().m_y << ")\n";

	for (int frame = 0; frame < 10; ++frame)
	{
		body.applyForce(gravity * body.getMass()); // F = m * g
		body.integrate(dt);

		std::cout << "Frame " << frame 
		          << " -> pos: (" << body.getPosition().m_x << ", " << body.getPosition().m_y << ")"
		          << " vel: (" << body.getVelocity().m_x << ", " << body.getVelocity().m_y << ")\n";
	}

	return 0;
}