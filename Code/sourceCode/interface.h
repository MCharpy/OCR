#ifndef INTERFACE_H
#define INTERFACE_H
    #include <stdlib.h>
    #include <gtk/gtk.h>
    #include "image.h"
    #include "BigMatrix.h"
    int interface_main(int argc, char **argv);
    struct Rundata
    {
        GtkTextBuffer *textBuffer;
        GtkFileChooserButton *loadButton;
        GtkLabel *label;
        GtkSpinButton *spinButton;
        GtkWindow *mainWindow;
    };
#endif
