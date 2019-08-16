#include "TechProSpEssential.h"

void TTRM_ClassInitializer::toastActivated() const
{
    std::wcout << L"The user clicked in this toast" << std::endl;
    exit(0);
}

void TTRM_ClassInitializer::toastActivated(int actionIndex) const
{
    std::wcout << L"The user clicked on action #" << actionIndex << std::endl;
    exit(16 + actionIndex);
}

void TTRM_ClassInitializer::toastDismissed(WinToastDismissalReason state) const
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

void TTRM_ClassInitializer::toastFailed() const
{
    std::wcout << L"Error showing current toast" << std::endl;
    exit(5);
}
