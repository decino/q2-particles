#include "g_local.h"

static void P_ProjectSource(gclient_t *client, vec3_t point, vec3_t distance, vec3_t forward, vec3_t right, vec3_t result)
{
	vec3_t	_distance;

	VectorCopy(distance, _distance);

	if (client->pers.hand == LEFT_HANDED)
	{
		_distance[1] *= -1;
	}
	else if (client->pers.hand == CENTER_HANDED)
	{
		_distance[1] = 0;
	}
	G_ProjectSource(point, _distance, forward, right, result);
}

void pfxEditEntityEffect(edict_t *ent, pmenuhnd_t *p)
{
	if (p->cur == 4)
	{
		ent->pfx_frequency = 1 + ent->pfx_frequency % 10;
		gi.dprintf("Frequency: %d Hz\n", ent->pfx_frequency);
	}
	if (p->cur == 7)
	{
		ent->pfx_projectile_speed = 100 + ent->pfx_projectile_speed % 2000;
		gi.dprintf("Projectile speed: %d\n", ent->pfx_projectile_speed);
	}
	/*
	if (p->cur == 10)
	{
		ent->pfx_hide_emitter = !ent->pfx_hide_emitter;

		ent->pfx_emitter->s.renderfx ^= RF_WEAPONMODEL;
		gi.dprintf("Hidden emitter: %d\n", ent->pfx_hide_emitter);
	}
	*/
}

pmenu_t entity_fx_settings[] = 
{
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Entity Effect Settings",	PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Frequency (Hz)",			PMENU_ALIGN_LEFT,	NULL },
	{ "10",							PMENU_ALIGN_LEFT,	pfxEditEntityEffect },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Projectile Speed",			PMENU_ALIGN_LEFT,	NULL },
	{ "1000",						PMENU_ALIGN_LEFT,	pfxEditEntityEffect },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Previous",					PMENU_ALIGN_LEFT,	pfxEntityEffectsMenu },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
};

void pfxSelectEntityPage01(edict_t *ent, pmenuhnd_t *p)
{
	ent->last_menu = PAGE_ENTITY_SETTINGS;
	ent->pfx_selected_fx = p->cur;

	PMenu_Close(ent);
	PMenu_Open(ent, entity_fx_settings, -1, sizeof(entity_fx_settings) / sizeof(pmenu_t), NULL);
}

pmenu_t entity_fx_menu_01[] = 
{
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Select Entity Effect",		PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Bloody Gib Trail",			PMENU_ALIGN_LEFT,	pfxSelectEntityPage01 },
	{ "Blaster Trail",				PMENU_ALIGN_LEFT,	pfxSelectEntityPage01 },
	{ "Grenade Smoke",				PMENU_ALIGN_LEFT,	pfxSelectEntityPage01 },
	{ "Rocket Smoke",				PMENU_ALIGN_LEFT,	pfxSelectEntityPage01 },
	{ "BFG Particles",				PMENU_ALIGN_LEFT,	pfxSelectEntityPage01 },
	{ "Flies",						PMENU_ALIGN_LEFT,	pfxSelectEntityPage01 },
	{ "Teleporter Fountain",		PMENU_ALIGN_LEFT,	pfxSelectEntityPage01 },
	{ "Red Flag Particles",			PMENU_ALIGN_LEFT,	pfxSelectEntityPage01 },
	{ "Blue Flag Particles",		PMENU_ALIGN_LEFT,	pfxSelectEntityPage01 },
	{ "Quad Damage Trail",			PMENU_ALIGN_LEFT,	pfxSelectEntityPage01 },
	{ "",							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Next",						PMENU_ALIGN_LEFT,	NULL },
	{ "Previous",					PMENU_ALIGN_LEFT,	pfxMainMenu },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
};

void pfxEntityEffectsMenu(edict_t *ent, pmenuhnd_t *p)
{
	ent->last_menu = PAGE_ENTITY_01;

	PMenu_Close(ent);
	PMenu_Open(ent, entity_fx_menu_01, -1, sizeof(entity_fx_menu_01) / sizeof(pmenu_t), NULL);
}

void pfxPointEffectsMenu(edict_t *ent, pmenuhnd_t *p)
{
	PMenu_Close(ent);
}

void pfxLineEffectsMenu(edict_t *ent, pmenuhnd_t *p)
{
	PMenu_Close(ent);
}

