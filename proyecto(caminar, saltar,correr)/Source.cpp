#include <SFML/Graphics.hpp>
#include "G-World.h"

using namespace std;
using namespace sf;
int main()
{
	//condicionales de estado
	bool standing = false;
	bool gliding = false;
	bool airborn = true;
	bool spacep = false;
	bool ap = false;
	bool dp = false;
	
	//crear parametros de la ventana.
	sf::RenderWindow window(sf::VideoMode(960, 560), "proyecto 2");
	
	//limitar el framerate
window.setFramerateLimit(60);


//crea eventos
Event event;

//crea el reloj que controla los frames
Clock clock;

//crear retenedores de texturas y sprites
Texture PlayerTexture;
Sprite PlayerSprite;
Texture BG_Texture;
Sprite BG_Sprite;

//cargar texturas
if (!BG_Texture.loadFromFile("assets/battle bg.png"))
{
	//en caso de que no cargue se le avisa al usuario
	cout << "no se encontro la textura" << endl;
}

if (!PlayerTexture.loadFromFile("assets/Flame head idle (frame 1).gif"))
{
	cout << "no se encontro la textura de jugador." << endl;
}


//asignar las texturas a los srites----------------
PlayerSprite.setTexture(PlayerTexture);
BG_Sprite.setTexture(BG_Texture);
//-------------------------------------------------

//le damos tamaño proporcional al de la ventana para que encaje.-------
BG_Sprite.setScale(Vector2f(0.704845815f, 0.777777778f));
PlayerSprite.setScale(Vector2f(0.20f, 0.20f));
//---------------------------------------------------------------------

//configracion del mundo y el cuerpo 

World world;
world.setGravity(Vec2(0.0f, 250.0f));

Body b1;
//asignar masa del objeto
b1.mass = 5.0f;
//valor de masa inversa
b1.invMass = 1 / b1.mass;
//asignar posicion en la ventana
b1.position = Vec2(200.0f, 100.0f);
//asignar velocidad inicial del objeto
b1.velocity = Vec2(0.0f, 0.0f);


//Agregar el cuerpo al mundo para que se afectado por sus propiedades------
world.addBody(&b1);

Rect<float> size = PlayerSprite.getGlobalBounds();
//--------------------------------------------------------------------------

//asigna el sprite del jugador al cuerpo---------------------------------
PlayerSprite.setPosition(Vector2f(b1.position.x, b1.position.y));

while (window.isOpen())
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed) {
			window.close();
		}

	}
//------------------------------------------------------------------------

	//detienen el salto al tocar el suelo.-----------------
	if (b1.position.y == 410.0f)
	{
	
		b1.velocity.y = 0.00;
	}
	//-----------------------------------------------------

	//hace saltar al cuerpo si esta en el suelo -----------------------
	
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			gliding = true;
			cout << " Space is pressed" << endl;

			if (gliding == true)
			{
				b1.force.y = -1490;
			}
		}

		if (gliding == true)
		{
			if (!Keyboard::isKeyPressed(Keyboard::Space))
			{
				b1.force.y = 0.0f ;
			}
		}
	
	//------------------------------------------------------------------

	
	//moverse a la izquierda ----------------------------------------------------------------
	
			if (sf::Keyboard::isKeyPressed(Keyboard::A))
			{
				ap = true;
				cout << " Left is pressed" << endl;
				if (ap == true)
				{
					b1.force.x = -800.0f;
				}
			}

			// bracket de if responsable por detener el sprite cuando A es presionada.--------------------
			if (ap == true)
			{
				if (!Keyboard::isKeyPressed(Keyboard::A))
				{
					ap = false;
					//b1.force.x = 0.0f;
				}
			}
	
	// --------------------------------------------------------------------------------------------

	//Moverse a la derecha-------------------------------------------------------------------------
	
		
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				dp = true;
				cout << " Right is pressed" << endl;
				if (dp == true)
				{
					b1.force.x = 800.0f;
				}
			}
		
		//bracket responsable por detener el sprited------------
		if (dp == true)
		{
			if (!Keyboard::isKeyPressed(Keyboard::D))
			{
				dp = false;
				//b1.force.x = 0.0f;
			}
		}
	
		//-------------------------------------------------------

	


	//evita que el cuerpo atraviese el piso-------------
	if (b1.position.y >= 410.0f)
	{
		standing = true;
		b1.position.y = 410.0f;
		if (airborn == false)
		{
			b1.velocity.y = 0;
		}
		
	}
	//--------------------------------------------------

		//lo que hace que pasen los frames y redibuja la pantalla---------------------
		Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();
		
		
		world.Step(dt);

		PlayerSprite.setPosition(Vector2f(b1.position.x, b1.position.y));
		window.clear(Color::Transparent);
		window.draw(BG_Sprite);
		window.draw(PlayerSprite);
		window.display();
		//-----------------------------------------------------------------------------
	}

	return 0;
}