/**
	@file Memory.hpp
	@brief Declares the Memory class.
*/

#pragma once

#include "..\Singleton.hpp"

#include <Windows.h>

#include <string>
#include <vector>

/**
	@brief Memory manager.
*/
class Memory_ : public Singleton <Memory_>
{
private:

	/**
		@brief Hook a function.
		@param Address The address of the function to hook. The memory must be readable.
		@param Destination The function that is the destination of the hook.
		@return A trampoline that can be used to call the function.
		@throw std::runtime_error Thrown if a Windows API function fails.
	*/
	void* Hook (size_t Address, void* Target);

public:

	/**
		@brief Memory protection type.
	*/
	enum ProtectionType : unsigned long
	{
		Execute = PAGE_EXECUTE,
		ExecuteRead = PAGE_EXECUTE_READ,
		ExecuteReadWrite = PAGE_EXECUTE_READWRITE,
		ExecuteWriteCopy = PAGE_EXECUTE_WRITECOPY,
		NoAccess = PAGE_NOACCESS,
		ReadWrite = PAGE_READWRITE,
		ReadOnly = PAGE_READONLY,
		WriteCopy = PAGE_WRITECOPY,

		Guard = PAGE_GUARD,
		NoCache = PAGE_NOCACHE,
		WriteCombine = PAGE_WRITECOMBINE,
	};

	/**
		@brief Default constructor
	*/
	Memory_ ();
	
	/**
		@brief Destructor
	*/
	~Memory_ ();

	/**
		@brief Write bytes to an address.
		@param Address The address to write the bytes to.
		@param Bytes The bytes to write.
		@param Size The total number of bytes to write.
		@throw std::runtime_error Thrown if a Windows API function fails.
	*/
	void Write (size_t Address, const void* Bytes, size_t Size) const;

	/**
		@brief Write an object to an address.
		@param Address The address to write the object to.
		@param Object The object to write.
		@throw std::runtime_error Thrown if a Windows API function fails.
	*/
	template <class Type>
	void Write (size_t Address, const Type& Object) const
	{
		this->Write(Address, &Object, sizeof(Type));
	}

	/**
		@brief Read bytes from an address.
		@param Address The address to read the bytes from.
		@param Bytes The buffer to copy the bytes to.
		@param Size The total number of bytes to read.
		@throw std::runtime_error Thrown if a Windows API function fails.
	*/
	void Read (size_t Address, void* Bytes, size_t Size) const;

	/**
		@brief Read an object from an address.
		@param Address The address to read the address from.
		@return A copy of the object.
		@throw std::runtime_error Thrown if a Windows API function fails.
	*/
	template <class Type>
	Type Read (size_t Address) const
	{
		Type Object;
		this->Read(Address, &Object, sizeof(Type));
		return Object;
	}

	/**
		@brief Get a reference to an object.

	*/

	/**
		@brief Allocate memory.
		@param Size The total number of bytes to allocate.
		@param Protection The memory page protection of the bytes.
		@return The address of the memory.
		@throw std::runtime_error Thrown if a Windows API function fails.
	*/
	size_t Allocate (size_t Size, ProtectionType Protection = ExecuteReadWrite) const;

	/**
		@brief Free memory.
		@param Address The address of the memory to free.
		@throw std::runtime_error Thrown if a Windows API function fails.
	*/
	void Free (size_t Address) const;

	/**
		@brief Hook a function.
		@param Address The address of the function to hook. The memory must be readable.
		@param Destination The function that is the destination of the hook.
		@return A trampoline that can be used to call the function.
		@throw std::runtime_error Thrown if a Windows API function fails.
	*/
	template <class Type>
	inline Type Hook (size_t Address, Type Target)
	{
		return reinterpret_cast<Type>(this->Hook(Address, static_cast<void*>(Target)));
	}

	/**
		@brief Unhook a function.
		@param Address The address of the function to unhook.
		@throw std::logic_error Thrown if the function is not hooked.
	*/
	void Unhook (size_t Address);

	/**
		@brief Get the base address of the main module.
		@return The base address of the main module.
	*/
	size_t GetMainModule () const;

	/**
		@brief Get a module.
		@param Name The name of the module.
		@return The base address of the module.
		@throw std::runtime_error Thrown if the module does not exist in the local process.
	*/
	size_t GetModule (const std::basic_string<TCHAR>& Name) const;
};

#define Memory Memory_::Get()