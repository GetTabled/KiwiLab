#include <gtk/gtk.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

/*
static void handleFileDialog(GtkDialog *dialog, int response) {
  if(response == GTK_RESPONSE_ACCEPT) {
      GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
      g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
      g_print(file);
    }
  gtk_window_destroy(GTK_WINDOW(dialog));
}

static void importFile(GtkWidget *button, gpointer user_data) {
  struct kwlb_Widgets *widgets = (struct kwlb_Widgets*) user_data; 

  gtk_button_set_label(widgets->importButton, "CLICKED"); 

  //gtk_window_present(GTK_WINDOW(dialog));
  g_print("Importing file");
}
*/

struct kwlb_Widgets {
  GtkWidget *window; // Gtk.Window
  GtkWidget *windowDivideContainer; // Gtk.Paned

  GtkWidget *topWindowDivider; // Gtk.Paned

  GtkWidget *tabbedPanelGrandParentContainer; // Gtk.Frame
  GtkWidget *tabbedPanelParentContainer; // Gtk.Box
  GtkWidget *tabbedPanelParent; // Gtk.Stack
  GtkWidget *tabbedPanelSwitcher; // Gtk.StackSwitcher

  GtkWidget *projectPanel; // Gtk.Frame
  GtkWidget *importButton; // Gtk.Button
  GtkWidget *fileDialog; // Gtk.FileChooserDialog

  GtkWidget *propertiesPanel; // Gtk.Frame

  GtkWidget *compositionPanel; // Gtk.Frame
  GtkWidget *frameDisplay; // Gtk.MediaFile

  GtkWidget *timelinePanel; // Gtk.Frame
};

static void activate(GtkApplication *app, gpointer user_data) {
  // Point to widgets
  struct kwlb_Widgets *widgets = (struct kwlb_Widgets*) user_data; 

  // Create a new window
  widgets->window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(widgets->window), "KiwiLab");
  gtk_window_set_default_size(GTK_WINDOW(widgets->window), 800, 800);

  // Put the windowDivideContainer in the window
  //gtk_window_set_child(GTK_WINDOW(widgets->window), widgets->windowDivideContainer);

  // Show the window
  gtk_widget_show(widgets->window);
}

static int get_video(const char *filePath) {
  AVFormatContext *formatContext = avformat_alloc_context();

  if(!formatContext) {
      return -1;
  }

  if(avformat_open_input(&formatContext, filePath, NULL, NULL)) {
    return -1;
  }

  if(avformat_find_stream_info(formatContext, NULL) < 0) {
    return -1;
  }

  AVCodec *codec = NULL;
  AVCodecParameters *codecParameters =  NULL;
}

int main(int argc, char **argv) {
  GtkApplication *app;
  struct kwlb_Widgets widgets;
  int status;

  // GTK application initialization
  app = gtk_application_new("table.kiwilab", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), &widgets);
  // GTK application initialization::END

  // Initialize widgets
  widgets = (struct kwlb_Widgets) { 
    .windowDivideContainer = gtk_paned_new(GTK_ORIENTATION_VERTICAL),
    .topWindowDivider = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL),
    .tabbedPanelGrandParentContainer =  gtk_frame_new(NULL),
    .tabbedPanelParentContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5),
    .tabbedPanelParent = gtk_stack_new(),
    .tabbedPanelSwitcher = gtk_stack_switcher_new(),
    .projectPanel = gtk_frame_new("projectPanel"),
    .importButton = gtk_button_new_with_label("Import"),
    .propertiesPanel = gtk_frame_new("propertiesPanel"),
    .compositionPanel = gtk_frame_new("compositionPanel"),
    .frameDisplay = gtk_media_file_new(),
    .timelinePanel = gtk_frame_new("timelinePanel")
  };

  // Top left area
  // [x] [ ]
  // [     ]
  gtk_frame_set_child(GTK_FRAME(widgets.tabbedPanelGrandParentContainer), widgets.tabbedPanelParentContainer);
  

  // Handle importButton press
  //g_signal_connect(GTK_BUTTON(importButton), "clicked", G_CALLBACK(importFile), &widgets);
  // Create new Gtk.FileChooserDialog
  //widgets->fileDialog =  gtk_file_chooser_dialog_new("Choose file", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
  //("Cancel"), GTK_RESPONSE_CANCEL, ("Open"), GTK_RESPONSE_ACCEPT);
  // Show the fileDialog
  //gtk_window_present(GTK_WINDOW(widgets->fileDialog));
  // Handle fileDialog response
  //g_signal_connect(widgets->fileDialog, "response", G_CALLBACK(handleFileDialog), NULL);
  // Place the importButton inside the projectPanel
  gtk_frame_set_child(GTK_FRAME(widgets.projectPanel), widgets.importButton);



  // Add childs to the Stack(tabbedPanelParent)
  gtk_stack_add_titled(GTK_STACK(widgets.tabbedPanelParent), widgets.projectPanel, "projectPanel", "Project");
  gtk_stack_add_titled(GTK_STACK(widgets.tabbedPanelParent), widgets.propertiesPanel, "propertiesPanel", "Properties");

  // Set the Stack to use for the StackSwitcher
  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(widgets.tabbedPanelSwitcher), GTK_STACK(widgets.tabbedPanelParent));
  
  // Place the tabbedPanelParent(Stack) to the tabbedPanelParentContainer(Box)
  gtk_box_append(GTK_BOX(widgets.tabbedPanelParentContainer), widgets.tabbedPanelSwitcher);
  gtk_box_append(GTK_BOX(widgets.tabbedPanelParentContainer), widgets.tabbedPanelParent);
  // Place the tabbedPanelParentContainer(Frame) in the topWindowDivider(Pane)
  gtk_paned_set_start_child(GTK_PANED(widgets.topWindowDivider), widgets.tabbedPanelGrandParentContainer);
  // Top left area::END


  // Top right area
  // [ ] [x]
  // [     ]

  // Place the compositionPanel(Frame) in the topWindowDivider(Pane)
  gtk_paned_set_end_child(GTK_PANED(widgets.topWindowDivider), widgets.compositionPanel);
  // Top right area::END


  // Buttom area
  // [ ] [ ]
  // [ x x ]

  // Bottom area::END


  // Set windowDivideContainer children
  gtk_paned_set_start_child(GTK_PANED(widgets.windowDivideContainer), widgets.topWindowDivider);
  gtk_paned_set_end_child(GTK_PANED(widgets.windowDivideContainer), widgets.timelinePanel);
  // Initialize widgets::END


  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}