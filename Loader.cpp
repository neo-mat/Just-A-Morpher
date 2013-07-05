/**
	@file Loader.cpp
	@brief Defines the loader class.
*/

#include "Loader.hpp"
#include "Lua.hpp"
#include "Offsets.hpp"

#include "Memory/Memory.hpp"

#include <Windows.h>

#include <fstream>

using namespace JustAMorpher;

CREATE_SINGLETON(Loader_);

size_t __cdecl Loader_::GetUnitFromName_Hook (const char* UnitID)
{
	if(!Loader.HasLoaded)
	{
		Loader.HasLoaded = true;

		Loader.LoadLua();
		Lua.DoString("print(\"[|c0000FFFFJust A Morpher|r] Loaded.\")", "Loaded Message");
	}

	return Loader.GetUnitFromName_Trampoline(UnitID);
}

void __cdecl Loader_::CGGameUI__Initialize_Hook ()
{
	Loader.HasLoaded = true;
	Loader.CGGameUI__Initialize_Trampoline();
	Loader.LoadLua();
}

void Loader_::LoadLua () const
{
	Lua.RegisterFunctions();

	char FileName [MAX_PATH];
	GetModuleFileName(Module, FileName, MAX_PATH);

	for(size_t Index = strlen(FileName); Index >= 0; Index--)
	{
		if(FileName[Index] == '\\')
		{
			break;
		}

		FileName[Index] = '\0';
	}

	WIN32_FIND_DATA FindData;
	ZeroMemory(&FindData, sizeof(WIN32_FIND_DATA));

	void* FindFile = FindFirstFile((std::string(FileName) + "Scripts\\*").c_str(), &FindData);
	do 
	{
		if(!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && strlen(FindData.cFileName) && strcmp(FindData.cFileName, ".") && strcmp(FindData.cFileName, ".."))
		{
			std::fstream File (std::string(FileName) + "Scripts\\" + FindData.cFileName, std::ios::in);

			std::string String;
			while(true)
			{
				std::string Line;
				std::getline(File, Line);

				String.append(Line);

				if(!File.good())
				{
					break;
				}

				String.append("\n");
			}

			Lua.DoString(String, FindData.cFileName);
		}
	}
	while(FindNextFile(FindFile, &FindData));
	FindClose(FindFile);
}

Loader_::Loader_ ()
{
	this->HasLoaded = false;
	this->GetUnitFromName_Trampoline = Memory.Hook(WoWBase + Offsets::Functions::GetUnitFromName, GetUnitFromName_Hook);
	this->CGGameUI__Initialize_Trampoline = Memory.Hook(WoWBase + Offsets::Functions::CGGameUI__Initialize, CGGameUI__Initialize_Hook);
}