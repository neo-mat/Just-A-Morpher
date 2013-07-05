/**
	@file Delegates.hpp
	@brief Declares the delegates class.
*/

#pragma once

#include "Just A Morpher.hpp"
#include "Offsets.hpp"
#include "Singleton.hpp"

namespace JustAMorpher
{
	/**
		@brief Delegates.
	*/
	class Delegates_ : public Singleton <Delegates_>
	{
	public:

		/**
			@brief Default constructor
		*/
		inline Delegates_ ()
		{
			CGUnit_C__UpdateDisplayInfo = reinterpret_cast<decltype(CGUnit_C__UpdateDisplayInfo)>(WoWBase + Offsets::Functions::CGUnit_C__UpdateDisplayInfo);
			CGUnit_C__OnMountDisplayChanged = reinterpret_cast<decltype(CGUnit_C__OnMountDisplayChanged)>(WoWBase + Offsets::Functions::CGUnit_C__OnMountDisplayChanged);
			CGUnit_C__UpdateScale = reinterpret_cast<decltype(CGUnit_C__UpdateScale)>(WoWBase + Offsets::Functions::CGUnit_C__UpdateScale);
			
			GetUnitFromName = reinterpret_cast<decltype(GetUnitFromName)>(WoWBase + Offsets::Functions::GetUnitFromName);

			FrameScript__RegisterFunction = reinterpret_cast<decltype(FrameScript__RegisterFunction)>(WoWBase + Offsets::Functions::FrameScript__RegisterFunction);
			FrameScript__ExecuteBuffer = reinterpret_cast<decltype(FrameScript__ExecuteBuffer)>(WoWBase + Offsets::Functions::FrameScript__ExecuteBuffer);
			lua_gettop = reinterpret_cast<decltype(lua_gettop)>(WoWBase + Offsets::Functions::lua_gettop);
			luaD_error = reinterpret_cast<decltype(luaD_error)>(WoWBase + Offsets::Functions::luaD_error);
			lua_tolstring = reinterpret_cast<decltype(lua_tolstring)>(WoWBase + Offsets::Functions::lua_tolstring);
			lua_tonumber = reinterpret_cast<decltype(lua_tonumber)>(WoWBase + Offsets::Functions::lua_tonumber);
			lua_pushnumber = reinterpret_cast<decltype(lua_pushnumber)>(WoWBase + Offsets::Functions::lua_pushnumber);
		}

		void (__thiscall* CGUnit_C__UpdateDisplayInfo)(size_t Object, bool ForceUpdate);
		void (__thiscall* CGUnit_C__OnMountDisplayChanged)(size_t Object, unsigned int DisplayID);
		void (__cdecl* CGUnit_C__UpdateScale)(unsigned long long GUID);

		size_t (__cdecl* GetUnitFromName)(const char* UnitID);

		void (__cdecl* FrameScript__RegisterFunction)(const char* Name, int (__cdecl* Function)(void*));
		void (__cdecl* FrameScript__ExecuteBuffer)(const char* String, const char* Name, void* Tainted);
		int (__cdecl* lua_gettop)(void* State);
		void (__cdecl* luaD_error)(void* State, const char* Message, void** Unknown);
		const char* (__cdecl* lua_tolstring)(void* State, int Index, size_t* Length);
		double (__cdecl* lua_tonumber)(void* State, int Index);
		void (__cdecl* lua_pushnumber)(void* State, double Value);
	};
}

#define Delegates JustAMorpher::Delegates_().Get()