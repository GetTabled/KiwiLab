/***
  KiwiLab - Free and open-source video editing application
  Copyright (C) 2022 GetTabled
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#include <gtk/gtk.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include "ui/main.h"

static void importFile(GtkButton *source, gpointer user_data) {
  // TODO::Open FileChooserDialog
  g_print("Importing file");
}

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *windowDivideContainer;

  GtkWidget *topWindowContainer;

  GtkWidget *tabbedPanelGrandParentContainer;
  GtkWidget *tabbedPanelParentContainer;
  GtkWidget *tabbedPanelParent;
  GtkWidget *tabbedPanelSwitcher;

  GtkWidget *projectPanel;
  GtkWidget *importButton;

  GtkWidget *propertiesPanel;

  GtkWidget *compositionPanel;
  GtkWidget *frameDisplay;

  GtkWidget *timelinePanel;


  // Create a new window
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "KiwiLab");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);

  windowDivideContainer = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  
  // [x] [ ]
  // [     ]
  topWindowContainer = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  tabbedPanelGrandParentContainer =  gtk_frame_new(NULL);
  tabbedPanelParentContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_frame_set_child(GTK_FRAME(tabbedPanelGrandParentContainer), tabbedPanelParentContainer);
  
  tabbedPanelParent = gtk_stack_new();
  tabbedPanelSwitcher = gtk_stack_switcher_new();

  projectPanel = gtk_frame_new("projectPanel");
  importButton = gtk_button_new_with_label("Import");
  g_signal_connect(GTK_BUTTON(importButton), "clicked", G_CALLBACK(importFile), NULL);
  gtk_frame_set_child(GTK_FRAME(projectPanel), importButton);

  propertiesPanel = gtk_frame_new("propertiesPanel");

  // Add childs to the Stack(tabbedPanelParent)
  gtk_stack_add_titled(GTK_STACK(tabbedPanelParent), projectPanel, "projectPanel", "Project");
  gtk_stack_add_titled(GTK_STACK(tabbedPanelParent), propertiesPanel, "propertiesPanel", "Properties");

  // Set the Stack to use for the StackSwitcher
  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(tabbedPanelSwitcher), GTK_STACK(tabbedPanelParent));
  
  // Place the tabbedPanelParent(Stack) to the tabbedPanelParentContainer(Box)
  gtk_box_append(GTK_BOX(tabbedPanelParentContainer), tabbedPanelSwitcher);
  gtk_box_append(GTK_BOX(tabbedPanelParentContainer), tabbedPanelParent);
  // Place the tabbedPanelParentContainer(Frame) in the topWindowContainer(Pane)
  gtk_paned_set_start_child(GTK_PANED(topWindowContainer), tabbedPanelGrandParentContainer);

  // [ ] [x]
  // [     ]
  compositionPanel = gtk_frame_new("compositionPanel");
  frameDisplay = gtk_drawing_area_new();
  gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(frameDisplay), 200);
  gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(frameDisplay), 200);
  //gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(frameDisplay), NULL, NULL, NULL);
  gtk_frame_set_child(GTK_FRAME(compositionPanel), frameDisplay);
  // Place the compositionPanel(Frame) in the topWindowContainer(Pane)
  gtk_paned_set_end_child(GTK_PANED(topWindowContainer), compositionPanel);

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
  int status;

  // GTK application initialization
  app = gtk_application_new("table.kiwilab", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}