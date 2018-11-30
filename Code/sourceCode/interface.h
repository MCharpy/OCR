#ifndef INTERFACE_H
#define INTERFACE_H
    #include <stdlib.h>
    #include <gtk/gtk.h>
    #include "image.h"
    int interface(int argc, char **argv);
    struct Rundata
    {
        GtkTextBuffer *textBuffer;
        GtkFileChooserButton *loadButton;
        GtkLabel *label;
        GtkWindow *mainWindow;
    };
#endif
