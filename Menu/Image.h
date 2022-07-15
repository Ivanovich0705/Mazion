#pragma once
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

class Entidad
{
protected:
	int x, y;
	int dx, dy;
	int ancho, alto;

	int IDx;
public:
	Entidad(){
		x = y = 45;
		dx = dy = 0;
		ancho = alto = 0;
		IDx = 0;
	}

	int GetX(){
		return x;
	}
	int GetY(){
		return y;
	}

	int GetDX(){
		return dx;
	}
	int GetDY(){
		return dy;
	}

	int GetAncho(){
		return ancho;
	}
	int GetAlto(){
		return alto;
	}

	int GetIDx(){
		return IDx;
	}
	void SetX(int value){
		x = value;
	}
	void SetY(int value){
		y = value;
	}
	void SetDX(int value){
		dx = value;
	}
	void SetDY(int value){
		dy = value;
	}

	void SetAncho(int value){
		ancho = value;
	}
	void SetAlto(int value){
		alto = value;
	}
	System::Drawing::Rectangle Aura() {
		return System::Drawing::Rectangle(x-70, y-50, 150, 150);
	}
	System::Drawing::Rectangle Area(){
		return System::Drawing::Rectangle(x, y, 75, 75);
	}
	System::Drawing::Rectangle NextArea(){
		return System::Drawing::Rectangle(x + dx, y + dy, ancho, alto);
	}
	System::Drawing::Rectangle HitBox() {
		double alfa = 0.5;
		return System::Drawing::Rectangle(x + 15 + dx, y + 38 + dy, 43, 33);
	}
	System::Drawing::Rectangle HitBoxDX(){
		double alfa = 0.5; 
		return System::Drawing::Rectangle(x + 15 + dx, y + 38, 43, 33);
	}
	System::Drawing::Rectangle HitBoxDY() {
		double alfa = 0.5; 
		return System::Drawing::Rectangle(x + 15, y + 38 + dy, 43, 33);
	}
	
	virtual void Mover(Graphics^ g){
		x += dx;
		y += dy;
	}

	virtual void Draw(Graphics^ g, Bitmap^ img, Bitmap^ imgHP){
		g->FillRectangle(Brushes::Black, x, y, ancho, alto);
	}
};