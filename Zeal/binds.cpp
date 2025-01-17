#include "binds.h"
#include "EqStructures.h"
#include "EqAddresses.h"
#include "EqFunctions.h"
#include "Zeal.h"
Binds::~Binds()
{
}

void ExecuteCmd(int cmd, int isdown, int unk2)
{
	ZealService* zeal = ZealService::get_instance();
	if (!Zeal::EqGame::game_wants_input()) //checks if the game wants keyboard input... don't call our binds when the game wants input
	{
		//if (isdown)
		//	Zeal::EqGame::print_chat("cmd: %i", cmd);
		if (zeal->binds_hook->ReplacementFunctions.count(cmd) > 0)
		{
			if (zeal->binds_hook->ReplacementFunctions[cmd](isdown)) //if the replacement function returns true, end here otherwise its really just adding more to the command 
				return;
		}

		if (zeal->binds_hook->KeyMapFunctions.count(cmd) > 0)
			zeal->binds_hook->KeyMapFunctions[cmd](isdown);
		else
			zeal->hooks->hook_map["executecmd"]->original(ExecuteCmd)(cmd, isdown, unk2);
	}
	else
	{
		zeal->hooks->hook_map["executecmd"]->original(ExecuteCmd)(cmd, isdown, unk2);
	}
}

void __fastcall InitKeyboardAssignments(int t, int unused)
{
	ZealService* zeal = ZealService::get_instance();
	zeal->binds_hook->ptr_binds = t;
	zeal->binds_hook->add_binds();
	zeal->binds_hook->read_ini();
	zeal->hooks->hook_map["initbinds"]->original(InitKeyboardAssignments)(t, unused);
}


UINT32 read_internal_from_ini(int index, int key_type)
{
	int fn = 0x525520;
	__asm
	{
		push key_type
		push index
		call fn
		pop ecx
		pop ecx
	}
}

void Binds::read_ini()
{
	int size = sizeof(KeyMapNames) / sizeof(KeyMapNames[0]);
	for (int i = 128; i < size; i++) //the game will load its own properly
	{
		if (KeyMapNames[i]) //check if its not nullptr
		{
			int keycode = read_internal_from_ini(i, 0);
			int keycode_alt = read_internal_from_ini(i, 1);
			if (keycode != -0x2)
			{
				Zeal::EqGame::ptr_PrimaryKeyMap[i] = keycode;
			}
			if (keycode_alt != -0x2)
			{
				Zeal::EqGame::ptr_AlternateKeyMap[i] = keycode_alt;
			}

		}
	}
}

void Binds::set_strafe(strafe_direction dir) 
{
	//slightly revised so the game properly sets speed based on encumber and handles the stance checks
	if (dir == strafe_direction::None || !Zeal::EqGame::can_move())
	{
		current_strafe = strafe_direction::None;
		*Zeal::EqGame::strafe_direction = 0;
		*Zeal::EqGame::strafe_speed = 0;
		if (orig_reset_strafe[0]!=0)
			mem::copy(0x53f424, orig_reset_strafe, 7);
	}
	else
	{
		if (orig_reset_strafe[0] == 0)
			mem::set(0x53f424, 0x90, 7, orig_reset_strafe);
		else if (*(BYTE*)0x53f424 != 0x90)
			mem::set(0x53f424, 0x90, 7);

	
		if (dir == strafe_direction::Right)
		{
			current_strafe = strafe_direction::Right;
			*Zeal::EqGame::strafe_direction = 0x2;
		}
		else
		{
			current_strafe = strafe_direction::Left;
			*Zeal::EqGame::strafe_direction = 0x1;
		}
	}
}

