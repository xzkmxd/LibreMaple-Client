//////////////////////////////////////////////////////////////////////////////
// This file is part of the LibreMaple MMORPG client                        //
// Copyright © 2015-2016 Daniel Allendorf, 2018-2019 LibreMaple Team        //
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
#include "../../Gameplay/Movement.h"
#include "../OutPacket.h"

namespace jrc
{
//! Base class for packets which update object movements with the server.
class MovementPacket : public OutPacket
{
public:
    MovementPacket(OutPacket::Opcode opc) : OutPacket(opc)
    {
    }

protected:
    void writemovement(const Movement& movement)
    {
        write_byte(movement.command);
        write_short(movement.xpos);
        write_short(movement.ypos);
        write_short(movement.lastx);
        write_short(movement.lasty);
        write_short(movement.fh);
        write_byte(movement.newstate);
        write_short(movement.duration);
    }
};
} // namespace jrc
