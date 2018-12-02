#include "interface.h"



void lancer_OCR(GtkWidget *widget, gpointer data)
{
    //besoins: textbuffer, loadButton, label
    widget = widget;
    gchar *filename;
    gchar* text;
    struct Rundata *run = (struct Rundata *)data;
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(run->loadButton));
    if(filename != NULL)
    {
        gtk_label_set_text(run->label, "OCR");
        text = evalImage(filename);
        gtk_text_buffer_set_text(GTK_TEXT_BUFFER(run->textBuffer), text, -1);
        printf("%s\n", text);
        g_free(filename);
        g_free(text);
    }
    else
    {
        gtk_label_set_text(run->label, "aucun fichier n'a été choisi");
    }
    
}

void run_train(GtkWidget *widget, gpointer data)
{
    //besoins: loadButton, textBuffer, label
    widget = widget;
    gchar *filename;
    gchar *training_text;
    gint spin = 0;
    GtkTextIter start;
    GtkTextIter end;
    struct Rundata *run = (struct Rundata *)data;

    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(run->loadButton));
    gtk_text_buffer_get_bounds(run->textBuffer, &start, &end);
    training_text = gtk_text_buffer_get_text(run->textBuffer,&start,&end,FALSE);
    spin = gtk_spin_button_get_value_as_int(run->spinButton);
    if(filename != NULL)
    {
        gtk_label_set_text(run->label, "Entraînement");
        trainImage(filename, training_text, spin);
    }
    else
    {
        gtk_label_set_text(run->label, "aucun fichier n'a été choisi");
    }
    g_free(filename);
    g_free(training_text);

}

void reset_matrix(GtkWidget *widget, gpointer data)
{
    widget = widget;
    data = data;
    resetMatrix("./OCRmat/bias1.mat", 1);
    resetMatrix("./OCRmat/bias2.mat", 1);
    resetMatrix("./OCRmat/weights1.mat", 0);
    resetMatrix("./OCRmat/weights2.mat", 0);
}

void sauvegarde_fichier(GtkWidget *widget, gpointer data)
{
    //besoins: MainWindow, textBuffer
    widget = widget;
    GtkWidget *dialog;
    gint res;
    struct Rundata *run = (struct Rundata *)data;

    dialog = gtk_file_chooser_dialog_new ("Enregistrer Sous",
                                           run->mainWindow,
                                           GTK_FILE_CHOOSER_ACTION_SAVE,
                                           "_Annuler",
                                           GTK_RESPONSE_CANCEL,
                                           "_Enregistrer",
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
    gtk_widget_destroy(dialog);
}

void update_image(GtkWidget *widget, gpointer data)
{
    gchar *filename;
    filename =  gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget));
    gtk_image_set_from_file(GTK_IMAGE(data), filename);
    g_free(filename);
}