void Binds::add_binds()
{
	//just start binds at 211 to avoid overwriting any existing cmd/bind
	add_bind(211, "Strafe Left", "StrafeLeft", key_category::Movement, [this](int key_down) {

		if (!key_down && current_strafe==strafe_direction::Left)
			set_strafe(strafe_direction::None);
		else if (key_down)
			set_strafe(strafe_direction::Left);
	});
	add_bind(212, "Strafe Right", "StrafeRight", key_category::Movement, [this](int key_down) {
		if (!key_down && current_strafe == strafe_direction::Right)
			set_strafe(strafe_direction::None);
		else if (key_down)
			set_strafe(strafe_direction::Right);
	});
	add_bind(213, "Cycle through nearest NPCs", "CycleTargetNPC", key_category::Target, [](int key_down) {

		if (key_down && !Zeal::EqGame::EqGameInternal::UI_ChatInputCheck())
		{
			Zeal::EqStructures::Entity* ent = ZealService::get_instance()->cycle_target->get_next_ent(250, 1);
			if (ent)
				Zeal::EqGame::set_target(ent);
		}
	});
	add_bind(214, "Cycle through nearest PCs", "CycleTargetPC", key_category::Target, [](int key_down) {
		if (key_down && !Zeal::EqGame::EqGameInternal::UI_ChatInputCheck())
		{
			Zeal::EqStructures::Entity* ent = ZealService::get_instance()->cycle_target->get_next_ent(250, 0);
			if (ent)
				Zeal::EqGame::set_target(ent);
		}
		});
	add_bind(215, "Toggle all containers", "OpenCloseContainers", key_category::UI | key_category::Commands, [](int key_down) {
		if (key_down && !Zeal::EqGame::EqGameInternal::UI_ChatInputCheck())
		{
			Zeal::EqStructures::Entity* self = Zeal::EqGame::get_self();
			std::vector<std::pair<Zeal::EqStructures::_EQITEMINFO*,int>> containers;
			std::vector<Zeal::EqStructures::_EQITEMINFO*> opened_containers; //don't need an index to close 
			for (int i = 0; i < 8; i++) //8 inventory slots for containers
			{
				Zeal::EqStructures::_EQITEMINFO* item = self->CharInfo->InventoryPackItem[i];
				if (item && item->OpenType==1 && item->Container.Capacity>0)
				{
					containers.push_back({ item, i });
					if (item->Container.IsOpen)
						opened_containers.push_back(item);
				}
			}
			if (opened_containers.size() == containers.size()) //all the containers are open..
			{
				Zeal::EqGame::EqGameInternal::CloseAllContainers(*Zeal::EqGame::ptr_ContainerMgr, 0);
			}
			else
			{
				for (auto& [c, index] : containers)
				{
					if (!c->Container.IsOpen)
						Zeal::EqGame::EqGameInternal::OpenContainer(*Zeal::EqGame::ptr_ContainerMgr, 0, (int)&c->Name, 22 + index);
				}
			}


		}
		});
	add_bind(216, "Toggle last two targets", "ToggleLastTwo", key_category::Target, [this](int key_down) {
		if (key_down && !Zeal::EqGame::EqGameInternal::UI_ChatInputCheck())
		{
			Zeal::EqStructures::Entity* target = Zeal::EqGame::get_target();
			if (target)
			{
				if (last_targets.first == target->SpawnId && last_targets.second!=0)
				{
					Zeal::EqStructures::Entity* ent = Zeal::EqGame::get_entity_by_id(last_targets.second);
					if (ent)
						Zeal::EqGame::set_target(ent);
				}
			}
			else
			{
				if (last_targets.first != 0)
				{
					Zeal::EqStructures::Entity* ent = Zeal::EqGame::get_entity_by_id(last_targets.first);
					if (ent)
						Zeal::EqGame::set_target(ent);
				}
			}
		}
		});
	add_bind(255, "Auto Inventory", "AutoInventory", key_category::Commands | key_category::Macros, [](int key_down) {

		if (key_down)
		{
			int a1 = *Zeal::EqGame::ptr_LocalPC;
			int a2 = a1 + 0xD78;
			Zeal::EqGame::EqGameInternal::auto_inventory(a1, a2, 0);
		}
	});
}

