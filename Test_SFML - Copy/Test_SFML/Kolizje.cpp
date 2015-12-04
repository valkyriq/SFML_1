#include <SFML\Graphics.hpp>
#include "cGracz.h"

class Kolizje
{
public:
	static void czyKoliduje(cGracz &g1, std::vector <cGracz> V, sf::Vector2f ruch)
	{
		sf::FloatRect X = g1.doKolizji();
		sf::FloatRect Y = g1.doKolizji();
		X.left += ruch.x;
		Y.top += ruch.y;
		bool kolX = false; bool kolY = false;

		for (int i = 0; i < V.size(); i++)
		if (X.intersects(V[i].doKolizji()))
			kolX = true;
		else if (Y.intersects(V[i].doKolizji()))
			kolY = true;

		if (!kolX)
			g1.ruch(sf::Vector2f(ruch.x, 0));
		if (!kolY)
			g1.ruch(sf::Vector2f(0, ruch.y));
	}
};
