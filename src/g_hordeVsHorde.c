#include "g_local.h"

static char *spawnerNames[] = {
	"leftsideBottomLeftSpawner", "leftsideBottomRightSpawner", "leftsideTopLeftSpawner", "leftsideTopRightSpawner",
	NULL
};

void setupHordeVsHordeSpawn(void)
{
	edict_t *ent;

	ent = G_Spawn();
	ent->nextthink = level.time + 20;
	ent->think = findAndTriggerSpawners;
	
}

static void findAndTriggerSpawners(edict_t *ent)
{
	
	gitem_t *spawners;
	//edict_t *spot;
	int i;

	i = 0;
	while (spawnerNames[i]) 
	{
		gi.dprintf ("%s was triggered for the first time\n", spawnerNames[i]);

		//stricmp(ent->classname, "trigger_once")
		/*if ((spawners = FindItemByClassname(spawnerNames[i])) != NULL &&
			(spot = FindSpawnerLocation()) != NULL)
			SpawnTech(spawners, spot);*/
		i++;
	}
}
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