#include "g_local.h"
//#include "g_target.c"//problems occur when included
//#include "g_spawn.c"

cvar_t *hvh;



static int wave = 0;

static char *spawnerNames[] = {
	"leftsideBottomLeftSpawner", "leftsideBottomRightSpawner",  "leftsideTopRightSpawner","leftsideTopLeftSpawner",
	"rightsideBottomLeftSpawner", "rightsideBottomRightSpawner",  "rightsideTopRightSpawner","rightsideTopLeftSpawner",
	NULL
};
static char *pathnames[] = {
	"LeftTeamPath1Point1", "LeftTeamPath2Point1", "LeftTeamPath3Point1", "LeftTeamPath4Point1",
	"RightTeamPath1Point1", "RightTeamPath2Point1", "RightTeamPath3Point1", "RightTeamPath4Point1",
	NULL
};

void ED_CallSpawn (edict_t *ent);
void use_target_spawner (edict_t *self, edict_t *other, edict_t *activator);

/**/
void WeaponSelected(edict_t *ent, char *desired_weapon)//Hastings-defin
{
	//char *s;
	//ent->item

	

	PMenu_Close(ent);
	/*
	ent->svflags &= ~SVF_NOCLIENT;
	ent->client->resp.ctf_team = desired_team;
	ent->client->resp.ctf_state = CTF_STATE_START;
	s = Info_ValueForKey (ent->client->pers.userinfo, "skin");
	CTFAssignSkin(ent, s);

	PutClientInServer (ent);
	// add a teleportation effect
	ent->s.event = EV_PLAYER_TELEPORT;
	// hold in place briefly
	ent->client->ps.pmove.pm_flags = PMF_TIME_TELEPORT;
	ent->client->ps.pmove.pm_time = 14;
	gi.bprintf(PRINT_HIGH, "%s joined the %s team.\n",
		ent->client->pers.netname, CTFTeamName(desired_team));
		*/

}

void WeaponSelectRifle(edict_t *ent, pmenu_t *p)//Hastings-join entity team
{
	WeaponSelected(ent, "weapon_machinegun");
	ent->client->pers.inventory[ITEM_INDEX(FindItem("Bullets"))] = 200;
}

void WeaponSelectShotgun(edict_t *ent, pmenu_t *p)
{
	WeaponSelected(ent, "weapon_shotgun");
	ent->client->pers.inventory[ITEM_INDEX(FindItem("Shells"))] = 24;
	
}

void WeaponSelectRailgun(edict_t *ent, pmenu_t *p)
{
	WeaponSelected(ent, "weapon_railgun");
	ent->client->pers.inventory[ITEM_INDEX(FindItem("Bullets"))] = 20;
}

void WeaponSelectRocketlauncher(edict_t *ent, pmenu_t *p)
{
	WeaponSelected(ent, "weapon_rocketlauncher");
		ent->client->pers.inventory[ITEM_INDEX(FindItem("Rockets"))] = 7;
	
}

pmenu_t weaponmenu[] = {
	{ "*Quake II",			PMENU_ALIGN_CENTER, NULL, NULL },
	{ "*Select your weapon",	PMENU_ALIGN_CENTER, NULL, NULL },
	{ NULL,					PMENU_ALIGN_CENTER, NULL, NULL },
	{ NULL,					PMENU_ALIGN_CENTER, NULL, NULL },
	{ "Rifleman(weapon_machinegun)",		PMENU_ALIGN_LEFT, NULL, WeaponSelectRifle },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, NULL },
	{ "Shotgunner(weapon_shotgun)",		PMENU_ALIGN_LEFT, NULL, WeaponSelectShotgun },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, NULL },
	{ "Railgunner(weapon_railgun)",		PMENU_ALIGN_LEFT, NULL, WeaponSelectRailgun },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, NULL },
	{ "Demolitionist(weapon_rocketlauncher)",		PMENU_ALIGN_LEFT, NULL, WeaponSelectRocketlauncher },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, NULL },
	{ "Use [ and ] to move cursor",	PMENU_ALIGN_LEFT, NULL, NULL },
	{ "ENTER to select",	PMENU_ALIGN_LEFT, NULL, NULL },
	{ "ESC to Exit Menu",	PMENU_ALIGN_LEFT, NULL, NULL },
	{ "(TAB to Return)",	PMENU_ALIGN_LEFT, NULL, NULL },
	//{ "v" CTF_STRING_VERSION,	PMENU_ALIGN_RIGHT, NULL, NULL },
};

