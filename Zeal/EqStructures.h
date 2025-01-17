#pragma once
//some structure information was found here
//https://github.com/kevrgithub/eqmac/

#include <Windows.h>
#include "vectors.h"
#define EQ_NUM_COMMANDS 277 // 0-276
#define EQ_NUM_BUFFS 15
#define EQ_NUM_SPELLS 4000
#define EQ_NUM_SPELL_GEMS 8
#define EQ_NUM_GROUP_MEMBERS 5
#define EQ_NUM_INVENTORY_SLOTS 21
#define EQ_NUM_INVENTORY_PACK_SLOTS 8
#define EQ_NUM_INVENTORY_BANK_SLOTS 8
#define EQ_NUM_SKILLS 74
#define EQ_NUM_SPELL_BOOK_SPELLS 250 // 32 pages, 8 spells per page, should be 256?
#define EQ_NUM_SPAWNS 8192
#define EQ_NUM_GUILDS 512
#define EQ_NUM_LOOT_WINDOW_ITEMS 30
#define EQ_NUM_HOTBUTTONS 10
#define EQ_NUM_HOTBUTTONS_TOTAL 100
#define EQ_NUM_CONTAINER_SLOTS 10
namespace Zeal
{
	namespace EqEnums
	{
		enum EntityTypes
		{
			Player,
			NPC,
			NPCCorpse,
			PlayerCorpse,
			Unknown
		};
		enum CameraView
		{
			FirstPerson,
			ThirdPerson1,
			ThirdPerson2,
			ThirdPerson3,
			ThirdPerson4,
			ZealCam,
			TotalCameras
		};
		enum Stance
		{
			Sitting = 110,
			Ducking = 111,
			Standing = 100,
			Frozen = 102,
			Looting = 105,
			Feigned = 115,
			Dead = 120
		};
		enum ClassTypes
		{
			Warrior = 1,
			Cleric = 2,
			Paladin = 3,
			Ranger = 4,
			Shadowknight = 5,
			Druid = 6,
			Monk = 7,
			Bard = 8,
			Rogue = 9,
			Shaman = 10,
			Necromancer = 11,
			Wizard = 12,
			Magician = 13,
			Enchanter = 14,
			Beastlord = 15,
			Banker = 16,
			Merchant = 32
		};


	}
	namespace EqStructures
	{

		struct KeyboardModifiers
		{
			int Shift;
			int Ctrl;
			int Alt;
		};

		struct KeyboardInput
		{
			int forward;
			int back;
			int right;
			int left;
		};

		struct EQCXSTR
		{
			/* 0x0000*/ DWORD Font; // 1,6 = Window Title or Button Text, 8 = Hot Button Small Text
			/* 0x0004*/ DWORD MaxLength;
			/* 0x0008*/ DWORD Length;
			/* 0x000C*/ DWORD Encoding; // 0 = ASCII, 1 = Unicode
			/* 0x0010*/ PCRITICAL_SECTION Lock;
			/* 0x0014*/ CHAR Text[1]; // use Length and MaxLength
		};

		struct EQCXRECT
		{
			DWORD X1;
			DWORD Y1;
			DWORD X2;
			DWORD Y2;
		};

		struct EQFONT
		{
			/* 0x0000 */ DWORD Unknown0000;
			/* 0x0004 */ DWORD Size;
		};


		struct EQWND
		{
			/* 0x0000 */ DWORD Unknown0000; // struct _CSIDLWNDVFTABLE *pvfTable; struct _CXWNDVFTABLE *pvfTable;
			/* 0x0004 */ DWORD MouseHoverTimer;
			/* 0x0008 */ DWORD Unknown0008; // usually equals 2000
			/* 0x000C */ DWORD Unknown000C; // usually equals 500
			/* 0x0010 */ BYTE Unknown0010;
			/* 0x0011 */ BYTE Unknown0011;
			/* 0x0012 */ BYTE IsLocked;
			/* 0x0013 */ BYTE Unknown0013;
			/* 0x0014 */ PVOID Unknown0014;
			/* 0x0018 */ DWORD Unknown0018;
			/* 0x001C */ EQWND* ParentWnd;
			/* 0x0020 */ EQWND* FirstChildWnd;
			/* 0x0024 */ EQWND* NextSiblingWnd;
			/* 0x0028 */ BYTE HasChildren;
			/* 0x0029 */ BYTE HasSiblings;
			/* 0x002A */ BYTE Unknown0030[2];
			/* 0x002C */ DWORD Flags;
			/* 0x0030 */ EQCXRECT Location;
			/* 0x0040 */ EQCXRECT LocationPlaceholder; // used when minimizing the window
			/* 0x0050 */ BYTE IsVisible; // show
			/* 0x0051 */ BYTE IsEnabled;
			/* 0x0052 */ BYTE IsMinimized;
			/* 0x0053 */ BYTE Unknown0053;
			/* 0x0054 */ BYTE IsOpen;
			/* 0x0055 */ BYTE Unknown0055;
			/* 0x0056 */ BYTE IsMouseOver; // mouse is hovering over
			/* 0x0057 */ BYTE Unknown0057;
			/* 0x0058 */ DWORD WindowStyleFlags;
			/* 0x005C */ EQFONT* FontPointer;
			/* 0x0060 */ EQCXSTR Text;
			/* 0x0064 */ EQCXSTR ToolTipText;
			/* 0x0068 */ BYTE Unknown0068[28];
			/* 0x0084 */ EQCXSTR XmlToolTipText;
			/* 0x0088 */ BYTE Unknown0088[22];
			/* 0x009E */ BYTE AlphaTransparency;
			/* 0x009F */ BYTE Unknown009F;
			/* 0x00A0 */ BYTE ZLayer;
			/* 0x00A1 */ BYTE Unknown00A1[7];
			/* 0x00A8 */ DWORD DrawTemplate;
			/* 0x00AC */
		};


