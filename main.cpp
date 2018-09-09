/*----------------------------------------------------------------------------
  main.cpp
  �v���O�C���̃g�b�v����
  ----------------------------------------------------------------------------*/
#include <AE_GeneralPlug.h>
#include <tchar.h>
#include <exception>

#include "common.h"
#include "version.h"

/*----------------------------------------------------------------------------
  �O���[�o���ϐ�
  ----------------------------------------------------------------------------*/
SPBasicSuite * pSPBasicSuite = NULL;
AEGP_PluginID  PluginID      = 0;

/*----------------------------------------------------------------------------
  �R�}���h�o�^�p�e�[�u��
  ----------------------------------------------------------------------------*/
typedef struct {
    char *      CommandStr;  // �R�}���h��
    AEGP_MenuID MenuID;      // �R�}���h�}���ꏊ
    void ( *Func )( void );  // �Ή�����֐�
} TCommandDef;

// �R�}���h�e�[�u��
static TCommandDef tblCommandDef[] = {
    // �R�}���h0 �I���o��
    {
        PLUGIN_NAME " " PLUGIN_VERSION DEBUG_STRING
                    " AEGP�v���O�C���̃e���v���[�g",
        AEGP_Menu_COMPOSITION,
        NULL,
    },
};

// �R�}���h��
#define NumCommand ( sizeof( tblCommandDef ) / sizeof( tblCommandDef[0] ) )

// �R�}���h���ʔԍ�
static AEGP_Command CommandID[NumCommand];

/*----------------------------------------------------------------------------
  DeathHook

  Main�֐����œo�^���Ďg�p����B
  AfterEffecs���I�������Ƃ��ɃR�[�������B
  ----------------------------------------------------------------------------*/
A_Err DeathHook( AEGP_GlobalRefcon plugin_refconP, AEGP_DeathRefcon refconP )
{
    return A_Err_NONE;
}

/*----------------------------------------------------------------------------
  UpdateMenuHook

  Main�֐����œo�^���Ďg�p����B
  �R�}���h�����s���ꂽ�Ƃ��ɃR�[�������B
  �R�}���h�ԍ������ʂ��ăR�}���h���Ƃ̏������s���B
  ----------------------------------------------------------------------------*/
A_Err UpdateMenuHook( AEGP_GlobalRefcon     plugin_refconPV,
                      AEGP_UpdateMenuRefcon refconPV,
                      AEGP_WindowType       active_window )
{
    AEGP_SuiteHandler suites( pSPBasicSuite );

    for ( int i = 0; i < NumCommand; i++ ) {
        /* ��ɋ��� */
        ErrCheck( suites.CommandSuite()->AEGP_EnableCommand( CommandID[i] ) );
    }

    return A_Err_NONE;
}

/*----------------------------------------------------------------------------
  CommandHook

  �v���O�C��������
  Main���Ŋ֐���AE�ɓo�^���A�{�^���������ꂽ�Ƃ��ɌĂяo�����B
  ----------------------------------------------------------------------------*/
A_Err CommandHook( AEGP_GlobalRefcon  plugin_refconPV,
                   AEGP_CommandRefcon refconPV,
                   AEGP_Command       command,
                   AEGP_HookPriority  hook_priority,
                   A_Boolean          already_handledB,
                   A_Boolean *        handledPB )
{
    *handledPB = FALSE;

    for ( int i = 0; i < NumCommand; i++ ) {
        if ( CommandID[i] != command ) {
            continue;
        }

        // �R�}���h�̎��s
        if ( tblCommandDef[i].Func != NULL ) {
            tblCommandDef[i].Func();
            *handledPB = TRUE;
        }

        break;
    }

    return A_Err_NONE;
}
/*----------------------------------------------------------------------------
  GPMain

  Main�֐�
  AE�N�����A�v���O�C���Ƃ��ĔF�����ꂽ�i�K��1�x�����Ăяo�����֐��B
  �����ŃR�}���h�̓o�^���s���B
  PiPL���Ŋ֐������w�肵�Ă���B (mainPiPL.r�Q��)
  ----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

__declspec( dllexport ) A_Err EntryPointFunc( SPBasicSuite * pica_basicP,
                                              A_long         major_versionL,
                                              A_long         minor_versionL,
                                              AEGP_PluginID  aegp_plugin_id,
                                              void *         global_refconPV )
{
    pSPBasicSuite = pica_basicP;
    PluginID      = aegp_plugin_id;

    AEGP_SuiteHandler suites( pSPBasicSuite );

    for ( int i = 0; i < NumCommand; i++ ) {
        /* �R�}���h�ԍ��擾 */
        suites.CommandSuite()->AEGP_GetUniqueCommand( &CommandID[i] );

        /* �R�}���h�}�� */
        suites.CommandSuite()->AEGP_InsertMenuCommand(
            CommandID[i],                /* �R�}���h�ԍ� */
            tblCommandDef[i].CommandStr, /* �R�}���h�� */
            tblCommandDef[i].MenuID,     /* �R�}���h�ǉ��ʒu */
            AEGP_MENU_INSERT_AT_BOTTOM );
    }

    /* �R�}���h�����s���ꂽ�Ƃ��ɌĂяo�����֐��̓o�^ */
    suites.RegisterSuite()->AEGP_RegisterCommandHook(
        PluginID,         /* �v���O�C��ID */
        AEGP_HP_AfterAE,  /* ���荞�ޗD�� */
        AEGP_Command_ALL, /* �w�肷���ނ͂���̂� */
        CommandHook,      /* �o�^�֐� */
        NULL );

    /* ���j���[���J�����тɌĂ΂��֐��̓o�^ */
    suites.RegisterSuite()->AEGP_RegisterUpdateMenuHook(
        PluginID,       /* �v���O�C��ID */
        UpdateMenuHook, /* �o�^�֐� */
        NULL );

    /* �I�����̃R�[���o�b�N�֐��̓o�^ */
    suites.RegisterSuite()->AEGP_RegisterDeathHook( PluginID, DeathHook, NULL );

    return A_Err_NONE;
}

#ifdef __cplusplus
}
#endif
