#include "ffcc/goout.h"
#include "ffcc/memory.h"
#include "ffcc/wm_menu.h"
#include <stdarg.h>
#include <string.h>

CGoOutMenu g_GoOutMenu;
CGoOutMenu* g_pGoOutMenu;
int g_freeCaravanIdx;

extern "C" void SetMenuCharaAnim__8CMenuPcsFii2(CMenuPcs*);

extern char s_The_Memory_Card_in_Slot_A_contains_801DEE30[];
extern char s_no_save_data_for_your_current_game_801DEE54[];
extern char s_or_contains_corrupt_data_Please_801DEE78[];
extern char s_insert_a_Memory_Card_containing_801DEE9C[];
extern char s_valid_save_data_into_Slot_A_801DEEBC[];
extern char s_This_game_has_not_been_saved_801DEEDC[];
extern char s_GoOutBlankLine[];
extern char s_You_must_save_your_game_before_801DEEFC[];
extern char s_you_can_import_a_character_801DEF1C[];
extern char s_This_game_contains_character_data_801DEF38[];
extern char s_that_has_not_yet_been_saved_801DEF5C[];
extern char s_Please_insert_a_Memory_Card_with_the_801DEF7C[];
extern char s_current_game_s_data_into_Slot_A_801DEFA4[];
extern char s_Insert_into_Slot_B_a_Memory_Card_801DEFC8[];
extern char s_with_the_character_data_to_be_transferred_801DEFEC[];
extern char s_Please_do_not_remove_either_Memory_Card_801DF018[];
extern char s_until_the_transfer_is_complete_801DF040[];
extern char s_Are_you_sure_you_wish_to_import_801DF060[];
extern char s_the_selected_character_into_the_801DF080[];
extern char s_current_game_The_character_will_801DF0A0[];
extern char s_be_unavailable_until_returned_801DF0C4[];
extern char s_Yes_No_801DF0E4[];
extern char s_Are_you_sure_you_wish_to_return_801DF0F4[];
extern char s_the_selected_character_to_the_801DF114[];
extern char s_current_game_The_character_s_801DF134[];
extern char s_guest_data_will_be_deleted_801DF154[];
extern char s_Saving_data_to_the_Memory_801DF170[];
extern char s_Card_in_Slot_A_Please_do_801DF18C[];
extern char s_not_touch_the_Memory_Card_801DF1A8[];
extern char s_or_the_POWER_Button_801DF1C4[];
extern char s_Card_in_Slot_B_Please_do_801DF1DC[];
extern char s_A_Memory_Card_has_been_removed_801DF1F8[];
extern char s_Cancelling_character_transfer_801DF218[];
extern char s_until_the_character_transfer_is_complete_801DF238[];
extern char s_GoOutSlotA[];
extern char s_GoOutSlotB[];
static const char s_No_Memory_Card_found_in_801DF264[] = "No Memory Card found in";
static const char s_This_data_is_a_copy_of_the_current_801DF27C[] = "This data is a copy of the current";
static const char s_game_s_data_and_cannot_be_used_801DF2A0[] = "game's data and cannot be used.";
static const char s_The_Memory_Card_in_Slot_B_contains_801DF2C0[] = "The Memory Card in Slot B contains";
static const char s_no_save_data_for_FINAL_FANTASY_801DF2E4[] = "no save data for FINAL FANTASY";
static const char s_Crystal_Chronicles_or_contains_801DF304[] = "Crystal Chronicles, or contains";
static const char s_corrupt_data_801DF324[] = "corrupt data.";
static const char s_Please_insert_a_Memory_Card_containing_801DF334[] = "Please insert a Memory Card containing";
static const char s_valid_save_data_into_Slot_B_801DF35C[] = "valid save data into Slot B.";
static const char s_You_cannot_import_characters_801DF37C[] = "You cannot import characters";
static const char s_that_are_currently_abroad_801DF39C[] = "that are currently abroad.";
static const char s_The_current_game_data_already_contains_801DF3B8[] = "The current game data already contains";
static const char s_the_same_character_so_this_character_801DF3E0[] = "the same character, so this character";
static const char s_cannot_be_transferred_801DF408[] = "cannot be transferred.";
static const char s_The_current_game_data_already_801DF420[] = "The current game data already";
static const char s_contains_8_characters_so_no_more_801DF440[] = "contains 8 characters, so no more";
static const char s_characters_can_be_transferred_801DF464[] = "characters can be transferred.";
static const char s_You_must_delete_at_least_one_character_801DF484[] = "You must delete at least one character";
static const char s_before_you_can_transfer_any_more_801DF4AC[] = "before you can transfer any more.";
static const char s_Guest_characters_can_only_be_801DF4D0[] = "Guest characters can only be";
static const char s_returned_to_their_original_save_data_801DF4F0[] = "returned to their original save data.";
static const char s_This_character_cannot_be_deleted_801DF518[] = "This character cannot be deleted.";
static const char s_At_least_one_non_guest_character_801DF53C[] = "At least one non-guest character";
static const char s_must_remain_801DF560[] = "must remain.";
static const char s_Delete_this_character_801DF570[] = "Delete this character?";
static const char s_Deleted_characters_801DF588[] = "Deleted characters";
static const char s_cannot_be_restored_801DF59C[] = "cannot be restored.";
static const char s_Are_you_sure_801DF5B0[] = "Are you sure?";
static const char s_The_guest_character_has_been_deleted_801DF5C0[] = "The guest character has been deleted.";
static const char s_Please_restore_the_character_s_801DF5E8[] = "Please restore the character's";
static const char s_original_save_data_801DF608[] = "original save data.";
static const char s_To_restore_a_character_who_is_abroad_801DF61C[] = "To restore a character who is abroad,";
static const char s_first_select_Delete_Character_then_801DF644[] = "first select \"Delete Character,\" then";
static const char s_select_the_character_you_wish_to_restore_801DF66C[] = "select the character you wish to restore.";
static const char s_The_character_has_been_deleted_801DF698[] = "The character has been deleted.";
static const char s_This_character_is_currently_abroad_801DF6B8[] = "This character is currently abroad";
static const char s_and_cannot_be_deleted_here_If_you_801DF6DC[] = "and cannot be deleted here. If you";
static const char s_wish_to_delete_the_character_s_801DF700[] = "wish to delete the character's";
static const char s_original_data_you_must_first_801DF720[] = "original data, you must first";
static const char s_restore_it_Proceed_801DF740[] = "restore it. Proceed?";
static const char s_This_will_restore_the_character_s_original_data_801DF758[] = "This will restore the character's original data";
static const char s_to_the_state_it_was_in_before_transfer_801DF788[] = "to the state it was in before transfer.";
static const char s_It_will_also_prevent_the_transferred_data_801DF7B0[] = "It will also prevent the transferred data";
static const char s_from_returning_to_this_save_location_Proceed_801DF7DC[] = "from returning to this save location. Proceed?";
static const char s_The_character_has_been_restored_801DF80C[] = "The character has been restored.";
static const char s_The_current_game_data_contains_no_801DF830[] = "The current game data contains no";
static const char s_characters_so_no_characters_can_801DF854[] = "characters, so no characters can";
static const char s_be_imported_801DF878[] = "be imported.";
static const char s_To_import_a_character_you_must_801DF888[] = "To import a character, you must";
static const char s_first_create_one_and_save_the_data_801DF8A8[] = "first create one and save the data";
static const char s_to_a_Memory_Card_801DF8CC[] = "to a Memory Card.";
static const char s_The_character_cannot_be_801DF8E0[] = "The character cannot be";
static const char s_deleted_from_the_current_data_801DF8F8[] = "deleted from the current data.";
static const char s_In_der_Memory_Card_in_Steckplatz_A_801DF918[] = "In der Memory Card in Steckplatz A";
static const char lbl_801DF93C[] = "befinden sich keine Spielst\xe4nde der";
static const char s_aktuellen_Spielsitzung_Bitte_stecken_801DF960[] = "aktuellen Spielsitzung. Bitte stecken";
static const char lbl_801DF988[] = "Sie eine Memory Card mit Spielst\xe4nden";
extern char s_der_aktuellen_Spielsitzung_in_Steckplatz_A_ein_801DF9B0[];
extern char s_Auf_die_Memory_Card_wurde_noch_nicht_801DF9E0[];
extern char s_gespeichert_Bitte_speichern_Sie_vorerst_801DFA08[];
extern char s_einen_aktuellen_Spielstand_um_Charaktere_801DFA34[];
extern char s_von_anderen_Memory_Cards_einzuladen_801DFA60[];
extern char s_Es_befinden_sich_noch_ungespeicherte_801DFA88[];
extern char s_Charaktere_in_der_aktuellen_Spielsitzung_801DFAB0[];
extern char s_Bitte_speichern_Sie_vorerst_einen_aktuellen_801DFADC[];
extern char s_Spielstand_um_Charaktere_von_anderen_801DFB08[];
extern char s_Memory_Cards_einzuladen_801DFB30[];
extern char s_Bitte_stecken_Sie_eine_Memory_Card_mit_801DFB4C[];
extern char lbl_801DFB74[];
extern char s_in_Steckplatz_A_ein_Die_Memory_Card_mit_801DFB9C[];
extern char s_dem_Spielstand_des_einzuladenden_801DFBC8[];
extern char s_Charakters_stecken_Sie_bitte_in_Steck_801DFBEC[];
extern char lbl_801DFC14[];
extern char lbl_801DFC40[];
extern char lbl_801DFC68[];
extern char lbl_801DFCA0[];
extern char lbl_801DFCD0[];
extern char lbl_801DFCFC[];
extern char s_Ja_Nein_801DFD30[];
extern char lbl_801DFD40[];
extern char s_die_aktuelle_Spielsitzung_801DFD58[];
extern char lbl_801DFD74[];
extern char lbl_801DFD90[];
extern char s_Auf_die_Memory_Card_in_Steckplatz_A_801DFDA8[];
extern char s_wird_gespeichert_Bitte_entfernen_Sie_801DFDCC[];
extern char s_nicht_die_Memory_Card_in_Steckplatz_A_und_801DFDF4[];
extern char lbl_801DFE20[];
extern char s_Auf_die_Memory_Card_in_Steckplatz_B_801DFE48[];
extern char s_wird_gespeichert_Bitte_entfernen_Sie_801DFE6C[];
extern char s_nicht_die_Memory_Card_in_Steckplatz_B_und_801DFE94[];
extern char s_Die_Memory_Card_wurde_entfernt_801DFEC0[];
extern char lbl_801DFEE0[];
extern char lbl_801DFF14[];
extern char s_des_Charakters_nicht_die_Memory_Card_801DFF40[];
extern char s_Es_befindet_sich_keine_Memory_Card_801DFF68[];
extern char s_in_Steckplatz_A_801DFF8C[];
extern char s_in_Steckplatz_B_801DFFA0[];
extern char s_Dieser_Spielstand_ist_eine_Kopie_der_aktuellen_801DFFB4[];
extern char s_Spielsitzung_und_kann_nicht_verwendet_werden_801DFFE4[];
extern char lbl_801E0014[];
extern char s_Crystal_Chronicles_in_der_Memory_Card_in_Steckplatz_B_801E004C[];
extern char s_oder_die_Daten_sind_fehlerhaft_801E0084[];
extern char s_Bitte_stecken_Sie_eine_Memory_Card_mit_fehlerfreien_801E00A8[];
extern char lbl_801E00DC[];
extern char lbl_801E0100[];
extern char lbl_801E012C[];
extern char s_Der_Charakter_ist_in_der_aktuellen_801E0148[];
extern char s_Spielsitzung_bereits_vorhanden_und_801E016C[];
extern char s_kann_nicht_bewegt_werden_801E0190[];
extern char s_In_der_aktuellen_Spielsitzung_befinden_801E01AC[];
extern char s_sich_bereits_acht_Charaktere_so_dass_keine_801E01D4[];
extern char lbl_801E0200[];
extern char s_Um_andere_Charaktere_einzuladen_muss_801E022C[];
extern char s_mindestens_ein_freier_Platz_vorhanden_sein_801E0254[];
extern char lbl_801E0280[];
extern char lbl_801E02A8[];
extern char lbl_801E02D8[];
extern char lbl_801E02FC[];
extern char lbl_801E0320[];
extern char s_pro_Spielstand_vorhanden_sein_801E034C[];
extern char lbl_801E036C[];
extern char lbl_801E038C[];
extern char lbl_801E03B0[];
extern char lbl_801E03D4[];
extern char lbl_801E03F8[];
extern char lbl_801E041C[];
extern char lbl_801E0440[];
extern char lbl_801E045C[];
extern char lbl_801E0480[];
extern char lbl_801E04A4[];
extern char lbl_801E04CC[];
extern char lbl_801E04F8[];
extern char lbl_801E0514[];
extern char lbl_801E0538[];
extern char lbl_801E0560[];
extern char lbl_801E0588[];
extern char lbl_801E05B0[];
extern char lbl_801E05D4[];
extern char lbl_801E05F8[];
extern char s_nicht_wiederhergestellt_werden_801E0624[];
extern char lbl_801E0644[];
extern char lbl_801E065C[];
extern char lbl_801E0680[];
extern char lbl_801E06A8[];
extern char lbl_801E06CC[];
extern char s_Um_einen_Charakter_zu_bewegen_muss_zuvor_801E06F0[];
extern char s_mindestens_ein_Charakter_kreiert_und_auf_der_801E071C[];
extern char s_Memory_Card_gespeichert_werden_801E074C[];
extern char s_Aus_der_aktuellen_Spielsitzung_801E076C[];
extern char lbl_801E078C[];
extern char s_La_Memory_Card_Scheda_Memoria_nello_801E07B4[];
extern char s_Slot_A_non_contiene_dati_della_801E07DC[];
extern char s_partita_in_corso_Inserisci_nello_801E07FC[];
extern char s_Slot_A_una_Memory_Card_Scheda_Memoria_801E0820[];
extern char s_contenente_dei_dati_di_gioco_adatti_801E0848[];
extern char lbl_801E0870[];
extern char s_Se_vuoi_trasferire_un_personaggio_801E0890[];
extern char s_devi_prima_salvare_la_partita_801E08B4[];
extern char s_I_dati_del_personaggio_di_questa_801E08D4[];
extern char s_partita_non_sono_ancora_stati_salvati_801E08F8[];
extern char s_Inserisci_nello_Slot_A_una_Memory_Card_Scheda_801E0920[];
extern char s_Memoria_contenente_i_dati_di_questa_partita_801E0950[];
extern char s_Inserisci_nello_Slot_B_una_Memory_Card_Scheda_801E0980[];
extern char s_Memoria_con_i_dati_del_personaggio_da_trasferire_801E09B0[];
extern char s_Non_rimuovere_le_due_Memory_Card_Schede_Memoria_801E09E4[];
extern char s_fino_al_completamento_del_trasferimento_801E0A18[];
extern char s_Vuoi_trasferire_il_personaggio_801E0A44[];
extern char s_selezionato_nella_partita_801E0A64[];
extern char lbl_801E0A80[];
extern char s_disponibile_fino_al_suo_ritorno_801E0AA4[];
extern char lbl_801E0AC8[];
extern char s_Vuoi_far_tornare_il_personaggio_801E0AD4[];
extern char s_selezionato_alla_partita_801E0AF4[];
extern char s_in_corso_I_dati_del_personaggio_801E0B10[];
extern char s_ospite_saranno_cancellati_801E0B34[];
extern char s_Salvataggio_sulla_Memory_Card_Scheda_801E0B50[];
extern char s_Memoria_nello_Slot_A_in_corso_801E0B78[];
extern char s_Non_toccare_la_Memory_Card_Scheda_801E0B98[];
extern char s_Memoria_o_il_Pulsante_POWER_801E0BBC[];
extern char s_Memoria_nello_Slot_B_in_corso_801E0BDC[];
extern char lbl_801E0BFC[];
extern char s_Trasferimento_del_personaggio_annullato_801E0C30[];
extern char s_Non_rimuovere_le_Memory_Card_Schede_Memoria_801E0C5C[];
extern char s_fino_al_completamento_del_trasferimento_del_personaggio_801E0C8C[];
extern char lbl_801E0CC8[];
extern char s_nessuna_Memory_Card_Scheda_Memoria_801E0CE4[];
extern char lbl_801E0D0C[];
extern char s_Questi_dati_sono_una_copia_dei_dati_della_801E0D28[];
extern char s_partita_in_corso_e_non_possono_essere_usati_801E0D54[];
extern char s_La_Memory_Card_Scheda_Memoria_nello_Slot_B_801E0D84[];
extern char s_non_contiene_dati_di_FINAL_FANTASY_Crystal_801E0DB4[];
extern char s_Chronicles_o_contiene_dati_danneggiati_801E0DE0[];
extern char s_Inserisci_nello_Slot_B_una_Memory_Card_801E0E08[];
extern char s_Scheda_Memoria_contenente_dei_dati_validi_801E0E30[];
extern char s_Non_puoi_trasferire_dei_personaggi_801E0E60[];
extern char s_che_sono_in_missione_801E0E84[];
extern char lbl_801E0E9C[];
extern char s_di_gioco_attuali_impossibile_801E0EC4[];
extern char s_trasferirlo_801E0EE4[];
extern char s_I_dati_di_gioco_attuali_contengono_801E0EF4[];
extern char lbl_801E0F18[];
extern char s_trasferirne_altri_801E0F38[];
extern char s_Prima_di_trasferire_un_altro_personaggio_801E0F4C[];
extern char s_devi_cancellarne_almeno_uno_801E0F78[];
extern char s_I_personaggi_ospiti_possono_essere_trasferiti_801E0F98[];
extern char s_solo_al_loro_salvataggio_d_origine_801E0FC8[];
extern char lbl_801E0FEC[];
extern char s_Deve_rimanere_almeno_un_personaggio_801E101C[];
extern char s_non_ospite_801E1040[];
extern char s_Vuoi_cancellare_questo_personaggio_801E104C[];
extern char s_Una_volta_cancellato_il_personaggio_801E1070[];
extern char lbl_801E1098[];
extern char s_Vuoi_procedere_801E10B0[];
extern char lbl_801E10C0[];
extern char s_Ricarica_i_dati_salvati_801E10EC[];
extern char s_originali_del_personaggio_801E1104[];
extern char s_Per_recuperare_un_personaggio_in_missione_801E1120[];
extern char s_seleziona_Cancella_Personaggio_e_poi_801E114C[];
extern char s_il_personaggio_da_recuperare_801E1174[];
extern char lbl_801E1194[];
extern char lbl_801E11B8[];
extern char lbl_801E11DC[];
extern char s_Se_vuoi_cancellare_un_personaggio_801E11FC[];
extern char s_devi_prima_ripristinarne_i_dati_801E1220[];
extern char s_Vuoi_ripristinare_i_dati_del_personaggio_801E1244[];
extern char s_Una_volta_caricati_801E1270[];
extern char s_i_dati_trasferiti_non_possono_801E1284[];
extern char s_essere_riportati_qui_801E12A4[];
extern char lbl_801E12BC[];
extern char s_I_dati_di_gioco_attuali_non_contengono_801E12E0[];
extern char lbl_801E1308[];
extern char s_trasferirne_nessuno_801E132C[];
extern char s_Per_trasferire_un_personaggio_devi_prima_801E1344[];
extern char s_crearne_uno_e_poi_salvarlo_sulla_801E1370[];
extern char s_Memory_Card_Scheda_Memoria_801E1394[];
extern char lbl_801E13B4[];
extern char s_cancellato_dai_dati_attuali_801E13D8[];
extern char lbl_801E13F8[];
extern char lbl_801E1424[];
extern char lbl_803331C4[];
extern char lbl_801E1450[];
extern char lbl_801E1480[];
extern char lbl_801E14B0[];
extern char s_Pour_pouvoir_importer_un_personnage_vous_801E14D8[];
extern char s_devez_d_abord_sauvegarder_la_partie_801E1504[];
extern char lbl_801E152C[];
extern char lbl_801E155C[];
extern char lbl_801E1584[];
extern char lbl_801E15BC[];
extern char lbl_801E15EC[];
extern char lbl_801E1624[];
extern char lbl_801E1658[];
extern char lbl_801E1690[];
extern char s_Voulez_vous_vraiment_importer_le_personnage_801E16BC[];
extern char lbl_801E16E8[];
extern char s_personnage_sera_indisponible_dans_sa_partie_801E1710[];
extern char lbl_801E173C[];
extern char s_Oui_Non_801E175C[];
extern char lbl_801E176C[];
extern char lbl_801E1790[];
extern char lbl_801E17B8[];
extern char lbl_801E17DC[];
extern char lbl_801E1804[];
extern char lbl_801E182C[];
extern char lbl_801E1854[];
extern char lbl_801E1874[];
extern char lbl_801E1898[];
extern char lbl_801E18C0[];
extern char s_Annulation_du_transfert_de_personnage_801E18F0[];
extern char lbl_801E1918[];
extern char lbl_801E1950[];
extern char lbl_801E1974[];
extern char lbl_801E1994[];
extern char s_Ce_fichier_est_une_copie_du_fichier_de_la_801E19B4[];
extern char lbl_801E19E0[];
extern char lbl_801E1A10[];
extern char lbl_801E1A40[];
extern char s_FINAL_FANTASY_Crystal_Chronicles_ou_contient_801E1A70[];
extern char lbl_801E1AA0[];
extern char lbl_801E1AB8[];
extern char lbl_801E1AE8[];
extern char s_sauvegarde_valides_801E1B14[];
extern char s_Il_est_impossible_d_importer_un_801E1B28[];
extern char s_personnage_qui_est_parti_en_voyage_801E1B48[];
extern char s_Le_fichier_actuel_contient_801E1B70[];
extern char lbl_801E1B8C[];
extern char lbl_801E1BA8[];
extern char lbl_801E1BC4[];
extern char s_personnages_Aucun_personnage_801E1BE4[];
extern char lbl_801E1C04[];
extern char s_Vous_devez_effacer_au_moins_un_personnage_801E1C2C[];
extern char s_avant_de_pouvoir_effectuer_un_transfert_801E1C58[];
extern char lbl_801E1C84[];
extern char lbl_801E1CA8[];
extern char lbl_801E1CD4[];
extern char s_Il_doit_rester_au_moins_un_801E1CFC[];
extern char lbl_801E1D18[];
extern char s_Effacer_ce_personnage_801E1D3C[];
extern char lbl_801E1D54[];
extern char lbl_801E1D7C[];
extern char s_Effacer_le_personnage_801E1DA8[];
extern char lbl_801E1DC0[];
extern char s_Veuillez_restaurer_la_sauvegarde_d_origine_de_ce_801E1DE8[];
extern char s_personnage_801E1E1C[];
extern char lbl_801E1E28[];
extern char lbl_801E1E54[];
extern char lbl_801E1E84[];
extern char lbl_801E1EB0[];
extern char s_Ce_personnage_est_actuellement_en_voyage_801E1ECC[];
extern char lbl_801E1EF8[];
extern char lbl_801E1F24[];
extern char s_de_pouvoir_l_effacer_801E1F50[];
extern char lbl_801E1F68[];
extern char lbl_801E1F90[];
extern char lbl_801E1FD0[];
extern char lbl_801E2010[];
extern char lbl_801E2050[];
extern char lbl_801E2090[];
extern char s_Le_fichier_actuel_ne_contient_aucun_801E20B0[];
extern char s_personnage_donc_aucun_personnage_801E20D4[];
extern char lbl_801E20F8[];
extern char s_Pour_importer_un_personnage_vous_devez_801E2110[];
extern char lbl_801E2138[];
extern char lbl_801E2164[];
extern char lbl_801E2188[];
extern char lbl_801E21A8[];
extern char s_La_Memory_Card_tarjeta_de_memoria_de_la_801E21C4[];
extern char s_Ranura_A_no_contiene_datos_del_juego_801E21F0[];
extern char s_Por_favor_inserta_una_Memory_Card_801E2218[];
extern char s_tarjeta_de_memoria_que_contenga_801E223C[];
extern char s_datos_del_juego_en_la_Ranura_A_801E2260[];
extern char s_Esta_partida_no_ha_sido_guardada_801E2280[];
extern char s_Antes_de_transferir_un_personaje_801E22A4[];
extern char s_debes_guardar_tu_partida_801E22C8[];
extern char s_Esta_partida_contiene_datos_de_personajes_801E22E4[];
extern char lbl_801E2310[];
extern char s_Por_favor_inserta_una_Memory_Card_tarjeta_de_memoria_801E2330[];
extern char s_en_la_Ranura_A_con_los_datos_de_la_partida_actual_y_801E2368[];
extern char s_otra_Memory_Card_tarjeta_de_memoria_en_la_Ranura_B_801E239C[];
extern char s_con_los_datos_del_personaje_a_transferir_801E23D4[];
extern char s_Por_favor_no_extraigas_ninguna_de_las_Memory_Card_tarjetas_801E2400[];
extern char s_de_memoria_hasta_que_la_transferencia_haya_finalizado_801E2440[];
extern char lbl_801E2478[];
extern char s_seleccionado_al_juego_actual_801E24A4[];
extern char lbl_801E24C4[];
extern char s_hasta_que_lo_devuelvas_801E24E8[];
extern char lbl_801E2500[];
extern char lbl_801E250C[];
extern char s_personaje_seleccionado_al_juego_801E252C[];
extern char s_actual_Los_datos_del_personaje_801E254C[];
extern char lbl_801E256C[];
extern char s_Guardando_datos_en_la_Memory_Card_tarjeta_801E2588[];
extern char s_de_memoria_en_la_Ranura_A_801E25B4[];
extern char s_Por_favor_no_toques_ni_la_Memory_Card_801E25D0[];
extern char lbl_801E25F8[];
extern char s_de_memoria_de_la_Ranura_B_801E2620[];
extern char lbl_801E263C[];
extern char lbl_801E267C[];
extern char s_Por_favor_no_extraigas_ninguna_de_las_Memory_Card_tarjetas_de_memoria_801E26AC[];
extern char s_hasta_que_la_transferencia_del_personaje_haya_finalizado_801E26F4[];
extern char s_No_se_ha_encontrado_ninguna_Memory_Card_801E2730[];
extern char s_tarjeta_de_memoria_en_la_Ranura_A_801E2758[];
extern char s_tarjeta_de_memoria_en_la_Ranura_B_801E2780[];
extern char s_Estos_datos_son_una_copia_de_los_datos_del_801E27A8[];
extern char s_juego_actual_y_no_pueden_ser_utilizados_801E27D4[];
extern char s_La_Memory_Card_tarjeta_de_memoria_de_la_Ranura_B_801E2800[];
extern char s_no_contiene_datos_de_partidas_de_FINAL_FANTASY_801E2834[];
extern char lbl_801E2864[];
extern char s_Por_favor_inserta_una_Memory_Card_tarjeta_de_801E2894[];
extern char lbl_801E28C4[];
extern char s_partidas_de_FINAL_FANTASY_Crystal_Chronicles_801E28F4[];
extern char s_No_puedes_transferir_personajes_que_801E2924[];
extern char lbl_801E2948[];
extern char s_Los_datos_de_la_partida_actual_contienen_801E2970[];
extern char s_el_mismo_personaje_de_modo_que_este_801E299C[];
extern char s_personaje_no_puede_ser_transferido_801E29C4[];
extern char s_Los_datos_de_la_partida_actual_contienen_ocho_801E29E8[];
extern char s_personajes_de_modo_que_no_es_posible_801E2A18[];
extern char lbl_801E2A40[];
extern char s_Debes_eliminar_al_menos_un_personaje_801E2A58[];
extern char s_antes_de_tranferir_otro_801E2A80[];
extern char s_Los_personajes_invitados_solo_pueden_ser_transferidos_801E2A9C[];
extern char s_hacia_donde_estaban_originalmente_guardados_801E2AD4[];
extern char s_Este_personaje_no_puede_ser_borrado_801E2B04[];
extern char s_Debes_mantener_al_menos_uno_de_801E2B2C[];
extern char s_los_personajes_no_invitados_801E2B4C[];
extern char lbl_801E2B6C[];
extern char s_Una_vez_que_un_personaje_es_borrado_801E2B8C[];
extern char s_los_datos_no_pueden_recuperarse_801E2BB0[];
extern char lbl_801E2BD4[];
extern char s_El_personaje_invitado_ha_sido_borrado_801E2BE8[];
extern char s_Por_favor_restituye_los_datos_801E2C10[];
extern char s_guardados_originalmente_801E2C30[];
extern char lbl_801E2C4C[];
extern char s_utilizado_selecciona_Borrar_Personaje_y_801E2C78[];
extern char s_luego_el_personaje_que_quieras_restituir_801E2CA4[];
extern char s_El_personaje_ha_sido_borrado_801E2CD0[];
extern char lbl_801E2CF0[];
extern char s_y_no_puede_ser_borrado_Debes_801E2D14[];
extern char s_restituir_los_datos_del_801E2D34[];
extern char s_personaje_para_poder_borrarlo_801E2D4C[];
extern char lbl_801E2D6C[];
extern char lbl_801E2D8C[];
extern char s_transferidos_no_pueden_ser_801E2DAC[];
extern char lbl_801E2DC8[];
extern char lbl_801E2DD8[];
extern char lbl_801E2DEC[];
extern char s_La_partida_actual_no_contiene_801E2E10[];
extern char s_personajes_de_modo_que_no_es_801E2E30[];
extern char s_posible_transferir_ninguno_801E2E50[];
extern char s_Para_transferir_un_personaje_debes_801E2E6C[];
extern char s_crear_uno_primero_y_guardar_los_datos_801E2E90[];
extern char s_en_una_Memory_Card_tarjeta_de_memoria_801E2EB8[];
extern char s_El_personaje_no_puede_ser_801E2EE4[];
extern char s_eliminado_de_los_datos_actuales_801E2F00[];
const char* g_strGooutMes[] = {
    s_The_Memory_Card_in_Slot_A_contains_801DEE30, s_no_save_data_for_your_current_game_801DEE54, s_or_contains_corrupt_data_Please_801DEE78, s_insert_a_Memory_Card_containing_801DEE9C, s_valid_save_data_into_Slot_A_801DEEBC,
    s_This_game_has_not_been_saved_801DEEDC, s_GoOutBlankLine, s_You_must_save_your_game_before_801DEEFC, s_you_can_import_a_character_801DEF1C, s_This_game_contains_character_data_801DEF38,
    s_that_has_not_yet_been_saved_801DEF5C, s_GoOutBlankLine, s_You_must_save_your_game_before_801DEEFC, s_you_can_import_a_character_801DEF1C, s_Please_insert_a_Memory_Card_with_the_801DEF7C,
    s_current_game_s_data_into_Slot_A_801DEFA4, s_Insert_into_Slot_B_a_Memory_Card_801DEFC8, s_with_the_character_data_to_be_transferred_801DEFEC, s_GoOutBlankLine, s_Please_do_not_remove_either_Memory_Card_801DF018,
    s_until_the_transfer_is_complete_801DF040, s_Are_you_sure_you_wish_to_import_801DF060, s_the_selected_character_into_the_801DF080, s_current_game_The_character_will_801DF0A0, s_be_unavailable_until_returned_801DF0C4,
    s_Yes_No_801DF0E4, s_Are_you_sure_you_wish_to_return_801DF0F4, s_the_selected_character_to_the_801DF114, s_current_game_The_character_s_801DF134, s_guest_data_will_be_deleted_801DF154,
    s_Yes_No_801DF0E4, s_Saving_data_to_the_Memory_801DF170, s_Card_in_Slot_A_Please_do_801DF18C, s_not_touch_the_Memory_Card_801DF1A8, s_or_the_POWER_Button_801DF1C4,
    s_Saving_data_to_the_Memory_801DF170, s_Card_in_Slot_B_Please_do_801DF1DC, s_not_touch_the_Memory_Card_801DF1A8, s_or_the_POWER_Button_801DF1C4, s_A_Memory_Card_has_been_removed_801DF1F8,
    s_Cancelling_character_transfer_801DF218, s_GoOutBlankLine, s_Please_do_not_remove_either_Memory_Card_801DF018, s_until_the_character_transfer_is_complete_801DF238, s_No_Memory_Card_found_in_801DF264,
    s_GoOutSlotA, s_No_Memory_Card_found_in_801DF264, s_GoOutSlotB, s_This_data_is_a_copy_of_the_current_801DF27C, s_game_s_data_and_cannot_be_used_801DF2A0,
    s_The_Memory_Card_in_Slot_B_contains_801DF2C0, s_no_save_data_for_FINAL_FANTASY_801DF2E4, s_Crystal_Chronicles_or_contains_801DF304, s_corrupt_data_801DF324, s_GoOutBlankLine,
    s_Please_insert_a_Memory_Card_containing_801DF334, s_valid_save_data_into_Slot_B_801DF35C, s_You_cannot_import_characters_801DF37C, s_that_are_currently_abroad_801DF39C, s_The_current_game_data_already_contains_801DF3B8,
    s_the_same_character_so_this_character_801DF3E0, s_cannot_be_transferred_801DF408, s_The_current_game_data_already_801DF420, s_contains_8_characters_so_no_more_801DF440, s_characters_can_be_transferred_801DF464,
    s_GoOutBlankLine, s_You_must_delete_at_least_one_character_801DF484, s_before_you_can_transfer_any_more_801DF4AC, s_Guest_characters_can_only_be_801DF4D0, s_returned_to_their_original_save_data_801DF4F0,
    s_This_character_cannot_be_deleted_801DF518, s_GoOutBlankLine, s_At_least_one_non_guest_character_801DF53C, s_must_remain_801DF560, s_Delete_this_character_801DF570,
    s_Yes_No_801DF0E4, s_Deleted_characters_801DF588, s_cannot_be_restored_801DF59C, s_Are_you_sure_801DF5B0, s_Yes_No_801DF0E4,
    s_The_guest_character_has_been_deleted_801DF5C0, s_GoOutBlankLine, s_Please_restore_the_character_s_801DF5E8, s_original_save_data_801DF608, s_GoOutBlankLine,
    s_To_restore_a_character_who_is_abroad_801DF61C, s_first_select_Delete_Character_then_801DF644, s_select_the_character_you_wish_to_restore_801DF66C, s_The_character_has_been_deleted_801DF698, s_This_character_is_currently_abroad_801DF6B8,
    s_and_cannot_be_deleted_here_If_you_801DF6DC, s_wish_to_delete_the_character_s_801DF700, s_original_data_you_must_first_801DF720, s_restore_it_Proceed_801DF740, s_Yes_No_801DF0E4,
    s_This_will_restore_the_character_s_original_data_801DF758, s_to_the_state_it_was_in_before_transfer_801DF788, s_It_will_also_prevent_the_transferred_data_801DF7B0, s_from_returning_to_this_save_location_Proceed_801DF7DC, s_Yes_No_801DF0E4,
    s_The_character_has_been_restored_801DF80C, s_The_current_game_data_contains_no_801DF830, s_characters_so_no_characters_can_801DF854, s_be_imported_801DF878, s_GoOutBlankLine,
    s_To_import_a_character_you_must_801DF888, s_first_create_one_and_save_the_data_801DF8A8, s_to_a_Memory_Card_801DF8CC, s_The_character_cannot_be_801DF8E0, s_deleted_from_the_current_data_801DF8F8,
    s_In_der_Memory_Card_in_Steckplatz_A_801DF918, lbl_801DF93C, s_aktuellen_Spielsitzung_Bitte_stecken_801DF960, lbl_801DF988, s_der_aktuellen_Spielsitzung_in_Steckplatz_A_ein_801DF9B0,
    s_Auf_die_Memory_Card_wurde_noch_nicht_801DF9E0, s_gespeichert_Bitte_speichern_Sie_vorerst_801DFA08, s_einen_aktuellen_Spielstand_um_Charaktere_801DFA34, s_von_anderen_Memory_Cards_einzuladen_801DFA60, s_Es_befinden_sich_noch_ungespeicherte_801DFA88,
    s_Charaktere_in_der_aktuellen_Spielsitzung_801DFAB0, s_Bitte_speichern_Sie_vorerst_einen_aktuellen_801DFADC, s_Spielstand_um_Charaktere_von_anderen_801DFB08, s_Memory_Cards_einzuladen_801DFB30, s_Bitte_stecken_Sie_eine_Memory_Card_mit_801DFB4C,
    lbl_801DFB74, s_in_Steckplatz_A_ein_Die_Memory_Card_mit_801DFB9C, s_dem_Spielstand_des_einzuladenden_801DFBC8, s_Charakters_stecken_Sie_bitte_in_Steck_801DFBEC, lbl_801DFC14,
    lbl_801DFC40, lbl_801DFC68, lbl_801DFCA0, lbl_801DFCD0, lbl_801DFCFC,
    s_Ja_Nein_801DFD30, lbl_801DFD40, s_die_aktuelle_Spielsitzung_801DFD58, lbl_801DFD74, lbl_801DFD90,
    s_Ja_Nein_801DFD30, s_Auf_die_Memory_Card_in_Steckplatz_A_801DFDA8, s_wird_gespeichert_Bitte_entfernen_Sie_801DFDCC, s_nicht_die_Memory_Card_in_Steckplatz_A_und_801DFDF4, lbl_801DFE20,
    s_Auf_die_Memory_Card_in_Steckplatz_B_801DFE48, s_wird_gespeichert_Bitte_entfernen_Sie_801DFE6C, s_nicht_die_Memory_Card_in_Steckplatz_B_und_801DFE94, lbl_801DFE20, s_Die_Memory_Card_wurde_entfernt_801DFEC0,
    lbl_801DFEE0, s_GoOutBlankLine, lbl_801DFF14, s_des_Charakters_nicht_die_Memory_Card_801DFF40, s_Es_befindet_sich_keine_Memory_Card_801DFF68,
    s_in_Steckplatz_A_801DFF8C, s_Es_befindet_sich_keine_Memory_Card_801DFF68, s_in_Steckplatz_B_801DFFA0, s_Dieser_Spielstand_ist_eine_Kopie_der_aktuellen_801DFFB4, s_Spielsitzung_und_kann_nicht_verwendet_werden_801DFFE4,
    lbl_801E0014, s_Crystal_Chronicles_in_der_Memory_Card_in_Steckplatz_B_801E004C, s_oder_die_Daten_sind_fehlerhaft_801E0084, s_GoOutBlankLine, s_GoOutBlankLine,
    s_Bitte_stecken_Sie_eine_Memory_Card_mit_fehlerfreien_801E00A8, lbl_801E00DC, lbl_801E0100, lbl_801E012C, s_Der_Charakter_ist_in_der_aktuellen_801E0148,
    s_Spielsitzung_bereits_vorhanden_und_801E016C, s_kann_nicht_bewegt_werden_801E0190, s_In_der_aktuellen_Spielsitzung_befinden_801E01AC, s_sich_bereits_acht_Charaktere_so_dass_keine_801E01D4, lbl_801E0200,
    s_GoOutBlankLine, s_Um_andere_Charaktere_einzuladen_muss_801E022C, s_mindestens_ein_freier_Platz_vorhanden_sein_801E0254, lbl_801E0280, lbl_801E02A8,
    lbl_801E02D8, lbl_801E02FC, lbl_801E0320, s_pro_Spielstand_vorhanden_sein_801E034C, lbl_801E036C,
    s_Ja_Nein_801DFD30, lbl_801E038C, lbl_801E03B0, lbl_801E03D4, s_Ja_Nein_801DFD30,
    lbl_801E03F8, lbl_801E041C, lbl_801E0440, s_GoOutBlankLine, lbl_801E045C,
    lbl_801E0480, lbl_801E04A4, lbl_801E04CC, lbl_801E04F8, lbl_801E0514,
    lbl_801E0538, lbl_801E0560, lbl_801E0588, lbl_801E05B0, s_Ja_Nein_801DFD30,
    lbl_801E05D4, lbl_801E05F8, s_nicht_wiederhergestellt_werden_801E0624, lbl_801E0644, s_Ja_Nein_801DFD30,
    lbl_801E065C, lbl_801E0680, lbl_801E06A8, lbl_801E06CC, s_GoOutBlankLine,
    s_Um_einen_Charakter_zu_bewegen_muss_zuvor_801E06F0, s_mindestens_ein_Charakter_kreiert_und_auf_der_801E071C, s_Memory_Card_gespeichert_werden_801E074C, s_Aus_der_aktuellen_Spielsitzung_801E076C, lbl_801E078C,
    s_La_Memory_Card_Scheda_Memoria_nello_801E07B4, s_Slot_A_non_contiene_dati_della_801E07DC, s_partita_in_corso_Inserisci_nello_801E07FC, s_Slot_A_una_Memory_Card_Scheda_Memoria_801E0820, s_contenente_dei_dati_di_gioco_adatti_801E0848,
    lbl_801E0870, s_GoOutBlankLine, s_Se_vuoi_trasferire_un_personaggio_801E0890, s_devi_prima_salvare_la_partita_801E08B4, s_I_dati_del_personaggio_di_questa_801E08D4,
    s_partita_non_sono_ancora_stati_salvati_801E08F8, s_GoOutBlankLine, s_Se_vuoi_trasferire_un_personaggio_801E0890, s_devi_prima_salvare_la_partita_801E08B4, s_Inserisci_nello_Slot_A_una_Memory_Card_Scheda_801E0920,
    s_Memoria_contenente_i_dati_di_questa_partita_801E0950, s_Inserisci_nello_Slot_B_una_Memory_Card_Scheda_801E0980, s_Memoria_con_i_dati_del_personaggio_da_trasferire_801E09B0, s_GoOutBlankLine, s_Non_rimuovere_le_due_Memory_Card_Schede_Memoria_801E09E4,
    s_fino_al_completamento_del_trasferimento_801E0A18, s_Vuoi_trasferire_il_personaggio_801E0A44, s_selezionato_nella_partita_801E0A64, lbl_801E0A80, s_disponibile_fino_al_suo_ritorno_801E0AA4,
    lbl_801E0AC8, s_Vuoi_far_tornare_il_personaggio_801E0AD4, s_selezionato_alla_partita_801E0AF4, s_in_corso_I_dati_del_personaggio_801E0B10, s_ospite_saranno_cancellati_801E0B34,
    lbl_801E0AC8, s_Salvataggio_sulla_Memory_Card_Scheda_801E0B50, s_Memoria_nello_Slot_A_in_corso_801E0B78, s_Non_toccare_la_Memory_Card_Scheda_801E0B98, s_Memoria_o_il_Pulsante_POWER_801E0BBC,
    s_Salvataggio_sulla_Memory_Card_Scheda_801E0B50, s_Memoria_nello_Slot_B_in_corso_801E0BDC, s_Non_toccare_la_Memory_Card_Scheda_801E0B98, s_Memoria_o_il_Pulsante_POWER_801E0BBC, lbl_801E0BFC,
    s_Trasferimento_del_personaggio_annullato_801E0C30, s_GoOutBlankLine, s_Non_rimuovere_le_Memory_Card_Schede_Memoria_801E0C5C, s_fino_al_completamento_del_trasferimento_del_personaggio_801E0C8C, lbl_801E0CC8,
    s_nessuna_Memory_Card_Scheda_Memoria_801E0CE4, lbl_801E0D0C, s_nessuna_Memory_Card_Scheda_Memoria_801E0CE4, s_Questi_dati_sono_una_copia_dei_dati_della_801E0D28, s_partita_in_corso_e_non_possono_essere_usati_801E0D54,
    s_La_Memory_Card_Scheda_Memoria_nello_Slot_B_801E0D84, s_non_contiene_dati_di_FINAL_FANTASY_Crystal_801E0DB4, s_Chronicles_o_contiene_dati_danneggiati_801E0DE0, s_GoOutBlankLine, s_GoOutBlankLine,
    s_Inserisci_nello_Slot_B_una_Memory_Card_801E0E08, s_Scheda_Memoria_contenente_dei_dati_validi_801E0E30, s_Non_puoi_trasferire_dei_personaggi_801E0E60, s_che_sono_in_missione_801E0E84, lbl_801E0E9C,
    s_di_gioco_attuali_impossibile_801E0EC4, s_trasferirlo_801E0EE4, s_I_dati_di_gioco_attuali_contengono_801E0EF4, lbl_801E0F18, s_trasferirne_altri_801E0F38,
    s_GoOutBlankLine, s_Prima_di_trasferire_un_altro_personaggio_801E0F4C, s_devi_cancellarne_almeno_uno_801E0F78, s_I_personaggi_ospiti_possono_essere_trasferiti_801E0F98, s_solo_al_loro_salvataggio_d_origine_801E0FC8,
    lbl_801E0FEC, s_GoOutBlankLine, s_Deve_rimanere_almeno_un_personaggio_801E101C, s_non_ospite_801E1040, s_Vuoi_cancellare_questo_personaggio_801E104C,
    lbl_801E0AC8, s_Una_volta_cancellato_il_personaggio_801E1070, lbl_801E1098, s_Vuoi_procedere_801E10B0, lbl_801E0AC8,
    lbl_801E10C0, s_GoOutBlankLine, s_Ricarica_i_dati_salvati_801E10EC, s_originali_del_personaggio_801E1104, s_GoOutBlankLine,
    s_Per_recuperare_un_personaggio_in_missione_801E1120, s_seleziona_Cancella_Personaggio_e_poi_801E114C, s_il_personaggio_da_recuperare_801E1174, lbl_801E1194, lbl_801E11B8,
    lbl_801E11DC, s_Se_vuoi_cancellare_un_personaggio_801E11FC, s_devi_prima_ripristinarne_i_dati_801E1220, s_Vuoi_ripristinare_i_dati_del_personaggio_801E1244, lbl_801E0AC8,
    s_Una_volta_caricati_801E1270, s_i_dati_trasferiti_non_possono_801E1284, s_essere_riportati_qui_801E12A4, s_Vuoi_procedere_801E10B0, lbl_801E0AC8,
    lbl_801E12BC, s_I_dati_di_gioco_attuali_non_contengono_801E12E0, lbl_801E1308, s_trasferirne_nessuno_801E132C, s_GoOutBlankLine,
    s_Per_trasferire_un_personaggio_devi_prima_801E1344, s_crearne_uno_e_poi_salvarlo_sulla_801E1370, s_Memory_Card_Scheda_Memoria_801E1394, lbl_801E13B4, s_cancellato_dai_dati_attuali_801E13D8,
    lbl_801E13F8, lbl_801E1424, lbl_803331C4, lbl_801E1450, lbl_801E1480,
    lbl_801E14B0, lbl_803331C4, s_Pour_pouvoir_importer_un_personnage_vous_801E14D8, s_devez_d_abord_sauvegarder_la_partie_801E1504, lbl_801E152C,
    lbl_801E155C, lbl_803331C4, s_Pour_pouvoir_importer_un_personnage_vous_801E14D8, s_devez_d_abord_sauvegarder_la_partie_801E1504, lbl_801E1584,
    lbl_801E15BC, lbl_801E15EC, lbl_801E1624, lbl_803331C4, lbl_801E1658,
    lbl_801E1690, s_Voulez_vous_vraiment_importer_le_personnage_801E16BC, lbl_801E16E8, s_personnage_sera_indisponible_dans_sa_partie_801E1710, lbl_801E173C,
    s_Oui_Non_801E175C, lbl_801E176C, lbl_801E1790, lbl_801E17B8, lbl_801E17DC,
    s_Oui_Non_801E175C, lbl_801E1804, lbl_801E182C, lbl_801E1854, lbl_801E1874,
    lbl_801E1804, lbl_801E1898, lbl_801E1854, lbl_801E1874, lbl_801E18C0,
    s_Annulation_du_transfert_de_personnage_801E18F0, lbl_803331C4, lbl_801E1658, lbl_801E1918, lbl_801E1950,
    lbl_801E1974, lbl_801E1950, lbl_801E1994, s_Ce_fichier_est_une_copie_du_fichier_de_la_801E19B4, lbl_801E19E0,
    lbl_801E1A10, lbl_801E1A40, s_FINAL_FANTASY_Crystal_Chronicles_ou_contient_801E1A70, lbl_801E1AA0, lbl_801E1AB8,
    lbl_801E1AE8, s_sauvegarde_valides_801E1B14, s_Il_est_impossible_d_importer_un_801E1B28, s_personnage_qui_est_parti_en_voyage_801E1B48, s_Le_fichier_actuel_contient_801E1B70,
    lbl_801E1B8C, lbl_801E1BA8, lbl_801E1BC4, s_personnages_Aucun_personnage_801E1BE4, lbl_801E1C04,
    lbl_803331C4, s_Vous_devez_effacer_au_moins_un_personnage_801E1C2C, s_avant_de_pouvoir_effectuer_un_transfert_801E1C58, lbl_801E1C84, lbl_801E1CA8,
    lbl_801E1CD4, lbl_803331C4, s_Il_doit_rester_au_moins_un_801E1CFC, lbl_801E1D18, s_Effacer_ce_personnage_801E1D3C,
    s_Oui_Non_801E175C, lbl_801E1D54, lbl_801E1D7C, s_Effacer_le_personnage_801E1DA8, s_Oui_Non_801E175C,
    lbl_801E1DC0, lbl_803331C4, s_Veuillez_restaurer_la_sauvegarde_d_origine_de_ce_801E1DE8, s_personnage_801E1E1C, lbl_803331C4,
    lbl_801E1E28, lbl_801E1E54, lbl_801E1E84, lbl_801E1EB0, s_Ce_personnage_est_actuellement_en_voyage_801E1ECC,
    lbl_801E1EF8, lbl_801E1F24, s_de_pouvoir_l_effacer_801E1F50, lbl_801E1F68, s_Oui_Non_801E175C,
    lbl_801E1F90, lbl_801E1FD0, lbl_801E2010, lbl_801E2050, s_Oui_Non_801E175C,
    lbl_801E2090, s_Le_fichier_actuel_ne_contient_aucun_801E20B0, s_personnage_donc_aucun_personnage_801E20D4, lbl_801E20F8, lbl_803331C4,
    s_Pour_importer_un_personnage_vous_devez_801E2110, lbl_801E2138, lbl_801E2164, lbl_801E2188, lbl_801E21A8,
    s_La_Memory_Card_tarjeta_de_memoria_de_la_801E21C4, s_Ranura_A_no_contiene_datos_del_juego_801E21F0, s_Por_favor_inserta_una_Memory_Card_801E2218, s_tarjeta_de_memoria_que_contenga_801E223C, s_datos_del_juego_en_la_Ranura_A_801E2260,
    s_Esta_partida_no_ha_sido_guardada_801E2280, s_GoOutBlankLine, s_Antes_de_transferir_un_personaje_801E22A4, s_debes_guardar_tu_partida_801E22C8, s_Esta_partida_contiene_datos_de_personajes_801E22E4,
    lbl_801E2310, s_GoOutBlankLine, s_Antes_de_transferir_un_personaje_801E22A4, s_debes_guardar_tu_partida_801E22C8, s_Por_favor_inserta_una_Memory_Card_tarjeta_de_memoria_801E2330,
    s_en_la_Ranura_A_con_los_datos_de_la_partida_actual_y_801E2368, s_otra_Memory_Card_tarjeta_de_memoria_en_la_Ranura_B_801E239C, s_con_los_datos_del_personaje_a_transferir_801E23D4, s_GoOutBlankLine, s_Por_favor_no_extraigas_ninguna_de_las_Memory_Card_tarjetas_801E2400,
    s_de_memoria_hasta_que_la_transferencia_haya_finalizado_801E2440, lbl_801E2478, s_seleccionado_al_juego_actual_801E24A4, lbl_801E24C4, s_hasta_que_lo_devuelvas_801E24E8,
    lbl_801E2500, lbl_801E250C, s_personaje_seleccionado_al_juego_801E252C, s_actual_Los_datos_del_personaje_801E254C, lbl_801E256C,
    lbl_801E2500, s_Guardando_datos_en_la_Memory_Card_tarjeta_801E2588, s_de_memoria_en_la_Ranura_A_801E25B4, s_Por_favor_no_toques_ni_la_Memory_Card_801E25D0, lbl_801E25F8,
    s_Guardando_datos_en_la_Memory_Card_tarjeta_801E2588, s_de_memoria_de_la_Ranura_B_801E2620, s_Por_favor_no_toques_ni_la_Memory_Card_801E25D0, lbl_801E25F8, lbl_801E263C,
    lbl_801E267C, s_GoOutBlankLine, s_Por_favor_no_extraigas_ninguna_de_las_Memory_Card_tarjetas_de_memoria_801E26AC, s_hasta_que_la_transferencia_del_personaje_haya_finalizado_801E26F4, s_No_se_ha_encontrado_ninguna_Memory_Card_801E2730,
    s_tarjeta_de_memoria_en_la_Ranura_A_801E2758, s_No_se_ha_encontrado_ninguna_Memory_Card_801E2730, s_tarjeta_de_memoria_en_la_Ranura_B_801E2780, s_Estos_datos_son_una_copia_de_los_datos_del_801E27A8, s_juego_actual_y_no_pueden_ser_utilizados_801E27D4,
    s_La_Memory_Card_tarjeta_de_memoria_de_la_Ranura_B_801E2800, s_no_contiene_datos_de_partidas_de_FINAL_FANTASY_801E2834, lbl_801E2864, s_GoOutBlankLine, s_Por_favor_inserta_una_Memory_Card_tarjeta_de_801E2894,
    lbl_801E28C4, s_partidas_de_FINAL_FANTASY_Crystal_Chronicles_801E28F4, s_No_puedes_transferir_personajes_que_801E2924, lbl_801E2948, s_Los_datos_de_la_partida_actual_contienen_801E2970,
    s_el_mismo_personaje_de_modo_que_este_801E299C, s_personaje_no_puede_ser_transferido_801E29C4, s_Los_datos_de_la_partida_actual_contienen_ocho_801E29E8, s_personajes_de_modo_que_no_es_posible_801E2A18, lbl_801E2A40,
    s_GoOutBlankLine, s_Debes_eliminar_al_menos_un_personaje_801E2A58, s_antes_de_tranferir_otro_801E2A80, s_Los_personajes_invitados_solo_pueden_ser_transferidos_801E2A9C, s_hacia_donde_estaban_originalmente_guardados_801E2AD4,
    s_Este_personaje_no_puede_ser_borrado_801E2B04, s_GoOutBlankLine, s_Debes_mantener_al_menos_uno_de_801E2B2C, s_los_personajes_no_invitados_801E2B4C, lbl_801E2B6C,
    lbl_801E2500, s_Una_vez_que_un_personaje_es_borrado_801E2B8C, s_los_datos_no_pueden_recuperarse_801E2BB0, lbl_801E2BD4, lbl_801E2500,
    s_El_personaje_invitado_ha_sido_borrado_801E2BE8, s_GoOutBlankLine, s_Por_favor_restituye_los_datos_801E2C10, s_guardados_originalmente_801E2C30, s_GoOutBlankLine,
    lbl_801E2C4C, s_utilizado_selecciona_Borrar_Personaje_y_801E2C78, s_luego_el_personaje_que_quieras_restituir_801E2CA4, s_El_personaje_ha_sido_borrado_801E2CD0, lbl_801E2CF0,
    s_y_no_puede_ser_borrado_Debes_801E2D14, s_restituir_los_datos_del_801E2D34, s_personaje_para_poder_borrarlo_801E2D4C, lbl_801E2D6C, lbl_801E2500,
    lbl_801E2D8C, s_transferidos_no_pueden_ser_801E2DAC, lbl_801E2DC8, lbl_801E2DD8, lbl_801E2500,
    lbl_801E2DEC, s_La_partida_actual_no_contiene_801E2E10, s_personajes_de_modo_que_no_es_801E2E30, s_posible_transferir_ninguno_801E2E50, s_GoOutBlankLine,
    s_Para_transferir_un_personaje_debes_801E2E6C, s_crear_uno_primero_y_guardar_los_datos_801E2E90, s_en_una_Memory_Card_tarjeta_de_memoria_801E2EB8, s_El_personaje_no_puede_ser_801E2EE4, s_eliminado_de_los_datos_actuales_801E2F00,
};

