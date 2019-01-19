#include "g_local.h"

// =============================================================================================================================
// Point Particle Effects
// =============================================================================================================================
void pfxEditPointEffect(edict_t *ent, pmenuhnd_t *p)
{
	if (p->cur == 4)
	{
		ent->pfx_frequency = 1 + ent->pfx_frequency % 10;
	}
	if (p->cur == 7)
	{
		// Number of particles.
		switch (ent->pfx_selected_fx)
		{
			case PFX_TE_SPLASH:
			case PFX_TE_LASER_SPARKS:
			case PFX_TE_WELDING_SPARKS:
			case PFX_TE_TUNNEL_SPARKS:

			ent->pfx_num = (ent->pfx_num << 1);

			if (ent->pfx_num == 256)
			{
				ent->pfx_num = 0xFF;
			}
			if (ent->pfx_num == 0x00 || ent->pfx_num > 0xFF)
			{
				ent->pfx_num = 1;
			}
			break;
		}
	}
	if (p->cur == 10)
	{
		// Splash index.
		if (ent->pfx_selected_fx == PFX_TE_SPLASH)
		{
			ent->pfx_splash_index = (ent->pfx_splash_index + 1) % 7;
		}

		// Colour.
		switch (ent->pfx_selected_fx)
		{
			case PFX_TE_LASER_SPARKS:
			case PFX_TE_WELDING_SPARKS:
			case PFX_TE_TUNNEL_SPARKS:

			ent->pfx_colour = (ent->pfx_colour + 1) % 256;

			break;
		}
	}
	updatePointEffectsMenu(ent, p);
}

void pfxPointEffectsMenu(edict_t *ent, pmenuhnd_t *p)
{
	if (ent->prev_menu == PAGE_POINT_01)
	{
		pfxPointEffectsMenu01(ent, p);
	}
	else
	{
		pfxPointEffectsMenu02(ent, p);
	}
}

pmenu_t point_fx_settings[] = 
{
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Entity Effect Settings",	PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Frequency (Hz)",			PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Previous",					PMENU_ALIGN_LEFT,	pfxPointEffectsMenu },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
};

void updatePointEffectsMenu(edict_t *ent, pmenuhnd_t *p)
{
	static char frequency[8];
	static char num[4];
	static char splash_index[4];
	static char colour[4];

	sprintf(frequency, "%d", ent->pfx_frequency);
	PMenu_UpdateEntry(p->entries + 4, frequency, PMENU_ALIGN_LEFT, pfxEditPointEffect);

	// Number of particles.
	switch (ent->pfx_selected_fx)
	{
		case PFX_TE_SPLASH:
		case PFX_TE_LASER_SPARKS:
		case PFX_TE_TUNNEL_SPARKS:
		case PFX_TE_WELDING_SPARKS:
		
		PMenu_UpdateEntry(p->entries + 6, "*Number of Particles", PMENU_ALIGN_LEFT, NULL);
		sprintf(num, "%d", ent->pfx_num);
		PMenu_UpdateEntry(p->entries + 7, num, PMENU_ALIGN_LEFT, pfxEditPointEffect);

		break;
	}
	// Splash index.
	if (ent->pfx_selected_fx == PFX_TE_SPLASH)
	{
		PMenu_UpdateEntry(p->entries + 9, "*Splash Index", PMENU_ALIGN_LEFT, NULL);
		sprintf(splash_index, "%d", ent->pfx_splash_index);
		PMenu_UpdateEntry(p->entries + 10, splash_index, PMENU_ALIGN_LEFT, pfxEditPointEffect);
	}
	// Colour.
	switch (ent->pfx_selected_fx)
	{
		case PFX_TE_LASER_SPARKS:
		case PFX_TE_TUNNEL_SPARKS:
		case PFX_TE_WELDING_SPARKS:

		PMenu_UpdateEntry(p->entries + 9, "*Colour", PMENU_ALIGN_LEFT, NULL);
		sprintf(colour, "%d", ent->pfx_colour);
		PMenu_UpdateEntry(p->entries + 10, colour, PMENU_ALIGN_LEFT, pfxEditPointEffect);

		break;
	}
	PMenu_Update(ent);
}

void pfxSelectPointSettings(edict_t *ent, pmenuhnd_t *p)
{
	if (ent->last_menu != PAGE_POINT_SETTINGS)
	{
		ent->pfx_selected_fx = p->cur + (ent->last_menu * 10);
		ent->prev_menu = ent->last_menu;
	}
	ent->last_menu = PAGE_POINT_SETTINGS;

	PMenu_Close(ent);
	PMenu_Open(ent, point_fx_settings, -1, sizeof(point_fx_settings) / sizeof(pmenu_t), NULL);

	updatePointEffectsMenu(ent, p);
}

