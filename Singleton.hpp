/**
	@file Singleton.hpp
	@brief Declares and defines the singleton class.
*/

#pragma once

#include <exception>
#include <stdexcept>

/**
	@brief A class that may only have one instance.
*/
template <class Type>
class Singleton
{
private:

	/**
		@brief The single class instance.
	*/
	static Type* Instance;

	/**
		@brief Copy constructor
		@param Other The object to copy from.
	*/
	inline Singleton (const Singleton& Other)
	{

	}

protected:

	/**
		@brief Default constructor
	*/
	Singleton ()
	{
		if(Instance)
		{
			throw std::logic_error ("A singleton may only have one instance.");
		}
	}

	/**
		@brief Destructor
	*/
	~Singleton ()
	{
		if(Instance)
		{
			Type* InstanceCopy = Instance;
			Instance = nullptr;
			delete InstanceCopy;
		}
	}

public:

	/**
		@brief Get the instance.
		@return A reference to the instance.
	*/
	static Type& Get ()
	{
		if(!Instance)
		{
			Instance = new Type;
		}

		return *Instance;
	}
};

#define CREATE_SINGLETON(Type) Type* Singleton<Type>::Instance = nullptr;