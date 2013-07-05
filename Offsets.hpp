/**
	@file Offsets.hpp
	@brief Declares offsets.
*/

#pragma once

namespace JustAMorpher
{
	namespace Offsets
	{
		namespace Functions
		{
			enum : size_t
			{
				CGUnit_C__UpdateDisplayInfo = 0x003F7390,
				CGUnit_C__OnMountDisplayChanged = 0x003EEC81,
				CGUnit_C__UpdateScale = 0x003E9696,

				GetUnitFromName = 0x00465ACC,
				FrameScript__InvalidPtrCheck = 0x0010EE63,
				CGGameUI__Initialize = 0x00851B53,

				FrameScript__RegisterFunction = 0x00054012,
				FrameScript__ExecuteBuffer = 0x00054EE6,
				lua_gettop = 0x000D50FF,
				luaD_error = 0x000D66A1,
				lua_tolstring = 0x000D567F,
				lua_tonumber = 0x000D55C6,
				lua_pushnumber = 0x000D57C4,
			};
		}

		namespace Globals
		{
			enum : size_t
			{

			};
		}

		namespace Object
		{
			enum : size_t
			{
				Descriptors = 0x4,
				
				GUID = 0x0,
				Scale = 0x1C,
			};
		}

		namespace Unit
		{
			enum : size_t
			{
				MountDisplayID = 0xBBC,

				Race = 0x70,
				Gender = 0x72,
				DisplayID = 0x108,
				NativeDisplayID = 0x10C,
				ItemDisplayIDs = 0xE50,
			};
		}
	}
}