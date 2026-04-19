#include "ffcc/singmenu.h"
#include "ffcc/chara.h"
#include "ffcc/file.h"
#include "ffcc/fontman.h"
#include "ffcc/graphic.h"
#include "ffcc/memory.h"
#include "ffcc/astar.h"
#include "ffcc/p_chara.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/linkage.h"
#include "ffcc/ptrarray.h"
#include "ffcc/sound.h"
extern "C" {
extern u8 gSingMenuItemIconByType[];
extern char* gSingMenuTextTableEn[];
extern char* gSingMenuTextTableDe[];
extern char* gSingMenuTextTableIt[];
extern char* gSingMenuTextTableFr[];
extern char* gSingMenuTextTableEs[];
extern char* gSingMenuHairTableFr[];
extern char* gSingMenuAttrTableEn[];
extern char* gSingMenuAttrTableDe[];
extern char* gSingMenuAttrTableIt[];
extern char* gSingMenuAttrTableFr[];
extern char* gSingMenuAttrTableEs[];
}
#include "ffcc/textureman.h"
#include "ffcc/util.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

typedef signed short s16;
typedef unsigned char u8;

struct SingleFadeEntry
{
    char pad_00[0x10];
    float alpha;
    char pad_14[0x0C];
    int elapsed;
    int startFrame;
    int duration;
    char pad_2C[0x14];
};

struct SingleFadeState
{
    s16 count;
    s16 pad_02;
    s16 active;
    s16 done;
    SingleFadeEntry entries[64];
};

extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void DrawFilter__8CMenuPcsFUcUcUcUc(CMenuPcs*, u8, u8, u8, u8);
extern "C" void SetProjection__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void SetLight__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void RestoreProjection__8CMenuPcsFv(CMenuPcs*);
extern "C" void Draw__9CShopMenuFv(void*);
extern "C" void Calc__9CShopMenuFv(void*);
extern "C" void SingleDrawCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" void SetFrame__Q26CChara6CModelFf(float, CChara::CModel*);
extern "C" void AddFrame__Q26CChara6CModelFf(float, CChara::CModel*);
extern "C" void SetMatrix__Q26CChara6CModelFPA4_f(CChara::CModel*, Mtx);
extern "C" void CalcMatrix__Q26CChara6CModelFv(CChara::CModel*);
extern "C" void CalcSkin__Q26CChara6CModelFv(CChara::CModel*);
extern "C" void _WaitDrawDone__8CGraphicFPci(CGraphic*, const char*, int);
extern "C" void DestroyTempBuffer__8CGraphicFv(CGraphic*);
extern "C" int GetModelNo__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" void* __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* __nw__11CTextureSetFUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" CCharaPcs::CHandle* __ct__Q29CCharaPcs7CHandleFv(CCharaPcs::CHandle*);
extern "C" CTextureSet* __ct__11CTextureSetFv(CTextureSet*);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __dl__FPv(void*);
extern "C" void __dla__FPv(void*);
extern "C" void Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii(CTextureSet*, void*, CMemory::CStage*, int, void*, int, int);
extern "C" int Find__11CTextureSetFPc(CTextureSet*, char*);
extern "C" char* GetLangString__5CGameFv(void*);
extern "C" void loadFont__8CMenuPcsFiPcii(CMenuPcs*, int, char*, int, int);
extern "C" void loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii(CMenuPcs*, char**, int, int, void*, int, int, int);
extern "C" void freeTexture__8CMenuPcsFiiii(CMenuPcs*, int, int, int, int);
extern "C" void DrawHeart__8CMesMenuFffff(void*, float, float, float, float);
extern "C" void createSingleMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void SingMenuInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void CreateShopMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void CreateSmithMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" char* s_stand_80332a24;
char s_singmenu_cpp_801de8d4[] = "singmenu.cpp";
extern "C" char* s_dvd__smenu__s_tex_801de8e4;
extern "C" char s_dvd__smenu_subfont_fnt_801de8f8[];
extern "C" char* PTR_s_solo1_80214b18[];
extern "C" char* PTR_s_solo2_80214a8c[];
extern "C" int DAT_80214ab0;
extern "C" int GetItemType__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" char* PTR_s_Tutti_802143ec;
extern "C" char* PTR_s_Alle_Rassen_8021430c;
extern "C" char* PTR_s_Todos_802145ac;
extern "C" char* PTR_DAT_802144cc;
extern "C" char* PTR_DAT_8021422c;
extern "C" char* PTR_s_Clavat_80214110[];
extern "C" char* PTR_s_Clavat_802140f0[];
extern "C" char* PTR_s_Clavat_80214100[];
extern "C" char* PTR_s_Clavate[];
extern "C" char* PTR_s_Clavat_80214120[];
extern "C" char* PTR_s_Maschio_802143e4[];
extern "C" char* PTR_DAT_80214304[];
extern "C" char* PTR_s_Hombre_802145a4[];
extern "C" char* PTR_s_Masculin_802144c4[];
extern "C" char* PTR_DAT_80214224[];
extern "C" char DAT_80332958[];
extern "C" char DAT_8033295c[];
extern "C" int DAT_802381a7;
extern "C" char* PTR_s_Blacksmith[];
extern "C" char* PTR_s_Schmied[];
extern "C" char* PTR_s_Fabbri[];
extern "C" char* PTR_s_Forgeron[];
extern "C" char* PTR_s_Herrero[];
extern "C" char* PTR_s_Cowlick[];
extern "C" char* PTR_s_Spitzschopf[];
extern "C" char* PTR_s_Ciuffo_ribelle[];
extern "C" char* PTR_s_Remolino[];
extern "C" unsigned char DAT_80214a50[];
extern "C" {
extern char lbl_803320D8[];
extern char lbl_803320E0[];
extern char lbl_803320E8[];
extern char lbl_803320F0[];
extern char lbl_803320F8[];
extern char lbl_80332100[];
extern char lbl_80332108[];
extern char lbl_80332110[];
extern char lbl_80332118[];
extern char lbl_80332120[];
extern char lbl_80332128[];
extern char lbl_80332130[];
extern char lbl_80332138[];
extern char lbl_80332140[];
extern char lbl_80332148[];
extern char lbl_80332150[];
extern char lbl_80332158[];
extern char lbl_80332160[];
extern char lbl_80332168[];
extern char lbl_80332170[];
extern char lbl_80332178[];
extern char lbl_80332180[];
extern char lbl_80332188[];
extern char lbl_80332190[];
extern char lbl_80332198[];
extern char lbl_803321A0[];
extern char lbl_803321A8[];
extern char lbl_803321B0[];
extern char lbl_803321B8[];
extern char lbl_80332574[];
extern char lbl_8033257C[];
extern char lbl_80332584[];
extern char lbl_80332588[];
extern char lbl_80332590[];
extern char lbl_80332598[];
extern char lbl_803325A0[];
extern char lbl_803325A8[];
extern char lbl_803325B0[];
extern char lbl_803325B8[];
extern char lbl_803325C0[];
extern char lbl_803325C8[];
extern char lbl_803325D0[];
extern char lbl_803325D8[];
extern char lbl_803325E0[];
extern char lbl_803325E8[];
extern char lbl_803325F0[];
extern char lbl_803325F8[];
extern char lbl_80332600[];
extern char lbl_80332608[];
extern char lbl_8033260C[];
extern char lbl_80332614[];
extern char lbl_8033261C[];
extern char lbl_80332624[];
extern char lbl_8033262C[];
extern char lbl_80332634[];
extern char lbl_80332638[];
extern char lbl_80332640[];
extern char lbl_80332648[];
extern char lbl_80332650[];
extern char lbl_80332658[];
extern char lbl_80332660[];
extern char lbl_80332668[];
extern char lbl_80332670[];
extern char lbl_80332678[];
extern char lbl_80332680[];
extern char lbl_80332688[];
extern char lbl_80332690[];
extern char lbl_80332698[];
extern char lbl_803326A0[];
extern char lbl_803326A8[];
extern char lbl_803326B0[];
extern char lbl_803326B8[];
extern char lbl_803326C0[];
extern char lbl_803326C8[];
extern char lbl_803326D0[];
extern char lbl_803326D8[];
extern char lbl_803326E0[];
extern char lbl_803326E8[];
extern char lbl_803326F0[];
extern char lbl_803326F8[];
extern char lbl_80332700[];
extern char lbl_80332708[];
extern char lbl_80332710[];
extern char s_Blacksmith_801DD718[];
extern char s_Fisherman_801DD724[];
extern char s_Merchant_801DD730[];
extern char s_Alchemist_801DD73C[];
extern char s_Schneider_801DD748[];
extern char s_Agricoltori_801DD760[];
extern char s_Allevatori_801DD76C[];
extern char s_Pescatori_801DD778[];
extern char s_Mercanti_801DD784[];
extern char s_Alchimisti_801DD790[];
extern char s_Forgeron_801DD79C[];
extern char s_Tailleur_801DD7A8[];
extern char s_Marchand_801DD7B4[];
extern char s_Alchimiste_801DD7C0[];
extern char s_Campesino_801DD7CC[];
extern char s_Granjero_801DD7D8[];
extern char s_Molinero_801DD7E4[];
extern char s_Pescador_801DD7F0[];
extern char s_Comerciante_801DD7FC[];
extern char s_Alquimista_801DD808[];
extern char s_Headband_801DDD60[];
extern char s_Long_Hair_801DDD6C[];
extern char s_Short_Hair_801DDD78[];
extern char s_Dark_Coat_801DDD84[];
extern char s_White_Cap_801DDD90[];
extern char s_Bare_Head_801DDD9C[];
extern char s_Horned_Helm_801DDDA8[];
extern char s_Steel_Visor_801DDDB4[];
extern char s_Bucket_Head_801DDDC0[];
extern char s_Blue_Armor_801DDDCC[];
extern char s_Red_Mask_801DDDD8[];
extern char s_One_Horn_801DDDE4[];
extern char s_Long_Beak_801DDDF0[];
extern char s_Black_Mage_801DDDFC[];
extern char s_Heart_Top_801DDE08[];
extern char s_Shark_Eyes_801DDE14[];
extern char s_Bandanna_801DDE20[];
extern char s_Raccoon_Tail_801DDE2C[];
extern char s_Owl_Head_801DDE3C[];
extern char s_Spitzschopf_801DDE48[];
extern char s_Stirnband_801DDE54[];
extern char s_Kopftuch_801DDE60[];
extern char s_lange_Haare_801DDE6C[];
extern char s_kurze_Haare_801DDE78[];
extern char s_mittellang_801DDE84[];
extern char s_Spitzhelm_801DDEA0[];
extern char s_Eisenmaske_801DDEAC[];
extern char s_Topfhelm_801DDEB8[];
extern char s_Ritterin_801DDEC4[];
extern char s_Augenmaske_801DDED0[];
extern char s_Gitterhelm_801DDEDC[];
extern char s_Knollhelm_801DDEE8[];
extern char s_Schleife_801DDF00[];
extern char s_Wolfkopf_801DDF0C[];
extern char s_Otterschwanz_801DDF24[];
extern char s_Katzenbein_801DDF34[];
extern char s_Eulenkopf_801DDF40[];
extern char s_Ciuffo_ribelle_801DDF4C[];
extern char s_Naturale_801DDF5C[];
extern char s_Cappello_801DDF68[];
extern char s_Capelli_lunghi_801DDF74[];
extern char s_Capelli_corti_801DDF84[];
extern char s_Giacca_scura_801DDF94[];
extern char s_Pettinato_801DDFA4[];
extern char s_Elmo_di_corno_801DDFB0[];
extern char s_Elmo_d_acciaio_801DDFC0[];
extern char s_Pettinata_801DDFD0[];
extern char s_Elegante_801DDFDC[];
extern char s_Mascherina_801DDFE8[];
extern char s_Monocorno_801DDFF4[];
extern char s_Irregolare_801DE000[];
extern char s_Becco_lungo_801DE00C[];
extern char s_Mago_nero_801DE018[];
extern char s_Tulipano_801DE024[];
extern char s_Cucchiaio_801DE030[];
extern char s_Occhi_rapaci_801DE03C[];
extern char s_Procione_801DE04C[];
extern char s_Testa_di_gufo_801DE058[];
extern char s_Unicorne_801DE080[];
extern char s_Long_bec_801DE08C[];
extern char s_Mage_noir_801DE098[];
extern char s_Remolino_801DE0B0[];
extern char s_Cabello_Largo_801DE0BC[];
extern char s_Cabello_Corto_801DE0CC[];
extern char s_Chaqueta_Osc_801DE0DC[];
extern char s_Gorro_Blanco_801DE0EC[];
extern char s_Cabeza_Aire_801DE0FC[];
extern char s_Yelmo_Cuerno_801DE108[];
extern char s_Cabeza_Balde_801DE128[];
extern char s_Un_Cuerno_801DE148[];
extern char s_Zarandeado_801DE154[];
extern char s_Pico_Largo_801DE160[];
extern char s_Magia_Negra_801DE16C[];
extern char s_Cresta_Coraz_801DE178[];
extern char s_Cola_Mapache_801DE198[];
extern char s_Resist_fire_801DE1B4[];
extern char s_Resist_cold_801DE1C0[];
extern char s_Resist_lightning_801DE1CC[];
extern char s_Resist_slow_801DE1E0[];
extern char s_Resist_prlysis_801DE1EC[];
extern char s_Resist_poison_801DE1FC[];
extern char s_Resist_curses_801DE20C[];
extern char s_Resist_petrif_801DE21C[];
extern char s_Casting_time_801DE22C[];
extern char s_Charge_time_801DE23C[];
extern char s_Spell_duration_801DE248[];
extern char s_Resist_miasma_801DE258[];
extern char s_Long_spell_range_801DE268[];
extern char s_Long_focus_attks_801DE27C[];
extern char s_Focus_attacks_801DE290[];
extern char s_Spell_damage_801DE2A0[];
extern char s_Cannot_be_stunned_801DE2B0[];
extern char s_Feuer_Res_801DE2C4[];
extern char s_Eis_Resist_801DE2D0[];
extern char s_Blitz_Res_801DE2E0[];
extern char s_Gemach_R_801DE2EC[];
extern char s_Stopp_Res_801DE2F8[];
extern char s_Gift_Res_801DE304[];
extern char s_Fluch_Res_801DE310[];
extern char s_Stein_Res_801DE31C[];
extern char s_Z_laden_801DE328[];
extern char s_Sammeln_801DE334[];
extern char s_Z_Wirkungszeit_801DE340[];
extern char s_Miasma_R_plus_801DE354[];
extern char s_Z_Reichw_plus_801DE360[];
extern char s_SA_Reichw_plus_801DE370[];
extern char s_Spezialattacke_801DE380[];
extern char s_Zauber_Schaden_801DE390[];
extern char s_Standfest_801DE3A0[];
extern char s_Antifuoco_801DE3AC[];
extern char s_Antigelo_801DE3B8[];
extern char s_Antituono_801DE3C4[];
extern char s_Antislow_801DE3D0[];
extern char s_Antistop_801DE3DC[];
extern char s_Antiveleno_801DE3E8[];
extern char s_Antimalediz_801DE3F4[];
extern char s_Antipietrif_801DE404[];
extern char s_Carica_magia_801DE414[];
extern char s_Carica_attacchi_801DE424[];
extern char s_Durata_magie_801DE434[];
extern char s_Antimiasma_801DE444[];
extern char s_Portata_magie_801DE450[];
extern char s_Portata_Super_Att_801DE460[];
extern char s_Rigenerazione_801DE474[];
extern char s_Super_Attacchi_801DE484[];
extern char s_Danno_Magico_801DE494[];
extern char s_Antistordimento_801DE4A4[];
extern char s_Anti_Feu_801DE4B4[];
extern char s_Anti_Glace_801DE4C0[];
extern char s_Anti_Foudre_801DE4CC[];
extern char s_Anti_Somni_801DE4D8[];
extern char s_Anti_Stop_801DE4E4[];
extern char s_Anti_Poison_801DE4F0[];
extern char s_Tps_de_lancem_801DE51C[];
extern char s_Tps_de_charge_801DE52C[];
extern char s_Anti_Miasme_801DE548[];
extern char s_Super_attaques_801DE57C[];
extern char s_Anti_fuego_801DE5B0[];
extern char s_Anti_rayos_801DE5C8[];
extern char s_Anti_Freno_801DE5D4[];
extern char s_Anti_Paro_801DE5E0[];
extern char s_Anti_veneno_801DE5EC[];
extern char s_Anti_maldic_801DE5F8[];
extern char s_Anti_petrif_801DE608[];
extern char s_Tiempo_lanzam_801DE618[];
extern char s_Tiempo_carga_801DE628[];
extern char s_Durac_hechiz_801DE638[];
extern char s_Anti_miasma_801DE648[];
extern char s_Alcance_hechiz_801DE654[];
extern char s_Alc_superataq_801DE664[];
extern char s_Revitalia_801DE674[];
extern char s_Superataque_801DE680[];
extern char s_No_se_aturde_801DE69C[];
extern char lbl_801DD754[];
extern char lbl_801DDE90[];
extern char lbl_801DDEF4[];
extern char lbl_801DDF18[];
extern char lbl_801DE068[];
extern char lbl_801DE074[];
extern char lbl_801DE0A4[];
extern char lbl_801DE118[];
extern char lbl_801DE138[];
extern char lbl_801DE188[];
extern char lbl_801DE1A8[];
extern char lbl_801DE4FC[];
extern char lbl_801DE50C[];
extern char lbl_801DE53C[];
extern char lbl_801DE554[];
extern char lbl_801DE568[];
extern char lbl_801DE58C[];
extern char lbl_801DE59C[];
extern char lbl_801DE5BC[];
extern char lbl_801DE68C[];
extern char lbl_803321BC[], lbl_803321C0[], lbl_803321C4[], lbl_803321CC[];
extern char lbl_803321D0[], lbl_803321D8[], lbl_803321E0[], lbl_803321E8[];
extern char lbl_803321F0[], lbl_803321F8[], lbl_80332200[], lbl_80332208[];
extern char lbl_8033220C[], lbl_80332214[], lbl_8033221C[], lbl_80332224[];
extern char lbl_8033222C[], lbl_80332230[], lbl_80332234[], lbl_80332238[];
extern char lbl_80332240[], lbl_80332248[], lbl_80332250[], lbl_80332258[];
extern char lbl_80332260[], lbl_80332264[], lbl_8033226C[], lbl_80332274[];
extern char lbl_8033227C[], lbl_80332284[], lbl_8033228C[], lbl_80332294[];
extern char lbl_8033229C[], lbl_803322A4[], lbl_803322AC[], lbl_803322B4[];
extern char lbl_803322B8[], lbl_803322C0[], lbl_803322C4[], lbl_803322CC[];
extern char lbl_803322D4[], lbl_803322DC[], lbl_803322E4[], lbl_803322E8[];
extern char lbl_803322F0[], lbl_803322F8[], lbl_80332300[], lbl_80332308[];
extern char lbl_8033230C[], lbl_80332314[], lbl_8033231C[], lbl_80332324[];
extern char lbl_8033232C[], lbl_80332330[], lbl_80332338[], lbl_80332340[];
extern char lbl_80332348[], lbl_80332350[], lbl_80332358[], lbl_80332360[];
extern char lbl_80332368[], lbl_80332370[], lbl_80332378[], lbl_80332380[];
extern char lbl_80332384[], lbl_8033238C[], lbl_80332394[], lbl_8033239C[];
extern char lbl_803323A4[], lbl_803323AC[], lbl_803323B4[], lbl_803323BC[];
extern char lbl_803323C4[], lbl_803323CC[], lbl_803323D4[], lbl_803323DC[];
extern char lbl_803323E4[], lbl_803323EC[], lbl_803323F4[], lbl_803323FC[];
extern char lbl_80332404[], lbl_80332408[], lbl_8033240C[], lbl_80332414[];
extern char lbl_8033241C[], lbl_80332424[], lbl_8033242C[], lbl_80332434[];
extern char lbl_8033243C[], lbl_80332444[], lbl_8033244C[], lbl_80332454[];
extern char lbl_8033245C[], lbl_80332464[], lbl_8033246C[], lbl_80332474[];
extern char lbl_8033247C[], lbl_80332484[], lbl_8033248C[], lbl_80332494[];
extern char lbl_8033249C[], lbl_803324A4[], lbl_803324AC[], lbl_803324B4[];
extern char lbl_803324BC[], lbl_803324C4[], lbl_803324C8[], lbl_803324D0[];
extern char lbl_803324D8[], lbl_803324E0[], lbl_803324E8[], lbl_803324F0[];
extern char lbl_803324F8[], lbl_80332500[], lbl_80332508[], lbl_80332510[];
extern char lbl_80332518[], lbl_80332520[], lbl_80332528[], lbl_80332530[];
extern char lbl_80332534[], lbl_8033253C[], lbl_80332544[], lbl_8033254C[];
extern char lbl_80332554[], lbl_8033255C[], lbl_80332564[], lbl_8033256C[];
extern char s_Strength_801DD814[], s_Memories_801DD820[], s_Send_item_801DD82C[], s_Send_gil_801DD838[];
extern char s_Send_nothing_801DD844[], s_Proceed_801DD854[], s_Take_out_801DD860[], s_the_reply_801DD86C[];
extern char s_Include_801DD878[], s_Family_Trade_801DD884[], s_Command_List_801DD894[], s_Artefacts_801DD8A4[];
extern char s_Treasures_801DD8B0[], s_Favourites_801DD8BC[], s_Abbrechen_801DD8C8[], s_Erinnerungen_801DD8D4[];
extern char s_Angreifen_801DD8E4[], s_Verteidigen_801DD8F0[], s_Kombinieren_801DD8FC[], s_Benutzen_801DD914[];
extern char s_Wegwerfen_801DD920[], s_Weiblich_801DD944[], s_Alle_Rassen_801DD950[], s_Schwester_801DD95C[];
extern char s_kl_Bruder_801DD968[], s_kl_Schwester_801DD974[], s_Liste_erhaltener_Briefe_801DD984[], s_herausholen_801DD9D0[];
extern char s_die_Antwort_801DD9E0[], s_schicken_801DD9F0[], s_Geschlecht_801DDA14[], s_Elterlicher_Beruf_801DDA20[];
extern char s_Kommandoliste_801DDA34[], s_Artefakte_801DDA5C[], s_Geborgtes_801DDA68[], s_Geschmack_801DDA74[];
extern char s_Distruggi_801DDA80[], s_Fratello_801DDA8C[], s_Invia_oggetto_801DDA98[], s_Invia_guil_801DDAA8[];
extern char s_Non_inviare_nulla_801DDAB4[], s_Vuoi_procedere_801DDAC8[], s_Vuoi_prendere_801DDAD8[], s_Vuoi_rispondere_a_801DDAE8[];
extern char s_Allegato_801DDAFC[], s_Conferma_801DDB08[], s_Mestiere_801DDB14[], s_Lista_Comandi_801DDB20[];
extern char s_Equipaggiamento_801DDB30[], s_Manufatti_801DDB40[], s_Preferiti_801DDB4C[], s_Famiglia_801DDB58[];
extern char s_Souvenirs_801DDB70[], s_Attaquer_801DDB7C[], s_Fusionner_801DDB94[], s_Utiliser_801DDBA0[];
extern char s_Masculin_801DDBB8[], s_Envoyer_un_objet_801DDBC4[], s_Envoyer_des_gils_801DDBD8[], s_Ne_rien_envoyer_801DDBEC[];
extern char s_Continuer_801DDBFC[], s_Prendre_801DDC08[], s_Joindre_801DDC2C[], s_Confirmer_801DDC38[];
extern char s_Commandes_801DDC44[], s_Cancelar_801DDC5C[], s_Memorias_801DDC68[], s_Defender_801DDC74[];
extern char s_Fusionar_801DDC80[], s_Utilizar_801DDC8C[], s_Descartar_801DDC98[], s_Destruir_801DDCA4[];
extern char s_Enviar_objeto_801DDCB0[], s_Enviar_guiles_801DDCC0[], s_No_enviar_nada_801DDCD0[], s_Enviar_la_respuesta_a_801DDCF8[];
extern char s_Incluir_801DDD10[], s_Confirmar_801DDD1C[], s_Oficio_familiar_801DDD28[], s_Comandos_801DDD3C[];
extern char s_Artefactos_801DDD48[], s_Favoritos_801DDD54[];
extern char lbl_801DD908[], lbl_801DD92C[], lbl_801DD938[], lbl_801DD99C[], lbl_801DD9B0[], lbl_801DD9C0[];
extern char lbl_801DD9FC[], lbl_801DDA08[], lbl_801DDA44[], lbl_801DDA50[], lbl_801DDB64[], lbl_801DDB88[];
extern char lbl_801DDBAC[], lbl_801DDC14[], lbl_801DDC20[], lbl_801DDC50[], lbl_801DDCE0[], lbl_801DDCEC[];
}
extern "C" char* PTR_s_Clavat_802140f0[] = {
    lbl_803320D8, lbl_803320E0, lbl_803320E8, lbl_803320F0,
};
extern "C" char* PTR_s_Clavat_80214100[] = {
    lbl_803320D8, lbl_803320E0, lbl_803320E8, lbl_803320F0,
};
extern "C" char* PTR_s_Clavat_80214110[] = {
    lbl_803320D8, lbl_803320F8, lbl_803320E8, lbl_80332100,
};
extern "C" char* PTR_s_Clavat_80214120[] = {
    lbl_803320D8, lbl_803320E0, lbl_803320E8, lbl_803320F0,
};
extern "C" char* PTR_s_Clavate[] = {
    lbl_80332108, lbl_80332110, lbl_80332118, lbl_80332120,
};
extern "C" char* PTR_s_Blacksmith[] = {
    s_Blacksmith_801DD718, lbl_80332128, lbl_80332130, lbl_80332138,
    lbl_80332140, s_Fisherman_801DD724, s_Merchant_801DD730, s_Alchemist_801DD73C,
};
extern "C" char* PTR_s_Schmied[] = {
    lbl_80332148, s_Schneider_801DD748, lbl_80332150, lbl_801DD754,
    lbl_80332158, lbl_80332160, lbl_80332168, s_Alchemist_801DD73C,
};
extern "C" char* PTR_s_Fabbri[] = {
    lbl_80332170, lbl_80332178, s_Agricoltori_801DD760, s_Allevatori_801DD76C,
    lbl_80332180, s_Pescatori_801DD778, s_Mercanti_801DD784, s_Alchimisti_801DD790,
};
extern "C" char* PTR_s_Forgeron[] = {
    s_Forgeron_801DD79C, s_Tailleur_801DD7A8, lbl_80332188, lbl_80332190,
    lbl_80332198, lbl_803321A0, s_Marchand_801DD7B4, s_Alchimiste_801DD7C0,
};
extern "C" char* PTR_s_Herrero[] = {
    lbl_803321A8, lbl_803321B0, s_Campesino_801DD7CC, s_Granjero_801DD7D8,
    s_Molinero_801DD7E4, s_Pescador_801DD7F0, s_Comerciante_801DD7FC, s_Alquimista_801DD808,
};
extern "C" char* gSingMenuTextTableEn[] = {
    lbl_803321B8, lbl_803321BC, lbl_803321C0, lbl_803321C4,
    lbl_803321CC, s_Strength_801DD814, lbl_803321D0, lbl_803321D8,
    s_Memories_801DD820, lbl_803321E0, lbl_803321E8, lbl_803321F0,
    lbl_803321F8, lbl_80332200, lbl_80332208, lbl_8033220C,
    lbl_80332214, lbl_8033221C, lbl_80332224, lbl_8033222C,
    lbl_80332230, lbl_80332234, lbl_80332238, lbl_80332240,
    lbl_80332248, lbl_80332250, lbl_80332248, lbl_80332250,
    lbl_803321B8, lbl_80332258, s_Send_item_801DD82C, s_Send_gil_801DD838,
    s_Send_nothing_801DD844, s_Proceed_801DD854, s_Take_out_801DD860, lbl_80332260,
    lbl_80332260, lbl_80332264, s_the_reply_801DD86C, lbl_803321B8,
    s_Include_801DD878, lbl_8033226C, lbl_80332274, lbl_8033227C,
    lbl_80332284, s_Family_Trade_801DD884, s_Command_List_801DD894, lbl_8033228C,
    lbl_80332294, s_Artefacts_801DD8A4, s_Treasures_801DD8B0, lbl_8033229C,
    s_Favourites_801DD8BC, lbl_803322A4, lbl_80332258, lbl_803322AC,
};
extern "C" char* gSingMenuTextTableDe[] = {
    lbl_803321B8, lbl_803322B4, lbl_803322B8, s_Abbrechen_801DD8C8,
    lbl_803322C0, lbl_803322C4, lbl_803322CC, lbl_803322D4,
    s_Erinnerungen_801DD8D4, s_Angreifen_801DD8E4, s_Verteidigen_801DD8F0, lbl_803322DC,
    s_Kombinieren_801DD8FC, lbl_801DD908, s_Benutzen_801DD914, s_Wegwerfen_801DD920,
    lbl_801DD92C, lbl_801DD938, s_Weiblich_801DD944, s_Alle_Rassen_801DD950,
    lbl_80332230, lbl_803322E4, lbl_803322E8, lbl_803322F0,
    lbl_803322F8, s_Schwester_801DD95C, s_kl_Bruder_801DD968, s_kl_Schwester_801DD974,
    lbl_803321B8, s_Liste_erhaltener_Briefe_801DD984, lbl_801DD99C, lbl_801DD9B0,
    lbl_801DD9C0, lbl_80332300, s_herausholen_801DD9D0, lbl_80332308,
    lbl_80332260, lbl_803321B8, s_die_Antwort_801DD9E0, s_schicken_801DD9F0,
    lbl_801DD9FC, lbl_801DDA08, lbl_80332274, s_Geschlecht_801DDA14,
    lbl_8033230C, s_Elterlicher_Beruf_801DDA20, s_Kommandoliste_801DDA34, lbl_801DDA44,
    lbl_801DDA50, s_Artefakte_801DDA5C, s_Geborgtes_801DDA68, lbl_80332314,
    s_Geschmack_801DDA74, lbl_8033231C, lbl_80332324, s_Abbrechen_801DD8C8,
};
extern "C" char* gSingMenuTextTableIt[] = {
    lbl_803321B8, lbl_8033232C, lbl_803321C0, lbl_80332330,
    lbl_80332338, lbl_80332340, lbl_80332348, lbl_80332350,
    lbl_80332358, lbl_80332360, lbl_80332348, lbl_80332368,
    lbl_80332370, lbl_80332378, lbl_80332380, lbl_80332384,
    s_Distruggi_801DDA80, lbl_8033238C, lbl_80332394, lbl_8033239C,
    lbl_80332230, lbl_80332234, lbl_803323A4, lbl_803323AC,
    s_Fratello_801DDA8C, lbl_803323B4, s_Fratello_801DDA8C, lbl_803323B4,
    lbl_803321B8, lbl_803323BC, s_Invia_oggetto_801DDA98, s_Invia_guil_801DDAA8,
    s_Non_inviare_nulla_801DDAB4, s_Vuoi_procedere_801DDAC8, s_Vuoi_prendere_801DDAD8, lbl_80332260,
    lbl_80332260, lbl_803323C4, s_Vuoi_rispondere_a_801DDAE8, lbl_803321B8,
    s_Allegato_801DDAFC, s_Conferma_801DDB08, lbl_803323CC, lbl_803323D4,
    lbl_803323DC, s_Mestiere_801DDB14, s_Lista_Comandi_801DDB20, lbl_803323E4,
    s_Equipaggiamento_801DDB30, s_Manufatti_801DDB40, lbl_803323EC, lbl_803323F4,
    s_Preferiti_801DDB4C, s_Famiglia_801DDB58, lbl_803323BC, lbl_803323FC,
};
extern "C" char* gSingMenuTextTableFr[] = {
    lbl_803321B8, lbl_80332404, lbl_80332408, lbl_8033240C,
    lbl_80332414, lbl_8033241C, lbl_801DDB64, lbl_803322D4,
    s_Souvenirs_801DDB70, s_Attaquer_801DDB7C, lbl_801DDB88, lbl_80332424,
    s_Fusionner_801DDB94, lbl_8033242C, s_Utiliser_801DDBA0, lbl_80332434,
    lbl_801DDBAC, s_Masculin_801DDBB8, lbl_8033243C, lbl_80332444,
    lbl_80332230, lbl_80332234, lbl_8033244C, lbl_80332454,
    lbl_8033245C, lbl_80332464, lbl_8033245C, lbl_80332464,
    lbl_803321B8, lbl_8033246C, s_Envoyer_un_objet_801DDBC4, s_Envoyer_des_gils_801DDBD8,
    s_Ne_rien_envoyer_801DDBEC, s_Continuer_801DDBFC, s_Prendre_801DDC08, lbl_80332260,
    lbl_80332260, lbl_801DDC14, lbl_801DDC20, lbl_803321B8,
    s_Joindre_801DDC2C, s_Confirmer_801DDC38, lbl_80332474, lbl_8033247C,
    lbl_80332484, lbl_8033248C, s_Commandes_801DDC44, lbl_80332494,
    lbl_8033249C, s_Artefacts_801DD8A4, lbl_803324A4, lbl_803324AC,
    lbl_801DDC50, lbl_803324B4, lbl_8033246C, lbl_803324BC,
};
extern "C" char* gSingMenuTextTableEs[] = {
    lbl_803321B8, lbl_803324C4, lbl_803321C0, s_Cancelar_801DDC5C,
    lbl_803324C8, lbl_803324D0, lbl_803324D8, lbl_80332350,
    s_Memorias_801DDC68, lbl_803324E0, s_Defender_801DDC74, lbl_803324E8,
    s_Fusionar_801DDC80, lbl_803324F0, s_Utilizar_801DDC8C, s_Descartar_801DDC98,
    s_Destruir_801DDCA4, lbl_803324F8, lbl_80332500, lbl_80332508,
    lbl_80332510, lbl_80332234, lbl_803323A4, lbl_803323AC,
    lbl_80332518, lbl_80332520, lbl_80332518, lbl_80332520,
    lbl_803321B8, lbl_80332528, s_Enviar_objeto_801DDCB0, s_Enviar_guiles_801DDCC0,
    s_No_enviar_nada_801DDCD0, lbl_801DDCE0, lbl_801DDCEC, lbl_80332260,
    lbl_80332260, lbl_80332530, s_Enviar_la_respuesta_a_801DDCF8, lbl_803321B8,
    s_Incluir_801DDD10, s_Confirmar_801DDD1C, lbl_80332534, lbl_8033253C,
    lbl_80332484, s_Oficio_familiar_801DDD28, s_Comandos_801DDD3C, lbl_80332544,
    lbl_8033254C, s_Artefactos_801DDD48, lbl_80332554, lbl_8033255C,
    s_Favoritos_801DDD54, lbl_80332564, lbl_80332528, lbl_8033256C,
};
extern "C" char* PTR_s_Cowlick[] = {
    lbl_80332574, lbl_8033257C, s_Headband_801DDD60, lbl_80332584,
    s_Long_Hair_801DDD6C, s_Short_Hair_801DDD78, s_Dark_Coat_801DDD84, s_White_Cap_801DDD90,
    s_Bare_Head_801DDD9C, s_Horned_Helm_801DDDA8, s_Steel_Visor_801DDDB4, s_Bucket_Head_801DDDC0,
    s_Bare_Head_801DDD9C, s_Blue_Armor_801DDDCC, lbl_80332588, s_Red_Mask_801DDDD8,
    s_One_Horn_801DDDE4, lbl_80332590, s_Long_Beak_801DDDF0, s_Black_Mage_801DDDFC,
    lbl_80332598, lbl_803325A0, lbl_803325A8, s_Heart_Top_801DDE08,
    lbl_803325B0, s_Shark_Eyes_801DDE14, s_Bandanna_801DDE20, s_Raccoon_Tail_801DDE2C,
    lbl_803325B0, s_Raccoon_Tail_801DDE2C, s_Shark_Eyes_801DDE14, s_Owl_Head_801DDE3C,
};
extern "C" char* PTR_s_Spitzschopf[] = {
    s_Spitzschopf_801DDE48, lbl_803325B8, s_Stirnband_801DDE54, s_Kopftuch_801DDE60,
    s_lange_Haare_801DDE6C, s_kurze_Haare_801DDE78, s_mittellang_801DDE84, lbl_801DDE90,
    lbl_803325C0, s_Spitzhelm_801DDEA0, s_Eisenmaske_801DDEAC, s_Topfhelm_801DDEB8,
    lbl_803325C0, s_Ritterin_801DDEC4, lbl_803325C8, s_Augenmaske_801DDED0,
    lbl_803325D0, s_Gitterhelm_801DDEDC, s_Knollhelm_801DDEE8, lbl_801DDEF4,
    lbl_803325D8, lbl_803325E0, lbl_803325E8, s_Schleife_801DDF00,
    s_Wolfkopf_801DDF0C, lbl_803325F0, lbl_801DDF18, s_Otterschwanz_801DDF24,
    s_Katzenbein_801DDF34, s_Otterschwanz_801DDF24, lbl_803325F0, s_Eulenkopf_801DDF40,
};
extern "C" char* PTR_s_Ciuffo_ribelle[] = {
    s_Ciuffo_ribelle_801DDF4C, s_Naturale_801DDF5C, lbl_803325F8, s_Cappello_801DDF68,
    s_Capelli_lunghi_801DDF74, s_Capelli_corti_801DDF84, s_Giacca_scura_801DDF94, s_Cappello_801DDF68,
    s_Pettinato_801DDFA4, s_Elmo_di_corno_801DDFB0, s_Elmo_d_acciaio_801DDFC0, lbl_80332600,
    s_Pettinata_801DDFD0, lbl_80332608, s_Elegante_801DDFDC, s_Mascherina_801DDFE8,
    s_Monocorno_801DDFF4, s_Irregolare_801DE000, s_Becco_lungo_801DE00C, s_Mago_nero_801DE018,
    lbl_8033260C, s_Tulipano_801DE024, s_Cucchiaio_801DE030, lbl_80332614,
    lbl_8033261C, s_Occhi_rapaci_801DE03C, lbl_80332624, s_Procione_801DE04C,
    lbl_8033262C, s_Procione_801DE04C, s_Occhi_rapaci_801DE03C, s_Testa_di_gufo_801DE058,
};
extern "C" char* gSingMenuHairTableFr[] = {
    lbl_80332634, lbl_80332638, lbl_80332640, lbl_80332648,
    lbl_80332650, lbl_80332658, lbl_80332660, lbl_80332648,
    lbl_801DE068, lbl_80332668, lbl_80332670, lbl_80332678,
    lbl_801DE068, lbl_80332678, lbl_801DE074, lbl_80332680,
    s_Unicorne_801DE080, lbl_80332688, s_Long_bec_801DE08C, s_Mage_noir_801DE098,
    lbl_8033260C, lbl_80332690, lbl_801DE0A4, lbl_80332698,
    lbl_803326A0, lbl_803326A8, lbl_80332624, lbl_803326B0,
    lbl_803326B8, lbl_803326B0, lbl_803326A8, lbl_803326C0,
};
extern "C" char* PTR_s_Remolino[] = {
    s_Remolino_801DE0B0, lbl_8033257C, lbl_803326C8, lbl_803326D0,
    s_Cabello_Largo_801DE0BC, s_Cabello_Corto_801DE0CC, s_Chaqueta_Osc_801DE0DC, s_Gorro_Blanco_801DE0EC,
    s_Cabeza_Aire_801DE0FC, s_Yelmo_Cuerno_801DE108, lbl_801DE118, s_Cabeza_Balde_801DE128,
    s_Cabeza_Aire_801DE0FC, lbl_803326D8, s_Elegante_801DDFDC, lbl_801DE138,
    s_Un_Cuerno_801DE148, s_Zarandeado_801DE154, s_Pico_Largo_801DE160, s_Magia_Negra_801DE16C,
    lbl_803326E0, lbl_803326E8, lbl_803326F0, s_Cresta_Coraz_801DE178,
    lbl_803326F8, lbl_801DE188, lbl_80332624, s_Cola_Mapache_801DE198,
    lbl_803326F8, s_Cola_Mapache_801DE198, lbl_801DE188, lbl_801DE1A8,
};
extern "C" char* gSingMenuAttrTableEn[] = {
    lbl_803321B8, s_Resist_fire_801DE1B4, s_Resist_cold_801DE1C0, s_Resist_lightning_801DE1CC,
    s_Resist_slow_801DE1E0, s_Resist_prlysis_801DE1EC, s_Resist_poison_801DE1FC, s_Resist_curses_801DE20C,
    s_Resist_petrif_801DE21C, s_Casting_time_801DE22C, s_Charge_time_801DE23C, s_Spell_duration_801DE248,
    s_Spell_duration_801DE248, s_Resist_miasma_801DE258, s_Long_spell_range_801DE268, s_Long_focus_attks_801DE27C,
    lbl_80332700, s_Focus_attacks_801DE290, s_Spell_damage_801DE2A0, s_Cannot_be_stunned_801DE2B0,
};
extern "C" char* gSingMenuAttrTableDe[] = {
    lbl_803321B8, s_Feuer_Res_801DE2C4, s_Eis_Resist_801DE2D0, s_Blitz_Res_801DE2E0,
    s_Gemach_R_801DE2EC, s_Stopp_Res_801DE2F8, s_Gift_Res_801DE304, s_Fluch_Res_801DE310,
    s_Stein_Res_801DE31C, s_Z_laden_801DE328, s_Sammeln_801DE334, s_Z_Wirkungszeit_801DE340,
    s_Z_Wirkungszeit_801DE340, s_Miasma_R_plus_801DE354, s_Z_Reichw_plus_801DE360, s_SA_Reichw_plus_801DE370,
    lbl_80332708, s_Spezialattacke_801DE380, s_Zauber_Schaden_801DE390, s_Standfest_801DE3A0,
};
extern "C" char* gSingMenuAttrTableIt[] = {
    lbl_803321B8, s_Antifuoco_801DE3AC, s_Antigelo_801DE3B8, s_Antituono_801DE3C4,
    s_Antislow_801DE3D0, s_Antistop_801DE3DC, s_Antiveleno_801DE3E8, s_Antimalediz_801DE3F4,
    s_Antipietrif_801DE404, s_Carica_magia_801DE414, s_Carica_attacchi_801DE424, s_Durata_magie_801DE434,
    s_Durata_magie_801DE434, s_Antimiasma_801DE444, s_Portata_magie_801DE450, s_Portata_Super_Att_801DE460,
    s_Rigenerazione_801DE474, s_Super_Attacchi_801DE484, s_Danno_Magico_801DE494, s_Antistordimento_801DE4A4,
};
extern "C" char* gSingMenuAttrTableFr[] = {
    lbl_803321B8, s_Anti_Feu_801DE4B4, s_Anti_Glace_801DE4C0, s_Anti_Foudre_801DE4CC,
    s_Anti_Somni_801DE4D8, s_Anti_Stop_801DE4E4, s_Anti_Poison_801DE4F0, lbl_801DE4FC,
    lbl_801DE50C, s_Tps_de_lancem_801DE51C, s_Tps_de_charge_801DE52C, lbl_801DE53C,
    lbl_801DE53C, s_Anti_Miasme_801DE548, lbl_801DE554, lbl_801DE568,
    lbl_80332710, s_Super_attaques_801DE57C, lbl_801DE58C, lbl_801DE59C,
};
extern "C" char* gSingMenuAttrTableEs[] = {
    lbl_803321B8, s_Anti_fuego_801DE5B0, lbl_801DE5BC, s_Anti_rayos_801DE5C8,
    s_Anti_Freno_801DE5D4, s_Anti_Paro_801DE5E0, s_Anti_veneno_801DE5EC, s_Anti_maldic_801DE5F8,
    s_Anti_petrif_801DE608, s_Tiempo_lanzam_801DE618, s_Tiempo_carga_801DE628, s_Durac_hechiz_801DE638,
    s_Durac_hechiz_801DE638, s_Anti_miasma_801DE648, s_Alcance_hechiz_801DE654, s_Alc_superataq_801DE664,
    s_Revitalia_801DE674, s_Superataque_801DE680, lbl_801DE68C, s_No_se_aturde_801DE69C,
};
extern "C" {
char s_DynamicMessStr[0x404];
}

