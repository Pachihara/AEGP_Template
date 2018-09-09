
#include <tchar.h>
#include <windows.h>

#include <AE_GeneralPlug.h>

#include "MsgForm.h"
#include "common.h"
#include "dialog.h"

using namespace AEGP_Template;

/*=======================================================================
  CLASS TDlgManage
  ダイアログ管理クラス
  =======================================================================*/
/*-----------------------------------------------------------------------
  初期化、解放処理
  -----------------------------------------------------------------------*/
TDlgManage::TDlgManage()
{
    /* ログフォームを開く */
    try {
        System::Windows::Forms::Form ^ form =
            System::Windows::Forms::Application::OpenForms["MsgForm"];

        if ( form == nullptr ) {
            System::Threading::Thread ^ thread;
            System::Threading::ThreadStart ^ thread_start;

            /* 別スレッド呼び出し */
            thread_start = gcnew System::Threading::ThreadStart(
                gcnew MsgForm(), &MsgForm::Run );
            thread = gcnew System::Threading::Thread( thread_start );
            thread->Start();
        }
    } catch ( System::Exception ^ E ) {
        System::Windows::Forms::MessageBox::Show( E->Message );
    }
}
TDlgManage::~TDlgManage()
{
}
/*-----------------------------------------------------------------------
  Begin
  文字列を空に
  OKボタンをDisable
  -----------------------------------------------------------------------*/
void TDlgManage::Begin( void )
{
    MsgForm::Begin();
}
/*-----------------------------------------------------------------------
  End
  OKボタンをEnableに
  -----------------------------------------------------------------------*/
void TDlgManage::End( void )
{
    MsgForm::End();
}
/*-----------------------------------------------------------------------
  SendText
  ログフォームに文字列の送信
  TextKindの種類によって挙動が異なる

  ログメッセージの出力
    LPARAM_TextKind_Normal
    LPARAM_TextKind_Warning
    LPARAM_TextKind_Error
    LPARAM_TextKind_FatalError

  現在の処理中のファイルを示す
    LPARAM_TextKind_FileName

  -----------------------------------------------------------------------*/
void TDlgManage::SendText( const std::string & _Text, int TextKind )
{
    MsgForm::LogPrint( gcnew System::String( _Text.c_str() ), TextKind );
}
/*-----------------------------------------------------------------------
  SetProgress

  プログレスバーの値指定
  No でプログレスバーの指定 0 or 1
  -----------------------------------------------------------------------*/
void TDlgManage::SetProgress( int No, double Rate )
{
    MsgForm::SetProgress( No, Rate );
}
/*-----------------------------------------------------------------------
  StopRequestの取得/設定
  -----------------------------------------------------------------------*/
bool TDlgManage::GetStopRequest( void )
{
    return MsgF orm::IsStopRequest;
}
