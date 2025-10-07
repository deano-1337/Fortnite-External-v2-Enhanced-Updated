#pragma once

#include <winternl.h>
#include <intrin.h>
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <unordered_map>


inline uintptr_t Base;
inline int processID;
inline uintptr_t base_address = 0;

#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
)

#define IOCTL_GET_DIRECTORY_BASE_ADDRESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0xB4D5, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_READ_WRITE_OPERATION CTL_CODE(FILE_DEVICE_UNKNOWN, 0x7D82, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_MOUSE_MOVEMENT CTL_CODE(FILE_DEVICE_UNKNOWN, 0xE4F1, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_GET_BASE_ADDRESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6F3B, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define SECURITY_FLAG 0xD4F861
#define MOUSE_MOVE 61283

#define MOUSE_LEFT_BUTTON_DOWN   0x0001  // Left Button changed to down.
#define MOUSE_LEFT_BUTTON_UP     0x0002  // Left Button changed to up.

inline static bool EAC = true;

typedef struct _ReadWrite
{
	INT32 Security;
	INT32 ProcessID;
	ULONGLONG Address;
	ULONGLONG Buffer;
	ULONGLONG Size;
	BOOLEAN Write;
	BOOLEAN EAC;
} RW, * PRW;

typedef struct _MU
{
	long X;
	long Y;
	unsigned short ButtonFlags;
};

typedef struct _DTB
{
	INT32 Security;
	INT32 ProcessID;
	bool* Operation;
} DTB, * DTBL;

typedef struct _BA
{
	INT32 Security;
	INT32 ProcessID;
	ULONGLONG* Address;
} BA, * PBA;

namespace Driver
{
	inline HWND bWindowHandle;

	inline HANDLE DriverHandle;
	inline INT32 ProcessID;

	inline bool Init()
	{
		DriverHandle = CreateFileA(("\\\\.\\\JeremyBase"), GENERIC_READ | GENERIC_WRITE, 0, 0, 3, 0x00000080, 0);

		if (!DriverHandle || (DriverHandle == INVALID_HANDLE_VALUE))

			return false;

		return true;
	}

	inline void ReadPhysicalMemory(PVOID address, PVOID buffer, DWORD size)
	{
		_ReadWrite Arguments = { 0 };
		Arguments.Security = SECURITY_FLAG;
		Arguments.Address = (ULONGLONG)address;
		Arguments.Buffer = (ULONGLONG)buffer;
		Arguments.Size = size;
		Arguments.ProcessID = ProcessID;
		Arguments.Write = FALSE;
		if (EAC)
			Arguments.EAC = TRUE;
		else
			Arguments.EAC = FALSE;

		DeviceIoControl(DriverHandle, IOCTL_READ_WRITE_OPERATION, &Arguments, sizeof(Arguments), nullptr, NULL, NULL, NULL);
	}

	inline void WritePhysicalMemory(PVOID address, PVOID buffer, DWORD size)
	{
		_ReadWrite Arguments = { 0 };
		Arguments.Security = SECURITY_FLAG;
		Arguments.Address = (ULONGLONG)address;
		Arguments.Buffer = (ULONGLONG)buffer;
		Arguments.Size = size;
		Arguments.ProcessID = ProcessID;
		Arguments.Write = TRUE;
		if (EAC)
			Arguments.EAC = TRUE;
		else
			Arguments.EAC = FALSE;

		DeviceIoControl(DriverHandle, IOCTL_READ_WRITE_OPERATION, &Arguments, sizeof(Arguments), nullptr, NULL, NULL, NULL);
	}

