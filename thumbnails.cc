#include<gtkmm.h>
#include<string>
#include<map>
#include<vector>
#include"thumbnails.h"
using namespace std;

std::map<std::string, int> getdir(string dir);

Thumbnails::Thumbnails(string dir) 
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
	bt.set_label(vert);
	set_size_request(600, 130);
	auto files = getdir(dir);
	files.erase("thumbnails");
	sstm("mkdir "+ dir + "/thumbnails");
	sstm("exiv2 -et " + dir + "/*");
	sstm("mv " + dir + "/*-thumb.jpg " + dir + "/thumbnails/");
	auto thumbs = getdir(dir + "/thumbnails");
	for(auto& a : files) {
		string s = a.first.substr(0, a.first.find_last_of('.'));
		images.push_back(Gtk::Image(dir + "/thumbnails/" + s + "-thumb.jpg"));
	}
	add(hbox1);
	hbox1.pack_start(bt, Gtk::PACK_SHRINK);
	hbox1.pack_start(scwin);
	scwin.add(hbox2);
	for(auto& a : images) hbox2.pack_start(a, Gtk::PACK_SHRINK);
}

void Thumbnails::sstm(string command)
{
	system(command.data());
}