extern "C" unsigned int CmdOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void CmdDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int ItemOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int ItemCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int ItemClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void ItemDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int EquipOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int EquipCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int EquipClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void EquipDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int ArtiOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int ArtiCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int ArtiClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void ArtiDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int TmpArtiOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int TmpArtiCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int TmpArtiClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void TmpArtiDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int MoneyOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int MoneyCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int MoneyClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void MoneyDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int FavoOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int FavoCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int FavoClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void FavoDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CompaOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CompaCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CompaClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void CompaDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int LetterOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int LetterCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int LetterClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void LetterDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int MLstOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int MLstCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int MLstClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void MLstDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" void CalcHeart__8CMesMenuFv(void*);

extern float FLOAT_8033292c;
extern float FLOAT_80332930;
extern float FLOAT_80332928;
extern float FLOAT_80332924;
extern float FLOAT_80332920;
extern float FLOAT_8033291c;
extern float FLOAT_80332918;
extern float FLOAT_80332934;
extern float FLOAT_80332940;
extern float FLOAT_80332948;
extern float FLOAT_8033294c;
extern float FLOAT_80332950;
extern float FLOAT_80332954;
extern float FLOAT_80332960;
extern float FLOAT_80332970;
extern float FLOAT_803329a4;
extern float FLOAT_803329a8;
extern float FLOAT_803329ac;
extern float FLOAT_803329b0;
extern float FLOAT_803329b4;
extern float FLOAT_803329bc;
extern float FLOAT_803329b8;
extern float FLOAT_803329c0;
extern float FLOAT_803329c4;
extern float FLOAT_803329c8;
extern float FLOAT_803329cc;
CFile::CHandle* gSingMenuAsyncFileHandle;
int gSingMenuAsyncLoadCompleted;
int gSingMenuHasScriptFoodBase;
int gSingMenuForcedSelection;
extern int DAT_80214b3c[];
extern float DAT_801dd708[];
extern float DAT_801dd6f8[];
float FLOAT_8032ea78 = 1.0f;
extern float FLOAT_803329d0;
extern float FLOAT_803329d4;
extern float FLOAT_803329d8;
extern float FLOAT_803329dc;
extern float FLOAT_803329e8;
extern float FLOAT_803329ec;
extern float FLOAT_803329f0;
extern float FLOAT_803329f4;
extern float FLOAT_803329f8;
extern float FLOAT_80332994;
extern float FLOAT_80332990;
extern float FLOAT_80332998;
extern float FLOAT_8033299c;
extern float FLOAT_803329a0;
extern float FLOAT_803329fc;
extern float FLOAT_80332960;
extern float FLOAT_80332a00;
extern float FLOAT_80332a04;
extern float FLOAT_80332a08;
extern float FLOAT_80332a0c;
extern float FLOAT_80332a10;
extern float FLOAT_80332a18;
extern float FLOAT_80332a1c;
extern float FLOAT_80332a2c;
extern float FLOAT_80332a48;
extern double DOUBLE_80332938;
extern double DOUBLE_80332968;
extern double DOUBLE_80332978;
extern double DOUBLE_80332980;
extern double DOUBLE_80332988;
extern double DOUBLE_80332a30;
extern double DOUBLE_80332a38;
extern double DOUBLE_80332a40;

static inline const char* GetSingWinMessage(int staticText, const char* dynamicText, int useDynamic)
{
    if (useDynamic != 0) {
        return dynamicText;
    }

    u8 languageId = Game.m_gameWork.m_languageId;
    if (languageId == 3) {
        return gSingMenuTextTableIt[staticText];
    }
    if (languageId >= 3) {
        if (languageId == 5) {
            return gSingMenuTextTableEs[staticText];
        }
        if (languageId >= 5) {
            return gSingMenuTextTableEn[staticText];
        }
        return gSingMenuTextTableFr[staticText];
    }
    if (languageId == 1) {
        return gSingMenuTextTableEn[staticText];
    }
    if (languageId >= 1) {
        return gSingMenuTextTableDe[staticText];
    }
    return gSingMenuTextTableEn[staticText];
}

