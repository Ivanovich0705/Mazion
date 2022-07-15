#pragma once
#include <Windows.h>
#include <MMSystem.h>
using namespace System;
using namespace System::Drawing;



ref class CGrafico abstract {
protected:
	System::Drawing::Rectangle area_dibujo;
	short dx, dy;
public:
	CGrafico(System::Drawing::Rectangle area_dibujo)
		: area_dibujo(area_dibujo) {}
	virtual void dibujar(Graphics^ graficador) abstract;
};

ref class CImagen : public CGrafico {
protected:
	Bitmap^ imagen;
public:
	CImagen(String^ ruta, System::Drawing::Rectangle area_dibujo)
		: CGrafico(area_dibujo) {
		this->imagen = gcnew Bitmap(ruta);
	}
	~CImagen() {
		delete this->imagen;
	}
	void dibujar(Graphics^ graficador) override {
		graficador->DrawImage(this->imagen, this->area_dibujo);
	}
	short get_ancho() { return this->imagen->Width; }
};


ref class CSprite : public CImagen {
	short n_filas;
	short n_columnas;
	short n_subimagenes;
	short indice;
public:
	CSprite(String^ ruta, System::Drawing::Rectangle area_dibujo, short n_f, short n_c, short n_subi)
		: CImagen(ruta, area_dibujo), n_filas(n_f), n_columnas(n_c), n_subimagenes(n_subi), indice(0) {
	}
	void dibujar(Graphics^ graficador) override {
		System::Drawing::Rectangle area_recorte = calcular_area_recorte();
		graficador->DrawImage(this->imagen, this->area_dibujo, area_recorte, GraphicsUnit::Pixel);
		++indice %= n_subimagenes;
	}
private:
	System::Drawing::Rectangle calcular_area_recorte() {
		short ancho_subimagen = this->imagen->Width / this->n_columnas;
		short alto_subimagen = this->imagen->Height / this->n_filas;
		short x = this->indice % this->n_columnas * ancho_subimagen;
		short y = this->indice / this->n_columnas * alto_subimagen;
		return System::Drawing::Rectangle(x, y, ancho_subimagen, alto_subimagen);
	}
};

ref class Animaciones {
	CImagen^ fondo;
	CImagen^ title;
	CImagen^ nombres;
	CSprite^ mc;
	CSprite^ ally;
	CSprite^ assasin;
	CSprite^ corrupt;
	CSprite^ portal;
	CSprite^ torch1;
	CSprite^ torch2;
	
public:
	Animaciones(System::Drawing::Rectangle area_dibujo) {
		this->fondo = gcnew CImagen("Sprites\\Fondo.png", System::Drawing::Rectangle(0, 0, 900, 600));
		this->title = gcnew CImagen("Sprites\\mazion_title.png", System::Drawing::Rectangle(450 - 240, 100, 480, 246));
		this->nombres = gcnew CImagen("Sprites\\Fondo_nombres.jpg", System::Drawing::Rectangle(0, 0, 900, 600));
		this->mc = gcnew CSprite("Sprites\\mc_menu.png", System::Drawing::Rectangle(125, 100, 100, 100), 2, 4, 8);
		this->ally = gcnew CSprite("Sprites\\ally_menu.png", System::Drawing::Rectangle(125, 270, 100, 100), 2, 4, 8);
		this->corrupt = gcnew CSprite("Sprites\\corrupt_menu.png", System::Drawing::Rectangle(380, 270, 100, 100), 2, 4, 8);
		this->assasin = gcnew CSprite("Sprites\\assassin_menu.png", System::Drawing::Rectangle(380, 480, 100, 100), 2, 4, 8);
		this->portal = gcnew CSprite("Sprites\\portal_all.png", System::Drawing::Rectangle(100, 450, 150, 150), 1, 4, 4);
		this->torch1 = gcnew CSprite("Sprites\\torch_all.png", System::Drawing::Rectangle(450 - 93 - 100, 352, 100, 100), 2, 2, 4);
		this->torch2 = gcnew CSprite("Sprites\\torch_all.png", System::Drawing::Rectangle(450 + 93, 352, 100, 100), 2, 2, 4);
	}
	~Animaciones() {
	}
	bool jugar(Graphics^ graficador) {
		this->renderizar(graficador);
		return true;
	}
	bool dibujar_fondo(Graphics^ graficador) {
		this->fondo->dibujar(graficador);
		this->title->dibujar(graficador);
		this->torch1->dibujar(graficador);
		this->torch2->dibujar(graficador);
		return true;
	}
private:
	void renderizar(Graphics^ graficador) {
		this->nombres->dibujar(graficador);
		this->mc->dibujar(graficador);
		this->ally->dibujar(graficador);
		this->assasin->dibujar(graficador);
		this->corrupt->dibujar(graficador);
		this->portal->dibujar(graficador);
	}
	
};
