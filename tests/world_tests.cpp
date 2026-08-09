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
#include "Physics/BoxShape.h"
#include "Physics/Collision.h"
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

// ---------------------------------------------------------------------
// Tests de deteccion de colisiones
// ---------------------------------------------------------------------

void test_two_circles_overlapping_are_detected()
{
	// Dos circulos de radio 1 centrados a distancia 1 -> se superponen.
	World world(Vec2::Zero);
	RigidBody* a = world.createBody(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));
	RigidBody* b = world.createBody(Vec2(1.0f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));
	(void)a;
	(void)b;

	world.step(0.0f);

	assert(world.getCollidingPairs().size() == 1);

	std::cout << "test_two_circles_overlapping_are_detected OK\n";
}

void test_two_circles_apart_are_not_detected()
{
	World world(Vec2::Zero);
	world.createBody(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));
	world.createBody(Vec2(10.0f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));

	world.step(0.0f);

	assert(world.getCollidingPairs().empty());

	std::cout << "test_two_circles_apart_are_not_detected OK\n";
}

void test_two_boxes_overlapping_are_detected()
{
	// Cajas de 2x2 centradas a distancia 1 en X -> se superponen (mitad de cada una).
	World world(Vec2::Zero);
	world.createBody(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<BoxShape>(2.0f, 2.0f));
	world.createBody(Vec2(1.0f, 0.0f), 1.0f, std::make_unique<BoxShape>(2.0f, 2.0f));

	world.step(0.0f);

	assert(world.getCollidingPairs().size() == 1);

	std::cout << "test_two_boxes_overlapping_are_detected OK\n";
}

void test_box_and_circle_not_overlapping_are_not_detected()
{
	World world(Vec2::Zero);
	world.createBody(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<BoxShape>(1.0f, 1.0f));
	world.createBody(Vec2(20.0f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));

	world.step(0.0f);

	assert(world.getCollidingPairs().empty());

	std::cout << "test_box_and_circle_not_overlapping_are_not_detected OK\n";
}

void test_three_bodies_only_touching_pair_is_reported()
{
	// A y B se tocan, C esta lejos de ambos -> solo 1 par reportado.
	World world(Vec2::Zero);
	RigidBody* bodyA = world.createBody(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));
	RigidBody* bodyB = world.createBody(Vec2(1.5f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));
	world.createBody(Vec2(50.0f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));

	world.step(0.0f);

	assert(world.getCollidingPairs().size() == 1);
	const CollidingPair& pair = world.getCollidingPairs()[0];
	assert((pair.a == bodyA && pair.b == bodyB) || (pair.a == bodyB && pair.b == bodyA));

	std::cout << "test_three_bodies_only_touching_pair_is_reported OK\n";
}

// ---------------------------------------------------------------------
// Tests de resolucion de colisiones
// ---------------------------------------------------------------------

void test_overlapping_circles_are_separated_after_resolution()
{
	// Dos circulos de radio 1 centrados a distancia 0.5 -> se superponen 1.5.
	// Despues de step(), la distancia entre centros debe ser >= suma de radios.
	World world(Vec2::Zero);
	RigidBody* a = world.createBody(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));
	RigidBody* b = world.createBody(Vec2(0.5f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));

	world.step(0.0f);

	float distance = (b->getPosition() - a->getPosition()).length();
	assert(distance >= 2.0f - 0.001f);

	std::cout << "test_overlapping_circles_are_separated_after_resolution OK\n";
}

void test_falling_body_bounces_off_static_body()
{
	// Cuerpo dinamico cayendo con velocidad hacia un cuerpo estatico debajo:
	// tras resolver la colision, su velocidad Y debe invertirse (rebotar hacia arriba).
	World world(Vec2::Zero);
	RigidBody* dynamicBody = world.createBody(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));
	world.createBody(Vec2(0.0f, 1.5f), 0.0f, std::make_unique<CircleShape>(1.0f)); // mass 0 -> estatico

	dynamicBody->setVelocity(Vec2(0.0f, 5.0f));
	dynamicBody->setRestitution(1.0f);

	world.step(0.0f); // dt 0 para aislar la resolucion de la integracion/gravedad

	assert(dynamicBody->getVelocity().m_y < 0.0f);

	std::cout << "test_falling_body_bounces_off_static_body OK\n";
}

void test_two_static_overlapping_bodies_do_not_move()
{
	// Ambos cuerpos con mass 0 (inverseMass 0) -> resolveCollision no debe
	// moverlos ni crashear al dividir por invMassSum.
	World world(Vec2::Zero);
	RigidBody* a = world.createBody(Vec2(0.0f, 0.0f), 0.0f, std::make_unique<CircleShape>(1.0f));
	RigidBody* b = world.createBody(Vec2(0.5f, 0.0f), 0.0f, std::make_unique<CircleShape>(1.0f));

	world.step(0.0f);

	assert(a->getPosition() == Vec2(0.0f, 0.0f));
	assert(b->getPosition() == Vec2(0.5f, 0.0f));

	std::cout << "test_two_static_overlapping_bodies_do_not_move OK\n";
}

void test_higher_restitution_bounces_back_faster()
{
	// Mismo escenario de caida, dos worlds distintos: restitucion 1.0 debe
	// devolver mas velocidad (en valor absoluto) que restitucion 0.0.
	World worldLow(Vec2::Zero);
	RigidBody* bodyLow = worldLow.createBody(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));
	RigidBody* staticLow = worldLow.createBody(Vec2(0.0f, 1.5f), 0.0f, std::make_unique<CircleShape>(1.0f));
	bodyLow->setVelocity(Vec2(0.0f, 5.0f));
	bodyLow->setRestitution(0.0f);
	staticLow->setRestitution(0.0f);

	World worldHigh(Vec2::Zero);
	RigidBody* bodyHigh = worldHigh.createBody(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<CircleShape>(1.0f));
	RigidBody* staticHigh = worldHigh.createBody(Vec2(0.0f, 1.5f), 0.0f, std::make_unique<CircleShape>(1.0f));
	bodyHigh->setVelocity(Vec2(0.0f, 5.0f));
	bodyHigh->setRestitution(1.0f);
	staticHigh->setRestitution(1.0f);

	worldLow.step(0.0f);
	worldHigh.step(0.0f);

	assert(bodyLow->getVelocity().m_y >= 0.0f); // restitucion 0 -> no rebota, solo se detiene
	assert(bodyHigh->getVelocity().m_y < bodyLow->getVelocity().m_y); // restitucion 1 -> rebota con mas velocidad

	std::cout << "test_higher_restitution_bounces_back_faster OK\n";
}

int main()
{
	test_static_body_does_not_move();

	// Descomenta cada linea a medida que implementes el test correspondiente:
	test_body_falls_under_gravity();
	test_bodies_with_different_mass_fall_at_same_rate();
	test_remove_body_keeps_other_pointers_valid();
	test_gravity_getter_setter_roundtrip();

	test_two_circles_overlapping_are_detected();
	test_two_circles_apart_are_not_detected();
	test_two_boxes_overlapping_are_detected();
	test_box_and_circle_not_overlapping_are_not_detected();
	test_three_bodies_only_touching_pair_is_reported();

	test_overlapping_circles_are_separated_after_resolution();
	test_falling_body_bounces_off_static_body();
	test_two_static_overlapping_bodies_do_not_move();
	test_higher_restitution_bounces_back_faster();

	std::cout << "All tests passed!\n";
	return 0;
}
