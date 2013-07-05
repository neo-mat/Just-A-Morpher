/**
	@file Unit.hpp
	@brief Declares the unit class.
*/

#pragma once

#include "Just A Morpher.hpp"

#include <map>
#include <string>

namespace JustAMorpher
{
	/**
		@brief A unit in WoW.
	*/
	class Unit
	{
	private:

		/**
			@brief Display IDs.
		*/
		static std::map<unsigned long long, unsigned int> DisplayIDs;

		/**
			@brief Units and their native display IDs.
		*/
		static std::map<unsigned long long, unsigned int> NativeDisplayIDs;

		/**
			@brief CGUnit_C::UpdateDisplayInfo trampoline.
		*/
		static void (__thiscall* CGUnit_C__UpdateDisplayInfo_Trampoline)(size_t This, bool ForceUpdate);

		/**
			@brief The unit's address.
		*/
		size_t Address;

		/**
			@brief CGUnit_C::UpdateDisplayInfo hook.
		*/
		static void __fastcall CGUnit_C__UpdateDisplayInfo_Hook (size_t This, int, bool ForceUpdate);

		/**
			@brief Throw an exception if the unit is null.
		*/
		void ThrowIfNull () const;

		/**
			@brief Apply the CGUnit_C::UpdateDisplayInfo hook.
		*/
		void ApplyHook ();

	public:

		enum PlayerRaceDisplayID : unsigned int
		{
			HumanMale = 49,
			HumanFemale = 50,
			DwarfMale = 53,
			DwarfFemale = 54,
			NightElfMale = 55,
			NightElfFemale = 56,
			GnomeMale = 1563,
			GnomeFemale = 1564,
			DraeneiMale = 16125,
			DraeneiFemale = 16126,
			WorgenMale = 29422,
			WorgenFemale = 29423,

			OrcMale = 51,
			OrcFemale = 52,
			UndeadMale = 57,
			UndeadFemale = 58,
			TaurenMale = 59,
			TaurenFemale = 60,
			TrollMale = 1478,
			TrollFemale = 1479,
			BloodElfFemale = 15475,
			BloodElfMale = 15476,
			GoblinMale = 6894,
			GoblinFemale = 6895,

			MalePanda = 38551,
			FemalePanda = 38552,
		};

		enum PlayerRace : unsigned char
		{
			Human = 1,
			Orc,
			Dwarf,
			NightElf,
			Undead,
			Tauren,
			Gnome,
			Troll,
			Goblin,
			BloodElf,
			Draenei,

			Worgen = 22,

			PandarenNeutral = 24,
			PandarenAlliance,
			PandarenHorde,
		};

		enum UnitGender : unsigned char
		{
			Male,
			Female,
			Unknown,
		};

		/**
			@brief Unit ID constructor
			@param UnitID The unit ID of the unit.
		*/
		Unit (const std::string& UnitID);

		/**
			@brief Address constructor
			@param Address The address of the unit.
		*/
		Unit (size_t Address);

		/**
			@brief Get the unit's address.
			@return The unit's address.
		*/
		size_t GetAddress () const;

		/**
			@brief Get the unit's GUID.
			@return The unit's GUID.
		*/
		unsigned long long GetGUID () const;

		/**
			@brief Get the address of the unit's descriptors.
			@return The address of the unit's descriptors.
		*/
		size_t GetDescriptors () const;

		/**
			@brief Update the unit's model.
			@param ForceUpdate If true, update the unit's model even if it has not changed.
		*/
		void UpdateModel (bool ForceUpdate = true) const;

		/**
			@brief Get the unit's display ID.
			@return The unit's display ID.
		*/
		unsigned int GetDisplayID () const;

		/**
			@brief Set the unit's display ID.
			You must call UpdateModel to update the unit's model for the changes to be shown.
			@param DisplayID The unit's new display ID.
		*/
		void SetDisplayID (unsigned int DisplayID) const;

		/**
			@brief Get the unit's native display ID.
			@return The unit's native display ID.
		*/
		unsigned int GetNativeDisplayID () const;

		/**
			@brief Get the unit's scale.
			@return The unit's scale.
		*/
		float GetScale () const;
		
		/**
			@brief Set the unit's scale.
			You must call UpdateModel to update the unit's model for the changes to be shown.
			@param Scale The unit's new scale.
		*/
		void SetScale (float Scale) const;

		/**
			@brief Get the unit's mount's display ID.
			@return The unit's mount's display ID.
		*/
		unsigned int GetMountDisplayID () const;

		/**
			@brief Set the unit's mount's display ID.
			@param DisplayID The unit's mount's new display ID.
		*/
		void SetMountDisplayID (unsigned int DisplayID) const;

		/**
			@brief Get the display ID of a unit's item.
			@param Item The index of the item slot.
		*/
		unsigned int GetItemDisplayID (unsigned int Item) const;

		/**
			@brief Set the display ID of a unit's item.
			@param Item The index of the item slot.
			@param DisplayID The item's new display ID.
		*/
		void SetItemDisplayID (unsigned int Item, unsigned int DisplayID) const;
	};
}