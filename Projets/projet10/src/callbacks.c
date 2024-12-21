#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "ajouter_agent.h"

int sexe_agent;
int services_agent[4]={0,0,0,0};
char *ID_AGENT;
void
on_ajouter_btn_agent_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ajouter_agent = lookup_widget(GTK_WIDGET(button), "ajouter_agent");
Agent agent;
int i;
GtkWidget *p_id, *p_nom, *p_prenom, *p_jour, *p_mois, *p_annee, *p_region, *p_telephone, *p_email, *p_msg_erreur;
int out;
    // Récupération des widgets
    p_id = lookup_widget(GTK_WIDGET(button), "id_entry");
    p_nom = lookup_widget(GTK_WIDGET(button), "nom_entry");
    p_prenom = lookup_widget(GTK_WIDGET(button), "prenom_entry");
    p_jour = lookup_widget(GTK_WIDGET(button), "spin_jour");
    p_mois = lookup_widget(GTK_WIDGET(button), "spin_mois");
    p_annee = lookup_widget(GTK_WIDGET(button), "spin_annee");
    p_region = lookup_widget(GTK_WIDGET(button), "combobox_region");
    p_email = lookup_widget(GTK_WIDGET(button), "email_entry");
    p_telephone = lookup_widget(GTK_WIDGET(button), "num_entry");
    p_msg_erreur = lookup_widget(GTK_WIDGET(button), "msg");

    // Récupération des données
    strcpy(agent.id, gtk_entry_get_text(GTK_ENTRY(p_id)));
    strcpy(agent.nom, gtk_entry_get_text(GTK_ENTRY(p_nom)));
    strcpy(agent.prenom, gtk_entry_get_text(GTK_ENTRY(p_prenom)));
    agent.date_naissance.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(p_jour));
    agent.date_naissance.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(p_mois));
    agent.date_naissance.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(p_annee));
    agent.sexe=sexe_agent;
    strcpy(agent.region, gtk_combo_box_get_active_text(GTK_COMBO_BOX(p_region)));
    strcpy(agent.email, gtk_entry_get_text(GTK_ENTRY(p_email)));
    strcpy(agent.telephone, gtk_entry_get_text(GTK_ENTRY(p_telephone)));
    for (i=0;i<4;i++) {
     agent.services_agent[i]=services_agent[i];
    }
    out=ajouter("agent.txt",agent); 
    if (out) { 
    gtk_label_set_text(GTK_LABEL(p_msg_erreur), "Ajout avec succès");
    }
     else { 
    gtk_label_set_text(GTK_LABEL(p_msg_erreur), "Agent non ajouté");
}

    if (ajouter_agent) {
        gtk_widget_hide(ajouter_agent);
    }
}

void
on_homme_radio_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
   sexe_agent=1; }
}


void
on_femme_radio_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
   sexe_agent=0; }
}


void
on_lavage_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
   services_agent[0]=1; }
}


void
on_gonflage_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
   services_agent[1]=1; }
}


void
on_recharge_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
   services_agent[2]=1; }
}


void
on_assistance_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
   services_agent[3]=1; }
}


void
on_annuler_btn_agent_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *ajouter_agent = lookup_widget(GTK_WIDGET(button), "ajouter_agent");
  gtk_widget_hide(ajouter_agent);
  GtkWidget *affichage_agent = create_affichage_agent();
  gtk_widget_show (affichage_agent);
}


void
on_bouton_modifier_agent_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
const char *file = "agent.txt"; // Fichier source
    FILE *f = fopen(file, "r");
    FILE *fnew = fopen("temp.txt", "w"); // Fichier temporaire pour écriture
    Agent a;
    gboolean modification_reussie = FALSE;

    // Récupération de la fenêtre "modifier_agent"
    GtkWidget *modifier_agent = lookup_widget(GTK_WIDGET(button), "modifier_agent");
