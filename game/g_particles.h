#define PFX_EF_GIB				0x0003
#define PFX_EF_BLASTER			0x0004
#define	PFX_EF_GRENADE			0x0005
#define	PFX_EF_ROCKET			0x0006
#define PFX_EF_BFG				0x0007
#define	PFX_EF_FLIES			0x0008
#define	PFX_EF_TELEPORTER		0x0009
#define	PFX_EF_FLAG1			0x000A
#define PFX_EF_FLAG2			0x000B
#define PFX_UNDEF_QUAD			0x000C

#define PAGE_MAIN				0x0000
#define	PAGE_ENTITY_01			0x0001
#define PAGE_ENTITY_SETTINGS	0x0002

void pfxSelectEntityPage01(edict_t *ent, pmenuhnd_t *p);
void pfxEntityEffectsMenu(edict_t *ent, pmenuhnd_t *p);
void pfxMainMenu(edict_t* ent);
void pfxSpawnEmitter(edict_t *ent, vec3_t g_offset);