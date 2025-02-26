#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include "resources.h"

#pragma comment(linker, "/ENTRY:mainCRTStartup")

void SetVolumeToMax()
{
    CoInitialize(nullptr);

    IMMDeviceEnumerator* pEnumerator = nullptr;
    IMMDevice* pDevice = nullptr;
    IAudioEndpointVolume* pVolume = nullptr;
    BOOL isMuted = FALSE;

    if (CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, IID_PPV_ARGS(&pEnumerator)) == S_OK)
    {
        if (pEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice) == S_OK)
        {
            if (pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pVolume) == S_OK)
            {
                pVolume->GetMute(&isMuted);
                
                if (isMuted)
                {
                    pVolume->SetMute(FALSE, nullptr);
                }

                pVolume->SetMasterVolumeLevelScalar(1.0f, nullptr);
            }
        }
    }

    if (pVolume) pVolume->Release();
    if (pDevice) pDevice->Release();
    if (pEnumerator) pEnumerator->Release();

    CoUninitialize();
}

void PlaySoundLoop()
{
    HMODULE hModule = GetModuleHandle(NULL);

    HRSRC hRes = FindResourceA(hModule, MAKEINTRESOURCE(IDR_WAV1), "WAVE");

    HGLOBAL hData = LoadResource(hModule, hRes);

    void* pData = LockResource(hData);
    DWORD dataSize = SizeofResource(hModule, hRes);

    PlaySound((LPCSTR)pData, hModule, SND_MEMORY | SND_LOOP | SND_ASYNC);
}

int main()
{
    
    PlaySoundLoop();
    while (true)
    {
        SetVolumeToMax();
        Sleep(1000);
    }

    return 0;
}