const char *id_modifie = g_object_get_data(G_OBJECT(modifier_agent), "id_agent");

    // Récupérer les nouvelles valeurs des champs
    const char *nom = gtk_entry_get_text(GTK_ENTRY(lookup_widget(modifier_agent, "nom_entry_modif")));
    const char *prenom = gtk_entry_get_text(GTK_ENTRY(lookup_widget(modifier_agent, "prenom_entry_modif")));
    int jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(modifier_agent, "spin_jour_modif")));
    int mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(modifier_agent, "spin_mois_modif")));
    int annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(modifier_agent, "spin_annee_modif")));

    const char *region = gtk_combo_box_get_active_text(GTK_COMBO_BOX(lookup_widget(modifier_agent, "combobox_region_modif")));

    const char *telephone = gtk_entry_get_text(GTK_ENTRY(lookup_widget(modifier_agent, "num_entry_modif")));
    const char *email = gtk_entry_get_text(GTK_ENTRY(lookup_widget(modifier_agent, "email_entry_modif")));
// Récupérer le sexe via les boutons radio
GtkToggleButton *radio_homme = GTK_TOGGLE_BUTTON(lookup_widget(modifier_agent, "radio_homme_modif"));
GtkToggleButton *radio_femme = GTK_TOGGLE_BUTTON(lookup_widget(modifier_agent, "radio_femme_modif"));
int sexe = gtk_toggle_button_get_active(radio_homme) ? 0 : 1; // 0 pour Homme, 1 pour Femme
// Mettre à jour les services associés
    int services[4] = {0, 0, 0, 0};
    services[0] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lookup_widget(modifier_agent, "lavage_modif")));
    services[1] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lookup_widget(modifier_agent, "gonflage_modif")));
    services[2] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lookup_widget(modifier_agent, "recharge_modif")));
    services[3] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lookup_widget(modifier_agent, "assistance_modif")));
    GtkWidget *msg_modif = lookup_widget(modifier_agent, "msg_modif");
    // Mettre à jour le fichier
    if (f != NULL && fnew != NULL) {
        while (fscanf(f, "%s %s %s %d %d %d %d %s %s %s %d %d %d %d\n", 
           a.id, a.nom, a.prenom, &a.date_naissance.jour, &a.date_naissance.mois,    &a.date_naissance.annee, &a.sexe, a.region, a.telephone, a.email, &a.services_agent[0], &a.services_agent[1], &a.services_agent[2], &a.services_agent[3]) != EOF) {
            if (strcmp(a.id, id_modifie) == 0) {
                // Écrire les nouvelles valeurs (ID reste inchangé)
                fprintf(fnew, "%s %s %s %d %d %d %d %s %s %s %d %d %d %d\n", 
                        a.id, nom, prenom, jour, mois, annee, sexe, region, telephone, email, services[0], services[1], services[2], services[3]);
                modification_reussie = TRUE;
            } else {
                // Conserver les anciennes valeurs
                fprintf(fnew, "%s %s %s %d %d %d %d %s %s %s %d %d %d %d\n", 
                        a.id, a.nom, a.prenom, 
                        a.date_naissance.jour, a.date_naissance.mois, a.date_naissance.annee, a.sexe, a.region, a.telephone, a.email, a.services_agent[0], a.services_agent[1], a.services_agent[2], a.services_agent[3]);
            }
        }
        fclose(f);
        fclose(fnew);

        // Remplacer l'ancien fichier par le nouveau
        remove(file);
        rename("temp.txt", file);
    }
if (modification_reussie) {
        gtk_label_set_text(GTK_LABEL(msg_modif), "Agent modifié avec succès.");
            gtk_widget_hide(modifier_agent);
            
} else {
        gtk_label_set_text(GTK_LABEL(msg_modif), "Erreur de modification.");
}
}

void
on_bouton_annuler_modif_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *modifier_agent = lookup_widget(GTK_WIDGET(button), "modifier_agent");
  gtk_widget_hide(modifier_agent);
  GtkWidget *affichage_agent = create_affichage_agent();
  gtk_widget_show (affichage_agent);
}


void
on_radio_homme_modif_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        sexe_agent = 1;
    }
}


void
on_radio_femme_modif_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        sexe_agent = 0;
    }
}


void
on_lavage_modif_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
   if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        services_agent[0] = 1;
    } 
}


void
on_recharge_modif_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        services_agent[2] = 1;
    } 
}


void
on_gonflage_modif_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        services_agent[1] = 1;
    }
}


void
on_assistance_modif_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        services_agent[3] = 1;
    } 
}