		struct CXSTR {
			/*0x00*/   DWORD   Font;            // maybe, dont know.  04 = Window 01 = button
			/*0x04*/   DWORD   MaxLength;
			/*0x08*/   DWORD   Length;
			/*0x0c*/   BOOL    Encoding; // 0: ASCII, 1:Unicode
			/*0x10*/   PCRITICAL_SECTION pLock;
			/*0x14*/   CHAR    Text[1]; // Stub, can be anywhere from Length to MaxLength (which is how much is malloc'd to this CXStr)
		};

		struct CXWndManager
		{
			/* 0x0000 */ BYTE unknown0[0x30];
			/* 0x0030 */ int ptr_focused_wnd;
			/* 0x0034 */ BYTE unknown34[0x8];
			/* 0x0030 */ int ptr_hovered_wnd;
		};
		typedef struct _EQITEMCOMMONINFO
		{
			/* 0x00E4 */ INT8 Strength;       // STR
			/* 0x00E5 */ INT8 Stamina;        // STA
			/* 0x00E6 */ INT8 Charisma;       // CHA
			/* 0x00E7 */ INT8 Dexterity;      // DEX
			/* 0x00E8 */ INT8 Intelligence;   // INT
			/* 0x00E9 */ INT8 Agility;        // AGI
			/* 0x00EA */ INT8 Wisdom;         // WIS
			/* 0x00EB */ INT8 SaveMagic;      // SV MAGIC
			/* 0x00EC */ INT8 SaveFire;       // SV FIRE
			/* 0x00ED */ INT8 SaveCold;       // SV COLD
			/* 0x00EE */ INT8 SaveDisease;    // SV DISEASE
			/* 0x00EF */ INT8 SavePoison;     // SV POISON
			/* 0x00F0 */ INT16 Health;        // HP
			/* 0x00F2 */ INT16 Mana;          // Mana
			/* 0x00F4 */ INT16 ArmorClass;    // AC
			/* 0x00F6 */ BYTE Unknown0246[2];
			/* 0x00F8 */ BYTE Light;
			/* 0x00F9 */ BYTE AttackDelay;    // Atk Delay
			/* 0x00FA */ BYTE Damage;         // DMG
			/* 0x00FB */ BYTE IsStackableEx;
			/* 0x00FC */ BYTE Range;
			/* 0x00FD */ BYTE Skill;
			/* 0x00FE */ BYTE Magic;
			/* 0x00FF */ BYTE CastingLevelEx;
			/* 0x0100 */ BYTE Material; // 0=None, 1=Leather, 2=Chain, 3=Plate, 4=Silk, etc
			/* 0x0101 */ BYTE Unknown0258[3];
			/* 0x0104 */ DWORD Color;
			/* 0x0108 */ BYTE Unknown0264[2];
			/* 0x010A */ WORD SpellIdEx;
			/* 0x010C */ WORD Classes; // bitwise flag
			/* 0x010E */ BYTE Unknown0270[2];
			/* 0x0110 */ WORD Races; // bitwise flag
			/* 0x0112 */ BYTE Unknown0274[2];
			/* 0x0114 */ BYTE IsStackable;
			/* 0x0115 */ BYTE CastingLevel; // also weapon proc level
			union
			{
				/* 0x0116 */ BYTE StackCount;
				/* 0x0116 */ BYTE Charges;
			};
			/* 0x0117 */ BYTE EffectType;
			/* 0x0118 */ WORD SpellId;
			/* 0x011A */ BYTE Unknown0123[10];
			/* 0x0124 */ WORD SkillModId;
			/* 0x0126 */ INT8 SkillModPercent;
			/* ...... */
		} EQITEMCOMMONINFO, * PEQITEMCOMMONINFO;
		typedef struct _EQITEMCONTAINERINFO
		{
			/* 0x00E4 */ struct _EQITEMINFO* Item[EQ_NUM_CONTAINER_SLOTS];
			/* 0x010C */ BYTE Combine;
			/* 0x010D */ BYTE Capacity; // num slots
			/* 0x010E */ BYTE IsOpen;
			/* 0x010F */ BYTE SizeCapacity;
			/* 0x0110 */ BYTE WeightReduction; // percent
			/* ...... */
		} EQITEMCONTAINERINFO, * PEQITEMCONTAINERINFO;
		typedef struct _EQITEMBOOKINFO
		{
			/* 0x00E4 */ BYTE Unknown0228[3];
			/* 0x00E7 */ CHAR File[15];
			/* ...... */
		} EQITEMBOOKINFO, * PEQITEMBOOKINFO;
		typedef struct _EQITEMINFO
		{
			/* 0x0000 */ CHAR Name[64]; // [0x40]
			/* 0x0040 */ CHAR LoreName[80]; // [0x50]
			/* 0x0090 */ CHAR IdFile[6]; // [0x06]
			/* 0x0096 */ BYTE Unknown0096[24];
			/* 0x00AE */ BYTE Weight; // multiply by 0.1 for actual decimal weight
			/* 0x00AF */ BYTE NoRent; // 0x00 = True, 0xFF = False
			/* 0x00B0 */ BYTE NoDrop; // 0x00 = True, 0xFF = False
			/* 0x00B1 */ BYTE Size; // EQ_ITEM_SIZE_x
			/* 0x00B2 */ BYTE OpenType; //0x1 = bag, 0x2 = letter
			/* 0x00B3 */ BYTE Unknown00B3;
			/* 0x00B4 */ WORD Id;
			/* 0x00B6 */ WORD Icon;
			/* 0x00B8 */ DWORD EquipSlot;
			/* 0x00BC */ DWORD EquippableSlots; // flag
			/* 0x00C0 */ DWORD Cost; // value in copper, sells to merchant for value
			/* 0x00C4 */ BYTE Unknown00C4[32];
			union
			{
				/* 0x00E4 */ EQITEMCOMMONINFO    Common;
				/* 0x00E4 */ EQITEMCONTAINERINFO Container;
				/* 0x00E4 */ EQITEMBOOKINFO      Book;
			};
			/* ...... */
		} EQITEMINFO, * PEQITEMINFO;

