#include "ffcc/ptrarray.h"
#include "ffcc/singmenu.h"
#include "ffcc/chara.h"
#include "ffcc/color.h"
#include "ffcc/file.h"
#include "ffcc/fontman.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/joybus.h"
#include "ffcc/memory.h"
#include "ffcc/mesmenu.h"
#include "ffcc/p_chara.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/linkage.h"
#include "ffcc/shopmenu.h"
#include "ffcc/sound.h"
extern "C" {
extern u8 gSingMenuItemIconByType[];
extern const char* gSingMenuTextTableEn[];
extern const char* gSingMenuTextTableDe[];
extern const char* gSingMenuTextTableIt[];
extern const char* gSingMenuTextTableFr[];
extern const char* gSingMenuTextTableEs[];
extern const char* gSingMenuHairTableFr[];
extern const char* gSingMenuAttrTableEn[];
extern const char* gSingMenuAttrTableDe[];
extern const char* gSingMenuAttrTableIt[];
extern const char* gSingMenuAttrTableFr[];
extern const char* gSingMenuAttrTableEs[];
}
#include "ffcc/textureman.h"
#include "ffcc/util.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <math.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h>

typedef signed short s16;
typedef unsigned char u8;

STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuStageActive) == 0x859);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuInitialized) == 0x85A);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuTextureLoadIndex) == 0x85C);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuTextureLoadState) == 0x860);

static inline CCaravanWork* SingleCaravanWork()
{
    return reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
}

struct SingMenuStaticMessageInfo
{
    int lineCount;
    s16 textIds[8];
};

struct SingMenuTextureRef
{
    int textureSetIndex;
    char* textureName;
};

struct SingMenuSoloNameTable
{
    char* entries[9];
};

extern char s_singmenu_cpp[];
extern "C" char* s_singMenuTexturePathFmt;
extern "C" char s_singMenuSubfontPathFmt[];
extern "C" char* PTR_s_Tutti_802143ec;
extern "C" char* PTR_s_Alle_Rassen_8021430c;
extern "C" char* PTR_s_Todos_802145ac;
extern "C" const char* PTR_s_Clavat_80214110[];
extern "C" {
extern const float kPppFilterScreenMin = 0.0f;
extern const float kPppFilterScreenMaxX = 640.0f;
extern const float kPppFilterScreenMaxY[2] = {448.0f, 0.0f};
const char s_Clavat_803320D8[] = "Clavat";
const char s_Lilty_803320E0[] = "Lilty";
const char s_Yuke_803320E8[] = "Yuke";
const char s_Selkie_803320F0[] = "Selkie";
const char s_Lility_803320F8[] = "Lility";
const char s_Seliky_80332100[] = "Seliky";
const char s_Clavate_80332108[] = "Clavate";
const char s_Lilti_80332110[] = "Lilti";
const char s_Yuko_80332118[] = "Yuko";
const char s_Selki_80332120[] = "Selki";
const char s_Tailor_80332128[] = "Tailor";
const char s_Farmer_80332130[] = "Farmer";
const char s_Rancher_80332138[] = "Rancher";
const char s_Miller_80332140[] = "Miller";
const char s_Schmied_80332148[] = "Schmied";
const char s_Bauer_80332150[] = "Bauer";
const char s_Moeller_80332158[] = "M\374ller";
const char s_Fischer_80332160[] = "Fischer";
const char s_Haendler_80332168[] = "H\344ndler";
const char s_Fabbri_80332170[] = "Fabbri";
const char s_Sarti_80332178[] = "Sarti";
const char s_Mugnai_80332180[] = "Mugnai";
const char s_Fermier_80332188[] = "Fermier";
const char s_Eleveur_80332190[] = "\311leveur";
const char s_Meunier_80332198[] = "Meunier";
const char s_Pecheur_803321A0[] = "P\352cheur";
const char s_Herrero_803321A8[] = "Herrero";
const char s_Sastre_803321B0[] = "Sastre";
const char s_Empty_803321B8[] = "";
const char s_Yes_803321BC[] = "Yes";
const char s_No_803321C0[] = "No";
const char s_Cancel_803321C4[] = "Cancel";
const char s_gil_803321CC[] = "gil";
const char s_Defence_803321D0[] = "Defence";
const char s_Magic_803321D8[] = "Magic";
const char s_Attack_803321E0[] = "Attack";
const char s_Defend_803321E8[] = "Defend";
const char s_Remove_803321F0[] = "Remove";
const char s_Fuse_803321F8[] = "Fuse";
const char s_Split_80332200[] = "Split";
const char s_Use_80332208[] = "Use";
const char s_Drop_8033220C[] = "Drop";
const char s_Destroy_80332214[] = "Destroy";
const char s_Male_8033221C[] = "Male";
const char s_Female_80332224[] = "Female";
const char s_All_8033222C[] = "All";
const char s_QuestionMarks_80332230[] = "???";
const char s_g_period_80332234[] = "g.";
const char s_Father_80332238[] = "Father";
const char s_Mother_80332240[] = "Mother";
const char s_Brother_80332248[] = "Brother";
const char s_Sister_80332250[] = "Sister";
const char s_Letters_80332258[] = "Letters";
const char s_Quote_80332260[] = "\"";
const char s_Send_80332264[] = "Send";
const char s_Confirm_8033226C[] = "Confirm";
const char s_Name_80332274[] = "Name:";
const char s_Gender_8033227C[] = "Gender:";
const char s_Tribe_80332284[] = "Tribe:";
const char s_Items_8033228C[] = "Items";
const char s_Equip_80332294[] = "Equip";
const char s_Money_8033229C[] = "Money";
const char s_Family_803322A4[] = "Family";
const char s_Done_803322AC[] = "Done";
const char s_Ja_803322B4[] = "Ja";
const char s_Nein_803322B8[] = "Nein";
const char s_Gil_803322C0[] = "Gil";
const char s_Staerke_803322C4[] = "St\344rke";
const char s_Abwehr_803322CC[] = "Abwehr";
const char s_Magie_803322D4[] = "Magie";
const char s_Ablegen_803322DC[] = "Ablegen";
const char s_G_803322E4[] = "G";
const char s_Vater_803322E8[] = "Vater";
const char s_Mutter_803322F0[] = "Mutter";
const char s_Bruder_803322F8[] = "Bruder";
const char s_Weiter_80332300[] = "Weiter?";
const char s_specialChar_80332308[] = "\204";
const char s_Rasse_8033230C[] = "Rasse:";
const char s_Geld_80332314[] = "Geld";
const char s_Familie_8033231C[] = "Familie";
const char s_Briefe_80332324[] = "Briefe";
const char s_Si_8033232C[] = "S\354";
const char s_Annulla_80332330[] = "Annulla";
const char s_guil_80332338[] = "guil";
const char s_Forza_80332340[] = "Forza";
const char s_Difesa_80332348[] = "Difesa";
const char s_Magia_80332350[] = "Magia";
const char s_Memorie_80332358[] = "Memorie";
const char s_Attacco_80332360[] = "Attacco";
const char s_Rimuovi_80332368[] = "Rimuovi";
const char s_Fusione_80332370[] = "Fusione";
const char s_Dividi_80332378[] = "Dividi";
const char s_Usa_80332380[] = "Usa";
const char s_Posa_80332384[] = "Posa";
const char s_Maschio_8033238C[] = "Maschio";
const char s_Femmina_80332394[] = "Femmina";
const char s_Tutti_8033239C[] = "Tutti";
const char s_Padre_803323A4[] = "Padre";
const char s_Madre_803323AC[] = "Madre";
const char s_Sorella_803323B4[] = "Sorella";
const char s_Lettere_803323BC[] = "Lettere";
const char s_con_803323C4[] = "con ";
const char s_Nome_803323CC[] = "Nome:";
const char s_Sesso_803323D4[] = "Sesso:";
const char s_Razza_803323DC[] = "Razza:";
const char s_Oggetti_803323E4[] = "Oggetti";
const char s_Tesori_803323EC[] = "Tesori";
const char s_Denaro_803323F4[] = "Denaro";
const char s_Fatto_803323FC[] = "Fatto";
const char s_Oui_80332404[] = "Oui";
const char s_Non_80332408[] = "Non";
const char s_Annuler_8033240C[] = "Annuler";
const char s_gils_80332414[] = "gils";
const char s_Force_8033241C[] = "Force";
const char s_Retirer_80332424[] = "Retirer";
const char s_Separer_8033242C[] = "S\351parer";
const char s_Jeter_80332434[] = "Jeter";
const char s_Feminin_8033243C[] = "F\351minin";
const char s_Tous_80332444[] = "Tous";
const char s_Pere_8033244C[] = "P\350re";
const char s_Mere_80332454[] = "M\350re";
const char s_Frere_8033245C[] = "Fr\350re";
const char s_Soeur_80332464[] = "S\234ur";
const char s_Lettres_8033246C[] = "Lettres";
const char s_Nom_80332474[] = "Nom:";
const char s_Sexe_8033247C[] = "Sexe:";
const char s_Tribu_80332484[] = "Tribu:";
const char s_Metier_8033248C[] = "M\351tier:";
const char s_Objets_80332494[] = "Objets";
const char s_Equiper_8033249C[] = "Equiper";
const char s_Tresors_803324A4[] = "Tr\351sors";
const char s_Gils_803324AC[] = "Gils";
const char s_Famille_803324B4[] = "Famille";
const char s_Laisser_803324BC[] = "Laisser";
const char s_Si_803324C4[] = "S\355";
const char s_guiles_803324C8[] = "guiles";
const char s_Fuerza_803324D0[] = "Fuerza";
const char s_Defensa_803324D8[] = "Defensa";
const char s_Atacar_803324E0[] = "Atacar";
const char s_Quitar_803324E8[] = "Quitar";
const char s_Separar_803324F0[] = "Separar";
const char s_Hombre_803324F8[] = "Hombre";
const char s_Mujer_80332500[] = "Mujer";
const char s_Todos_80332508[] = "Todos";
const char s_invQuestions_80332510[] = "\277\277??";
const char s_Hermano_80332518[] = "Hermano";
const char s_Hermana_80332520[] = "Hermana";
const char s_Cartas_80332528[] = "Cartas";
const char s_period_80332530[] = ".";
const char s_Nombre_80332534[] = "Nombre:";
const char s_Sexo_8033253C[] = "Sexo:";
const char s_Objetos_80332544[] = "Objetos";
const char s_Equipo_8033254C[] = "Equipo";
const char s_Tesoros_80332554[] = "Tesoros";
const char s_Dinero_8033255C[] = "Dinero";
const char s_Familia_80332564[] = "Familia";
const char s_Hecho_8033256C[] = "Hecho";
const char s_Cowlick_80332574[] = "Cowlick";
const char s_Natural_8033257C[] = "Natural";
const char s_Cap_80332584[] = "Cap";
const char s_Elegant_80332588[] = "Elegant";
const char s_Bumpy_80332590[] = "Bumpy";
const char s_Spiral_80332598[] = "Spiral";
const char s_Tulip_803325A0[] = "Tulip";
const char s_Spoon_803325A8[] = "Spoon";
const char s_Wolfie_803325B0[] = "Wolfie";
const char s_Wuschel_803325B8[] = "Wuschel";
const char s_normal_803325C0[] = "normal";
const char s_fesch_803325C8[] = "fesch";
const char s_Einhorn_803325D0[] = "Einhorn";
const char s_Kreisel_803325D8[] = "Kreisel";
const char s_Tulpe_803325E0[] = "Tulpe";
const char s_Loeffel_803325E8[] = "L\366ffel";
const char s_Haiauge_803325F0[] = "Haiauge";
const char s_Fascia_803325F8[] = "Fascia";
const char s_Secchio_80332600[] = "Secchio";
const char s_Blu_80332608[] = "Blu";
const char s_Spirale_8033260C[] = "Spirale";
const char s_Cuore_80332614[] = "Cuore";
const char s_Lupo_8033261C[] = "Lupo";
const char s_Bandana_80332624[] = "Bandana";
const char s_Lupa_8033262C[] = "Lupa";
const char s_Epi_80332634[] = "Epi";
const char s_Naturel_80332638[] = "Naturel";
const char s_Bandeau_80332640[] = "Bandeau";
const char s_Chapeau_80332648[] = "Chapeau";
const char s_Plumes_80332650[] = "Plumes";
const char s_Brune_80332658[] = "Brune";
const char s_Chatain_80332660[] = "Ch\342tain";
const char s_Cornes_80332668[] = "Cornes";
const char s_Visiere_80332670[] = "Visi\350re";
const char s_Heaume_80332678[] = "Heaume";
const char s_Masquee_80332680[] = "Masqu\351e";
const char s_Bosses_80332688[] = "Bosses";
const char s_Tulipe_80332690[] = "Tulipe";
const char s_Coeur_80332698[] = "C\234ur";
const char s_Loup_803326A0[] = "Loup";
const char s_Lynx_803326A8[] = "Lynx";
const char s_Castor_803326B0[] = "Castor";
const char s_Louve_803326B8[] = "Louve";
const char s_Hibou_803326C0[] = "Hibou";
const char s_Cinta_803326C8[] = "Cinta";
const char s_Gorra_803326D0[] = "Gorra";
const char s_Azul_803326D8[] = "Azul";
const char s_Espiral_803326E0[] = "Espiral";
const char s_Tulipan_803326E8[] = "Tulip\341n";
const char s_Cuchara_803326F0[] = "Cuchara";
const char s_Lobezna_803326F8[] = "Lobezna";
const char s_Regen_80332700[] = "Regen";
const char s_Regena_80332708[] = "Regena";
const char s_Recup_80332710[] = "R\351cup";
const char s_solo2_80332718[] = "solo2";
const char s_solo1_80332720[] = "solo1";
const char s_solo4_80332728[] = "solo4";
const char s_solo5_80332730[] = "solo5";
const char s_solo8_80332738[] = "solo8";
const char s_solo9_80332740[] = "solo9";
const char s_solo30_80332748[] = "solo30";
const char s_solo42_80332750[] = "solo42";
const char s_solo47_80332758[] = "solo47";
const char s_solo48_80332760[] = "solo48";
const char s_solo49_80332768[] = "solo49";
const char s_solo50_80332770[] = "solo50";
const char s_solo51_80332778[] = "solo51";
const char s_solo63_80332780[] = "solo63";
const char s_solo3_80332788[] = "solo3";
const char s_solo6_80332790[] = "solo6";
const char s_solo7_80332798[] = "solo7";
const char s_solo10_803327A0[] = "solo10";
const char s_solo11_803327A8[] = "solo11";
const char s_solo12_803327B0[] = "solo12";
const char s_solo13_803327B8[] = "solo13";
const char s_solo14_803327C0[] = "solo14";
const char s_solo15_803327C8[] = "solo15";
const char s_solo16_803327D0[] = "solo16";
const char s_solo17_803327D8[] = "solo17";
const char s_solo18_803327E0[] = "solo18";
const char s_solo19_803327E8[] = "solo19";
const char s_solo20_803327F0[] = "solo20";
const char s_solo21_803327F8[] = "solo21";
const char s_solo22_80332800[] = "solo22";
const char s_solo24_80332808[] = "solo24";
const char s_solo25_80332810[] = "solo25";
const char s_solo26_80332818[] = "solo26";
const char s_solo27_80332820[] = "solo27";
const char s_solo28_80332828[] = "solo28";
const char s_solo29_80332830[] = "solo29";
const char s_solo31_80332838[] = "solo31";
const char s_solo32_80332840[] = "solo32";
const char s_solo33_80332848[] = "solo33";
const char s_solo34_80332850[] = "solo34";
const char s_solo35_80332858[] = "solo35";
const char s_solo36_80332860[] = "solo36";
const char s_solo37_80332868[] = "solo37";
const char s_solo38_80332870[] = "solo38";
const char s_solo39_80332878[] = "solo39";
const char s_solo40_80332880[] = "solo40";
const char s_solo41_80332888[] = "solo41";
const char s_solo43_80332890[] = "solo43";
const char s_solo44_80332898[] = "solo44";
const char s_solo45_803328A0[] = "solo45";
const char s_solo46_803328A8[] = "solo46";
const char s_solo52_803328B0[] = "solo52";
const char s_solo53_803328B8[] = "solo53";
const char s_solo54_803328C0[] = "solo54";
const char s_solo55_803328C8[] = "solo55";
const char s_solo56_803328D0[] = "solo56";
const char s_solo57_803328D8[] = "solo57";
const char s_solo58_803328E0[] = "solo58";
const char s_solo59_803328E8[] = "solo59";
const char s_solo60_803328F0[] = "solo60";
const char s_solo61_803328F8[] = "solo61";
const char s_solo62_80332900[] = "solo62";
const char s_solo64_80332908[] = "solo64";
const char s_solo23_80332910[] = "solo23";
const char s_plural_s_80332958[] = "s";
const char s_space_8033295c[] = " ";
const char s_stand_80332a24[] = "stand";
}

