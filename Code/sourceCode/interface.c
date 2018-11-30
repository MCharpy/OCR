#include "interface.h"
#include "image.h"

void lancer_OCR(GtkWidget *widget, gpointer data)
{
    /* Création du dialogue de choix de fichier */
    gchar *filename;
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(data));
    if(filename != NULL)
    {
        process_image(filename);
        //recuperer le texte
    }
    else
    {
        printf("Aucun fichier n'a été selectionné\n");
    }
    g_free(filename);
}

void sauvegarde_fichier(GtkWidget *widget, gpointer data)
{
    gchar *text_to_save;
    gchar *filename;
    FILE *fp;
    GtkTextIter start;
    GtkTextIter end;
    GtkWidget *dialog;
    gint res;
    
    dialog = gtk_file_chooser_dialog_new ("Enregistrer Sous",
                                           data.window,
                                           GTK_FILE_CHOOSER_ACTION_SAVE,
                                           "_Cancel",
                                           GTK_RESPONSE_CANCEL,
                                           "_Open",
                                           GTK_RESPONSE_ACCEPT,
                                           NULL);

    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog),
                                                    TRUE);
    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(dialog));
    }
    
    gtk_text_buffer_get_bounds(data, &start, &end);
    //filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget));
    text_to_save = gtk_text_buffer_get_text(data, &start, &end, FALSE);
    fp = fopen(filename, "w");
    fprintf(fp, "%s", text_to_save)//sauvegarde du texte dans un fichier
    g_free(filename);
    g_free(text_to_save);
}

int interface(int argc, char **argv)
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
                     G_CALLBACK(gtk_main_quit()), NULL);
                                             //on prévoit de recevoir le signal 
                                             //de fermeture de la fenêtre
                                             //ce qui appellera la fct "fin"
    gtk_window_set_title(GTK_WINDOW(MainWindow), "A.S.M.R.: O.C.R"); //titre de                                                                      //la fenêtre
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 1000, 1000); //taille de
                                                                   //la fenêtre
    
    /*Création des onglets (GTKNotebook)*/
    GtkWidget *notebook
    notebook = gtk_notebook_new();
    

    /* Création de la box */
    GtkWidget *box;
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); //création boite,
                                                      //orientation horizontale
                                                      //espacement 0 pixels
    gtk_container_add(GTK_CONTAINER(MainWindow), box); //ajouter box a la fenêtre

    /*Création du paned widget*/
    GtkWidget *hpaned;
    GtkWidget *frame1;
    GtkWidget *frame2;
    GtkWidget *frameL;
    GtkWidget *frameR;
    
    hpaned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    frameL = gtk_frame_new(NULL);
    frameR = gtk_frame_new(NULL);
    frame1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); 
    frame2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); 
    gtk_frame_set_shadow_type(GTK_FRAME (frameL), GTK_SHADOW_IN);
    gtk_frame_set_shadow_type(GTK_FRAME (frameR), GTK_SHADOW_IN);

    gtk_paned_pack1(GTK_PANED(hpaned), frameL, TRUE, FALSE);
    gtk_paned_pack2(GTK_PANED (hpaned), frameR, FALSE, FALSE);
    gtk_widget_set_size_request (frameL, 50, -1);
    gtk_widget_set_size_request (frameR, 200, 200);

    gtk_container_add(GTK_CONTAINER(frameL), frame1);
    gtk_container_add(GTK_CONTAINER(frameR), frame2);
    gtk_container_add(GTK_CONTAINER(box), hpaned);

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
    gtk_widget_set_size_request (label, -1, 180);

    gtk_container_add(GTK_CONTAINER(box), label); //ajouter le label à box

    /* Création du bouton de choix de l'image */
    GtkWidget *button;

    button = gtk_file_chooser_button_new ("Choisissez un fichier",
                                          GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (button),
                                         ".");

    gtk_container_add(GTK_CONTAINER(frame1), button); //on ajoute le bouton à
                                                      //frame1
    /* Création d'un cadre de texte */
    GtkWidget *textView;
    GtkTextBuffer *textBuffer;

    textBuffer = gtk_text_buffer_new(gtk_text_tag_table_new());
    textView = gtk_text_view_new_with_buffer(textBuffer);
    gtk_widget_set_size_request (textView, 200, 180);
    gtk_container_add(GTK_CONTAINER(frame2), textView); 

    /* Création du bouton qui lance l'OCR et du bouton de sauvegarde du texte */
    GtkWidget *runButton;
    GtkWidget *saveButton;

    runButton = gtk_button_new_with_label("Commencer");
    g_signal_connect(G_OBJECT(runButton), "clicked",
                     G_CALLBACK(lancer_OCR), button);
    saveButton = gtk_button_new_with_label("Enregistrer sous...");

   
    g_signal_connect(G_OBJECT(saveButton), "clicked",
                     G_CALLBACK(sauvegarde_fichier), textBuffer); //recevoir le 
                                                                //signal clicked
    gtk_container_add(GTK_CONTAINER(frame1), runButton);
    gtk_container_add(GTK_CONTAINER(frame2), saveButton); 
    
    /*Affichage et boucle évènementielle */
    gtk_widget_show_all(MainWindow); //afficher 'MainWindow' et ses enfants
    gtk_main(); //boucle évènementielle

    /* Fermeture de GTK+ */
    return EXIT_SUCCESS;
}