void CTFUpdateWeaponMenu(edict_t *ent)
{
	static char levelname[32];
	//static char team1players[32];
	//static char team2players[32];
	//int playersTeam1, playersTeam2, i;
	//int rifle, shotgun, railgun, rocketlauncher;

	weaponmenu[4].text = "Rifleman(machinegun)";
	weaponmenu[4].SelectFunc = WeaponSelectRifle;
	weaponmenu[6].text = "Shotgun(shotgun)";
	weaponmenu[6].SelectFunc = WeaponSelectShotgun;
	weaponmenu[8].text = "Railgunner(railgun)";
	weaponmenu[8].SelectFunc = WeaponSelectRailgun;
	weaponmenu[10].text = "Demolitionist(rocketlauncher)";
	weaponmenu[10].SelectFunc = WeaponSelectRocketlauncher;

	

	/*if (ctf_forcejoin->string && *ctf_forcejoin->string) 
	{
		if (stricmp(ctf_forcejoin->string, "red") == 0) 
		{
			weaponmenu[6].text = NULL;
			weaponmenu[6].SelectFunc = NULL;
		} 
		else if (stricmp(ctf_forcejoin->string, "blue") == 0) 
		{
			weaponmenu[4].text = NULL;
			weaponmenu[4].SelectFunc = NULL;
		}
	}

	if (ent->client->chase_target)
		weaponmenu[8].text = "Leave Chase Camera";
	else
		weaponmenu[8].text = "Chase Camera";
	*/
	levelname[0] = '*';
	if (g_edicts[0].message)
		strncpy(levelname+1, g_edicts[0].message, sizeof(levelname) - 2);
	else
		strncpy(levelname+1, level.mapname, sizeof(levelname) - 2);
	levelname[sizeof(levelname) - 1] = 0;

	/*playersTeam1 = playersTeam2 = 0;
	for (i = 0; i < maxclients->value; i++) 
	{
		if (!g_edicts[i+1].inuse)
			continue;
		if (game.clients[i].resp.ctf_team == CTF_TEAM1)
			playersTeam1++;
		else if (game.clients[i].resp.ctf_team == CTF_TEAM2)
			playersTeam2++;
	}

	sprintf(team1players, "  (%d players)", playersTeam1);
	sprintf(team2players, "  (%d players)", playersTeam2);*/

	weaponmenu[2].text = levelname;
	/*if (weaponmenu[4].text)
		weaponmenu[5].text = team1players;
	else
		weaponmenu[5].text = NULL;
	if (weaponmenu[6].text)
		weaponmenu[7].text = team2players;
	else
		weaponmenu[7].text = NULL;
	
	if (playersTeam1 > playersTeam2)
		return CTF_TEAM1;
	else if (playersTeam2 > playersTeam1)
		return CTF_TEAM1;
	return (rand() & 1) ? CTF_TEAM1 : CTF_TEAM2;*/
}

void CTFOpenWeaponMenu(edict_t *ent)
{
	//int weapon;
	ent->showweaponselect = true;
	CTFUpdateWeaponMenu(ent);

	/*switch(weapon)
	{
	case 1:
		weapon = 4;
		break;
	case 2:
		weapon = 6;
		break;
	case 3:
		weapon = 8;
		break;
	default:
		weapon = 10;
		break;
	}*/
	PMenu_Open(ent, weaponmenu, 4, sizeof(weaponmenu) / sizeof(pmenu_t));
	
	ent->showweaponselect = false;//Hastings-findmeplease
}