pmenu_t point_fx_menu_02[] = 
{
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Select Point Effect",		PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Explosion",					PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "BFG Explosion",				PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Teleport",					PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Big Teleport",				PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Log In",						PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Log Out",					PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Respawn",					PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Respawning Item",			PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Tunnel Sparks",				PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Welding Sparks",				PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Next",						PMENU_ALIGN_LEFT,	pfxPointEffectsMenu02 },
	{ "Previous",					PMENU_ALIGN_LEFT,	pfxResetToMainMenu },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
};

void pfxPointEffectsMenu02(edict_t *ent, pmenuhnd_t *p)
{
	ent->last_menu = PAGE_POINT_02;

	PMenu_Close(ent);
	PMenu_Open(ent, point_fx_menu_02, -1, sizeof(point_fx_menu_02) / sizeof(pmenu_t), NULL);
}

pmenu_t point_fx_menu_01[] = 
{
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Select Point Effect",		PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Blood Impact",				PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Gunshot Impact",				PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Shotgun Pellet Impact",		PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Blaster Impact",				PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Sparks",						PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Bullet Sparks",				PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Power Screen Sparks",		PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Power Shield Sparks",		PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Splash",						PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ "Laser Sparks",				PMENU_ALIGN_LEFT,	pfxSelectPointSettings },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Next",						PMENU_ALIGN_LEFT,	pfxPointEffectsMenu02 },
	{ "Previous",					PMENU_ALIGN_LEFT,	pfxResetToMainMenu },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
};

// =============================================================================================================================
// Entity Particle Effects
// =============================================================================================================================
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
	}
	if (p->cur == 7)
	{
		ent->pfx_projectile_speed = (ent->pfx_projectile_speed + 100) % 2100;
	}
	updateEntityEffectsMenu(ent, p);
}

void pfxEntityEffectsMenu(edict_t *ent, pmenuhnd_t *p)
{
	if (ent->prev_menu == PAGE_ENTITY_01)
	{
		pfxEntityEffectsMenu01(ent, p);
	}
	else
	{
		pfxEntityEffectsMenu02(ent, p);
	}
}

pmenu_t entity_fx_settings[] = 
{
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Entity Effect Settings",	PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Frequency (Hz)",			PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Projectile Speed",			PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
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

void updateEntityEffectsMenu(edict_t *ent, pmenuhnd_t *p)
{
	static char frequency[8];
	static char speed[8];

	sprintf(frequency, "%d", ent->pfx_frequency);
	sprintf(speed, "%d", ent->pfx_projectile_speed);

	PMenu_UpdateEntry(p->entries + 4, frequency, PMENU_ALIGN_LEFT, pfxEditEntityEffect);
	PMenu_UpdateEntry(p->entries + 7, speed, PMENU_ALIGN_LEFT, pfxEditEntityEffect);
	PMenu_Update(ent);
}

void pfxSelectEntitySettings(edict_t *ent, pmenuhnd_t *p)
{
	if (ent->last_menu != PAGE_ENTITY_SETTINGS)
	{
		ent->pfx_selected_fx = p->cur + (ent->last_menu * 10);
		ent->prev_menu = ent->last_menu;
	}
	ent->last_menu = PAGE_ENTITY_SETTINGS;

	PMenu_Close(ent);
	PMenu_Open(ent, entity_fx_settings, -1, sizeof(entity_fx_settings) / sizeof(pmenu_t), NULL);

	updateEntityEffectsMenu(ent, p);
}

pmenu_t entity_fx_menu_02[] = 
{
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Select Entity Effect",		PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Ion Ripper Trail",			PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Gekk Gib Trail",				PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Trap Vortex",				PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Tag Token Trail",			PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Tracker Trail",				PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Tracker Daemon",				PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Green Blaster Trail",		PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "",							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Previous",					PMENU_ALIGN_LEFT,	pfxEntityEffectsMenu01 },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
};

void pfxEntityEffectsMenu02(edict_t *ent, pmenuhnd_t *p)
{
	ent->last_menu = PAGE_ENTITY_02;

	PMenu_Close(ent);
	PMenu_Open(ent, entity_fx_menu_02, -1, sizeof(entity_fx_menu_02) / sizeof(pmenu_t), NULL);
}

void pfxResetToMainMenu(edict_t *ent, pmenuhnd_t *p)
{
	ent->last_menu = PAGE_MAIN;
	ent->prev_menu = ent->last_menu;

	pfxMainMenu(ent);
}

pmenu_t entity_fx_menu_01[] = 
{
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*Select Entity Effect",		PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Bloody Gib Trail",			PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Blaster Trail",				PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Grenade Smoke",				PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Rocket Smoke",				PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "BFG Particles",				PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Flies",						PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Teleporter Fountain",		PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Red Flag Particles",			PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Blue Flag Particles",		PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ "Quad Damage Trail",			PMENU_ALIGN_LEFT,	pfxSelectEntitySettings },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Next",						PMENU_ALIGN_LEFT,	pfxEntityEffectsMenu02 },
	{ "Previous",					PMENU_ALIGN_LEFT,	pfxResetToMainMenu },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
};

