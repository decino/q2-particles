#define PFX_EF_GIB				3
#define PFX_EF_BLASTER			4
#define	PFX_EF_GRENADE			5
#define	PFX_EF_ROCKET			6
#define PFX_EF_BFG				7
#define	PFX_EF_FLIES			8
#define	PFX_EF_TELEPORTER		9
#define	PFX_EF_FLAG1			10
#define PFX_EF_FLAG2			11
#define PFX_UNDEF_QUAD			12

#define PFX_EF_IONRIPPER		13
#define PFX_EF_GREENGIB			14
#define	PFX_EF_TRAP				15
#define	PFX_EF_TAGTRAIL			16
#define PFX_EF_TRACKER			17
#define PFX_EF_TRACKERTRAIL		18
#define PFX_EF_BLASTER2			19

#define PAGE_MAIN				0x000F

#define PAGE_ENTITY_SETTINGS	0x000C
#define PAGE_POINT_SETTINGS		0x000D
#define PAGE_LINE_SETTINGS		0x000E

#define	PAGE_ENTITY_01			0x0000
#define	PAGE_ENTITY_02			0x0001

void pfxEditEntityEffect(edict_t *ent, pmenuhnd_t *p);
void pfxEntityEffectsMenu02(edict_t *ent, pmenuhnd_t *p);
void pfxEntityEffectsMenu01(edict_t *ent, pmenuhnd_t *p);
void pfxMainMenu(edict_t* ent);

void pfxSpawnEmitter(edict_t *ent, vec3_t g_offset);