		struct ViewActor
		{
			/* 0x0000 */ DWORD Unknown0000;
			/* 0x0004 */ DWORD Unknown0004;
			/* 0x0008 */ DWORD Unknown0008;
			/* 0x000C */ DWORD Unknown000C;
			/* 0x0010 */ Vec3 Position;
			/* 0x001C */ DWORD Unknown001C;
			/* 0x0020 */ DWORD Unknown0020;
			/* 0x0024 */ DWORD Unknown0024;
			/* 0x0028 */ DWORD RegionNumber;
			/* 0x002C */ struct _EQACTORCOLLISIONINFO* CollisionInfo;
			/* 0x0030 */ DWORD Unknown0030;
			/* 0x0034 */ FLOAT ScaleFactor;
			/* 0x0038 */ FLOAT BoundingRadius;
			/* 0x003C */ BYTE Unknown003C[36];
			/* 0x0060 */ struct Entity* Entity;
		};

		struct ActorInfo
		{
			/* 0x0000 */ ViewActor* ViewActor_;
			/* 0x0004 */ struct _EQLIGHTINFO* LightInfo; // PointLight
			/* 0x0008 */ char ActorDef[64]; // xxx_ACTORDEF string (HUM_ACTORDEF, ELM_ACTORDEF, etc)
			/* 0x0048 */ FLOAT Z;
			/* 0x004C */ FLOAT ZCeiling; // Z axis of the ceiling or first collision above player
			/* 0x0050 */ PVOID Unknown0050; // EqMobileEmitter*
			/* 0x0054 */ DWORD Unknown0054;
			/* 0x0058 */ DWORD UnknownTimer1;
			/* 0x005C */ DWORD UnknownTimer2;
			/* 0x0060 */ DWORD UnknownTimer3;
			/* 0x0064 */ DWORD UnknownTimer4;
			/* 0x0068 */ DWORD Unknown0068;
			/* 0x006C */ DWORD Unknown006C;
			/* 0x0070 */ DWORD Unknown0070;
			/* 0x0074 */ DWORD UnknownTimer5;
			/* 0x0078 */ DWORD UnknownTimer6;
			/* 0x007C */ DWORD UnknownTimer7;
			/* 0x0080 */ WORD LevitationMovementCounter; // loops from 0 to 512 while levitating, causes up/down movement, 0xFFFF = Not Levitating
			/* 0x0082 */ WORD DrunkMovementCounter; // loops from 0 to 512 while drunk, causes left/right movement, 0xFFFF = Not Drunk
			/* 0x0084 */ WORD Unknown0084;
			/* 0x0086 */ WORD Unknown0086;
			/* 0x0088 */ FLOAT DrunkMovementModifier; // how far left/right the player moves while drunk
			/* 0x008C */ FLOAT LevitationMovementModifier; // how far up/down the player moves while levitating
			/* 0x0090 */ BYTE IsAffectedByGravity; // gravity is enabled for the player (disabled while levitating)
			/* 0x0091 */ BYTE Unknown0091; // equals 0, 11 or 13
			/* 0x0092 */ BYTE Unknown0092;
			/* 0x0093 */ BYTE Unknown0093;
			/* 0x0094 */ PVOID Unknown0094; // pointer, static address 0x006EC6E8 has same value
			/* 0x0098 */ PVOID Unknown0098; // pointer, static address 0x006EC6E8 has same value
			/* 0x009C */ PVOID Unknown009C; // pointer, static address 0x006EC6E8 has same value
			/* 0x00A0 */ BYTE IsSwimmingUnderwater;
			/* 0x00A1 */ BYTE SwimmingWaterType; // 5,6,9,10 = Water, 7 = Lava, 8 = Freezing Water (7 and 8 cause damage!)
			/* 0x00A2 */ BYTE SwimmingFeetTouchingWater; // 0 = False, 5 = True
			/* 0x00A3 */ BYTE SwimmingUnknown1; // 0 = False, 5 = True
			/* 0x00A4 */ BYTE SwimmingUnknown2;
			/* 0x00A5 */ BYTE SwimmingUnknown3;
			/* 0x00A6 */ BYTE SwimmingUnknown4;
			/* 0x00A7 */ BYTE SwimmingUnknown5;
			/* 0x00A8 */ FLOAT MovementFriction1; // used for sliding on ice or slippery surfaces (Default = 0.625)
			/* 0x00AC */ FLOAT MovementFriction2; // used for sliding on ice or slippery surfaces (Default = 0.8000000119)
			/* 0x00B0 */ FLOAT JumpHeightModifier; // how high the player jumps (Default = 1.350000024)
			/* 0x00B4 */ FLOAT Unknown00B4;
			/* 0x00B8 */ FLOAT Unknown00B8;
			/* 0x00BC */ FLOAT MovementSpeedModifier; // how much slower/faster you move
			/* 0x00C0 */ BYTE Unknown00C0[196];
			/* 0x0184 */ DWORD Animation;
			/* 0x0188 */ BYTE Unknown0188[16];
			/* 0x0198 */ int Unsure_Strafe_Calc;
			/* 0x019C */ BYTE Unknown019c[24];
			/* 0x01B4 */ DWORD IsInvisible; // NPCs only? used by /hidecorpses command
			/* 0x01B8 */ BYTE Unknown01B8[168];
			/* 0x0260 */ DWORD IsHoldingBoth;
			/* 0x0264 */ DWORD IsHoldingSecondary;
			/* 0x0268 */ DWORD IsHoldingPrimary;
			/* 0x026C */ BYTE Unknown026C[4];
			/* 0x0270 */ BYTE Unknown0270[4];
			/* 0x0274 */ BYTE Unknown0274[4];
			/* 0x0278 */ BYTE Unknown0278[4];
			/* 0x027C */ WORD CastingSpellId;
			/* 0x027E */ BYTE CastingSpellGemNumber; // 255 = Bard Singing
			/* 0x027F */ BYTE Unknown027F;
			/* 0x0280 */ BYTE Unknown0280[4];
			/* 0x0284 */ struct _EQMODELINFO* ModelInfo;
			/* 0x0288 */ struct _EQDAGINFO* DagHeadPoint;
			/* 0x028C */ struct _EQDAGINFO* DagHead;
			/* 0x0290 */ struct _EQDAGINFO* DagUnknown;
			/* 0x0294 */ struct _EQDAGINFO* DagRightPoint;
			/* 0x0298 */ struct _EQDAGINFO* DagLeftPoint;
			/* 0x029C */ struct _EQDAGINFO* DagShieldPoint;
			/* 0x02A0 */ BYTE Unknown02A0[128];
			/* 0x0320 */ BYTE MovementType; // 0 = None, 4 = Walking, 6 = Running, 7 = Swimming
			/* 0x0321 */ BYTE Unknown0321[12];
			/* 0x032D */ BYTE IsMovingTimer; // 0 = Moving, 1-6 = Recently Stopped Moving, 200 = Not Moving
			/* 0x032E */ BYTE Unknown032E[266];
			/* 0x0438 */ DWORD IsLookingForGroup;
			/* 0x043C */ DWORD IsTrader;
			/* ...... */
		};
		typedef struct _EQINVENTORY
		{
			/* 00 */ struct _EQITEMINFO* EarLeft;
			/* 01 */ struct _EQITEMINFO* Head;
			/* 02 */ struct _EQITEMINFO* Face;
			/* 03 */ struct _EQITEMINFO* EarRight;
			/* 04 */ struct _EQITEMINFO* Neck;
			/* 05 */ struct _EQITEMINFO* Shoulders;
			/* 06 */ struct _EQITEMINFO* Arms;
			/* 07 */ struct _EQITEMINFO* Back;
			/* 08 */ struct _EQITEMINFO* WristLeft;
			/* 09 */ struct _EQITEMINFO* WristRight;
			/* 10 */ struct _EQITEMINFO* Ranged;
			/* 11 */ struct _EQITEMINFO* Hands;
			/* 12 */ struct _EQITEMINFO* Primary;
			/* 13 */ struct _EQITEMINFO* Secondary;
			/* 14 */ struct _EQITEMINFO* RingLeft;
			/* 15 */ struct _EQITEMINFO* RingRight;
			/* 16 */ struct _EQITEMINFO* Chest;
			/* 17 */ struct _EQITEMINFO* Legs;
			/* 18 */ struct _EQITEMINFO* Feet;
			/* 19 */ struct _EQITEMINFO* Waist;
			/* 20 */ struct _EQITEMINFO* Ammo;
		} EQINVENTORY, * PEQINVENTORY;
		struct _EQBUFFINFO
		{
			/* 0x0000 */ BYTE Unknown0000;
			/* 0x0001 */ BYTE CasterLevel; // level of player who casted the buff
			/* 0x0002 */ BYTE Modifier; // divide by 10 to get Bard song modifier
			/* 0x0003 */ BYTE Unknown0003;
			/* 0x0004 */ WORD SpellId;
			/* 0x0006 */ WORD Ticks; //  duration in ticks ; seconds = ticks * 6
			/* 0x0008 */ WORD Unknown0008;
			/* 0x000A */
		};
		struct EQCHARINFO
		{
			/* 0x0000 */ BYTE Unknown0000[2];
			/* 0x0002 */ CHAR Name[64]; // [0x40]
			/* 0x0042 */ CHAR LastName[70]; // [0x46] ; surname or title
			/* 0x0088 */ WORD Gender; // EQ_GENDER_x
			/* 0x008A */ WORD Race; // EQ_RACE_x
			/* 0x008C */ WORD Class; // EQ_CLASS_x
			/* 0x008E */ WORD Unknown008E;
			/* 0x0090 */ WORD Level;
			/* 0x0092 */ WORD Unknown0092;
			/* 0x0094 */ DWORD Experience; // EXP
			/* 0x0098 */ WORD PracticePoints; // Training window
			/* 0x009A */ WORD Mana;
			/* 0x009C */ WORD BaseHP;
			/* 0x009E */ WORD StunnedState; // EQ_STUNNED_STATE_x
			/* 0x00A0 */ WORD BaseSTR;
			/* 0x00A2 */ WORD BaseSTA;
			/* 0x00A4 */ WORD BaseCHA;
			/* 0x00A6 */ WORD BaseDEX;
			/* 0x00A8 */ WORD BaseINT;
			/* 0x00AA */ WORD BaseAGI;
			/* 0x00AC */ WORD BaseWIS;
			/* 0x00AE */ BYTE Unknown00AE[438];
			/* 0x0264 */ _EQBUFFINFO Buff[EQ_NUM_BUFFS];
			/* 0x02FA */ BYTE Unknown02FA[1080];
			/* 0x0732 */ WORD SpellBook[EQ_NUM_SPELL_BOOK_SPELLS];
			/* 0x0926 */ BYTE Unknown0926[524];
			/* 0x0B32 */ WORD MemorizedSpell[EQ_NUM_SPELL_GEMS]; // spell gem spell ids
			/* 0x0B42 */ BYTE Unknown0B42[14];
			/* 0x0B50 */ WORD Unknown0B50;
			/* 0x0B52 */ WORD Unknown0B52;
			/* 0x0B54 */ FLOAT ZoneEnterY;
			/* 0x0B58 */ FLOAT ZoneEnterX;
			/* 0x0B5C */ FLOAT ZoneEnterZ;
			/* 0x0B60 */ FLOAT Unknown0060;
			/* 0x0B64 */ BYTE StandingState; // EQ_STANDING_STATE_x
			/* 0x0B65 */ BYTE Unknown0B65[3];
			/* 0x0B68 */ DWORD Platinum;
			/* 0x0B6C */ DWORD Gold;
			/* 0x0B70 */ DWORD Silver;
			/* 0x0B74 */ DWORD Copper;
			/* 0x0B78 */ DWORD BankPlatinum;
			/* 0x0B7C */ DWORD BankGold;
			/* 0x0B80 */ DWORD BankSilver;
			/* 0x0B84 */ DWORD BankCopper;
			/* 0x0B88 */ DWORD CursorPlatinum; // currency held on the mouse cursor
			/* 0x0B8C */ DWORD CursorGold;
			/* 0x0B90 */ DWORD CursorSilver;
			/* 0x0B94 */ DWORD CursorCopper;
			/* 0x0B98 */ BYTE Unknown0B98[16];
			/* 0x0BA8 */ WORD Skill[EQ_NUM_SKILLS];
			/* 0x0C3C */ BYTE Unknown0C3C[64];
			/* 0x0C7C */ WORD Vision1;
			/* 0x0C7E */ BYTE Unknown0C7E[12];
			/* 0x0C8A */ WORD Vision2;
			/* 0x0C8C */ BYTE Unknown0C8C[120];
			/* 0x0D04 */ DWORD IsSwimmingUnderwater;
			/* 0x0D08 */ BYTE Unknown0D08[4];
			/* 0x0D0C */ BYTE Unknown0D0C[4];
			/* 0x0D10 */ BYTE IsAutoSplitEnabled;
			/* 0x0D11 */ BYTE Unknown0D11[43];
			/* 0x0D3C */ DWORD Unknown0D3C;
			/* 0x0D40 */ BYTE Unknown0D40[20];
			/* 0x0D54 */ DWORD Hunger;
			/* 0x0D58 */ DWORD Thirst;
			/* 0x0D5C */ BYTE Unknown0D5C[20];
			/* 0x0D70 */ DWORD ZoneId;
			/* 0x0D74 */ struct _EQSPAWNINFO* SpawnInfo;
			/* 0x0D78 */ struct _EQITEMINFO* CursorItem;
			union
			{
				/* 0x0D7C */ struct _EQINVENTORY Inventory;
				/* 0x0D7C */ struct _EQITEMINFO* InventoryItem[EQ_NUM_INVENTORY_SLOTS];
			};
			/* 0x0DD0 */ struct _EQITEMINFO* InventoryPackItem[EQ_NUM_INVENTORY_PACK_SLOTS];
			/* 0x0DF0 */ BYTE Unknown0DF0[116];
			/* 0x0E64 */ DWORD Unknown0E64;
			/* 0x0E68 */ BYTE Unknown0E68[32];
			/* 0x0E88 */ DWORD Unknown0E88;
			/* 0x0E8C */ BYTE Unknown0E8C[56];
			/* 0x0EC4 */ DWORD ZoneBoundId;
			/* 0x0EC8 */ DWORD Unknown0EC8;
			/* 0x0ECC */ DWORD Unknown0ECC;
			/* 0x0ED0 */ DWORD Unknown0ED0;
			/* 0x0ED4 */ DWORD ZoneBirthId;
			/* 0x0ED8 */ FLOAT ZoneBoundY;
			/* 0x0EDC */ DWORD Unknown0EDC;
			/* 0x0EE0 */ DWORD Unknown0EE0;
			/* 0x0EE4 */ DWORD Unknown0EE4;
			/* 0x0EE8 */ FLOAT ZoneBirthY;
			/* 0x0EEC */ FLOAT ZoneBoundX;
			/* 0x0EF0 */ DWORD Unknown0EF0;
			/* 0x0EF4 */ DWORD Unknown0EF4;
			/* 0x0EF8 */ DWORD Unknown0EF8;
			/* 0x0EFC */ FLOAT ZoneBirthX;
			/* 0x0F00 */ FLOAT ZoneBoundZ;
			/* 0x0F04 */ DWORD Unknown0F04;
			/* 0x0F08 */ DWORD Unknown0F08;
			/* 0x0F0C */ DWORD Unknown0F0C;
			/* 0x0F10 */ FLOAT ZoneBirthZ;
			/* 0x0F14 */ BYTE Unknown0F14[1080];
			/* 0x134C */ WORD Deity;
			/* 0x134E */ WORD GuildId;
			/* 0x1350 */ BYTE Unknown1350[8];
			/* 0x1358 */ BYTE Unknown1358;
			/* 0x1359 */ BYTE Unknown1359;
			/* 0x135A */ BYTE Unknown135A;
			/* 0x135B */ BYTE Unknown135B;
			/* 0x135C */ BYTE Unknown135C;
			/* 0x135D */ BYTE Unknown135D;
			/* 0x135E */ BYTE Stamina; // yellow endurance bar ; 100 = Empty, 0 = Full
			/* 0x135F */ BYTE Unknown135F;
			/* 0x1360 */ BYTE Unknown1360;
			/* 0x1361 */ BYTE AnonymousState;
			/* 0x1362 */ BYTE Unknown1362;
			/* 0x1363 */ BYTE GuildStatus; // guild rank
			/* 0x1364 */ BYTE Drunkness; // 0 = Not Drunk, counts down over time
			/* 0x1365 */ BYTE Unknown1365[451];
			/* 0x1528 */ DWORD AlternateAdvancementExperience;
			/* 0x152C */ BYTE Unknown152C[476];
			/* 0x1708 */ BYTE AirSupply; // air remaining while swimming underwater
			/* 0x1709 */ BYTE Unknown1709[2475];
			/* 0x20B4 */ struct _EQITEMINFO* InventoryBankItem[EQ_NUM_INVENTORY_BANK_SLOTS];
			/* ...... */
		};

