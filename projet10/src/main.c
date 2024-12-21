/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"

int
main (int argc, char *argv[])
{

 GtkWidget *ajouter_agent;
 GtkWidget *modifier_agent;
 GtkWidget *affichage_agent; 
 GtkWidget *liste_reservations_agent;

#ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif
 // Paramétrer la locale en français avec UTF-8


  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */



  affichage_agent = create_affichage_agent ();
  gtk_widget_show (affichage_agent);
  liste_reservations_agent = create_liste_reservations_agent();
  gtk_widget_show (liste_reservations_agent);


  gtk_main ();
  return 0;
}