extern "C" const char* PTR_s_Clavat_802140f0[];
extern "C" const char* PTR_s_Clavat_80214100[];
extern "C" const char* PTR_s_Clavate[];
extern "C" const char* PTR_s_Clavat_80214120[];
extern "C" const char* PTR_s_Maschio_802143e4[];
extern "C" const char* PTR_s_Hombre_802145a4[];
extern "C" const char* PTR_s_Masculin_802144c4[];
extern "C" const char* PTR_s_Blacksmith[];
extern "C" const char* PTR_s_Schmied[];
extern "C" const char* PTR_s_Fabbri[];
extern "C" const char* PTR_s_Forgeron[];
extern "C" const char* PTR_s_Herrero[];
extern "C" const char* PTR_s_Cowlick[];
extern "C" const char* PTR_s_Spitzschopf[];
extern "C" const char* PTR_s_Ciuffo_ribelle[];
extern "C" const char* PTR_s_Remolino[];
extern "C" {
extern char s_pcts_pctd_item_pctd_m_equip_pct08x_801DE8B0[];
extern char s_sololetter_801DE8A4[];
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
extern char s_Viehzuechter_801DD754[];
extern char s_Weisskaeppchen_801DDE90[];
extern char s_Fluegelhelm_801DDEF4[];
extern char s_Baerentatze_801DDF18[];
extern char s_Tete_nue_801DE068[];
extern char s_Elegante_801DE074[];
extern char s_Cuillere_801DE0A4[];
extern char s_Visor_Metalico_801DE118[];
extern char s_Mascara_Roja_801DE138[];
extern char s_Ojos_Tiburon_801DE188[];
extern char s_Cabeza_Buho_801DE1A8[];
extern char s_Anti_Malefice_801DE4FC[];
extern char s_Anti_Petrif_801DE50C[];
extern char s_Duree_sorts_801DE53C[];
extern char s_Portee_des_sorts_801DE554[];
extern char s_Portee_super_atq_801DE568[];
extern char s_Degats_magiq_801DE58C[];
extern char s_Rend_inebranlable_801DE59C[];
extern char s_Anti_frio_801DE5BC[];
extern char s_Danos_magicos_801DE68C[];
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
extern char s_Aufloesen_801DD908[], s_Zerstoeren_801DD92C[], s_Maennlich_801DD938[];
extern char s_Gegenstand_beifuegen_801DD99C[], s_Gil_beifuegen_801DD9B0[], s_Nichts_beifuegen_801DD9C0[];
extern char s_beifuegen_801DD9FC[], s_Bestaetigen_801DDA08[], s_Gegenstaende_801DDA44[];
extern char s_Ausruesten_801DDA50[], s_Resistance_801DDB64[], s_Defendre_801DDB88[];
extern char s_Detruire_801DDBAC[], s_la_reponse_801DDC14[], s_Envoyer_a_801DDC20[], s_Preferences_801DDC50[];
extern char s_Continuar_801DDCE0[], s_Extraer_801DDCEC[];
}
char* CMenuPcs::GetAttrStr(int index)
{
    switch (Game.m_gameWork.m_languageId) {
        case 1:
            return (char*)gSingMenuAttrTableDe[index];
        case 2:
            return (char*)gSingMenuAttrTableIt[index];
        case 3:
            return (char*)gSingMenuAttrTableFr[index];
        case 4:
            return (char*)gSingMenuAttrTableEs[index];
        default:
            return (char*)gSingMenuAttrTableEn[index];
    }
}

char* CMenuPcs::GetMenuStr(int index)
{
    switch (Game.m_gameWork.m_languageId) {
        case 1:
            return (char*)gSingMenuTextTableDe[index];
        case 2:
            return (char*)gSingMenuTextTableIt[index];
        case 3:
            return (char*)gSingMenuTextTableFr[index];
        case 4:
            return (char*)gSingMenuTextTableEs[index];
        default:
            return (char*)gSingMenuTextTableEn[index];
    }
}

char* CMenuPcs::GetHairStr(int index)
{
    switch (Game.m_gameWork.m_languageId) {
        case 1:
            return (char*)PTR_s_Spitzschopf[index];
        case 2:
            return (char*)PTR_s_Ciuffo_ribelle[index];
        case 3:
            return (char*)gSingMenuHairTableFr[index];
        case 4:
            return (char*)PTR_s_Remolino[index];
        default:
            return (char*)PTR_s_Cowlick[index];
    }
}

char* CMenuPcs::GetJobStr(int index)
{
    switch (Game.m_gameWork.m_languageId) {
        case 1:
            return (char*)PTR_s_Schmied[index];
        case 2:
            return (char*)PTR_s_Fabbri[index];
        case 3:
            return (char*)PTR_s_Forgeron[index];
        case 4:
            return (char*)PTR_s_Herrero[index];
        default:
            return (char*)PTR_s_Blacksmith[index];
    }
}

char* CMenuPcs::GetTribeStr(int index)
{
    switch (Game.m_gameWork.m_languageId) {
        case 1:
            return (char*)PTR_s_Clavat_80214100[index];
        case 2:
            return (char*)PTR_s_Clavat_80214110[index];
        case 3:
            return (char*)PTR_s_Clavat_80214120[index];
        case 4:
            return (char*)PTR_s_Clavate[index];
        default:
            return (char*)PTR_s_Clavat_802140f0[index];
    }
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
    int raceType;
    char* text;
    char* suffix;

    GetItemType(itemNo, 1);
    raceBits = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 4);
    int raceLow = raceBits & 0xF;
    int genderMask = raceBits & 0x30;
    outText[0] = '\0';

    if (raceLow == 0xF) {
        switch (Game.m_gameWork.m_languageId) {
        case 2:
            text = (char*)gSingMenuTextTableDe[19];
            break;
        case 3:
            text = (char*)gSingMenuTextTableIt[19];
            break;
        case 4:
            text = (char*)gSingMenuTextTableFr[19];
            break;
        case 5:
            text = (char*)gSingMenuTextTableEs[19];
            break;
        case 1:
        default:
            text = (char*)gSingMenuTextTableEn[19];
            break;
        }
        strcpy(outText, text);
        return;
    }

    for (raceType = 0; raceType < 4; raceType++) {
        if ((raceBits & (1 << raceType)) != 0) {
            break;
        }
    }

    if (raceType < 4) {
        switch (Game.m_gameWork.m_languageId) {
        case 2:
            text = (char*)PTR_s_Clavat_80214100[raceType];
            break;
        case 3:
            text = (char*)PTR_s_Clavat_80214110[raceType];
            break;
        case 4:
            text = (char*)PTR_s_Clavat_80214120[raceType];
            break;
        case 5:
            text = (char*)PTR_s_Clavate[raceType];
            break;
        case 1:
        default:
            text = (char*)PTR_s_Clavat_802140f0[raceType];
            break;
        }

        strcpy(outText, text);
        if (Game.m_gameWork.m_languageId == 2) {
            strcat(outText, (char*)s_plural_s_80332958);
        }
    }

    if (raceLow != 0 && genderMask != 0) {
        strcpy(outText, (char*)s_space_8033295c);
    }
    if (genderMask == 0) {
        return;
    }

    raceType = genderMask >> 5;
    switch (Game.m_gameWork.m_languageId) {
    case 2:
        suffix = (char*)gSingMenuTextTableDe[raceType + 17];
        break;
    case 3:
        suffix = (char*)gSingMenuTextTableIt[raceType + 17];
        break;
    case 4:
        suffix = (char*)gSingMenuTextTableFr[raceType + 17];
        break;
    case 5:
        suffix = (char*)gSingMenuTextTableEs[raceType + 17];
        break;
    case 1:
    default:
        suffix = (char*)gSingMenuTextTableEn[raceType + 17];
        break;
    }
    strcat(outText, suffix);
}

