#include "g_local.h"

void pfxEntityEffectsMenu(edict_t *ent, pmenuhnd_t *p)
{
	PMenu_Close(ent);
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
	{ "Shoot gun to spawn a",		PMENU_ALIGN_LEFT,	NULL },
	{ "particle emitter.",			PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "Entity Effects",				PMENU_ALIGN_LEFT,	pfxEntityEffectsMenu },
	{ "Point Effects",				PMENU_ALIGN_LEFT,	pfxPointEffectsMenu },
	{ "Line Effects",				PMENU_ALIGN_LEFT,	pfxLineEffectsMenu },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
	{ "*www.youtube.com/c/decino",	PMENU_ALIGN_LEFT,	NULL },
	{ NULL,							PMENU_ALIGN_LEFT,	NULL },
};

void pfxMainMenu(edict_t* ent)
{
	PMenu_Open(ent, main_menu, -1, sizeof(main_menu) / sizeof(pmenu_t), NULL);
}