static inline double SingWinUIntToDouble(unsigned int value)
{
    unsigned long long bits = 0x4330000000000000ULL | static_cast<unsigned long long>(value ^ 0x80000000U);
    return static_cast<double>(bits) - DOUBLE_80332938;
}

/*
 * --INFO--
 * PAL Address: 0x8014a7cc
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::createSingleMenu()
{
    u8* self = reinterpret_cast<u8*>(this);

    *reinterpret_cast<s16*>(self + 0x866) = 0;
    gSingMenuAsyncLoadCompleted = 0;
    if (Game.m_gameWork.m_menuStageMode == 0) {
        if (self[0x859] != 0) {
            *reinterpret_cast<int*>(self + 0xF0) = 0;

            void* font = *reinterpret_cast<void**>(self + 0x108);
            if (font != 0) {
                int* raw = reinterpret_cast<int*>(font);
                int refCount = raw[1] - 1;
                raw[1] = refCount;
                if (refCount == 0) {
                    reinterpret_cast<void (*)(void*, int)>(*reinterpret_cast<int*>(raw[0] + 8))(font, 1);
                }
                *reinterpret_cast<void**>(self + 0x108) = 0;
            }

            self[0x859] = 0;
            self[0x85A] = 0;
        }
    } else {
        if (self[0x859] == 0) {
            *reinterpret_cast<int*>(self + 0xF0) = *reinterpret_cast<int*>(reinterpret_cast<u8*>(&CharaPcs) + 0x212);
            self[0x859] = 1;
        }

        char path[128];
        char* language = GetLangString__5CGameFv(&Game);
        sprintf(path, s_dvd__smenu_subfont_fnt_801de8f8, language);
        loadFont__8CMenuPcsFiPcii(this, 1, path, 4, -1);

        self[0x85A] = 0;
        gSingMenuForcedSelection = -1;
        gSingMenuAsyncFileHandle = 0;

        if (Game.m_gameWork.m_menuStageMode != 0) {
            loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii(
                this, PTR_s_solo2_80214a8c, 4, 1, &DAT_80214ab0, 0x20, 0xD, 1);
            *reinterpret_cast<int*>(self + 0x814) = 0;
            *reinterpret_cast<int*>(self + 0x850) = 0;
            *reinterpret_cast<int*>(self + 0x82C) = 0;
            *reinterpret_cast<int*>(self + 0x848) = 0;
            *reinterpret_cast<void**>(self + 0x868) = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8014A67C
 * PAL Size: 336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::destroySingleMenu()
{
    u8* self = reinterpret_cast<u8*>(this);

    if (gSingMenuAsyncFileHandle != 0) {
        File.Close(gSingMenuAsyncFileHandle);
        gSingMenuAsyncFileHandle = 0;
    }

    void* font = *reinterpret_cast<void**>(self + 0x108);
    if (font != 0) {
        int* raw = reinterpret_cast<int*>(font);
        int refCount = raw[1] - 1;
        raw[1] = refCount;
        if (refCount == 0) {
            reinterpret_cast<void (*)(void*, int)>(*reinterpret_cast<int*>(raw[0] + 8))(font, 1);
        }
        *reinterpret_cast<void**>(self + 0x108) = 0;
    }

    freeTexture__8CMenuPcsFiiii(this, 4, 1, 0x20, 0xD);
    freeTexture__8CMenuPcsFiiii(this, 5, 2, 0x2D, 0x33);

    *reinterpret_cast<int*>(self + 0xF0) = 0;
    self[0x85A] = 0;
    self[0x859] = 0;
    gSingMenuForcedSelection = -1;

    void* ptr = *reinterpret_cast<void**>(self + 0x814);
    if (ptr != 0) {
        __dla__FPv(ptr);
        *reinterpret_cast<void**>(self + 0x814) = 0;
    }

    ptr = *reinterpret_cast<void**>(self + 0x850);
    if (ptr != 0) {
        __dl__FPv(ptr);
        *reinterpret_cast<void**>(self + 0x850) = 0;
    }

    ptr = *reinterpret_cast<void**>(self + 0x82C);
    if (ptr != 0) {
        __dl__FPv(ptr);
        *reinterpret_cast<void**>(self + 0x82C) = 0;
    }

    ptr = *reinterpret_cast<void**>(self + 0x848);
    if (ptr != 0) {
        __dl__FPv(ptr);
        *reinterpret_cast<void**>(self + 0x848) = 0;
    }

    _GXColor clearColor = *reinterpret_cast<_GXColor*>(&DAT_802381a7);
    GXSetCopyClear(clearColor, 0xFFFFFF);
}

/*
 * --INFO--
 * PAL Address: 0x8014a214
 * PAL Size: 1128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingMenuInit()
{
    u8* self = reinterpret_cast<u8*>(this);

    _WaitDrawDone__8CGraphicFPci(&Graphic, s_singmenu_cpp_801de8d4, 0x5C2);
    DestroyTempBuffer__8CGraphicFv(&Graphic);

    *reinterpret_cast<void**>(self + 0xF4) = *reinterpret_cast<void**>(reinterpret_cast<u8*>(&Graphic) + 8);
    memset(self + 0x85C, 0, 8);
    *reinterpret_cast<void**>(self + 0x774) = 0;

    CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
    if (Game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
    }

    CCharaPcs::CHandle* handle =
        static_cast<CCharaPcs::CHandle*>(__nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci(
            0x194, stage, s_singmenu_cpp_801de8d4, 0x5CD));
    if (handle != 0) {
        handle = __ct__Q29CCharaPcs7CHandleFv(handle);
    }
    *reinterpret_cast<CCharaPcs::CHandle**>(self + 0x774) = handle;

    handle->Add();
    int modelNo = GetModelNo__8CMenuPcsFiii(
        this,
        static_cast<int>(*reinterpret_cast<u16*>(Game.m_scriptFoodBase[0] + 0x3E0)),
        static_cast<int>(*reinterpret_cast<u16*>(Game.m_scriptFoodBase[0] + 0x3E4)),
        static_cast<int>(*reinterpret_cast<u16*>(Game.m_scriptFoodBase[0] + 0x3E2)));
    handle->LoadModel(0, static_cast<unsigned long>(modelNo), 0, 0, -1, 0, 0);
    handle->m_flags |= 0x300141;
    handle->LoadAnim(s_stand_80332a24, 0, 1, 0, (handle->m_charaNo / 100) * 100, -1, 0);
    handle->SetAnim(0, -1, -1, -1, 0);

    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
    if (Game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
    }
    *reinterpret_cast<void**>(self + 0x814) = __nwa__FUlPQ27CMemory6CStagePci(0x50, stage, s_singmenu_cpp_801de8d4, 0x5DD);

    int state = *reinterpret_cast<int*>(self + 0x814);
    *reinterpret_cast<float*>(state + 0x24) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x20) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x1C) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x30) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x2C) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x28) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x3C) = FLOAT_80332934;
    *reinterpret_cast<float*>(state + 0x38) = FLOAT_80332934;
    *reinterpret_cast<float*>(state + 0x34) = FLOAT_80332934;
    *reinterpret_cast<int*>(state + 0) = 0;
    *reinterpret_cast<int*>(state + 4) = 0;
    *reinterpret_cast<s16*>(state + 8) = 0;
    *reinterpret_cast<s16*>(state + 10) = 0;
    *reinterpret_cast<s16*>(state + 12) = 0x280;
    *reinterpret_cast<s16*>(state + 14) = 0x1C0;
    *reinterpret_cast<float*>(state + 0x10) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x14) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x18) = FLOAT_80332a2c;
    *reinterpret_cast<int*>(state + 0x40) = 0;
    *reinterpret_cast<int*>(state + 0x44) = 0;
    *reinterpret_cast<int*>(state + 0x48) = 0x280;
    *reinterpret_cast<int*>(state + 0x4C) = 0x1C0;
    *reinterpret_cast<s16*>(state + 8) = static_cast<s16>(static_cast<int>(
        static_cast<double>(static_cast<float>(DOUBLE_80332a30 + static_cast<double>(FLOAT_803329f4) * DOUBLE_80332968
                + static_cast<double>(FLOAT_803329d4 + FLOAT_803329ec)) - DOUBLE_80332a38) - DOUBLE_80332a30));
    *reinterpret_cast<s16*>(state + 10) = static_cast<s16>(static_cast<int>(
        static_cast<double>(static_cast<float>(static_cast<double>(FLOAT_803329f0) * DOUBLE_80332968
                + static_cast<double>(FLOAT_803329f0))) - DOUBLE_80332a40));
    *reinterpret_cast<int*>(state + 0x40) = static_cast<int>(static_cast<double>(FLOAT_80332a48)
                + static_cast<double>(FLOAT_803329d4 + FLOAT_803329ec));
    *reinterpret_cast<int*>(state + 0x44) = static_cast<int>(FLOAT_80332950);
    *reinterpret_cast<int*>(state + 0x48) = 0x48;
    *reinterpret_cast<int*>(state + 0x4C) = 0x58;

    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
    if (Game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
    }
    *reinterpret_cast<void**>(self + 0x850) = __nw__FUlPQ27CMemory6CStagePci(0x1008, stage, s_singmenu_cpp_801de8d4, 0x605);
    memset(*reinterpret_cast<void**>(self + 0x850), 0, 0x1008);

    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
    if (Game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
    }
    *reinterpret_cast<void**>(self + 0x82C) = __nw__FUlPQ27CMemory6CStagePci(0x48, stage, s_singmenu_cpp_801de8d4, 0x609);
    memset(*reinterpret_cast<void**>(self + 0x82C), 0, 0x48);

    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
    if (Game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
    }
    *reinterpret_cast<void**>(self + 0x848) = __nw__FUlPQ27CMemory6CStagePci(0xC, stage, s_singmenu_cpp_801de8d4, 0x60D);
    memset(*reinterpret_cast<void**>(self + 0x848), 0, 0xC);

    *reinterpret_cast<s16*>(self + 0x866) = 0;
    if (gSingMenuForcedSelection >= 0) {
        *reinterpret_cast<s16*>(self + 0x864) = 8;
        gSingMenuForcedSelection = -1;
    }
    FLOAT_8032ea78 = FLOAT_803329b8;
    *reinterpret_cast<int*>(self + 0x874) = -1;
    *(self + 0x872) = 1;
    *(self + 0x85A) = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingMenuEnd()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::calcSingleMenu()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80149534
 * PAL Size: 2344b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::drawSingleMenu()
{
    u8* self = reinterpret_cast<u8*>(this);

    if ((Game.m_gameWork.m_menuStageMode != 0) &&
        (Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag != 0)) {
        DrawInit__8CMenuPcsFv(this);
        DrawFilter__8CMenuPcsFUcUcUcUc(this, 0, 0, 0, 0xFF);
        gUtil.ClearZBufferRect(FLOAT_8033294c, FLOAT_8033294c, FLOAT_803329a4, FLOAT_803329a4);
        DrawInit__8CMenuPcsFv(this);

        unsigned int scriptFoodBase = Game.m_scriptFoodBase[0];
        if (scriptFoodBase != 0) {
            u8 menuType = *reinterpret_cast<u8*>(scriptFoodBase + 0xBE0);
            void* shopMenu = *reinterpret_cast<void**>(self + 0x868);
            if (((menuType == 1) || (menuType == 2)) && (shopMenu != 0)) {
                Draw__9CShopMenuFv(shopMenu);
            }
        }

        s16 mode = *reinterpret_cast<s16*>(self + 0x866);
        if (mode == 1) {
            SingleDrawCtrl__8CMenuPcsFv(this);
            return;
        }

        if ((mode == 0) || (mode == 2)) {
            s16* menuData = *reinterpret_cast<s16**>(self + 0x850);
            if (menuData == 0) {
                return;
            }

            s16 count = menuData[0];
            s16* entry = menuData + 4;

            for (s16 i = 0; i < count; i++) {
                if ((i == 0) || (*reinterpret_cast<s16*>(self + 0x864) != 8)) {
                    float alpha = *reinterpret_cast<float*>(entry + 8);

                    if (i == 0) {
                        DrawInit__8CMenuPcsFv(this);
                        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
                        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
                        u8 a = static_cast<u8>(FLOAT_80332940 * alpha);
                        _GXColor color = {0xFF, 0xFF, 0xFF, a};
                        GXSetChanMatColor(GX_COLOR0A0, color);

                        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x20);
                        DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033294c, FLOAT_8033294c, FLOAT_803329a4, FLOAT_80332928,
                                                         FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
                        DrawRect__8CMenuPcsFUlfffffffff(this, 4, FLOAT_8033294c, FLOAT_803329a8, FLOAT_803329a4, FLOAT_80332928,
                                                         FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);

                        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x28);
                        unsigned int step = 0x20;
                        for (unsigned int y = 0x40; y < 0x180; y += step) {
                            if ((0x180 - y) < step) {
                                step = 0x180 - y;
                            }
                            DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033294c, static_cast<float>(y), FLOAT_803329a4,
                                                             static_cast<float>(step), FLOAT_8033294c, FLOAT_8033294c,
                                                             FLOAT_80332934, FLOAT_80332934, 0.0f);
                        }
                    } else if (i == 1) {
                        DrawInit__8CMenuPcsFv(this);
                        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
                        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
                        _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
                        GXSetChanMatColor(GX_COLOR0A0, white);
                        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x21);
                        DrawRect__8CMenuPcsFUlfffffffff(this, 0, -(FLOAT_803329ac * alpha - FLOAT_803329bc), FLOAT_80332948,
                                                         FLOAT_803329ac, FLOAT_803329b0, FLOAT_8033294c, FLOAT_8033294c,
                                                         alpha, FLOAT_80332934, 0.0f);
                        DrawRect__8CMenuPcsFUlfffffffff(this, 8, FLOAT_803329b4, FLOAT_80332948, FLOAT_803329ac, FLOAT_803329b0,
                                                         FLOAT_8033294c, FLOAT_8033294c, alpha, FLOAT_80332934, 0.0f);
                    } else if (i == 2) {
                        DrawSingleStat(alpha);
                    } else {
                        DrawSingleHelpWim(alpha);
                    }
                }
                entry += 0x20;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80149e5c
 * PAL Size: 952b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::loadTextureAsync(char **, int, int, CMenuPcs::CTmp*, int, int, int)
{
    u8* self = reinterpret_cast<u8*>(this);

    gSingMenuHasScriptFoodBase = static_cast<int>(*reinterpret_cast<char*>(Game.m_scriptFoodBase[0] + 0xBE0) != 0);
    if (Game.m_gameWork.m_menuStageMode == 0) {
        if (self[0x859] == 0) {
            return;
        }

        *reinterpret_cast<int*>(self + 0xF0) = 0;
        self[0x859] = 0;
        self[0x85A] = 0;
        return;
    }

    if (self[0x859] == 0) {
        createSingleMenu__8CMenuPcsFv(this);
    }
    if (Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag == 0) {
        return;
    }
    if (self[0x85A] == 0) {
        SingMenuInit__8CMenuPcsFv(this);
    }

    if (*reinterpret_cast<char*>(Game.m_scriptFoodBase[0] + 0xBE0) == 0) {
        int loadIndex = *reinterpret_cast<int*>(self + 0x85C);
        if (loadIndex < 2) {
            if (*reinterpret_cast<int*>(self + 0x860) == 0) {
                char path[260];
                char* language = GetLangString__5CGameFv(&Game);
                sprintf(path, s_dvd__smenu__s_tex_801de8e4, language, PTR_s_solo1_80214b18[loadIndex]);
                gSingMenuAsyncFileHandle = File.Open(path, 0, CFile::PRI_LOW);
                File.ReadASync(gSingMenuAsyncFileHandle);
                *reinterpret_cast<int*>(self + 0x860) = *reinterpret_cast<int*>(self + 0x860) + 1;
            } else if (*reinterpret_cast<int*>(self + 0x860) == 1) {
                if (!File.IsCompleted(gSingMenuAsyncFileHandle)) {
                    gSingMenuAsyncLoadCompleted = 0;
                    goto post_texture_load;
                }

                CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
                if (Game.m_gameWork.m_menuStageMode != 0) {
                    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
                }

                CTextureSet* textureSet = static_cast<CTextureSet*>(
                    __nw__11CTextureSetFUlPQ27CMemory6CStagePci(0x24, stage, s_singmenu_cpp_801de8d4, 0x748));
                if (textureSet != 0) {
                    textureSet = __ct__11CTextureSetFv(textureSet);
                }
                *reinterpret_cast<CTextureSet**>(self + 0x160 + loadIndex * 4) = textureSet;

                stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
                if (Game.m_gameWork.m_menuStageMode != 0) {
                    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
                }

                Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii(textureSet, File.m_readBuffer, stage, 0, 0, 0, 0);
                File.Close(gSingMenuAsyncFileHandle);
                gSingMenuAsyncFileHandle = 0;
                *reinterpret_cast<int*>(self + 0x860) = 0;
                *reinterpret_cast<int*>(self + 0x85C) = *reinterpret_cast<int*>(self + 0x85C) + 1;
            }

            if (*reinterpret_cast<int*>(self + 0x85C) < 2) {
                gSingMenuAsyncLoadCompleted = 0;
            } else {
                int* mapping = DAT_80214b3c;
                for (int i = 0; i < 0x33; i++) {
                    CTextureSet* set = *reinterpret_cast<CTextureSet**>(self + 0x14C + mapping[0] * 4);
                    int texIdx = Find__11CTextureSetFPc(set, reinterpret_cast<char*>(mapping[1]));
                    CTexture* tex = (*reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<u8*>(set) + 8))[static_cast<unsigned long>(texIdx)];
                    *reinterpret_cast<CTexture**>(reinterpret_cast<u8*>(this) + 0x240 + i * 4) = tex;
                    *reinterpret_cast<int*>(reinterpret_cast<u8*>(tex) + 4) = *reinterpret_cast<int*>(reinterpret_cast<u8*>(tex) + 4) + 1;
                    mapping += 2;
                }
                gSingMenuAsyncLoadCompleted = 1;
            }
        } else {
            gSingMenuAsyncLoadCompleted = 1;
        }
    }

post_texture_load:
    if (*reinterpret_cast<s16*>(*reinterpret_cast<int*>(self + 0x850) + 6) != 0) {
        *reinterpret_cast<s16*>(self + 0x866) = *reinterpret_cast<s16*>(self + 0x866) + 1;
        *reinterpret_cast<s16*>(*reinterpret_cast<int*>(self + 0x850) + 6) = 0;
        *reinterpret_cast<s16*>(*reinterpret_cast<int*>(self + 0x850) + 4) = 0;
        *(reinterpret_cast<u8*>(*reinterpret_cast<int*>(self + 0x82C)) + 0xB) = 0;
        *(reinterpret_cast<u8*>(*reinterpret_cast<int*>(self + 0x82C)) + 0xD) = 0;
        *reinterpret_cast<s16*>(*reinterpret_cast<int*>(self + 0x82C) + 0x10) = 0;
        *reinterpret_cast<s16*>(*reinterpret_cast<int*>(self + 0x82C) + 0x22) = 0;
    }

    char menuKind = *reinterpret_cast<char*>(Game.m_scriptFoodBase[0] + 0xBE0);
    if (menuKind == 1) {
        if (*reinterpret_cast<void**>(self + 0x868) == 0) {
            CreateShopMenu__8CMenuPcsFv(this);
        } else {
            Calc__9CShopMenuFv(*reinterpret_cast<void**>(self + 0x868));
        }
    } else if (menuKind == 2) {
        if (*reinterpret_cast<void**>(self + 0x868) == 0) {
            CreateSmithMenu__8CMenuPcsFv(this);
        } else {
            Calc__9CShopMenuFv(*reinterpret_cast<void**>(self + 0x868));
        }
    }

    if (gSingMenuHasScriptFoodBase == 0) {
        s16 state = *reinterpret_cast<s16*>(self + 0x866);
        if (state == 1) {
            SingleCalcCtrl();
        } else if (state < 1) {
            if (state >= 0) {
                SingleCalcFadeIn();
            }
        } else if (state < 3) {
            SingleCalcFadeOut();
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingCalcChara(float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8014935c
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingleBase(float alpha)
{
    DrawInit__8CMenuPcsFv(this);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

    _GXColor color = {0xFF, 0xFF, 0xFF, static_cast<u8>(FLOAT_80332940 * alpha)};
    GXSetChanMatColor(GX_COLOR0A0, color);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x20);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033294c, FLOAT_8033294c, FLOAT_803329a4, FLOAT_80332928,
                                     FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(this, 4, FLOAT_8033294c, FLOAT_803329a8, FLOAT_803329a4, FLOAT_80332928,
                                     FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x28);
    float y = 64.0f;
    float sliceHeight = 32.0f;
    while (y < 384.0f) {
        if ((384.0f - y) < sliceHeight) {
            sliceHeight = 384.0f - y;
        }

        DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033294c, y, FLOAT_803329a4, sliceHeight, FLOAT_8033294c,
                                         FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
        y += sliceHeight;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80148b98
 * PAL Size: 1988b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingleStat(float alpha)
{
    u8* self = reinterpret_cast<u8*>(this);
    u8 languageId = Game.m_gameWork.m_languageId;

    DrawInit__8CMenuPcsFv(this);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

    _GXColor color = {0xFF, 0xFF, 0xFF, static_cast<u8>(FLOAT_80332940 * alpha)};
    GXSetChanMatColor(GX_COLOR0A0, color);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x26);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_803329d4, 0.0f, FLOAT_803329d8, FLOAT_803329d0,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(this, 4, FLOAT_803329d4, FLOAT_803329dc, FLOAT_803329d8, FLOAT_803329d0,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x29);
    for (float y = FLOAT_803329d0; y < FLOAT_803329dc; ) {
        float sliceHeight = 32.0f;
        if ((FLOAT_803329dc - y) < sliceHeight) {
            sliceHeight = FLOAT_803329dc - y;
        }
        DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_803329d4, y, FLOAT_803329a4, sliceHeight,
                                         0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        y += sliceHeight;
    }

    color.a = static_cast<u8>(FLOAT_80332940 * static_cast<float>(DOUBLE_80332968) * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x22);

    unsigned short charaNo = *reinterpret_cast<unsigned short*>(Game.m_scriptFoodBase[0] + 0x3E0);
    float iconStep = FLOAT_803329e8;
    float texU = static_cast<float>(charaNo & 1) * iconStep;
    float texV = static_cast<float>(charaNo >> 1) * iconStep;
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_803329d4 - FLOAT_8033292c, FLOAT_803329ac, iconStep, iconStep,
                                     texU, texV, 1.0f, 1.0f, 0.0f);

    color.a = static_cast<u8>(FLOAT_80332940 * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x2A);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_803329d4 + FLOAT_803329ec, FLOAT_803329f0, FLOAT_803329f4, FLOAT_803329f0,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    DrawInit__8CMenuPcsFv(this);
    SetProjection__8CMenuPcsFi(this, 0);
    SetLight__8CMenuPcsFi(this, 1);
    *reinterpret_cast<float*>(*reinterpret_cast<int*>(*reinterpret_cast<int*>(self + 0x774) + 0x168) + 0x9C) = alpha;
    (*reinterpret_cast<CCharaPcs::CHandle**>(self + 0x774))->Draw(5);
    RestoreProjection__8CMenuPcsFv(this);

    DrawInit__8CMenuPcsFv(this);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
    color.a = static_cast<u8>(FLOAT_80332940 * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x2A);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_803329d4 + FLOAT_803329ec, FLOAT_80332994, FLOAT_803329f4, FLOAT_803329f8,
                                     0.0f, FLOAT_803329f0, 1.0f, 1.0f, 0.0f);

    DrawInit__8CMenuPcsFv(this);
    CFont* font = *reinterpret_cast<CFont**>(self + 0xF8);
    font->SetMargin(0.0f);
    font->SetShadow(1);
    font->SetScale(FLOAT_803329b8);

    _GXColor fontColor = {0xFF, 0xFF, 0xFF, static_cast<u8>(FLOAT_80332940 * alpha)};
    font->SetColor(fontColor);
    font->DrawInit();

    char* charaName = reinterpret_cast<char*>(Game.m_scriptFoodBase[0] + 0x3CA);
    float titleWidth = static_cast<float>(font->GetWidth(charaName));
    float titleX = FLOAT_803329d4 + (FLOAT_803329d8 - titleWidth) * static_cast<float>(DOUBLE_80332968);
    font->SetTlut(0x12);
    font->SetPosX(titleX);
    font->SetPosY(FLOAT_803329fc);
    font->Draw(charaName);

    font->SetTlut(0x17);
    font->SetPosX(titleX);
    font->SetPosY(FLOAT_80332a00);
    font->Draw(charaName);

    font->SetTlut(0x15);
    float y = FLOAT_80332a04;
    for (int i = 0; i < 4; i++) {
        font->SetPosX(FLOAT_803329d4);
        font->SetPosY(y - 5.0f);

        char* label;
        if (languageId == 3) {
            label = gSingMenuTextTableIt[i + 5];
        } else if (languageId < 3) {
            if ((languageId == 0) || (languageId == 1)) {
                label = gSingMenuTextTableEn[i + 5];
            } else {
                label = gSingMenuTextTableDe[i + 5];
            }
        } else if (languageId == 5) {
            label = gSingMenuTextTableEs[i + 5];
        } else if (languageId > 4) {
            label = gSingMenuTextTableEn[i + 5];
        } else {
            label = gSingMenuTextTableFr[i + 5];
        }

        if ((languageId == 2) && (i == 3)) {
            font->SetScaleX(FLOAT_80332a08);
            font->SetScaleY(FLOAT_803329b8);
        } else {
            font->SetScaleX(FLOAT_803329b8);
        }
        font->Draw(label);

        font->renderFlags = (font->renderFlags & 0xEF) | 0x10;
        if (languageId == 2) {
            font->SetMargin(FLOAT_80332a0c);
            font->SetScaleX(FLOAT_80332a08);
            font->SetScaleY(FLOAT_803329b8);
        } else {
            font->SetMargin(FLOAT_80332a10);
            font->SetScale(FLOAT_803329b8);
        }

        unsigned short stat;
        if (i == 0) {
            stat = *reinterpret_cast<unsigned short*>(Game.m_scriptFoodBase[0] + 0x1E);
        } else if (i == 1) {
            stat = *reinterpret_cast<unsigned short*>(Game.m_scriptFoodBase[0] + 0x22);
        } else if (i == 2) {
            stat = *reinterpret_cast<unsigned short*>(Game.m_scriptFoodBase[0] + 0x20);
        } else {
            stat = *reinterpret_cast<unsigned short*>(Game.m_scriptFoodBase[0] + 0x3DE);
        }

        char valueText[36];
        sprintf(valueText, "%d", stat);
        float valueW = static_cast<float>(font->GetWidth(valueText));
        font->SetPosX(FLOAT_80332a18 - valueW);
        font->Draw(valueText);

        font->renderFlags &= 0xEF;
        font->SetMargin(FLOAT_80332934);
        y += FLOAT_80332a1c;
    }

    font->renderFlags &= 0xEF;
    font->SetMargin(FLOAT_80332934);
    DrawInit__8CMenuPcsFv(this);
}

/*
 * --INFO--
 * PAL Address: 0x801488f0
 * PAL Size: 680b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingleHelpWim(float alpha)
{
    DrawInit__8CMenuPcsFv(this);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

    int alphaInt = static_cast<int>(FLOAT_80332940 * alpha);
    _GXColor color = {0xFF, 0xFF, 0xFF, static_cast<u8>(alphaInt)};
    GXSetChanMatColor(GX_COLOR0A0, color);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x23);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033292c, FLOAT_803329c0, FLOAT_8033292c, FLOAT_8033292c, FLOAT_8033294c,
                                    FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(this, 8, FLOAT_803329c4, FLOAT_803329c0, FLOAT_8033292c, FLOAT_8033292c, FLOAT_8033294c,
                                    FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(this, 4, FLOAT_8033292c, FLOAT_803329a8, FLOAT_8033292c, FLOAT_8033292c, FLOAT_8033294c,
                                    FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0xC, FLOAT_803329c4, FLOAT_803329a8, FLOAT_8033292c, FLOAT_8033292c, FLOAT_8033294c,
                                    FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x27);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_80332928, FLOAT_803329c0, FLOAT_803329c8, FLOAT_8033292c, FLOAT_8033294c,
                                    FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(this, 4, FLOAT_80332928, FLOAT_803329a8, FLOAT_803329c8, FLOAT_8033292c, FLOAT_8033294c,
                                    FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x24);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033292c, FLOAT_803329cc, FLOAT_8033292c, FLOAT_803329d0, FLOAT_8033294c,
                                    FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(this, 8, FLOAT_803329c4, FLOAT_803329cc, FLOAT_8033292c, FLOAT_803329d0, FLOAT_8033294c,
                                    FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x2B);
    DrawRect__8CMenuPcsFUlfffffffff(this, 8, FLOAT_80332928, FLOAT_803329cc, FLOAT_803329c8, FLOAT_803329d0, FLOAT_8033294c,
                                    FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleCrescent(float scaleX, float alpha)
{
    DrawInit__8CMenuPcsFv(this);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 0);

    _GXColor color = {0xFF, 0xFF, 0xFF, static_cast<u8>(FLOAT_80332940 * alpha)};
    GXSetChanMatColor(GX_COLOR0A0, color);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, 0x21);
    DrawRect__8CMenuPcsFUlfffffffff(&MenuPcs, 0,
                                    -(FLOAT_803329ac * scaleX - FLOAT_803329bc), FLOAT_80332948,
                                    FLOAT_803329ac, FLOAT_803329b0,
                                    FLOAT_8033294c, FLOAT_8033294c,
                                    scaleX, FLOAT_80332934, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(&MenuPcs, 8,
                                    FLOAT_803329b4, FLOAT_80332948,
                                    FLOAT_803329ac, FLOAT_803329b0,
                                    FLOAT_8033294c, FLOAT_8033294c,
                                    scaleX, FLOAT_80332934, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x801484e4
 * PAL Size: 744b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingleCalcFadeIn()
{
    u8* self = reinterpret_cast<u8*>(this);
    if (*(short*)(*reinterpret_cast<int*>(self + 0x850) + 4) == 0) {
        Sound.PlaySe(0xE, 0x40, 0x7F, 0);
        memset(*reinterpret_cast<void**>(self + 0x850), 0, 0x1008);

        int fadePtr = *reinterpret_cast<int*>(self + 0x850);
        int phase = (*reinterpret_cast<s16*>(self + 0x864) == 8) ? 10 : 0;
        *(int*)(fadePtr + 0x2C) = 0;
        *(int*)(fadePtr + 0x30) = 10;

        fadePtr = *reinterpret_cast<int*>(self + 0x850);
        *(int*)(fadePtr + 0x6C) = phase;
        *(int*)(fadePtr + 0x70) = 10;

        fadePtr = *reinterpret_cast<int*>(self + 0x850);
        *(int*)(fadePtr + 0xAC) = phase;
        *(int*)(fadePtr + 0xB0) = 10;

        fadePtr = *reinterpret_cast<int*>(self + 0x850);
        *(int*)(fadePtr + 0xEC) = phase;
        *(int*)(fadePtr + 0xF0) = 10;

        **reinterpret_cast<short**>(self + 0x850) = 4;
        *(short*)(*reinterpret_cast<int*>(self + 0x850) + 6) = 0;
        *(short*)(*reinterpret_cast<int*>(self + 0x850) + 4) = 1;
    }

    int completed = 0;
    *(short*)(*reinterpret_cast<int*>(self + 0x82C) + 0x22) = *(short*)(*reinterpret_cast<int*>(self + 0x82C) + 0x22) + 1;

    int count = (int)**reinterpret_cast<short**>(self + 0x850);
    short* entry = *reinterpret_cast<short**>(self + 0x850) + 4;
    int frame = (int)*(short*)(*reinterpret_cast<int*>(self + 0x82C) + 0x22);
    if (0 < count) {
        do {
            if (*(int*)(entry + 0x12) <= frame) {
                if (frame < *(int*)(entry + 0x12) + *(int*)(entry + 0x14)) {
                    *(int*)(entry + 0x10) = *(int*)(entry + 0x10) + 1;
                    *(float*)(entry + 8) = static_cast<float>((DOUBLE_80332980 / (double)*(int*)(entry + 0x14)) *
                                                              (double)*(int*)(entry + 0x10));
                } else {
                    completed = completed + 1;
                    *(float*)(entry + 8) = FLOAT_80332934;
                }
            }
            entry = entry + 0x20;
            count = count - 1;
        } while (count != 0);
    }

    CChara::CModel* model = *reinterpret_cast<CChara::CModel**>(*reinterpret_cast<int*>(self + 0x774) + 0x168);
    if (*reinterpret_cast<float*>(reinterpret_cast<u8*>(model) + 0x10) <=
        *reinterpret_cast<float*>(reinterpret_cast<u8*>(model) + 0x08)) {
        SetFrame__Q26CChara6CModelFf(FLOAT_8033294c, model);
    } else {
        AddFrame__Q26CChara6CModelFf(FLOAT_80332934, model);
    }

    unsigned short modelScaleIndex = *reinterpret_cast<unsigned short*>(Game.m_scriptFoodBase[0] + 0x3E0);
    float modelScale = DAT_801dd708[modelScaleIndex];
    Mtx scaleMtx;
    PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
    scaleMtx[1][3] = DAT_801dd6f8[modelScaleIndex];
    scaleMtx[0][3] = FLOAT_8033294c;
    scaleMtx[2][3] = FLOAT_8033294c;

    int modelPtr = *reinterpret_cast<int*>(*reinterpret_cast<int*>(self + 0x774) + 0x168);
    *reinterpret_cast<u8*>(modelPtr + 0x10C) = (*reinterpret_cast<u8*>(modelPtr + 0x10C) & 0x7F) | 0x80;
    SetMatrix__Q26CChara6CModelFPA4_f(model, scaleMtx);
    CalcMatrix__Q26CChara6CModelFv(model);
    CalcSkin__Q26CChara6CModelFv(model);

    if (**reinterpret_cast<short**>(self + 0x850) == completed) {
        (*reinterpret_cast<short**>(self + 0x850))[3] = 1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingleDrawFadeIn()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80148220
 * PAL Size: 708b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingleCalcFadeOut()
{
    u8* self = reinterpret_cast<u8*>(this);
    SingleFadeState* fadeState = *reinterpret_cast<SingleFadeState**>(self + 0x850);

    if (fadeState->active == 0) {
        Sound.PlaySe(0xF, 0x40, 0x7F, 0);
        memset(fadeState, 0, sizeof(SingleFadeState));

        fadeState->entries[0].startFrame = (*reinterpret_cast<s16*>(self + 0x864) == 8) * 10;
        fadeState->entries[0].duration = 10;
        fadeState->entries[1].startFrame = 0;
        fadeState->entries[1].duration = 10;
        fadeState->entries[2].startFrame = 0;
        fadeState->entries[2].duration = 10;
        fadeState->entries[3].startFrame = 0;
        fadeState->entries[3].duration = 10;

        fadeState->count = 4;
        fadeState->done = 0;
        fadeState->active = 1;
    }

    int completed = 0;
    int ctrlState = *reinterpret_cast<int*>(self + 0x82C);
    ++(*reinterpret_cast<s16*>(ctrlState + 0x22));

    int totalEntries = static_cast<int>(fadeState->count);
    int frame = static_cast<int>(*reinterpret_cast<s16*>(ctrlState + 0x22));
    for (int i = 0; i < totalEntries; i++) {
        SingleFadeEntry* entry = &fadeState->entries[i];
        int start = entry->startFrame;
        if (frame < start) {
            entry->alpha = FLOAT_80332934;
        } else {
            int duration = entry->duration;
            if (frame < start + duration) {
                int elapsed = ++entry->elapsed;
                entry->alpha =
                    static_cast<float>(-((DOUBLE_80332980 / static_cast<double>(duration)) *
                                          static_cast<double>(elapsed) - DOUBLE_80332980));
            } else {
                completed++;
                entry->alpha = FLOAT_8033294c;
            }
        }
    }

    CChara::CModel* model = *reinterpret_cast<CChara::CModel**>(*reinterpret_cast<int*>(self + 0x774) + 0x168);
    if (*reinterpret_cast<float*>(reinterpret_cast<u8*>(model) + 0x10) <=
        *reinterpret_cast<float*>(reinterpret_cast<u8*>(model) + 0x08)) {
        SetFrame__Q26CChara6CModelFf(FLOAT_8033294c, model);
    } else {
        AddFrame__Q26CChara6CModelFf(FLOAT_80332934, model);
    }

    unsigned short modelScaleIndex = *reinterpret_cast<unsigned short*>(Game.m_scriptFoodBase[0] + 0x3E0);
    float modelScale = DAT_801dd708[modelScaleIndex];
    Mtx scaleMtx;
    PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
    scaleMtx[1][3] = DAT_801dd6f8[modelScaleIndex];
    scaleMtx[0][3] = FLOAT_8033294c;
    scaleMtx[2][3] = FLOAT_8033294c;

    int modelPtr = *reinterpret_cast<int*>(*reinterpret_cast<int*>(self + 0x774) + 0x168);
    *reinterpret_cast<u8*>(modelPtr + 0x10C) = (*reinterpret_cast<u8*>(modelPtr + 0x10C) & 0x7F) | 0x80;
    SetMatrix__Q26CChara6CModelFPA4_f(model, scaleMtx);
    CalcMatrix__Q26CChara6CModelFv(model);
    CalcSkin__Q26CChara6CModelFv(model);

    if (totalEntries == completed) {
        fadeState->done = 1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingleDrawFadeOut()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80147d50
 * PAL Size: 1232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingleCalcCtrl()
{
    u8* self = reinterpret_cast<u8*>(this);

    if (gSingMenuAsyncLoadCompleted == 0) {
        return;
    }

    int statePtr = *reinterpret_cast<int*>(self + 0x82C);
    if ((self[0x872] != 0) && (*reinterpret_cast<s16*>(statePtr + 0x10) != 0)) {
        self[0x872] = 0;
    }

    unsigned short result = 0;
    CChara::CModel* model = *reinterpret_cast<CChara::CModel**>(*reinterpret_cast<int*>(self + 0x774) + 0x168);
    if (*reinterpret_cast<float*>(reinterpret_cast<u8*>(model) + 0x10) <=
        *reinterpret_cast<float*>(reinterpret_cast<u8*>(model) + 0x08)) {
        SetFrame__Q26CChara6CModelFf(FLOAT_8033294c, model);
    } else {
        AddFrame__Q26CChara6CModelFf(FLOAT_80332934, model);
    }

    unsigned short modelScaleIndex = *reinterpret_cast<unsigned short*>(Game.m_scriptFoodBase[0] + 0x3E0);
    float modelScale = DAT_801dd708[modelScaleIndex];
    Mtx scaleMtx;
    PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
    scaleMtx[1][3] = DAT_801dd6f8[modelScaleIndex];
    scaleMtx[0][3] = FLOAT_8033294c;
    scaleMtx[2][3] = FLOAT_8033294c;

    int modelPtr = *reinterpret_cast<int*>(*reinterpret_cast<int*>(self + 0x774) + 0x168);
    *reinterpret_cast<u8*>(modelPtr + 0x10C) = (*reinterpret_cast<u8*>(modelPtr + 0x10C) & 0x7F) | 0x80;
    SetMatrix__Q26CChara6CModelFPA4_f(model, scaleMtx);
    CalcMatrix__Q26CChara6CModelFv(model);
    CalcSkin__Q26CChara6CModelFv(model);

    s16 mode = *reinterpret_cast<s16*>(self + 0x864);
    s16 proc = *reinterpret_cast<s16*>(statePtr + 0x10);
    switch (mode) {
    case 0:
        result = (proc == 0) ? CmdOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? CmdCtrl__8CMenuPcsFv(this) : CmdClose__8CMenuPcsFv(this));
        break;
    case 1:
        result = (proc == 0) ? ItemOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? ItemCtrl__8CMenuPcsFv(this) : ItemClose__8CMenuPcsFv(this));
        if (*reinterpret_cast<int*>(self + 0x874) >= 0) {
            ++(*reinterpret_cast<int*>(self + 0x874));
            if (*reinterpret_cast<int*>(self + 0x874) > 0x31) {
                *reinterpret_cast<int*>(self + 0x874) = -1;
            }
        }
        break;
    case 2:
        result = (proc == 0) ? EquipOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? EquipCtrl__8CMenuPcsFv(this) : EquipClose__8CMenuPcsFv(this));
        break;
    case 3:
        result = (proc == 0) ? ArtiOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? ArtiCtrl__8CMenuPcsFv(this) : ArtiClose__8CMenuPcsFv(this));
        break;
    case 4:
        result = (proc == 0) ? TmpArtiOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? TmpArtiCtrl__8CMenuPcsFv(this) : TmpArtiClose__8CMenuPcsFv(this));
        break;
    case 5:
        result = (proc == 0) ? MoneyOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? MoneyCtrl__8CMenuPcsFv(this) : MoneyClose__8CMenuPcsFv(this));
        break;
    case 6:
        result = (proc == 0) ? FavoOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? FavoCtrl__8CMenuPcsFv(this) : FavoClose__8CMenuPcsFv(this));
        break;
    case 7:
        result = (proc == 0) ? CompaOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? CompaCtrl__8CMenuPcsFv(this) : CompaClose__8CMenuPcsFv(this));
        break;
    case 8:
        result = (proc == 0) ? LetterOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? LetterCtrl__8CMenuPcsFv(this) : LetterClose__8CMenuPcsFv(this));
        break;
    case 9:
        result = (proc == 0) ? MLstOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? MLstCtrl__8CMenuPcsFv(this) : MLstClose__8CMenuPcsFv(this));
        break;
    }

    CalcHeart__8CMesMenuFv(*reinterpret_cast<void**>(self + 0x268));
    *reinterpret_cast<unsigned short*>(statePtr + 0x2E) = result;

    bool hasInput = (Pad._452_4_ != 0) || (Pad._448_4_ != -1);
    unsigned short press;
    if (hasInput) {
        press = 0;
    } else {
        __cntlzw((unsigned int)Pad._448_4_);
        press = Pad._8_2_;
    }

    if ((press & 0x800) != 0) {
        *reinterpret_cast<unsigned short*>(*reinterpret_cast<int*>(self + 0x850) + 6) = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801478cc
 * PAL Size: 1156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingleDrawCtrl()
{
    u8* self = reinterpret_cast<u8*>(this);

    DrawInit__8CMenuPcsFv(this);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, white);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x20);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033294c, FLOAT_8033294c, FLOAT_803329a4, FLOAT_80332928,
                                     FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(this, 4, FLOAT_8033294c, FLOAT_803329a8, FLOAT_803329a4, FLOAT_80332928,
                                     FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x28);
    unsigned int step = 0x20;
    for (unsigned int y = 0x40; y < 0x180; y += step) {
        if ((0x180 - y) < step) {
            step = 0x180 - y;
        }

        DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033294c, static_cast<float>(y), FLOAT_803329a4,
                                         static_cast<float>(step), FLOAT_8033294c, FLOAT_8033294c,
                                         FLOAT_80332934, FLOAT_80332934, 0.0f);
    }

    if (*reinterpret_cast<s16*>(self + 0x864) != 8) {
        DrawInit__8CMenuPcsFv(this);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
        GXSetChanMatColor(GX_COLOR0A0, white);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x21);
        DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033292c, FLOAT_80332948, FLOAT_803329ac, FLOAT_803329b0,
                                         FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
        DrawRect__8CMenuPcsFUlfffffffff(this, 8, FLOAT_803329b4, FLOAT_80332948, FLOAT_803329ac, FLOAT_803329b0,
                                         FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
        DrawSingleStat(FLOAT_80332934);
        DrawSingleHelpWim(FLOAT_80332934);
    }

    if (gSingMenuAsyncLoadCompleted == 0) {
        return;
    }

    switch (*reinterpret_cast<s16*>(self + 0x864)) {
    case 0:
        CmdDraw__8CMenuPcsFv(this);
        break;
    case 1:
        ItemDraw__8CMenuPcsFv(this);
        break;
    case 2:
        EquipDraw__8CMenuPcsFv(this);
        break;
    case 3:
        ArtiDraw__8CMenuPcsFv(this);
        break;
    case 4:
        TmpArtiDraw__8CMenuPcsFv(this);
        break;
    case 5:
        MoneyDraw__8CMenuPcsFv(this);
        break;
    case 6:
        FavoDraw__8CMenuPcsFv(this);
        break;
    case 7:
        CompaDraw__8CMenuPcsFv(this);
        break;
    case 8:
        LetterDraw__8CMenuPcsFv(this);
        break;
    case 9:
        MLstDraw__8CMenuPcsFv(this);
        break;
    }

    int statePtr = *reinterpret_cast<int*>(self + 0x82C);
    if (*reinterpret_cast<s16*>(statePtr + 0x2E) == 0) {
        return;
    }

    if (*reinterpret_cast<s16*>(statePtr + 0x10) < 2) {
        ++(*reinterpret_cast<s16*>(statePtr + 0x10));
        *reinterpret_cast<s16*>(statePtr + 0x22) = 0;
        *reinterpret_cast<u8*>(statePtr + 0xB) = 0;
        *reinterpret_cast<s16*>(statePtr + 0x2E) = 0;
        return;
    }

    s16 previousMode = 0;
    if (*reinterpret_cast<u8*>(statePtr + 0xD) == 0) {
        s16 mode = *reinterpret_cast<s16*>(self + 0x864);
        if (mode == 9) {
            *reinterpret_cast<s16*>(self + 0x864) = *reinterpret_cast<s16*>(statePtr + 0x26);
        } else if ((mode == 8) && (gSingMenuForcedSelection >= 0)) {
            *reinterpret_cast<s16*>(self + 0x864) = static_cast<s16>(gSingMenuForcedSelection);
        } else if ((mode == 8) || (gSingMenuForcedSelection < 0)) {
            if (*reinterpret_cast<s16*>(statePtr + 0x1E) < 1) {
                --(*reinterpret_cast<s16*>(self + 0x864));
                if (*reinterpret_cast<s16*>(self + 0x864) < 0) {
                    *reinterpret_cast<s16*>(self + 0x864) = 8;
                }
            } else {
                ++(*reinterpret_cast<s16*>(self + 0x864));
                if (*reinterpret_cast<s16*>(self + 0x864) > 8) {
                    *reinterpret_cast<s16*>(self + 0x864) = 0;
                }
            }
        } else {
            *reinterpret_cast<s16*>(self + 0x864) = 8;
        }
    } else {
        s16 mode = *reinterpret_cast<s16*>(self + 0x864);
        if (mode == 9) {
            *reinterpret_cast<s16*>(*reinterpret_cast<int*>(self + 0x850) + 6) = 1;
        } else {
            *reinterpret_cast<s16*>(self + 0x864) = 9;
            previousMode = mode;
        }
    }

    memset(reinterpret_cast<void*>(statePtr), 0, 0x48);
    FLOAT_8032ea78 = FLOAT_803329b8;
    *reinterpret_cast<s16*>(statePtr + 0x26) = previousMode;
}

/*
 * --INFO--
 * PAL Address: 0x80147728
 * PAL Size: 420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingleIcon(int iconNo, int posX, int posY, float alpha, int rawIcon, float uvScale)
{
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

    _GXColor color = {0xFF, 0xFF, 0xFF, static_cast<u8>(FLOAT_80332940 * alpha)};
    GXSetChanMatColor(GX_COLOR0A0, color);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x25);
    if (rawIcon == 0) {
        iconNo = static_cast<int>(gSingMenuItemIconByType[iconNo]);
    }

    int row = iconNo / 8;
    int col = iconNo % 8;
    if (col < 0) {
        col += 8;
        row--;
    }

    DrawRect__8CMenuPcsFUlfffffffff(
        this, 0, static_cast<float>(posX), static_cast<float>(posY), FLOAT_8033292c, FLOAT_8033292c,
        static_cast<float>(col * 0x20), static_cast<float>(row * 0x20), uvScale, uvScale, FLOAT_8033294c);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawShadowFont(CFont* font, char* text, float x, float y, int tlut, int shadowTlut)
{
    font->SetTlut(shadowTlut);
    font->SetPosX(FLOAT_80332934 + x);
    font->SetPosY((FLOAT_80332934 + y) - FLOAT_80332954);
    font->Draw(text);

    font->SetTlut(tlut);
    font->SetPosX(x);
    font->SetPosY(y - FLOAT_80332954);
    font->Draw(text);
}

/*
 * --INFO--
 * PAL Address: 0x801475BC
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawNoShadowFont(CFont* font, char* text, float x, float y, int tlut, int)
{
    font->SetTlut(tlut);
    font->SetPosX(x);
    font->SetPosY(y - FLOAT_80332954);
    font->Draw(text);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMenuPcs::GetItemType(int itemId, int useRawItemId)
{
    if (useRawItemId == 0) {
        itemId = static_cast<int>(*reinterpret_cast<s16*>(Game.m_scriptFoodBase[0] + itemId * 2 + 0xB6));
    }

    if (itemId < 1) {
        return 0;
    }
    if (itemId < 0x9F) {
        return 1;
    }
    if (itemId < 0x100) {
        return 2;
    }
    if (itemId < 0x125) {
        return 3;
    }
    if (itemId == 0x125) {
        return 4;
    }
    if (itemId < 0x12A) {
        return 5;
    }
    if (itemId < 0x17D) {
        return 6;
    }
    if (itemId <= 0x188) {
        return 7;
    }
    if (itemId <= 400) {
        return 8;
    }
    return 9;
}

/*
 * --INFO--
 * PAL Address: 0x8014744c
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
double CMenuPcs::CalcListPos(int listPos, int listSize, int mode)
{
    float span;

    if (mode != 0) {
        span = static_cast<float>(static_cast<double>(listSize - 1));
    } else {
        span = static_cast<float>(static_cast<double>(listSize - 8));
    }

    if ((span <= FLOAT_8033294c) || (listSize <= 8)) {
        return FLOAT_8033299c;
    }

    return (FLOAT_803329a0 * (static_cast<float>(static_cast<double>(listPos)) / span)) +
           FLOAT_8033292c;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawListPosMark(float x, float y, float z)
{
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 0);

    _GXColor color = { 0xFF, 0xFF, 0xFF, 0xFF };
    GXSetChanMatColor(GX_COLOR0A0, color);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, 0x2E);
    DrawRect__8CMenuPcsFUlfffffffff(
        &MenuPcs, 0, FLOAT_80332990 + x, y + z, FLOAT_80332930, FLOAT_80332930, FLOAT_80332994,
        FLOAT_80332998, FLOAT_80332934, FLOAT_80332934, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x801471cc
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::EquipChk(int itemNo)
{
    int script = Game.m_scriptFoodBase[0];

    if (*reinterpret_cast<s16*>(script + 0xbaa) > 2) {
        if (*reinterpret_cast<s16*>(script + 0x208) >= 0 && *reinterpret_cast<s16*>(script + 0x208) == itemNo) {
            return 1;
        }
        if (*reinterpret_cast<s16*>(script + 0xbaa) > 3) {
            if (*reinterpret_cast<s16*>(script + 0x20a) >= 0 && *reinterpret_cast<s16*>(script + 0x20a) == itemNo) {
                return 1;
            }
            if (*reinterpret_cast<s16*>(script + 0xbaa) > 4) {
                if (*reinterpret_cast<s16*>(script + 0x20c) >= 0 && *reinterpret_cast<s16*>(script + 0x20c) == itemNo) {
                    return 1;
                }
                if (*reinterpret_cast<s16*>(script + 0xbaa) > 5) {
                    if (*reinterpret_cast<s16*>(script + 0x20e) >= 0 && *reinterpret_cast<s16*>(script + 0x20e) == itemNo) {
                        return 1;
                    }
                    if (*reinterpret_cast<s16*>(script + 0xbaa) > 6) {
                        if (*reinterpret_cast<s16*>(script + 0x210) >= 0 && *reinterpret_cast<s16*>(script + 0x210) == itemNo) {
                            return 1;
                        }
                        if (*reinterpret_cast<s16*>(script + 0xbaa) > 7 && *reinterpret_cast<s16*>(script + 0x212) >= 0 &&
                            *reinterpret_cast<s16*>(script + 0x212) == itemNo) {
                            return 1;
                        }
                    }
                }
            }
        }
    }

    if (*reinterpret_cast<s16*>(script + 0xac) >= 0 && *reinterpret_cast<s16*>(script + 0xac) == itemNo) {
        return 1;
    }
    if (*reinterpret_cast<s16*>(script + 0xae) >= 0 && *reinterpret_cast<s16*>(script + 0xae) == itemNo) {
        return 1;
    }
    if (*reinterpret_cast<s16*>(script + 0xb0) >= 0 && *reinterpret_cast<s16*>(script + 0xb0) == itemNo) {
        return 1;
    }
    if (*reinterpret_cast<s16*>(script + 0xb2) >= 0 && *reinterpret_cast<s16*>(script + 0xb2) == itemNo) {
        return 1;
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801470b8
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawEquipMark(int x, int y, float alpha)
{
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 0);

    _GXColor color = {0xFF, 0xFF, 0xFF, static_cast<u8>(static_cast<int>(FLOAT_80332940 * alpha))};
    GXSetChanMatColor(GX_COLOR0A0, color);

    union {
        double value;
        u32 words[2];
    } xPos, yPos;

    xPos.words[0] = 0x43300000;
    xPos.words[1] = static_cast<u32>(x) ^ 0x80000000U;
    yPos.words[0] = 0x43300000;
    yPos.words[1] = static_cast<u32>(y) ^ 0x80000000U;

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, 0x2C);
    DrawRect__8CMenuPcsFUlfffffffff(
        &MenuPcs, 0, static_cast<float>(xPos.value - DOUBLE_80332938),
        static_cast<float>(yPos.value - DOUBLE_80332938), FLOAT_80332948, FLOAT_80332948, FLOAT_8033294c, FLOAT_8033294c,
        FLOAT_80332934, FLOAT_80332934, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x80146adc
 * PAL Size: 1500b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingWin(short mode)
{
    u8* self = reinterpret_cast<u8*>(this);
    s16* win = *reinterpret_cast<s16**>(self + 0x848);

    if (mode >= 0 && win[5] != mode) {
        win[5] = mode;
    }

    if (win[5] == 3) {
        return;
    }

    float left = static_cast<float>(win[0]) + static_cast<float>(win[2]) * 0.5f;
    float top = static_cast<float>(win[1]) + static_cast<float>(win[3]) * 0.5f;
    float width;
    float height;

    if (win[5] == 1) {
        left = static_cast<float>(win[0]);
        top = static_cast<float>(win[1]);
        width = static_cast<float>(win[2]);
        height = static_cast<float>(win[3]);
    } else {
        float leftScale = (((left - static_cast<float>(win[0])) - FLOAT_8033292c) / FLOAT_80332970) * static_cast<float>(win[4]);
        float topScale = (((top - static_cast<float>(win[1])) - FLOAT_8033292c) / FLOAT_80332970) * static_cast<float>(win[4]);
        left = (left - FLOAT_8033292c) - leftScale;
        width = static_cast<float>(DOUBLE_80332978 * static_cast<double>(FLOAT_8033292c + leftScale));
        height = static_cast<float>(DOUBLE_80332978 * static_cast<double>(FLOAT_8033292c + topScale));
        top = (top - FLOAT_8033292c) - topScale;
    }

    int leftPx = static_cast<int>(static_cast<double>(left) - DOUBLE_80332968);
    int topPx = static_cast<int>(static_cast<double>(top) - DOUBLE_80332968);
    int widthPx = static_cast<int>(static_cast<double>(width) - DOUBLE_80332980);
    int heightPx = static_cast<int>(static_cast<double>(height) - DOUBLE_80332980);

    float x0 = static_cast<float>(leftPx);
    float y0 = static_cast<float>(topPx);
    float w = static_cast<float>(widthPx);
    float h = static_cast<float>(heightPx);
    float x1 = x0 + w - FLOAT_8033292c;
    float y1 = y0 + h - FLOAT_8033292c;

    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, white);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x3F);
    for (unsigned long i = 0; i < 4; i++) {
        unsigned long uvFlag = 0;
        float x = x0;
        float y = y0;
        if ((i & 1) != 0) {
            uvFlag = 8;
            x = x1;
        }
        if ((i & 2) != 0) {
            uvFlag |= 4;
            y = y1;
        }
        DrawRect__8CMenuPcsFUlfffffffff(this, uvFlag, x, y, FLOAT_8033292c, FLOAT_8033292c, FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    }

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x41);
    float innerW = w - static_cast<float>(DOUBLE_80332988);
    float innerX = FLOAT_8033292c + x0;
    for (int i = 0; i < 2; i++) {
        unsigned long uvFlag = 0;
        float y = y0;
        if (i != 0) {
            uvFlag = 4;
            y = y1;
        }
        DrawRect__8CMenuPcsFUlfffffffff(this, uvFlag, innerX, y, innerW, FLOAT_8033292c, FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    }

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x40);
    float innerH = h - static_cast<float>(DOUBLE_80332988);
    float innerY = FLOAT_8033292c + y0;
    for (int i = 0; i < 2; i++) {
        unsigned long uvFlag = 0;
        float x = x0;
        if (i != 0) {
            uvFlag = 8;
            x = x1;
        }
        DrawRect__8CMenuPcsFUlfffffffff(this, uvFlag, x, innerY, FLOAT_8033292c, innerH, FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    }

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x42);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, innerX, innerY, innerW, innerH, FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);

    int winStatePtr = *reinterpret_cast<int*>(self + 0x848);
    s16 state = *reinterpret_cast<s16*>(winStatePtr + 10);
    if (state == 0) {
        *reinterpret_cast<s16*>(winStatePtr + 8) = *reinterpret_cast<s16*>(winStatePtr + 8) + 1;
        if (*reinterpret_cast<s16*>(winStatePtr + 8) > 5) {
            *reinterpret_cast<s16*>(winStatePtr + 8) = 6;
            *reinterpret_cast<s16*>(winStatePtr + 10) = 1;
        }
    } else if (state == 1) {
        if (*reinterpret_cast<s16*>(winStatePtr + 8) != 6) {
            *reinterpret_cast<s16*>(winStatePtr + 8) = 6;
        }
    } else if (state == 2) {
        *reinterpret_cast<s16*>(winStatePtr + 8) = *reinterpret_cast<s16*>(winStatePtr + 8) - 1;
        if (*reinterpret_cast<s16*>(winStatePtr + 8) < 1) {
            *reinterpret_cast<s16*>(winStatePtr + 8) = 0;
            *reinterpret_cast<s16*>(winStatePtr + 10) = 3;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x801466ec
 * PAL Size: 1008b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingWinMess(int messageNo, int activeMask, int useDynamic)
{
    CFont* font = *reinterpret_cast<CFont**>(reinterpret_cast<u8*>(this) + 0xF8);
    font->SetMargin(FLOAT_80332934);
    font->SetShadow(1);
    font->SetScale(FLOAT_8032ea78);
    font->DrawInit();

    _GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
    font->SetColor(color);

    int lineCount = AStar.m_bestPath.m_pathLength;
    if (useDynamic == 0) {
        lineCount = *reinterpret_cast<int*>(DAT_80214a50 + messageNo * 0x14);
    }

    int maxWidth = 0;
    char* dynamicText = s_DynamicMessStr;
    unsigned char* staticInfo = DAT_80214a50 + messageNo * 0x14;
    for (int i = 0; i < lineCount; i++) {
        short textId = *reinterpret_cast<short*>(staticInfo + 4);
        int textWidth = font->GetWidth(GetSingWinMessage(textId, dynamicText, useDynamic));
        if (maxWidth < textWidth) {
            maxWidth = textWidth;
        }
        staticInfo += 2;
        dynamicText += 0x80;
    }

    s16* win = *reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x848);
    int lineHeight = static_cast<int>(FLOAT_80332960 * FLOAT_8032ea78);
    if (FLOAT_8033294c < FLOAT_80332960 * FLOAT_8032ea78 - static_cast<float>(lineHeight)) {
        lineHeight++;
    }

    float x = static_cast<float>(win[0]) + static_cast<float>(win[2] - maxWidth) * static_cast<float>(DOUBLE_80332968);
    float y = static_cast<float>(win[1] + 0x20);
    int lineStep = lineHeight + 3;

    dynamicText = s_DynamicMessStr;
    staticInfo = DAT_80214a50 + messageNo * 0x14;
    for (int i = 0; i < lineCount; i++) {
        font->SetTlut(((activeMask & (1 << i)) != 0) + 8);

        short textId = *reinterpret_cast<short*>(staticInfo + 4);
        const char* text = GetSingWinMessage(textId, dynamicText, useDynamic);
        if (strlen(text) != 0) {
            char lineBuffer[128];
            strcpy(lineBuffer, text);
            font->SetPosX(x);
            font->SetPosY(y - FLOAT_80332954);
            font->Draw(lineBuffer);
        }

        staticInfo += 2;
        dynamicText += 0x80;
        y += static_cast<float>(lineStep);
    }

    DrawInit__8CMenuPcsFv(this);
}

/*
 * --INFO--
 * PAL Address: 0x801464cc
 * PAL Size: 544b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetSingWinSize(int messageNo, short* outWidth, short* outHeight, int useDynamic)
{
    CFont* font = *reinterpret_cast<CFont**>(reinterpret_cast<u8*>(this) + 0xF8);
    font->SetMargin(FLOAT_80332934);
    font->SetShadow(1);
    font->SetScale(FLOAT_8032ea78);

    int lineCount = AStar.m_bestPath.m_pathLength;
    if (useDynamic == 0) {
        lineCount = *reinterpret_cast<int*>(DAT_80214a50 + messageNo * 0x14);
    }

    int maxWidth = 0;
    char* dynamicText = s_DynamicMessStr;
    unsigned char* staticInfo = DAT_80214a50 + messageNo * 0x14;
    for (int i = 0; i < lineCount; i++) {
        short textId = *reinterpret_cast<short*>(staticInfo + 4);
        int textWidth = font->GetWidth(GetSingWinMessage(textId, dynamicText, useDynamic));
        if (maxWidth < textWidth) {
            maxWidth = textWidth;
        }
        staticInfo += 2;
        dynamicText += 0x80;
    }

    if (useDynamic == 0) {
        maxWidth -= 0x18;
    } else {
        maxWidth += 0x16;
    }

    int lineHeight = static_cast<int>(FLOAT_80332960 * FLOAT_8032ea78);
    if (FLOAT_8033294c < FLOAT_80332960 * FLOAT_8032ea78 - static_cast<float>(lineHeight)) {
        lineHeight++;
    }

    int widthLines = maxWidth / lineHeight;
    if (maxWidth != widthLines * lineHeight) {
        widthLines++;
    }

    if (useDynamic == 0) {
        widthLines += 3;
    }

    *outWidth = static_cast<short>(widthLines * lineHeight + 0x40);
    *outHeight = static_cast<short>(lineCount * (lineHeight + 2) + 0x40);
}

/*
 * --INFO--
 * PAL Address: 0x80146490
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetSingWinInfo(int x, int y, int w, int h)
{
    (*reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x848))[0] = static_cast<s16>(x);
    (*reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x848))[1] = static_cast<s16>(y);
    (*reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x848))[2] = static_cast<s16>(w);
    (*reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x848))[3] = static_cast<s16>(h);
    (*reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x848))[4] = 0;
    (*reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x848))[5] = 3;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetSingDynamicWinMessInfo(
    int lineCount,
    char* line0,
    char* line1,
    char* line2,
    char* line3,
    char* line4,
    char* line5,
    char* line6,
    char* line7)
{
    AStar.m_bestPath.m_pathLength = lineCount;

    if (line0 != 0) {
        strcpy(s_DynamicMessStr, line0);
    }
    if (line1 != 0) {
        strcpy(s_DynamicMessStr + 0x80, line1);
    }
    if (line2 != 0) {
        strcpy(s_DynamicMessStr + 0x100, line2);
    }
    if (line3 != 0) {
        strcpy(s_DynamicMessStr + 0x180, line3);
    }
    if (line4 != 0) {
        strcpy(s_DynamicMessStr + 0x200, line4);
    }
    if (line5 != 0) {
        strcpy(s_DynamicMessStr + 0x280, line5);
    }
    if (line6 != 0) {
        strcpy(s_DynamicMessStr + 0x300, line6);
    }
    if (line7 != 0) {
        strcpy(s_DynamicMessStr + 0x380, line7);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80146364
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetSingWinScl(float scale)
{
    FLOAT_8032ea78 = scale;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CMenuPcs::GetSingWinScl()
{
    return FLOAT_8032ea78;
}

/*
 * --INFO--
 * PAL Address: 0x8014630c
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::SingWinMessHeight()
{
    float scaled = FLOAT_80332960 * FLOAT_8032ea78;
    int lineHeight = static_cast<int>(scaled);
    union {
        struct {
            u32 hi;
            u32 lo;
        } words;
        double d;
    } conv;

    conv.words.hi = 0x43300000;
    conv.words.lo = static_cast<u32>(lineHeight ^ 0x80000000U);
    if (FLOAT_8033294c <
        scaled - static_cast<float>(conv.d - DOUBLE_80332938)) {
        lineHeight += 1;
    }
    return lineHeight + 3;
}

/*
 * --INFO--
 * PAL Address: 0x8014624c
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ChkEquipPossible(int itemNo)
{
    u16 flags = *reinterpret_cast<u16*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 4);
    unsigned int raceMask = 1 << (*reinterpret_cast<u16*>(Game.m_scriptFoodBase[0] + 0x3E0) & 3);
    unsigned int genderMask = 0x10;

    if (*reinterpret_cast<s16*>(Game.m_scriptFoodBase[0] + 0x3E2) != 0) {
        genderMask = 0x20;
    }

    bool result;
    if ((flags & 0xF) != 0) {
        if ((flags & 0x30) != 0) {
            result = (((flags & 0xF) & raceMask) != 0) && (((flags & 0x30) & genderMask) != 0);
            return result ? 1 : 0;
        }
        result = ((flags & 0xF) & raceMask) != 0;
    } else {
        result = ((flags & 0x30) & genderMask) != 0;
    }

    return result ? 1 : 0;
}

/*
 * --INFO--
 * PAL Address: 0x80146190
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetEquipType(int itemNo)
{
    u16 flags = *reinterpret_cast<u16*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 4);
    int equipType = 0;

    if ((flags & 0x100) == 0) {
        if ((flags & 0x400) == 0) {
            if ((flags & 0xA00) == 0) {
                if ((flags & 0x3000) == 0) {
                    if (System.m_execParam != 0) {
                        System.Printf((char*)"%s(%d): item = %d m_equip = %08x", s_singmenu_cpp_801de8d4, 0xD3D, itemNo, flags);
                    }
                } else {
                    equipType = 3;
                }
            } else {
                equipType = 2;
            }
        } else {
            equipType = 1;
        }
    }

    return equipType;
}

/*
 * --INFO--
 * PAL Address: 0x80145ff4
 * PAL Size: 412b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetSmithItem(int itemNo)
{
    int script = Game.m_scriptFoodBase[0];

    GetItemType__8CMenuPcsFii(this, itemNo, 1);
    u16 race = *reinterpret_cast<u16*>(script + 0x3E0);
    u16 raceType = race & 3;
    int itemBase = Game.unkCFlatData0[2] + itemNo * 0x48;

    int smithItem = *reinterpret_cast<u16*>(itemBase + raceType * 2 + 0x38);
    if (smithItem != 0) {
        u16 flags = *reinterpret_cast<u16*>(Game.unkCFlatData0[2] + smithItem * 0x48 + 4);
        unsigned int raceMask = 1 << (*reinterpret_cast<u16*>(script + 0x3E0) & 3);
        unsigned int genderMask = 0x10;
        if (*reinterpret_cast<s16*>(script + 0x3E2) != 0) {
            genderMask = 0x20;
        }

        bool valid;
        if (((flags & 0xF) == 0) || ((flags & 0x30) == 0)) {
            if ((flags & 0xF) == 0) {
                valid = (flags & 0x30 & genderMask) != 0;
            } else {
                valid = (flags & 0xF & raceMask) != 0;
            }
        } else {
            valid = ((flags & 0xF & raceMask) != 0) && ((flags & 0x30 & genderMask) != 0);
        }

        if (valid) {
            return smithItem;
        }
    }

    if (raceType != 0) {
        smithItem = *reinterpret_cast<u16*>(itemBase + 0x38);
        if (smithItem != 0) {
            return smithItem;
        }
    }
    if (raceType != 1) {
        smithItem = *reinterpret_cast<u16*>(itemBase + 0x3A);
        if (smithItem != 0) {
            return smithItem;
        }
    }
    if (raceType != 2) {
        smithItem = *reinterpret_cast<u16*>(itemBase + 0x3C);
        if (smithItem != 0) {
            return smithItem;
        }
    }
    if (raceType != 3) {
        smithItem = *reinterpret_cast<u16*>(itemBase + 0x3E);
        if (smithItem != 0) {
            return smithItem;
        }
    }

    return -1;
}

/*
 * --INFO--
 * PAL Address: 0x80145f70
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetRecipeMaterial(int itemNo, CMenuPcs::MaterialInfo* materialInfo)
{
    GetItemType__8CMenuPcsFii(this, itemNo, 1);

    u8* itemBase = reinterpret_cast<u8*>(Game.unkCFlatData0[2]) + (itemNo * 0x48);

    materialInfo->m_itemNo[0] = *reinterpret_cast<u16*>(itemBase + 0x26);
    materialInfo->m_count[0] = *reinterpret_cast<u16*>(itemBase + 0x2C);
    materialInfo->m_itemNo[1] = *reinterpret_cast<u16*>(itemBase + 0x28);
    materialInfo->m_count[1] = *reinterpret_cast<u16*>(itemBase + 0x2E);
    materialInfo->m_itemNo[2] = *reinterpret_cast<u16*>(itemBase + 0x2A);
    materialInfo->m_count[2] = *reinterpret_cast<u16*>(itemBase + 0x30);
}

/*
 * --INFO--
 * PAL Address: 0x80145c84
 * PAL Size: 748b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetRaceStr(int itemNo, char* outText)
{
    unsigned short raceBits;
    unsigned int raceType;
    char* text;
    char* suffix;
    unsigned char languageId;

    GetItemType__8CMenuPcsFii(this, itemNo, 1);
    raceBits = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 4);
    outText[0] = '\0';

    languageId = static_cast<unsigned char>(Game.m_gameWork.m_languageId);
    if ((raceBits & 0xF) == 0xF) {
        text = PTR_s_Tutti_802143ec;
        if (languageId != 3) {
            if (languageId < 3) {
                if (languageId != 1 && languageId != 0) {
                    text = PTR_s_Alle_Rassen_8021430c;
                }
            } else {
                text = PTR_s_Todos_802145ac;
                if (languageId != 5 && languageId >= 5) {
                    text = PTR_DAT_8021422c;
                } else if (languageId < 5) {
                    text = PTR_DAT_802144cc;
                }
            }
        }
        strcpy(outText, text);
        return;
    }

    raceType = 0;
    if ((raceBits & 1) == 0) {
        raceType = 1;
        if ((raceBits & 2) == 0) {
            raceType = 2;
            if ((raceBits & 4) == 0) {
                raceType = 3;
                if ((raceBits & 8) == 0) {
                    raceType = 4;
                }
            }
        }
    }

    if (raceType < 4) {
        if (languageId == 3) {
            text = PTR_s_Clavat_80214110[raceType];
        } else if (languageId < 3) {
            if (languageId == 1 || languageId == 0) {
                text = PTR_s_Clavat_802140f0[raceType];
            } else {
                text = PTR_s_Clavat_80214100[raceType];
            }
        } else if (languageId == 5) {
            text = PTR_s_Clavate[raceType];
        } else if (languageId < 5) {
            text = PTR_s_Clavat_80214120[raceType];
        } else {
            text = PTR_s_Clavat_802140f0[raceType];
        }

        strcpy(outText, text);
        if (languageId == 2) {
            strcat(outText, DAT_80332958, 0x80);
        }
    }

    if ((raceBits & 0xF) != 0 && (raceBits & 0x30) != 0) {
        strcpy(outText, DAT_8033295c);
    }
    if ((raceBits & 0x30) == 0) {
        return;
    }

    suffix = 0;
    raceType = (raceBits & 0x30) >> 5;
    if (languageId == 3) {
        suffix = PTR_s_Maschio_802143e4[raceType];
    } else if (languageId < 3) {
        if (languageId != 1 && languageId != 0) {
            suffix = PTR_DAT_80214304[raceType];
        }
    } else if (languageId == 5) {
        suffix = PTR_s_Hombre_802145a4[raceType];
    } else if (languageId < 5) {
        suffix = PTR_s_Masculin_802144c4[raceType];
    }

    if (suffix == 0) {
        suffix = PTR_DAT_80214224[raceType];
    }
    strcat(outText, suffix, 0x80);
}

/*
 * --INFO--
 * PAL Address: 0x801458ec
 * PAL Size: 920b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingBar(int x, int y, int value, float alpha)
{
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

    unsigned char alphaU8 = static_cast<unsigned char>(FLOAT_80332940 * alpha);
    _GXColor color = {0xFF, 0xFF, 0xFF, alphaU8};
    GXSetChanMatColor(GX_COLOR0A0, color);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x53);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, static_cast<float>(x), static_cast<float>(y), 16.0f,
                                    FLOAT_80332948, FLOAT_8033294c, FLOAT_8033294c,
                                    FLOAT_80332934, FLOAT_80332934, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(this, 8, static_cast<float>(x + 0x60), static_cast<float>(y), 16.0f,
                                    FLOAT_80332948, FLOAT_8033294c, FLOAT_8033294c,
                                    FLOAT_80332934, FLOAT_80332934, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x54);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, static_cast<float>(x + 0x10), static_cast<float>(y),
                                    FLOAT_80332950, FLOAT_80332948, FLOAT_8033294c, FLOAT_8033294c,
                                    FLOAT_80332934, FLOAT_80332934, 0.0f);

    int tex = 0x55;
    if (value < 0x29) {
        tex = 0x59;
    } else if (value < 0x3D) {
        tex = 0x57;
    }

    int bars = value / 10 + (value >> 31);
    bars -= bars >> 31;
    if (value != bars * 10) {
        ++bars;
    }

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);
    int barY = y + 8;
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, static_cast<float>(x + 0x10), static_cast<float>(barY),
                                    4.0f, 8.0f, FLOAT_8033294c, FLOAT_8033294c,
                                    FLOAT_80332934, FLOAT_80332934, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(this, 8, static_cast<float>(x + 0x10 + bars * 8 - 4), static_cast<float>(barY),
                                    4.0f, 8.0f, FLOAT_8033294c, FLOAT_8033294c,
                                    FLOAT_80332934, FLOAT_80332934, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex + 1);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, static_cast<float>(x + 0x14), static_cast<float>(barY),
                                    static_cast<float>(bars * 8 - 8), 8.0f, FLOAT_8033294c, FLOAT_8033294c,
                                    FLOAT_80332934, FLOAT_80332934, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x801458e4
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingSetLetterAttachflg(int flag)
{
    gSingMenuForcedSelection = flag;
}

/*
 * --INFO--
 * PAL Address: 0x801458dc
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::SingGetLetterAttachflg()
{
    return gSingMenuForcedSelection;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcSingLife()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80145738
 * PAL Size: 420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingLife()
{
    unsigned int scriptFood = Game.m_scriptFoodBase[0];
    int lifeTimer = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x874);
    if (lifeTimer < 0) {
        return;
    }

    float y = FLOAT_8033291c;
    if (lifeTimer < 10) {
        int phase = lifeTimer;
        if (phase < 0) {
            phase = 0;
        } else if (phase > 10) {
            phase = 10;
        }
        y = FLOAT_80332928 * static_cast<float>(sin(FLOAT_80332920 * FLOAT_80332924 * static_cast<float>(phase))) + FLOAT_8033291c;
    } else if (lifeTimer > 0x27) {
        int phase = 10 - (lifeTimer - 0x28);
        if (phase < 0) {
            phase = 0;
        } else if (phase > 10) {
            phase = 10;
        }
        y = FLOAT_80332928 * static_cast<float>(sin(FLOAT_80332920 * FLOAT_80332924 * static_cast<float>(phase))) + FLOAT_8033291c;
    }

    int halfHearts = static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(scriptFood + 0x1A) >> 1);
    float x = FLOAT_80332918 + static_cast<float>(((8 - halfHearts) * 0x18) / 2);
    DrawHeart__8CMesMenuFffff(*reinterpret_cast<void**>(reinterpret_cast<u8*>(this) + 0x268), x, y - FLOAT_80332930, FLOAT_80332934,
                              FLOAT_80332934);
}

/*
 * --INFO--
 * PAL Address: 0x80145710
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingLifeInit(int timer)
{
    u8* self = reinterpret_cast<u8*>(this);
    if ((*reinterpret_cast<int*>(self + 0x874) > 0) && (timer == 0)) {
        *reinterpret_cast<int*>(self + 0x874) = 10;
        return;
    }
    *reinterpret_cast<int*>(self + 0x874) = timer;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingLifeResetWait()
{
	// TODO
}

static inline char* GetLanguageTableString(int index, char** englishTable, char** germanTable, char** italianTable,
                                           char** frenchTable, char** spanishTable)
{
    u8 languageId = Game.m_gameWork.m_languageId;
    if (languageId == 3) {
        return italianTable[index];
    }
    if (languageId >= 3) {
        if (languageId == 5) {
            return spanishTable[index];
        }
        if (languageId >= 5) {
            return englishTable[index];
        }
        return frenchTable[index];
    }
    if (languageId == 1) {
        return englishTable[index];
    }
    if (languageId >= 1) {
        return germanTable[index];
    }
    return englishTable[index];
}

/*
 * --INFO--
 * PAL Address: 0x80145674
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CMenuPcs::GetTribeStr(int index)
{
    return GetLanguageTableString(index, PTR_s_Clavat_802140f0, PTR_s_Clavat_80214100, PTR_s_Clavat_80214110,
                                  PTR_s_Clavat_80214120, PTR_s_Clavate);
}

/*
 * --INFO--
 * PAL Address: 0x801455d8
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CMenuPcs::GetJobStr(int index)
{
    return GetLanguageTableString(index, PTR_s_Blacksmith, PTR_s_Schmied, PTR_s_Fabbri, PTR_s_Forgeron, PTR_s_Herrero);
}

/*
 * --INFO--
 * PAL Address: 0x8014553c
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CMenuPcs::GetHairStr(int index)
{
    return GetLanguageTableString(index, PTR_s_Cowlick, PTR_s_Spitzschopf, PTR_s_Ciuffo_ribelle, gSingMenuHairTableFr, PTR_s_Remolino);
}

/*
 * --INFO--
 * PAL Address: 0x801454a0
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CMenuPcs::GetMenuStr(int index)
{
    u8 languageId = Game.m_gameWork.m_languageId;

    if (languageId == 3) {
        return gSingMenuTextTableIt[index];
    }
    if (languageId >= 3) {
        if (languageId == 5) {
            return gSingMenuTextTableEs[index];
        }
        if (languageId >= 5) {
            return gSingMenuTextTableEn[index];
        }
        return gSingMenuTextTableFr[index];
    }
    if (languageId == 1) {
        return gSingMenuTextTableEn[index];
    }
    if (languageId >= 1) {
        return gSingMenuTextTableDe[index];
    }
    return gSingMenuTextTableEn[index];
}

/*
 * --INFO--
 * PAL Address: 0x80145404
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CMenuPcs::GetAttrStr(int index)
{
    return GetLanguageTableString(index, gSingMenuAttrTableEn, gSingMenuAttrTableDe, gSingMenuAttrTableIt, gSingMenuAttrTableFr, gSingMenuAttrTableEs);
}

/*
 * --INFO--
 * PAL Address: 0x801453f4
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
u8 CMenuPcs::GetItemIcon(int index)
{
    return gSingMenuItemIconByType[index];
}
