#ifndef DIALOG_H_DEFINE
#define DIALOG_H_DEFINE

#include <AE_GeneralPlug.h>
#include <windows.h>
#include <string>
#include <vector>
#include "textkind_def.h"

class TDlgManage
{
public:
    TDlgManage();
    ~TDlgManage();

    void SendText( const std::string & _Text,
                   int                 TextKind = LPARAM_TextKind_Normal );
    void SetProgress( int No, double Rate );
    bool GetStopRequest( void );
    void Begin( void );
    void End( void );

    /* Dialog , DialogItem Handler */
    unsigned int StopRequest;

    HWND   LogHWindow;
    HANDLE MapHandle;
    HANDLE MutexHandle;
};

#endif