void setupHordeVsHordeSpawn(void)
{
	//edict_t *ent;
	cvar_t *hvh = gi.cvar("hvh", "1", CVAR_SERVERINFO);
	//ent = G_Spawn();
	//ent->nextthink = level.time + 20;
	//ent->think = 
	findAndTriggerSpawners();
	
}

static void findAndTriggerSpawners()//edict_t *ent)
{
	
	//gitem_t *spawner;
	edict_t	*e;
	edict_t	*f;
	//edict_t *spot;
	int i;
	i = 0;
	while (spawnerNames[i]&&pathnames[i]) 
	{
		//gi.dprintf ("%s was triggered for the first time\n", spawnerNames[i]);

		//stricmp(ent->classname, "trigger_once")

		if ((e = G_Find (NULL, FOFS(targetname), spawnerNames[i])) != NULL)//find(e, classname, "inv_spawn")
		{
			gi.dprintf ("%s was triggered for the first time\n", spawnerNames[i]);//SpawnTech(spawners, spot);*/
			e->nextthink=level.time + 30;
			e->think = G_SpawnerThink;

			if ((f = G_Find (NULL, FOFS(targetname), pathnames[i])) != NULL)//find(e, classname, "inv_spawn")
			{
				e->movetarget = f;
			}
			//G_SpawnerThink (e);
		}
		i++;
	}
}

//Hastings
void G_SpawnerThink (edict_t *self)
{
	int enemiesPerWave = 3;
	//int wave;
	//edict_t *ent;//monster ent to be used later
	
	if(wave==0)
		wave = 1;
	else if(wave<5)
		wave++;
	
	//spawns a wave of monsters
	//monster_soldier_light
//	ent->target= SP_monster_infantry;
	switch (wave) 
	{
	case 1:
		self->target= "monster_soldier_light";
		break;
	case 2:
		self->target= "monster_soldier_light";//Change these to spawn other monsters, add more cases to spawn additional monster wave types
		break;
	default:
		self->target= "monster_soldier_light";
		wave=1;
	}
	//self->target= "monster_soldier_light";
	self->nextthink = level.time + 30;
	gi.dprintf("Spawner Thinking(%s)\n",self->targetname);
	gi.dprintf("Spawner Thinking(%s)\n",self->target);

	//ent = G_Spawn ();
	//ent->targetname
	//ED_CallSpawn (ent);
	//SP_monster_soldier_light (edict_t *self)
	//while(enemiesPerWave>0)
	//{
		use_target_spawner (self, NULL, NULL);//Hastings
	//	enemiesPerWave--;
	//}
	//self->classname
}
/*
//------------------------- EXAMPLE/UNUSED CODE BEYOND THIS POINT------------------------------------------------

int CTFUpdateJoinMenu(edict_t *ent)
{
	static char levelname[32];
	static char team1players[32];
	static char team2players[32];
	int playersTeam1, playersTeam2, i;

	joinmenu[4].text = "Join Red Team";
	joinmenu[4].SelectFunc = WeaponSelectRifle;
	joinmenu[6].text = "Join Blue Team";
	joinmenu[6].SelectFunc = WeaponSelectRifle;

	if (ctf_forcejoin->string && *ctf_forcejoin->string) {
		if (stricmp(ctf_forcejoin->string, "red") == 0) {
			joinmenu[6].text = NULL;
			joinmenu[6].SelectFunc = NULL;
		} else if (stricmp(ctf_forcejoin->string, "blue") == 0) {
			joinmenu[4].text = NULL;
			joinmenu[4].SelectFunc = NULL;
		}
	}

	if (ent->client->chase_target)
		joinmenu[8].text = "Leave Chase Camera";
	else
		joinmenu[8].text = "Chase Camera";

	levelname[0] = '*';
	if (g_edicts[0].message)
		strncpy(levelname+1, g_edicts[0].message, sizeof(levelname) - 2);
	else
		strncpy(levelname+1, level.mapname, sizeof(levelname) - 2);
	levelname[sizeof(levelname) - 1] = 0;

	playersTeam1 = playersTeam2 = 0;
	for (i = 0; i < maxclients->value; i++) {
		if (!g_edicts[i+1].inuse)
			continue;
		if (game.clients[i].resp.ctf_team == CTF_TEAM1)
			playersTeam1++;
		else if (game.clients[i].resp.ctf_team == CTF_TEAM2)
			playersTeam2++;
	}

	sprintf(team1players, "  (%d players)", playersTeam1);
	sprintf(team2players, "  (%d players)", playersTeam2);

	joinmenu[2].text = levelname;
	if (joinmenu[4].text)
		joinmenu[5].text = team1players;
	else
		joinmenu[5].text = NULL;
	if (joinmenu[6].text)
		joinmenu[7].text = team2players;
	else
		joinmenu[7].text = NULL;
	
	if (playersTeam1 > playersTeam2)
		return CTF_TEAM1;
	else if (playersTeam2 > playersTeam1)
		return CTF_TEAM1;
	return (rand() & 1) ? CTF_TEAM1 : CTF_TEAM2;
}
*/
/*void SetLightStyles (void)
{
	int		stylenum;
	char	*t;
	entity_t	*e;
	int		i, j;
	char	value[10];
	char	lighttargets[MAX_SWITCHED_LIGHTS][64];


	// any light that is controlled (has a targetname)
	// must have a unique style number generated for it

	stylenum = 0;
	for (i=1 ; i<num_entities ; i++)
	{
		e = &entities[i];

		t = ValueForKey (e, "classname");
		if (Q_strncasecmp (t, "light", 5))
			continue;
		t = ValueForKey (e, "targetname");
		if (!t[0])
			continue;
		
		// find this targetname
		for (j=0 ; j<stylenum ; j++)
			if (!strcmp (lighttargets[j], t))
				break;
		if (j == stylenum)
		{
			if (stylenum == MAX_SWITCHED_LIGHTS)
				Error ("stylenum == MAX_SWITCHED_LIGHTS");
			strcpy (lighttargets[j], t);
			stylenum++;
		}
		sprintf (value, "%i", 32 + j);
		SetKeyValue (e, "style", value);
	}

}*/
//----------------

