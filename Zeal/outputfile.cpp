#include "outputfile.h"
#include "Zeal.h"
#include "StringUtil.h"
#include <fstream>

enum EquipSlot
{
  LeftEar,
  Head,
  Face,
  RightEar,
  Neck,
  Shoulder,
  Arms,
  Back,
  LeftWrist,
  RightWrist,
  Range,
  Hands,
  Primary,
  Secondary,
  LeftFinger,
  RightFinger,
  Chest,
  Legs,
  Feet,
  Waist,
  Ammo
};

static std::string IDToEquipSlot(int equipSlot)
{
  switch (equipSlot) {
    case LeftEar:
    case RightEar:    return "Ear";
    case Head:        return "Head";
    case Face:        return "Face";
    case Neck:        return "Neck";
    case Shoulder:    return "Shoulders";
    case Arms:        return "Arms";
    case Back:        return "Back";
    case LeftWrist:
    case RightWrist:  return "Wrist";
    case Range:       return "Range";
    case Hands:       return "Hands";
    case Primary:     return "Primary";
    case Secondary:   return "Secondary";
    case LeftFinger:
    case RightFinger: return "Fingers";
    case Chest:       return "Chest";
    case Legs:        return "Legs";
    case Feet:        return "Feet";
    case Waist:       return "Waist";
    case Ammo:        return "Ammo";
    default:{}break;
  }
  return "Unknown";
}

static bool ItemIsContainer(Zeal::EqStructures::EQITEMINFO* item)
{
  return item->OpenType == 0x1;
}

static bool ItemIosstackable(Zeal::EqStructures::EQITEMINFO* item)
{
  return ((item->Common.IsStackable) && (item->Common.SpellId == 0));
}

void OutputFile::export_inventory(std::vector<std::string>& args)
{
  std::string t = "\t"; // output spacer

  std::ostringstream oss;
  oss << "Location" << t << "Name" << t << "ID" << t << "Count" << t << "Slots" << std::endl;

  // Processing Equipment
  for (size_t i = 0; i < EQ_NUM_INVENTORY_SLOTS; ++i) {
    auto item = Zeal::EqGame::get_self()->CharInfo->InventoryItem[i];
    // EQITEMINFO->EquipSlot value only updates when a load happens. Don't use it for this.
    if (item != nullptr) {
      oss << IDToEquipSlot(i) << t << item->Name << t << item->Id << t << 1 << t << 0 << std::endl;
    }
    else {
      oss << IDToEquipSlot(i) << t << "Empty" << t << "0" << t << "0" << t << "0" << std::endl;
    }
  }

  // Processing Inventory Slots
  for (size_t i = 0; i < EQ_NUM_INVENTORY_PACK_SLOTS; ++i) {
    auto item = Zeal::EqGame::get_self()->CharInfo->InventoryPackItem[i];
    if (item != nullptr) {
      if (ItemIsContainer(item)) {
        int capacity = static_cast<int>(item->Container.Capacity);
        oss << "General" << i + 1 << t << item->Name << t << item->Id << t << 1 << t << capacity << std::endl;
        for (int j = 0; j < capacity; ++j) {
          auto bag_item = item->Container.Item[j];
          if (bag_item != nullptr) {
            int stack_count = ItemIosstackable(bag_item) ? static_cast<int>(bag_item->Common.StackCount) : 1;
            oss << "General" << i + 1 << "-Slot" << j + 1 << t << bag_item->Name << t << bag_item->Id << t << stack_count << t << 0 << std::endl;
          }
          else {
            oss << "General" << i + 1 << "-Slot" << j + 1 << t << "Empty" << t << "0" << t << "0" << t << "0" << std::endl;
          }
        }
      }
      else {
        int stack_count = ItemIosstackable(item) ? static_cast<int>(item->Common.StackCount) : 1;
        oss << "General" << i + 1 << t << item->Name << t << item->Id << t << stack_count << t << 0 << std::endl;
      }
    }
    else {
      oss << "General" << i + 1 << t << "Empty" << t << "0" << t << "0" << t << "0" << std::endl;
    }
  }

  // Process Cursor Item
  {
    auto item = Zeal::EqGame::get_self()->CharInfo->CursorItem;
    if (item != nullptr) {
      if (ItemIsContainer(item)) {
        int capacity = static_cast<int>(item->Container.Capacity);
        oss << "Held" << t << item->Name << t << item->Id << t << 1 << t << capacity << std::endl;
        for (int i = 0; i < capacity; ++i) {
          auto bag_item = item->Container.Item[i];
          if (bag_item != nullptr) {
            int stack_count = ItemIosstackable(bag_item) ? static_cast<int>(bag_item->Common.StackCount) : 1;
            oss << "Held" << "-Slot" << i + 1 << t << bag_item->Name << t << bag_item->Id << t << stack_count << t << 0 << std::endl;
          }
          else {
            oss << "Held" << "-Slot" << i + 1 << t << "Empty" << t << "0" << t << "0" << t << "0" << std::endl;
          }
        }
      }
      else {
        int stack_count = ItemIosstackable(item) ? static_cast<int>(item->Common.StackCount) : 1;
        oss << "Held" << t << item->Name << t << item->Id << t << stack_count << t << 0 << std::endl;
      }
    }
    else {
      oss << "Held" << t << "Empty" << t << "0" << t << "0" << t << "0" << std::endl;
    }
  }

  // Process Bank Items
  for (size_t i = 0; i < EQ_NUM_INVENTORY_BANK_SLOTS; ++i) {
    auto item = Zeal::EqGame::get_self()->CharInfo->InventoryBankItem[i];
    if (item != nullptr) {
      if (ItemIsContainer(item)) {
        int capacity = static_cast<int>(item->Container.Capacity);
        oss << "Bank" << i + 1 << t << item->Name << t << item->Id << t << 1 << t << capacity << std::endl;
        for (int j = 0; j < capacity; ++j) {
          auto bag_item = item->Container.Item[j];
          if (bag_item != nullptr) {
            int stack_count = ItemIosstackable(bag_item) ? static_cast<int>(bag_item->Common.StackCount) : 1;
            oss << "Bank" << i + 1 << "-Slot" << j + 1 << t << bag_item->Name << t << bag_item->Id << t << stack_count << t << 0 << std::endl;
          }
          else {
            oss << "Bank" << i + 1 << "-Slot" << j + 1 << t << "Empty" << t << "0" << t << "0" << t << "0" << std::endl;
          }
        }
      }
      else {
        int stack_count = ItemIosstackable(item) ? static_cast<int>(item->Common.StackCount) : 1;
        oss << "Bank" << i + 1 << t << item->Name << t << item->Id << t << stack_count << t << 0 << std::endl;
      }
    }
    else {
      oss << "Bank" << i + 1 << t << "Empty" << t << "0" << t << "0" << t << "0" << std::endl;
    }
  }

  //Zeal::EqGame::print_chat(oss.str()); // debug purposes

  std::string optional_name = "";
  if (args.size() > 2) {
    optional_name = args[2];
  }
  write_to_file(oss.str(), "Inventory", optional_name);
}

