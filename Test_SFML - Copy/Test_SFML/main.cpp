#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML\Audio.hpp>
#include <iostream>
#include <Windows.h>
class cGracz{

	sf::RectangleShape kwadrat;
	float predkosc = 150.f;
	bool doGory, doDolu, wPrawo, wLewo;
public:
	cGracz(sf::Vector2f rozmiar)
	{
		kwadrat.setSize(rozmiar);
	}

	void zmienPozycje(sf::Vector2f pozycja)
	{
		kwadrat.setPosition(pozycja);
	}

	void aktualizuj()
	{
		doGory = false; doDolu = false;
		wLewo = false; wPrawo = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			doGory = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			doDolu = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			wLewo = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			wPrawo = true;
	}

	void ruch(sf::Vector2f v)
	{
		kwadrat.move(v);
	}

	sf::Vector2f ruch(sf::Time czas)
	{
		sf::Vector2f v(0, 0);
		if (doGory)
			v.y -= predkosc;
		if (doDolu)
			v.y += predkosc;
		if (wLewo)
			v.x -= predkosc;
		if (wPrawo)
			v.x += predkosc;

		return v * czas.asSeconds();
	}

	sf::FloatRect doKolizji()
	{
		return kwadrat.getGlobalBounds();
	}

	void rysuj(sf::RenderWindow &okno)
	{
		okno.draw(kwadrat);
	}

};

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

int main()
{
	sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 600), "Kolizje");

	sf::Clock zegar;
	sf::Time CzasOdAktualizacji = sf::Time::Zero;
	const sf::Time KrokCzasowy = sf::seconds(1.f / 160.f);
	cGracz gracz(sf::Vector2f(50, 50));
	cGracz on(sf::Vector2f(50, 50)); on.zmienPozycje(sf::Vector2f(200, 200));
	cGracz inny(sf::Vector2f(50, 50)); inny.zmienPozycje(sf::Vector2f(300, 300));
	cGracz inny2(sf::Vector2f(50, 50)); inny2.zmienPozycje(sf::Vector2f(380, 180));
	std::vector <cGracz> V;
	V.push_back(on);
	V.push_back(inny);
	V.push_back(inny2);
	sf::SoundBuffer bufor;
	bufor.loadFromFile("A5.wav");
	sf::Sound dzwiek;
	dzwiek.setBuffer(bufor);

	while (oknoAplikacji.isOpen())
	{
		sf::Time Czas = zegar.restart();
		CzasOdAktualizacji += Czas;
		gracz.aktualizuj();
		while (CzasOdAktualizacji > KrokCzasowy)
		{
			CzasOdAktualizacji -= KrokCzasowy;
			sf::Event zdarzenie;
			while (oknoAplikacji.pollEvent(zdarzenie))
			{
				if (zdarzenie.type == sf::Event::Closed)
					oknoAplikacji.close();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					std::cout << "hello\n" << std::endl;
					dzwiek.play();
				}

			}
			Kolizje::czyKoliduje(gracz, V, gracz.ruch(KrokCzasowy));
		}
		oknoAplikacji.clear();
		gracz.rysuj(oknoAplikacji);
		for (int i = 0; i < V.size(); i++)
			V[i].rysuj(oknoAplikacji);
		oknoAplikacji.display();

		Sleep(5);

	}
	return 0;
}