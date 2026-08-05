#include <iostream>
#include <optional>

#include "Physics/CircleShape.h"
#include "Physics/RigidBody.h"
#include "Physics/Vec2.h"
#include "SFML/Graphics.hpp"

void actualizarPosicion(const RigidBody& cuerpo, sf::CircleShape& circulo_sfml)
{
	const Vec2& pos = cuerpo.getPosition();
	const float x = pos.m_x;
	const float y = pos.m_y;
	circulo_sfml.setPosition({x, y});
}

void procesarEventos(sf::RenderWindow& window)
{
	while (const std::optional<sf::Event> event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
	}
}

void actualizarCuerpo(RigidBody& cuerpo, const Vec2& gravedad, float dt)
{
	cuerpo.applyForce(gravedad * cuerpo.getMass());
	cuerpo.integrate(dt);
}

int main()
{
	constexpr float k_radio = 50.0f;
	constexpr float k_anchuraVentana = 1280.0f;
	constexpr float k_alturaVentana = 720.0f;
	constexpr float k_dt = 1.0f / 60.0f;
	constexpr float k_masa = 1.0f;

	const Vec2 p_inicial(640.0f, 0.0f);
	const Vec2 gravedad(0.0f, 9.81f);

	RigidBody cuerpo(p_inicial, k_masa, std::make_unique<CircleShape>(k_radio));

	sf::CircleShape circulo_sfml(k_radio);
	circulo_sfml.setOrigin(circulo_sfml.getGeometricCenter());
	circulo_sfml.setFillColor(sf::Color(86, 168, 219));
	circulo_sfml.setPosition({p_inicial.m_x, p_inicial.m_y});

	sf::RenderWindow window(sf::VideoMode({static_cast<unsigned int>(k_anchuraVentana), static_cast<unsigned int>(k_alturaVentana)}), "Test1");

	sf::Clock clock;
	float acumulador = 0.0f;

	while (window.isOpen())
	{
		procesarEventos(window);

		acumulador += clock.restart().asSeconds();
		while (acumulador >= k_dt)
		{
			actualizarCuerpo(cuerpo, gravedad, k_dt);
			acumulador -= k_dt;
		}

		window.clear();
		actualizarPosicion(cuerpo, circulo_sfml);

		std:: cout << "Posición: (" << cuerpo.getPosition().m_x << ", " << cuerpo.getPosition().m_y << ")\n";

		window.draw(circulo_sfml);
		window.display();
	}

	return 0;
}