void Binds::add_bind(int cmd, const char* name, const char* short_name, int category, std::function<void(int state)> callback)
{

	char* str = new char[64]; 
	strcpy_s(str, 64, short_name);
	KeyMapNames[cmd] = str;

	int options = ZealService::get_instance()->binds_hook->ptr_binds;
	if (!options)
		return;
	Zeal::EqGame::EqGameInternal::InitKeyBindStr((options + cmd * 0x8 + 0x20c), 0, (char*)name);
	*(int*)((options + cmd * 0x8 + 0x210)) = category;
	KeyMapFunctions[cmd] = callback;
}

void Binds::replace_bind(int cmd, std::function<bool(int state)> callback)
{
	ReplacementFunctions[cmd] = callback;
}

void Binds::main_loop()
{

	if (Zeal::EqGame::get_target() && Zeal::EqGame::get_target()->SpawnId != last_targets.first)
	{
		last_targets.second = last_targets.first;
		last_targets.first = Zeal::EqGame::get_target()->SpawnId;
	}

	if (current_strafe != strafe_direction::None)
	{
		Zeal::EqStructures::Entity* controlled_player = Zeal::EqGame::get_controlled();
		float encumberance = Zeal::EqGame::encum_factor();
		*Zeal::EqGame::strafe_speed = encumberance + encumberance;
		if (controlled_player->IsSneaking || controlled_player->StandingState == Stance::Duck)
			*Zeal::EqGame::strafe_speed *= .5f;
		if (controlled_player->ActorInfo && controlled_player->ActorInfo->MovementSpeedModifier < 0)
			*Zeal::EqGame::strafe_speed *= .5f;
		if (controlled_player->ActorInfo && controlled_player->ActorInfo->Unsure_Strafe_Calc != 0)
			*Zeal::EqGame::strafe_speed *= .25f;
		if (controlled_player->ActorInfo && controlled_player->ActorInfo->MovementSpeedModifier < -1000.0f)
		{
			*Zeal::EqGame::strafe_direction = 0;
			*Zeal::EqGame::strafe_speed = 0;
		}
		if (controlled_player->StandingState != Stance::Duck && controlled_player->StandingState != Stance::Stand)
		{
			*Zeal::EqGame::strafe_direction = 0;
			*Zeal::EqGame::strafe_speed = 0;
		}
	}
}

void Binds::on_zone()
{
	Zeal::EqGame::print_chat("zoned");
	last_targets.first = 0;
	last_targets.second = 0;
}


Binds::Binds(ZealService* zeal)
{
	zeal->main_loop_hook->add_callback([this]() { main_loop(); }, callback_fn::MainLoop);
	zeal->main_loop_hook->add_callback([this]() { on_zone(); }, callback_fn::Zone);
	for (int i = 0; i < 128; i++)
		KeyMapNames[i] = *(char**)(0x611220 + (i * 4)); //copy the original short names to the new array
	mem::write(0x52507A, (int)KeyMapNames);//write ini keymap
	mem::write(0x5254D9, (int)KeyMapNames);//clear ini keymap
	mem::write(0x525544, (int)KeyMapNames);//read ini keymap
	mem::write(0x42C52F, (byte)0xEB); //remove the check for max index of 116 being stored in client ini
	mem::write(0x52485A, (int)256); //increase this for loop to look through all 256
	mem::write(0x52591C, (int)(Zeal::EqGame::ptr_AlternateKeyMap + (256 * 4))); //fix another for loop to loop through all 256
	zeal->hooks->Add("initbinds", Zeal::EqGame::EqGameInternal::fn_initkeyboardassignments, InitKeyboardAssignments, hook_type_detour);
	zeal->hooks->Add("executecmd", Zeal::EqGame::EqGameInternal::fn_executecmd, ExecuteCmd, hook_type_detour);
}