		struct Entity
		{
			/* 0x0000 */ BYTE Unknown0000; // always equals 0x03
			/* 0x0001 */ CHAR Name[30]; // [0x1E]
			/* 0x001F */ BYTE Unknown001F[37];
			/* 0x0044 */ DWORD ZoneId; // EQ_ZONE_ID_x
			Vec3 Position;
			///* 0x0048 */ FLOAT Y;
			///* 0x004C */ FLOAT X;
			///* 0x0050 */ FLOAT Z;
			/* 0x0054 */ FLOAT Heading; // camera view left/right, yaw
			/* 0x0058 */ FLOAT Unk;
			/* 0x005C */ FLOAT MovementSpeed;
			/* 0x0060 */ FLOAT MovementSpeedY;
			/* 0x0064 */ FLOAT MovementSpeedX;
			/* 0x0068 */ FLOAT MovementSpeedZ;
			/* 0x006C */ FLOAT MovementSpeedHeading;
			/* 0x0070 */ FLOAT Unknown0070;
			/* 0x0074 */ FLOAT Pitch; // camera view up/down
			/* 0x0078 */ Entity* Prev;
			/* 0x007C */ Entity* Next;
			/* 0x0080 */ PVOID Unknown0080;
			/* 0x0084 */ ActorInfo* ActorInfo;
			/* 0x0088 */ EQCHARINFO* CharInfo;
			/* 0x008C */ FLOAT CameraHeightOffset;
			/* 0x0090 */ FLOAT ModelHeightOffset;
			/* 0x0094 */ WORD SpawnId;
			/* 0x0096 */ WORD PetOwnerSpawnId; // spawn id of the owner of this pet spawn
			/* 0x0098 */ DWORD HpMax;
			/* 0x009C */ DWORD HpCurrent;
			/* 0x00A0 */ WORD GuildId;
			/* 0x00A2 */ BYTE Unknown00A2[6];
			/* 0x00A8 */ BYTE Type; // EQ_SPAWN_TYPE_x
			/* 0x00A9 */ BYTE Class; // EQ_CLASS_x
			/* 0x00AA */ WORD Race;  // EQ_RACE_x
			/* 0x00AC */ BYTE Gender; // EQ_GENDER_x
			/* 0x00AD */ BYTE Level;
			/* 0x00AE */ BYTE IsHidden; // 0 = Visible, 1 = Invisible
			/* 0x00AF */ BYTE IsSneaking; // sneaking or snared ; 0 = Normal Movement Speed, 1 = Slow Movement Speed
			/* 0x00B0 */ BYTE IsPlayerKill; // PVP flagged with red name by Priest of Discord
			/* 0x00B1 */ BYTE StandingState; // EQ_STANDING_STATE_x
			/* 0x00B2 */ BYTE LightType; // EQ_LIGHT_TYPE_x
			/* 0x00B3 */ BYTE Unknown00B3;
			/* 0x00B4 */ WORD EquipmentMaterialType[7]; // EQ_EQUIPMENT_MATERIAL_TYPE_x ; Head,Chest,Arms,Wrist,Hands,Legs,Feet
			/* 0x00C2 */ WORD EquipmentPrimaryItemType; // EQ_EQUIPMENT_ITEM_TYPE_x ; Primary
			/* 0x00C4 */ WORD EquipmentSecondaryItemType; // EQ_EQUIPMENT_ITEM_TYPE_x ; Secondary
			/* 0x00C6 */ WORD Unknown00C6;
			/* 0x00C8 */ BYTE Unknown00C8[36];
			/* 0x00EC */ BYTE Unknown00EC;
			/* 0x00F0 */ FLOAT Height; // model height or size/scale (shrink, grow, etc)
			/* 0x00F4 */ FLOAT Unknown00F4;
			/* 0x00F8 */ FLOAT Unknown00F8;
			/* 0x00FC */ FLOAT Unknown00FC;
			/* 0x0100 */ FLOAT MovementBackwardSpeedMultiplier; // modifies how fast you move backwards (Default = 0.4600000083)
			/* 0x0104 */ FLOAT MovementForwardSpeedMultiplier; // modifies how fast you move forwards (Default = 0.6999999881)
			/* 0x0108 */ BYTE IsLinkDead; // LD
			/* 0x0109 */ BYTE IsGameMaster; // GM
			/* 0x010A */ WORD LevitationState; // EQ_LEVITATION_STATE_x
			/* 0x010C */ DWORD TargetType; // EQ_SPAWN_TARGET_TYPE_x
			/* 0x0110 */ DWORD Unknown0110;
			/* 0x0114 */ DWORD AnonymousState; // EQ_ANONYMOUS_STATE_x, /anonymous and /roleplay
			/* 0x0118 */ DWORD Unknown0118;
			/* 0x011C */ DWORD IsAwayFromKeyboard; // AFK
			/* 0x0120 */ BYTE Unknown0120[4];
			/* 0x0124 */ DWORD AlternateAdvancementRank; // AA points title value (0-3) (Venerable, Baroness, etc)
			/* 0x0128 */ BYTE Unknown0128[4];
			/* 0x012C */ CHAR LastName[22]; // surname or title
			/* 0x0142 */ BYTE Unknown0142[10];
			/* 0x014C */ WORD GuildStatus; // guild rank
			/* 0x014E */ WORD Deity; // EQ_DEITY_x
			/* 0x0150 */ BYTE Unknown0150;
			/* 0x0151 */ BYTE Unknown0151[6];
			/* 0x0157 */ BYTE Unknown0157[5];
			/* 0x015C */ DWORD Unknown015C;
			/* 0x0160 */ DWORD Unknown0160;
			/* 0x0164 */ DWORD Unknown0164;
			/* 0x0168 */
		};
		struct GuildName
		{
			char name[512][0x60];
		};