void pfxEntityEffectsMenu01(edict_t *ent, pmenuhnd_t *p)
{
	ent->last_menu = PAGE_ENTITY_01;

	PMenu_Close(ent);
	PMenu_Open(ent, entity_fx_menu_01, -1, sizeof(entity_fx_menu_01) / sizeof(pmenu_t), NULL);
}

void pfxPointEffectsMenu01(edict_t *ent, pmenuhnd_t *p)
{
	ent->last_menu = PAGE_POINT_01;

	PMenu_Close(ent);
	PMenu_Open(ent, point_fx_menu_01, -1, sizeof(point_fx_menu_01) / sizeof(pmenu_t), NULL);
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
	{ "Entity Effects",				PMENU_ALIGN_LEFT,	pfxEntityEffectsMenu01 },
	{ "Point Effects",				PMENU_ALIGN_LEFT,	pfxPointEffectsMenu01 },
	{ "Line Effects",				PMENU_ALIGN_LEFT,	pfxLineEffectsMenu },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*www.youtube.com/c/decino",	PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
};

void pfxMainMenu(edict_t* ent)
{
	PMenu_Close(ent);

	switch (ent->last_menu)
	{
		case PAGE_MAIN:				PMenu_Open(ent, main_menu, -1, sizeof(main_menu) / sizeof(pmenu_t), NULL); break;
		case PAGE_ENTITY_SETTINGS:	PMenu_Open(ent, entity_fx_settings, -1, sizeof(entity_fx_settings) / sizeof(pmenu_t), NULL); pfxSelectEntitySettings(ent, ent->client->menu); break;
		case PAGE_ENTITY_01:		PMenu_Open(ent, entity_fx_menu_01, -1, sizeof(entity_fx_menu_01) / sizeof(pmenu_t), NULL); break;
		case PAGE_ENTITY_02:		PMenu_Open(ent, entity_fx_menu_02, -1, sizeof(entity_fx_menu_02) / sizeof(pmenu_t), NULL); break;
		case PAGE_POINT_SETTINGS:	PMenu_Open(ent, point_fx_settings, -1, sizeof(entity_fx_settings) / sizeof(pmenu_t), NULL); pfxSelectPointSettings(ent, ent->client->menu); break;
		case PAGE_POINT_01:			PMenu_Open(ent, point_fx_menu_01, -1, sizeof(point_fx_menu_01) / sizeof(pmenu_t), NULL); break;
	}
}

int getEntityEffect(int selected_fx)
{
	switch (selected_fx)
	{
		case PFX_EF_GIB:			return EF_GIB;
		case PFX_EF_BLASTER:		return EF_BLASTER;
		case PFX_EF_GRENADE:		return EF_GRENADE;
		case PFX_EF_ROCKET:			return EF_ROCKET;
		case PFX_EF_BFG:			return EF_BFG;				// TODO: Work without anim fast.
		case PFX_EF_FLIES:			return EF_FLIES;
		case PFX_EF_TELEPORTER:		return EF_TELEPORTER;
		case PFX_EF_FLAG1:			return EF_FLAG1;
		case PFX_EF_FLAG2:			return EF_FLAG2;
		case PFX_UNDEF_QUAD:		return EF_FLAG2|EF_TRACKER;	// TODO: edit client.

		case PFX_EF_IONRIPPER:		return EF_IONRIPPER;
		case PFX_EF_GREENGIB:		return EF_GREENGIB;
		case PFX_EF_TRAP:			return EF_TRAP;
		case PFX_EF_TAGTRAIL:		return EF_TAGTRAIL;
		case PFX_EF_TRACKER:		return EF_TRACKER;
		case PFX_EF_TRACKERTRAIL:	return EF_TRACKERTRAIL;
		case PFX_EF_BLASTER2:		return EF_BLASTER|EF_TRACKER;

		default:					return 0x00000000;
	}
}