extern "C" const char* PTR_s_Clavat_802140f0[] = {
    s_Clavat_803320D8, s_Lilty_803320E0, s_Yuke_803320E8, s_Selkie_803320F0,
};
extern "C" const char* PTR_s_Clavat_80214100[] = {
    s_Clavat_803320D8, s_Lilty_803320E0, s_Yuke_803320E8, s_Selkie_803320F0,
};
extern "C" const char* PTR_s_Clavat_80214110[] = {
    s_Clavat_803320D8, s_Lility_803320F8, s_Yuke_803320E8, s_Seliky_80332100,
};
extern "C" const char* PTR_s_Clavat_80214120[] = {
    s_Clavat_803320D8, s_Lilty_803320E0, s_Yuke_803320E8, s_Selkie_803320F0,
};
extern "C" const char* PTR_s_Clavate[] = {
    s_Clavate_80332108, s_Lilti_80332110, s_Yuko_80332118, s_Selki_80332120,
};
extern "C" const char* PTR_s_Blacksmith[] = {
    s_Blacksmith_801DD718, s_Tailor_80332128, s_Farmer_80332130, s_Rancher_80332138,
    s_Miller_80332140, s_Fisherman_801DD724, s_Merchant_801DD730, s_Alchemist_801DD73C,
};
extern "C" const char* PTR_s_Schmied[] = {
    s_Schmied_80332148, s_Schneider_801DD748, s_Bauer_80332150, s_Viehzuechter_801DD754,
    s_Moeller_80332158, s_Fischer_80332160, s_Haendler_80332168, s_Alchemist_801DD73C,
};
extern "C" const char* PTR_s_Fabbri[] = {
    s_Fabbri_80332170, s_Sarti_80332178, s_Agricoltori_801DD760, s_Allevatori_801DD76C,
    s_Mugnai_80332180, s_Pescatori_801DD778, s_Mercanti_801DD784, s_Alchimisti_801DD790,
};
extern "C" const char* PTR_s_Forgeron[] = {
    s_Forgeron_801DD79C, s_Tailleur_801DD7A8, s_Fermier_80332188, s_Eleveur_80332190,
    s_Meunier_80332198, s_Pecheur_803321A0, s_Marchand_801DD7B4, s_Alchimiste_801DD7C0,
};
extern "C" const char* PTR_s_Herrero[] = {
    s_Herrero_803321A8, s_Sastre_803321B0, s_Campesino_801DD7CC, s_Granjero_801DD7D8,
    s_Molinero_801DD7E4, s_Pescador_801DD7F0, s_Comerciante_801DD7FC, s_Alquimista_801DD808,
};
extern "C" const char* PTR_s_Cowlick[] = {
    s_Cowlick_80332574, s_Natural_8033257C, s_Headband_801DDD60, s_Cap_80332584,
    s_Long_Hair_801DDD6C, s_Short_Hair_801DDD78, s_Dark_Coat_801DDD84, s_White_Cap_801DDD90,
    s_Bare_Head_801DDD9C, s_Horned_Helm_801DDDA8, s_Steel_Visor_801DDDB4, s_Bucket_Head_801DDDC0,
    s_Bare_Head_801DDD9C, s_Blue_Armor_801DDDCC, s_Elegant_80332588, s_Red_Mask_801DDDD8,
    s_One_Horn_801DDDE4, s_Bumpy_80332590, s_Long_Beak_801DDDF0, s_Black_Mage_801DDDFC,
    s_Spiral_80332598, s_Tulip_803325A0, s_Spoon_803325A8, s_Heart_Top_801DDE08,
    s_Wolfie_803325B0, s_Shark_Eyes_801DDE14, s_Bandanna_801DDE20, s_Raccoon_Tail_801DDE2C,
    s_Wolfie_803325B0, s_Raccoon_Tail_801DDE2C, s_Shark_Eyes_801DDE14, s_Owl_Head_801DDE3C,
};
extern "C" const char* PTR_s_Spitzschopf[] = {
    s_Spitzschopf_801DDE48, s_Wuschel_803325B8, s_Stirnband_801DDE54, s_Kopftuch_801DDE60,
    s_lange_Haare_801DDE6C, s_kurze_Haare_801DDE78, s_mittellang_801DDE84, s_Weisskaeppchen_801DDE90,
    s_normal_803325C0, s_Spitzhelm_801DDEA0, s_Eisenmaske_801DDEAC, s_Topfhelm_801DDEB8,
    s_normal_803325C0, s_Ritterin_801DDEC4, s_fesch_803325C8, s_Augenmaske_801DDED0,
    s_Einhorn_803325D0, s_Gitterhelm_801DDEDC, s_Knollhelm_801DDEE8, s_Fluegelhelm_801DDEF4,
    s_Kreisel_803325D8, s_Tulpe_803325E0, s_Loeffel_803325E8, s_Schleife_801DDF00,
    s_Wolfkopf_801DDF0C, s_Haiauge_803325F0, s_Baerentatze_801DDF18, s_Otterschwanz_801DDF24,
    s_Katzenbein_801DDF34, s_Otterschwanz_801DDF24, s_Haiauge_803325F0, s_Eulenkopf_801DDF40,
};
extern "C" const char* PTR_s_Ciuffo_ribelle[] = {
    s_Ciuffo_ribelle_801DDF4C, s_Naturale_801DDF5C, s_Fascia_803325F8, s_Cappello_801DDF68,
    s_Capelli_lunghi_801DDF74, s_Capelli_corti_801DDF84, s_Giacca_scura_801DDF94, s_Cappello_801DDF68,
    s_Pettinato_801DDFA4, s_Elmo_di_corno_801DDFB0, s_Elmo_d_acciaio_801DDFC0, s_Secchio_80332600,
    s_Pettinata_801DDFD0, s_Blu_80332608, s_Elegante_801DDFDC, s_Mascherina_801DDFE8,
    s_Monocorno_801DDFF4, s_Irregolare_801DE000, s_Becco_lungo_801DE00C, s_Mago_nero_801DE018,
    s_Spirale_8033260C, s_Tulipano_801DE024, s_Cucchiaio_801DE030, s_Cuore_80332614,
    s_Lupo_8033261C, s_Occhi_rapaci_801DE03C, s_Bandana_80332624, s_Procione_801DE04C,
    s_Lupa_8033262C, s_Procione_801DE04C, s_Occhi_rapaci_801DE03C, s_Testa_di_gufo_801DE058,
};
extern "C" const char* gSingMenuHairTableFr[] = {
    s_Epi_80332634, s_Naturel_80332638, s_Bandeau_80332640, s_Chapeau_80332648,
    s_Plumes_80332650, s_Brune_80332658, s_Chatain_80332660, s_Chapeau_80332648,
    s_Tete_nue_801DE068, s_Cornes_80332668, s_Visiere_80332670, s_Heaume_80332678,
    s_Tete_nue_801DE068, s_Heaume_80332678, s_Elegante_801DE074, s_Masquee_80332680,
    s_Unicorne_801DE080, s_Bosses_80332688, s_Long_bec_801DE08C, s_Mage_noir_801DE098,
    s_Spirale_8033260C, s_Tulipe_80332690, s_Cuillere_801DE0A4, s_Coeur_80332698,
    s_Loup_803326A0, s_Lynx_803326A8, s_Bandana_80332624, s_Castor_803326B0,
    s_Louve_803326B8, s_Castor_803326B0, s_Lynx_803326A8, s_Hibou_803326C0,
};
extern "C" const char* PTR_s_Remolino[] = {
    s_Remolino_801DE0B0, s_Natural_8033257C, s_Cinta_803326C8, s_Gorra_803326D0,
    s_Cabello_Largo_801DE0BC, s_Cabello_Corto_801DE0CC, s_Chaqueta_Osc_801DE0DC, s_Gorro_Blanco_801DE0EC,
    s_Cabeza_Aire_801DE0FC, s_Yelmo_Cuerno_801DE108, s_Visor_Metalico_801DE118, s_Cabeza_Balde_801DE128,
    s_Cabeza_Aire_801DE0FC, s_Azul_803326D8, s_Elegante_801DDFDC, s_Mascara_Roja_801DE138,
    s_Un_Cuerno_801DE148, s_Zarandeado_801DE154, s_Pico_Largo_801DE160, s_Magia_Negra_801DE16C,
    s_Espiral_803326E0, s_Tulipan_803326E8, s_Cuchara_803326F0, s_Cresta_Coraz_801DE178,
    s_Lobezna_803326F8, s_Ojos_Tiburon_801DE188, s_Bandana_80332624, s_Cola_Mapache_801DE198,
    s_Lobezna_803326F8, s_Cola_Mapache_801DE198, s_Ojos_Tiburon_801DE188, s_Cabeza_Buho_801DE1A8,
};
extern "C" const char* gSingMenuAttrTableEn[] = {
    s_Empty_803321B8, s_Resist_fire_801DE1B4, s_Resist_cold_801DE1C0, s_Resist_lightning_801DE1CC,
    s_Resist_slow_801DE1E0, s_Resist_prlysis_801DE1EC, s_Resist_poison_801DE1FC, s_Resist_curses_801DE20C,
    s_Resist_petrif_801DE21C, s_Casting_time_801DE22C, s_Charge_time_801DE23C, s_Spell_duration_801DE248,
    s_Spell_duration_801DE248, s_Resist_miasma_801DE258, s_Long_spell_range_801DE268, s_Long_focus_attks_801DE27C,
    s_Regen_80332700, s_Focus_attacks_801DE290, s_Spell_damage_801DE2A0, s_Cannot_be_stunned_801DE2B0,
};
extern "C" const char* gSingMenuAttrTableDe[] = {
    s_Empty_803321B8, s_Feuer_Res_801DE2C4, s_Eis_Resist_801DE2D0, s_Blitz_Res_801DE2E0,
    s_Gemach_R_801DE2EC, s_Stopp_Res_801DE2F8, s_Gift_Res_801DE304, s_Fluch_Res_801DE310,
    s_Stein_Res_801DE31C, s_Z_laden_801DE328, s_Sammeln_801DE334, s_Z_Wirkungszeit_801DE340,
    s_Z_Wirkungszeit_801DE340, s_Miasma_R_plus_801DE354, s_Z_Reichw_plus_801DE360, s_SA_Reichw_plus_801DE370,
    s_Regena_80332708, s_Spezialattacke_801DE380, s_Zauber_Schaden_801DE390, s_Standfest_801DE3A0,
};
extern "C" const char* gSingMenuAttrTableIt[] = {
    s_Empty_803321B8, s_Antifuoco_801DE3AC, s_Antigelo_801DE3B8, s_Antituono_801DE3C4,
    s_Antislow_801DE3D0, s_Antistop_801DE3DC, s_Antiveleno_801DE3E8, s_Antimalediz_801DE3F4,
    s_Antipietrif_801DE404, s_Carica_magia_801DE414, s_Carica_attacchi_801DE424, s_Durata_magie_801DE434,
    s_Durata_magie_801DE434, s_Antimiasma_801DE444, s_Portata_magie_801DE450, s_Portata_Super_Att_801DE460,
    s_Rigenerazione_801DE474, s_Super_Attacchi_801DE484, s_Danno_Magico_801DE494, s_Antistordimento_801DE4A4,
};
extern "C" const char* gSingMenuAttrTableFr[] = {
    s_Empty_803321B8, s_Anti_Feu_801DE4B4, s_Anti_Glace_801DE4C0, s_Anti_Foudre_801DE4CC,
    s_Anti_Somni_801DE4D8, s_Anti_Stop_801DE4E4, s_Anti_Poison_801DE4F0, s_Anti_Malefice_801DE4FC,
    s_Anti_Petrif_801DE50C, s_Tps_de_lancem_801DE51C, s_Tps_de_charge_801DE52C, s_Duree_sorts_801DE53C,
    s_Duree_sorts_801DE53C, s_Anti_Miasme_801DE548, s_Portee_des_sorts_801DE554, s_Portee_super_atq_801DE568,
    s_Recup_80332710, s_Super_attaques_801DE57C, s_Degats_magiq_801DE58C, s_Rend_inebranlable_801DE59C,
};
extern "C" const char* gSingMenuAttrTableEs[] = {
    s_Empty_803321B8, s_Anti_fuego_801DE5B0, s_Anti_frio_801DE5BC, s_Anti_rayos_801DE5C8,
    s_Anti_Freno_801DE5D4, s_Anti_Paro_801DE5E0, s_Anti_veneno_801DE5EC, s_Anti_maldic_801DE5F8,
    s_Anti_petrif_801DE608, s_Tiempo_lanzam_801DE618, s_Tiempo_carga_801DE628, s_Durac_hechiz_801DE638,
    s_Durac_hechiz_801DE638, s_Anti_miasma_801DE648, s_Alcance_hechiz_801DE654, s_Alc_superataq_801DE664,
    s_Revitalia_801DE674, s_Superataque_801DE680, s_Danos_magicos_801DE68C, s_No_se_aturde_801DE69C,
};
extern "C" {
extern int s_DynamicMess[5];
}
extern char s_DynamicMessStr[0x400];
extern "C" SingMenuStaticMessageInfo s_singleMenuStaticMessages[];

extern "C" SingMenuSoloNameTable PTR_s_solo2 = {
    {(char*)s_solo2_80332718, 0, 0, 0, 0, 0, 0, 0, 0},
};

CMenuPcs::CTmp s_singleMenuTextureTable[] = {
    {4, (char*)s_solo1_80332720},
    {4, (char*)s_solo4_80332728},
    {4, (char*)s_solo5_80332730},
    {4, (char*)s_solo8_80332738},
    {4, (char*)s_solo9_80332740},
    {4, (char*)s_solo30_80332748},
    {4, (char*)s_solo42_80332750},
    {4, (char*)s_solo47_80332758},
    {4, (char*)s_solo48_80332760},
    {4, (char*)s_solo49_80332768},
    {4, (char*)s_solo50_80332770},
    {4, (char*)s_solo51_80332778},
    {4, (char*)s_solo63_80332780},
};

extern "C" SingMenuSoloNameTable PTR_s_solo1 = {
    {(char*)s_solo1_80332720, s_sololetter_801DE8A4, 0, 0, 0, 0, 0, 0, 0},
};

extern "C" SingMenuTextureRef s_singleMenuModelTextureTable[] = {
    {5, (char*)s_solo2_80332718}, {5, (char*)s_solo3_80332788}, {5, (char*)s_solo6_80332790}, {5, (char*)s_solo7_80332798}, {5, (char*)s_solo10_803327A0},
    {5, (char*)s_solo11_803327A8}, {5, (char*)s_solo12_803327B0}, {5, (char*)s_solo13_803327B8}, {5, (char*)s_solo14_803327C0}, {5, (char*)s_solo15_803327C8},
    {5, (char*)s_solo16_803327D0}, {5, (char*)s_solo17_803327D8}, {5, (char*)s_solo18_803327E0}, {5, (char*)s_solo19_803327E8}, {5, (char*)s_solo20_803327F0},
    {5, (char*)s_solo21_803327F8}, {5, (char*)s_solo22_80332800}, {5, (char*)s_solo24_80332808}, {5, (char*)s_solo25_80332810}, {5, (char*)s_solo26_80332818},
    {5, (char*)s_solo27_80332820}, {5, (char*)s_solo28_80332828}, {5, (char*)s_solo29_80332830}, {5, (char*)s_solo31_80332838}, {5, (char*)s_solo32_80332840},
    {5, (char*)s_solo33_80332848}, {5, (char*)s_solo34_80332850}, {5, (char*)s_solo35_80332858}, {5, (char*)s_solo36_80332860}, {5, (char*)s_solo37_80332868},
    {5, (char*)s_solo38_80332870}, {5, (char*)s_solo39_80332878}, {5, (char*)s_solo40_80332880}, {5, (char*)s_solo41_80332888}, {5, (char*)s_solo43_80332890},
    {5, (char*)s_solo44_80332898}, {5, (char*)s_solo45_803328A0}, {5, (char*)s_solo46_803328A8}, {5, (char*)s_solo52_803328B0}, {5, (char*)s_solo53_803328B8},
    {5, (char*)s_solo54_803328C0}, {5, (char*)s_solo55_803328C8}, {5, (char*)s_solo56_803328D0}, {5, (char*)s_solo57_803328D8}, {5, (char*)s_solo58_803328E0},
    {5, (char*)s_solo59_803328E8}, {5, (char*)s_solo60_803328F0}, {5, (char*)s_solo61_803328F8}, {5, (char*)s_solo62_80332900}, {5, (char*)s_solo64_80332908},
    {6, (char*)s_solo23_80332910},
};

