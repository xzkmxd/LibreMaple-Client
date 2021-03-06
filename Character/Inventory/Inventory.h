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
#include "../../Template/EnumMap.h"
#include "../../Template/nullable_ptr.h"
#include "../Look/EquipSlot.h"
#include "Equip.h"
#include "InventoryType.h"
#include "Item.h"
#include "Pet.h"
#include "Weapon.h"
#include "boost/container/flat_map.hpp"

#include <unordered_map>

namespace jrc
{
//! The player's inventory.
class Inventory
{
public:
    enum Movement : std::int8_t {
        MOVE_NONE = -1,
        MOVE_INTERNAL = 0,
        MOVE_UNEQUIP = 1,
        MOVE_EQUIP = 2
    };

    enum Modification : std::int8_t {
        ADD,
        CHANGE_COUNT,
        SWAP,
        REMOVE,
        ADD_COUNT
    };

    //! Return the move type by value.
    static Movement movement_by_value(std::int8_t value);

    Inventory();

    //! Recalculate sums of equip stats.
    void recalc_stats(Weapon::Type weapontype);
    //! Set the meso amount.
    void set_meso(std::int64_t meso);
    //! Set the number of slots for a given inventory.
    void set_slotmax(InventoryType::Id type, std::uint8_t value);

    //! Modify the inventory with info from a packet.
    void modify(InventoryType::Id type,
                std::int16_t pos,
                std::int8_t mode,
                std::int16_t arg,
                Movement movement);
    //! Add a general item.
    void add_item(InventoryType::Id type,
                  std::int16_t slot,
                  std::int32_t itemid,
                  bool cash,
                  std::int64_t expire,
                  std::uint16_t count,
                  const std::string& owner,
                  std::int16_t flag);
    //! Add a pet item.
    void add_pet(InventoryType::Id type,
                 std::int16_t slot,
                 std::int32_t itemid,
                 bool cash,
                 std::int64_t expire,
                 const std::string& name,
                 std::int8_t level,
                 std::int16_t closeness,
                 std::int8_t fullness);
    //! Add an equip item.
    void add_equip(InventoryType::Id type,
                   std::int16_t slot,
                   std::int32_t itemid,
                   bool cash,
                   std::int64_t expire,
                   std::uint8_t slots,
                   std::uint8_t level,
                   const EnumMap<Equipstat::Id, std::uint16_t>& stats,
                   const std::string& owner,
                   std::int16_t flag,
                   std::uint8_t itemlevel,
                   std::uint16_t itemexp,
                   std::int32_t vicious);

    //! Check if the use inventory contains at least one projectile.
    bool has_projectile() const;
    //! Return if an equip is equipped in the specfied slot.
    bool has_equipped(Equipslot::Id slot) const;
    //! Return the currently active projectile slot.
    std::int16_t get_bullet_slot() const;
    //! Return the count of the currently active projectile.
    std::uint16_t get_bullet_count() const;
    //! Return the item_id of the currently active projectile.
    std::int32_t get_bullet_id() const;
    //! Return the number of slots for the specified inventory.
    std::uint8_t get_slotmax(InventoryType::Id type) const;
    //! Return a total stat.
    std::uint16_t get_stat(Equipstat::Id type) const;
    //! Return the amount of meso.
    std::int64_t get_meso() const;
    //! Find a free slot for the specified equip.
    Equipslot::Id find_equip_slot(std::int32_t itemid) const;
    //! Find a free slot in the specfified inventory.
    std::int16_t find_free_slot(InventoryType::Id type) const;
    //! Return the first slot which contains the specified item.
    std::int16_t find_item(InventoryType::Id type, std::int32_t itemid) const;
    //! Return the count of an item. Returns 0 if the slot is empty.
    std::int16_t get_item_count(InventoryType::Id type,
                                std::int16_t slot) const;
    //! Return the id of an item. Returns 0 if the slot is empty.
    std::int32_t get_item_id(InventoryType::Id type, std::int16_t slot) const;

    //! Return a pointer to an equip.
    nullable_ptr<const Equip> get_equip(InventoryType::Id type,
                                        std::int16_t slot) const;

private:
    //! Add an inventory slot and return the unique_id.
    std::int32_t add_slot(InventoryType::Id type,
                          std::int16_t slot,
                          std::int32_t item_id,
                          std::int16_t count,
                          bool cash);
    //! Change the quantity of an item.
    void change_count(InventoryType::Id type,
                      std::int16_t slot,
                      std::int16_t count);
    //! Swap two items.
    void swap(InventoryType::Id first_type,

              std::int16_t first_slot,
              InventoryType::Id second_type,
              std::int16_t second_slot);
    //! Remove an item.
    void remove(InventoryType::Id type, std::int16_t slot);

    struct Slot {
        std::int32_t unique_id;
        std::int32_t item_id;
        std::int16_t count;
        bool cash;
    };

    EnumMap<InventoryType::Id, boost::container::flat_map<std::int16_t, Slot>>
        inventories;
    std::unordered_map<std::int32_t, Item> items;
    std::unordered_map<std::int32_t, Equip> equips;
    std::unordered_map<std::int32_t, Pet> pets;
    std::int32_t running_uid;

    EnumMap<Equipstat::Id, std::uint16_t> total_stats;
    EnumMap<InventoryType::Id, std::uint8_t> slotmaxima;
    std::int64_t meso;
    std::int16_t bullet_slot;
};
} // namespace jrc
