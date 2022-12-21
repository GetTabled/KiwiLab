#include <gtk/gtk.h>

static void activate(GtkApplication* app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *windowDivideContainer;

  GtkWidget *grid;
  GtkWidget *tabbedPanelParentContainer;
  GtkWidget *tabbedPanelParent;
  GtkWidget *tabbedPanelSwitcher;
  GtkWidget *projectPanel;
  GtkWidget *propertiesPanel;

  GtkWidget *compositionPanel;

  GtkWidget *timelinePanel;

  GtkWidget *label;

  // Create a new window
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "KiwiLab");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);

  windowDivideContainer = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  
  // [x] [ ]
  // [     ]
  grid = gtk_grid_new();
  tabbedPanelParentContainer = gtk_frame_new("tabbedPanelParentContainer");
  
  tabbedPanelParent = gtk_stack_new();
  tabbedPanelSwitcher = gtk_stack_switcher_new();

  projectPanel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 300);
  label = gtk_label_new("Project panel");
  gtk_box_prepend(GTK_BOX(projectPanel), label);

  propertiesPanel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 300);
  label = gtk_label_new("Properties panel");
  gtk_box_prepend(GTK_BOX(propertiesPanel), label);

  gtk_stack_add_child(GTK_STACK(tabbedPanelParent), projectPanel);
  gtk_stack_add_child(GTK_STACK(tabbedPanelParent), propertiesPanel);

  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(tabbedPanelSwitcher), GTK_STACK(tabbedPanelParent));
  
  gtk_frame_set_child(GTK_FRAME(tabbedPanelParentContainer), tabbedPanelParent);
  gtk_grid_attach(GTK_GRID(grid), tabbedPanelParentContainer, 0, 0, 1, 1);

  // [ ] [x]
  // [     ]
  compositionPanel = gtk_frame_new("compositionPanel");
  gtk_grid_attach(GTK_GRID(grid), compositionPanel, 1, 0, 1, 1);

  // [ ] [ ]
  // [ x x ]
  timelinePanel = gtk_frame_new("timelinePanel");

  // Set windowDivideContainer children
  gtk_paned_set_start_child(GTK_PANED(windowDivideContainer), grid);
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