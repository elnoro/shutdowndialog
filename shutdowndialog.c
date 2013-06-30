#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdlib.h>

gint key_press(GtkWidget *window, GdkEventKey *event, gpointer data);
void system_wrapper(GtkWidget *button, gpointer data);
void close_app(GtkWidget *button, gpointer data);

int main(int argc, char *argv[])
{
	GtkWidget *window, *label, *poweroff_button, *reboot_button, *escape_button, *vbox, *hbox;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Завершение работы");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

	label = gtk_label_new("Выберите действие:");
	poweroff_button = gtk_button_new_with_label("Выключение");
	reboot_button = gtk_button_new_with_label("Перезагрузка");
	escape_button = gtk_button_new_with_label("Отмена");
	vbox = gtk_vbox_new(FALSE, 10);
	hbox = gtk_hbox_new(FALSE, 10);
	
	gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), poweroff_button, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), reboot_button, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), escape_button, TRUE, FALSE, 5);

	gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, FALSE, 0);
	
	gtk_container_add(GTK_CONTAINER(window), hbox);

	g_signal_connect(GTK_OBJECT(poweroff_button), "clicked", GTK_SIGNAL_FUNC(system_wrapper), "echo \"password\" | sudo -S poweroff");
	g_signal_connect(GTK_OBJECT(reboot_button), "clicked", GTK_SIGNAL_FUNC(system_wrapper), "echo \"password\" | sudo -S reboot");
	g_signal_connect(GTK_OBJECT(escape_button), "clicked", GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
	g_signal_connect(GTK_OBJECT(window), "key_press_event", G_CALLBACK(key_press), NULL);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}

gint key_press(GtkWidget *window, GdkEventKey *event, gpointer data) {
	if (event->keyval == GDK_KEY_Escape) {
		gtk_main_quit();
	}
}
void system_wrapper(GtkWidget *button, gpointer data) {
	system((char*) data);
}
void close_app(GtkWidget *button, gpointer data) {
	gtk_main_quit();
}
