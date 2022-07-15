#pragma once
#include "Image.h"
#include "Maze.h"

enum Csprite{

	cCaminarIzquierda,
	cCaminarDerecha,
	cQuieto,
};

class EntidadesIA : public Entidad {//hereda publicamente de entidad

	Csprite mov;
	Csprite Clastmov;
	short Presa = 0;
public:
	bool Transformed;
	EntidadesIA(Bitmap^ jpg, Maze *mAze){
			Random rand;
			bool nacioBien = false;
			Transformed = false;
		do {
			x = rand.Next(6, 30);
			y = rand.Next(5, 18);
			/*int Y = 0;*/
			if (mAze->Fondo[y][x] != 1) {
				nacioBien = true;
			}
		} while (nacioBien == false);
		x = x * 45-13;
		y = y * 45-35;
		
		ancho = jpg->Width / 4;
		alto = jpg->Height / 3;

		dx = dy = 0;

		mov = cCaminarIzquierda;
	};
	void SetTransformed(bool value) { this->Transformed = value; }
	bool GetTransformed() { return this->Transformed; }
	void Mover(Graphics^ g) {

		x += dx;
		y += dy;

	}
	void SetPresa(short value) { this->Presa = value; }

	short GetPresa() { return this->Presa; }

	void Colisiona_con(EntidadesIA* entity){
		if (this->HitBoxDX().IntersectsWith(entity->HitBoxDX())){
			this->SetDX(0);
		}
		if (this->HitBoxDY().IntersectsWith(entity->HitBoxDY())) {
			this->SetDY(0);
		}
	}
	System::Drawing::Rectangle Aura() {
		/*return System::Drawing::Rectangle(x-(3*45),y-(4*45),45*6,45*7);*/
		return System::Drawing::Rectangle(x - (3 * 45), y - (3 * 45), 45 * 6, 45 * 6);
	}
	void SetLastmov(Csprite valor) {
		Clastmov = valor;
	}
	void Setmov(Csprite valor) {
		mov = valor;
	}
	Csprite Getmov() {
		return mov;
	}
	Csprite GetLastmov() {
		return Clastmov;
	}
	void SetAccion(Csprite valor) {
		mov = valor;
	}
	void Draw(Graphics^ g, Bitmap^ img, int T){
		System::Drawing::Rectangle corte = System::Drawing::Rectangle(IDx % 4 * ancho, mov * alto, ancho, alto);
		g->DrawImage(img, System::Drawing::Rectangle(x, y, 58, 70), corte, GraphicsUnit::Pixel);
		if (T == 1)
			g->DrawRectangle(Pens::Red, HitBox());
		if (T == 2)
			g->DrawRectangle(Pens::Black, HitBox());

		if (dx != 0 || dy != 0)
		{
			if (mov == cCaminarDerecha || mov == cCaminarIzquierda)
				IDx = (IDx + 1) % 4;

		}
		if (dx == 0 && dy == 0) {
			if (Clastmov == cCaminarIzquierda)
				IDx = 0;
			else
				IDx = 1;
			mov = cQuieto;

		}
	}

};

class Corrupts {//clase donde se crean un vector de la clase entidadIA
public:
	vector<EntidadesIA*>corrupts;
	short Transformado = 0;
public:
	Corrupts(short n, Bitmap^ img, Maze* mAze)
	{
		for (int i = 0; i < n; i++) {
			EntidadesIA* obs = new EntidadesIA(img, mAze);
			corrupts.push_back(obs);
			if (i != 0 && corrupts.at(i)->GetX() == corrupts.at(i - 1)->GetX()) {
				delete corrupts.at(i);
				corrupts.erase(corrupts.begin() + i);
				i--;
			}
			corrupts[i]->SetLastmov(cCaminarDerecha);
		}
	}

	bool Colision(System::Drawing::Rectangle jugador)
	{
		for each (EntidadesIA * obs in corrupts)
		{
			if (obs->HitBox().IntersectsWith(jugador))
				return true;
		}
		return false;
	}
	bool Eliminar(System::Drawing::Rectangle obj)
	{
		for (int i = 0; i < corrupts.size(); i++)
		{
			if (corrupts.at(i)->Area().IntersectsWith(obj))
			{
				delete corrupts.at(i);
				corrupts.erase(corrupts.begin() + i);
				i--;
				Transformado++;
				return true;
			}
		}
		return false;
	}