struct GoOutMenuState
{
    unsigned char unk0[0x18];
    signed short m_waitFrames;
    signed short unk1A;
    signed short m_closeMode;
    signed short m_resultDir;
    signed short m_resultSelect;
    signed short m_animFrame;
};

struct CGoOutSaveCaravan
{
    int m_dataPresent;
    unsigned char unk4[0x308];
    unsigned char m_odekakeOutFlag;
    unsigned char m_odekakeReturnFlag;
    unsigned char unk30E[0x6B2];
};

struct CGoOutSaveDatLayout
{
    unsigned char unk0[0x1A84];
    CGoOutSaveCaravan m_caravan[8];
};

static inline unsigned char ReadGoOutU8(CGoOutMenu& menu, int offset) { return *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(&menu) + offset); }

static inline GoOutMenuState& MenuGoOutState()
{
    return *MenuPcs.m_goOutState;
}

static inline unsigned short GetGoOutInputMask()
{
    bool hasPendingInput = false;
    if ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) {
        hasPendingInput = true;
    }
    if (hasPendingInput) {
        return 0;
    }

    int padIndex = 0;
    padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
    return static_cast<unsigned short>(Pad.GetPadInputs()[padIndex].buttonDown[0]);
}

static inline const char* GetGoOutMessageLine(int languageId, int line)
{
    return g_strGooutMes[(languageId * 0x6E) + line];
}

