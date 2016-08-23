#include"googlemap.h"
#include<string>

int main(int c, char** v)
{
	int i=0;
	std::string s;
	if(c<2) s = "/home/zezeon/Dropbox/Photos/6month/";
	else s = v[1];
	auto app = Gtk::Application::create(i, v, "");
	Winmain window(s);
	app->run(window);
}

