
#include <tchar.h>
#include <windows.h>

#include <AE_GeneralPlug.h>

#include "MsgForm.h"
#include "common.h"
#include "dialog.h"

using namespace AEGP_Template;

/*=======================================================================
  CLASS TDlgManage
  �_�C�A���O�Ǘ��N���X
  =======================================================================*/
/*-----------------------------------------------------------------------
  �������A�������
  -----------------------------------------------------------------------*/
TDlgManage::TDlgManage()
{
    /* ���O�t�H�[�����J�� */
    try {
        System::Windows::Forms::Form ^ form =
            System::Windows::Forms::Application::OpenForms["MsgForm"];

        if ( form == nullptr ) {
            System::Threading::Thread ^ thread;
            System::Threading::ThreadStart ^ thread_start;

            /* �ʃX���b�h�Ăяo�� */
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
  ����������
  OK�{�^����Disable
  -----------------------------------------------------------------------*/
void TDlgManage::Begin( void )
{
    MsgForm::Begin();
}
/*-----------------------------------------------------------------------
  End
  OK�{�^����Enable��
  -----------------------------------------------------------------------*/
void TDlgManage::End( void )
{
    MsgForm::End();
}
/*-----------------------------------------------------------------------
  SendText
  ���O�t�H�[���ɕ�����̑��M
  TextKind�̎�ނɂ���ċ������قȂ�

  ���O���b�Z�[�W�̏o��
    LPARAM_TextKind_Normal
    LPARAM_TextKind_Warning
    LPARAM_TextKind_Error
    LPARAM_TextKind_FatalError

  ���݂̏������̃t�@�C��������
    LPARAM_TextKind_FileName

  -----------------------------------------------------------------------*/
void TDlgManage::SendText( const std::string & _Text, int TextKind )
{
    MsgForm::LogPrint( gcnew System::String( _Text.c_str() ), TextKind );
}
/*-----------------------------------------------------------------------
  SetProgress

  �v���O���X�o�[�̒l�w��
  No �Ńv���O���X�o�[�̎w�� 0 or 1
  -----------------------------------------------------------------------*/
void TDlgManage::SetProgress( int No, double Rate )
{
    MsgForm::SetProgress( No, Rate );
}
/*-----------------------------------------------------------------------
  StopRequest�̎擾/�ݒ�
  -----------------------------------------------------------------------*/
bool TDlgManage::GetStopRequest( void )
{
    return MsgF orm::IsStopRequest;
}
