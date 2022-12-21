#include <gtk/gtk.h>

static void activate(GtkApplication* app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *windowDivideContainer;

  GtkWidget *topWindowContainer;
  GtkWidget *tabbedPanelGrandParentContainer;
  GtkWidget *tabbedPanelParentContainer;
  GtkWidget *tabbedPanelParent;
  GtkWidget *tabbedPanelSwitcher;
  GtkWidget *projectPanel;
  GtkWidget *propertiesPanel;

  GtkWidget *compositionPanel;

  GtkWidget *timelinePanel;


  // Create a new window
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "KiwiLab");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);

  windowDivideContainer = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  
  // [x] [ ]
  // [     ]
  topWindowContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
  tabbedPanelGrandParentContainer =  gtk_frame_new(NULL);
  tabbedPanelParentContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_frame_set_child(GTK_FRAME(tabbedPanelGrandParentContainer), tabbedPanelParentContainer);
  
  tabbedPanelParent = gtk_stack_new();
  tabbedPanelSwitcher = gtk_stack_switcher_new();

  projectPanel = gtk_frame_new("projectPanel");
  propertiesPanel = gtk_frame_new("propertiesPanel");

  // Add childs to the Stack(tabbedPanelParent)
  gtk_stack_add_titled(GTK_STACK(tabbedPanelParent), projectPanel, "projectPanel", "Project");
  gtk_stack_add_titled(GTK_STACK(tabbedPanelParent), propertiesPanel, "propertiesPanel", "Properties");

  // Set the Stack to use for the StackSwitcher
  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(tabbedPanelSwitcher), GTK_STACK(tabbedPanelParent));
  
  // Place the tabbedPanelParent(Stack) to the tabbedPanelParentContainer(Box)
  gtk_box_append(GTK_BOX(tabbedPanelParentContainer), tabbedPanelSwitcher);
  gtk_box_append(GTK_BOX(tabbedPanelParentContainer), tabbedPanelParent);
  // Place the tabbedPanelParentContainer(Frame) in the topWindowContainer(Box)
  gtk_box_append(GTK_BOX(topWindowContainer), tabbedPanelGrandParentContainer);

  // [ ] [x]
  // [     ]
  compositionPanel = gtk_frame_new("compositionPanel");
  // Place the compositionPanel(Frame) in the topWindowContainer(Box)
  gtk_box_append(GTK_BOX(topWindowContainer), compositionPanel);

  // [ ] [ ]
  // [ x x ]
  timelinePanel = gtk_frame_new("timelinePanel");

  // Set windowDivideContainer children
  gtk_paned_set_start_child(GTK_PANED(windowDivideContainer), topWindowContainer);
  gtk_paned_set_end_child(GTK_PANED(windowDivideContainer), timelinePanel);

  // Put the windowDivideContainer in the window
  gtk_window_set_child(GTK_WINDOW(window), windowDivideContainer);

  // Show the window
  gtk_widget_show(window);
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("table.kiwilab", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}