#include <iostream>
#include <optional>

#include "Physics/CircleShape.h"
#include "Physics/BoxShape.h"
#include "Physics/RigidBody.h"
#include "Physics/Vec2.h"
#include "Physics/World.h"
#include "SFML/Graphics.hpp"

Vec2 gravedad(0.0f, 9.81f);

constexpr float k_radio = 15.0f;
constexpr float k_anchuraVentana = 900.0f;
constexpr float k_alturaVentana = 720.0f;
constexpr float k_dt = 1.0f / 60.0f;
constexpr float k_masa = 15.0f;
constexpr float k_densidad = 1.0f;
constexpr float pi = 3.141592;
constexpr float k_restitucion = 1.0f;

int cantidad_circulos = 3;

std::vector<RigidBody*> cuerpos; // arreglo para almacenar los cuerpos de world
std::vector<sf::CircleShape> circulos_sfml;
std::vector<sf::RectangleShape> rectangulos_sfml;
World world(gravedad);

void actualizarPosicion(const RigidBody& cuerpo, sf::CircleShape& circulo_sfml)
{
	const Vec2& pos = cuerpo.getPosition();
	const float x = pos.m_x;
	const float y = pos.m_y;
	circulo_sfml.setPosition({x, y});
}

void actualizarPosicion(const RigidBody& cuerpo, sf::RectangleShape& rectangulo_sfml)
{
	const Vec2& pos = cuerpo.getPosition();
	const float x = pos.m_x;
	const float y = pos.m_y;
	rectangulo_sfml.setPosition({x, y});
}

void setShapeColorRandom(sf::Shape& shape)
{
	// Generar valores aleatorios para los componentes de color
	int red = rand() % 256;   // Valor entre 0 y 255
	int green = rand() % 256; // Valor entre 0 y 255
	int blue = rand() % 256;  // Valor entre 0 y 255

	// Establecer el color del shape
	shape.setFillColor(sf::Color(red, green, blue));
}

void agregarCirculo(){
	float x = static_cast<float>(rand() % static_cast<int>(k_anchuraVentana));
	float y = static_cast<float>(rand() % static_cast<int>(k_alturaVentana));

	float radio = static_cast<float>(rand() % 20 + 10); // Radio aleatorio entre 10 y 30
	float masa = k_densidad * pi * radio * radio; // Calcular la masa del círculo

	RigidBody* circulo = world.createBody(Vec2(x, y), masa, std::make_unique<CircleShape>(radio));
	circulo->setVelocity(Vec2(x * 0.5f, y * 0.5f));
	circulo->setRestitution(k_restitucion);
	cuerpos.push_back(circulo);

	sf::CircleShape circulo_sfml(radio);
	setShapeColorRandom(circulo_sfml);
	circulo_sfml.setOrigin(circulo_sfml.getGeometricCenter());
	circulo_sfml.setPosition({x, y});
	setShapeColorRandom(circulo_sfml);

	circulos_sfml.push_back(circulo_sfml);
	cantidad_circulos++;

	std::cout << "Total de círculos: " << cantidad_circulos << "\n";
}