CFile::CHandle* gSingMenuAsyncFileHandle;
int gSingMenuAsyncLoadCompleted;
int gSingMenuHasScriptFoodBase;
int gSingMenuForcedSelection;
extern "C" SingMenuTextureRef s_singleMenuModelTextureTable[];
extern float gSingMenuRaceModelScales[];
extern float gSingMenuRaceModelYOffset[];
float FLOAT_8032ea78 = 1.0f;

static inline const char* GetSingWinMessage(int staticText, const char* dynamicText, int useDynamic)
{
    if (useDynamic != 0) {
        return dynamicText;
    }

    int languageId = Game.m_gameWork.m_languageId;
    switch (languageId) {
    case 2:
        return (char*)gSingMenuTextTableDe[staticText];
    case 3:
        return (char*)gSingMenuTextTableIt[staticText];
    case 4:
        return (char*)gSingMenuTextTableFr[staticText];
    case 5:
        return (char*)gSingMenuTextTableEs[staticText];
    case 1:
    default:
        return (char*)gSingMenuTextTableEn[staticText];
    }
}

static inline double SingWinUIntToDouble(unsigned int value)
{
    unsigned long long bits = 0x4330000000000000ULL | static_cast<unsigned long long>(value ^ 0x80000000U);
    return static_cast<double>(bits) - 4503601774854144.0;
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
#pragma dont_inline on
void CMenuPcs::createSingleMenu()
{
    u8* self = reinterpret_cast<u8*>(this);

    m_singleMenuPhase = 0;
    gSingMenuAsyncLoadCompleted = 0;
    if (Game.m_gameWork.m_menuStageMode == 0) {
        if (m_singleMenuStageActive != 0) {
            m_stageF0 = 0;

            CFont* font = m_fonts[4];
            if (font != 0) {
                if (font->DecRef() == 0) {
                    delete font;
                }
                m_fonts[4] = 0;
            }

            m_singleMenuStageActive = 0;
            m_singleMenuInitialized = 0;
        }
    } else {
        if (m_singleMenuStageActive == 0) {
            m_stageF0 = CharaPcs.m_viewerAnimStage;
            m_singleMenuStageActive = 1;
        }

        char path[128];
        sprintf(path, s_singMenuSubfontPathFmt, Game.GetLangString());
        loadFont(1, path, 4, -1);

        m_singleMenuInitialized = 0;
        gSingMenuForcedSelection = -1;
        gSingMenuAsyncFileHandle = 0;

        if (Game.m_gameWork.m_menuStageMode != 0) {
            loadTexture(PTR_s_solo2.entries, 4, 1, s_singleMenuTextureTable, 0x20, 0xD, 1);
            m_bonus.m_bonusBoardPtr = 0;
            m_singleFadeState = 0;
            m_singMenuState = 0;
            m_menuWindowInfo = 0;
            m_shopMenu = 0;
        }
    }
}
#pragma dont_inline reset

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

    CFont* font = m_fonts[4];
    if (font != 0) {
        if (font->DecRef() == 0) {
            delete font;
        }
        m_fonts[4] = 0;
    }

    freeTexture(4, 1, 0x20, 0xD);
    freeTexture(5, 2, 0x2D, 0x33);

    m_stageF0 = 0;
    m_singleMenuInitialized = 0;
    m_singleMenuStageActive = 0;
    gSingMenuForcedSelection = -1;

    void* ptr = reinterpret_cast<void*>(m_bonus.m_bonusBoardPtr);
    if (ptr != 0) {
        delete[] static_cast<u8*>(ptr);
        m_bonus.m_bonusBoardPtr = 0;
    }

    ptr = m_singleFadeState;
    if (ptr != 0) {
        delete static_cast<SingleFadeState*>(ptr);
        m_singleFadeState = 0;
    }

    ptr = m_singMenuState;
    if (ptr != 0) {
        delete static_cast<u8*>(ptr);
        m_singMenuState = 0;
    }

    ptr = m_menuWindowInfo;
    if (ptr != 0) {
        delete static_cast<MenuWindowInfo*>(ptr);
        m_menuWindowInfo = 0;
    }

    GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0xFFFFFF);
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

    Graphic._WaitDrawDone(s_singmenu_cpp, 0x5C2);
    Graphic.DestroyTempBuffer();

    m_stageF4 = *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<u8*>(&Graphic) + 8);
    memset(&m_singleMenuTextureLoadIndex, 0, 8);
    m_wm.m_handles[0] = 0;

    CCharaPcs::CHandle* handle = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, s_singmenu_cpp, 0x5CD) CCharaPcs::CHandle;
    m_wm.m_handles[0] = handle;

    CCharaPcs::CHandle** handlePtr = &m_wm.m_handles[0];
    (*handlePtr)->Add();
    CCaravanWork* caravanWork = SingleCaravanWork();
    int modelNo = GetModelNo(
        static_cast<int>(caravanWork->m_tribeId),
        static_cast<int>(caravanWork->m_appearanceVariant),
        static_cast<int>(caravanWork->m_genderFlag));
    (*handlePtr)->LoadModel(0, static_cast<unsigned long>(modelNo), 0, 0, -1, 0, 0);
    (*handlePtr)->m_flags |= 0x300141;
    (*handlePtr)->LoadAnim((char*)s_stand_80332a24, 0, 1, 0, ((*handlePtr)->m_charaNo / 100) * 100, -1, 0);
    (*handlePtr)->SetAnim(0, -1, -1, -1, 0);

    m_bonus.m_bonusBoardPtr = reinterpret_cast<int>(new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, s_singmenu_cpp, 0x5DD) u8[sizeof(MenuBoardEntry)]);

    MenuBoardEntry* boardEntry = reinterpret_cast<MenuBoardEntry*>(m_bonus.m_bonusBoardPtr);
    boardEntry->m_rotZ = 0.0f;
    boardEntry->m_rotY = 0.0f;
    boardEntry->m_rotX = 0.0f;
    boardEntry->m_scaleZ = 0.0f;
    boardEntry->m_scaleY = 0.0f;
    boardEntry->m_scaleX = 0.0f;
    boardEntry->m_unk3c = 1.0f;
    boardEntry->m_unk38 = 1.0f;
    boardEntry->m_unk34 = 1.0f;
    boardEntry->m_modelHandle = 0;
    boardEntry->m_effectHandle = 0;
    boardEntry->m_centerX = 0;
    boardEntry->m_centerY = 0;
    boardEntry->m_width = 0x280;
    boardEntry->m_height = 0x1C0;
    boardEntry->m_posX = 0.0f;
    boardEntry->m_posY = 0.0f;
    boardEntry->m_depth = 100.0f;
    boardEntry->m_screenX = 0;
    boardEntry->m_screenY = 0;
    boardEntry->m_screenWidth = 0x280;
    boardEntry->m_screenHeight = 0x1C0;
    boardEntry->m_centerX = static_cast<s16>(static_cast<int>(
        static_cast<double>(static_cast<float>(4.0 + static_cast<double>(96.0f) * 0.5
                + static_cast<double>(440.0f + 28.0f)) - 320.0) - 4.0));
    boardEntry->m_centerY = static_cast<s16>(static_cast<int>(
        static_cast<double>(static_cast<float>(static_cast<double>(88.0f) * 0.5
                + static_cast<double>(88.0f))) - 224.0));
    boardEntry->m_screenX = static_cast<int>(static_cast<double>(12.0f)
                                             + static_cast<double>(440.0f + 28.0f));
    boardEntry->m_screenY = static_cast<int>(80.0f);
    boardEntry->m_screenWidth = 0x48;
    boardEntry->m_screenHeight = 0x58;

    m_singleFadeState = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, s_singmenu_cpp, 0x605) SingleFadeState;
    memset(m_singleFadeState, 0, sizeof(SingleFadeState));

    m_singMenuState = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, s_singmenu_cpp, 0x609) SingMenuState;
    memset(m_singMenuState, 0, sizeof(SingMenuState));

    m_menuWindowInfo = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, s_singmenu_cpp, 0x60D) MenuWindowInfo;
    memset(m_menuWindowInfo, 0, sizeof(MenuWindowInfo));

    m_singleMenuPhase = 0;
    if (gSingMenuForcedSelection >= 0) {
        m_singleMenuMode = 8;
        gSingMenuForcedSelection = -1;
    }
    FLOAT_8032ea78 = 0.8999999761581421f;
    m_singleLifeTimer = -1;
    m_singleMenuCtrlResetFlag = 1;
    m_singleMenuInitialized = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CMenuPcs::SingMenuEnd()
{
    Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 0;
    gSingMenuHasScriptFoodBase = 0;
    gSingMenuAsyncLoadCompleted = 0;
    destroySingleMenu();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CMenuPcs::calcSingleMenu()
{
    loadTextureAsync(0, 0, 0, 0, 0, 0, 0);
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
        DrawInit();
        DrawFilter(0, 0, 0, 0xFF);
        gUtil.ClearZBufferRect(0.0f, 0.0f, 640.0f, 448.0f);
        DrawInit();

        char menuType = SingleCaravanWork()->m_shopRequestState;
        if (menuType == 1) {
            if (m_shopMenu != 0) {
                m_shopMenu->Draw();
            }
        } else if ((menuType == 2) && (m_shopMenu != 0)) {
            m_shopMenu->Draw();
        }

        if ((gSingMenuHasScriptFoodBase != 0) && (m_singleFadeState->done != 0)) {
            Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 0;
            Graphic._WaitDrawDone(s_singmenu_cpp, 0x62B);
            m_singleMenuInitialized = 0;

            if (gSingMenuAsyncFileHandle != 0) {
                File.Close(gSingMenuAsyncFileHandle);
                gSingMenuAsyncFileHandle = 0;
            }

            freeTexture(5, 2, 0x2D, 0x33);

            if (m_wm.m_handles[0] != 0) {
                delete m_wm.m_handles[0];
                m_wm.m_handles[0] = 0;
            }

            if (m_bonus.m_bonusBoardPtr != 0) {
                delete[] static_cast<u8*>(reinterpret_cast<void*>(m_bonus.m_bonusBoardPtr));
                m_bonus.m_bonusBoardPtr = 0;
            }

            if (m_singMenuState != 0) {
                delete[] reinterpret_cast<u8*>(m_singMenuState);
                m_singMenuState = 0;
            }

            if (m_singleFadeState != 0) {
                delete m_singleFadeState;
                m_singleFadeState = 0;
            }

            if (m_menuWindowInfo != 0) {
                delete m_menuWindowInfo;
                m_menuWindowInfo = 0;
            }

            m_stageF4->heapWalker(-1, 0, 0xFFFFFFFF);
            Graphic.CreateTempBuffer();
            m_stageF4 = 0;
            m_singleMenuCtrlResetFlag = 0;
            Joybus.SetCtrlMode(0, 0);
        }

        if (gSingMenuHasScriptFoodBase != 0) {
            return;
        }

        s16 mode = m_singleMenuPhase;
        switch (mode) {
        case 1:
            SingleDrawCtrl();
            return;
        case 0:
        {
            SingleFadeState* fadeState = m_singleFadeState;
            int count = fadeState->count;
            SingleFadeEntry* entry = fadeState->entries;
            for (int i = 0; i < count; i++) {
                if ((i == 0) || (m_singleMenuMode != 8)) {
                    if (i == 0) {
                        float alpha = entry->alpha;
                        DrawInit();
                        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
                        MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

                        _GXColor color = {0xFF, 0xFF, 0xFF, static_cast<u8>(255.0f * alpha)};
                        GXSetChanMatColor(GX_COLOR0A0, color);

                        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x20));
                        MenuPcs.DrawRect(0, 0.0f, 0.0f, 640.0f,
                                                         64.0f, 0.0f, 0.0f,
                                                         1.0f, 1.0f, 0.0f);
                        MenuPcs.DrawRect(4, 0.0f, 384.0f, 640.0f,
                                                         64.0f, 0.0f, 0.0f,
                                                         1.0f, 1.0f, 0.0f);

                        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x28));
                        unsigned int step = 0x20;
                        for (unsigned int y = 0x40; y < 0x180; y += step) {
                            if ((0x180 - y) < step) {
                                step = 0x180 - y;
                            }
                            MenuPcs.DrawRect(0, 0.0f, static_cast<float>(y),
                                                             640.0f, static_cast<float>(step),
                                                             0.0f, 0.0f, 1.0f,
                                                             1.0f, 0.0f);
                        }
                    } else if (i == 1) {
                        float alpha = entry->alpha;
                        DrawInit();
                        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
                        MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

                        _GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
                        GXSetChanMatColor(GX_COLOR0A0, color);
                        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x21));
                        MenuPcs.DrawRect(0, -(176.0f * alpha - 208.0f),
                                                         24.0f, 176.0f, 288.0f,
                                                         0.0f, 0.0f, alpha, 1.0f,
                                                         0.0f);
                        MenuPcs.DrawRect(8, 224.0f, 24.0f, 176.0f,
                                                         288.0f, 0.0f, 0.0f, alpha,
                                                         1.0f, 0.0f);
                    } else if (i == 2) {
                        DrawSingleStat(entry->alpha);
                    } else {
                        DrawSingleHelpWim(entry->alpha);
                    }
                }
                ++entry;
            }
            return;
        }
        case 2:
        {
            SingleFadeState* fadeState = m_singleFadeState;
            int count = fadeState->count;
            SingleFadeEntry* entry = fadeState->entries;
            for (int i = 0; i < count; i++) {
                if ((i == 0) || (m_singleMenuMode != 8)) {
                    if (i == 0) {
                        float alpha = entry->alpha;
                        DrawInit();
                        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
                        MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

                        _GXColor color = {0xFF, 0xFF, 0xFF, static_cast<u8>(255.0f * alpha)};
                        GXSetChanMatColor(GX_COLOR0A0, color);

                        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x20));
                        MenuPcs.DrawRect(0, 0.0f, 0.0f, 640.0f,
                                                         64.0f, 0.0f, 0.0f,
                                                         1.0f, 1.0f, 0.0f);
                        MenuPcs.DrawRect(4, 0.0f, 384.0f, 640.0f,
                                                         64.0f, 0.0f, 0.0f,
                                                         1.0f, 1.0f, 0.0f);

                        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x28));
                        unsigned int step = 0x20;
                        for (unsigned int y = 0x40; y < 0x180; y += step) {
                            if ((0x180 - y) < step) {
                                step = 0x180 - y;
                            }
                            MenuPcs.DrawRect(0, 0.0f, static_cast<float>(y),
                                                             640.0f, static_cast<float>(step),
                                                             0.0f, 0.0f, 1.0f,
                                                             1.0f, 0.0f);
                        }
                    } else if (i == 1) {
                        float alpha = entry->alpha;
                        DrawInit();
                        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
                        MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

                        _GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
                        GXSetChanMatColor(GX_COLOR0A0, color);
                        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x21));
                        MenuPcs.DrawRect(0, -(176.0f * alpha - 208.0f),
                                                         24.0f, 176.0f, 288.0f,
                                                         0.0f, 0.0f, alpha, 1.0f,
                                                         0.0f);
                        MenuPcs.DrawRect(8, 224.0f, 24.0f, 176.0f,
                                                         288.0f, 0.0f, 0.0f, alpha,
                                                         1.0f, 0.0f);
                    } else if (i == 2) {
                        DrawSingleStat(entry->alpha);
                    } else {
                        DrawSingleHelpWim(entry->alpha);
                    }
                }
                ++entry;
            }
            return;
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
    gSingMenuHasScriptFoodBase = static_cast<int>(SingleCaravanWork()->m_shopRequestState != 0);
    if (Game.m_gameWork.m_menuStageMode == 0) {
        if (m_singleMenuStageActive == 0) {
            return;
        }

        m_stageF0 = 0;
        m_singleMenuStageActive = 0;
        m_singleMenuInitialized = 0;
        return;
    }

    if (m_singleMenuStageActive == 0) {
        createSingleMenu();
    }
    if (Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag == 0) {
        return;
    }
    if (m_singleMenuInitialized == 0) {
        SingMenuInit();
    }

    if (SingleCaravanWork()->m_shopRequestState == 0) {
        int loadIndex = m_singleMenuTextureLoadIndex;
        if (loadIndex < 2) {
            if (m_singleMenuTextureLoadState == 0) {
                char path[260];
                const char* language = Game.GetLangString();
                sprintf(path, s_singMenuTexturePathFmt, language, PTR_s_solo1.entries[loadIndex]);
                gSingMenuAsyncFileHandle = File.Open(path, 0, CFile::PRI_LOW);
                File.ReadASync(gSingMenuAsyncFileHandle);
                m_singleMenuTextureLoadState = m_singleMenuTextureLoadState + 1;
            } else if (m_singleMenuTextureLoadState == 1) {
                if (!File.IsCompleted(gSingMenuAsyncFileHandle)) {
                    gSingMenuAsyncLoadCompleted = 0;
                    goto post_texture_load;
                }

                CTextureSet* textureSet = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, s_singmenu_cpp, 0x748) CTextureSet;
                m_textureSets[loadIndex + 5] = textureSet;

                textureSet->Create(File.m_readBuffer, Game.m_gameWork.m_menuStageMode != 0 ? m_stageF4 : m_menuStage, 0, 0, 0, 0);
                File.Close(gSingMenuAsyncFileHandle);
                gSingMenuAsyncFileHandle = 0;
                m_singleMenuTextureLoadState = 0;
                m_singleMenuTextureLoadIndex = m_singleMenuTextureLoadIndex + 1;
            }

            if (m_singleMenuTextureLoadIndex < 2) {
                gSingMenuAsyncLoadCompleted = 0;
            } else {
                SingMenuTextureRef* mapping = s_singleMenuModelTextureTable;
                for (int i = 0; i < 0x33; i++) {
                    CTextureSet* set = m_textureSets[mapping->textureSetIndex];
                    int texIdx = set->Find(mapping->textureName);
                    CTexture* tex = set->GetTexture(static_cast<unsigned long>(texIdx));
                    m_textures[i + 45] = tex;
                    tex->AddRef();
                    ++mapping;
                }
                gSingMenuAsyncLoadCompleted = 1;
            }
        } else {
            gSingMenuAsyncLoadCompleted = 1;
        }
    }

