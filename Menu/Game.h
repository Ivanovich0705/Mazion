#pragma once
#include "Image.h"
#include "Characters.h"
#include "Controller.h"

namespace Menu {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	public ref class Game : public System::Windows::Forms::Form{
		Controller^ game;
		short idk = 0;
	private: System::Windows::Forms::Timer^ movement_tmr;
	private: SoundPlayer^ Music;

	public:
		Game(void)
		{
			InitializeComponent();
			this->Music = gcnew SoundPlayer("Music\\Heaven_and_Hell.wav");
			this->Music->PlayLooping();
			this->game = gcnew Controller();
		}

	protected:
		
		~Game()
		{
			this->Music->Stop();
			delete this->game;
			if (components)
			{
				delete components, game;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		


#pragma region Windows Form Designer generated code
		
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->movement_tmr = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// movement_tmr
			// 
			this->movement_tmr->Enabled = true;
			this->movement_tmr->Interval = 70;
			this->movement_tmr->Tick += gcnew System::EventHandler(this, &Game::clock_Tick);
			// 
			// Game
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1440, 810);
			this->Name = L"Game";
			this->Text = L"Mazion: Escape the Labyrinth";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Game::Game_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Game::Game_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void sprite_tmr_Tick(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void movement_tmr_Tick(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void clock_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ bfc = BufferedGraphicsManager::Current;
		BufferedGraphics^ bf = bfc->Allocate(g, this->ClientRectangle);

		bf->Graphics->Clear(Color::White);
		
		if (game->CorruptsLose == true && this->idk == 0) {

			game->MostrarVentanas(g);
			idk = 1;
			this->movement_tmr->Enabled = true;
		}else game->Mover(bf->Graphics);
			
		game->Draw(bf->Graphics);
		if (game->Ganar == true) {
			this->movement_tmr->Enabled = false; 
			game->MostrarVentanas(g);
			_sleep(5000);
			this->Visible = false;
		}
		if (game->Perder == true) {
			this->movement_tmr->Enabled = false;
			game->MostrarVentanas(g);
			_sleep(5000);
			this->Visible = false;
		}
		bf->Render(g);
	}
	private: System::Void Game_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		game->MoverJugador(true, e->KeyCode);
	}
	private: System::Void Game_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		game->MoverJugador(false, e->KeyCode);
	}
	};
}
