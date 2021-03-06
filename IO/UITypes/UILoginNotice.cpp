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
#include "UILoginNotice.h"

#include "../../Graphics/Sprite.h"
#include "../Components/MapleButton.h"
#include "nlnx/nx.hpp"

namespace jrc
{
UILoginNotice::UILoginNotice(Message id)
{
    nl::node notice = nl::nx::ui["Login.img"]["Notice"];

    background = notice["backgrnd"][id == BLOCKED_ID ? "1" : "0"];
    text = {notice["text"][id], {17, 13}};

    buttons[BT_OK] = std::make_unique<MapleButton>(
        notice["BtYes"], Point<std::int16_t>{100, 100});

    position = {292, 200};
    dimension = {362, 219};
    active = true;

    Console::get().print("conStructed");
}

void UILoginNotice::draw(float alpha) const
{
    Console::get().print("draWering");
    background.draw(position);
    text.draw(position, alpha);

    UIElement::draw(alpha);
}

Button::State UILoginNotice::button_pressed(std::uint16_t)
{
    active = false;
    return Button::PRESSED;
}
} // namespace jrc
