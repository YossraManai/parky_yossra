#include <gtk/gtk.h>


void
on_ajouter_btn_agent_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_homme_radio_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_femme_radio_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_lavage_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gonflage_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_recharge_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_assistance_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_annuler_btn_agent_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_bouton_modifier_agent_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_bouton_annuler_modif_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_radio_homme_modif_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radio_femme_modif_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_lavage_modif_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_recharge_modif_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_gonflage_modif_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_assistance_modif_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_bouton_rechercher_agent_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_bouton_filtrer_agent_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_afficher_agents_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_affichage_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_Ajouter_agent_affichage_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_modifier_agent_affichage_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_supprimer_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

 


void
on_calendar1_day_selected              (GtkCalendar     *calendar,
                                        gpointer         user_data);

void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview_R_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_bouton_recherche_date_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_bouton_retour_R_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_bouton_acceuil_R_clicked            (GtkButton       *button,
                                        gpointer         user_data);
