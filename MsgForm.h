#pragma once

namespace AEGP_Template {

	/// <summary>
	/// MsgForm の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class MsgForm : public System::Windows::Forms::Form
	{
	public:
        MsgForm( System::Void );

		static bool IsStopRequest;
        bool    IsRunning;
        bool    IsError;
        bool    IsWarning;
        System::String ^    RunningFileName;

    protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MsgForm();

	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>

    private: System::ComponentModel::IContainer^  components;
    private: System::Windows::Forms::TabControl^  tabControl1;
    private: System::Windows::Forms::TabPage^  tabPage1;
    private: System::Windows::Forms::TabPage^  tabPage2;
    private: System::Windows::Forms::RichTextBox^  textB_Msg;
    private: System::Windows::Forms::RichTextBox^  textB_Err;
    private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::ProgressBar^  progressBar2;
	private: System::Windows::Forms::Button^  button_OK;
    private: System::Windows::Forms::Button^  button_Cancel;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MsgForm::typeid));
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->textB_Msg = (gcnew System::Windows::Forms::RichTextBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->textB_Err = (gcnew System::Windows::Forms::RichTextBox());
			this->progressBar2 = (gcnew System::Windows::Forms::ProgressBar());
			this->button_Cancel = (gcnew System::Windows::Forms::Button());
			this->button_OK = (gcnew System::Windows::Forms::Button());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->SuspendLayout();
			// 
			// progressBar1
			// 
			this->progressBar1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->progressBar1->Location = System::Drawing::Point(3, 360);
			this->progressBar1->Maximum = 65536;
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(606, 18);
			this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->progressBar1->TabIndex = 1;
			// 
			// tabControl1
			// 
			this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->ItemSize = System::Drawing::Size(80, 20);
			this->tabControl1->Location = System::Drawing::Point(3, 3);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(606, 351);
			this->tabControl1->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->textB_Msg);
			this->tabPage1->Location = System::Drawing::Point(4, 24);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(598, 323);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"出力";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// textB_Msg
			// 
			this->textB_Msg->BackColor = System::Drawing::SystemColors::Window;
			this->textB_Msg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textB_Msg->Font = (gcnew System::Drawing::Font(L"ＭＳ 明朝", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->textB_Msg->HideSelection = false;
			this->textB_Msg->Location = System::Drawing::Point(3, 3);
			this->textB_Msg->Name = L"textB_Msg";
			this->textB_Msg->ReadOnly = true;
			this->textB_Msg->Size = System::Drawing::Size(592, 317);
			this->textB_Msg->TabIndex = 0;
			this->textB_Msg->Text = L"";
			this->textB_Msg->WordWrap = false;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->textB_Err);
			this->tabPage2->Location = System::Drawing::Point(4, 24);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(598, 323);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"エラー一覧";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// textB_Err
			// 
			this->textB_Err->BackColor = System::Drawing::SystemColors::Window;
			this->textB_Err->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textB_Err->Font = (gcnew System::Drawing::Font(L"ＭＳ 明朝", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->textB_Err->HideSelection = false;
			this->textB_Err->Location = System::Drawing::Point(3, 3);
			this->textB_Err->Name = L"textB_Err";
			this->textB_Err->ReadOnly = true;
			this->textB_Err->Size = System::Drawing::Size(592, 317);
			this->textB_Err->TabIndex = 2;
			this->textB_Err->Text = L"";
			this->textB_Err->WordWrap = false;
			// 
			// progressBar2
			// 
			this->progressBar2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->progressBar2->Location = System::Drawing::Point(3, 384);
			this->progressBar2->Maximum = 65536;
			this->progressBar2->Name = L"progressBar2";
			this->progressBar2->Size = System::Drawing::Size(606, 18);
			this->progressBar2->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->progressBar2->TabIndex = 2;
			// 
			// button_Cancel
			// 
			this->button_Cancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button_Cancel->Enabled = false;
			this->button_Cancel->Location = System::Drawing::Point(534, 408);
			this->button_Cancel->Name = L"button_Cancel";
			this->button_Cancel->Size = System::Drawing::Size(75, 23);
			this->button_Cancel->TabIndex = 4;
			this->button_Cancel->Tag = L"Cancel";
			this->button_Cancel->Text = L"Cancel";
			this->button_Cancel->UseVisualStyleBackColor = true;
			this->button_Cancel->Click += gcnew System::EventHandler(this, &MsgForm::button_Cancel_Click);
			// 
			// button_OK
			// 
			this->button_OK->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button_OK->Location = System::Drawing::Point(453, 408);
			this->button_OK->Name = L"button_OK";
			this->button_OK->Size = System::Drawing::Size(75, 23);
			this->button_OK->TabIndex = 3;
			this->button_OK->Tag = L"OK";
			this->button_OK->Text = L"OK";
			this->button_OK->UseVisualStyleBackColor = true;
			this->button_OK->Click += gcnew System::EventHandler(this, &MsgForm::button_OK_Click);
			// 
			// MsgForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(612, 437);
			this->Controls->Add(this->button_Cancel);
			this->Controls->Add(this->button_OK);
			this->Controls->Add(this->progressBar2);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->progressBar1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"MsgForm";
			this->ShowIcon = false;
			this->Text = L"素材の差替え";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MsgForm::MsgForm_FormClosing);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

    private: System::Void MsgForm_FormClosing( System::Object ^sender , System::Windows::Forms::FormClosingEventArgs ^e );
	private: System::Void button_OK_Click( System::Object ^sender , System::EventArgs ^e );
    private: System::Void button_Cancel_Click( System::Object ^sender , System::EventArgs ^e );

    public: static   System::Void Begin( System::Void );
    public: static   System::Void End( System::Void );
    public:          System::Void BeginEnd_Body( int Kind );
    public: delegate System::Void BeginEndCallback( int Kind );

    public: static   System::Void MsgPrint       ( System::String ^ Text , int Kind );
    public:          System::Void MsgPrint_Body  ( System::String ^ Text , int Kind );
    public: delegate System::Void SetTextCallback( System::String ^ Text , int Kind );

    public: static   System::Void SetProgress        ( int ID , double Value );
    public:          System::Void SetProgress_Body   ( int ID , double Value );
    public: delegate System::Void SetProgressCallback( int ID , double Value );

    public: System::Void Run( System::Void );
    };
}