// This function on the Titanium client prints out the spell level and actual name of the spell.
// Unfortuantely, we currently lack functionality to figure out spell data solely based off of SpellId,
// so we'll settle for just printing out that information for now.
void OutputFile::export_spellbook(std::vector<std::string>& args)
{
  std::stringstream oss;

  oss << "Index\tSpell Id" << std::endl;
  for (size_t i = 0; i < EQ_NUM_SPELL_BOOK_SPELLS; ++i) {
    auto SpellId = Zeal::EqGame::get_self()->CharInfo->SpellBook[i];
    // EQITEMINFO->EquipSlot value only updates when a load happens. Don't use it for this.
    if (SpellId != USHRT_MAX) {
      oss << i << "\t" << SpellId << std::endl;
    }
  }

  //Zeal::EqGame::print_chat(oss.str()); // debug purposes

  std::string optional_name = "";
  if (args.size() > 2) {
    optional_name = args[2];
  }
  write_to_file(oss.str(), "Spellbook", optional_name);
}

void OutputFile::write_to_file(std::string data, std::string file_arg, std::string optional_name)
{
  std::string filename = optional_name;
  if (filename.empty()) {
    filename = Zeal::EqGame::get_self()->CharInfo->Name;
    filename += "-" + file_arg;
  }
  filename += ".txt";

  std::ofstream file;
  file.open(filename);
  file << data;
  file.close();
}

OutputFile::OutputFile(ZealService* zeal)
{
  zeal->commands_hook->add("/outputfile", { "/output", "/out" },
    [this](std::vector<std::string>& args) {
      if (args.size() == 1 || args.size() > 3)
      {
        Zeal::EqGame::print_chat("usage: /outputfile [inventory | spellbook] [optional filename]");
        return true;
      }
      if (args.size() > 1) {
        if (StringUtil::caseInsensitive(args[1], "inventory"))
          export_inventory(args);
        else if (StringUtil::caseInsensitive(args[1], "spellbook"))
          export_spellbook(args);
      }
      return true;
    }
  );
}
