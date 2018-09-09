#include <vector>
#include "common.h"

#include "AEGP_SuiteHandler.cpp"

/*------------------------------------------------------------------------------
  MissingSuiteError
  AEGP_SuiteHandler�p�̃G���[�n���h��
  �G���[���̏�����API�̃��[�U�[�T�C�h�Œ�`����
  ------------------------------------------------------------------------------*/
void AEGP_SuiteHandler::MissingSuiteError() const
{
    throw TPluginException( __FILE__, __LINE__, "MissingSuiteError" );
}

/*------------------------------------------------------------------------------
  UTF16MemH_To_String

  CS4�ȍ~�p�̑Ή�
  CS3�ȑO�͕�����擾�����͌Œ�z���p���Ă������A
  �����������𔲂��o�����߂ɁA�ϒ��̃��������g�p����悤�ɂȂ���

  �G���ȏ����������ꏊ���Ȃ������̂ł����ɂ����B
  misc.cpp�Ȃǂ��o�����炻�����Ɉړ�����B

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
        // �K�v�Ȓ����擾
        _wcstombs_s_l( &len, NULL, 0, utf_string, 0, locale );

        // �o�b�t�@�m��
        tmp_buff.resize( len + 1 );

        // �R���o�[�g
        _wcstombs_s_l( NULL, &tmp_buff[0], len, utf_string, len, locale );

        // �o�͗p
        dst_string = &tmp_buff[0];
    }
    ErrCheck( suites.MemorySuite()->AEGP_UnlockMemHandle( memH ) );
}

/*------------------------------------------------------------------------------
  GetLayerName
  LayerSuite -> GetLayerName �̃��b�p�[����
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
  ItemSuite -> GetItemName �̃��b�p�[����
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
  FootageSuite -> GetFootagePath �̃��b�p�[����
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
  ProjSuite -> GetProjectPath �̃��b�p�[����
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
