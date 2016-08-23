#include<gtkmm.h>
#include<iostream>
#include<functional>
#include"thumbnails.h"

int main(int c, char** v)
{
	auto app = Gtk::Application::create(c, v);
	Gtk::Window win;
	Thumbnails th("/home/zezeon/Dropbox/Photos/6month/2014-08-18/");
	win.add(th);
	win.show_all_children();
	app->run(win);
}
