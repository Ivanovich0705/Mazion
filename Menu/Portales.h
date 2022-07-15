#pragma once
#include "Image.h"
#include "Maze.h"



class Portal : public Entidad {//hereda publicamente de entidad
	bool activo = false;
public:
	Portal(Bitmap^ jpg, Maze* mAze) {
		Random rand;
		bool nacioBien = false;
		do {
			srand(time(NULL));
			x = rand.Next(3, 28);
			y = rand.Next(2, 17);
			/*int Y = 0;*/
			if (mAze->Fondo[y][x] != 1) {
				nacioBien = true;
			}
		} while (nacioBien == false);
		x = x * 45;
		y = y * 45;

		ancho = jpg->Width / 4;
		alto = jpg->Height;

		dx = dy = 0;

	}
	~Portal() {}
	System::Drawing::Rectangle PortalArea() {
		return System::Drawing::Rectangle(x, y, 45, 45);
	}
	void Draw(Graphics^ g, Bitmap^ img) {
		System::Drawing::Rectangle corte = System::Drawing::Rectangle(IDx % 4 * ancho, 0, ancho, alto);
		g->DrawImage(img, System::Drawing::Rectangle(x, y, 45, 45), corte, GraphicsUnit::Pixel);
		g->DrawRectangle(Pens::Purple, PortalArea());
		IDx = (IDx + 1) % 4;
	}
};

class Portals {//clase donde se crean un vector de la clase portal
	short portalTimeVisible = 0;
public:
	vector<Portal*> Portales;
	
	Portals(Bitmap^ img, Maze* mAze, PlayerC* jugador) {}

	void CrearPortal(Bitmap^ img, PlayerC* jugador, Maze* mAze) {
		//Portal* P0 = new Portal(img, mAze);
		Portales.push_back(new Portal(img, mAze));
		for (short i = 1; i < 2; i++) {
			//Portal* P1 = new Portal(img, mAze);
			Portales.push_back(new Portal(img, mAze));
			if (jugador->Aura().IntersectsWith(Portales.at(i)->PortalArea()) == false) {
				delete Portales.at(i);
				Portales.erase(Portales.begin() + i);
				i--;
			}
		}
	}
	void Teletransport(Graphics^ g, Bitmap^ img, PlayerC* jugador, Maze* mAze) {
		for (short i = 0; i < Portales.size(); i++)
			Portales.at(i)->Draw(g, img);
		if(Portales.size()>1)
			if (jugador->HitBox().IntersectsWith(Portales.at(1)->PortalArea())) {
				jugador->SetX(Portales.at(0)->GetX() - 13);
				jugador->SetY(Portales.at(0)->GetY() - 35);
				portalTimeVisible = clock();
				
			}
			if (clock() - portalTimeVisible >= 1000 && portalTimeVisible>0) {
				for (short i = Portales.size() - 1; i >= 0; i--) {
					delete Portales.at(0);
					Portales.erase(Portales.begin());
				}
				portalTimeVisible = 0;
			}
	}
};