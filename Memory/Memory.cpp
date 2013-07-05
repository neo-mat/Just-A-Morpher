/**
	@file Memory.cpp
	@brief Defines the Memory class.
*/

#include "Memory.hpp"

#include "MinHook/hook.h"

#include <exception>
#include <stdexcept>

CREATE_SINGLETON(Memory_);

#pragma warning (disable : 4325)

void* Memory_::Hook (size_t Address, void* Target)
{
	void* Original;
	MinHook::CreateHook(reinterpret_cast<void*>(Address), Target, &Original);
	MinHook::EnableHook(reinterpret_cast<void*>(Address));

	return Original;
}

Memory_::Memory_ ()
{
	MinHook::Initialize();
}

Memory_::~Memory_ ()
{
	MinHook::Uninitialize();
}

void Memory_::Write (size_t Address, const void* Bytes, size_t Size) const
{
	if(!WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(Address), Bytes, Size, nullptr))
	{
		throw std::runtime_error ("Unable to write memory: WriteProcessMemory failed.");
	}

	if(!FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<const void*>(Address), Size))
	{
		throw std::runtime_error ("Unable to write memory: FlushInstructionCache failed.");
	}
}

void Memory_::Read (size_t Address, void* Bytes, size_t Size) const
{
	if(!ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<const void*>(Address), Bytes, Size, nullptr))
	{
		throw std::runtime_error ("Unable to read memory: ReadProcessMemory failed.");
	}
}

size_t Memory_::Allocate (size_t Size, ProtectionType Protection) const
{
	size_t Address = reinterpret_cast<size_t>(VirtualAlloc(nullptr, Size, MEM_COMMIT, Protection));

	if(!Address)
	{
		throw std::runtime_error ("Unable to allocate memory: VirtualAlloc failed.");
	}

	return Address;
}

void Memory_::Free (size_t Address) const
{
	if(!VirtualFree(reinterpret_cast<void*>(Address), 0, MEM_RELEASE))
	{
		throw std::runtime_error ("Unable to free memory: VirtualFree failed.");
	}
}

void Memory_::Unhook (size_t Address)
{
	if(MinHook::DisableHook(reinterpret_cast<void*>(Address)))
	{
		throw std::logic_error ("The function is not hooked.");
	}
}

size_t Memory_::GetMainModule () const
{
	return reinterpret_cast<size_t>(GetModuleHandle(nullptr));
}

size_t Memory_::GetModule (const std::basic_string<TCHAR>& Name) const
{
	size_t BaseAddress = reinterpret_cast<size_t>(GetModuleHandle(Name.c_str()));

	if(!BaseAddress)
	{
		throw std::runtime_error ("Unable to get the module's base address: It does not exist.");
	}

	return BaseAddress;
}