int getPointEffect(int selected_fx)
{
	switch (selected_fx)
	{
		case PFX_TE_BLOOD:				return TE_BLOOD;
		case PFX_TE_GUNSHOT:			return TE_GUNSHOT;
		case PFX_TE_SHOTGUN:			return TE_SHOTGUN;
		case PFX_TE_BLASTER:			return TE_BLASTER;
		case PFX_TE_SPARKS:				return TE_SPARKS;
		case PFX_TE_BULLET_SPARKS:		return TE_BULLET_SPARKS;
		case PFX_TE_SCREEN_SPARKS:		return TE_SCREEN_SPARKS;
		case PFX_TE_SHIELD_SPARKS:		return TE_SHIELD_SPARKS;
		case PFX_TE_SPLASH:				return TE_SPLASH;
		case PFX_TE_LASER_SPARKS:		return TE_LASER_SPARKS;
		case PFX_TE_EXPLOSION1:			return TE_EXPLOSION1;
		case PFX_TE_BFG_BIGEXPLOSION:	return TE_BFG_BIGEXPLOSION;
		case PFX_TE_TELEPORT:			return TE_TELEPORT_EFFECT;
		case PFX_TE_BOSSTPORT:			return TE_BOSSTPORT;
		case PFX_TE_TUNNEL_SPARKS:		return TE_TUNNEL_SPARKS;
		case PFX_TE_WELDING_SPARKS:		return TE_WELDING_SPARKS;

		default:						return 0x00000000;
	}
}

// =============================================================================================================================
// Particle Emitter
// =============================================================================================================================
void pfxEmitterThink(edict_t* ent)
{
	edict_t*	projectile;
	vec3_t		dir;

	int selected_fx = ent->owner->pfx_selected_fx;

	AngleVectors(ent->s.angles, dir, NULL, NULL);

	if (selected_fx <= PFX_EF_BLASTER2)
	{
		projectile = G_Spawn();

		VectorCopy(ent->s.origin, projectile->s.origin);
		VectorCopy(ent->s.origin, projectile->s.old_origin);
		vectoangles(dir, projectile->s.angles);
		VectorScale(dir, ent->owner->pfx_projectile_speed, projectile->velocity);
		projectile->movetype = MOVETYPE_FLYMISSILE;
		projectile->clipmask = MASK_SHOT;
		projectile->solid = SOLID_BBOX;
		projectile->s.effects = getEntityEffect(selected_fx);
		VectorClear(projectile->mins);
		VectorClear(projectile->maxs);
		projectile->s.modelindex = gi.modelindex("models/objects/flash/tris.md2");
		projectile->touch = G_FreeEdict;

		gi.linkentity(projectile);
	}
	else if (selected_fx == PFX_MZ_LOGIN || selected_fx == PFX_MZ_LOGOUT || selected_fx == PFX_MZ_RESPAWN)
	{
		gi.WriteByte(svc_muzzleflash);
		gi.WriteShort(ent - g_edicts);

		switch (selected_fx)
		{
			case PFX_MZ_LOGIN:		gi.WriteByte(MZ_LOGIN);		break;
			case PFX_MZ_LOGOUT:		gi.WriteByte(MZ_LOGOUT);	break;
			case PFX_MZ_RESPAWN:	gi.WriteByte(MZ_RESPAWN);	break;
		}
		gi.multicast(ent->s.origin, MULTICAST_PVS);
	}
	else if (selected_fx == PFX_EV_ITEM_RESPAWN)
	{
		ent->s.event = EV_ITEM_RESPAWN;
	}
	else if (selected_fx >= PFX_TE_BLOOD) // && <= PFX_???)
	{
		gi.WriteByte (svc_temp_entity);
		gi.WriteByte(getPointEffect(selected_fx));

		// Number of particles.
		switch (selected_fx)
		{
			case PFX_TE_SPLASH:
			case PFX_TE_LASER_SPARKS:
			case PFX_TE_TUNNEL_SPARKS:
			case PFX_TE_WELDING_SPARKS:

			gi.WriteByte(ent->owner->pfx_num);

			break;
		}
		gi.WritePosition(ent->s.origin);

		if (selected_fx != PFX_TE_EXPLOSION1		&& 
			selected_fx != PFX_TE_BFG_BIGEXPLOSION	&& 
			selected_fx != PFX_TE_TELEPORT			&& 
			selected_fx != PFX_TE_BOSSTPORT)
		{
			gi.WriteDir(dir);
		}

		// Splash index.
		if (selected_fx == PFX_TE_SPLASH)
		{
			gi.WriteByte(ent->owner->pfx_splash_index);
		}
		// Colour.
		switch (selected_fx)
		{
			case PFX_TE_LASER_SPARKS:
			case PFX_TE_TUNNEL_SPARKS:
			case PFX_TE_WELDING_SPARKS:

			gi.WriteByte(ent->owner->pfx_colour);

			break;
		}
		gi.multicast(ent->s.origin, MULTICAST_PVS);
	}
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