static const char s_gooutCpp[] = "goout.cpp";

static inline CGoOutSaveDatLayout& GoOutSaveDat(Mc::SaveDat* saveData)
{
    return *reinterpret_cast<CGoOutSaveDatLayout*>(saveData);
}

static inline int FindFreeCaravanIdx(Mc::SaveDat* saveData)
{
    for (int i = 0; i < 8; i++) {
        if (GoOutSaveDat(saveData).m_caravan[i].m_dataPresent == 0) {
            return i;
        }
    }

    return -1;
}

/*
 * --INFO--
 * PAL Address: 0x80168130
 * PAL Size: 676b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void DrawGoOutMenu()
{
    CGoOutMenu& goOutMenu = g_GoOutMenu;
    g_pGoOutMenu = &goOutMenu;
    unsigned char mode = goOutMenu.m_mainMode;

    switch (mode) {
    case 2:
        if (goOutMenu.m_saveLoadMenuOpen != 0) {
            MenuPcs.DrawInit();
            MenuPcs.DrawCMakeMenu();
        }
        if (goOutMenu.m_goOutMode != 0xF && goOutMenu.m_goOutMode < 0xF && goOutMenu.m_goOutMode >= 0xE) {
            MenuPcs.DrawLoadMenu();
        }
        if (goOutMenu.m_goOutMode == 1 &&
            MenuGoOutState().m_resultSelect != 0) {
            MenuGoOutState().m_closeMode = 8;
            goOutMenu.SetMainMode(1);
            MenuGoOutState().m_resultSelect = 0;
        }
        break;
    case 3:
        MenuPcs.DrawInit();
        MenuPcs.DrawCMakeMenu();
        if (goOutMenu.m_deleteMode == 1 &&
            MenuGoOutState().m_resultSelect != 0) {
            MenuGoOutState().m_closeMode = 8;
            goOutMenu.SetMainMode(1);
            MenuGoOutState().m_resultSelect = 0;
        }
        break;
    }

    if (goOutMenu.m_currentMessage != -1) {
        MenuPcs.DrawMcWin(-1, 0);
        if (MenuPcs.m_menuWindowInfo->state == 1) {
            const unsigned int message = static_cast<unsigned int>(goOutMenu.m_currentMessage);
            MenuPcs.DrawMcWinMess(message, (goOutMenu.m_currentMessage < 0x1E) ? 0 : 2);
        }
    }

    if (MenuPcs.m_menuWindowInfo->state == 1 && goOutMenu.m_drawCursor != 0) {
        const float cursorY = (float)(MenuPcs.m_menuWindowInfo->y +
            MenuPcs.m_menuWindowInfo->height - 0x3E);
        float cursorX = (float)(MenuPcs.m_menuWindowInfo->x + 0x20);

        if (goOutMenu.m_cursorMode != 0) {
            const int localY = goOutMenu.m_cursorListY1 + goOutMenu.m_cursorChoice * 0x1E;
            MenuPcs.DrawCursor((int)cursorX, localY, 1.0f);
        } else {
            cursorX = (float)MenuPcs.GetYesNoXPos(goOutMenu.m_cursorChoice);
            MenuPcs.DrawCursor((int)cursorX, (int)cursorY, 1.0f);
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int getFreeCaravanIdx(Mc::SaveDat* saveData)
{
    g_freeCaravanIdx = FindFreeCaravanIdx(saveData);
    return g_freeCaravanIdx;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::CharaSelClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMemCardSlot(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMemCardProc(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMemCardSaveBuff(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::GetMemCardResult()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::CalcMemCardProc()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8016c564
 * PAL Size: 1156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned char CGoOutMenu::SetMemCardError()
{
    switch (m_memCardResult) {
    case -5:
        MenuPcs.m_menuWindowInfo->state = 3;
        MenuGoOutState().m_animFrame = 0;
        m_currentMessage = -1;
        m_messageTimer = 0;
        m_messageState = 1;
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 3;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        break;
    case -13:
    case -6:
        SetGoOutMode(3);
        return 1;
    case -999:
    case -1000:
        if (m_lastMemCardProc == 1) {
            MenuPcs.m_menuWindowInfo->state = 3;
            MenuGoOutState().m_animFrame = 0;
            m_currentMessage = -1;
            m_messageTimer = 0;
            m_messageState = 1;
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 5,
                       GetGoOutMessageLine(languageId, 0),
                       GetGoOutMessageLine(languageId, 1),
                       GetGoOutMessageLine(languageId, 2),
                       GetGoOutMessageLine(languageId, 3),
                       GetGoOutMessageLine(languageId, 4));
        } else if (m_lastMemCardProc == 3) {
            MenuPcs.m_menuWindowInfo->state = 3;
            MenuGoOutState().m_animFrame = 0;
            m_currentMessage = -1;
            m_messageTimer = 0;
            m_messageState = 1;
            if (m_currentMessage >= 0) {
                MenuPcs.m_menuWindowInfo->state = 2;
                MenuGoOutState().m_animFrame = 0;
            }
            m_messageWindowOpen = 0;
            m_pendingMessage = 0xd;
            m_messageCloseMode = 0;
            m_pendingMessageTimer = 0;
        } else if (m_lastMemCardProc == 2) {
            MenuPcs.m_menuWindowInfo->state = 3;
            MenuGoOutState().m_animFrame = 0;
            m_currentMessage = -1;
            m_messageTimer = 0;
            m_messageState = 1;
            if (m_currentMessage >= 0) {
                MenuPcs.m_menuWindowInfo->state = 2;
                MenuGoOutState().m_animFrame = 0;
            }
            m_messageWindowOpen = 0;
            m_pendingMessage = 0xf;
            m_messageCloseMode = 0;
            m_pendingMessageTimer = 0;
        }
        break;
    case -1:
    case -3:
        MenuPcs.m_menuWindowInfo->state = 3;
        MenuGoOutState().m_animFrame = 0;
        m_currentMessage = -1;
        m_messageTimer = 0;
        m_messageState = 1;
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 1;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        break;
    case -2:
        MenuPcs.m_menuWindowInfo->state = 3;
        MenuGoOutState().m_animFrame = 0;
        m_currentMessage = -1;
        m_messageTimer = 0;
        m_messageState = 1;
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 2;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        break;
    case -4:
        if (m_lastMemCardProc != 1) {
            MenuPcs.m_menuWindowInfo->state = 3;
            MenuGoOutState().m_animFrame = 0;
            m_currentMessage = -1;
            m_messageTimer = 0;
            m_messageState = 1;
            if (m_currentMessage >= 0) {
                MenuPcs.m_menuWindowInfo->state = 2;
                MenuGoOutState().m_animFrame = 0;
            }
            m_messageWindowOpen = 0;
            m_pendingMessage = 0x13;
            m_messageCloseMode = 0;
            m_pendingMessageTimer = 0;
        } else {
            MenuPcs.m_menuWindowInfo->state = 3;
            MenuGoOutState().m_animFrame = 0;
            m_currentMessage = -1;
            m_messageTimer = 0;
            m_messageState = 1;
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 5,
                       GetGoOutMessageLine(languageId, 0),
                       GetGoOutMessageLine(languageId, 1),
                       GetGoOutMessageLine(languageId, 2),
                       GetGoOutMessageLine(languageId, 3),
                       GetGoOutMessageLine(languageId, 4));
        }
        break;
    case 1:
        return 0;
    }

    m_goOutMode = 2;
    return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMenu(short message, long timer)
{
    if (m_currentMessage >= 0) {
        MenuPcs.m_menuWindowInfo->state = 2;
        MenuGoOutState().m_animFrame = 0;
    }

    m_messageState = 1;
    m_messageWindowOpen = 0;
    m_pendingMessage = message;
    m_messageCloseMode = 0;
    m_pendingMessageTimer = static_cast<int>(timer);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMenuStr(long timer, int lineCount, ...)
{
    va_list args;
    unsigned int leadingZeros;
    int i;
    int indexBase;
    int mask;
    int* winMessage;
    const char** winMessageBuffer;
    short messageIndex;

    m_menuStringSlot ^= 1;
    winMessage = (int*)MenuPcs.GetWinMess(m_menuStringSlot + 0x22);
    *winMessage = lineCount;

    leadingZeros = (unsigned int)__cntlzw((unsigned int)m_menuStringSlot);
    mask = -static_cast<int>(leadingZeros >> 5 & 1U);
    indexBase = 10;
    indexBase &= ~mask;
    va_start(args, lineCount);
    winMessageBuffer = (const char**)MenuPcs.GetMcWinMessBuff(2);
    for (i = 0; i < lineCount; i++) {
        winMessageBuffer[indexBase + i] = va_arg(args, const char*);
    }
    va_end(args);

    messageIndex = m_menuStringSlot + 0x22;
    if (m_currentMessage >= 0) {
        MenuPcs.m_menuWindowInfo->state = 2;
        MenuGoOutState().m_animFrame = 0;
    }

    m_messageWindowOpen = 0;
    m_pendingMessage = messageIndex;
    m_messageCloseMode = 0;
    m_pendingMessageTimer = timer;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::CalcMenu()
{
    if (MenuPcs.m_menuWindowInfo->state == 1) {
        m_messageState = 1;
        m_messageWindowOpen = 1;
    }

    if (m_messageState != 0 && MenuPcs.m_menuWindowInfo->state == 3) {
        short x;
        short y;

        m_currentMessage = m_pendingMessage;
        if (m_pendingMessage != -1) {
            MenuPcs.GetWinSize(static_cast<unsigned short>(m_currentMessage), &x, &y,
                               (m_currentMessage >= 0x1E) ? 2 : 0);
            MenuPcs.SetMcWinInfo(x, y);
            MenuPcs.m_menuWindowInfo->state = 0;
            MenuGoOutState().m_animFrame = 0;
            m_messageTimer = m_pendingMessageTimer;
            m_messageState = 0;
        }
    }

    if (m_messageTimer != 0) {
        m_messageTimer--;
        if (m_messageTimer == 0) {
            SetMenuForceClose();
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::DrawMenu()
{
    if (m_currentMessage != -1) {
        MenuPcs.DrawMcWin(-1, 0);
        if (MenuPcs.m_menuWindowInfo->state == 1) {
            const int message = static_cast<int>(m_currentMessage);
            MenuPcs.DrawMcWinMess(message, (message >= 0x1E) ? 2 : 0);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMenuForceClose()
{
    if (m_currentMessage >= 0) {
        MenuPcs.m_menuWindowInfo->state = 2;
        MenuGoOutState().m_animFrame = 0;
    }

    m_messageWindowOpen = 0;
    m_pendingMessage = -1;
    m_messageCloseMode = 0;
    m_pendingMessageTimer = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::CalcLoadMenu()
{
    CalcMenu();
}

/*
 * --INFO--
 * PAL Address: 0x8016c1a4
 * PAL Size: 616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGoOutMenu::SetMainMode(unsigned char mode)
{
    unsigned char prevMainMode;
    int i;

    {
        MenuPcs.m_goOutSaveLoadMode = 0;
        MenuPcs.m_goOutUnknown88A = 0;
        MenuPcs.m_goOutTransferWorkActive = 0;
    }
    if (m_mainMode == '\x02') {
        MemoryCardMan.McEnd();
    }
    prevMainMode = m_mainMode;
    m_mainMode = mode;
    m_modeFrame = 0;
    switch (mode) {
    case 1: {
        m_cursorChoice = 1;
        if (prevMainMode != 3U) {
            m_cursorChoice = 0;
        }
        MenuPcs.ChgAllModel();
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 0x1e;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        unk_0x14 = 0;
        break;
    }
    case 2:
        if (static_cast<signed char>(Game.m_gameWork.m_mcHasSerial) != 1) {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 4,
                       GetGoOutMessageLine(languageId, 5),
                       GetGoOutMessageLine(languageId, 6),
                       GetGoOutMessageLine(languageId, 7),
                       GetGoOutMessageLine(languageId, 8));
            m_returnGoOutMode = (char)0xff;
            m_goOutMode = 0;
        }
        i = 0;
        do {
            if (Game.m_caravanWorkArr[i].m_shopState != 0 &&
                static_cast<signed char>(Game.m_caravanWorkArr[i].unk_0xc1e) != 1) {
                int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                SetMenuStr(0, 5,
                           GetGoOutMessageLine(languageId, 9),
                           GetGoOutMessageLine(languageId, 10),
                           GetGoOutMessageLine(languageId, 11),
                           GetGoOutMessageLine(languageId, 12),
                           GetGoOutMessageLine(languageId, 13));
                m_returnGoOutMode = (char)0xff;
                m_goOutMode = 0;
            }
            i++;
        } while (i < 8);
        m_memCardProc = 0;
        m_lastMemCardProc = 0;
        m_cardChannel = 0;
        m_saveIndex = 0;
        m_memCardResult = -1;
        m_memCardBuffer = 0;
        SetGoOutMode(7);
        break;
    case 3: {
        MenuPcs.ChgAllModel();
        MenuPcs.m_goOutUnknown888 = 2;
        unk_0x14 = 0;
        m_deleteInitSelChar = 0;
        SetDelMode(2);
        break;
    }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SelectYesNo(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::InitSelectYesNo()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::HitAnyKey()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::HitCanncel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::Init()
{
    memset(this, 0, sizeof(*this));
    m_memCardResult = -1;
    m_returnGoOutMode = -1;
    m_pendingMessage = -1;
    m_currentMessage = -1;
    m_menuStringSlot = 0;
    m_messageState = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::Destroy()
{
    if (MenuPcs.m_goOutTransferSaveData != 0) {
        delete reinterpret_cast<unsigned char*>(MenuPcs.m_goOutTransferSaveData);
        MenuPcs.m_goOutTransferSaveData = 0;
    }
    if (MenuPcs.m_goOutTransferWork != 0) {
        delete static_cast<unsigned char*>(MenuPcs.m_goOutTransferWork);
        MenuPcs.m_goOutTransferWork = 0;
    }

    MenuPcs.m_goOutTransferWorkActive = 0;
    MenuPcs.m_goOutUnknown888 = 0;
    MenuPcs.m_goOutSaveLoadMode = 0;
    MenuPcs.m_goOutUnknown88A = 0;

    if (m_mainMode == 2) {
        MemoryCardMan.McEnd();
    }
}

/*
 * --INFO--
 * PAL Address: 0x8016b8d4
 * PAL Size: 2256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void CGoOutMenu::SetGoOutMode(unsigned char mode)
{

	m_goOutMode = mode;
	switch(m_goOutMode) {
    case 7:
        MenuPcs.m_goOutUnknown888 = 1;
        unk_0x14 = 0;
        m_goOutMode = 7;
        m_watchCardDisconnect = 0;
        m_saveLoadMenuOpen = 0;
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 7,
                       GetGoOutMessageLine(languageId, 14),
                       GetGoOutMessageLine(languageId, 15),
                       GetGoOutMessageLine(languageId, 16),
                       GetGoOutMessageLine(languageId, 17),
                       GetGoOutMessageLine(languageId, 18),
                       GetGoOutMessageLine(languageId, 19),
                       GetGoOutMessageLine(languageId, 20));
        }
        break;
	case 1:
		m_watchCardDisconnect = 0;
        MenuGoOutState().m_resultDir = -1;
        MenuGoOutState().m_waitFrames = 10;
		break;
    case 0xC:
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 0x21;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        MenuPcs.GetMcAccessPos(&m_accessCardChannel, &m_accessSaveIndex);
        m_accessCardChannel = 0;
        MenuPcs.m_mcCtrl.m_cardChannel = m_accessCardChannel;
        m_cardChannel = static_cast<char>(MenuPcs.m_mcCtrl.m_cardChannel);
        m_saveIndex = static_cast<char>(m_accessSaveIndex);
        m_memCardResult = static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(static_cast<signed char>(m_cardChannel));
        if (m_memCardResult == 1) {
            const unsigned char savedSaveIndex = static_cast<unsigned char>(m_saveIndex);
            const unsigned char savedCardChannel = static_cast<unsigned char>(m_cardChannel);
            MenuPcs.m_mcCtrl.m_previousState = 0;
            MenuPcs.m_mcCtrl.m_state = 0;
            MenuPcs.m_mcCtrl.m_lastResult = 0;
            MenuPcs.m_mcCtrl.m_iteration = 0;
            MenuPcs.m_mcCtrl.m_userBuffer = 0;
            MenuPcs.m_mcCtrl.m_createFlag = 0;
            MenuPcs.m_mcCtrl.m_cardChannel = savedCardChannel;
            MenuPcs.m_mcCtrl.m_saveIndex = savedSaveIndex;
            m_memCardProc = 1;
        }
        break;
    case 0xE:
        MenuPcs.InitSaveLoadMenu();
        SetMenuCharaAnim__8CMenuPcsFii2(&MenuPcs);
        MenuPcs.CopyNowCaravanDat(MenuPcs.m_goOutTransferSaveData);
        MenuPcs.m_goOutSaveLoadMode = 2;
        MenuPcs.m_goOutUnknown88A = 1;
        MenuPcs.m_goOutTransferWorkActive = MenuPcs.m_goOutTransferWork;
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = -1;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        break;
    case 0xF:
        MenuPcs.ChgAllModel2();
        if (m_saveLoadMenuOpen == 0) {
            MenuPcs.InitSaveLoadMenu();
        }
        SetMenuCharaAnim__8CMenuPcsFii2(&MenuPcs);
        m_saveLoadMenuOpen = 1;
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = -1;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        MenuPcs.m_goOutSaveLoadMode = 2;
        MenuPcs.m_goOutUnknown88A = 1;
        MenuPcs.m_goOutTransferWorkActive = MenuPcs.m_goOutTransferWork;
        break;
    case 0x10:
        if (m_returnTransfer == 0) {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 5,
                       GetGoOutMessageLine(languageId, 21),
                       GetGoOutMessageLine(languageId, 22),
                       GetGoOutMessageLine(languageId, 23),
                       GetGoOutMessageLine(languageId, 24),
                       GetGoOutMessageLine(languageId, 25));
        } else {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 5,
                       GetGoOutMessageLine(languageId, 26),
                       GetGoOutMessageLine(languageId, 27),
                       GetGoOutMessageLine(languageId, 28),
                       GetGoOutMessageLine(languageId, 29),
                       GetGoOutMessageLine(languageId, 30));
        }
        m_cursorChoice = 1;
        break;
    case 0x11:
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 0x1F;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        m_cursorChoice = 1;
        break;
    case 0x12: {
        m_watchCardDisconnect = 0;
        const int selectedChara = m_selectedTransferChara;
        int freeCaravanIdx;

        if (GoOutSaveDat(static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork)).m_caravan[selectedChara].m_odekakeReturnFlag == 0) {
            freeCaravanIdx = FindFreeCaravanIdx(MenuPcs.m_goOutTransferSaveData);
            MemoryCardMan.Odekake(1, *static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork), selectedChara, *MenuPcs.m_goOutTransferSaveData, freeCaravanIdx);
        } else {
            freeCaravanIdx = MenuPcs.GetSameCharaData(MenuPcs.m_goOutTransferSaveData, static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork), selectedChara, 0);
            MemoryCardMan.Odekake(0, *static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork), m_selectedTransferChara, *MenuPcs.m_goOutTransferSaveData, freeCaravanIdx);
        }

        MenuPcs.m_mcCtrl.m_cardChannel = m_accessCardChannel;
        m_cardChannel = static_cast<char>(MenuPcs.m_mcCtrl.m_cardChannel);
        m_saveIndex = static_cast<char>(m_accessSaveIndex);
        m_memCardBuffer = MenuPcs.m_goOutTransferSaveData;
        m_memCardResult = static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(static_cast<unsigned char>(m_cardChannel));
        if (m_memCardResult == 1) {
            const unsigned char savedSaveIndex = static_cast<unsigned char>(m_saveIndex);
            const unsigned char savedCardChannel = static_cast<unsigned char>(m_cardChannel);
            MenuPcs.m_mcCtrl.m_previousState = 0;
            MenuPcs.m_mcCtrl.m_state = 0;
            MenuPcs.m_mcCtrl.m_lastResult = 0;
            MenuPcs.m_mcCtrl.m_iteration = 0;
            MenuPcs.m_mcCtrl.m_userBuffer = 0;
            MenuPcs.m_mcCtrl.m_createFlag = 0;
            MenuPcs.m_mcCtrl.m_cardChannel = savedCardChannel;
            MenuPcs.m_mcCtrl.m_saveIndex = savedSaveIndex;
            m_memCardProc = 2;
        }
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 4,
                       GetGoOutMessageLine(languageId, 31),
                       GetGoOutMessageLine(languageId, 32),
                       GetGoOutMessageLine(languageId, 33),
                       GetGoOutMessageLine(languageId, 34));
        }
        break;
    }
    case 0x13:
        MenuPcs.m_mcCtrl.m_cardChannel = static_cast<unsigned char>(m_odekakeCardChannel);
        m_cardChannel = m_odekakeCardChannel;
        m_saveIndex = m_odekakeSaveIndex;
        m_memCardBuffer = MenuPcs.m_goOutTransferWork;
        m_memCardResult = static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(static_cast<unsigned char>(m_cardChannel));
        if (m_memCardResult == 1) {
            const unsigned char savedSaveIndex = static_cast<unsigned char>(m_saveIndex);
            const unsigned char savedCardChannel = static_cast<unsigned char>(m_cardChannel);
            MenuPcs.m_mcCtrl.m_previousState = 0;
            MenuPcs.m_mcCtrl.m_state = 0;
            MenuPcs.m_mcCtrl.m_lastResult = 0;
            MenuPcs.m_mcCtrl.m_iteration = 0;
            MenuPcs.m_mcCtrl.m_userBuffer = 0;
            MenuPcs.m_mcCtrl.m_createFlag = 0;
            MenuPcs.m_mcCtrl.m_cardChannel = savedCardChannel;
            MenuPcs.m_mcCtrl.m_saveIndex = savedSaveIndex;
            m_memCardProc = 2;
        }
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 4,
                       GetGoOutMessageLine(languageId, 35),
                       GetGoOutMessageLine(languageId, 36),
                       GetGoOutMessageLine(languageId, 37),
                       GetGoOutMessageLine(languageId, 38));
        }
        break;
    case 0x14:
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 0x20;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        break;
	case 3:
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
		m_messageWindowOpen = 0;
		m_pendingMessage = 4;
		m_messageCloseMode = 0;
		m_pendingMessageTimer = 0;
		m_cursorChoice = 1;
		break;
	case 4:
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
		m_messageWindowOpen = 0;
		m_pendingMessage = 5;
		m_messageCloseMode = 0;
		m_pendingMessageTimer = 0;
		m_cursorChoice = 1;
		break;
    case 5:
        m_memCardResult = static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(static_cast<unsigned char>(m_cardChannel));
        if (m_memCardResult == 1) {
            const unsigned char savedSaveIndex = static_cast<unsigned char>(m_saveIndex);
            const unsigned char savedCardChannel = static_cast<unsigned char>(m_cardChannel);
            MenuPcs.m_mcCtrl.m_previousState = 0;
            MenuPcs.m_mcCtrl.m_state = 0;
            MenuPcs.m_mcCtrl.m_lastResult = 0;
            MenuPcs.m_mcCtrl.m_iteration = 0;
            MenuPcs.m_mcCtrl.m_userBuffer = 0;
            MenuPcs.m_mcCtrl.m_createFlag = 0;
            MenuPcs.m_mcCtrl.m_cardChannel = savedCardChannel;
            MenuPcs.m_mcCtrl.m_saveIndex = savedSaveIndex;
            m_memCardProc = 3;
        }
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 7;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        break;
    case 6:
        if (MenuPcs.m_menuWindowInfo->state == 1) {
            MenuPcs.m_menuWindowInfo->state = 3;
            MenuGoOutState().m_animFrame = 0;
            m_currentMessage = -1;
            m_messageTimer = 0;
            m_messageState = 1;
        }
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = 0xc;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        m_cursorChoice = 1;
        break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8016a06c
 * PAL Size: 6248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGoOutMenu::CalcGoOut()
{
    unsigned short input;

    if (m_watchCardDisconnect != 0 && m_modeFrame >= 0x14 && (m_modeFrame & 0xF) == 0) {
        if ((m_modeFrame & 0x10) != 0) {
            if (static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(0) == 1) {
                goto card_connected;
            }
        card_disconnected:
            m_watchCardDisconnect = 0;
            m_returnGoOutMode = -1;
            m_goOutMode = 0;
            MenuPcs.m_menuWindowInfo->state = 3;
            MenuGoOutState().m_animFrame = 0;
            m_currentMessage = -1;
            m_messageTimer = 0;
            m_messageState = 1;
            {
                int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                SetMenuStr(0, 5,
                           GetGoOutMessageLine(languageId, 39),
                           GetGoOutMessageLine(languageId, 40),
                           GetGoOutMessageLine(languageId, 41),
                           GetGoOutMessageLine(languageId, 42),
                           GetGoOutMessageLine(languageId, 43));
            }
            return;
        }
        if (static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(1) != 1) {
            goto card_disconnected;
        }
    }
card_connected:;

    int selResult = -1;
    if (m_saveLoadMenuOpen != 0) {
        const unsigned char selInit = static_cast<unsigned char>(__cntlzw(0xF - static_cast<int>(m_goOutMode)) >> 5 & 0xFF);
        selResult = MenuPcs.CalcGoOutSelChar(selInit, 1);
    }

    switch (m_goOutMode) {
    case 0:
        if (m_messageWindowOpen == 0) {
            break;
        }

        input = GetGoOutInputMask();
        {
            bool pressed;
            if ((input & 0x100) != 0) {
                Sound.PlaySe(2, 0x40, 0x7f, 0);
                pressed = true;
            } else {
                pressed = false;
            }
            if (pressed) {
                if (m_returnGoOutMode == -1) {
                    SetMainMode(1);
                } else {
                    SetGoOutMode(m_returnGoOutMode);
                }
            }
        }
        break;
    case 2:
        if (m_messageWindowOpen == 0) {
            break;
        }

        input = GetGoOutInputMask();
        {
            bool pressed;
            if ((input & 0x100) != 0) {
                Sound.PlaySe(2, 0x40, 0x7f, 0);
                pressed = true;
            } else {
                pressed = false;
            }
            if (pressed) {
                SetMainMode(1);
            }
        }
        break;
    case 7:
        if (m_messageWindowOpen == 0) {
            break;
        }

        input = GetGoOutInputMask();
        {
            bool pressed;
            if ((input & 0x100) != 0) {
                Sound.PlaySe(2, 0x40, 0x7f, 0);
                pressed = true;
            } else {
                pressed = false;
            }
            if (pressed) {
                SetGoOutMode(8);
            }
        }
        break;
    case 8:
        if (static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(0) == -1) {
            return;
        }
        m_modeFrame = 0;
        SetGoOutMode(9);
        break;
    case 9:
        if (m_modeFrame < 0x14) {
            return;
        }
        if (static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(0) == -3) {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 2,
                       GetGoOutMessageLine(languageId, 44),
                       GetGoOutMessageLine(languageId, 45));
            m_returnGoOutMode = -1;
            SetGoOutMode(0);
            return;
        }
        SetGoOutMode(0xC);
        break;
    case 0xC:
        if (m_memCardResult != 0) {
            if (SetMemCardError() != 0) {
                return;
            }

            MenuPcs.GetMcAccessPos(&m_accessCardChannel, &m_accessSaveIndex);
            if (m_accessCardChannel == -1) {
                int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                SetMenuStr(0, 5,
                           GetGoOutMessageLine(languageId, 0),
                           GetGoOutMessageLine(languageId, 1),
                           GetGoOutMessageLine(languageId, 2),
                           GetGoOutMessageLine(languageId, 3),
                           GetGoOutMessageLine(languageId, 4));
                m_returnGoOutMode = -1;
                SetGoOutMode(0);
            } else {
                m_accessCardChannel = 0;
                const int cardChannel = m_accessCardChannel;
                const int saveIndex = m_accessSaveIndex;
                m_cardChannel = static_cast<char>(cardChannel);
                m_saveIndex = static_cast<char>(saveIndex);
                MenuPcs.m_mcCtrl.m_cardChannel = cardChannel;
                SetGoOutMode(10);
            }
        }
        break;
    case 10:
        if (static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(1) == -1) {
            return;
        }
        m_modeFrame = 0;
        SetGoOutMode(0xB);
        break;
    case 0xB:
        if (m_modeFrame < 0x14) {
            return;
        }
        if (static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkConnect(1) == -3) {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 2,
                       GetGoOutMessageLine(languageId, 46),
                       GetGoOutMessageLine(languageId, 47));
            m_returnGoOutMode = -1;
            SetGoOutMode(0);
            return;
        }
        SetGoOutMode(0xE);
        break;
    case 0xE:
        if (static_cast<signed char>(MenuPcs.m_goOutLoadFinished) != 0) {
            if (MenuPcs.m_goOutLoadResult == 4) {
                MenuGoOutState().m_resultSelect = 0;
                MenuPcs.InitSaveLoadMenu();
                SetMenuCharaAnim__8CMenuPcsFii2(&MenuPcs);
                if (MenuPcs.CheckSameMcFormatID(MenuPcs.m_goOutTransferSaveData,
                                                static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork)) != 0) {
                    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                    SetMenuStr(0, 2,
                               GetGoOutMessageLine(languageId, 48),
                               GetGoOutMessageLine(languageId, 49));
                    m_returnGoOutMode = -1;
                    SetGoOutMode(0);
                    return;
                }

                int odekakeX;
                int odekakeY;
                MenuPcs.GetMcOdekakePos(&odekakeX, &odekakeY);
                m_odekakeCardChannel = static_cast<char>(odekakeX);
                m_odekakeSaveIndex = static_cast<char>(odekakeY);
                SetGoOutMode(0xF);
                m_watchCardDisconnect = 1;
            } else if (MenuPcs.m_goOutLoadResult == 1) {
                SetMainMode(1);
            } else {
                MenuGoOutState().m_resultSelect = 0;
                MenuPcs.InitSaveLoadMenu();
                SetMenuCharaAnim__8CMenuPcsFii2(&MenuPcs);
                int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                SetMenuStr(0, 7,
                           GetGoOutMessageLine(languageId, 50),
                           GetGoOutMessageLine(languageId, 51),
                           GetGoOutMessageLine(languageId, 52),
                           GetGoOutMessageLine(languageId, 53),
                           GetGoOutMessageLine(languageId, 54),
                           GetGoOutMessageLine(languageId, 55),
                           GetGoOutMessageLine(languageId, 56));
                m_returnGoOutMode = -1;
                SetGoOutMode(0);
            }
        }
        if (m_currentMessage == -1) {
            MenuPcs.CalcLoadMenu();
        }
        break;
    case 0xF:
        m_selectedTransferChara = selResult;
        if (m_selectedTransferChara == -2) {
            SetGoOutMode(1);
            return;
        }
        if (m_selectedTransferChara != -1) {
            if (GoOutSaveDat(static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork)).m_caravan[m_selectedTransferChara].m_odekakeOutFlag != 0) {
                int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                SetMenuStr(0, 2,
                           GetGoOutMessageLine(languageId, 57),
                           GetGoOutMessageLine(languageId, 58));
                m_returnGoOutMode = 0xF;
                SetGoOutMode(0);
            } else {
                m_returnTransfer = 0;
                Mc::SaveDat* transferWork = static_cast<Mc::SaveDat*>(MenuPcs.m_goOutTransferWork);
                if (GoOutSaveDat(transferWork).m_caravan[m_selectedTransferChara].m_odekakeReturnFlag == 0) {
                    int sameChara = MenuPcs.GetSameCharaData(MenuPcs.m_goOutTransferSaveData, transferWork, m_selectedTransferChara, 1);
                    if (sameChara == -3) {
                        m_returnGoOutMode = 0xF;
                        m_goOutMode = 0;
                        int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                        SetMenuStr(0, 3,
                                   GetGoOutMessageLine(languageId, 59),
                                   GetGoOutMessageLine(languageId, 60),
                                   GetGoOutMessageLine(languageId, 61));
                        break;
                    }

                    g_freeCaravanIdx = FindFreeCaravanIdx(MenuPcs.m_goOutTransferSaveData);
                    if (g_freeCaravanIdx < 0) {
                        m_returnGoOutMode = 0xF;
                        m_goOutMode = 0;
                        int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                        SetMenuStr(0, 6,
                                   GetGoOutMessageLine(languageId, 62),
                                   GetGoOutMessageLine(languageId, 63),
                                   GetGoOutMessageLine(languageId, 64),
                                   GetGoOutMessageLine(languageId, 65),
                                   GetGoOutMessageLine(languageId, 66),
                                   GetGoOutMessageLine(languageId, 67));
                        break;
                    }
                } else {
                    g_freeCaravanIdx = MenuPcs.GetSameCharaData(MenuPcs.m_goOutTransferSaveData, transferWork, m_selectedTransferChara, 0);
                    if (g_freeCaravanIdx < 0) {
                        m_returnGoOutMode = 0xF;
                        m_goOutMode = 0;
                        m_returnGoOutMode = 0xF;
                        m_goOutMode = 0;
                        int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                        SetMenuStr(0, 2,
                                   GetGoOutMessageLine(languageId, 68),
                                   GetGoOutMessageLine(languageId, 69));
                        break;
                    }
                    m_returnTransfer = 1;
                }
                SetGoOutMode(0x10);
            }
        }
        break;
    case 0x10:
        if (m_messageWindowOpen == 0) {
            break;
        }

        input = GetGoOutInputMask();
        {
            bool pressed;
            if ((input & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7f, 0);
                pressed = true;
            } else {
                pressed = false;
            }
            if (pressed) {
                SetGoOutMode(0xf);
                break;
            }
        }

        if (m_returnTransfer == 0) {
            m_drawCursor = 1;
            m_cursorListY0 = 0xb1;
            m_cursorListY1 = 0xdc;
            m_cursorMode = 0;
        } else {
            m_drawCursor = 1;
            m_cursorListY0 = 0x8b;
            m_cursorListY1 = 0xdc;
            m_cursorMode = 0;
        }
        {
            unsigned char next;

            if (MenuPcs.m_menuWindowInfo->state != 1) {
                next = 0;
                goto do_switch_go10;
            }

            input = GetGoOutInputMask();
            if ((input & 3) != 0) {
                m_cursorChoice ^= 1;
                Sound.PlaySe(1, 0x40, 0x7f, 0);
            } else {
                input = GetGoOutInputMask();
                if ((input & 0x100) != 0) {
                    if (m_cursorChoice == 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                    } else if (m_cursorChoice == 1) {
                        Sound.PlaySe(3, 0x40, 0x7f, 0);
                    }
                    next = static_cast<unsigned char>(m_cursorChoice + 1);
                    goto do_switch_go10;
                }
            }

            next = 0;
        do_switch_go10:
            switch (next) {
            case 1:
                SetGoOutMode(0x11);
                break;
            case 2:
                SetGoOutMode(0xf);
                break;
            }
        }
        break;
    case 0x11:
        if (m_messageWindowOpen == 0) {
            break;
        }

        input = GetGoOutInputMask();
        {
            bool pressed;
            if ((input & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7f, 0);
                pressed = true;
            } else {
                pressed = false;
            }
            if (pressed) {
                SetGoOutMode(0xf);
                break;
            }
        }

        m_drawCursor = 1;
        m_cursorListY0 = 0xd3;
        m_cursorListY1 = 0xe9;
        m_cursorMode = 0;
        {
            unsigned char next;

            if (MenuPcs.m_menuWindowInfo->state != 1) {
                next = 0;
                goto do_switch_go11;
            }

            input = GetGoOutInputMask();
            if ((input & 3) != 0) {
                m_cursorChoice ^= 1;
                Sound.PlaySe(1, 0x40, 0x7f, 0);
            } else {
                input = GetGoOutInputMask();
                if ((input & 0x100) != 0) {
                    if (m_cursorChoice == 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                    } else if (m_cursorChoice == 1) {
                        Sound.PlaySe(3, 0x40, 0x7f, 0);
                    }
                    next = static_cast<unsigned char>(m_cursorChoice + 1);
                    goto do_switch_go11;
                }
            }

            next = 0;
        do_switch_go11:
            switch (next) {
            case 1:
                SetGoOutMode(0x12);
                break;
            case 2:
                SetGoOutMode(0xf);
                break;
            }
        }
        break;
    case 0x12:
        if (m_messageWindowOpen != 0 && m_memCardResult != 0) {
            if (SetMemCardError() != 0) {
                return;
            }
            SetGoOutMode(0x13);
        }
        break;
    case 0x13:
        if (m_messageWindowOpen != 0 && m_memCardResult != 0) {
            if (SetMemCardError() != 0) {
                return;
            }
            SetGoOutMode(0x14);
        }
        break;
    case 0x14:
        if (m_messageWindowOpen != 0) {
            input = GetGoOutInputMask();
            if ((input & 0x100) != 0) {
                Sound.PlaySe(2, 0x40, 0x7f, 0);
                MenuPcs.SetCaravanWork(MenuPcs.m_goOutTransferSaveData);
                MenuPcs.ChgAllModel();
                SetGoOutMode(1);
            }
        }
        break;
    case 3:
        if (m_messageWindowOpen == 0) {
            break;
        }

        m_drawCursor = 1;
        m_cursorListY0 = 0xcf;
        m_cursorListY1 = 0xe7;
        m_cursorMode = 0;
        {
            signed char next;

            if (MenuPcs.m_menuWindowInfo->state != 1) {
                next = 0;
                goto do_switch_go3;
            }

            input = GetGoOutInputMask();
            if ((input & 3) != 0) {
                m_cursorChoice ^= 1;
                Sound.PlaySe(1, 0x40, 0x7f, 0);
            } else {
                input = GetGoOutInputMask();
                if ((input & 0x100) != 0) {
                    if (m_cursorChoice == 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                    } else if (m_cursorChoice == 1) {
                        Sound.PlaySe(3, 0x40, 0x7f, 0);
                    }

                    next = static_cast<unsigned char>(m_cursorChoice + 1);
                    goto do_switch_go3;
                }
            }

            next = 0;
        do_switch_go3:
            switch (next) {
            case 1:
                SetGoOutMode(4);
                break;
            case 2:
                SetMainMode(1);
                break;
            }
        }
        break;
    case 4:
        if (m_messageWindowOpen == 0) {
            break;
        }

        m_drawCursor = 1;
        m_cursorListY0 = 0xce;
        m_cursorListY1 = 0xde;
        m_cursorMode = 0;
        {
            unsigned char next;

            if (MenuPcs.m_menuWindowInfo->state == 1) {
                input = GetGoOutInputMask();
                if ((input & 3) != 0) {
                    m_cursorChoice ^= 1;
                    Sound.PlaySe(1, 0x40, 0x7f, 0);
                } else {
                    input = GetGoOutInputMask();
                    if ((input & 0x100) != 0) {
                        if (m_cursorChoice == 0) {
                            Sound.PlaySe(2, 0x40, 0x7f, 0);
                        } else if (m_cursorChoice == 1) {
                            Sound.PlaySe(3, 0x40, 0x7f, 0);
                        }

                        next = static_cast<signed char>(m_cursorChoice + 1);
                        goto do_switch_go4;
                    }
                }
            }

            next = 0;
        do_switch_go4:
            switch (next) {
            case 1:
                SetGoOutMode(5);
                break;
            case 2:
                SetMainMode(1);
                break;
            }
        }
        break;
    case 5:
        if (m_messageWindowOpen == 0 || m_memCardResult == 0) {
            break;
        }

        if (SetMemCardError() != 0) {
            return;
        }
        SetGoOutMode(6);
        break;
    case 6:
        if (m_messageWindowOpen == 0) {
            break;
        }

        input = GetGoOutInputMask();
        if ((input & 0x100) != 0) {
            Sound.PlaySe(2, 0x40, 0x7f, 0);
            SetMainMode(1);
        }
        break;
    default:
        break;
    }

    switch (static_cast<unsigned char>(m_memCardProc)) {
    case 1:
        m_memCardResult = static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->ChkNowData();
        if (m_memCardResult != 0) {
            m_lastMemCardProc = m_memCardProc;
            m_memCardProc = 0;
        }
        break;
    case 2:
        static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->SaveDataBuffer(static_cast<char*>(m_memCardBuffer));
        m_memCardResult = MenuPcs.m_mcCtrl.m_lastResult;
        if (m_memCardResult != 0) {
            m_lastMemCardProc = m_memCardProc;
            m_memCardProc = 0;
        }
        break;
    case 3: {
        static_cast<McCtrl*>(&MenuPcs.m_mcCtrl)->Format(1);
        int formatResult = MenuPcs.m_mcCtrl.m_lastResult;
        if (formatResult < 0) {
            MemoryCardMan.m_opDoneFlag = 1;
            MemoryCardMan.m_currentSlot = static_cast<char>(0xff);
        }

        if (formatResult == 0) {
            m_memCardResult = 0;
        } else if (formatResult == 1) {
            m_memCardResult = 1;
        } else if (formatResult == -2) {
            m_memCardResult = -5;
        } else {
            m_memCardResult = -999;
        }

        if (m_memCardResult != 0) {
            m_lastMemCardProc = m_memCardProc;
            m_memCardProc = 0;
        }
        break;
    }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::DrawGoOut()
{

    if (ReadGoOutU8(*this, 0x29) != 0) {
        MenuPcs.DrawInit();
        MenuPcs.DrawCMakeMenu();
    }

    if (m_deleteMode > 0xD && m_deleteMode < 0xF) {
        MenuPcs.DrawLoadMenu();
    }

    if (m_deleteMode == 1 && MenuGoOutState().m_resultSelect != 0) {
        MenuGoOutState().m_closeMode = 8;
        SetMainMode(1);
        MenuGoOutState().m_resultSelect = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80169c18
 * PAL Size: 1108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGoOutMenu::SetDelMode(unsigned char mode)
{

    m_deleteMode = mode;
    switch (m_deleteMode) {
    case 2:
        if (m_currentMessage >= 0) {
            MenuPcs.m_menuWindowInfo->state = 2;
            MenuGoOutState().m_animFrame = 0;
        }
        m_messageWindowOpen = 0;
        m_pendingMessage = -1;
        m_messageCloseMode = 0;
        m_pendingMessageTimer = 0;
        if (m_deleteInitSelChar == 0) {
            MenuPcs.InitSaveLoadMenu();
        }
        SetMenuCharaAnim__8CMenuPcsFii2(&MenuPcs);
        m_deleteInitSelChar = 1;
        break;
    case 1:
        MenuGoOutState().m_resultDir = -1;
        MenuGoOutState().m_waitFrames = 10;
        break;
    case 3: {
        if (Game.m_caravanWorkArr[m_selectedChara].m_caravanLocalFlags == 0) {
            int activeMainCharacterCount = 0;
            for (int i = 0; i < 8; i++) {
                if (Game.m_caravanWorkArr[i].m_objType != 0 && Game.m_caravanWorkArr[i].m_caravanLocalFlags == 0) {
                    activeMainCharacterCount++;
                }
            }

            if (activeMainCharacterCount <= 1) {
                int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                SetMenuStr(0, 4,
                           GetGoOutMessageLine(languageId, 70),
                           GetGoOutMessageLine(languageId, 71),
                           GetGoOutMessageLine(languageId, 72),
                           GetGoOutMessageLine(languageId, 73));
                m_prevDeleteMode = 2;
                SetDelMode(0);
                return;
            }
        }

        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 2,
                       GetGoOutMessageLine(languageId, 74),
                       GetGoOutMessageLine(languageId, 75));
        }
        m_cursorChoice = 1;
        break;
    }
    case 4:
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 4,
                       GetGoOutMessageLine(languageId, 76),
                       GetGoOutMessageLine(languageId, 77),
                       GetGoOutMessageLine(languageId, 78),
                       GetGoOutMessageLine(languageId, 79));
        }
        m_cursorChoice = 1;
        break;
    case 5:
        if (Game.m_caravanWorkArr[m_selectedChara].m_caravanLocalFlags != 0) {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 8,
                       GetGoOutMessageLine(languageId, 80),
                       GetGoOutMessageLine(languageId, 81),
                       GetGoOutMessageLine(languageId, 82),
                       GetGoOutMessageLine(languageId, 83),
                       GetGoOutMessageLine(languageId, 84),
                       GetGoOutMessageLine(languageId, 85),
                       GetGoOutMessageLine(languageId, 86),
                       GetGoOutMessageLine(languageId, 87));
        } else {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 1, GetGoOutMessageLine(languageId, 88));
        }
        m_cursorChoice = 1;
        MenuPcs.SetMenuCharaAnim(m_selectedChara, 5);
        break;
    case 6:
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 6,
                       GetGoOutMessageLine(languageId, 89),
                       GetGoOutMessageLine(languageId, 90),
                       GetGoOutMessageLine(languageId, 91),
                       GetGoOutMessageLine(languageId, 92),
                       GetGoOutMessageLine(languageId, 93),
                       GetGoOutMessageLine(languageId, 94));
        }
        m_cursorChoice = 1;
        break;
    case 7:
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 5,
                       GetGoOutMessageLine(languageId, 95),
                       GetGoOutMessageLine(languageId, 96),
                       GetGoOutMessageLine(languageId, 97),
                       GetGoOutMessageLine(languageId, 98),
                       GetGoOutMessageLine(languageId, 99));
        }
        m_cursorChoice = 1;
        break;
    case 8:
        MenuPcs.SetMenuCharaAnim(m_selectedChara, 3);
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 1, GetGoOutMessageLine(languageId, 100));
        }
        break;
    default:
        break;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80168e3c
 * PAL Size: 3548b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGoOutMenu::CalcDel()
{

    const unsigned char selInit = static_cast<unsigned char>(__cntlzw(2 - static_cast<int>(m_deleteMode)) >> 5 & 0xFF);
    const int selResult = MenuPcs.CalcGoOutSelChar(selInit, 0);
    unsigned short input;

    switch (m_deleteMode) {
    case 0:
        if (m_messageWindowOpen != 0) {
            input = GetGoOutInputMask();
            bool pressed;
            if ((input & 0x100) != 0) {
                Sound.PlaySe(2, 0x40, 0x7f, 0);
                pressed = true;
            } else {
                pressed = false;
            }
            if (pressed) {
                if (m_prevDeleteMode == -1) {
                    SetMainMode(1);
                } else {
                    SetDelMode(m_prevDeleteMode);
                }
            }
        }
        break;
    case 2:
        m_selectedChara = selResult;
        if (m_selectedChara == -2) {
            SetDelMode(1);
        } else if (m_selectedChara != -1) {
            if (Game.m_caravanWorkArr[m_selectedChara].m_shopBusyFlag != 0) {
                SetDelMode(6);
            } else {
                SetDelMode(3);
            }
        }
        break;
    case 3:
        if (m_messageWindowOpen == 0) {
            return;
        }

        input = GetGoOutInputMask();
        {
            bool pressed;
            if ((input & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7f, 0);
                pressed = true;
            } else {
                pressed = false;
            }
            if (pressed) {
                SetDelMode(2);
            }
        }

        m_drawCursor = 1;
        m_cursorListY0 = 0xad;
        m_cursorListY1 = 0xbc;
        m_cursorMode = 0;
        {
            unsigned char next;

            if (MenuPcs.m_menuWindowInfo->state != 1) {
                next = 0;
                goto do_switch_del3;
            }

            input = GetGoOutInputMask();
            if ((input & 3) != 0) {
                m_cursorChoice ^= 1;
                Sound.PlaySe(1, 0x40, 0x7f, 0);
            } else {
                input = GetGoOutInputMask();
                if ((input & 0x100) != 0) {
                    if (m_cursorChoice == 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                    } else if (m_cursorChoice == 1) {
                        Sound.PlaySe(3, 0x40, 0x7f, 0);
                    }
                    next = static_cast<unsigned char>(m_cursorChoice + 1);
                    goto do_switch_del3;
                }
            }

            next = 0;
        do_switch_del3:
            switch (next) {
            case 1:
                SetDelMode(4);
                break;
            case 2:
                SetDelMode(2);
                break;
            }
        }
        break;
    case 4:
        if (m_messageWindowOpen == 0) {
            return;
        }

        input = GetGoOutInputMask();
        {
            bool pressed;
            if ((input & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7f, 0);
                pressed = true;
            } else {
                pressed = false;
            }
            if (pressed) {
                SetDelMode(2);
            }
        }

        m_drawCursor = 1;
        m_cursorListY0 = 0xc2;
        m_cursorListY1 = 0xd1;
        m_cursorMode = 0;
        {
            unsigned char next;

            if (MenuPcs.m_menuWindowInfo->state != 1) {
                next = 0;
                goto do_switch_del4;
            }

            input = GetGoOutInputMask();
            if ((input & 3) != 0) {
                m_cursorChoice ^= 1;
                Sound.PlaySe(1, 0x40, 0x7f, 0);
            } else {
                input = GetGoOutInputMask();
                if ((input & 0x100) != 0) {
                    if (m_cursorChoice == 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                    } else if (m_cursorChoice == 1) {
                        Sound.PlaySe(3, 0x40, 0x7f, 0);
                    }
                    next = static_cast<unsigned char>(m_cursorChoice + 1);
                    goto do_switch_del4;
                }
            }

            next = 0;
        do_switch_del4:
            switch (next) {
            case 1:
                SetDelMode(5);
                break;
            case 2:
                SetDelMode(2);
                break;
            }
        }
        break;
    case 5:
        if (m_messageWindowOpen != 0 && static_cast<int>(MenuPcs.IsMenuCharaAnimIdle(m_selectedChara)) != 0) {
            input = GetGoOutInputMask();
            if ((input & 0x100) != 0) {
                Sound.PlaySe(2, 0x40, 0x7f, 0);
                CCaravanWork& caravanWork = Game.m_caravanWorkArr[m_selectedChara];
                caravanWork.m_shopState = 0;
                memset(reinterpret_cast<unsigned char*>(&caravanWork) + 0x8A4, 0, 0x100);
                memset(reinterpret_cast<unsigned char*>(&caravanWork) + 0x9A4, 0, 0x200);
                SetDelMode(1);
            }
        }
        break;
    case 6:
        if (m_messageWindowOpen == 0) {
            return;
        }

        input = GetGoOutInputMask();
        {
            bool pressed;
            if ((input & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7f, 0);
                pressed = true;
            } else {
                pressed = false;
            }
            if (pressed) {
                SetDelMode(2);
            }
        }

        m_drawCursor = 1;
        m_cursorListY0 = 0x97;
        m_cursorListY1 = 0xe9;
        m_cursorMode = 0;
        {
            unsigned char next;

            if (MenuPcs.m_menuWindowInfo->state != 1) {
                next = 0;
                goto do_switch_del6;
            }

            input = GetGoOutInputMask();
            if ((input & 3) != 0) {
                m_cursorChoice ^= 1;
                Sound.PlaySe(1, 0x40, 0x7f, 0);
            } else {
                input = GetGoOutInputMask();
                if ((input & 0x100) != 0) {
                    if (m_cursorChoice == 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                    } else if (m_cursorChoice == 1) {
                        Sound.PlaySe(3, 0x40, 0x7f, 0);
                    }
                    next = static_cast<unsigned char>(m_cursorChoice + 1);
                    goto do_switch_del6;
                }
            }

            next = 0;
        do_switch_del6:
            switch (next) {
            case 1:
                SetDelMode(7);
                break;
            case 2:
                SetDelMode(2);
                break;
            }
        }
        break;
    case 7:
        if (m_messageWindowOpen == 0) {
            return;
        }

        input = GetGoOutInputMask();
        {
            bool pressed;
            if ((input & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7f, 0);
                pressed = true;
            } else {
                pressed = false;
            }
            if (pressed) {
                SetDelMode(2);
            }
        }

        m_drawCursor = 1;
        m_cursorListY0 = 0x9f;
        m_cursorListY1 = 0xdb;
        m_cursorMode = 0;
        {
            signed char next;

            if (MenuPcs.m_menuWindowInfo->state != 1) {
                next = 0;
                goto do_switch_del7;
            }

            input = GetGoOutInputMask();
            if ((input & 3) != 0) {
                m_cursorChoice ^= 1;
                Sound.PlaySe(1, 0x40, 0x7f, 0);
            } else {
                input = GetGoOutInputMask();
                if ((input & 0x100) != 0) {
                    if (m_cursorChoice == 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                    } else if (m_cursorChoice == 1) {
                        Sound.PlaySe(3, 0x40, 0x7f, 0);
                    }
                    next = static_cast<unsigned char>(m_cursorChoice + 1);
                    goto do_switch_del7;
                }
            }

            next = 0;
        do_switch_del7:
            switch (next) {
            case 1:
                Game.m_caravanWorkArr[m_selectedChara].m_shopBusyFlag = 0;
                SetDelMode(8);
                break;
            case 2:
                SetDelMode(2);
                break;
            }
        }
        break;
    case 8:
        if (m_messageWindowOpen != 0 && static_cast<int>(MenuPcs.IsMenuCharaAnimIdle(m_selectedChara)) != 0) {
            input = GetGoOutInputMask();
            if ((input & 0x100) != 0) {
                Sound.PlaySe(2, 0x40, 0x7f, 0);
                SetDelMode(1);
            }
        }
        break;
    default:
        break;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::DrawDel()
{

    MenuPcs.DrawInit();
    MenuPcs.DrawCMakeMenu();
    if (m_currentMessage == 1 && MenuGoOutState().m_resultSelect != 0) {
        MenuGoOutState().m_closeMode = 8;
        SetMainMode(1);
        MenuGoOutState().m_resultSelect = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80168400
 * PAL Size: 2620b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGoOutMenu::Calc()
{
    unsigned short input;
    char mode;

    m_drawCursor = 0;

    if (MenuPcs.m_goOutReset.m_resetFlag != 0) {
        MenuPcs.m_goOutReset.m_resetFlag = 0;
        MenuPcs.m_menuWindowInfo->state = 3;
        m_currentMessage = -1;
        m_pendingMessage = -1;
        m_menuStringSlot = 0;
        SetMainMode(1);
        MenuPcs.m_goOutTransferSaveData =
            static_cast<Mc::SaveDat*>(operator new(0x8BD0, MenuPcs.m_menuStage, const_cast<char*>(s_gooutCpp), 0x32B));
        MenuPcs.m_goOutTransferWork = operator new(0x8BD0, MenuPcs.m_menuStage, const_cast<char*>(s_gooutCpp), 0x32D);
        MenuPcs.m_goOutTransferWorkActive = 0;
        MenuPcs.m_goOutUnknown888 = 0;
        MenuPcs.m_goOutSaveLoadMode = 0;
        MenuPcs.m_goOutUnknown88A = 0;
        int* winMessage = reinterpret_cast<int*>(MenuPcs.GetWinMess(0x22));
        *winMessage = 0;
        short* winMessageEntries = reinterpret_cast<short*>(winMessage + 1);
        winMessageEntries[0] = 0;
        winMessageEntries[1] = 1;
        winMessageEntries[2] = 2;
        winMessageEntries[3] = 3;
        winMessageEntries[4] = 4;
        winMessageEntries[5] = 5;
        winMessageEntries[6] = 6;
        winMessageEntries[7] = 7;
        winMessage = reinterpret_cast<int*>(MenuPcs.GetWinMess(0x23));
        *winMessage = 0;
        winMessageEntries = reinterpret_cast<short*>(winMessage + 1);
        winMessageEntries[0] = 10;
        winMessageEntries[1] = 11;
        winMessageEntries[2] = 12;
        winMessageEntries[3] = 13;
        winMessageEntries[4] = 14;
        winMessageEntries[5] = 15;
        winMessageEntries[6] = 16;
        winMessageEntries[7] = 17;
        MenuPcs.m_menuWindowInfo->state = 3;
        m_messageState = 1;
    }

    if (m_messageCloseMode == 0) {
        mode = m_mainMode;
        switch (mode) {
        case 0:
            if (m_messageWindowOpen != 0) {
                input = GetGoOutInputMask();
                bool pressed;
                if ((input & 0x100) != 0) {
                    Sound.PlaySe(2, 0x40, 0x7f, 0);
                    pressed = true;
                } else {
                    pressed = false;
                }
                if (pressed) {
                    SetMainMode(m_nextMainMode);
                }
            }
            break;
        case 1:
            if (m_messageWindowOpen != 0) {
                input = GetGoOutInputMask();
                if ((input & 0x200) != 0) {
                    Sound.PlaySe(3, 0x40, 0x7f, 0);
                    MenuPcs.InitSaveLoadMenu();
                    SetMenuCharaAnim__8CMenuPcsFii2(&MenuPcs);
                    MenuGoOutState().m_resultSelect = -1;

                    if (MenuPcs.m_goOutTransferSaveData != 0) {
                        delete reinterpret_cast<unsigned char*>(MenuPcs.m_goOutTransferSaveData);
                        MenuPcs.m_goOutTransferSaveData = 0;
                    }
                    if (MenuPcs.m_goOutTransferWork != 0) {
                        delete static_cast<unsigned char*>(MenuPcs.m_goOutTransferWork);
                        MenuPcs.m_goOutTransferWork = 0;
                    }

                    MenuPcs.m_goOutTransferWorkActive = 0;
                    MenuPcs.m_goOutUnknown888 = 0;
                    MenuPcs.m_goOutSaveLoadMode = 0;
                    MenuPcs.m_goOutUnknown88A = 0;
                    MenuPcs.m_goOutReset.m_resetFlag = 1;
                    MenuPcs.ChgAllModel();
                    return;
                }
                m_drawCursor = 1;
                m_cursorListY0 = 200;
                m_cursorListY1 = 0xB0;
                m_cursorMode = 1;

                unsigned char nextMode;
                if (MenuPcs.m_menuWindowInfo->state != 1) {
                    nextMode = 0;
                    goto do_switch_calc;
                }

                input = GetGoOutInputMask();
                if ((input & 0xC) != 0) {
                    m_cursorChoice ^= 1;
                    Sound.PlaySe(1, 0x40, 0x7f, 0);
                } else {
                    input = GetGoOutInputMask();
                    if ((input & 0x100) != 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                        nextMode = static_cast<unsigned char>(m_cursorChoice + 1);
                        goto do_switch_calc;
                    }
                }

                nextMode = 0;
            do_switch_calc:
                switch (nextMode) {
                case 1: {
                    int characterCount = 0;
                    for (int i = 0; i < 8; i++) {
                        if (Game.m_caravanWorkArr[i].m_shopState != 0) {
                            characterCount++;
                        }
                    }

                    if (characterCount <= 0) {
                        int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                        SetMenuStr(0, 7,
                                   GetGoOutMessageLine(languageId, 101),
                                   GetGoOutMessageLine(languageId, 102),
                                   GetGoOutMessageLine(languageId, 103),
                                   GetGoOutMessageLine(languageId, 104),
                                   GetGoOutMessageLine(languageId, 105),
                                   GetGoOutMessageLine(languageId, 106),
                                   GetGoOutMessageLine(languageId, 107));
                        m_nextMainMode = 1;
                        SetMainMode(0);
                    } else {
                        int transferableCount = 0;
                        for (int i = 0; i < 8; i++) {
                            if (Game.m_caravanWorkArr[i].m_shopState != 0 && Game.m_caravanWorkArr[i].m_shopBusyFlag == 0) {
                                transferableCount++;
                            }
                        }

                        if (transferableCount >= 8) {
                            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                            SetMenuStr(0, 6,
                                       GetGoOutMessageLine(languageId, 62),
                                       GetGoOutMessageLine(languageId, 63),
                                       GetGoOutMessageLine(languageId, 64),
                                       GetGoOutMessageLine(languageId, 65),
                                       GetGoOutMessageLine(languageId, 66),
                                       GetGoOutMessageLine(languageId, 67));
                            m_nextMainMode = 1;
                            SetMainMode(0);
                        } else {
                            SetMainMode(2);
                        }
                    }
                    break;
                }
                case 2: {
                    int activeCount = 0;
                    for (int i = 0; i < 8; i++) {
                        if (Game.m_caravanWorkArr[i].m_shopState != 0) {
                            activeCount++;
                            if (Game.m_caravanWorkArr[i].m_shopBusyFlag != 0) {
                                activeCount++;
                            }
                        }
                    }

                    if (activeCount >= 2) {
                        SetMainMode(3);
                        if (m_currentMessage >= 0) {
                            MenuPcs.m_menuWindowInfo->state = 2;
                            MenuGoOutState().m_animFrame = 0;
                        }
                        m_messageWindowOpen = 0;
                        m_pendingMessage = -1;
                        m_messageCloseMode = 0;
                        m_pendingMessageTimer = 0;
                    } else {
                        int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                        SetMenuStr(0, 2,
                                   GetGoOutMessageLine(languageId, 108),
                                   GetGoOutMessageLine(languageId, 109));
                        m_nextMainMode = 1;
                        SetMainMode(0);
                    }
                    break;
                }
                }
            }
            break;
        case 2:
            CalcGoOut();
            break;
        case 3:
            CalcDel();
            break;
        }

        m_modeFrame = m_modeFrame + 1;
        if (10000 < m_modeFrame) {
            m_modeFrame = 10000;
        }
    }

    if (MenuPcs.m_menuWindowInfo->state == 1) {
        m_messageState = 1;
        m_messageWindowOpen = 1;
    }

    if (m_messageState != 0 && MenuPcs.m_menuWindowInfo->state == 3) {
        short x;
        short y;

        m_currentMessage = m_pendingMessage;
        if (m_pendingMessage != -1) {
            MenuPcs.GetWinSize(static_cast<short>(m_currentMessage), &x, &y, (m_currentMessage < 0x1E) ? 0 : 2);
            MenuPcs.SetMcWinInfo(x, y);
            MenuPcs.m_menuWindowInfo->state = 0;
            MenuGoOutState().m_animFrame = 0;
            m_messageTimer = m_pendingMessageTimer;
            m_messageState = 0;
        } else {
            m_messageState = 1;
        }
    }

    if (m_messageTimer != 0) {
        int remaining = m_messageTimer - 1;
        m_messageTimer = remaining;
        if (remaining == 0) {
            if (m_currentMessage >= 0) {
                MenuPcs.m_menuWindowInfo->state = 2;
                MenuGoOutState().m_animFrame = 0;
            }
            m_messageWindowOpen = 0;
            m_pendingMessage = -1;
            m_messageCloseMode = 0;
            m_pendingMessageTimer = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x801683d4
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CalcGoOutMenu()
{
    g_pGoOutMenu = &g_GoOutMenu;
    g_GoOutMenu.Calc();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::DrawSelectYesNo()
{

    if (MenuPcs.m_menuWindowInfo->state == 1 && m_drawCursor != 0) {
        const int cursorY = MenuPcs.m_menuWindowInfo->y + MenuPcs.m_menuWindowInfo->height - 0x3E;

        if (m_cursorMode == 0) {
            const int cursorX = MenuPcs.GetYesNoXPos(m_cursorChoice);
            MenuPcs.DrawCursor(cursorX, cursorY, 1.0f);
        } else {
            const int cursorX = MenuPcs.m_menuWindowInfo->x + 0x20;
            const int localY = m_cursorListY0 + m_cursorChoice * 0x1E;
            MenuPcs.DrawCursor(cursorX, localY, 1.0f);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::Draw()
{
    if (m_messageState == 3) {
        DrawDel();
    } else if (m_messageState == 2) {
        DrawGoOut();
    }

    DrawMenu();
    DrawSelectYesNo();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::InitMemCardProc()
{
    McCtrl& mcCtrl = *MenuPcs.GetMcCtrl();

    mcCtrl.m_saveIndex = static_cast<unsigned char>(m_saveIndex);
    mcCtrl.m_cardChannel = static_cast<unsigned char>(m_cardChannel);
    mcCtrl.m_previousState = 0;
    mcCtrl.m_state = 0;
    mcCtrl.m_lastResult = 0;
    mcCtrl.m_iteration = 0;
    mcCtrl.m_userBuffer = m_memCardBuffer;
    mcCtrl.m_createFlag = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::EndMemCardProc()
{
    m_memCardProc = 0;
    m_memCardResult = -1;
    MemoryCardMan.McEnd();
}
