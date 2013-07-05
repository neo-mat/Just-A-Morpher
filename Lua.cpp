/**
	@file Lua.cpp
	@brief Defines the Lua class.
*/

#include "Lua.hpp"

#include "Delegates.hpp"
#include "Unit.hpp"

#include "Memory/Memory.hpp"

using namespace JustAMorpher;

CREATE_SINGLETON(Lua_);

int __cdecl Lua_::UpdateModel (void* State)
{
	try
	{
		if(Lua.GetArgumentCount(State) < 1)
		{
			throw std::logic_error ("Usage: UpdateModel (UnitID)");
		}

		std::string UnitID = Lua.ToString(State, 1);
		Unit (UnitID).UpdateModel(true);
	}
	catch(std::exception& Exception)
	{
		Lua.Error(State, Exception.what());
	}

	return 0;
}

int __cdecl Lua_::SetDisplayID (void* State)
{
	try
	{
		if(Lua.GetArgumentCount(State) < 2)
		{
			throw std::logic_error ("Usage: SetDisplayID (UnitID, DisplayID)");
		}

		std::string UnitID = Lua.ToString(State, 1);
		Unit (UnitID).SetDisplayID(Lua.ToNumber(State, 2));
	}
	catch(std::exception& Exception)
	{
		Lua.Error(State, Exception.what());
	}

	return 0;
}

int __cdecl Lua_::GetDisplayID (void* State)
{
	try
	{
		if(Lua.GetArgumentCount(State) < 1)
		{
			throw std::logic_error ("Usage: GetDisplayID (UnitID)");
		}

		std::string UnitID = Lua.ToString(State, 1);
		Lua.PushNumber(State, Unit (UnitID).GetDisplayID());

		return 1;
	}
	catch(std::exception& Exception)
	{
		Lua.Error(State, Exception.what());
	}

	return 0;
}

int __cdecl Lua_::GetNativeDisplayID (void* State)
{
	try
	{
		if(Lua.GetArgumentCount(State) < 1)
		{
			throw std::logic_error ("Usage: GetNativeDisplayID (UnitID)");
		}

		std::string UnitID = Lua.ToString(State, 1);
		Lua.PushNumber(State, Unit (UnitID).GetNativeDisplayID());

		return 1;
	}
	catch(std::exception& Exception)
	{
		Lua.Error(State, Exception.what());
	}

	return 0;
}

int __cdecl Lua_::SetMountDisplayID (void* State)
{
	try
	{
		if(Lua.GetArgumentCount(State) < 2)
		{
			throw std::logic_error ("Usage: SetMountDisplayID (UnitID, DisplayID)");
		}

		std::string UnitID = Lua.ToString(State, 1);
		Unit (UnitID).SetMountDisplayID(Lua.ToNumber(State, 2));
	}
	catch(std::exception& Exception)
	{
		Lua.Error(State, Exception.what());
	}

	return 0;
}

int __cdecl Lua_::GetMountDisplayID (void* State)
{
	try
	{
		if(Lua.GetArgumentCount(State) < 1)
		{
			throw std::logic_error ("Usage: GetMountDisplayID (UnitID)");
		}

		std::string UnitID = Lua.ToString(State, 1);
		Lua.PushNumber(State, Unit (UnitID).GetMountDisplayID());

		return 1;
	}
	catch(std::exception& Exception)
	{
		Lua.Error(State, Exception.what());
	}

	return 0;
}

int __cdecl Lua_::SetScale (void* State)
{
	try
	{
		if(Lua.GetArgumentCount(State) < 2)
		{
			throw std::logic_error ("Usage: SetScale (UnitID, Scale)");
		}

		std::string UnitID = Lua.ToString(State, 1);
		Unit (UnitID).SetScale(Lua.ToNumber(State, 2));
	}
	catch(std::exception& Exception)
	{
		Lua.Error(State, Exception.what());
	}

	return 0;
}

int __cdecl Lua_::GetScale (void* State)
{
	try
	{
		if(Lua.GetArgumentCount(State) < 1)
		{
			throw std::logic_error ("Usage: GetScale (UnitID)");
		}

		std::string UnitID = Lua.ToString(State, 1);
		Lua.PushNumber(State, Unit (UnitID).GetScale());

		return 1;
	}
	catch(std::exception& Exception)
	{
		Lua.Error(State, Exception.what());
	}

	return 0;
}

int __cdecl Lua_::SetItemDisplayID (void* State)
{
	try
	{
		if(Lua.GetArgumentCount(State) < 3)
		{
			throw std::logic_error ("Usage: SetItemDisplayID (UnitID, Item, DisplayID)");
		}

		std::string UnitID = Lua.ToString(State, 1);
		Unit (UnitID).SetItemDisplayID(Lua.ToNumber(State, 2), Lua.ToNumber(State, 3));
	}
	catch(std::exception& Exception)
	{
		Lua.Error(State, Exception.what());
	}

	return 0;
}

int __cdecl Lua_::GetItemDisplayID (void* State)
{
	try
	{
		if(Lua.GetArgumentCount(State) < 2)
		{
			throw std::logic_error ("Usage: GetItemDisplayID (UnitID, Item)");
		}

		std::string UnitID = Lua.ToString(State, 1);
		Lua.PushNumber(State, Unit (UnitID).GetItemDisplayID(Lua.ToNumber(State, 2)));
		
		return 1;
	}
	catch(std::exception& Exception)
	{
		Lua.Error(State, Exception.what());
	}

	return 0;
}

void Lua_::RegisterFunction (const std::string& Name, int (__cdecl* Function)(void*)) const
{
	Delegates.FrameScript__RegisterFunction(Name.c_str(), Function);
}

unsigned int Lua_::GetArgumentCount (void* State) const
{
	return Delegates.lua_gettop(State);
}

void Lua_::Error (void* State, const std::string& String) const
{
	Delegates.luaD_error(State, String.c_str(), &State);
}

std::string Lua_::ToString (void* State, int Index) const
{
	return Delegates.lua_tolstring(State, Index, nullptr);
}

double Lua_::ToNumber (void* State, int Index) const
{
	return Delegates.lua_tonumber(State, Index);
}

void Lua_::PushNumber (void* State, double Value) const
{
	Delegates.lua_pushnumber(State, Value);
}

Lua_::Lua_ ()
{
	unsigned char InvalidPtrCheck_Patch [] = { 0xEB, 0x22 };
	Memory.Write(WoWBase + Offsets::Functions::FrameScript__InvalidPtrCheck + 0x2C, InvalidPtrCheck_Patch, sizeof(InvalidPtrCheck_Patch));
}

void Lua_::DoString (const std::string& String, const std::string& Name) const
{
	Delegates.FrameScript__ExecuteBuffer(String.c_str(), Name.c_str(), nullptr);
}

void Lua_::RegisterFunctions () const
{
	this->RegisterFunction("UpdateModel", UpdateModel);
	this->RegisterFunction("SetDisplayID", SetDisplayID);
	this->RegisterFunction("GetDisplayID", GetDisplayID);
	this->RegisterFunction("GetNativeDisplayID", GetNativeDisplayID);
	this->RegisterFunction("SetMountDisplayID", SetMountDisplayID);
	this->RegisterFunction("GetMountDisplayID", GetMountDisplayID);
	this->RegisterFunction("SetScale", SetScale);
	this->RegisterFunction("GetScale", GetScale);
	this->RegisterFunction("SetItemDisplayID", SetItemDisplayID);
	this->RegisterFunction("GetItemDisplayID", GetItemDisplayID);
}