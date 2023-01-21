#ifndef KLONOA_MEM_H
#define KLONOA_MEM_H

#include "pine.h"

class KlonoaMemory {
public:
    static const uint IRQC_ADDRESS = 0x0036EAC0;
    static const uint GAMEGBL_VISION = 0x00366454;
    static const uint GAMEGBL_ADDRESS = 0x00366450;
    static const uint GAMEGBL_KLONOA_ADDRESS = 0x003667DC;
    static const uint OBJWORK_BUFF_ADDRESS = 0x00366BB0;
    static const uint LEVEL_PACK_PTR_ADDRESS = 0x003FC2E8;
    static const uint VT_WAVE_ADDRESS = 0x003FB940;
    static const uint HRBGBIN_ADDRESS = 0x00332A90;
    static const uint HRI_ANM_ADDRESS = 0x003FA718;
    static const uint CAMFIX_ADDRESS = 0x003FC45C;
    static const uint VICON_ADDRESS = 0x00518C10;
    static const uint RPCARG_ADDRESS = 0x0040efa0;
    static const uint RPCRECVBUF_ADDRESS = 0x00417200;
    static const uint SNDMAINBUFFER_ADDRESS = 0x00417300;

    static bool IsValidPointer(uint ptr) {
        return ptr != 0 && ptr < 0x2000000;
    }

    PINE::PCSX2* ipc;
    char* ps2_ram;

    KlonoaMemory()  {
        ipc = new PINE::PCSX2();
        ps2_ram = (char*)malloc(32 * 1024 * 1024); // 32 MB
    }

    ~KlonoaMemory() {
        delete ipc;
        free(ps2_ram);
    }

    template <class T>
    T Read(uint address) {
        return ipc->Read<T>(address);
    }

    char* Read(uint address, uint size) {
        for (int i = 0; i < size; i++) {
            ps2_ram[address + i] = ipc->Read<char>(address + i);
        }
        return ps2_ram + address;
    }

    template <class T>
    T* ReadObj(uint address) {
        return (T*)Read(address, sizeof(T));
    }

    template <class T>
    inline void Write(uint address, T value) {
        ipc->Write<T>(address, value);
    }

    template <class T>
    inline void WriteObj(uint address) {
        for (int i = 0; i < sizeof(T); i++) {
            ipc->Write<char>(address + i, *(ps2_ram + address + i));
        }
    }

    // Class to traverse the game's archive files
    class FHM {
    public:
        inline uint GetAddress(KlonoaMemory* mem) {
            return ((char*)this - mem->ps2_ram);
        }

        uint GetCount(KlonoaMemory* mem) {
            return mem->Read<uint>(GetAddress(mem));
        }

        uint GetFileAddress(KlonoaMemory* mem, uint index) {
            uint addr = GetAddress(mem);
            return addr + mem->Read<uint>(addr + 4 + index * 4);
        }

        template <class T>
        T* ReadObj(KlonoaMemory* mem, uint index) {
            uint address = GetFileAddress(mem, index);
            return mem->ReadObj<T>(address);
        }

        FHM* ReadFHM(KlonoaMemory* mem, uint index) {
            uint address = GetFileAddress(mem, index);
            return mem->ReadFHM(address);
        }
    };

    FHM* ReadFHM(uint address) {
        return (FHM *)(ps2_ram + address);
    }
};

#endif
