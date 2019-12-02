#include <iostream>
#include "../lib/include/uFCoder.h"
using namespace std;

UFR_HANDLE hndUFR[10];
int32_t NumberOfDevices;

int main()
{
    UFR_STATUS status = ReaderList_UpdateAndGetCount(&NumberOfDevices);

    c_string DeviceSerialNumber[NumberOfDevices];

    UFR_HANDLE DeviceHandle;
    int DeviceType, DeviceFW, DeviceCommID, DeviceCommSpeed;
    c_string DeviceCommFTDISerial;
    c_string DeviceCommFTDIDescription;
    int DeviceIsOpened, DeviceStatus;

    if(!status)
    {
        for(int i = 0; i < NumberOfDevices; i++)
        {
            status = ReaderList_GetInformation(&DeviceHandle, &DeviceSerialNumber[i], &DeviceType, &DeviceFW, &DeviceCommID, &DeviceCommSpeed, &DeviceCommFTDISerial, &DeviceCommFTDIDescription, &DeviceIsOpened, &DeviceStatus);
            ReaderList_OpenByIndex(i, &hndUFR[i]);
        }
    }
    else
    {
        printf("Error, cannot count readers: %s", UFR_Status2String(status));
        return 1;
    }

    char c = 0;

    printf("---------------------------------------------\n");
    printf("Select reader to beep:\n");

    for(int i = 0; i < NumberOfDevices; i++)
    {
        printf("%d.%s\n", i + 1, DeviceSerialNumber[i]);
    }

    printf("0. exit\n");
    printf("---------------------------------------------\n");

    do
    {
        c = getchar();

        uint8_t index = c - 0x30;

        status = ReaderUISignalM(hndUFR[index - 1], 1, 1);
        printf("%s\n", UFR_Status2String(status));

        fflush(stdin);
    }
    while(c != '0');

    return 0;
}