//----------------
/*
static edict_t *FindSpawnerLocation(void)
{
	edict_t *spot = NULL;
	int i = 0;

	while (spawnerNames[i]) 
	{
		G_Find (spot, FOFS(classname), spawnerNames[i]);
		i++;
	}
	if (!spot)
		spot = G_Find (spot, FOFS(classname), "info_player_deathmatch");
	return spot;
}

static void SpawnTech(gitem_t *item, edict_t *spot)
{
	edict_t	*ent;
	vec3_t	forward, right;
	vec3_t  angles;

	ent = G_Spawn();

	ent->classname = item->classname;
	ent->item = item;
	ent->spawnflags = DROPPED_ITEM;
	ent->s.effects = item->world_model_flags;
	ent->s.renderfx = RF_GLOW;
	VectorSet (ent->mins, -15, -15, -15);
	VectorSet (ent->maxs, 15, 15, 15);
	gi.setmodel (ent, ent->item->world_model);
	ent->solid = SOLID_TRIGGER;
	ent->movetype = MOVETYPE_TOSS;  
	ent->touch = Touch_Item;
	ent->owner = ent;

	angles[0] = 0;
	angles[1] = rand() % 360;
	angles[2] = 0;

	AngleVectors (angles, forward, right, NULL);
	VectorCopy (spot->s.origin, ent->s.origin);
	ent->s.origin[2] += 16;
	VectorScale (forward, 100, ent->velocity);
	ent->velocity[2] = 300;

	ent->nextthink = level.time + CTF_TECH_TIMEOUT;
	ent->think = TechThink;

	gi.linkentity (ent);
}

*/