#pragma once
#include "Animaciones.h"
#include "Game.h"
namespace Menu {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;


	public ref class MyForm : public System::Windows::Forms::Form
	{
		Graphics^ graficador;
		BufferedGraphics^ buffer;
	private: System::Windows::Forms::Timer^ tim_animador;
	private: System::Windows::Forms::Timer^ timer1;
	private: SoundPlayer^ Music;
		   Animaciones^ menu;

		   bool InstOpen = false;
		   
	public:
		MyForm(void)
		{
			InitializeComponent();
			this->graficador = this->CreateGraphics();
			this->buffer = BufferedGraphicsManager::Current->Allocate(this->graficador, this->ClientRectangle);
			this->menu = gcnew Animaciones(this->ClientRectangle);
			this->Music = gcnew SoundPlayer("Music\\EtherOar.wav");
			this->Music->PlayLooping();
		}

	protected:

		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		this->Music->Stop();
		}


	protected:











	private: System::Windows::Forms::Button^ btt_instruccionesaparecer;
	private: System::Windows::Forms::Button^ btt_regresar;





	private: System::Windows::Forms::Button^ btt_jugar;

	private: System::ComponentModel::IContainer^ components;









	private:
	


#pragma region Windows Form Designer generated code
	
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->btt_instruccionesaparecer = (gcnew System::Windows::Forms::Button());
			this->btt_regresar = (gcnew System::Windows::Forms::Button());
			this->btt_jugar = (gcnew System::Windows::Forms::Button());
			this->tim_animador = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// btt_instruccionesaparecer
			// 
			this->btt_instruccionesaparecer->BackColor = System::Drawing::Color::Chocolate;
			this->btt_instruccionesaparecer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btt_instruccionesaparecer->ForeColor = System::Drawing::Color::White;
			this->btt_instruccionesaparecer->Location = System::Drawing::Point(347, 415);
			this->btt_instruccionesaparecer->Name = L"btt_instruccionesaparecer";
			this->btt_instruccionesaparecer->Size = System::Drawing::Size(186, 28);
			this->btt_instruccionesaparecer->TabIndex = 12;
			this->btt_instruccionesaparecer->Text = L"INSTRUCCIONES";
			this->btt_instruccionesaparecer->UseVisualStyleBackColor = false;
			this->btt_instruccionesaparecer->Click += gcnew System::EventHandler(this, &MyForm::btt_instruccionesaparecer_Click);
			// 
			// btt_regresar
			// 
			this->btt_regresar->BackColor = System::Drawing::Color::Transparent;
			this->btt_regresar->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btt_regresar.Image")));
			this->btt_regresar->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->btt_regresar->Location = System::Drawing::Point(900-76, 600-56);
			this->btt_regresar->Name = L"btt_regresar";
			this->btt_regresar->Size = System::Drawing::Size(76, 56);
			this->btt_regresar->TabIndex = 11;
			this->btt_regresar->UseVisualStyleBackColor = false;
			this->btt_regresar->Visible = false;
			this->btt_regresar->Click += gcnew System::EventHandler(this, &MyForm::btt_instrucciones_Click);
			// 
			// btt_jugar
			// 
			this->btt_jugar->BackColor = System::Drawing::Color::Goldenrod;
			this->btt_jugar->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btt_jugar->ForeColor = System::Drawing::Color::White;
			this->btt_jugar->Location = System::Drawing::Point(347, 362);
			this->btt_jugar->Name = L"btt_jugar";
			this->btt_jugar->Size = System::Drawing::Size(186, 28);
			this->btt_jugar->TabIndex = 13;
			this->btt_jugar->Text = L"JUGAR";
			this->btt_jugar->UseVisualStyleBackColor = false;
			this->btt_jugar->Click += gcnew System::EventHandler(this, &MyForm::btt_jugar_Click);
			// 
			// tim_animador
			// 
			this->tim_animador->Enabled = true;
			this->tim_animador->Interval = 200;
			this->tim_animador->Tick += gcnew System::EventHandler(this, &MyForm::tim_animador_Tick);
			// 
			// timer1
			// 
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(900, 600);
			this->Controls->Add(this->btt_instruccionesaparecer);
			this->Controls->Add(this->btt_jugar);
			this->Controls->Add(this->btt_regresar);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->Text = L"Mazion: Escape the Labyrinth";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void btt__Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void btt_instrucciones_Click(System::Object^ sender, System::EventArgs^ e) {
	
	this->menu->jugar(this->buffer->Graphics);
	this->buffer->Render();
	this->InstOpen = false;
	this->btt_regresar->Visible = false;
	this->btt_instruccionesaparecer->Visible = true;
	this->btt_jugar->Visible = true;
	
}
private: System::Void btt_instruccionesaparecer_Click(System::Object^ sender, System::EventArgs^ e) {
	this->btt_instruccionesaparecer->Visible = true;
	this->InstOpen = true;
	this->btt_regresar->Visible = true;
	this->btt_instruccionesaparecer->Visible = false;
	this->btt_jugar->Visible = false;
	this->graficador = this->CreateGraphics();
	this->buffer = BufferedGraphicsManager::Current->Allocate(this->graficador, this->ClientRectangle);
	this->menu = gcnew Animaciones(this->ClientRectangle);
}
private: System::Void pictureBox4_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void btt_jugar_Click(System::Object^ sender, System::EventArgs^ e) {
	//aqui se iniciaria el juego
	Game^ frm = gcnew Game();
	this->Visible = false;
	frm->ShowDialog();
	this->Visible = true;
	

}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pictureBox2_Click(System::Object^ sender, System::EventArgs^ e) {
	
}
private: System::Void tim_animador_Tick(System::Object^ sender, System::EventArgs^ e) {
	if (this->InstOpen == true) {
		this->menu->jugar(this->buffer->Graphics);
		this->buffer->Render();
	}
	else {
		this->menu->dibujar_fondo(this->buffer->Graphics);
		this->buffer->Render();
	}
}
private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
}
};
}
