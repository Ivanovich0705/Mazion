#pragma once
#include "Characters.h"
#include "Enemigos.h"
#include "Maze.h"
#include "Image.h"
#include "Portales.h"
#include <vector>
#include <conio.h>

ref class Controller {//clase controladora
private:
	//creas el objeto
	PlayerC* jugador;
	Corrupts* corrupts;
	Allys* allys;
	Assasins* assasins;
	Portals* portales;
	Maze* maze;
	
	//creas la imagen para usarla en el objeto
	Bitmap^ imgJugador;
	Bitmap^ imgCorrupt;
	Bitmap^ imgAlly;
	Bitmap^ imgAssasin;
	Bitmap^ imgAllyCorrupted;
	Bitmap^ imgWall;
	Bitmap^ imgGround;
	Bitmap^ imgPortal;
	Bitmap^ imgFlag;
	Bitmap^ imgWin;
	Bitmap^ imgLose;
	Bitmap^ waiting;
	Bitmap^ imgHP;
	Bitmap^ imgCorruptIdle;
	Bitmap^ imgAssassinIdle;

	Random x;
	int velCorrupt = x.Next(4, 6);
	Random y;
	int velAssasin = y.Next(3, 9);
	//contadores a usar
	int coolDown;
	short NumAli = 10;
	short NumCorrupt = (NumAli * 4) / 10;
	short NumAssasin = (NumAli * 6) / 10;
	int tiempoInicio;
public:
	//bools para poder mostrar ventanas de ganar o perder
	bool Ganar = false;
	bool Perder = false;
	bool CorruptsLose = false;
	Controller() {
		
		
		imgJugador = gcnew Bitmap("Sprites/mc_all.png");
		imgCorrupt = gcnew Bitmap("Sprites/corrupt_all.png");
		imgAlly = gcnew Bitmap("Sprites/ally_all.png");
		imgAssasin = gcnew Bitmap("Sprites/assassin_all.png");
		imgAllyCorrupted = gcnew Bitmap("Sprites/corrupted_all.png");
		imgCorruptIdle  =gcnew Bitmap("Sprites/corrupt_idle.png");
		imgAssassinIdle	=gcnew Bitmap("Sprites/assassin_idle.png");
		imgWall = gcnew Bitmap("Sprites/Wall.png");
		imgGround = gcnew Bitmap("Sprites/Ground.png");
		imgPortal = gcnew Bitmap("Sprites/portal_all.png");
		imgFlag = gcnew Bitmap("Sprites/Flag.png");
		imgWin = gcnew Bitmap("Sprites/YouWinM.png");
		imgLose = gcnew Bitmap("Sprites/YouLoseM.png");
		waiting = gcnew Bitmap("Sprites/waiting.png");
		imgHP = gcnew Bitmap ("Sprites/hp_all.png");
		maze = new Maze();

		jugador = new PlayerC(imgJugador);
		corrupts = new Corrupts(NumCorrupt, imgCorrupt, maze);
		allys = new Allys(NumAli, imgAlly, maze);
		assasins = new Assasins(NumAssasin, imgAssasin, maze);
		portales = new Portals(imgPortal, maze, jugador);

		this->jugador->SetLastmov(CaminarDerecha);
		
		coolDown = 0;
		tiempoInicio = clock();
		
	}
	~Controller() {
		delete jugador;
		delete corrupts, allys, assasins, maze, portales;
		delete imgJugador;
		delete imgCorrupt;
		delete imgAlly;
		delete imgAssasin;
		delete imgAllyCorrupted;
		delete imgCorruptIdle;
		delete imgAssassinIdle;
		delete imgWall;
		delete imgGround;
		delete imgPortal;
		delete imgFlag;
		delete imgWin;
		delete imgLose;
		delete waiting;
		delete imgHP;
	}


	void MoverJugador(bool accion, Keys tecla)//se recibe la tecla detectada y se le da una dx o dy al personaje
	{
		if (accion == true)
		{
			if (tecla == Keys::Up && jugador->GetLastmov() == CaminarDerecha)
			{
				jugador->SetDY(-15);
				jugador->SetAccion(CaminarDerecha);
				jugador->SetLastmov(CaminarDerecha);
			}
			else if (tecla == Keys::Up && jugador->GetLastmov() == CaminarIzquierda)
			{
				jugador->SetDY(-15);
				jugador->SetAccion(CaminarIzquierda);
				jugador->SetLastmov(CaminarIzquierda);
			}
			else if (tecla == Keys::Down && jugador->GetLastmov() == CaminarIzquierda)
			{
				jugador->SetDY(15);
				jugador->SetAccion(CaminarIzquierda);
				jugador->SetLastmov(CaminarIzquierda);
			}
			else if (tecla == Keys::Down && jugador->GetLastmov() == CaminarDerecha)
			{
				jugador->SetDY(15);
				jugador->SetAccion(CaminarDerecha);
				jugador->SetLastmov(CaminarDerecha);
			}
			else if (tecla == Keys::Left)
			{
				jugador->SetDX(-15);
				jugador->SetAccion(CaminarIzquierda);
				jugador->SetLastmov(CaminarIzquierda);
			}
			else if (tecla == Keys::Right)
			{
				jugador->SetDX(15);
				jugador->SetAccion(CaminarDerecha);
				jugador->SetLastmov(CaminarDerecha);
			}
		}
		else//al soltar la tecla se setea en 0 el movimiento
		{
			if (tecla == Keys::Up)
				jugador->SetDY(0);
			else if (tecla == Keys::Down)
				jugador->SetDY(0);
			else if (tecla == Keys::Left)
				jugador->SetDX(0);
			else if (tecla == Keys::Right)
				jugador->SetDX(0);
		}
	}
	
	void Perseguir() {
		
		for (int i = 0; i < corrupts->corrupts.size(); i++) {
			
			if (allys->allies[corrupts->corrupts[i]->GetPresa()]->GetX() - corrupts->corrupts[i]->GetX() < 0) {
				corrupts->corrupts[i]->SetDX(-velCorrupt);
				corrupts->corrupts[i]->SetAccion(cCaminarIzquierda);
				corrupts->corrupts[i]->SetLastmov(cCaminarIzquierda);
			}
			else if (allys->allies[corrupts->corrupts[i]->GetPresa()]->GetX() - corrupts->corrupts[i]->GetX() > 0) {
				corrupts->corrupts[i]->SetDX(+velCorrupt);
				corrupts->corrupts[i]->SetAccion(cCaminarDerecha);
				corrupts->corrupts[i]->SetLastmov(cCaminarDerecha);
			}
			if (allys->allies[corrupts->corrupts[i]->GetPresa()]->GetY() - corrupts->corrupts[i]->GetY() < 0) {
			corrupts->corrupts[i]->SetDY(-velCorrupt);
			}
			else if (allys->allies[corrupts->corrupts[i]->GetPresa()]->GetY() - corrupts->corrupts[i]->GetY() > 0) {
			corrupts->corrupts[i]->SetDY(+velCorrupt);
			}

		}
		/*for (int i = 0; i < allys->allies.size(); i++) {
			for (int j = 0; j < corrupts->corrupts.size(); j++) {

				if (corrupts->corrupts[j]->HitBox().IntersectsWith(allys->allies[i]->Aura()))
					corrupts->corrupts[j]->SetPresa(i);
				else
					corrupts->corrupts[j]->SetPresa(0);
			}
		}*/
		/*for (int i = 0; i < corrupts->corrupts.size(); i++) {

			if (jugador->GetX() - corrupts->corrupts[i]->GetX() < 0) {
				corrupts->corrupts[i]->SetDX(-velCorrupt);
				corrupts->corrupts[i]->SetAccion(cCaminarIzquierda);
				corrupts->corrupts[i]->SetLastmov(cCaminarIzquierda);
			}
			else if (jugador->GetX() - corrupts->corrupts[i]->GetX() > 0) {
				corrupts->corrupts[i]->SetDX(+velCorrupt);
				corrupts->corrupts[i]->SetAccion(cCaminarDerecha);
				corrupts->corrupts[i]->SetLastmov(cCaminarDerecha);
			}
			if (jugador->GetY() - corrupts->corrupts[i]->GetY() < 0) {
				corrupts->corrupts[i]->SetDY(-velCorrupt);
			}
			else if (jugador->GetY() - corrupts->corrupts[i]->GetY() > 0) {
				corrupts->corrupts[i]->SetDY(+velCorrupt);
			}

		}*/
		if (allys->allies.size() > 2)
			for (int i = 0; i < 2; i++) {
				if (jugador->GetX() - allys->allies[i]->GetX() < 0) {
					allys->allies[i]->SetDX(-5);
					allys->allies[i]->SetAccion(cCaminarIzquierda);
					allys->allies[i]->SetLastmov(cCaminarIzquierda);
				}
				else if (jugador->GetX() - allys->allies[i]->GetX() > 0) {
					allys->allies[i]->SetDX(+5);
					allys->allies[i]->SetAccion(cCaminarDerecha);
					allys->allies[i]->SetLastmov(cCaminarDerecha);
				}
				if (jugador->GetY() - allys->allies[i]->GetY() < 0) {
					allys->allies[i]->SetDY(-5);
				}
				else if (jugador->GetY() - allys->allies[i]->GetY() > 0) {
					allys->allies[i]->SetDY(+5);
				}
			}
		else if(allys->allies.size() <= 2)
			for (short i = allys->allies.size() - 1; i >= 0; i--) {
				if (jugador->GetX() - allys->allies[i]->GetX() < 0) {
					allys->allies[i]->SetDX(-5);
					allys->allies[i]->SetAccion(cCaminarIzquierda);
					allys->allies[i]->SetLastmov(cCaminarIzquierda);
				}
				else if (jugador->GetX() - allys->allies[i]->GetX() > 0) {
					allys->allies[i]->SetDX(+5);
					allys->allies[i]->SetAccion(cCaminarDerecha);
					allys->allies[i]->SetLastmov(cCaminarDerecha);
				}
				if (jugador->GetY() - allys->allies[i]->GetY() < 0) {
					allys->allies[i]->SetDY(-5);
				}
				else if (jugador->GetY() - allys->allies[i]->GetY() > 0) {
					allys->allies[i]->SetDY(+5);
				}
			}
		for (int i = 0; i < assasins->assasins.size(); i++) {
			if (jugador->GetX() - assasins->assasins[i]->GetX() < 0) {
				assasins->assasins[i]->SetDX(-velAssasin);
				assasins->assasins[i]->SetAccion(cCaminarIzquierda);
				assasins->assasins[i]->SetLastmov(cCaminarIzquierda);
			}
			else if (jugador->GetX() - assasins->assasins[i]->GetX() > 0) {
				assasins->assasins[i]->SetDX(+velAssasin);
				assasins->assasins[i]->SetAccion(cCaminarDerecha);
				assasins->assasins[i]->SetLastmov(cCaminarDerecha);
			}
			if (jugador->GetY() - assasins->assasins[i]->GetY() < 0) {
				assasins->assasins[i]->SetDY(-velAssasin);
			}
			else if (jugador->GetY() - assasins->assasins[i]->GetY() > 0) {
				assasins->assasins[i]->SetDY(+velAssasin);
			}

		}
		/*for (int i = allys->allies.size() - 1; i >= 0; i--) {
			for (int j = corrupts->corrupts.size()-1; j >= 0; j--) {

					if (corrupts->corrupts[j]->HitBox().IntersectsWith(allys->allies[i]->Aura()))
						corrupts->corrupts[j]->SetPresa(i);

			}
		}*/
	}
	void ValidarMovimiento(Graphics^ g) {
		int SIZE = 45;
		short X = 0;
		short Y = 0;
		for (int i = 0; i < 18; i++)
		{
			X = 0;
			for (int j = 0; j < 32; j++) {
				System::Drawing::Rectangle wall = System::Drawing::Rectangle(X, Y, 45, 45);
				if (maze->Fondo[i][j] == 1) {
					if (jugador->HitBoxDX().IntersectsWith(wall)) jugador->SetDX(0);
					if (jugador->HitBoxDY().IntersectsWith(wall)) jugador->SetDY(0);
					for (short i = 0; i < corrupts->corrupts.size(); i++) {//validar movimiento para corrupts
						if (corrupts->corrupts[i]->HitBoxDX().IntersectsWith(wall)) corrupts->corrupts[i]->SetDX(0);
						if (corrupts->corrupts[i]->HitBoxDY().IntersectsWith(wall)) corrupts->corrupts[i]->SetDY(0);
						if (corrupts->corrupts[i]->HitBoxDY().IntersectsWith(wall) && 
							corrupts->corrupts[i]->HitBoxDX().IntersectsWith(wall)) corrupts->corrupts[i]->Setmov(cQuieto);
						if (i > 0)
							corrupts->corrupts[i]->Colisiona_con(corrupts->corrupts[i - 1]);
					}
					if (allys->allies.size() > 2)
						for (short i = 0; i < 2; i++) {//validar movimiento para aliados
							if (allys->allies.at(i)->HitBoxDX().IntersectsWith(wall)) allys->allies.at(i)->SetDX(0);
							if (allys->allies.at(i)->HitBoxDY().IntersectsWith(wall)) allys->allies.at(i)->SetDY(0);
							if (allys->allies.at(i)->HitBoxDY().IntersectsWith(wall) 
								&& allys->allies.at(i)->HitBoxDX().IntersectsWith(wall)) allys->allies[i]->Setmov(cQuieto);
							if (i > 0)
								allys->allies.at(i)->Colisiona_con(allys->allies[i - 1]);
						}
					else if(allys->allies.size() <= 2)
						for (short i = allys->allies.size() - 1; i >=0; i--) {//validar movimiento para aliados
							if (allys->allies.at(i)->HitBoxDX().IntersectsWith(wall)) allys->allies.at(i)->SetDX(0);
							if (allys->allies.at(i)->HitBoxDY().IntersectsWith(wall)) allys->allies.at(i)->SetDY(0);
							if (allys->allies.at(i)->HitBoxDY().IntersectsWith(wall) 
								&& allys->allies.at(i)->HitBoxDX().IntersectsWith(wall)) allys->allies[i]->Setmov(cQuieto);
							if (i > 0)
								allys->allies.at(i)->Colisiona_con(allys->allies[i - 1]);
						}
					if (allys->allies.size() > 2)
						for (short i = allys->allies.size()-1; i >= 2; i--) {//validar movimiento para aliados
							if (allys->allies.at(i)->HitBoxDX().IntersectsWith(wall)) {
							allys->allies.at(i)->SetDX(allys->allies[i]->GetDX() * -1);
								if (allys->allies.at(i)->Getmov() == cCaminarDerecha)allys->allies.at(i)->SetAccion(cCaminarIzquierda); else allys->allies.at(i)->SetAccion(cCaminarDerecha);
							};
							if (allys->allies[i]->HitBoxDY().IntersectsWith(wall)) allys->allies[i]->SetDY(allys->allies[i]->GetDY() * -1);
							if (allys->allies[i]->HitBoxDY().IntersectsWith(wall) && allys->allies[i]->HitBoxDX().IntersectsWith(wall)) allys->allies[i]->Setmov(cQuieto);
							if (i > 0)
							allys->allies[i]->Colisiona_con(allys->allies[i - 1]);
						}
					for (short i = 0; i < assasins->assasins.size(); i++) {//validar movimiento para assasin
						if (assasins->assasins[i]->HitBoxDX().IntersectsWith(wall)) assasins->assasins[i]->SetDX(0);
						if (assasins->assasins[i]->HitBoxDY().IntersectsWith(wall)) assasins->assasins[i]->SetDY(0);
						if (assasins->assasins[i]->HitBoxDY().IntersectsWith(wall) && assasins->assasins[i]->HitBoxDX().IntersectsWith(wall)) assasins->assasins[i]->Setmov(cQuieto);
						if (i > 0)
							assasins->assasins[i]->Colisiona_con(assasins->assasins[i - 1]);
					}
				}
				X += SIZE;
			}
			Y += SIZE;
		}

	}
	void Mover(Graphics^ g) {
		ValidarMovimiento(g);
		jugador->Mover(g);
		allys->Mover(g);
		if (assasins->Eliminar(jugador->HitBox()) == true && clock() - coolDown >= 1000 && CorruptsLose == true) {
			portales->CrearPortal(imgPortal, jugador, maze);
			jugador->SetVidas(-1);
			coolDown = clock();
		}
		for (unsigned int i = 0; i < corrupts->corrupts.size(); i++) {
			if (clock() >= 5000) {
				if (allys->Eliminar(corrupts->corrupts.at(i)->HitBox())) {
					corrupts->corrupts.at(i)->SetTransformed(true);
					corrupts->Transformado++;
				}
			}
		}
		if (jugador->GetVidas() == 0) Perder = true;
		if (clock()-tiempoInicio >= 35000) CorruptsLose = true;
		if (corrupts->Transformado == this->NumAli-1) Perder = true;
		if (jugador->HitBox().IntersectsWith(maze->getEndFlag()))
			Ganar = true;
		if (CorruptsLose == false) corrupts->Mover(g);
		if (CorruptsLose == true) assasins->Mover(g);
		

	}
	void MostrarVentanas(Graphics^ g) {
		
		int letra = 25;
		int tiempoLetra = 3000;
		if (Ganar == true) g->DrawImage(imgWin, System::Drawing::Rectangle(335, 135, 700, 500));
		if (Perder == true) g->DrawImage(imgLose, System::Drawing::Rectangle(355, 135, 700, 500));
		if (CorruptsLose == true && Perder == false && clock() - tiempoInicio <= 35000) {//ventana de negociacion
			g->FillRectangle(Brushes::DimGray, 0, 0, 1440, 800);
			g->DrawImage(imgCorruptIdle, System::Drawing::Rectangle(240, 100, 400, 400));
			g->DrawImage(imgAssassinIdle, System::Drawing::Rectangle(815, 100, 400, 400));
			g->DrawString("Ese tipo quiere problemas", gcnew Font("Arial", letra), Brushes::WhiteSmoke, 240, 550);
			_sleep(tiempoLetra);
			g->FillRectangle(Brushes::DimGray, 0, 0, 1440, 800);
			g->DrawImage(imgCorruptIdle, System::Drawing::Rectangle(240, 100, 400, 400));
			g->DrawImage(imgAssassinIdle, System::Drawing::Rectangle(815, 100, 400, 400));
			g->DrawString("Pues ahora escuchará nuestro lema", gcnew Font("Arial", letra), Brushes::Red, 780, 550);
			_sleep(tiempoLetra);
			g->FillRectangle(Brushes::DimGray, 0, 0, 1440, 800);
			g->DrawImage(imgCorruptIdle, System::Drawing::Rectangle(240, 100, 400, 400));
			g->DrawImage(imgAssassinIdle, System::Drawing::Rectangle(815, 100, 400, 400));
			g->DrawString("Para traerle al mundo devastación...", gcnew Font("Arial", letra), Brushes::WhiteSmoke, 200, 550);
			_sleep(tiempoLetra);
			g->FillRectangle(Brushes::DimGray, 0, 0, 1440, 800);
			g->DrawImage(imgCorruptIdle, System::Drawing::Rectangle(240, 100, 400, 400));
			g->DrawImage(imgAssassinIdle, System::Drawing::Rectangle(815, 100, 400, 400));
			g->DrawString("Y dar a los corazones desesperación...", gcnew Font("Arial", letra), Brushes::Red, 780, 550);
			_sleep(tiempoLetra);
			g->FillRectangle(Brushes::DimGray, 0, 0, 1440, 800);
			g->DrawImage(imgCorruptIdle, System::Drawing::Rectangle(240, 100, 400, 400));
			g->DrawImage(imgAssassinIdle, System::Drawing::Rectangle(815, 100, 400, 400));
			g->DrawString("¡Para pelear infundiendo odio y temor!", gcnew Font("Arial", letra), Brushes::WhiteSmoke, 180, 550);
			_sleep(tiempoLetra);
			g->FillRectangle(Brushes::DimGray, 0, 0, 1440, 800);
			g->DrawImage(imgCorruptIdle, System::Drawing::Rectangle(240, 100, 400, 400));
			g->DrawImage(imgAssassinIdle, System::Drawing::Rectangle(815, 100, 400, 400));
			g->DrawString("¡Para expandir nuestro imperio", gcnew Font("Arial", letra), Brushes::Red, 780, 550);
			g->DrawString("hasta el espacio exterior!", gcnew Font("Arial", letra), Brushes::Red, 810,590);
			_sleep(tiempoLetra);
			g->FillRectangle(Brushes::DimGray, 0, 0, 1440, 800);
			g->DrawImage(imgCorruptIdle, System::Drawing::Rectangle(240, 100, 400, 400));
			g->DrawImage(imgAssassinIdle, System::Drawing::Rectangle(815, 100, 400, 400));
			g->DrawString("¡Corrupt!", gcnew Font("Arial", letra), Brushes::WhiteSmoke, 350, 550);
			_sleep(tiempoLetra);
			g->FillRectangle(Brushes::DimGray, 0, 0, 1440, 800);
			g->DrawImage(imgCorruptIdle, System::Drawing::Rectangle(240, 100, 400, 400));
			g->DrawImage(imgAssassinIdle, System::Drawing::Rectangle(815, 100, 400, 400));
			g->DrawString("¡Assassin! ", gcnew Font("Arial", letra), Brushes::Red, 925, 550);
			_sleep(tiempoLetra);
			g->FillRectangle(Brushes::DimGray, 0, 0, 1440, 800);
			g->DrawImage(imgCorruptIdle, System::Drawing::Rectangle(240, 100, 400, 400));
			g->DrawImage(imgAssassinIdle, System::Drawing::Rectangle(815, 100, 400, 400));
			g->DrawString("¡La oscuridad viajando a ", gcnew Font("Arial", letra), Brushes::WhiteSmoke, 260, 550);
			g->DrawString("la velocidad de la luz!", gcnew Font("Arial", letra), Brushes::WhiteSmoke, 280, 590);
			_sleep(tiempoLetra);
			g->FillRectangle(Brushes::DimGray, 0, 0, 1440, 800);
			g->DrawImage(imgCorruptIdle, System::Drawing::Rectangle(240, 100, 400, 400));
			g->DrawImage(imgAssassinIdle, System::Drawing::Rectangle(815, 100, 400, 400));
			g->DrawString("Ríndanse ahora o prepárense para luchar", gcnew Font("Arial", letra), Brushes::Red, 750, 550);
			_sleep(tiempoLetra);
			Draw(g);

		}
	}

	void Draw(Graphics^ g)
	{
		maze->dibujar(g, imgWall, imgGround, imgFlag);
		portales->Teletransport(g, imgPortal, jugador, maze);
		if (CorruptsLose == false) corrupts->Draw(g, imgCorrupt, imgAllyCorrupted);
		allys->Draw(g, imgAlly);
		if (CorruptsLose == true) assasins->Draw(g, imgAssasin);
		jugador->Draw(g, imgJugador, imgHP);
		Perseguir();

	}

};