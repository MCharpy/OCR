#ifndef INTERFACE_H
#define INTERFACE_H
    #include <stdlib.h>
    #include <gtk/gtk.h>
    void fin(GtkWidget *widget, gpointer data);
    void lancer_OCR(GtkWidget *widget, gpointer data);
    void sauvegarde_fichier(GtkWidget *widget, gpointer data);
    int interface(int argc, char **argv);
#endif