void
on_bouton_rechercher_agent_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
       GtkWidget *recherche_id_entry; // Champ de saisie pour l'ID
    GtkWidget *treeview;           // TreeView pour afficher les résultats
    GtkWidget *dialog;             // Boîte de dialogue pour messages d'erreur
    const char *id_recherche;      // ID saisi par l'utilisateur
    Agent agent;                   // Structure pour l'agent trouvé

    // Récupérer les widgets nécessaires
    recherche_id_entry = lookup_widget(GTK_WIDGET(button), "recherche_id_entry");
    treeview = lookup_widget(GTK_WIDGET(button), "treeview_affichage");

    // Vérification des widgets
    if (recherche_id_entry == NULL || treeview == NULL) {
        printf("Erreur : Widgets introuvables.\n");
        return;
    }

    // Récupérer le texte saisi dans le champ de recherche
    id_recherche = gtk_entry_get_text(GTK_ENTRY(recherche_id_entry));

    // Vérifier si la case est vide
    if (id_recherche == NULL || strlen(id_recherche) == 0) {
        dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "Veuillez saisir un ID d'agent.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Rechercher l'agent dans le fichier
    agent = rechercher_agent("agent.txt", id_recherche);

    // Vérifier si l'agent a été trouvé
    if (strlen(agent.id) == 0) {
        dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "L'ID de l'agent est incorrect ou introuvable.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Créer un nouveau modèle de données pour le TreeView
    GtkListStore *store = gtk_list_store_new(5,
        G_TYPE_STRING, // ID
        G_TYPE_STRING, // Nom
        G_TYPE_STRING, // Prénom
        G_TYPE_STRING, // Région
        G_TYPE_STRING  // Téléphone
    );

    // Ajouter les informations de l'agent au modèle
    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       0, agent.id,
                       1, agent.nom,
                       2, agent.prenom,
                       3, agent.region,
                       4, agent.telephone,
                       -1);

    // Vider le TreeView et ajouter le nouveau modèle
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store); // Libérer le modèle après l'attachement
}

void
on_bouton_filtrer_agent_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview;
    GtkWidget *combo_box_region;

    // Récupération du ComboBoxText pour la région
    combo_box_region = lookup_widget(GTK_WIDGET(button), "combobox_filtre");

    if (combo_box_region == NULL) {
        printf("Erreur : Widget 'combobox_filtre' introuvable.\n");
        return;
    }

    // Vérifiez si le widget est un GtkComboBoxText
    if (!GTK_IS_COMBO_BOX(combo_box_region)) {
        printf("Erreur : 'combobox_filtre' n'est pas un GtkComboBoxText.\n");
        return;
    }

    // Vérification de la région sélectionnée
    const char *region_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_box_region));

    // Récupération du TreeView pour afficher les agents
    treeview = lookup_widget(GTK_WIDGET(button), "treeview_affichage");

    if (region_text != NULL) {
        // Obtenir l'indice de la région
        int index_region = obtenir_index_region((char *)region_text);

        if (index_region != -1) {
            // La région existe, filtrer les agents
            afficher_agents_par_region(treeview, region_text);
        } else {
            // Si la région n'est pas valide, afficher tous les agents
            printf("Région invalide. Affichage de tous les agents.\n");
            afficher_agents(treeview);
        }
    } else {
        // Si aucune région n'est sélectionnée, afficher tous les agents
        printf("Aucune région sélectionnée. Affichage de tous les agents.\n");
        afficher_agents(treeview);
    }
}

void
on_afficher_agents_clicked             (GtkButton       *button,
                                        gpointer         user_data){
    GtkWidget *treeview;

    // Récupération du widget TreeView
    treeview = lookup_widget(GTK_WIDGET(button), "treeview_affichage");

    // Appel à la fonction d'affichage
    afficher_agents(treeview);
}


void
on_treeview_affichage_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_Ajouter_agent_affichage_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *affichage_agent = lookup_widget(GTK_WIDGET(button), "affichage_agent");
  gtk_widget_hide(affichage_agent);
  GtkWidget *ajouter_agent = create_ajouter_agent();
  gtk_widget_show (ajouter_agent);
}


