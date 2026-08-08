/**
 * world_tests.cpp
 * Tests manuales (sin framework) para la clase World.
 *
 * Cada test es una funcion que arma un escenario, ejecuta step()
 * y usa assert() para verificar que el resultado es el esperado.
 * assert() aborta el programa inmediatamente si la condicion es falsa,
 * imprimiendo el archivo y la linea donde fallo.
 *
 * IMPORTANTE: assert() se desactiva si el simbolo NDEBUG esta definido
 * (esto pasa automaticamente en builds "Release" de CMake). Mientras
 * estemos escribiendo tests, conviene compilar en Debug:
 *   cmake -B build -DCMAKE_BUILD_TYPE=Debug
 */

#include "Physics/World.h"
#include "Physics/RigidBody.h"
#include "Physics/CircleShape.h"
#include <cassert>
#include <iostream>
#include <memory>

// ---------------------------------------------------------------------
// Test ya resuelto, a modo de ejemplo del patron a seguir
// ---------------------------------------------------------------------
void test_static_body_does_not_move()
{
	World world;

	// mass = 0.0f -> inverseMass = 0 -> World::step() no le aplica gravedad
	RigidBody* body = world.createBody(Vec2(0.0f, 0.0f), 0.0f, std::make_unique<CircleShape>(1.0f));

	world.step(1.0f);
	world.step(1.0f);
	world.step(1.0f);

	assert(body->getPosition().m_x == 0.0f);
	assert(body->getPosition().m_y == 0.0f);
	assert(body->getVelocity().m_y == 0.0f);

	std::cout << "test_static_body_does_not_move OK\n";
}

// ---------------------------------------------------------------------
// TODO: completa los siguientes tests.
// Cada uno tiene una pista de que verificar; el "como" (armar el World,
// crear los bodies, calcular a mano el valor esperado) queda en tus manos.
// Cuando termines un test, descomenta su llamada en main().
// ---------------------------------------------------------------------

void test_body_falls_under_gravity()
{
	// Pista: crea un World con gravity = Vec2(0.0f, 9.81f) (o usa el default),
	// crea un body con mass > 0, llama step(dt) una vez con dt = 1.0f
	// y compara la posicion/velocidad resultante contra el calculo manual:
	//   v = v0 + g * dt
	//   p = p0 + v * dt
	World world;

	RigidBody* body = world.createBody(Vec2(0.0f, 0.0f), 10.0f, std::make_unique<CircleShape>(1.0f));

	world.step(1.0f);

	assert(body->getVelocity().m_y == 9.81f);
	assert(body->getPosition().m_y == 9.81f);

	std::cout << "test_body_falls_under_gravity OK\n";
}

void test_bodies_with_different_mass_fall_at_same_rate()
{
	// Pista: crea dos bodies con distinta mass (ej. 1.0f y 10.0f) en la
	// misma posicion inicial, haz varios step() con el mismo dt, y verifica
	// que ambos terminan con la MISMA velocidad y la MISMA posicion Y.
	// Esto confirma que F = m*g y a = F/m se cancelan correctamente.
	World world;

	RigidBody* body1 = world.createBody(Vec2(0.0f, 0.0f), 10.0f, std::make_unique<CircleShape>(1.0f));
	RigidBody* body2 = world.createBody(Vec2(0.0f, 0.0f), 100.0f, std::make_unique<CircleShape>(1.0f));

	world.step(1.0f);
	world.step(1.0f);
	world.step(1.0f);

	assert(body1->getPosition().m_y == body2->getPosition().m_y);
	assert(body1->getVelocity().m_y == body2->getVelocity().m_y);

	std::cout << "test_bodies_with_different_mass_fall_at_same_rate OK\n";

}

void test_remove_body_keeps_other_pointers_valid()
{
	// Pista: crea tres bodies (A, B, C), guarda sus punteros, remueve B,
	// y verifica que A y C siguen teniendo la posicion/velocidad correcta
	// despues de otro step(). Esto prueba que vector<unique_ptr<RigidBody>>
	// no invalida los punteros de los elementos que NO se removieron.
	//
	World world;

	RigidBody* body1 = world.createBody(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));
	RigidBody* body2 = world.createBody(Vec2(0.0f, 0.0f), 2.0f, std::make_unique<CircleShape>(1.0f));
	RigidBody* body3 = world.createBody(Vec2(0.0f, 0.0f), 3.0f, std::make_unique<CircleShape>(1.0f));

	world.step(1.0f);

	world.removeBody(body2);

	assert(body1->getVelocity().m_y == 9.81f && body1->getPosition().m_y == 9.81f);
	assert(body3->getVelocity().m_y == 9.81f && body3->getPosition().m_y == 9.81f);

	std::cout << "test_remove_body_keeps_other_pointers_valid OK\n";
}

void test_gravity_getter_setter_roundtrip()
{
	// Pista: crea un World, llama setGravity(Vec2(1.0f, 2.0f)),
	// y verifica que getGravity() devuelve exactamente ese valor.
	
	World world;

	world.setGravity(Vec2(1.0f, 2.0f));

	assert(world.getGravity() == Vec2(1.0f, 2.0f));

	std::cout << "test_gravity_setter_getter_roundtrip OK\n";
	
}

int main()
{
	test_static_body_does_not_move();

	// Descomenta cada linea a medida que implementes el test correspondiente:
	test_body_falls_under_gravity();
	test_bodies_with_different_mass_fall_at_same_rate();
	test_remove_body_keeps_other_pointers_valid();
	test_gravity_getter_setter_roundtrip();

	std::cout << "All tests passed!\n";
	return 0;
}
