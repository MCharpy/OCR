#include <stdlib.h>
#include <gtk/gtk.h>

void mafonction(GtkWidget *widget, gpointer data)
{
    printf("Merci d'avoir choisi ASMR\n");
    gtk_main_quit();
}

int main(int argc, char **argv)
{
    /* Variables */
    GtkWidget* MainWindow;
    GtkWidget* label;
    gchar* TexteLabel;

    /* Initialisation de GTK+ */
    gtk_init(&argc, &argv);

    /* Création de la fenêtre*/
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL); //definition de la fenêtre
    g_signal_connect(G_OBJECT(MainWindow), "delete-event",
                     G_CALLBACK(mafonction), NULL);
   
    /* Personnalisation de la fenêtre */
    gtk_window_set_title(GTK_WINDOW(MainWindow), "A.S.M.R.: O.C.R"); //titre de 
                                                                     //la fenêtre
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 500, 500); //taille de
                                                                   //la fenêtre

    /*Création du label*/
    TexteLabel = g_locale_to_utf8("Voici notre OCR", -1, NULL, NULL, NULL); 
                                                             //générer un texte
                                                             //qui sera rendu par
                                                             //pango
    label = gtk_label_new(TexteLabel); //definition du label avec le texte généré
    g_free(TexteLabel); //libération de la mémoire
    gtk_label_set_use_markup(GTK_LABEL(label), TRUE); //on dit qu'on utilise les
                                                      //balises pango 
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);//centrer le texte
    gtk_container_add(GTK_CONTAINER(MainWindow), label); //ajouter le label à la 
                                                         //fenêtre

    
    /*Affichage et "boucle évènementielle" */
    gtk_widget_show_all(MainWindow); //afficher 'MainWindow' et ses enfants
    gtk_main();

    /* Fermeture de GTK+ */
    return EXIT_SUCCESS;
}
