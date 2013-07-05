/**
	@file Main.cpp
	@brief Defines the entry point.
*/

#include "Just A Morpher.hpp"

#include "Loader.hpp"

using namespace JustAMorpher;

size_t JustAMorpher::WoWBase = 0;
HMODULE JustAMorpher::Module = nullptr;

int WINAPI DllMain (HMODULE Module, unsigned long, void*)
{
	WoWBase = reinterpret_cast<size_t>(GetModuleHandle(nullptr));
	JustAMorpher::Module = Module;

	Loader;

	DisableThreadLibraryCalls(Module);
	return 1;
}