// Technical Project Specific Essential Function Header File by Janrey "CodexLink" Licas

#ifndef TECHPROSPESSENTIAL_H
#define TECHPROSPESSENTIAL_H

#include <iostream>
#include <string>
#include <WinToast_Main/wintoastlib.h>
#include <windows.h> // For Win32 API

#define RETURN_NULL 0
#define LIMIT_COUNTER 5

namespace TTRM_Technical_Namespace
{

class TTRM_TechnicalFunctions
{
};

class WinToastHandler_TTRM : public IWinToastHandler
{
public:
    void toastActivated() const
    {
        std::wcout << L"The user clicked in this toast" << std::endl;
        exit(0);
    }

    void toastActivated(int actionIndex) const
    {
        std::wcout << L"The user clicked on action #" << actionIndex << std::endl;
        exit(16 + actionIndex);
    }

    void toastDismissed(WinToastDismissalReason state) const
    {
        switch (state)
        {
        case UserCanceled:
            std::wcout << L"The user dismissed this toast" << std::endl;
            exit(1);
            break;
        case TimedOut:
            std::wcout << L"The toast has timed out" << std::endl;
            exit(2);
            break;
        case ApplicationHidden:
            std::wcout << L"The application hid the toast using ToastNotifier.hide()" << std::endl;
            exit(3);
            break;
        default:
            std::wcout << L"Toast not activated" << std::endl;
            exit(4);
            break;
        }
    }

    void toastFailed() const
    {
        std::wcout << L"Error showing current toast" << std::endl;
        exit(5);
    }
};

} // namespace TTRM_Technical_Namespace
#endif