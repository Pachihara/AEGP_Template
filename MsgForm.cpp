#include "MsgForm.h"
#include "textkind_def.h"

namespace AEGP_Template
{

/*--------------------------------------------------------------------------
  MsgForm
  ����������
  --------------------------------------------------------------------------*/
MsgForm::MsgForm( System::Void )
{
    InitializeComponent();
}
/*--------------------------------------------------------------------------
  ~MsgForm
  �������
  --------------------------------------------------------------------------*/
MsgForm::~MsgForm()
{
    if ( components ) {
        delete components;
    }
}
/*--------------------------------------------------------------------------
  �I���{�^��
  �v���O�C�����I�����Ă��Ȃ��ꍇ�͒�~�v���݂̂𑗐M����B
  --------------------------------------------------------------------------*/
System::Void MsgForm::MsgForm_FormClosing(
    Object ^ sender,
    System::Windows::Forms::FormClosingEventArgs ^ e )
{
    /* ���[�U�[�N���̏I���ł͂Ȃ��ꍇ�͑��I��
       (�A�v���P�[�V�������̂̏I���ȂǂŖ��߂��R�[�����ꂽ�ꍇ�Ȃ�) */
    if ( e->CloseReason != System::Windows::Forms::CloseReason::UserClosing )
        return;

    if ( IsRunning == false )
        return;

    textB_Msg->SelectionColor = System::Drawing::Color::Black;
    textB_Msg->AppendText(
        "�����𒆎~���Ă��܂��B���΂炭���҂����������B\r\n" );
    IsStopRequest = true;

    e->Cancel = true;
}
/*--------------------------------------------------------------------------
  �{�^������
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
        "�����𒆎~���Ă��܂��B���΂炭���҂����������B\r\n" );
    IsStopRequest = true;
}
/*--------------------------------------------------------------------------
  �����J�n�A�I���̎w��
  --------------------------------------------------------------------------*/
System::Void MsgForm::Begin( System::Void )
{
    MsgForm ^ form;

    /* �t�H�[���̌���/�擾 */
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

    /* �t�H�[���̌���/�擾 */
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
        /* �X���b�h�Z�[�t�ȌĂяo�� */
        BeginEndCallback ^ pDelegateFunc =
            gcnew BeginEndCallback( this, &MsgForm::BeginEnd_Body );
        Invoke( pDelegateFunc, gcnew array<Object ^>{Kind} );
    } else {
        /* �����X���b�h����Ăяo���Ă��邽�ߒʏ�̌Ăяo���Ŗ��Ȃ� */
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
                    "�G���[���������Ă��܂��B "
                    "�G���[�ꗗ���Q�Ƃ��Ă��������B\r\n" );
            } else if ( IsWarning == true ) {
                textB_Msg->SelectionColor = System::Drawing::Color::Blue;
                textB_Msg->AppendText(
                    "���[�j���O���������Ă��܂��B "
                    "�G���[�ꗗ���Q�Ƃ��Ă��������B\r\n" );
            } else {

                if ( IsStopRequest == true ) {
                    textB_Msg->SelectionColor = System::Drawing::Color::Black;
                    textB_Msg->AppendText( "�����𒆎~���܂����B\r\n" );
                } else {
                    textB_Msg->SelectionColor = System::Drawing::Color::Black;
                    textB_Msg->AppendText( "����I�����܂����B\r\n" );
                }
            }
        }
    }
}
/*--------------------------------------------------------------------------
  ������o��
  --------------------------------------------------------------------------*/
System::Void MsgForm::MsgPrint( System::String ^ Text, int Kind )
{
    MsgForm ^ form;

    if ( System::String::IsNullOrEmpty( Text ) == true )
        return;

    /* �t�H�[���̌���/�擾 */
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
        /* �X���b�h�Z�[�t�ȌĂяo�� */
        SetTextCallback ^ pDelegateFunc =
            gcnew SetTextCallback( this, &MsgForm::MsgPrint_Body );
        Invoke( pDelegateFunc, gcnew array<Object ^>{Text, Kind} );
    } else {
        /* �����X���b�h����Ăяo���Ă��邽�ߒʏ�̌Ăяo���Ŗ��Ȃ� */

        // �F�I��
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

        // �ʏ탍�O�o��
        textB_Msg->AppendText( Text );
        // �G���[�p���O�o��
        if ( Kind != LPARAM_TextKind_Normal ) {

            /* ��肪�������t�@�C������\�� */
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
  �v���O���X�o�[
  --------------------------------------------------------------------------*/
System::Void MsgForm::SetProgress( int ID, double Value )
{
    MsgForm ^ form;

    /* �t�H�[���̌���/�擾 */
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
        /* �X���b�h�Z�[�t�ȌĂяo�� */
        SetProgressCallback ^ pDelegateFunc =
            gcnew SetProgressCallback( this, &MsgForm::SetProgress_Body );
        Invoke( pDelegateFunc, gcnew array<Object ^>{ID, Value} );
    } else {
        /* �����X���b�h����Ăяo���Ă��邽�ߒʏ�̌Ăяo���Ŗ��Ȃ� */
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
  �t�H�[���̒P�ƋN���Ɏg�p
  �������g�𑖂点��B
  --------------------------------------------------------------------------*/
System::Void MsgForm::Run( System::Void )
{
    System::Windows::Forms::Application::Run( this );
}

}  // namespace AEGP_Template
