#if defined _ln_included
	#endinput
#endif
#define _ln_included


#include <amxmodx>
#include <fun>
#include <cstrike>

#define cm(%1)	( charsmax(%1) - 1 )


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
	i_deagle,
	i_usp,
	i_awp
}


enum Color
{
	NORMAL = 1, 
	YELLOW = 1, 
	GREEN, 
	TEAM_COLOR, 
	GREY, 
	RED, 
	BLUE, 
}
 
new TeamName[][] =
{
	"",
	"TERRORIST",
	"CT",	
	"SPECTATOR"
}

stock give_user_bonus(index, skill_type, count)
{
	switch( skill_type )
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
			give_item(index, "weapon_flashbang")
			cs_set_user_bpammo(index, CSW_FLASHBANG, count)
		}

		case SG:
		{
			give_item(index, "weapon_smokegrenade")
			cs_set_user_bpammo(index, CSW_SMOKEGRENADE, count)			
		}

		case HE:
		{
			give_item(index, "weapon_hegrenade")
			cs_set_user_bpammo(index, CSW_HEGRENADE, count)				
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
		case i_deagle:
		{
			new iwpn = give_item(index, "weapon_deagle")
			cs_set_weapon_ammo(iwpn, count)
			cs_set_user_bpammo(index, CSW_DEAGLE, count2)
			return 0
		}

		case i_awp:
		{
			new iwpn = give_item(index, "weapon_awp")
			cs_set_weapon_ammo(iwpn, count)
			cs_set_user_bpammo(index, CSW_AWP, count2)
			return 0
		}

		case i_usp:
		{
			new iwpn = give_item(index, "weapon_usp")
			cs_set_weapon_ammo(iwpn, count)
			cs_set_user_bpammo(index, CSW_USP, count2)
			return 0
		}
	}	
	return 0
}

stock player_name(index)
{
	new szName[33]
	
	get_user_name(index, szName, charsmax(szName) - 1)

	return szName;
	
}

ln_color(id, Color:type, const msg[], {Float,Sql,Result,_}:...)
{
	new message[256];
 
	switch(type)
	{
		case NORMAL: // clients scr_concolor cvar color
		{
			message[0] = 0x01;
		}
		case GREEN: // Green
		{
			message[0] = 0x04;
		}
		default: // White, Red, Blue
		{
			message[0] = 0x03;
		}
	}
	 
	vformat(message[1], 251, msg, 4);
 
	// Make sure message is not longer than 192 character. Will crash the server.
	message[191] = '^0';
 
	new team, ColorChange, index, MSG_Type;
	if(id)
	{
		MSG_Type = MSG_ONE;
		index = id;
	} else {
		index = FindPlayer();
		MSG_Type = MSG_ALL;
	}

	team = get_user_team(index);
	ColorChange = ColorSelection(index, MSG_Type, type);
 

	ShowColorMessage(index, MSG_Type, message);
	if(ColorChange)
	{
		Team_Info(index, MSG_Type, TeamName[team]);
	}
}
 
ShowColorMessage(id, type, message[])
{
	static get_user_msgid_saytext;
	if(!get_user_msgid_saytext)
	{
		get_user_msgid_saytext = get_user_msgid("SayText");
	}
	message_begin(type, get_user_msgid_saytext, _, id);
	write_byte(id)	
	write_string(message);
	message_end();	
}
 
Team_Info(id, type, team[])
{
	static bool:teaminfo_used;
	static get_user_msgid_teaminfo;
	if(!teaminfo_used)
	{
		get_user_msgid_teaminfo = get_user_msgid("TeamInfo");
		teaminfo_used = true;
	}
	message_begin(type, get_user_msgid_teaminfo, _, id);
	write_byte(id);
	write_string(team);
	message_end();
 
	return 1;
}
 
ColorSelection(index, type, Color:Type)
{
	switch(Type)
	{
		case RED:
		{
			return Team_Info(index, type, TeamName[1]);
		}
		case BLUE:
		{
			return Team_Info(index, type, TeamName[2]);
		}
		case GREY:
		{
			return Team_Info(index, type, TeamName[0]);
		}
	}
 
	return 0;
}
 
FindPlayer()
{
	new i = -1;
	static iMaxPlayers;
	if( !iMaxPlayers )
	{
		iMaxPlayers = get_maxplayers( );
	}
	while(i <= iMaxPlayers)
	{
		if(is_user_connected(++i))
			return i;
	}
 
	return -1;
}
