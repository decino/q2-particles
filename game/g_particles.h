#define PFX_EF_GIB					3
#define PFX_EF_BLASTER				4
#define	PFX_EF_GRENADE				5
#define	PFX_EF_ROCKET				6
#define PFX_EF_BFG					7
#define	PFX_EF_FLIES				8
#define	PFX_EF_TELEPORTER			9
#define	PFX_EF_FLAG1				10
#define PFX_EF_FLAG2				11
#define PFX_UNDEF_QUAD				12

#define PFX_EF_IONRIPPER			13
#define PFX_EF_GREENGIB				14
#define	PFX_EF_TRAP					15
#define	PFX_EF_TAGTRAIL				16
#define PFX_EF_TRACKER				17
#define PFX_EF_TRACKERTRAIL			18
#define PFX_EF_BLASTER2				19

#define PFX_TE_BLOOD				23
#define PFX_TE_GUNSHOT				24
#define PFX_TE_SHOTGUN				25
#define	PFX_TE_BLASTER				26
#define PFX_TE_SPARKS				27
#define PFX_TE_BULLET_SPARKS		28
#define PFX_TE_SCREEN_SPARKS		29
#define PFX_TE_SHIELD_SPARKS		30
#define PFX_TE_SPLASH				31
#define PFX_TE_LASER_SPARKS			32

#define PFX_TE_EXPLOSION1			33
#define PFX_TE_BFG_BIGEXPLOSION		34
#define PFX_TE_TELEPORT				35
#define PFX_TE_BOSSTPORT			36
#define PFX_MZ_LOGIN				37
#define PFX_MZ_LOGOUT				38
#define PFX_MZ_RESPAWN				39
#define PFX_EV_ITEM_RESPAWN			40
#define PFX_TE_TUNNEL_SPARKS		41
#define PFX_TE_WELDING_SPARKS		42

#define PFX_TE_GREENBLOOD			43
#define PFX_TE_BLASTER2				44
#define PFX_TE_FLECHETTE			45
#define PFX_TE_HEATBEAM_SPARKS		46
#define PFX_TE_HEATBEAM_STEAM		47
#define PFX_TE_STEAM				48
#define PFX_TE_CHAINFIST_SMOKE		49
#define PFX_TE_MOREBLOOD			50
#define PFX_TE_ELECTRIC_SPARKS		51
#define PFX_TE_TRACKER_EXPLOSION	52

#define PFX_UNDEF_TRACKER			53
#define PFX_TE_WIDOWBEAMOUT			54
#define PFX_TE_WIDOWSPLASH			55
#define PFX_TE_MONSTER_HEATBEAM		56
#define PFX_TE_NUKEBLAST			57
#define	PFX_TE_FLAME				58
#define	PFX_UNDEF_GENERIC			59

#define	PFX_TE_RAILTRAIL			63
#define PFX_TE_BUBBLETRAIL			64
#define PFX_TE_DEBUGTRAIL			65
#define PFX_TE_FORCEWALL			66
#define PFX_TE_BUBBLETRAIL2			67
#define PFX_TE_HEATBEAM				68

#define PAGE_MAIN				0x000F

#define PAGE_ENTITY_SETTINGS	0x000C
#define PAGE_POINT_SETTINGS		0x000D
#define PAGE_LINE_SETTINGS		0x000E

#define	PAGE_ENTITY_01			0x0000
#define	PAGE_ENTITY_02			0x0001
#define PAGE_POINT_01			0x0002
#define PAGE_POINT_02			0x0003
#define PAGE_POINT_03			0x0004
#define PAGE_POINT_04			0x0005
#define PAGE_LINE_01			0x0006

void updateLineEffectsMenu(edict_t *ent, pmenuhnd_t *p);
void pfxLineEffectsMenu01(edict_t *ent, pmenuhnd_t *p);

void updatePointEffectsMenu(edict_t *ent, pmenuhnd_t *p);
void pfxPointEffectsMenu04(edict_t *ent, pmenuhnd_t *p);
void pfxPointEffectsMenu03(edict_t *ent, pmenuhnd_t *p);
void pfxPointEffectsMenu02(edict_t *ent, pmenuhnd_t *p);
void pfxPointEffectsMenu01(edict_t *ent, pmenuhnd_t *p);

void updateEntityEffectsMenu(edict_t *ent, pmenuhnd_t *p);
void pfxEditEntityEffect(edict_t *ent, pmenuhnd_t *p);
void pfxEntityEffectsMenu02(edict_t *ent, pmenuhnd_t *p);
void pfxEntityEffectsMenu01(edict_t *ent, pmenuhnd_t *p);

void pfxResetToMainMenu(edict_t *ent, pmenuhnd_t *p);
void pfxMainMenu(edict_t* ent);

void pfxSpawnEmitter(edict_t *ent, vec3_t g_offset);