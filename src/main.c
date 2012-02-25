#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include <cairo.h>

#include "shape.h"
#include "game.h"

Game *game;

static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	Game* game= (Game*)data;
	switch(event->keyval)
	{
		case GDK_Up:
			game_rotate_left(game);
			break;
		case GDK_Left:
			game_move_left(game);
			break;
		case GDK_Right:
			game_move_right(game);
			break;
		case GDK_Down:
			game_rotate_right(game);
			break;
		case GDK_Space:
			game_drop_to_bottom(game);
			break;
	}

	return FALSE;
}

static gboolean on_timer(Game *game)
{
	if(!game->isStarted)
		return;
	if(game->isPaused)
		return;

	if(game->isFallingFinished)
	{
		game->isFallingFinished = false;
		game_new_piece(game);
	}
	else
	{
		game_one_line_down(game);
	}
	
//	gtk_widget_queue_draw(game->window);
	game_refresh(game);
	return true;
}

static gboolean on_expose(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	return FALSE;
}

int main(int argc, char **argv)
{
	GtkWidget *window;
	GtkWidget *drawArea;

	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Tetris");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window),10, 22);

	drawArea = gtk_drawing_area_new();
	gtk_container_add(GTK_CANTAINER(window), drawArea);
	GTK_WIDGET_SET_FLAGS(drawArea, GTiK_CAN_FOCUS);
	gtk_widget_grab_focus(drawArea);

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(drawArea, "expose-event", G_CALLBACK(on_expose),NULL);
	g_signal_connect(drawArea, "key-press-event", G_CALLBACK(on_key_press),NULL);
	g_timeout_add(500, (GSourceFunc)on_timer, (gpointer)game);
	
	gtk_widget_show_all(window);
	gtk_main();
	
	return 0;
}