	inline bool CR3()
	{
		bool Ret = false;
		_DTB arguments = { 0 };
		arguments.Security = SECURITY_FLAG;
		arguments.ProcessID = ProcessID;
		arguments.Operation = (bool*)&Ret;

		if (EAC)
		{
			DeviceIoControl(DriverHandle, IOCTL_GET_DIRECTORY_BASE_ADDRESS, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
		}
		else
		{
			return true;
		}

		return Ret;
	}

	inline uintptr_t GetBase()
	{
		uintptr_t image_address = { NULL };
		_BA Arguments = { NULL };

		Arguments.Security = SECURITY_FLAG;
		Arguments.ProcessID = ProcessID;
		Arguments.Address = (ULONGLONG*)&image_address;
		DeviceIoControl(DriverHandle, IOCTL_GET_BASE_ADDRESS, &Arguments, sizeof(Arguments), nullptr, NULL, NULL, NULL);

		return image_address;
	}

	inline HWND GetProcessWND(uint32_t pid)
	{

		std::pair<HWND, uint32_t> params = { 0, pid };
		BOOL bresult = EnumWindows([](HWND hwnd, LPARAM lparam) -> BOOL
			{
				auto pparams = (std::pair<HWND, uint32_t>*)(lparam);
				uint32_t processid = 0;
				if (GetWindowThreadProcessId(hwnd, reinterpret_cast<LPDWORD>(&processid)) && processid == pparams->second)
				{
					SetLastError((uint32_t)-1);
					pparams->first = hwnd;
					return FALSE;
				}
				return TRUE;
			}, (LPARAM)&params);
		if (!bresult && GetLastError() == -1 && params.first) return params.first;
		return 0;
	}

	inline void MoveMouse(long X, long Y, unsigned short ButtonFlags)
	{
		_MU Arguments = { 0 };
		Arguments.X = X + MOUSE_MOVE;
		Arguments.Y = Y + MOUSE_MOVE;
		Arguments.ButtonFlags = ButtonFlags;
		DeviceIoControl(DriverHandle, IOCTL_MOUSE_MOVEMENT, &Arguments, sizeof(Arguments), &Arguments, sizeof(Arguments), 0, 0);
	}

	inline INT32 FindProcess(LPCTSTR process_name)
	{

		PROCESSENTRY32 pt;
		HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pt.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hsnap, &pt)) {
			do {
				if (!lstrcmpi(pt.szExeFile, process_name))
				{
					CloseHandle(hsnap);
					ProcessID = pt.th32ProcessID;
					return pt.th32ProcessID;
				}
			} while (Process32Next(hsnap, &pt));
		}

		CloseHandle(hsnap);
		return ProcessID;
	}
}

template <typename T>
inline T read(uint64_t address)
{
	T buffer{ };
	Driver::ReadPhysicalMemory((PVOID)address, &buffer, sizeof(T));
	return buffer;
}
bool IsValidAddress(const uint64_t address)
{
	return address != 0 && address != 0xCCCCCCCCCCCCCCCC && address != 0xFFFFFFFFFFFFFFFF && address > 0x400000 && address <= 0x7FFFFFFFFFFFFFFF;
}
template <typename T>
inline T write(uint64_t address, T buffer)
{
	Driver::WritePhysicalMemory((PVOID)address, &buffer, sizeof(T));
	return buffer;
}
bool is_valid(const uint64_t address) {
	if (address <= 0x400000 || address == 0xCCCCCCCCCCCCCCCC || reinterpret_cast<void*>(address) == nullptr || address > 0x7FFFFFFFFFFFFFFF) {
		return false;
	}
	return true;
}




struct CachedRead {
	uint64_t address;
	uint64_t value;
	std::chrono::steady_clock::time_point timestamp;
};

class ReadCache {
private:
	std::unordered_map<uint64_t, CachedRead> cache;
	std::vector<uint64_t> addresses;
	static constexpr int MAX_CACHE_AGE_MS = 100;

public:
	void Add(uint64_t address) {
		addresses.push_back(address);
	}

	void ReadAll() {
		for (auto addr : addresses) {
			uint64_t value = read<uint64_t>(addr); 
			cache[addr] = { addr, value, std::chrono::steady_clock::now() };
		}
		addresses.clear(); 
	}

	template<typename T>
	T Get(uint64_t address) {
		auto it = cache.find(address);
		if (it != cache.end()) {
			auto age = std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::steady_clock::now() - it->second.timestamp
			).count();

			if (age < MAX_CACHE_AGE_MS) {
				return static_cast<T>(it->second.value);
			}
		}
		return T{}; 
	}

	template<typename T>
	bool TryGetCached(uint64_t address, T& out) {
		auto it = cache.find(address);
		if (it != cache.end()) {
			auto age = std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::steady_clock::now() - it->second.timestamp
			).count();

			if (age < MAX_CACHE_AGE_MS) {
				out = static_cast<T>(it->second.value);
				return true;
			}
		}
		return false;
	}

	void Store(uint64_t address, uint64_t value) {
		cache[address] = { address, value, std::chrono::steady_clock::now() };
	}

	void Clear() {
		cache.clear();
		addresses.clear();
	}
};

inline ReadCache g_readCache;

template <typename T>
inline T read_cached(uint64_t address) {
	T result;
	if (!g_readCache.TryGetCached(address, result)) {
		result = read<T>(address);
		if constexpr (sizeof(T) == sizeof(uint64_t)) {
			g_readCache.Store(address, static_cast<uint64_t>(result));
		}
	}
	return result;
}

struct BatchReadRequest {
	uint64_t address;
	void* buffer;
	size_t size;
};

inline void BatchRead(const std::vector<BatchReadRequest>& requests) {
	for (const auto& req : requests) {
		Driver::ReadPhysicalMemory((PVOID)req.address, req.buffer, req.size);
	}
}