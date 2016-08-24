#include"googlemap.h"

int main(int c, char** v)
{
	int i=0;
	const char* p;
	if(c<2) p = "/home/zezeon/Dropbox/Photos/6month/";
	else p = v[1];
	auto app = Gtk::Application::create(i, v, "");
	Winmain window(p);
	app->run(window);
}

