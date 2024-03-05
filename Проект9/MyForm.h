#pragma once

namespace Animation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		Bitmap^ bmp1;
		Image^ imageObj;
		Rectangle rectImageObj;
		Bitmap^ moveObj;
		Double i;
		Double j;
		Double f;
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			imageObj = Bitmap::FromFile("Object.png");
			bmp1 = nullptr;
			rectImageObj = Rectangle(0, 0, imageObj->Width / 5, imageObj->Height / 5);
			i = 1;
			j = 1;
			f = 0;
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pb;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;

	protected:

	protected:

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pb = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb))->BeginInit();
			this->SuspendLayout();
			// 
			// pb
			// 
			this->pb->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pb->Location = System::Drawing::Point(12, 12);
			this->pb->Name = L"pb";
			this->pb->Size = System::Drawing::Size(751, 458);
			this->pb->TabIndex = 0;
			this->pb->TabStop = false;
			// 
			// timer1
			// 
			this->timer1->Interval = 16;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(775, 482);
			this->Controls->Add(this->pb);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		if (bmp1 != nullptr) {
			restore(rectImageObj, bmp1);
		}

		if (((rectImageObj.X + imageObj->Width / 5) >= pb->Width) || ((rectImageObj.X <= 0) && (rectImageObj.Y != 0))) {
			i = -1 * i;
		}
		if (((rectImageObj.Y + imageObj->Height / 5) >= pb->Height) || ((rectImageObj.Y <= 0) && (rectImageObj.X != 0))) {
			j = -1 * j;
		}
		rectImageObj.X = rectImageObj.X + i * 7;
		rectImageObj.Y = rectImageObj.Y + j * 7;
		bmp1 = StoreImage(rectImageObj);
		moveObj->RotateFlip(RotateFlipType::Rotate90FlipNone);
		restore(rectImageObj, moveObj);
	}

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {

		pb->Image = Bitmap::FromFile("fon.jpeg");
		moveObj = gcnew Bitmap(imageObj->Width / 5, imageObj->Height / 5);
		Graphics^ g = Graphics::FromImage(moveObj);
		g->DrawImage(imageObj, rectImageObj);
		timer1->Enabled = true;
		timer1->Interval = 16;
	}

			 Bitmap^ StoreImage(Rectangle r) {
				 GraphicsUnit units = GraphicsUnit::Pixel;
				 Bitmap^ bmp = gcnew Bitmap(r.Width, r.Height);
				 Graphics^ g = Graphics::FromImage(bmp);
				 Rectangle rec = Rectangle(0, 0, r.Width, r.Height);

				 g->DrawImage(pb->Image, rec, r.X, r.Y, (r.Width), (r.Height), units);
				 return bmp;
			 }

			 void restore(Rectangle rec, Bitmap^ bmp) {
				 Graphics^ g = Graphics::FromImage(pb->Image);

				 g->DrawImage(bmp, rec);
				 pb->Invalidate();
			 }

			 void restoreR(Rectangle rec, Bitmap^ bmp) {
				 GraphicsUnit units = GraphicsUnit::Pixel;
				 Graphics^ g = Graphics::FromImage(pb->Image);
				 Rectangle rec1 = Rectangle(rec.X, rec.Y, pb->Width, pb->Height);
				 g->DrawImage(pb->Image, rec1, rec.X, rec.Y, (pb->Width), (pb->Height), units);
				 g->RotateTransform(1 * f);
				 g->DrawImage(bmp, rec);
				 pb->Invalidate();
			 }
	};
}