	void Mover(Graphics^ g)
	{
		for each (EntidadesIA * i in corrupts)
		{
			i->Mover(g);
		}
	}
	void Draw(Graphics^ g, Bitmap^ img, Bitmap^ corrupted)
	{
		for (EntidadesIA* obs : corrupts)
		{	
			if (obs->GetTransformed() == false)
				obs->Draw(g, img, 1);
			if(obs->GetTransformed() == true)
				obs->Draw(g, corrupted, 1);
		}
	}
};

class Allys {//clase donde se crean un vector de la clase entidadIA
public:
	vector<EntidadesIA*>allies;
public:
	Allys(short n, Bitmap^ img, Maze* mAze)
	{

		for (int i = 0; i < n; i++) {
			EntidadesIA* obs = new EntidadesIA(img, mAze);
			allies.push_back(obs);
			if (i < 2) {
				allies[i]->SetX(30);
				allies[i]->SetY(15 + (45 * (i + 1)));
			}
			if (i != 0 && allies.at(i)->GetX() == allies.at(i - 1)->GetX() && i>=2) {
				delete allies.at(i);
				allies.erase(allies.begin() + i);
				i--;
			}
			allies[i]->SetLastmov(cCaminarDerecha);
			allies[i]->Setmov(cCaminarDerecha);
			allies[i]->SetDX(5);
			allies[i]->SetDY(5);
		}

	}
	bool Colision(System::Drawing::Rectangle jugador)
	{
		for each (EntidadesIA * obs in allies)
		{
			if (obs->HitBoxDX().IntersectsWith(jugador) || obs->HitBoxDY().IntersectsWith(jugador))
				return true;
		}
		return false;
	}
	bool Eliminar(System::Drawing::Rectangle obj)
	{
		for (unsigned int i = 0; i < allies.size(); i++)
		{
			if (allies.at(i)->HitBox().IntersectsWith(obj))
			{
				delete allies.at(i);
				allies.erase(allies.begin() + i);
				
				i--;
				return true;
			}
			
		}
		return false;
	}

	void Mover(Graphics^ g)
	{
		for each (EntidadesIA * i in allies)
		{
			i->Mover(g);
		}
	}
	void Draw(Graphics^ g, Bitmap^ img)
	{
		for (EntidadesIA* obs : allies)
		{
			obs->Draw(g, img, 2);
		}
	}
};

class Assasins {//clase donde se crean un vector de la clase entidadIA
public:
	vector<EntidadesIA*>assasins;
public:
	Assasins(short n, Bitmap^ img, Maze* mAze)
	{
		for (int i = 0; i < n; i++) {
			EntidadesIA* obs = new EntidadesIA(img, mAze);
			assasins.push_back(obs);
			if (i != 0 && assasins.at(i)->GetX() == assasins.at(i - 1)->GetX()) {
				assasins.erase(assasins.begin() + i);
				i--;
			}
			assasins[i]->SetLastmov(cCaminarDerecha);
		}

	}

	bool Colision(System::Drawing::Rectangle jugador)
	{
		for each (EntidadesIA * obs in assasins)
		{
			if (obs->HitBox().IntersectsWith(jugador) || obs->HitBoxDY().IntersectsWith(jugador))
				return true;
		}
		return false;
	}
	bool Eliminar(System::Drawing::Rectangle obj)
	{
		for (int i = 0; i < assasins.size(); i++)
		{
			if (assasins.at(i)->HitBox().IntersectsWith(obj))
			{
				delete assasins.at(i);
				assasins.erase(assasins.begin() + i);
				i--;
				return true;
			}
		}
		return false;
	}

	void Mover(Graphics^ g)
	{
		for each (EntidadesIA * i in assasins)
		{
			i->Mover(g);
		}
	}
	void Draw(Graphics^ g, Bitmap^ img)
	{
		for (EntidadesIA* obs : assasins)
		{
			obs->Draw(g, img, 1);
		}
	}
};