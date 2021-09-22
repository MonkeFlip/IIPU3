#include <windows.h>
#include <string>
#include <powrprof.h>
#pragma comment(lib, "Powrprof.lib")
#include <iostream>
using namespace std;

typedef struct _SYSTEM_POWER_INFORMATION {
    ULONG MaxIdlenessAllowed;
    ULONG Idleness;
    ULONG TimeRemaining;
    UCHAR CoolingMode;
}SYSTEM_POWER_INFORMATION, * PSYSTEM_POWER_INFORMATION;

void SystemPowerInfo()
{
    NTSTATUS power_info;
    SYSTEM_POWER_INFORMATION sys_bat_state;
    power_info = CallNtPowerInformation(SystemPowerInformation, NULL, 0, &sys_bat_state, sizeof(sys_bat_state));
    cout << power_info << endl;
    cout <<"MaxIdlenessAllowed: "<< sys_bat_state.MaxIdlenessAllowed << endl;
    cout <<"Idleness: " << sys_bat_state.Idleness << endl;
    cout <<"CoolingMode: "<< sys_bat_state.CoolingMode << endl;
    cout <<"TimeRemaining: "<< sys_bat_state.TimeRemaining << endl;
    SYSTEM_POWER_STATUS sys_power_stat;
    if (GetSystemPowerStatus(&sys_power_stat))
    {
        if (sys_power_stat.ACLineStatus & 1)
        {
            cout << "Online" << endl;
        }
        else if (sys_power_stat.ACLineStatus == 0)
        {
            cout << "Offline" << endl;
        }
        else
        {
            cout << "Unknown status." << endl;
        }

        if (sys_power_stat.BatteryFlag & 1)
        {
            cout << "High—the battery capacity is at more than 66 percent" << endl;
        }
        else if (sys_power_stat.BatteryFlag & 2)
        {
            cout << "Low—the battery capacity is at less than 33 percent" << endl;
        }
        else if (sys_power_stat.BatteryFlag & 4)
        {
            cout << "Critical—the battery capacity is at less than five percent" << endl;
        }
        else if (sys_power_stat.BatteryFlag & 8)
        {
            cout << "Charging" << endl;
        }
        else if (sys_power_stat.BatteryFlag & 128)
        {
            cout << "No system battery" << endl;
        }
        else
        {
            cout << "Unknown status—unable to read the battery flag information" << endl;
        }

        if (sys_power_stat.BatteryLifePercent != 255)
        {
            cout << "Battery lifepercent is " << sys_power_stat.BatteryLifePercent << endl;;
        }

        if (sys_power_stat.SystemStatusFlag)
        {
            cout << "Battery saver on. Save energy where possible." << endl;
        }
        else
        {
            cout << "Battery saver is off." << endl;
        }

        if (sys_power_stat.BatteryFullLifeTime != -1)
        {
            cout << "Full lifetime of battery is " << sys_power_stat.BatteryFullLifeTime;
        }
        else
        {
            cout << "Device is connected to AC power." << endl;
        }

        if (sys_power_stat.BatteryLifeTime != -1)
        {
            cout << "Full lifetime of battery is " << sys_power_stat.BatteryFullLifeTime;
        }
        else
        {
            cout << "Device is connected to AC power." << endl;
        }
    }
}

int main()
{
    SystemPowerInfo();
    
}