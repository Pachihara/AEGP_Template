/*----------------------------------------------------------------------------
  main.cpp
  プラグインのトップ処理
  ----------------------------------------------------------------------------*/
#include <AE_GeneralPlug.h>
#include <tchar.h>
#include <exception>

#include "common.h"
#include "version.h"

/*----------------------------------------------------------------------------
  グローバル変数
  ----------------------------------------------------------------------------*/
SPBasicSuite * pSPBasicSuite = NULL;
AEGP_PluginID  PluginID      = 0;

/*----------------------------------------------------------------------------
  コマンド登録用テーブル
  ----------------------------------------------------------------------------*/
typedef struct {
    char *      CommandStr;  // コマンド名
    AEGP_MenuID MenuID;      // コマンド挿入場所
    void ( *Func )( void );  // 対応する関数
} TCommandDef;

// コマンドテーブル
static TCommandDef tblCommandDef[] = {
    // コマンド0 選択出力
    {
        PLUGIN_NAME " " PLUGIN_VERSION DEBUG_STRING
                    " AEGPプラグインのテンプレート",
        AEGP_Menu_COMPOSITION,
        NULL,
    },
};

// コマンド数
#define NumCommand ( sizeof( tblCommandDef ) / sizeof( tblCommandDef[0] ) )

// コマンド識別番号
static AEGP_Command CommandID[NumCommand];

/*----------------------------------------------------------------------------
  DeathHook

  Main関数内で登録して使用する。
  AfterEffecsが終了したときにコールされる。
  ----------------------------------------------------------------------------*/
A_Err DeathHook( AEGP_GlobalRefcon plugin_refconP, AEGP_DeathRefcon refconP )
{
    return A_Err_NONE;
}

/*----------------------------------------------------------------------------
  UpdateMenuHook

  Main関数内で登録して使用する。
  コマンドが実行されたときにコールされる。
  コマンド番号を識別してコマンドごとの処理を行う。
  ----------------------------------------------------------------------------*/
A_Err UpdateMenuHook( AEGP_GlobalRefcon     plugin_refconPV,
                      AEGP_UpdateMenuRefcon refconPV,
                      AEGP_WindowType       active_window )
{
    AEGP_SuiteHandler suites( pSPBasicSuite );

    for ( int i = 0; i < NumCommand; i++ ) {
        /* 常に許可 */
        ErrCheck( suites.CommandSuite()->AEGP_EnableCommand( CommandID[i] ) );
    }

    return A_Err_NONE;
}

/*----------------------------------------------------------------------------
  CommandHook

  プラグイン処理部
  Main内で関数をAEに登録し、ボタンが押されたときに呼び出される。
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

        // コマンドの実行
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

  Main関数
  AE起動時、プラグインとして認識された段階で1度だけ呼び出される関数。
  ここでコマンドの登録を行う。
  PiPL内で関数名を指定している。 (mainPiPL.r参照)
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
        /* コマンド番号取得 */
        suites.CommandSuite()->AEGP_GetUniqueCommand( &CommandID[i] );

        /* コマンド挿入 */
        suites.CommandSuite()->AEGP_InsertMenuCommand(
            CommandID[i],                /* コマンド番号 */
            tblCommandDef[i].CommandStr, /* コマンド名 */
            tblCommandDef[i].MenuID,     /* コマンド追加位置 */
            AEGP_MENU_INSERT_AT_BOTTOM );
    }

    /* コマンドが実行されたときに呼び出される関数の登録 */
    suites.RegisterSuite()->AEGP_RegisterCommandHook(
        PluginID,         /* プラグインID */
        AEGP_HP_AfterAE,  /* 割り込む優先 */
        AEGP_Command_ALL, /* 指定する種類はこれのみ */
        CommandHook,      /* 登録関数 */
        NULL );

    /* メニューが開くたびに呼ばれる関数の登録 */
    suites.RegisterSuite()->AEGP_RegisterUpdateMenuHook(
        PluginID,       /* プラグインID */
        UpdateMenuHook, /* 登録関数 */
        NULL );

    /* 終了時のコールバック関数の登録 */
    suites.RegisterSuite()->AEGP_RegisterDeathHook( PluginID, DeathHook, NULL );

    return A_Err_NONE;
}

#ifdef __cplusplus
}
#endif
