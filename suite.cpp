#include <vector>
#include "common.h"

#include "AEGP_SuiteHandler.cpp"

/*------------------------------------------------------------------------------
  MissingSuiteError
  AEGP_SuiteHandler用のエラーハンドラ
  エラー時の処理をAPIのユーザーサイドで定義する
  ------------------------------------------------------------------------------*/
void AEGP_SuiteHandler::MissingSuiteError() const
{
    throw TPluginException( __FILE__, __LINE__, "MissingSuiteError" );
}

/*------------------------------------------------------------------------------
  UTF16MemH_To_String

  CS4以降用の対応
  CS3以前は文字列取得処理は固定配列を用いていたが、
  文字数制限を抜け出すために、可変長のメモリを使用するようになった

  雑多な処理をおく場所がなかったのでここにおく。
  misc.cppなどが出来たらそっちに移動する。

  ------------------------------------------------------------------------------*/
void UTF16MemH_To_String( AEGP_MemHandle memH, std::string & dst_string )
{
    AEGP_SuiteHandler suites( pSPBasicSuite );
    std::vector<char> tmp_buff;
    _locale_t         locale = _create_locale( LC_ALL, "jpn" );
    wchar_t *         utf_string;
    size_t            len;

    ErrCheck( suites.MemorySuite()->AEGP_LockMemHandle(
        memH, (void **)&utf_string ) );
    {
        // 必要な長さ取得
        _wcstombs_s_l( &len, NULL, 0, utf_string, 0, locale );

        // バッファ確保
        tmp_buff.resize( len + 1 );

        // コンバート
        _wcstombs_s_l( NULL, &tmp_buff[0], len, utf_string, len, locale );

        // 出力用
        dst_string = &tmp_buff[0];
    }
    ErrCheck( suites.MemorySuite()->AEGP_UnlockMemHandle( memH ) );
}

/*------------------------------------------------------------------------------
  GetLayerName
  LayerSuite -> GetLayerName のラッパー処理
  ------------------------------------------------------------------------------*/
A_Err GetLayerName( AEGP_LayerH   layerH,
                    std::string & layer_name,
                    std::string & source_name )
{
    AEGP_SuiteHandler suites( pSPBasicSuite );
    AEGP_MemHandle    layer_memH  = NULL;
    AEGP_MemHandle    source_memH = NULL;

    ErrCheck( suites.LayerSuite6()->AEGP_GetLayerName(
        PluginID, layerH, &layer_memH, &source_memH ) );

    UTF16MemH_To_String( layer_memH, layer_name );
    UTF16MemH_To_String( source_memH, source_name );

    ErrCheck( suites.MemorySuite()->AEGP_FreeMemHandle( layer_memH ) );
    ErrCheck( suites.MemorySuite()->AEGP_FreeMemHandle( source_memH ) );

    return A_Err_NONE;
}

/*------------------------------------------------------------------------------
  GetItemName
  ItemSuite -> GetItemName のラッパー処理
  ------------------------------------------------------------------------------*/
A_Err GetItemName( AEGP_ItemH itemH, std::string & item_name )
{
    AEGP_SuiteHandler suites( pSPBasicSuite );
    AEGP_MemHandle    name_memH = NULL;

    ErrCheck(
        suites.ItemSuite8()->AEGP_GetItemName( PluginID, itemH, &name_memH ) );

    UTF16MemH_To_String( name_memH, item_name );

    ErrCheck( suites.MemorySuite()->AEGP_FreeMemHandle( name_memH ) );

    return A_Err_NONE;
}

/*------------------------------------------------------------------------------
  GetFootagePath
  FootageSuite -> GetFootagePath のラッパー処理
  ------------------------------------------------------------------------------*/
extern A_Err GetFootagePath( AEGP_FootageH footageH,
                             int           index,
                             std::string & footage_name )
{
    AEGP_SuiteHandler suites( pSPBasicSuite );
    AEGP_MemHandle    name_memH = NULL;

    ErrCheck( suites.FootageSuite()->AEGP_GetFootagePath(
        footageH, index, AEGP_FOOTAGE_MAIN_FILE_INDEX, &name_memH ) );

    UTF16MemH_To_String( name_memH, footage_name );

    ErrCheck( suites.MemorySuite()->AEGP_FreeMemHandle( name_memH ) );

    return A_Err_NONE;
}

/*------------------------------------------------------------------------------
  GetProjectPath
  ProjSuite -> GetProjectPath のラッパー処理
  ------------------------------------------------------------------------------*/
A_Err GetProjectPath( AEGP_ProjectH projH, std::string & project_path )
{
    AEGP_SuiteHandler suites( pSPBasicSuite );
    AEGP_MemHandle    name_memH = NULL;

    ErrCheck( suites.ProjSuite()->AEGP_GetProjectPath( projH, &name_memH ) );

    UTF16MemH_To_String( name_memH, project_path );

    ErrCheck( suites.MemorySuite()->AEGP_FreeMemHandle( name_memH ) );

    return A_Err_NONE;
}
