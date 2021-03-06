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
#include "../../Graphics/Texture.h"
#include "BodyDrawInfo.h"

namespace jrc
{
class Body
{
public:
    enum Layer {
        NONE,
        BODY,
        ARM,
        ARM_BELOW_HEAD,
        ARM_BELOW_HEAD_OVER_MAIL,
        ARM_OVER_HAIR,
        ARM_OVER_HAIR_BELOW_WEAPON,
        HAND_BELOW_WEAPON,
        HAND_OVER_HAIR,
        HAND_OVER_WEAPON,
        HEAD,
        NUM_LAYERS
    };

    Body(std::int32_t skin, const BodyDrawinfo& draw_info);

    void draw(Stance::Id stance,
              Layer layer,
              std::uint8_t frame,
              const DrawArgument& args) const;

    std::string_view get_name() const noexcept;

    static Layer layer_by_name(const std::string& name);

private:
    std::unordered_map<std::uint8_t, Texture> stances[Stance::LENGTH]
                                                     [Layer::NUM_LAYERS];
    std::string name;

    static const std::unordered_map<std::string, Layer> layers_by_name;
};
} // namespace jrc
