#ifndef KLONOA_MEM_H
#define KLONOA_MEM_H

#include "pine.h"
#include "common.h"

class KlonoaMemory {
public:
    static const u32 IRQC_ADDRESS = 0x0036EAC0;
    static const u32 GAMEGBL_VISION = 0x00366454;
    static const u32 GAMEGBL_ADDRESS = 0x00366450;
    static const u32 GAMEGBL_KLONOA_ADDRESS = 0x003667DC;
    static const u32 LEVEL_PACK_PTR_ADDRESS = 0x003FC2E8;
    static const u32 VT_WAVE_ADDRESS = 0x003FB940;
    static const u32 HRBGBIN_ADDRESS = 0x00332A90;
    static const u32 HRI_ANM_ADDRESS = 0x003FA718;
    static const u32 CAMNOR_ADDRESS = 0x003FC458;
    static const u32 CAMFIX_ADDRESS = 0x003FC45C;
    static const u32 VICON_ADDRESS = 0x00518C10;
    static const u32 RPCARG_ADDRESS = 0x0040efa0;
    static const u32 RPCRECVBUF_ADDRESS = 0x00417200;
    static const u32 SNDMAINBUFFER_ADDRESS = 0x00417300;
    static const u32 HFMIRCNT_ADDRESS = 0x003FA4E4;
    static const u32 HFMIRBUF_ADDRESS = 0x00334BC0;

    static KlonoaMemory* Instance;

    static bool IsValidPointer(u32 ptr) {
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
    T Read(u32 address) {
        return ipc->Read<T>(address);
    }

    char* Read(u32 address, u32 size) {
        u32 i = 0;
        while (i != size) {
            if (size - i >= 8) {
                *(u64 *)&ps2_ram[address + i] = ipc->Read<u64>(address + i);
                i += 8;
            } else {
                ps2_ram[address + i] = ipc->Read<char>(address + i);
                i++;
            }
        }
        return ps2_ram + address;
    }

    template <class T>
    T* ReadObj(u32 address) {
        return (T*)Read(address, sizeof(T));
    }

    template <class T>
    inline void Write(u32 address, T value) {
        ipc->Write<T>(address, value);
    }

    template <class T>
    inline void WriteObj(u32 address) {
        for (int i = 0; i < sizeof(T); i++) {
            ipc->Write<char>(address + i, *(ps2_ram + address + i));
        }
    }

    // Class to traverse the game's archive files
    class FHM {
    public:
        inline u32 GetAddress(KlonoaMemory* mem) {
            return ((char*)this - mem->ps2_ram);
        }

        u32 GetCount(KlonoaMemory* mem) {
            return mem->Read<u32>(GetAddress(mem));
        }

        u32 GetFileAddress(KlonoaMemory* mem, u32 index) {
            u32 addr = GetAddress(mem);
            return addr + mem->Read<u32>(addr + 4 + index * 4);
        }

        template <class T>
        T* ReadObj(KlonoaMemory* mem, u32 index) {
            u32 address = GetFileAddress(mem, index);
            return mem->ReadObj<T>(address);
        }

        FHM* ReadFHM(KlonoaMemory* mem, u32 index) {
            u32 address = GetFileAddress(mem, index);
            return mem->ReadFHM(address);
        }
    };

    FHM* ReadFHM(u32 address) {
        return (FHM *)(ps2_ram + address);
    }
};

#endif