void procesarEventos(sf::RenderWindow& window)
{
	while(const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			window.close();

		else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if(keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				window.close();
			if(keyPressed->scancode == sf::Keyboard::Scancode::Up)
				gravedad.m_y += 9.81f;
			if(keyPressed->scancode == sf::Keyboard::Scancode::Down)
				gravedad.m_y -= 9.81f;
			if(keyPressed->scancode == sf::Keyboard::Scancode::Space)
				agregarCirculo();
		}
	}

}

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Inicializar la semilla para números aleatorios

	RigidBody* cuerpo = world.createBody(Vec2(100.0f, 0.0f), k_masa, std::make_unique<CircleShape>(k_radio));
	RigidBody* cuerpo2 = world.createBody(Vec2(138.0f, 250.0f), k_masa, std::make_unique<CircleShape>(k_radio));
	RigidBody* cuerpo3 = world.createBody(Vec2(120.0f, 400.0f), k_masa*0.25f, std::make_unique<CircleShape>(k_radio/2.0f));

	// bordes de pantalla para rebotar los cuerpos
	RigidBody* bordeSuperior = world.createBody(Vec2(k_anchuraVentana / 2.0f, 0.0f), 0.0f, std::make_unique<BoxShape>(k_anchuraVentana, 10.0f));
	RigidBody* bordeInferior = world.createBody(Vec2(k_anchuraVentana / 2.0f, k_alturaVentana), 0.0f, std::make_unique<BoxShape>(k_anchuraVentana, 10.0f));
	RigidBody* bordeIzquierdo = world.createBody(Vec2(0.0f, k_alturaVentana / 2.0f), 0.0f, std::make_unique<BoxShape>(10.0f, k_alturaVentana));
	RigidBody* bordeDerecho = world.createBody(Vec2(k_anchuraVentana, k_alturaVentana / 2.0f), 0.0f, std::make_unique<BoxShape>(10.0f, k_alturaVentana));

	cuerpos = {cuerpo, cuerpo2, cuerpo3, bordeSuperior, bordeInferior, bordeIzquierdo, bordeDerecho}; // arreglo para almacenar los cuerpos de world

	// Crear las representaciones gráficas de los cuerpos
	for (RigidBody* cuerpo : cuerpos)
	{
		if (cuerpo->getShape().getType() == ShapeType::Circle)
		{
			const CircleShape& circleShape = static_cast<const CircleShape&>(cuerpo->getShape());
			sf::CircleShape circulo_sfml(circleShape.getRadius());
			setShapeColorRandom(circulo_sfml);
			circulo_sfml.setOrigin(circulo_sfml.getGeometricCenter());
			circulos_sfml.push_back(circulo_sfml);
		}
		else if (cuerpo->getShape().getType() == ShapeType::Box)
		{
			const BoxShape& boxShape = static_cast<const BoxShape&>(cuerpo->getShape());
			sf::RectangleShape rectangulo_sfml({boxShape.getWidth(), boxShape.getHeight()});
			setShapeColorRandom(rectangulo_sfml);
			rectangulo_sfml.setOrigin(rectangulo_sfml.getGeometricCenter());
			rectangulos_sfml.push_back(rectangulo_sfml);
		}
	}

	sf::RenderWindow window(sf::VideoMode({static_cast<unsigned int>(k_anchuraVentana), static_cast<unsigned int>(k_alturaVentana)}), "Test1");

	sf::Clock clock;
	float acumulador = 0.0f;

	while (window.isOpen())
	{
		procesarEventos(window);

		if(!(world.getGravity() == gravedad))
		{
			world.setGravity(gravedad);
			std::cout << "Gravedad actual: " << world.getGravity().m_x << ", " << world.getGravity().m_y << "\n";
		}
			

		acumulador += clock.restart().asSeconds();
		while (acumulador >= k_dt)
		{
			world.step(k_dt);
			acumulador -= k_dt;
		}

		window.clear();

		size_t cont_c = 0;
		size_t cont_r = 0;

		for(RigidBody* cuerpo : cuerpos)
		{
			if (cuerpo->getShape().getType() == ShapeType::Circle)
			{
				actualizarPosicion(*cuerpo, circulos_sfml[cont_c]);
				cont_c++;
			}
			else if (cuerpo->getShape().getType() == ShapeType::Box)
			{
				actualizarPosicion(*cuerpo, rectangulos_sfml[cont_r]);
				cont_r++;
			}
		}


		for(const auto& circulo : circulos_sfml)
		{
			window.draw(circulo);
		}
		for(const auto& rectangulo : rectangulos_sfml)
		{
			window.draw(rectangulo);
		}
		window.display();
	}

	return 0;
}