		struct MouseDelta
		{
			INT16 x;
			INT16 y;
		};
		struct CameraSetting
		{
			/* 0x0000 */ Vec3 Position;
			/* 0x00C */ FLOAT Heading; // Yaw
			/* 0x010 */ FLOAT Pitch;
			/* 0x01C */ FLOAT WhoKnows;
		};
		struct CameraInfo
		{
			/* 0x0000 */ DWORD Unknown0000;
			/* 0x0004 */ DWORD RegionNumber;
			/* 0x0008 */ Vec3 Position;
			/* 0x0014 */ FLOAT Heading; // Yaw
			/* 0x0018 */ FLOAT Pitch;
			/* 0x001C */ FLOAT Roll;
			/* 0x0020 */ FLOAT FieldOfView;
			/* 0x0024 */ FLOAT AspectRatio;
			/* 0x0028 */ FLOAT Unknown0028;
			/* 0x002C */ FLOAT Unknown002C;
			/* 0x0030 */ FLOAT DrawDistance;
			/* 0x0034 */ BYTE Unknown0034[20];
			/* 0x0048 */ DWORD ResolutionWidth;
			/* 0x004C */ DWORD ResolutionHeight;
			/* 0x0050 */ BYTE Unknown0050[12];
			/* 0x005C */ FLOAT Unknown005C;
			/* 0x0060 */ FLOAT Unknown0060;
			/* 0x0064 */ FLOAT ResolutionWidthHalf;
			/* 0x0068 */ FLOAT ResolutionHeightHalf;
			/* 0x006C */ FLOAT Yaw;
			/* 0x0070 */ FLOAT Unk;
			/* 0x0074 */ FLOAT sPitch;
			/* ...... */
		};