void
on_modifier_agent_affichage_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{

 // Récupérer la fenêtre d'affichage des agents
    GtkWidget *affichage_agent = lookup_widget(GTK_WIDGET(button), "affichage_agent");

    // Récupérer le TreeView et la sélection
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(affichage_agent, "treeview_affichage"));
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;

    // Vérifier si une ligne est sélectionnée
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *id_agent;
        gtk_tree_model_get(model, &iter, 0, &id_agent, -1); // 0 correspond à la colonne de l'ID
        ID_AGENT=id_agent;
GtkWidget *modifier_agent = create_modifier_agent();
        Agent agent = rechercher_agent("agent.txt", id_agent);

        if (strcmp(agent.id, "") != 0) {
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(modifier_agent, "nom_entry_modif")), agent.nom);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(modifier_agent, "prenom_entry_modif")), agent.prenom);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(modifier_agent, "spin_jour_modif")), agent.date_naissance.jour);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(modifier_agent, "spin_mois_modif")), agent.date_naissance.mois);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(modifier_agent, "spin_annee_modif")), agent.date_naissance.annee);

            if (agent.sexe == 1) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lookup_widget(modifier_agent, "radio_homme_modif")), TRUE);
            } else {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lookup_widget(modifier_agent, "radio_femme_modif")), TRUE);
            }

            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(modifier_agent, "combobox_region_modif")), obtenir_index_region(agent.region));
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(modifier_agent, "num_entry_modif")), agent.telephone);
            gtk_entry_set_text(GTK_ENTRY(lookup_widget(modifier_agent, "email_entry_modif")), agent.email);

            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lookup_widget(modifier_agent, "lavage_modif")), agent.services_agent[0]);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lookup_widget(modifier_agent, "gonflage_modif")), agent.services_agent[1]);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lookup_widget(modifier_agent, "recharge_modif")), agent.services_agent[2]);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lookup_widget(modifier_agent, "assistance_modif")), agent.services_agent[3]);

            g_object_set_data(G_OBJECT(modifier_agent), "id_agent", id_agent);
            gtk_widget_show(modifier_agent);
        } else {
            g_warning("Agent non trouvé pour l'ID : %s", id_agent);
        }
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(affichage_agent),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez sélectionner un agent avant de cliquer sur Modifier."
        );
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

}

void
on_supprimer_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *affichage_agent = lookup_widget(GTK_WIDGET(button), "affichage_agent");

    // Récupérer le TreeView et la sélection
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(affichage_agent, "treeview_affichage"));
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;

    // Vérifier si une ligne est sélectionnée
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *id_agent;
        gtk_tree_model_get(model, &iter, 0, &id_agent, -1); // 0 correspond à la colonne de l'ID

        // Appeler la fonction supprimerAgent
        int resultat = supprimerAgent("agent.txt", id_agent);

        // Vérifier le résultat de la suppression
        if (resultat) {
            // Supprimer la ligne du TreeView
            gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
        } else {
            // Afficher une erreur en cas de problème avec la suppression
            GtkWidget *dialog = gtk_message_dialog_new(
                GTK_WINDOW(affichage_agent),
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_ERROR,
                GTK_BUTTONS_OK,
                "Erreur lors de la suppression de l'agent.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }

        // Libérer la mémoire allouée pour l'ID récupéré
        g_free(id_agent);
    } else {
        // Aucun agent n'est sélectionné
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(affichage_agent),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez sélectionner un agent à supprimer.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}




void
on_treeview_R_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_bouton_recherche_date_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *spin_jour_R = lookup_widget((GtkWidget*)button, "spin_jour_R");
    GtkWidget *spin_mois_R = lookup_widget((GtkWidget*)button, "spin_mois_R");
    GtkWidget *spin_annee_R = lookup_widget((GtkWidget*)button, "spin_annee_R");

    // Récupération de la date sélectionnée
    int jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour_R));
    int mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois_R));
    int annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee_R));

    // Créer une structure Date pour la date sélectionnée
    Date dateRecherche = { jour, mois, annee };

    // Filtrer les réservations par la date
    Liste reservationsFiltrees = filtreReservationParDate("reservation.txt", dateRecherche);

    // Charger la liste filtrée dans le TreeView
    GtkWidget *treeview_R = lookup_widget((GtkWidget*)button, "treeview_R");
    chargerListeFiltreeDansTreeView(treeview_R, reservationsFiltrees);
}


void
on_bouton_retour_R_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_bouton_acceuil_R_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}

