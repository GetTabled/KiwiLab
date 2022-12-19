#include <gtk/gtk.h>

static void activate(GtkApplication* app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *grid;

  // Create a new window
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "KiwiLab");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);

  // Initialize the grid
  grid = gtk_grid_new();
  // Put the grid in the window
  gtk_window_set_child(GTK_WINDOW(window), grid);

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