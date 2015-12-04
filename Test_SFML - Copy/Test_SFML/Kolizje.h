#include <SFML\Graphics.hpp>
#include "cGracz.h"

class Kolizje
{
public:
	static void czyKoliduje(cGracz &g1, std::vector <cGracz> V, sf::Vector2f ruch);
};
