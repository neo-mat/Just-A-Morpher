/**
	@file Lua.hpp
	@brief Declares the Lua class.
*/

#pragma once

#include "Just A Morpher.hpp"
#include "Singleton.hpp"

namespace JustAMorpher
{
	/**
		@brief Lua functions.
	*/
	class Lua_ : public Singleton <Lua_>
	{
	private:

		/**
			@brief Update a unit's model
			@param State The Lua state.
		*/
		static int __cdecl UpdateModel (void* State);

		/**
			@brief Set the display ID a unit.
			@param State The Lua state.
		*/
		static int __cdecl SetDisplayID (void* State);

		/**
			@brief Get the display ID of a unit.
			@param State The Lua state.
		*/
		static int __cdecl GetDisplayID (void* State);

		/**
			@brief Get the native display ID of a unit.
			@param State The Lua state.
		*/
		static int __cdecl GetNativeDisplayID (void* State);

		/**
			@brief Set the display ID of a unit's mount.
			@param State The Lua state.
		*/
		static int __cdecl SetMountDisplayID (void* State);

		/**
			@brief Get the display ID of a unit's mount.
			@param State The Lua state.
		*/
		static int __cdecl GetMountDisplayID (void* State);

		/**
			@brief Set the scale of a unit.
			@param State The Lua state.
		*/
		static int __cdecl SetScale (void* State);

		/**
			@brief Get the scale of a unit.
			@param State The Lua state.
		*/
		static int __cdecl GetScale (void* State);

		/**
			@brief Set the display ID of a unit's item.
			@param State The Lua state.
		*/
		static int __cdecl SetItemDisplayID (void* State);

		/**
			@brief Get the display ID of a unit's item.
			@param State The Lua state.
		*/
		static int __cdecl GetItemDisplayID (void* State);

		/**
			@brief Register a Lua function.
			@param Name The name of the function.
			@param Function The function.
		*/
		void RegisterFunction (const std::string& Name, int (__cdecl* Function)(void*)) const;

		/**
			@brief Get the total number of arguments.
			@param State The Lua state.
			@return The total number of arguments.
		*/
		unsigned int GetArgumentCount (void* State) const;

		/**
			@brief Throw a Lua error.
			@param State The Lua state.
			@param The error string.
		*/
		void Error (void* State, const std::string& String) const;

		/**
			@brief Get a value from Lua's stack as a string.
			@param State The Lua state.
			@param Index The index of the argument.
		*/
		std::string ToString (void* State, int Index) const;

		/**
			@brief Get a value from Lua's stack as a number.
			@param State The Lua state.
			@param Index The index of the argument.
		*/
		double ToNumber (void* State, int Index) const;

		/**
			@brief Push a number onto Lua's stack.
			@param State The Lua state.
			@param Value The number.
		*/
		void PushNumber (void* State, double Value) const;

	public:

		/**
			@brief Default constructor
		*/
		Lua_ ();

		/**
			@brief Execute a Lua string.
			@param String The string.
			@param Name The name of the string.
		*/
		void DoString (const std::string& String, const std::string& Name) const;

		/**
			@brief Register Lua functions.
		*/
		void RegisterFunctions () const;
	};
}

#define Lua JustAMorpher::Lua_::Get()