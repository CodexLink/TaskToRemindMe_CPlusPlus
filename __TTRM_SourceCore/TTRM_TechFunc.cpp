#include "TTRM_Core.h"
/*
    Technical Project Specific Essential Function CPP File by Janrey "CodexLink" Licas
    File Category Type: Core Function Body Definition, "CoreFunc".
	Note that this CPP file will only contain external library functions.
*/

/*
	WinToast Library Function Declaration - START
*/
void TTRM::toastActivated(void) const
{
    std::wcout << L"The user clicked in this toast" << std::endl;
}

void TTRM::toastActivated(int actionIndex) const
{
    std::wcout << L"The user clicked on action #" << actionIndex << std::endl;
}

void TTRM::toastDismissed(WinToastDismissalReason state) const
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
void TTRM::toastFailed(void) const
{
    std::wcout << L"Error showing current toast" << std::endl;
    exit(5);
}
/*
	WinToast Library Function Declaration - END
*/

/*
	SQLite Library Function Declaration - START
*/
bool TTRM::SQLite_Initialize() const
{
    return RETURN_BACK_NOTHING;
}
bool TTRM::SQLite_CheckDatabase() const
{
    return RETURN_BACK_NOTHING;
}
bool TTRM::SQLite_CreateTable() const
{
    return RETURN_BACK_NOTHING;
}
bool TTRM::SQLite_ManipulateValues(SQLite_ExecutionType Execution) const
{
	return RETURN_BACK_NOTHING;
}
/*
	SQLite Library Function Declaration - START
*/