pmenu_t main_menu[] = 
{
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Quake II",					PMENU_ALIGN_LEFT,	NULL },
	{ "*Particle Effect Tester",	PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Use [ and ] to move",		PMENU_ALIGN_LEFT,	NULL },
	{ "the cursor.",				PMENU_ALIGN_LEFT,	NULL },
	{ "Press enter to select.",		PMENU_ALIGN_LEFT,	NULL },
	{ "Use tab to open or",			PMENU_ALIGN_LEFT,	NULL },
	{ "close menu.",				PMENU_ALIGN_LEFT,	NULL },
	{ "Shoot gun to spawn a",		PMENU_ALIGN_LEFT,	NULL },
	{ "particle emitter.",			PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Entity Effects",				PMENU_ALIGN_LEFT,	pfxEntityEffectsMenu },
	{ "Point Effects",				PMENU_ALIGN_LEFT,	pfxPointEffectsMenu },
	{ "Line Effects",				PMENU_ALIGN_LEFT,	pfxLineEffectsMenu },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*www.youtube.com/c/decino",	PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
};

void pfxMainMenu(edict_t* ent)
{
	switch (ent->last_menu)
	{
		case 0: PMenu_Open(ent, main_menu, -1, sizeof(main_menu) / sizeof(pmenu_t), NULL); break;
		case 1: PMenu_Open(ent, entity_fx_menu_01, -1, sizeof(entity_fx_menu_01) / sizeof(pmenu_t), NULL); break;
		case 2: PMenu_Open(ent, entity_fx_settings, -1, sizeof(entity_fx_settings) / sizeof(pmenu_t), NULL); break;
	}
}

int getEntityEffect(edict_t* ent)
{
	switch (ent->pfx_selected_fx)
	{
		case PFX_EF_GIB:		return EF_GIB;
		case PFX_EF_BLASTER:	return EF_BLASTER;
		case PFX_EF_GRENADE:	return EF_GRENADE;
		case PFX_EF_ROCKET:		return EF_ROCKET;
		case PFX_EF_BFG:		return EF_BFG;				// TODO: Work without anim fast.
		case PFX_EF_FLIES:		return EF_FLIES;
		case PFX_EF_TELEPORTER: return EF_TELEPORTER;
		case PFX_EF_FLAG1:		return EF_FLAG1;
		case PFX_EF_FLAG2:		return EF_FLAG2;
		case PFX_UNDEF_QUAD:	return EF_FLAG2|EF_TRACKER;	// TODO: edit client.

		default:				return 0x00000000;
	}
}

void pfxEmitterThink(edict_t* ent)
{
	edict_t*	projectile;
	vec3_t		dir;

	AngleVectors(ent->s.angles, dir, NULL, NULL);

	projectile = G_Spawn();
	VectorCopy(ent->s.origin, projectile->s.origin);
	VectorCopy(ent->s.origin, projectile->s.old_origin);
	vectoangles(dir, projectile->s.angles);
	VectorScale(dir, ent->owner->pfx_projectile_speed, projectile->velocity);
	projectile->movetype = MOVETYPE_FLYMISSILE;
	projectile->clipmask = MASK_SHOT;
	projectile->solid = SOLID_BBOX;
	projectile->s.effects = getEntityEffect(ent->owner);
	VectorClear(projectile->mins);
	VectorClear(projectile->maxs);
	projectile->s.modelindex = gi.modelindex("models/objects/flash/tris.md2");
	projectile->touch = G_FreeEdict;
	gi.linkentity(projectile);

	ent->nextthink = level.time + (1.0f / (float)ent->owner->pfx_frequency);
}

void pfxSpawnEmitter(edict_t *ent, vec3_t g_offset)
{
	edict_t*	emitter;
	vec3_t		forward, right;
	vec3_t		start;
	vec3_t		offset;

	AngleVectors(ent->client->v_angle, forward, right, NULL);
	VectorSet(offset, 0, 0, ent->viewheight - 8);
	P_ProjectSource(ent->client, ent->s.origin, offset, forward, right, start);

	ent->client->kick_angles[0] = -1;
	VectorNormalize(forward);

	emitter = ent->pfx_emitter;

	if (emitter != NULL)
	{
		G_FreeEdict(emitter);
	}
	emitter = G_Spawn();
	VectorCopy(start, emitter->s.origin);
	VectorCopy(start, emitter->s.old_origin);
	vectoangles(forward, emitter->s.angles);
	emitter->movetype = MOVETYPE_FLYMISSILE;
	emitter->solid = SOLID_NOT;
	VectorClear(emitter->mins);
	VectorClear(emitter->maxs);
	emitter->s.modelindex = gi.modelindex("models/monsters/parasite/tip/tris.md2");
	emitter->owner = ent;
	emitter->think = pfxEmitterThink;
	emitter->nextthink = level.time + 0.0;
	gi.linkentity(emitter);

	ent->pfx_emitter = emitter;

	gi.WriteByte(svc_muzzleflash);
	gi.WriteShort(ent - g_edicts);
	gi.WriteByte(MZ2_MEDIC_BLASTER_1);
	gi.multicast(ent->s.origin, MULTICAST_PVS);
}