int interface_main(int argc, char **argv)
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
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 1000, 900);

    /* Création du notebook*/
    GtkWidget *notebook;

    notebook = gtk_notebook_new();
    /*Création des paned widgets*/
    GtkWidget *hpanedOCR;
    GtkWidget *hpanedTrain;
    GtkWidget *vpanedOCRl;
    GtkWidget *vpanedOCRr;
    GtkWidget *vpanedTrainl;
    
    hpanedOCR = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    hpanedTrain = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    vpanedOCRl = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    vpanedOCRr = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    vpanedTrainl = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    /*Création de l'apercu de l'image*/
    GtkWidget *image;
    GtkWidget *imageTrain;

    image = gtk_image_new();
    imageTrain = gtk_image_new();

    /*Création du label*/
    GtkWidget *label;
    GtkWidget *labelTrain;

    label = gtk_label_new("OCR"); //definition du label
    labelTrain = gtk_label_new("Entraînement");
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_label_set_justify(GTK_LABEL(labelTrain), GTK_JUSTIFY_CENTER);

    /* Création du bouton de choix de l'image */
    GtkWidget *loadButton;
    GtkWidget *loadButtonTrain;

    loadButton = gtk_file_chooser_button_new ("Choisissez un fichier",
                                          GTK_FILE_CHOOSER_ACTION_OPEN);
    loadButtonTrain = gtk_file_chooser_button_new ("Choisissez un fichier",
                                          GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(loadButton),
                                         ".");
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(loadButtonTrain),
                                         ".");
    g_signal_connect(G_OBJECT(loadButton), "file-set",
                    G_CALLBACK(update_image),
                    image);
    g_signal_connect(G_OBJECT(loadButtonTrain), "file-set",
                    G_CALLBACK(update_image),
                    imageTrain);

    /*Création du SpinButton*/
    GtkWidget *spinButton;
    spinButton = gtk_spin_button_new(gtk_adjustment_new(1,1,1000,1,10,0),1,0);

    /* Création d'un cadre de texte */
    GtkWidget *textView;
    GtkWidget *textViewTrain;
    GtkTextBuffer *textBuffer;
    GtkTextBuffer *textBufferTrain;

    textBufferTrain = gtk_text_buffer_new(gtk_text_tag_table_new());
    textView = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textView), GTK_WRAP_WORD_CHAR);
    textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    textViewTrain = gtk_text_view_new_with_buffer(textBufferTrain);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textViewTrain), GTK_WRAP_WORD_CHAR);

    
    /* Création du bouton qui lance l'OCR et du bouton de sauvegarde du texte */
    GtkWidget *runButton;
    GtkWidget *saveButton;
    GtkWidget *trainButton;
    GtkWidget *rMatButton;

    struct Rundata rundata;
    struct Rundata traindata;
    rundata.textBuffer = textBuffer;
    traindata.textBuffer = textBufferTrain;
    rundata.loadButton = GTK_FILE_CHOOSER_BUTTON(loadButton);
    traindata.loadButton = GTK_FILE_CHOOSER_BUTTON(loadButtonTrain);
    rundata.label = GTK_LABEL(label);
    traindata.label = GTK_LABEL(labelTrain);
    rundata.spinButton = GTK_SPIN_BUTTON(spinButton);
    traindata.spinButton = GTK_SPIN_BUTTON(spinButton);
    rundata.mainWindow = GTK_WINDOW(MainWindow);
    traindata.mainWindow = GTK_WINDOW(MainWindow);

    runButton = gtk_button_new_with_label("Commencer");
    g_signal_connect(G_OBJECT(runButton), "clicked",
                     G_CALLBACK(lancer_OCR), &rundata);
    
    saveButton = gtk_button_new_with_label("Enregistrer Sous...");
    g_signal_connect(G_OBJECT(saveButton), "clicked",
                     G_CALLBACK(sauvegarde_fichier), &rundata);
    

    trainButton = gtk_button_new_with_label("Entraînement");
    g_signal_connect(G_OBJECT(trainButton), "clicked",
                     G_CALLBACK(run_train), &traindata);
    

    rMatButton = gtk_button_new_with_label("Reinitialiser le Réseau Neuronal");
    g_signal_connect(G_OBJECT(rMatButton), "clicked",
                     G_CALLBACK(reset_matrix), NULL);

    /*Assemblage des composants*/
    GtkWidget *boxOCRl = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *boxTrainl = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

        gtk_container_add(GTK_CONTAINER(boxOCRl), loadButton);
        gtk_container_add(GTK_CONTAINER(boxOCRl), runButton);
        gtk_container_add(GTK_CONTAINER(boxOCRl), label);
       gtk_paned_pack1(GTK_PANED(vpanedOCRl), boxOCRl, TRUE, TRUE);
       gtk_paned_pack2(GTK_PANED(vpanedOCRl), image, FALSE, TRUE);
      gtk_paned_pack1(GTK_PANED(hpanedOCR), vpanedOCRl, FALSE, TRUE);
       gtk_paned_pack1(GTK_PANED(vpanedOCRr), textView, TRUE, FALSE);
       gtk_paned_pack2(GTK_PANED(vpanedOCRr), saveButton, FALSE, FALSE);
      gtk_paned_pack2(GTK_PANED(hpanedOCR), vpanedOCRr, FALSE, TRUE);
     gtk_notebook_append_page(GTK_NOTEBOOK(notebook), hpanedOCR, gtk_label_new("OCR"));
        gtk_container_add(GTK_CONTAINER(boxTrainl), loadButtonTrain);
        gtk_container_add(GTK_CONTAINER(boxTrainl), trainButton);
        gtk_container_add(GTK_CONTAINER(boxTrainl), spinButton);
        gtk_container_add(GTK_CONTAINER(boxTrainl), rMatButton);
        gtk_container_add(GTK_CONTAINER(boxTrainl), labelTrain);
       gtk_paned_pack1(GTK_PANED(vpanedTrainl), boxTrainl, FALSE, TRUE);
       gtk_paned_pack2(GTK_PANED(vpanedTrainl), textViewTrain, TRUE, FALSE);
      gtk_paned_pack1(GTK_PANED(hpanedTrain), vpanedTrainl, FALSE, TRUE);
      gtk_paned_pack2(GTK_PANED(hpanedTrain), imageTrain, TRUE, TRUE);
     gtk_notebook_append_page(GTK_NOTEBOOK(notebook), hpanedTrain, gtk_label_new("Train"));
    gtk_container_add(GTK_CONTAINER(MainWindow), notebook);

    /*Affichage et boucle évènementielle */
    gtk_widget_show_all(MainWindow); //afficher 'MainWindow' et ses enfants
    gtk_main(); //boucle évènementielle
    /* Fermeture de GTK+ */
    return EXIT_SUCCESS;
}
