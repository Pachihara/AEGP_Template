#ifndef SUITE_H_DEFINE_
#define SUITE_H_DEFINE_

#include <AEGP_SuiteHandler.h>
#include <string>

/* ƒo[ƒWƒ‡ƒ“ŠÔ‚Ìˆá‚¢‚ğ‹zû */
#define UtilitySuite        UtilitySuite4
#define CommandSuite        CommandSuite1
#define RegisterSuite       RegisterSuite5
#define LayerSuite          LayerSuite5
#define FootageSuite        FootageSuite5
#define CompSuite           CompSuite5
#define ItemSuite           ItemSuite6
#define StreamSuite         StreamSuite2
#define ProjSuite           ProjSuite5
#define EffectSuite         EffectSuite3
#define MemorySuite         MemorySuite1

extern A_Err GetLayerName( AEGP_LayerH layerH , std::string &layer_name , std::string &source_name );
extern A_Err GetItemName( AEGP_ItemH itemH , std::string &item_name );
extern A_Err GetFootagePath( AEGP_FootageH footageH , int index , std::string &footage_name );
extern A_Err GetProjectPath( AEGP_ProjectH projH , std::string &project_path );

#endif

