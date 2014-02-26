#include <amxmodx>
#include <fun>
#include <cstrike>

enum 
{
	ITEM_HP,
	ITEM_ARMOR,
	ITEM_SPEED,
	ITEM_GRAVITY
}

enum
{
	FL,
	HE,
	SG
}

enum
{
	ideagle,
	iusp,
	iawp
}

stock give_user_bonus(index, skill_type, count)
{
	siwtch( skill_type )
	{
	
		case ITEM_HP:
		{
			set_user_health( index, get_user_health( index ) + count )
		}

		case ITEM_ARMOR:
		{
			set_user_armor( index, get_user_armor( index ) + count )
		}		

		case ITEM_GRAVITY:
		{
			set_user_gravity( index, float(count) / 800.0 )
		}

		case ITEM_SPEED:
		{
			set_user_maxspeed( index, get_user_maxspeed( index ) + float(count) )
		}
	}

}

stock give_nade(index, nade_type, count)
{
	switch( nade_type )
	{
		case FL:
		{
			give_item(id, "weapon_flashbang")
			cs_set_user_bpammo(id, CSW_FLASHBANG, count)
		}

		case SG:
		{
			give_item(id, "weapon_smokegrenade")
			cs_set_user_bpammo(id, CSW_SMOKEGRENADE, count)			
		}

		case HE:
		{
			give_item(id, "weapon_hegrenade")
			cs_set_user_bpammo(id, CSW_HEGRENADE, count)				
		}
	}
}

stock give_weapons(index, weapon_type, count, count2)
{
	if(!is_user_alive( index ))
	{
		return 1
	}

	switch( weapon_type )
	{
		case ideagle:
		{
			new iwpn = give_item(id, "weapon_deagle")
			cs_set_weapon_ammo(iwpn, count)
			cs_set_user_bpammo(id, CSW_DEAGLE, count2)
			return 0
		}

		case iawp:
		{
			new iwpn = give_item(id, "weapon_awp")
			cs_set_weapon_ammo(iwpn, count)
			cs_set_user_bpammo(id, CSW_AWP, count2)
			return 0
		}

		case iusp:
		{
			new iwpn = give_item(id, "weapon_usp")
			cs_set_weapon_ammo(iwpn, count)
			cs_set_user_bpammo(id, CSW_USP, count2)
			return 0
		}
	}	
	return 0
}
