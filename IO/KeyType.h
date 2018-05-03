//////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright © 2015-2016 Daniel Allendorf                                   //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#pragma once
#include <cstdint>

namespace jrc
{
namespace KeyType
{
// Keytypes determine how a keycode is interpreted.
enum Id {
    NONE = 0,
    SKILL = 1,
    ITEM = 2,
    CASH = 3,
    MENU = 4,
    ACTION = 5,
    FACE = 6,
    MACRO = 8,
    LETTER = 9,
    NUMBER = 10,
    LENGTH
};

inline Id typebyid(uint8_t id)
{
    if (id <= NONE || id >= LENGTH)
        return NONE;

    return static_cast<Id>(id);
}
} // namespace KeyType
} // namespace jrc
