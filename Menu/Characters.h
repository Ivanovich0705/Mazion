#pragma once
#include "Image.h"
#include <conio.h>
using namespace System;
using namespace System::Drawing;

enum sprite
{
	CaminarIzquierda,
	CaminarDerecha,
	Quieto
};

class PlayerC : public Entidad {
protected:
	sprite mov;
	sprite lastmov;
	short HP = 3;
public:
	PlayerC(Bitmap^ jpg) {
		ancho = jpg->Width / 4;
		alto = jpg->Height / 3;

		dx = dy = 0;

		x = 30;
		y = 15;

		mov = Quieto;
	}
	short GetVidas() { return HP; }
	void SetVidas(short value) { this->HP += value; }
	void SetAccion(sprite valor){
		mov = valor;
	}
	void SetLastmov(sprite valor){
		lastmov = valor;
	}
	sprite GetLastmov(){
		return lastmov;
	}
	sprite GetAccion(){
		return mov;
	}
	void Mover(Graphics^ g)
	{
			x += dx;
			y += dy;
	}
	void Draw(Graphics^ g, Bitmap^ img, Bitmap^ imgHP) override {
		System::Drawing::Rectangle corte = System::Drawing::Rectangle(IDx % 4 * ancho, mov * alto, ancho, alto);//corte del jugador
		g->DrawImage(imgHP, System::Drawing::Rectangle(3, 3, 35* this->GetVidas(), 35), System::Drawing::Rectangle(0, 0, imgHP->Width/10*this->GetVidas(), imgHP->Height), GraphicsUnit::Pixel);//imprime vida
		g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);//imprime jugador
		g->DrawRectangle(Pens::Purple, HitBox());

		if (dx != 0 || dy != 0)
		{
			if (mov == CaminarDerecha || mov == CaminarIzquierda)
				IDx = (IDx + 1) % 4;

		}
		if (dx == 0 && dy == 0) {
			if (lastmov == CaminarIzquierda)
				IDx = 0;
			else
				IDx = 1;
			mov = Quieto;

		}
	}
	

};
