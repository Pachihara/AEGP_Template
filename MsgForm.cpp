#include "MsgForm.h"
#include "textkind_def.h"

namespace AEGP_Template
{

/*--------------------------------------------------------------------------
  MsgForm
  初期化処理
  --------------------------------------------------------------------------*/
MsgForm::MsgForm( System::Void )
{
    InitializeComponent();
}
/*--------------------------------------------------------------------------
  ~MsgForm
  解放処理
  --------------------------------------------------------------------------*/
MsgForm::~MsgForm()
{
    if ( components ) {
        delete components;
    }
}
/*--------------------------------------------------------------------------
  終了ボタン
  プラグインが終了していない場合は停止要求のみを送信する。
  --------------------------------------------------------------------------*/
System::Void MsgForm::MsgForm_FormClosing(
    Object ^ sender,
    System::Windows::Forms::FormClosingEventArgs ^ e )
{
    /* ユーザー起動の終了ではない場合は即終了
       (アプリケーション自体の終了などで命令がコールされた場合など) */
    if ( e->CloseReason != System::Windows::Forms::CloseReason::UserClosing )
        return;

    if ( IsRunning == false )
        return;

    textB_Msg->SelectionColor = System::Drawing::Color::Black;
    textB_Msg->AppendText(
        "処理を中止しています。しばらくお待ちください。\r\n" );
    IsStopRequest = true;

    e->Cancel = true;
}
/*--------------------------------------------------------------------------
  ボタン処理
  --------------------------------------------------------------------------*/
System::Void MsgForm::button_OK_Click( System::Object ^ sender,
                                       System::EventArgs ^ e )
{
    Close();
}
/*--------------------------------------------------------------------------*/
System::Void MsgForm::button_Cancel_Click( System::Object ^ sender,
                                           System::EventArgs ^ e )
{
    textB_Msg->SelectionColor = System::Drawing::Color::Black;
    textB_Msg->AppendText(
        "処理を中止しています。しばらくお待ちください。\r\n" );
    IsStopRequest = true;
}
/*--------------------------------------------------------------------------
  処理開始、終了の指定
  --------------------------------------------------------------------------*/
System::Void MsgForm::Begin( System::Void )
{
    MsgForm ^ form;

    /* フォームの検索/取得 */
    do {
        System::Threading::Thread::Sleep( 50 );
        form = safe_cast<MsgForm ^>(
            System::Windows::Forms::Application::OpenForms["MsgForm"] );
    } while ( form == nullptr );

    form->BeginEnd_Body( 0 );
}
/*--------------------------------------------------------------------------*/
System::Void MsgForm::End( System::Void )
{
    MsgForm ^ form;

    /* フォームの検索/取得 */
    do {
        System::Threading::Thread::Sleep( 50 );
        form = safe_cast<MsgForm ^>(
            System::Windows::Forms::Application::OpenForms["MsgForm"] );
    } while ( form == nullptr );

    form->BeginEnd_Body( 1 );
}
/*--------------------------------------------------------------------------*/
System::Void MsgForm::BeginEnd_Body( int Kind )
{
    if ( InvokeRequired == true ) {
        /* スレッドセーフな呼び出し */
        BeginEndCallback ^ pDelegateFunc =
            gcnew BeginEndCallback( this, &MsgForm::BeginEnd_Body );
        Invoke( pDelegateFunc, gcnew array<Object ^>{Kind} );
    } else {
        /* 同じスレッドから呼び出しているため通常の呼び出しで問題なし */
        if ( Kind == 0 ) {
            /* Begin */
            textB_Msg->Clear();
            textB_Err->Clear();
            IsStopRequest          = false;
            IsRunning              = true;
            IsError                = false;
            IsWarning              = false;
            RunningFileName        = nullptr;
            button_OK->Enabled     = false;
            button_Cancel->Enabled = true;

            SetProgress( 0, 0.0 );
            SetProgress( 1, 0.0 );

            Activate();
        } else {
            /* End */
            IsRunning              = false;
            button_OK->Enabled     = true;
            button_Cancel->Enabled = false;

            if ( IsStopRequest == false ) {
                SetProgress( 0, 1.0 );
                SetProgress( 1, 1.0 );
            }

            if ( IsError == true ) {
                textB_Msg->SelectionColor = System::Drawing::Color::Red;
                textB_Msg->AppendText(
                    "エラーが発生しています。 "
                    "エラー一覧を参照してください。\r\n" );
            } else if ( IsWarning == true ) {
                textB_Msg->SelectionColor = System::Drawing::Color::Blue;
                textB_Msg->AppendText(
                    "ワーニングが発生しています。 "
                    "エラー一覧を参照してください。\r\n" );
            } else {

                if ( IsStopRequest == true ) {
                    textB_Msg->SelectionColor = System::Drawing::Color::Black;
                    textB_Msg->AppendText( "処理を中止しました。\r\n" );
                } else {
                    textB_Msg->SelectionColor = System::Drawing::Color::Black;
                    textB_Msg->AppendText( "正常終了しました。\r\n" );
                }
            }
        }
    }
}
/*--------------------------------------------------------------------------
  文字列出力
  --------------------------------------------------------------------------*/
System::Void MsgForm::MsgPrint( System::String ^ Text, int Kind )
{
    MsgForm ^ form;

    if ( System::String::IsNullOrEmpty( Text ) == true )
        return;

    /* フォームの検索/取得 */
    do {
        System::Threading::Thread::Sleep( 50 );
        form = safe_cast<MsgForm ^>(
            System::Windows::Forms::Application::OpenForms["MsgForm"] );
    } while ( form == nullptr );

    form->MsgPrint_Body( Text, Kind );
}
/*--------------------------------------------------------------------------*/
System::Void MsgForm::MsgPrint_Body( System::String ^ Text, int Kind )
{
    if ( InvokeRequired == true ) {
        /* スレッドセーフな呼び出し */
        SetTextCallback ^ pDelegateFunc =
            gcnew SetTextCallback( this, &MsgForm::MsgPrint_Body );
        Invoke( pDelegateFunc, gcnew array<Object ^>{Text, Kind} );
    } else {
        /* 同じスレッドから呼び出しているため通常の呼び出しで問題なし */

        // 色選択
        switch ( Kind ) {
        case LPARAM_TextKind_Normal:
            textB_Msg->SelectionColor = System::Drawing::Color::Black;
            break;
        case LPARAM_TextKind_Warning:
            textB_Msg->SelectionColor = System::Drawing::Color::Blue;
            break;
        case LPARAM_TextKind_Error:
            textB_Msg->SelectionColor = System::Drawing::Color::Red;
            break;
        case LPARAM_TextKind_FatalError:
            textB_Msg->SelectionColor = System::Drawing::Color::Purple;
            break;
        case LPARAM_TextKind_FileName:
            if ( Text->Length == 0 ) {
                RunningFileName = nullptr;
            } else {
                RunningFileName = Text;
            }
            return;
        }

        // 通常ログ出力
        textB_Msg->AppendText( Text );
        // エラー用ログ出力
        if ( Kind != LPARAM_TextKind_Normal ) {

            /* 問題があったファイル名を表示 */
            if ( Kind != LPARAM_TextKind_FatalError &&
                 RunningFileName != nullptr ) {

                textB_Err->SelectionColor = System::Drawing::Color::Black;
                textB_Err->AppendText( ( gcnew System::String( "[ " ) ) +
                                       RunningFileName + " ]\r\n" );
                RunningFileName = nullptr;
            }

            if ( Kind == LPARAM_TextKind_Warning )
                IsWarning = true;
            else
                IsError = true;

            textB_Err->SelectionColor = textB_Msg->SelectionColor;
            textB_Err->AppendText( Text );
        }
    }
}
/*--------------------------------------------------------------------------
  プログレスバー
  --------------------------------------------------------------------------*/
System::Void MsgForm::SetProgress( int ID, double Value )
{
    MsgForm ^ form;

    /* フォームの検索/取得 */
    do {
        System::Threading::Thread::Sleep( 50 );
        form = safe_cast<MsgForm ^>(
            System::Windows::Forms::Application::OpenForms["MsgForm"] );
    } while ( form == nullptr );

    form->SetProgress_Body( ID, Value );
}
/*--------------------------------------------------------------------------*/
System::Void MsgForm::SetProgress_Body( int ID, double Value )
{
    if ( InvokeRequired == true ) {
        /* スレッドセーフな呼び出し */
        SetProgressCallback ^ pDelegateFunc =
            gcnew SetProgressCallback( this, &MsgForm::SetProgress_Body );
        Invoke( pDelegateFunc, gcnew array<Object ^>{ID, Value} );
    } else {
        /* 同じスレッドから呼び出しているため通常の呼び出しで問題なし */
        if ( ID == 0 ) {
            progressBar1->Value   = (int)( Value * 65536.0 );
            progressBar1->Maximum = 65536;
        } else {
            progressBar2->Value   = (int)( Value * 65536.0 );
            progressBar2->Maximum = 65536;
        }
    }
}
/*--------------------------------------------------------------------------
  Run
  フォームの単独起動に使用
  自分自身を走らせる。
  --------------------------------------------------------------------------*/
System::Void MsgForm::Run( System::Void )
{
    System::Windows::Forms::Application::Run( this );
}

}  // namespace AEGP_Template