		struct Cam
		{
			/* 0x0000 */float zoom;
			/* 0x0004 */float heading;
			/* 0x0008 */float height;
			/* 0x000c */float unk3;
			/* 0x0010 */float pitch;
			/* 0x0014 */float unk5;
			/* 0x0018 */float unk6;
		};
		struct ActorLocation
		{
			Vec3 Position;
			float heading;
			float pitch;
			float unk3;
			float unk4;
			float unk5;
			float unk6;
			float unk7;
		};

		struct pInstWindows
		{
			void* CContextMenuManager;  // 0x63D5CC
			EQWND* CChatManager;  // 0x63D5D0
			EQWND* uknownWnd1;  // 0x63D5D4
			EQWND* CharacterSelect;  // 0x63D5D8
			EQWND* CFacePick;  // 0x63D5DC
			EQWND* CItemDisplayManager;  // 0x63D5E0
			EQWND* CNote;  // 0x63D5E4
			EQWND* CHelp;  // 0x63D5E8
			EQWND* CBook;  // 0x63D5EC
			EQWND* CPetInfo;  // 0x63D5F0
			EQWND* CTrain;  // 0x63D5F4
			EQWND* CSkills;  // 0x63D5F8
			EQWND* CSkillsSelect;  // 0x63D5FC
			EQWND* CFriends;  // 0x63D600
			EQWND* CAA;  // 0x63D604
			EQWND* CGroup;  // 0x63D608
			EQWND* CLoadskin;  // 0x63D60C
			EQWND* CAlarm;  // 0x63D610
			EQWND* CMusicPlayer;  // 0x63D614
			EQWND* CRaid;  // 0x63D618
			EQWND* CRaidOptions;  // 0x63D61C
			EQWND* CBreath;  // 0x63D620
			EQWND* CTarget;  // 0x63D624
			EQWND* CHotButton;  // 0x63D628
			EQWND* CColorPicker;  // 0x63D62C
			EQWND* CPlayer;  // 0x63D630
			EQWND* COptions;  // 0x63D634
			EQWND* CBuffWindowNORMAL;  // 0x63D638
			EQWND* CharacterCreation;  // 0x63D63C
			EQWND* CCursorAttachment;  // 0x63D640
			EQWND* CCasting;  // 0x63D644
			EQWND* CCastSpell;  // 0x63D648
			EQWND* CSpellBook;  // 0x63D64C
			EQWND* CInventory;  // 0x63D650
			EQWND* CBank;  // 0x63D654
			EQWND* CQuantity;  // 0x63D658
			EQWND* CLoot;  // 0x63D65C
			EQWND* CActions;  // 0x63D660
			EQWND* CMerchant;  // 0x63D664
			EQWND* CTrade;  // 0x63D668
			EQWND* CSelector;  // 0x63D66C
			EQWND* CBazaar;  // 0x63D670
			EQWND* CBazaarSearch;  // 0x63D674
			EQWND* CGive;  // 0x63D678
			EQWND* CTracking;  // 0x63D67C
			EQWND* CInspect;  // 0x63D680
			EQWND* CSocialEdit;  // 0x63D684
			EQWND* CFeedback;  // 0x63D688
			EQWND* CBugReport;  // 0x63D68C
			EQWND* CVideoModes;  // 0x63D690
			EQWND* CTextEntry;  // 0x63D694
			EQWND* CFileSelection;  // 0x63D698
			EQWND* CCompass;  // 0x63D69C
			EQWND* CPlayerNotes;  // 0x63D6A0
			EQWND* CGemsGame;  // 0x63D6A4
			EQWND* CTimeLeft;  // 0x63D6A8
			EQWND* CPetitionQ;  // 0x63D6AC
			EQWND* CSoulmark;  // 0x63D6B0
			void* CInvSlotMgr;  // 0x63D6B4
			void* CContainerMgr;  // 0x63D6B8
		};

		struct EQCommand
		{
			int string_id;
			const char* name;
			const char* localized_name;
			int fn;
		};
	}
}
