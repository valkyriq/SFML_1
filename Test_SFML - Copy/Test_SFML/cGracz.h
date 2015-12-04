#include <SFML\Graphics.hpp>

class cGracz{

	sf::RectangleShape kwadrat;
	float predkosc = 150.f;
	bool doGory, doDolu, wPrawo, wLewo;
public:
	cGracz(sf::Vector2f rozmiar);
	void zmienPozycje(sf::Vector2f pozycja);
	void aktualizuj();
	void ruch(sf::Vector2f v);
	sf::Vector2f ruch(sf::Time czas);
	sf::FloatRect doKolizji();
	void rysuj(sf::RenderWindow &okno);
};