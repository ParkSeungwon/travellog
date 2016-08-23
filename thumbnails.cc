#include<gtkmm.h>
#include<string>
#include<map>
#include<vector>
#include<functional>
#include<iostream>
#include"thumbnails.h"
#include"interface.h"
using namespace std;

std::map<std::string, int> getdir(string dir);
Interface* interface;

void Thumbnails::on_bt_click()
{
	interface->set_map(gps);
	cout << "clicked" << endl;
}

string Thumbnails::vlabel(string dir)
{
	string s = dir.substr(dir.find_last_of('/') + 1);
	s.erase(0, 2);
	string vert;
	for(auto& a : s) {
		if(a != '-') {
			vert += a; 
			vert += '\n';
		}
	}
	vert.pop_back();
	return vert;
}

Thumbnails::Thumbnails(string dir) 
{
	bt.set_label(vlabel(dir));
	bt.signal_clicked().connect(bind(&Thumbnails::sstm, this, "ls"));
	set_size_request(900, 140);
	auto files = getdir(dir);
	files.erase("thumbnails");
//	sstm("mkdir "+ dir + "/thumbnails");
//	sstm("exiv2 -et " + dir + "/*");
//	sstm("mv " + dir + "/*-thumb.jpg " + dir + "/thumbnails/");
	auto thumbs = getdir(dir + "/thumbnails");
	int i=0;
	for(auto& a : files) {
		char buf[40];
		FILE* f = popen(("exiv2 -pc " + dir + '/' + a.first).c_str(), "r"); 
		fgets(buf, sizeof(buf), f);
		pclose(f);
		string s(buf);
		cout << s << endl;
		int sp = s.find(' ');
		float lat = stof(s.substr(0, sp));
		float lng = stof(s.substr(sp+1));
		gps.push_back({lat, lng});
		s = a.first.substr(0, a.first.find_last_of('.'));
		ims.push_back(Gtk::Image{dir + "/thumbnails/" + s + "-thumb.jpg"});
		bts.push_back(Gtk::Button());
		bts.back().set_image(ims.back());
		bts.back().signal_clicked().connect(bind(&Thumbnails::sstm, this, "shotwell " + dir + '/' + a.first +'&'));
	}
	add(hbox1);
	hbox1.pack_start(bt, Gtk::PACK_SHRINK);
	hbox1.pack_start(scwin);
	scwin.add(hbox2);
	for(auto& a : bts) hbox2.pack_start(a, Gtk::PACK_SHRINK);
}

void Thumbnails::sstm(string command)
{
	system(command.data());
}
