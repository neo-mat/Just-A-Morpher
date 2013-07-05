/**
	@file Unit.cpp
	@brief Defines the unit class.
*/

#include "Unit.hpp"

#include "Delegates.hpp"
#include "Offsets.hpp"

#include "Memory/Memory.hpp"

#include <exception>
#include <stdexcept>

using namespace JustAMorpher;

std::map<unsigned long long, unsigned int> Unit::DisplayIDs;
std::map<unsigned long long, unsigned int> Unit::NativeDisplayIDs;
void (__thiscall* Unit::CGUnit_C__UpdateDisplayInfo_Trampoline)(size_t This, bool ForceUpdate) = nullptr;

void __fastcall Unit::CGUnit_C__UpdateDisplayInfo_Hook (size_t This, int, bool ForceUpdate)
{
	Unit Unit (This);

	if(DisplayIDs[Unit.GetGUID()])
	{
		Unit.SetDisplayID(DisplayIDs[Unit.GetGUID()]);
	}

	CGUnit_C__UpdateDisplayInfo_Trampoline(This, ForceUpdate);
}

void Unit::ThrowIfNull () const
{
	if(!this->Address)
	{
		throw std::logic_error ("The unit is null.");
	}
}

void Unit::ApplyHook ()
{
	if(!CGUnit_C__UpdateDisplayInfo_Trampoline)
	{
		CGUnit_C__UpdateDisplayInfo_Trampoline = reinterpret_cast<decltype(CGUnit_C__UpdateDisplayInfo_Trampoline)>(Memory.Hook(WoWBase + Offsets::Functions::CGUnit_C__UpdateDisplayInfo, CGUnit_C__UpdateDisplayInfo_Hook));
	}
}

Unit::Unit (const std::string& UnitID)
{
	this->ApplyHook();

	this->Address = Delegates.GetUnitFromName(UnitID.c_str());

	if(!this->GetAddress())
	{
		throw std::runtime_error ("The unit does not exist.");
	}

	if(!NativeDisplayIDs[this->GetGUID()])
	{
		NativeDisplayIDs[this->GetGUID()] = this->GetDisplayID();
	}
}

Unit::Unit (size_t Address)
{
	this->ApplyHook();

	this->Address = Address;

	if(!NativeDisplayIDs[this->GetGUID()])
	{
		NativeDisplayIDs[this->GetGUID()] = this->GetDisplayID();
	}
}

size_t Unit::GetAddress () const
{
	return this->Address;
}

unsigned long long Unit::GetGUID () const
{
	this->ThrowIfNull();

	return *reinterpret_cast<unsigned long long*>(this->GetDescriptors() + Offsets::Object::GUID);
}

size_t Unit::GetDescriptors () const
{
	this->ThrowIfNull();

	return *reinterpret_cast<size_t*>(this->GetAddress() + Offsets::Object::Descriptors);
}

void Unit::UpdateModel (bool ForceUpdate) const
{
	this->ThrowIfNull();

	Delegates.CGUnit_C__UpdateDisplayInfo(this->GetAddress(), ForceUpdate);
	Delegates.CGUnit_C__UpdateScale(this->GetGUID());
}

unsigned int Unit::GetDisplayID () const
{
	this->ThrowIfNull();

	return *reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::DisplayID);
}

void Unit::SetDisplayID (unsigned int DisplayID) const
{
	this->ThrowIfNull();

	DisplayIDs[this->GetGUID()] = DisplayID;

	*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::DisplayID) = DisplayID;
	*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = NativeDisplayIDs[this->GetGUID()];

	switch(this->GetDisplayID())
	{
	case HumanMale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Human;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Male;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case HumanFemale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Human;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Female;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case DwarfMale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Dwarf;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Male;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case DwarfFemale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Dwarf;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Female;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case NightElfMale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = NightElf;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Male;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case NightElfFemale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = NightElf;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Female;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case GnomeMale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Gnome;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Male;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case GnomeFemale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Gnome;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Female;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case DraeneiMale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Draenei;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Male;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case DraeneiFemale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Draenei;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Female;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case WorgenFemale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Worgen;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Female;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case WorgenMale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Worgen;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Male;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case OrcMale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Orc;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Male;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case OrcFemale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Orc;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Female;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case UndeadMale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Undead;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Male;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case UndeadFemale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Undead;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Female;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case TaurenMale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Tauren;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Male;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case TaurenFemale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Tauren;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Female;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case TrollMale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Troll;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Male;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case TrollFemale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Troll;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Female;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case BloodElfMale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = BloodElf;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Male;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case BloodElfFemale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = BloodElf;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Female;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case GoblinMale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Goblin;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Male;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case GoblinFemale:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = Goblin;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Female;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case MalePanda:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = PandarenNeutral;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Male;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;

	case FemalePanda:

		*reinterpret_cast<PlayerRace*>(this->GetDescriptors() + Offsets::Unit::Race) = PandarenNeutral;
		*reinterpret_cast<UnitGender*>(this->GetDescriptors() + Offsets::Unit::Gender) = Female;
		*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::NativeDisplayID) = DisplayID;
		break;
	}
}

unsigned int Unit::GetNativeDisplayID () const
{
	this->ThrowIfNull();

	return NativeDisplayIDs[this->GetGUID()];
}

float Unit::GetScale () const
{
	this->ThrowIfNull();

	return *reinterpret_cast<float*>(this->GetDescriptors() + Offsets::Object::Scale);
}

void Unit::SetScale (float Scale) const
{
	this->ThrowIfNull();

	*reinterpret_cast<float*>(this->GetDescriptors() + Offsets::Object::Scale) = Scale;
}

unsigned int Unit::GetMountDisplayID() const
{
	this->ThrowIfNull();

	return *reinterpret_cast<unsigned int*>(this->GetAddress() + Offsets::Unit::MountDisplayID);
}

void Unit::SetMountDisplayID (unsigned int DisplayID) const
{
	this->ThrowIfNull();

	Delegates.CGUnit_C__OnMountDisplayChanged(this->GetAddress(), DisplayID);
}

unsigned int Unit::GetItemDisplayID (unsigned int Item) const
{
	this->ThrowIfNull();

	return *reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::ItemDisplayIDs + (Item * 8));
}

void Unit::SetItemDisplayID (unsigned int Item, unsigned int DisplayID) const
{
	this->ThrowIfNull();

	*reinterpret_cast<unsigned int*>(this->GetDescriptors() + Offsets::Unit::ItemDisplayIDs + (Item * 8)) = DisplayID;
}