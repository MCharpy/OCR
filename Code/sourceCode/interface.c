#include "interface.h"



void lancer_OCR(GtkWidget *widget, gpointer data)
{
    //besoins: textbuffer, loadButton, label
    gchar *filename;
    gchar* text;
    struct Rundata *run = (struct Rundata *)data;
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(run->loadButton));
    if(filename != NULL)
    {
        /*text = lancer l'ocr(filename)*/
        /***run->textBuffer.set_text(text)*/
    }
    else
    {
        gtk_label_set_text(run->label, "aucun fichier n'a été choisi");
    }
    g_free(filename);
    g_free(text);
}

void train(GtkWidget *widget, gpointer data)
{
    //besoins: loadButton, textBuffer, label
    gchar *filename;
    gchar *training_text;
    GtkTextIter start;
    GtkTextIter end;
    struct Rundata *run = (struct Rundata *)data;

    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(run->loadButton));
    gtk_text_buffer_get_bounds(run->textBuffer, &start, &end);
    training_text = gtk_text_buffer_get_text(run->textBuffer, &start, &end, FALSE);
    if(filename != NULL)
    {
        /*train(filename, training_text)*/
    }
    else
    {
        gtk_label_set_text(run->label, "aucun fichier n'a été choisi");
    }
    g_free(filename);
    g_free(training_text);

}

void reset_matrix(GtkWidget *Widget, gpointer data)
{
    //resetMatrices();
}

void sauvegarde_fichier(GtkWidget *widget, gpointer data)
{
    //besoins: MainWindow, textBuffer
    GtkWidget *dialog;
    gint res;
    struct Rundata *run = (struct Rundata *)data;

    dialog = gtk_file_chooser_dialog_new ("Enregistrer Sous",
                                           run->mainWindow,
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
        gchar *filename;
        gchar *text_to_save;
        FILE *fp;
        GtkTextIter start;
        GtkTextIter end;

        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(dialog));
        fp = fopen(filename,"w");
        gtk_text_buffer_get_bounds(run->textBuffer, &start, &end);
        text_to_save = gtk_text_buffer_get_text(run->textBuffer, &start, &end, FALSE);
        fprintf(fp,"%s\n",text_to_save);
        fclose(fp);
        g_free (filename);
        g_free (text_to_save);
    }
}

void update_image(GtkWidget *widget, gpointer data)
{
    gchar *filename;
    filename =  gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget));
    gtk_image_set_from_file(GTK_IMAGE(data), filename);
    g_free(filename);
}

int main(int argc, char **argv)
{
    /* Initialisation de GTK+ */
    gtk_init(&argc, &argv);

    /* Création de la fenêtre*/
    GtkWidget* MainWindow;

    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(MainWindow), "delete-event",
                     G_CALLBACK(gtk_main_quit), NULL); 
    //on prévoit de recevoir le signal de fermeture de la fenêtre
   //ce qui appellera la fct "gtk_main_quit"
    gtk_window_set_title(GTK_WINDOW(MainWindow), "A.S.M.R.: O.C.R");
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 500, 500);

    /* Création du notebook*/
    GtkWidget *notebook;

    /*Création des paned widgets*/
    GtkWidget *hpanedOCR;
    GtkWidget *hpanedTrain;
    GtkWidget *vpanedOCRl;
    GtkWidget *vpanedOCRr;
    GtkWidget *vpanedTrain;

    hpanedOCR = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    hpanedTrain = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    vpanedOCRl = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    vpanedOCRr = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    vpanedTrain = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    gtk_paned_pack1(GTK_PANED(hpanedOCR), vpanedOCRl, TRUE, FALSE);
    gtk_paned_pack2(GTK_PANED(hpanedOCR), vpanedOCRr, FALSE, FALSE);
    gtk_paned_pack1(GTK_PANED(hpanedTrain), vpanedTrain, TRUE, FALSE);

    /*Création de l'apercu de l'image*/
    GtkWidget *image;

    image = gtk_image_new();

    /*Création du label*/
    GtkWidget* label;

    label = gtk_label_new("Voici notre OCR"); //definition du label
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);

    /* Création du bouton de choix de l'image */
    GtkWidget *loadButton;

    loadButton = gtk_file_chooser_button_new ("Choisissez un fichier",
                                          GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(loadButton),
                                         ".");
    g_signal_connect(G_OBJECT(loadButton), "file-set",
                    G_CALLBACK(update_image),
                    &image);

    /* Création d'un cadre de texte */
    GtkWidget *textView;
    GtkTextBuffer *textBuffer;

    textBuffer = gtk_text_buffer_new(gtk_text_tag_table_new());
    textView = gtk_text_view_new_with_buffer(textBuffer);

    /* Création du bouton qui lance l'OCR et du bouton de sauvegarde du texte */
    GtkWidget *runButton;
    GtkWidget *saveButton;
    GtkWidget *trainButton;
    GtkWidget *rMatButton;

    struct Rundata rundata;
    rundata.textBuffer = textBuffer;
    rundata.loadButton = loadButton;
    rundata.label = label;
    rundata.mainWindow = MainWindow;

    runButton = gtk_button_new_with_label("Commencer");
    g_signal_connect(G_OBJECT(runButton), "clicked",
                     G_CALLBACK(lancer_OCR), &rundata);
    
    trainButton = gtk_button_new_with_label("Entraînement");
    g_signal_connect(G_OBJECT(trainButton), "clicked",
                     G_CALLBACK(train), &rundata);
    

    rMatButton = gtk_button_new_with_label("Reinitialiser le Réseau Neuronal");
    g_signal_connect(G_OBJECT(rMatButton), "clicked",
                     G_CALLBACK(reset_matrix), NULL);
    


    saveButton = gtk_button_new_with_label("Enregistrer Sous...");
    g_signal_connect(G_OBJECT(saveButton), "clicked",
                     G_CALLBACK(sauvegarde_fichier), &rundata);
    
    /*Affichage et boucle évènementielle */
    gtk_widget_show_all(MainWindow); //afficher 'MainWindow' et ses enfants
    gtk_main(); //boucle évènementielle

    /* Fermeture de GTK+ */
    return EXIT_SUCCESS;
}
