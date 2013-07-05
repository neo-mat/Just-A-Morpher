/**
	@file Loader.hpp
	@brief Declares the loader class.
*/

#pragma once

#include "Just A Morpher.hpp"
#include "Singleton.hpp"

namespace JustAMorpher
{
	/**
		@brief Loads Lua code.
	*/
	class Loader_ : public Singleton <Loader_>
	{
	private:

		/**
			@brief If Just A Morpher has loaded the Lua code already.
		*/
		bool HasLoaded;

		/**
			@brief Trampoline for the GetUnitFromName hook.
		*/
		size_t (__cdecl* GetUnitFromName_Trampoline)(const char* UnitID);

		/**
			@brief Trampoline for the CGGameUI::Initialize hook.
		*/
		void (__cdecl* CGGameUI__Initialize_Trampoline)();

		/**
			@brief Hook for GetUnitFromName.
			@param UnitID The unit ID.
			@return The unit's address.
		*/
		static size_t __cdecl GetUnitFromName_Hook (const char* UnitID);

		/**
			@brief Hook for CGGameUI::Initialize.
		*/
		static void __cdecl CGGameUI__Initialize_Hook ();

		/**
			@brief Load all Lua files.
		*/
		void LoadLua () const;

	public:

		/**
			@brief Default constructor
		*/
		Loader_ ();
	};
}

#define Loader JustAMorpher::Loader_::Get()