post_texture_load:
    if (m_singleFadeState->done != 0) {
        m_singleMenuPhase = m_singleMenuPhase + 1;
        m_singleFadeState->done = 0;
        m_singleFadeState->active = 0;
        m_singMenuState->initialized = 0;
        m_singMenuState->closeRequested = 0;
        m_singMenuState->stepState = 0;
        m_singMenuState->frame = 0;
    }

    char menuKind = SingleCaravanWork()->m_shopRequestState;
    if (menuKind == 1) {
        if (m_shopMenu == 0) {
            CreateShopMenu();
        } else {
            m_shopMenu->Calc();
        }
    } else if (menuKind == 2) {
        if (m_shopMenu == 0) {
            CreateSmithMenu();
        } else {
            m_shopMenu->Calc();
        }
    }

    if (gSingMenuHasScriptFoodBase == 0) {
        s16 state = m_singleMenuPhase;
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
inline void CMenuPcs::SingCalcChara(float frameStep)
{
    CChara::CModel* model = m_wm.m_handles[0]->m_model;

    if (model->m_animEnd < model->m_curFrame) {
        model->AddFrame(frameStep);
    } else {
        model->SetFrame(0.0f);
    }

    unsigned short modelScaleIndex = SingleCaravanWork()->m_tribeId;
    float modelScale = gSingMenuRaceModelScales[modelScaleIndex];
    Mtx scaleMtx;
    PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
    scaleMtx[1][3] = gSingMenuRaceModelYOffset[modelScaleIndex];
    scaleMtx[0][3] = 0.0f;
    scaleMtx[2][3] = 0.0f;

    model->m_flags10C = (model->m_flags10C & 0x7F) | 0x80;
    model->SetMatrix(scaleMtx);
    model->CalcMatrix();
    model->CalcSkin();
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
    DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x20));
    MenuPcs.DrawRect(0, 0.0f, 0.0f, 640.0f, 64.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(4, 0.0f, 384.0f, 640.0f, 64.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x28));
    int y = 64;
    int sliceHeight = 32;
    while (y < 384) {
        if ((384 - y) < sliceHeight) {
            sliceHeight = 384 - y;
        }

        MenuPcs.DrawRect(0, 0.0f, static_cast<float>(y), 640.0f, static_cast<float>(sliceHeight), 0.0f,
                                         0.0f, 1.0f, 1.0f, 0.0f);
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
    unsigned int languageId = Game.m_gameWork.m_languageId;

    DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x26));
    MenuPcs.DrawRect(0, 440.0f, 0.0f, 152.0f, 40.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(4, 440.0f, 408.0f, 152.0f, 40.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x29));
    for (float y = 40.0f; y < 408.0f; ) {
        float sliceHeight = 32.0f;
        if ((408.0f - y) < sliceHeight) {
            sliceHeight = 408.0f - y;
        }
        MenuPcs.DrawRect(0, 440.0f, y, 640.0f, sliceHeight,
                                         0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        y += sliceHeight;
    }

    color.a = static_cast<u8>(255.0f * static_cast<float>(0.5) * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x22));

    unsigned short charaNo = SingleCaravanWork()->m_tribeId;
    float iconStep = 216.0f;
    float texU = static_cast<float>(charaNo & 1) * iconStep;
    float texV = static_cast<float>(charaNo >> 1) * iconStep;
    MenuPcs.DrawRect(0, 440.0f - 32.0f, 176.0f, iconStep, iconStep,
                                     texU, texV, 1.0f, 1.0f, 0.0f);

    color.a = static_cast<u8>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x2A));
    MenuPcs.DrawRect(0, 440.0f + 28.0f, 88.0f, 96.0f, 88.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    DrawInit();
    SetProjection(0);
    SetLight(1);
    m_wm.m_handles[0]->m_model->m_lightAlpha = alpha;
    m_wm.m_handles[0]->Draw(5);
    RestoreProjection();

    DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
    color.a = static_cast<u8>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x2A));
    MenuPcs.DrawRect(0, 440.0f + 28.0f, 128.0f, 96.0f, 48.0f,
                                     0.0f, 88.0f, 1.0f, 1.0f, 0.0f);

    DrawInit();
    CFont* font = m_fonts[0];
    font->SetMargin(0.0f);
    font->SetShadow(1);
    font->SetScale(0.8999999761581421f);

    _GXColor fontColor = {0xFF, 0xFF, 0xFF, static_cast<u8>(255.0f * alpha)};
    font->SetColor(fontColor);
    font->DrawInit();

    CCaravanWork* caravanWork = SingleCaravanWork();
    char* charaName = reinterpret_cast<char*>(caravanWork->m_name);
    float titleWidth = static_cast<float>(font->GetWidth(charaName));
    float titleX = 440.0f + (152.0f - titleWidth) * static_cast<float>(0.5);
    font->SetTlut(0x12);
    font->SetPosX(titleX);
    font->SetPosY(53.0f);
    font->Draw(charaName);

    font->SetTlut(0x17);
    font->SetPosX(titleX);
    font->SetPosY(52.0f);
    font->Draw(charaName);

    font->SetTlut(0x15);
    float y = 184.0f;
    for (int i = 0; i < 4; i++) {
        font->SetPosX(440.0f);
        font->SetPosY(y - 5.0f);

        char* label;
        if (languageId == 3) {
            label = (char*)gSingMenuTextTableIt[i + 5];
        } else if (languageId < 3) {
            if ((languageId == 0) || (languageId == 1)) {
                label = (char*)gSingMenuTextTableEn[i + 5];
            } else {
                label = (char*)gSingMenuTextTableDe[i + 5];
            }
        } else if (languageId == 5) {
            label = (char*)gSingMenuTextTableEs[i + 5];
        } else if (languageId > 4) {
            label = (char*)gSingMenuTextTableEn[i + 5];
        } else {
            label = (char*)gSingMenuTextTableFr[i + 5];
        }

        if ((languageId == 2) && (i == 3)) {
            font->SetScaleX(0.7199999690055847f);
            font->SetScaleY(0.8999999761581421f);
        } else {
            font->SetScaleX(0.8999999761581421f);
        }
        font->Draw(label);

        font->renderFlags = (font->renderFlags & 0xEF) | 0x10;
        if (languageId == 2) {
            font->SetMargin(-5.0f);
            font->SetScaleX(0.7199999690055847f);
            font->SetScaleY(0.8999999761581421f);
        } else {
            font->SetMargin(-3.0f);
            font->SetScale(0.8999999761581421f);
        }

        unsigned short stat;
        if (i == 0) {
            stat = caravanWork->m_strength;
        } else if (i == 1) {
            stat = caravanWork->m_defense;
        } else if (i == 2) {
            stat = caravanWork->m_magic;
        } else {
            stat = caravanWork->m_progressValue;
        }

        char valueText[36];
        sprintf(valueText, "%d", stat);
        float valueW = static_cast<float>(font->GetWidth(valueText));
        font->SetPosX(592.0f - valueW);
        font->Draw(valueText);

        font->renderFlags &= 0xEF;
        font->SetMargin(1.0f);
        y += 36.0f;
    }

    font->renderFlags &= 0xEF;
    font->SetMargin(1.0f);
    DrawInit();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleCrescent(float scaleX, float alpha)
{
    DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x21));
    MenuPcs.DrawRect(0,
                                    -(176.0f * scaleX - 208.0f), 24.0f,
                                    176.0f, 288.0f,
                                    0.0f, 0.0f,
                                    scaleX, 1.0f, 0.0f);
    MenuPcs.DrawRect(8,
                                    224.0f, 24.0f,
                                    176.0f, 288.0f,
                                    0.0f, 0.0f,
                                    scaleX, 1.0f, 0.0f);
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
    if (m_singleFadeState->active == 0) {
        Sound.PlaySe(0xE, 0x40, 0x7F, 0);
        memset(m_singleFadeState, 0, sizeof(SingleFadeState));

        m_singleFadeState->entries[0].startFrame = 0;
        m_singleFadeState->entries[0].duration = 10;
        m_singleFadeState->entries[1].startFrame = (m_singleMenuMode == 8) ? 10 : 0;
        m_singleFadeState->entries[1].duration = 10;
        m_singleFadeState->entries[2].startFrame = (m_singleMenuMode == 8) ? 10 : 0;
        m_singleFadeState->entries[2].duration = 10;
        m_singleFadeState->entries[3].startFrame = (m_singleMenuMode == 8) ? 10 : 0;
        m_singleFadeState->entries[3].duration = 10;

        m_singleFadeState->count = 4;
        m_singleFadeState->done = 0;
        m_singleFadeState->active = 1;
    }

    int completed = 0;
    m_singMenuState->frame = m_singMenuState->frame + 1;

    int count = static_cast<int>(m_singleFadeState->count);
    SingleFadeEntry* entry = m_singleFadeState->entries;
    int frame = static_cast<int>(m_singMenuState->frame);
    if (0 < count) {
        do {
            if (entry->startFrame <= frame) {
                if (frame < entry->startFrame + entry->duration) {
                    entry->elapsed = entry->elapsed + 1;
                    entry->alpha = static_cast<float>((1.0 / (double)entry->duration) *
                                                      (double)entry->elapsed);
                } else {
                    completed = completed + 1;
                    entry->alpha = 1.0f;
                }
            }
            entry = entry + 1;
            count = count - 1;
        } while (count != 0);
    }

    if (m_wm.m_handles[0]->m_model->m_animEnd < m_wm.m_handles[0]->m_model->m_time) {
        m_wm.m_handles[0]->m_model->SetFrame(0.0f);
    } else {
        m_wm.m_handles[0]->m_model->AddFrame(1.0f);
    }

    unsigned short modelScaleIndex = SingleCaravanWork()->m_tribeId;
    float modelScale = gSingMenuRaceModelScales[modelScaleIndex];
    Mtx scaleMtx;
    PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
    scaleMtx[1][3] = gSingMenuRaceModelYOffset[modelScaleIndex];
    scaleMtx[0][3] = 0.0f;
    scaleMtx[2][3] = 0.0f;

    m_wm.m_handles[0]->m_model->m_flags10C = (m_wm.m_handles[0]->m_model->m_flags10C & 0x7F) | 0x80;
    m_wm.m_handles[0]->m_model->SetMatrix(scaleMtx);
    m_wm.m_handles[0]->m_model->CalcMatrix();
    m_wm.m_handles[0]->m_model->CalcSkin();

    if (m_singleFadeState->count == completed) {
        m_singleFadeState->done = 1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CMenuPcs::SingleDrawFadeIn()
{
    SingleFadeState* fadeState = m_singleFadeState;
    if (fadeState == 0) {
        return;
    }

    DrawSingleBase(fadeState->entries[0].alpha);
    if (m_singleMenuMode == 8) {
        return;
    }

    DrawSingleCrescent(fadeState->entries[1].alpha, fadeState->entries[1].alpha);
    DrawSingleStat(fadeState->entries[2].alpha);
    DrawSingleHelpWim(fadeState->entries[3].alpha);
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
    if (m_singleFadeState->active == 0) {
        Sound.PlaySe(0xF, 0x40, 0x7F, 0);
        memset(m_singleFadeState, 0, sizeof(SingleFadeState));

        m_singleFadeState->entries[0].startFrame = (m_singleMenuMode == 8) ? 10 : 0;
        m_singleFadeState->entries[0].duration = 10;
        m_singleFadeState->entries[1].startFrame = 0;
        m_singleFadeState->entries[1].duration = 10;
        m_singleFadeState->entries[2].startFrame = 0;
        m_singleFadeState->entries[2].duration = 10;
        m_singleFadeState->entries[3].startFrame = 0;
        m_singleFadeState->entries[3].duration = 10;

        m_singleFadeState->count = 4;
        m_singleFadeState->done = 0;
        m_singleFadeState->active = 1;
    }

    int completed = 0;
    ++m_singMenuState->frame;

    int count = static_cast<int>(m_singleFadeState->count);
    SingleFadeEntry* entry = m_singleFadeState->entries;
    int frame = static_cast<int>(m_singMenuState->frame);
    if (0 < count) {
        do {
            if (frame < entry->startFrame) {
                entry->alpha = 1.0f;
            } else if (frame < entry->startFrame + entry->duration) {
                entry->elapsed = entry->elapsed + 1;
                entry->alpha =
                    static_cast<float>(-((1.0 / static_cast<double>(entry->duration)) *
                                          static_cast<double>(entry->elapsed) - 1.0));
            } else {
                completed = completed + 1;
                entry->alpha = 0.0f;
            }
            entry = entry + 1;
            count = count - 1;
        } while (count != 0);
    }

    if (m_wm.m_handles[0]->m_model->m_animEnd < m_wm.m_handles[0]->m_model->m_time) {
        m_wm.m_handles[0]->m_model->SetFrame(0.0f);
    } else {
        m_wm.m_handles[0]->m_model->AddFrame(1.0f);
    }

    unsigned short modelScaleIndex = SingleCaravanWork()->m_tribeId;
    float modelScale = gSingMenuRaceModelScales[modelScaleIndex];
    Mtx scaleMtx;
    PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
    scaleMtx[1][3] = gSingMenuRaceModelYOffset[modelScaleIndex];
    scaleMtx[0][3] = 0.0f;
    scaleMtx[2][3] = 0.0f;

    m_wm.m_handles[0]->m_model->m_flags10C = (m_wm.m_handles[0]->m_model->m_flags10C & 0x7F) | 0x80;
    m_wm.m_handles[0]->m_model->SetMatrix(scaleMtx);
    m_wm.m_handles[0]->m_model->CalcMatrix();
    m_wm.m_handles[0]->m_model->CalcSkin();

    if (m_singleFadeState->count == completed) {
        m_singleFadeState->done = 1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CMenuPcs::SingleDrawFadeOut()
{
    SingleFadeState* fadeState = m_singleFadeState;
    if (fadeState == 0) {
        return;
    }

    DrawSingleBase(fadeState->entries[0].alpha);
    if (m_singleMenuMode == 8) {
        return;
    }

    DrawSingleCrescent(fadeState->entries[1].alpha, fadeState->entries[1].alpha);
    DrawSingleStat(fadeState->entries[2].alpha);
    DrawSingleHelpWim(fadeState->entries[3].alpha);
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

    SingMenuState* state = m_singMenuState;
    if ((m_singleMenuCtrlResetFlag != 0) && (state->stepState != 0)) {
        m_singleMenuCtrlResetFlag = 0;
    }

    int result = 0;
    if (m_wm.m_handles[0]->m_model->m_animEnd < m_wm.m_handles[0]->m_model->m_time) {
        m_wm.m_handles[0]->m_model->SetFrame(0.0f);
    } else {
        m_wm.m_handles[0]->m_model->AddFrame(1.0f);
    }

    unsigned short modelScaleIndex = SingleCaravanWork()->m_tribeId;
    float modelScale = gSingMenuRaceModelScales[modelScaleIndex];
    Mtx scaleMtx;
    PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
    scaleMtx[1][3] = gSingMenuRaceModelYOffset[modelScaleIndex];
    scaleMtx[0][3] = 0.0f;
    scaleMtx[2][3] = 0.0f;

    m_wm.m_handles[0]->m_model->m_flags10C = (m_wm.m_handles[0]->m_model->m_flags10C & 0x7F) | 0x80;
    m_wm.m_handles[0]->m_model->SetMatrix(scaleMtx);
    m_wm.m_handles[0]->m_model->CalcMatrix();
    m_wm.m_handles[0]->m_model->CalcSkin();

    switch (m_singleMenuMode) {
    case 0: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            CmdOpen();
        } else if (proc == 1) {
            result = CmdCtrl();
        } else {
            result = CmdClose();
        }
        break;
    }
    case 1: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = ItemOpen();
        } else if (proc == 1) {
            result = ItemCtrl();
        } else {
            result = ItemClose();
        }
        if ((m_singleLifeTimer >= 0) && (++m_singleLifeTimer, m_singleLifeTimer >= 0x32)) {
            m_singleLifeTimer = -1;
        }
        break;
    }
    case 2: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = EquipOpen();
        } else if (proc == 1) {
            EquipCtrl();
        } else {
            result = EquipClose();
        }
        break;
    }
    case 3: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = ArtiOpen();
        } else if (proc == 1) {
            result = ArtiCtrl();
        } else {
            result = ArtiClose();
        }
        break;
    }
    case 4: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = TmpArtiOpen();
        } else if (proc == 1) {
            result = TmpArtiCtrl();
        } else {
            result = TmpArtiClose();
        }
        break;
    }
    case 5: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = MoneyOpen();
        } else if (proc == 1) {
            result = MoneyCtrl();
        } else {
            result = MoneyClose();
        }
        break;
    }
    case 6: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = FavoOpen();
        } else if (proc == 1) {
            result = FavoCtrl();
        } else {
            result = FavoClose();
        }
        break;
    }
    case 7: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = CompaOpen();
        } else if (proc == 1) {
            CompaCtrl();
        } else {
            result = CompaClose();
        }
        break;
    }
    case 8: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = LetterOpen();
        } else if (proc == 1) {
            result = LetterCtrl();
        } else {
            result = LetterClose();
        }
        break;
    }
    case 9: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = MLstOpen();
        } else if (proc == 1) {
            result = MLstCtrl();
        } else {
            result = MLstClose();
        }
        break;
    }
    }

    reinterpret_cast<CMesMenu*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(&MenuPcs) + 0x268))->CalcHeart();
    m_singMenuState->result = result;

    bool hasInput = (Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1);
    unsigned short press;
    if (hasInput) {
        press = 0;
    } else {
        __cntlzw((unsigned int)Pad.m_debugPadPort);
        press = Pad.GetPadInputs()[0].buttonDown[0];
    }

    if ((press & 0x800) != 0) {
        m_singleFadeState->done = 1;
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
    DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
    _GXColor white;
    white.r = 0xFF;
    white.g = 0xFF;
    white.b = 0xFF;
    white.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, white);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x20));
    MenuPcs.DrawRect(0, 0.0f, 0.0f, 640.0f, 64.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(4, 0.0f, 384.0f, 640.0f, 64.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x28));
    unsigned int step = 0x20;
    for (unsigned int y = 0x40; y < 0x180; y += step) {
        if ((0x180 - y) < step) {
            step = 0x180 - y;
        }

        MenuPcs.DrawRect(0, 0.0f, static_cast<float>(y), 640.0f,
                                         static_cast<float>(step), 0.0f, 0.0f,
                                         1.0f, 1.0f, 0.0f);
    }

    if (m_singleMenuMode != 8) {
        DrawInit();
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
        GXSetChanMatColor(GX_COLOR0A0, white);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x21));
        MenuPcs.DrawRect(0, 32.0f, 24.0f, 176.0f, 288.0f,
                                         0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        MenuPcs.DrawRect(8, 224.0f, 24.0f, 176.0f, 288.0f,
                                         0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        DrawSingleStat(1.0f);
        DrawSingleHelpWim(1.0f);
    }

    if (gSingMenuAsyncLoadCompleted == 0) {
        return;
    }

    switch (m_singleMenuMode) {
    case 0:
        CmdDraw();
        break;
    case 1:
        ItemDraw();
        break;
    case 2:
        EquipDraw();
        break;
    case 3:
        ArtiDraw();
        break;
    case 4:
        TmpArtiDraw();
        break;
    case 5:
        MoneyDraw();
        break;
    case 6:
        FavoDraw();
        break;
    case 7:
        CompaDraw();
        break;
    case 8:
        LetterDraw();
        break;
    case 9:
        MLstDraw();
        break;
    }

    SingMenuState* state = m_singMenuState;
    if (state->result == 0) {
        return;
    }

    if (state->stepState < 2) {
        ++state->stepState;
        state->frame = 0;
        state->initialized = 0;
        state->result = 0;
        return;
    }

    s16 previousMode = 0;
    if (state->closeRequested != 0) {
        s16 mode = m_singleMenuMode;
        if (mode == 9) {
            m_singleFadeState->done = 1;
        } else {
            m_singleMenuMode = 9;
            previousMode = mode;
        }
    } else {
        s16 mode = m_singleMenuMode;
        if (mode == 9) {
            m_singleMenuMode = state->selectedIndex;
        } else if ((mode == 8) && (gSingMenuForcedSelection >= 0)) {
            m_singleMenuMode = static_cast<s16>(gSingMenuForcedSelection);
        } else if ((mode == 8) || (gSingMenuForcedSelection < 0)) {
            if (state->cursorMove < 1) {
                --m_singleMenuMode;
                if (m_singleMenuMode < 0) {
                    m_singleMenuMode = 8;
                }
            } else {
                ++m_singleMenuMode;
                if (m_singleMenuMode > 8) {
                    m_singleMenuMode = 0;
                }
            }
        } else {
            m_singleMenuMode = 8;
        }
    }

    memset(state, 0, sizeof(SingMenuState));
    FLOAT_8032ea78 = 0.8999999761581421f;
    state->selectedIndex = previousMode;
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
    DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int alphaInt = static_cast<int>(255.0f * alpha);
    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(alphaInt);
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x23));
    MenuPcs.DrawRect(0, 32.0f, 312.0f, 32.0f, 32.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(8, 576.0f, 312.0f, 32.0f, 32.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(4, 32.0f, 384.0f, 32.0f, 32.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(0xC, 576.0f, 384.0f, 32.0f, 32.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x27));
    MenuPcs.DrawRect(0, 64.0f, 312.0f, 512.0f, 32.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(4, 64.0f, 384.0f, 512.0f, 32.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x24));
    MenuPcs.DrawRect(0, 32.0f, 344.0f, 32.0f, 40.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(8, 576.0f, 344.0f, 32.0f, 40.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x2B));
    MenuPcs.DrawRect(8, 64.0f, 344.0f, 512.0f, 40.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);
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
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x25));
    if (rawIcon == 0) {
        iconNo = static_cast<int>(gSingMenuItemIconByType[iconNo]);
    }

    int row = iconNo / 8;
    int col = iconNo % 8;

    MenuPcs.DrawRect(0, static_cast<float>(posX), static_cast<float>(posY), 32.0f, 32.0f,
        static_cast<float>(col * 0x20), static_cast<float>(row * 0x20), uvScale, uvScale, 0.0f);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawShadowFont(CFont* font, char* text, float x, float y, int tlut, int shadowTlut)
{
    font->SetTlut(shadowTlut);
    font->SetPosX(1.0f + x);
    font->SetPosY((1.0f + y) - 4.0f);
    font->Draw(text);

    font->SetTlut(tlut);
    font->SetPosX(x);
    font->SetPosY(y - 4.0f);
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
    font->SetPosY(y - 4.0f);
    font->Draw(text);
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
        span = static_cast<float>(listSize - 1);
    } else {
        span = static_cast<float>(listSize - 8);
    }

    if ((span <= 0.0f) || (listSize <= 8)) {
        return -1.0f;
    }

    return (192.0f * (static_cast<float>(listPos) / span)) + 32.0f;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawListPosMark(float x, float y, float z)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color = { 0xFF, 0xFF, 0xFF, 0xFF };
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x2E));
    MenuPcs.DrawRect(0, 10.0f + x, y + z, 8.0f, 8.0f, 128.0f,
        280.0f, 1.0f, 1.0f, 0.0f);
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
    const CCaravanWork* const caravanWork = SingleCaravanWork();
    int slot;
    int commandItem;

    slot = 2;
    if (slot < caravanWork->m_numCmdListSlots) {
        commandItem = caravanWork->m_commandListInventorySlotRef[2];
        if ((commandItem >= 0) && (commandItem == itemNo)) {
            return 1;
        }
        slot = 3;
        if (slot < caravanWork->m_numCmdListSlots) {
            commandItem = caravanWork->m_commandListInventorySlotRef[3];
            if ((commandItem >= 0) && (commandItem == itemNo)) {
                return 1;
            }
            slot = 4;
            if (slot < caravanWork->m_numCmdListSlots) {
                commandItem = caravanWork->m_commandListInventorySlotRef[4];
                if ((commandItem >= 0) && (commandItem == itemNo)) {
                    return 1;
                }
                slot = 5;
                if (slot < caravanWork->m_numCmdListSlots) {
                    commandItem = caravanWork->m_commandListInventorySlotRef[5];
                    if ((commandItem >= 0) && (commandItem == itemNo)) {
                        return 1;
                    }
                    slot = 6;
                    if (slot < caravanWork->m_numCmdListSlots) {
                        commandItem = caravanWork->m_commandListInventorySlotRef[6];
                        if ((commandItem >= 0) && (commandItem == itemNo)) {
                            return 1;
                        }
                        slot = 7;
                        if (slot < caravanWork->m_numCmdListSlots) {
                            commandItem = caravanWork->m_commandListInventorySlotRef[7];
                            if ((commandItem >= 0) && (commandItem == itemNo)) {
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }

    int equipment = caravanWork->m_equipment[0];
    if ((equipment >= 0) && (equipment == itemNo)) {
        return 1;
    }
    equipment = caravanWork->m_equipment[1];
    if ((equipment >= 0) && (equipment == itemNo)) {
        return 1;
    }
    equipment = caravanWork->m_equipment[2];
    if ((equipment >= 0) && (equipment == itemNo)) {
        return 1;
    }
    equipment = caravanWork->m_equipment[3];
    if ((equipment >= 0) && (equipment == itemNo)) {
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
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    union {
        u32 word;
        _GXColor color;
    } color;
    color.word = 0xFFFFFF00;
    color.color.a = static_cast<u8>(static_cast<int>(255.0f * alpha));
    GXSetChanMatColor(GX_COLOR0A0, color.color);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x2C));

    union {
        double value;
        u32 words[2];
    } xPos, yPos;

    xPos.words[0] = 0x43300000;
    xPos.words[1] = static_cast<u32>(x) ^ 0x80000000U;
    yPos.words[0] = 0x43300000;
    yPos.words[1] = static_cast<u32>(y) ^ 0x80000000U;

    MenuPcs.DrawRect(0, static_cast<float>(xPos.value - 4503601774854144.0),
        static_cast<float>(yPos.value - 4503601774854144.0), 24.0f, 24.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f);
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
    if (mode >= 0 && m_menuWindowInfo->state != mode) {
        m_menuWindowInfo->state = mode;
    }

    if (m_menuWindowInfo->state == 3) {
        return;
    }

    float left = static_cast<float>(m_menuWindowInfo->x) + static_cast<float>(m_menuWindowInfo->width) * 0.5f;
    float top = static_cast<float>(m_menuWindowInfo->y) + static_cast<float>(m_menuWindowInfo->height) * 0.5f;
    float width;
    float height;

    if (m_menuWindowInfo->state == 1) {
        left = static_cast<float>(m_menuWindowInfo->x);
        top = static_cast<float>(m_menuWindowInfo->y);
        width = static_cast<float>(m_menuWindowInfo->width);
        height = static_cast<float>(m_menuWindowInfo->height);
    } else {
        float leftScale = (((left - static_cast<float>(m_menuWindowInfo->x)) - 32.0f) / 6.0f) * static_cast<float>(m_menuWindowInfo->frame);
        float topScale = (((top - static_cast<float>(m_menuWindowInfo->y)) - 32.0f) / 6.0f) * static_cast<float>(m_menuWindowInfo->frame);
        left = (left - 32.0f) - leftScale;
        width = static_cast<float>(2.0 * static_cast<double>(32.0f + leftScale));
        height = static_cast<float>(2.0 * static_cast<double>(32.0f + topScale));
        top = (top - 32.0f) - topScale;
    }

    int leftPx = static_cast<int>(static_cast<double>(left) - 0.5);
    int topPx = static_cast<int>(static_cast<double>(top) - 0.5);
    int widthPx = static_cast<int>(static_cast<double>(width) - 1.0);
    int heightPx = static_cast<int>(static_cast<double>(height) - 1.0);

    float x0 = static_cast<float>(leftPx);
    float y0 = static_cast<float>(topPx);
    float w = static_cast<float>(widthPx);
    float h = static_cast<float>(heightPx);
    float x1 = x0 + w - 32.0f;
    float y1 = y0 + h - 32.0f;

    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, white);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
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
        MenuPcs.DrawRect(uvFlag, x, y, 32.0f, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x41));
    float innerW = w - static_cast<float>(64.0);
    float innerX = 32.0f + x0;
    for (int i = 0; i < 2; i++) {
        unsigned long uvFlag = 0;
        float y = y0;
        if (i != 0) {
            uvFlag = 4;
            y = y1;
        }
        MenuPcs.DrawRect(uvFlag, innerX, y, innerW, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
    float innerH = h - static_cast<float>(64.0);
    float innerY = 32.0f + y0;
    for (int i = 0; i < 2; i++) {
        unsigned long uvFlag = 0;
        float x = x0;
        if (i != 0) {
            uvFlag = 8;
            x = x1;
        }
        MenuPcs.DrawRect(uvFlag, x, innerY, 32.0f, innerH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x42));
    MenuPcs.DrawRect(0, innerX, innerY, innerW, innerH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuWindowInfo* win = m_menuWindowInfo;
    s16 state = win->state;
    if (state == 0) {
        win->frame = win->frame + 1;
        if (win->frame > 5) {
            win->frame = 6;
            win->state = 1;
        }
    } else if (state == 1) {
        if (win->frame != 6) {
            win->frame = 6;
        }
    } else if (state == 2) {
        win->frame = win->frame - 1;
        if (win->frame < 1) {
            win->frame = 0;
            win->state = 3;
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
    CFont* font = m_fonts[0];
    font->SetMargin(1.0f);
    font->SetShadow(1);
    font->SetScale(FLOAT_8032ea78);
    font->DrawInit();

    CColor color(0xFF, 0xFF, 0xFF, 0xFF);
    font->SetColor(color.color);

    int lineCount;
    if (useDynamic != 0) {
        lineCount = s_DynamicMess[0];
    } else {
        lineCount = s_singleMenuStaticMessages[messageNo].lineCount;
    }
    const SingMenuStaticMessageInfo& staticMessage = s_singleMenuStaticMessages[messageNo];

    int maxWidth = 0;
    char* dynamicText = s_DynamicMessStr;
    for (int i = 0; i < lineCount; i++) {
        const char* text = dynamicText;
        if (useDynamic == 0) {
            text = GetSingWinMessage(staticMessage.textIds[i], dynamicText, 0);
        }
        int textWidth = font->GetWidth(text);
        if (maxWidth < textWidth) {
            maxWidth = textWidth;
        }
        dynamicText += 0x80;
    }

    MenuWindowInfo* win = m_menuWindowInfo;
    unsigned int lineHeight = static_cast<int>(22.0f * FLOAT_8032ea78);
    if (0.0f < 22.0f * FLOAT_8032ea78 - static_cast<float>(lineHeight)) {
        lineHeight++;
    }

    float x = static_cast<float>(win->x) + static_cast<float>(win->width - maxWidth) * static_cast<float>(0.5);
    float y = static_cast<float>(win->y + 0x20);
    unsigned int lineStep = lineHeight + 3;

    dynamicText = s_DynamicMessStr;
    for (int i = 0; i < lineCount; i++) {
        font->SetTlut(((activeMask & (1 << i)) != 0) + 8);

        const char* text = dynamicText;
        if (useDynamic == 0) {
            text = GetSingWinMessage(staticMessage.textIds[i], dynamicText, 0);
        }
        if (strlen(text) != 0) {
            char lineBuffer[128];
            strcpy(lineBuffer, text);
            font->SetPosX(x);
            font->SetPosY(y - 4.0f);
            font->Draw(lineBuffer);
        }

        dynamicText += 0x80;
        y += static_cast<float>(lineStep);
    }

    DrawInit();
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
    CFont* font = m_fonts[0];
    font->SetMargin(1.0f);
    font->SetShadow(1);
    font->SetScale(FLOAT_8032ea78);

    unsigned int lineCount;
    if (useDynamic != 0) {
        lineCount = s_DynamicMess[0];
    } else {
        lineCount = s_singleMenuStaticMessages[messageNo].lineCount;
    }
    const SingMenuStaticMessageInfo& staticMessage = s_singleMenuStaticMessages[messageNo];

    int maxWidth = 0;
    char* dynamicText = s_DynamicMessStr;
    for (int i = 0; i < lineCount; i++) {
        const char* text = dynamicText;
        if (useDynamic == 0) {
            text = GetSingWinMessage(staticMessage.textIds[i], dynamicText, 0);
        }
        int textWidth = font->GetWidth(text);
        if (maxWidth < textWidth) {
            maxWidth = textWidth;
        }
        dynamicText += 0x80;
    }

    if (useDynamic == 0) {
        maxWidth -= 0x18;
    } else {
        maxWidth += 0x16;
    }

    int lineHeight = static_cast<int>(22.0f * FLOAT_8032ea78);
    if (0.0f < 22.0f * FLOAT_8032ea78 - static_cast<float>(lineHeight)) {
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

extern "C" const char* gSingMenuTextTableEn[] = {
    s_Empty_803321B8, s_Yes_803321BC, s_No_803321C0, s_Cancel_803321C4,
    s_gil_803321CC, s_Strength_801DD814, s_Defence_803321D0, s_Magic_803321D8,
    s_Memories_801DD820, s_Attack_803321E0, s_Defend_803321E8, s_Remove_803321F0,
    s_Fuse_803321F8, s_Split_80332200, s_Use_80332208, s_Drop_8033220C,
    s_Destroy_80332214, s_Male_8033221C, s_Female_80332224, s_All_8033222C,
    s_QuestionMarks_80332230, s_g_period_80332234, s_Father_80332238, s_Mother_80332240,
    s_Brother_80332248, s_Sister_80332250, s_Brother_80332248, s_Sister_80332250,
    s_Empty_803321B8, s_Letters_80332258, s_Send_item_801DD82C, s_Send_gil_801DD838,
    s_Send_nothing_801DD844, s_Proceed_801DD854, s_Take_out_801DD860, s_Quote_80332260,
    s_Quote_80332260, s_Send_80332264, s_the_reply_801DD86C, s_Empty_803321B8,
    s_Include_801DD878, s_Confirm_8033226C, s_Name_80332274, s_Gender_8033227C,
    s_Tribe_80332284, s_Family_Trade_801DD884, s_Command_List_801DD894, s_Items_8033228C,
    s_Equip_80332294, s_Artefacts_801DD8A4, s_Treasures_801DD8B0, s_Money_8033229C,
    s_Favourites_801DD8BC, s_Family_803322A4, s_Letters_80332258, s_Done_803322AC,
};
extern "C" const char* gSingMenuTextTableDe[] = {
    s_Empty_803321B8, s_Ja_803322B4, s_Nein_803322B8, s_Abbrechen_801DD8C8,
    s_Gil_803322C0, s_Staerke_803322C4, s_Abwehr_803322CC, s_Magie_803322D4,
    s_Erinnerungen_801DD8D4, s_Angreifen_801DD8E4, s_Verteidigen_801DD8F0, s_Ablegen_803322DC,
    s_Kombinieren_801DD8FC, s_Aufloesen_801DD908, s_Benutzen_801DD914, s_Wegwerfen_801DD920,
    s_Zerstoeren_801DD92C, s_Maennlich_801DD938, s_Weiblich_801DD944, s_Alle_Rassen_801DD950,
    s_QuestionMarks_80332230, s_G_803322E4, s_Vater_803322E8, s_Mutter_803322F0,
    s_Bruder_803322F8, s_Schwester_801DD95C, s_kl_Bruder_801DD968, s_kl_Schwester_801DD974,
    s_Empty_803321B8, s_Liste_erhaltener_Briefe_801DD984, s_Gegenstand_beifuegen_801DD99C, s_Gil_beifuegen_801DD9B0,
    s_Nichts_beifuegen_801DD9C0, s_Weiter_80332300, s_herausholen_801DD9D0, s_specialChar_80332308,
    s_Quote_80332260, s_Empty_803321B8, s_die_Antwort_801DD9E0, s_schicken_801DD9F0,
    s_beifuegen_801DD9FC, s_Bestaetigen_801DDA08, s_Name_80332274, s_Geschlecht_801DDA14,
    s_Rasse_8033230C, s_Elterlicher_Beruf_801DDA20, s_Kommandoliste_801DDA34, s_Gegenstaende_801DDA44,
    s_Ausruesten_801DDA50, s_Artefakte_801DDA5C, s_Geborgtes_801DDA68, s_Geld_80332314,
    s_Geschmack_801DDA74, s_Familie_8033231C, s_Briefe_80332324, s_Abbrechen_801DD8C8,
};
extern "C" const char* gSingMenuTextTableIt[] = {
    s_Empty_803321B8, s_Si_8033232C, s_No_803321C0, s_Annulla_80332330,
    s_guil_80332338, s_Forza_80332340, s_Difesa_80332348, s_Magia_80332350,
    s_Memorie_80332358, s_Attacco_80332360, s_Difesa_80332348, s_Rimuovi_80332368,
    s_Fusione_80332370, s_Dividi_80332378, s_Usa_80332380, s_Posa_80332384,
    s_Distruggi_801DDA80, s_Maschio_8033238C, s_Femmina_80332394, s_Tutti_8033239C,
    s_QuestionMarks_80332230, s_g_period_80332234, s_Padre_803323A4, s_Madre_803323AC,
    s_Fratello_801DDA8C, s_Sorella_803323B4, s_Fratello_801DDA8C, s_Sorella_803323B4,
    s_Empty_803321B8, s_Lettere_803323BC, s_Invia_oggetto_801DDA98, s_Invia_guil_801DDAA8,
    s_Non_inviare_nulla_801DDAB4, s_Vuoi_procedere_801DDAC8, s_Vuoi_prendere_801DDAD8, s_Quote_80332260,
    s_Quote_80332260, s_con_803323C4, s_Vuoi_rispondere_a_801DDAE8, s_Empty_803321B8,
    s_Allegato_801DDAFC, s_Conferma_801DDB08, s_Nome_803323CC, s_Sesso_803323D4,
    s_Razza_803323DC, s_Mestiere_801DDB14, s_Lista_Comandi_801DDB20, s_Oggetti_803323E4,
    s_Equipaggiamento_801DDB30, s_Manufatti_801DDB40, s_Tesori_803323EC, s_Denaro_803323F4,
    s_Preferiti_801DDB4C, s_Famiglia_801DDB58, s_Lettere_803323BC, s_Fatto_803323FC,
};
extern "C" const char* gSingMenuTextTableFr[] = {
    s_Empty_803321B8, s_Oui_80332404, s_Non_80332408, s_Annuler_8033240C,
    s_gils_80332414, s_Force_8033241C, s_Resistance_801DDB64, s_Magie_803322D4,
    s_Souvenirs_801DDB70, s_Attaquer_801DDB7C, s_Defendre_801DDB88, s_Retirer_80332424,
    s_Fusionner_801DDB94, s_Separer_8033242C, s_Utiliser_801DDBA0, s_Jeter_80332434,
    s_Detruire_801DDBAC, s_Masculin_801DDBB8, s_Feminin_8033243C, s_Tous_80332444,
    s_QuestionMarks_80332230, s_g_period_80332234, s_Pere_8033244C, s_Mere_80332454,
    s_Frere_8033245C, s_Soeur_80332464, s_Frere_8033245C, s_Soeur_80332464,
    s_Empty_803321B8, s_Lettres_8033246C, s_Envoyer_un_objet_801DDBC4, s_Envoyer_des_gils_801DDBD8,
    s_Ne_rien_envoyer_801DDBEC, s_Continuer_801DDBFC, s_Prendre_801DDC08, s_Quote_80332260,
    s_Quote_80332260, s_la_reponse_801DDC14, s_Envoyer_a_801DDC20, s_Empty_803321B8,
    s_Joindre_801DDC2C, s_Confirmer_801DDC38, s_Nom_80332474, s_Sexe_8033247C,
    s_Tribu_80332484, s_Metier_8033248C, s_Commandes_801DDC44, s_Objets_80332494,
    s_Equiper_8033249C, s_Artefacts_801DD8A4, s_Tresors_803324A4, s_Gils_803324AC,
    s_Preferences_801DDC50, s_Famille_803324B4, s_Lettres_8033246C, s_Laisser_803324BC,
};
extern "C" const char* gSingMenuTextTableEs[] = {
    s_Empty_803321B8, s_Si_803324C4, s_No_803321C0, s_Cancelar_801DDC5C,
    s_guiles_803324C8, s_Fuerza_803324D0, s_Defensa_803324D8, s_Magia_80332350,
    s_Memorias_801DDC68, s_Atacar_803324E0, s_Defender_801DDC74, s_Quitar_803324E8,
    s_Fusionar_801DDC80, s_Separar_803324F0, s_Utilizar_801DDC8C, s_Descartar_801DDC98,
    s_Destruir_801DDCA4, s_Hombre_803324F8, s_Mujer_80332500, s_Todos_80332508,
    s_invQuestions_80332510, s_g_period_80332234, s_Padre_803323A4, s_Madre_803323AC,
    s_Hermano_80332518, s_Hermana_80332520, s_Hermano_80332518, s_Hermana_80332520,
    s_Empty_803321B8, s_Cartas_80332528, s_Enviar_objeto_801DDCB0, s_Enviar_guiles_801DDCC0,
    s_No_enviar_nada_801DDCD0, s_Continuar_801DDCE0, s_Extraer_801DDCEC, s_Quote_80332260,
    s_Quote_80332260, s_period_80332530, s_Enviar_la_respuesta_a_801DDCF8, s_Empty_803321B8,
    s_Incluir_801DDD10, s_Confirmar_801DDD1C, s_Nombre_80332534, s_Sexo_8033253C,
    s_Tribu_80332484, s_Oficio_familiar_801DDD28, s_Comandos_801DDD3C, s_Objetos_80332544,
    s_Equipo_8033254C, s_Artefactos_801DDD48, s_Tesoros_80332554, s_Dinero_8033255C,
    s_Favoritos_801DDD54, s_Familia_80332564, s_Cartas_80332528, s_Hecho_8033256C,
};

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
    m_menuWindowInfo->x = static_cast<s16>(x);
    m_menuWindowInfo->y = static_cast<s16>(y);
    m_menuWindowInfo->width = static_cast<s16>(w);
    m_menuWindowInfo->height = static_cast<s16>(h);
    m_menuWindowInfo->frame = 0;
    m_menuWindowInfo->state = 3;
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
    s_DynamicMess[0] = lineCount;

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

extern "C" {
int s_DynamicMess[5];
}
char s_DynamicMessStr[0x400];
extern "C" SingMenuStaticMessageInfo s_singleMenuStaticMessages[] = {
    {4, {14, 15, 16, 3, 0, 0, 0, 0}},
    {2, {15, 3, 0, 0, 0, 0, 0, 0}},
    {4, {30, 31, 32, 3, 0, 0, 0, 0}},
};

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
inline float CMenuPcs::GetSingWinScl()
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
    float scaled = 22.0f * FLOAT_8032ea78;
    int lineHeight = static_cast<int>(scaled);

    if (0.0f < scaled - static_cast<float>(lineHeight)) {
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
    unsigned int genderMask = 0x10;
    s16 flags = *reinterpret_cast<u16*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 4);
    unsigned int raceMask = 1 << (SingleCaravanWork()->m_tribeId & 3);

    if (SingleCaravanWork()->m_genderFlag != 0) {
        genderMask = 0x20;
    }

    int raceBits = flags & 0xF;
    int genderBits = flags & 0x30;

    int result;
    if (raceBits != 0 && genderBits != 0) {
        result = (raceBits & raceMask) != 0 && (genderBits & genderMask) != 0;
    } else if (raceBits != 0) {
        result = (raceBits & raceMask) != 0;
    } else {
        result = (genderBits & genderMask) != 0;
    }
    return result;
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
    int equipType;

    if (flags & 0x100) {
        equipType = 0;
    } else if (flags & 0x400) {
        equipType = 1;
    } else if (flags & 0xA00) {
        equipType = 2;
    } else if (flags & 0x3000) {
        equipType = 3;
    } else {
        equipType = 0;
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(s_pcts_pctd_item_pctd_m_equip_pct08x_801DE8B0, s_singmenu_cpp, 0xD3D, itemNo, flags);
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
    unsigned int caravanWork = reinterpret_cast<unsigned int>(SingleCaravanWork());

    GetItemType(itemNo, 1);
    u16 race = *reinterpret_cast<u16*>(caravanWork + 0x3e0);
    u16 raceType = race & 3;
    int itemBase = Game.unkCFlatData0[2] + itemNo * 0x48;

    int smithItem = *reinterpret_cast<u16*>((itemBase + (race & 3) * 2) + 0x38);
    if (smithItem > 0) {
        unsigned int genderMask = 0x10;
        u16 flags = *reinterpret_cast<u16*>(Game.unkCFlatData0[2] + smithItem * 0x48 + 4);
        unsigned int raceMask = 1 << (*reinterpret_cast<u16*>(reinterpret_cast<unsigned int>(SingleCaravanWork()) + 0x3e0) & 3);
        if (*reinterpret_cast<short*>(reinterpret_cast<unsigned int>(SingleCaravanWork()) + 0x3e2) != 0) {
            genderMask = 0x20;
        }

        unsigned int valid;
        if (((flags & 0xF) != 0) && ((flags & 0x30) != 0)) {
            if (((flags & 0xF & raceMask) != 0) && ((flags & 0x30 & genderMask) != 0)) {
                valid = 1;
            } else {
                valid = 0;
            }
        } else if ((flags & 0xF) == 0) {
            valid = static_cast<unsigned int>(-static_cast<int>(flags & 0x30 & genderMask)) >> 0x1f;
        } else {
            valid = static_cast<unsigned int>(-static_cast<int>(flags & 0xF & raceMask)) >> 0x1f;
        }

        if (valid != 0) {
            return smithItem;
        }
    }

    if ((((((race & 3) == 0) || (smithItem = *reinterpret_cast<u16*>(itemBase + 0x38), smithItem <= 0)) &&
          ((raceType == 1) || (smithItem = *reinterpret_cast<u16*>(itemBase + 0x3A), smithItem <= 0))) &&
         ((raceType == 2) || (smithItem = *reinterpret_cast<u16*>(itemBase + 0x3C), smithItem <= 0))) &&
        ((raceType == 3) || (smithItem = *reinterpret_cast<u16*>(itemBase + 0x3E), smithItem <= 0))) {
        smithItem = 0xFFFFFFFF;
    }
    return smithItem;
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
    GetItemType(itemNo, 1);

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
 * PAL Address: 0x801458ec
 * PAL Size: 920b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingBar(int x, int y, int value, float alpha)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    unsigned char alphaU8 = static_cast<unsigned char>(255.0f * alpha);
    _GXColor color = {0xFF, 0xFF, 0xFF, alphaU8};
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x53));
    MenuPcs.DrawRect(0, static_cast<float>(x), static_cast<float>(y), 16.0f,
                                    24.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(8, static_cast<float>(x + 0x60), static_cast<float>(y), 16.0f,
                                    24.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x54));
    MenuPcs.DrawRect(0, static_cast<float>(x + 0x10), static_cast<float>(y),
                                    80.0f, 24.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);

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

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
    int barY = y + 8;
    MenuPcs.DrawRect(0, static_cast<float>(x + 0x10), static_cast<float>(barY),
                                    4.0f, 8.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(8, static_cast<float>(x + 0x10 + bars * 8 - 4), static_cast<float>(barY),
                                    4.0f, 8.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex + 1));
    MenuPcs.DrawRect(0, static_cast<float>(x + 0x14), static_cast<float>(barY),
                                    static_cast<float>(bars * 8 - 8), 8.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);
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
inline void CMenuPcs::CalcSingLife()
{
    int* lifeTimer = &m_singleLifeTimer;
    if (*lifeTimer >= 0) {
        ++(*lifeTimer);
        if (*lifeTimer > 0x31) {
            *lifeTimer = -1;
        }
    }
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
    const CCaravanWork* const caravanWork = SingleCaravanWork();
    int lifeTimer = m_singleLifeTimer;
    float xBase = 366.0f;
    float yBase = -32.0f;
    if (lifeTimer < 0) {
        return;
    }

    float y;
    if (lifeTimer < 10) {
        int phase;
        if (lifeTimer < 0) {
            phase = 0;
        } else {
            phase = 10;
            if (lifeTimer <= 10) {
                phase = lifeTimer;
            }
        }
        y = 64.0f * static_cast<float>(sin(0.01745329238474369f * (9.0f * static_cast<float>(phase)))) + yBase;
    } else {
        y = 32.0f;
        if (lifeTimer > 0x27) {
            int t = 10 - (lifeTimer - 0x28);
            int phase;
            if (t < 0) {
                phase = 0;
            } else {
                phase = 10;
                if (t <= 10) {
                    phase = t;
                }
            }
            y = 64.0f * static_cast<float>(sin(0.01745329238474369f * (9.0f * static_cast<float>(phase)))) + yBase;
        }
    }

    int halfHearts = static_cast<unsigned int>(caravanWork->m_maxHp >> 1);
    reinterpret_cast<CMesMenu*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(&MenuPcs) + 0x268))
        ->DrawHeart(xBase + static_cast<float>(((8 - halfHearts) * 0x18) / 2), y - 8.0f, 1.0f, 1.0f);
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
    if ((m_singleLifeTimer > 0) && (timer == 0)) {
        m_singleLifeTimer = 10;
        return;
    }
    m_singleLifeTimer = timer;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CMenuPcs::SingLifeResetWait()
{
    SingLifeInit(0);
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

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMenuPcs::GetItemType(int itemId, int useRawItemId)
{
    if (useRawItemId == 0) {
        itemId = static_cast<int>(SingleCaravanWork()->m_inventoryItems[itemId]);
    }

    if (itemId <= 0) {
        return 0;
    }
    if (itemId <= 0x9E) {
        return 1;
    }
    if (itemId <= 0xFF) {
        return 2;
    }
    if (itemId <= 0x124) {
        return 3;
    }
    if (itemId == 0x125) {
        return 4;
    }
    if (itemId <= 0x129) {
        return 5;
    }
    if (itemId <= 0x17C) {
        return 6;
    }
    if (itemId <= 0x188) {
        return 7;
    }
    if (itemId <= 0x190) {
        return 8;
    }
    return 9;
}
