#include<webkit2/webkit2.h>
#include<initializer_list>
#include<string>
#include<iostream>
#include"googlemap.h"
using namespace std;

std::map<string, int> getdir(string dir);

Winmain::Winmain(string dir)
{
	directories = getdir(dir);
	for(auto& a : directories) {
		auto b = getdir(dir + '/' + a.first);
		photoes.push_back(b);
	}
	for(auto& a : photoes) for(auto& b : a) cout << b.first << endl;
	auto webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
	add(*Glib::wrap(GTK_WIDGET(webview)));
	string content = googlemap({{37.112206, 128.924017},
			{37.097790, 128.914983},
			{37.163722, 128.917627},
			{37.218231, 128.962182},
			{37.310797, 129.011924},
			{37.325828, 129.017115}});
	webkit_web_view_load_html(webview, content.c_str(), "");
	set_default_size(1024, 768);
	show_all_children();
}

string Winmain::googlemap(initializer_list<pair<float, float>> pts)
{
	string ad = "var trip = [];"
		"var marker = [];"
		"var bound = new google.maps.LatLngBounds();";
	for(auto& a : pts) {
		ad += "trip.push(new google.maps.LatLng(";
		ad += to_string(a.first) + ',' + to_string(a.second) + "));";
	}
	ad += "for(i=0; i<trip.length; i++) {"
		"marker.push(new google.maps.Marker({position:trip[i],}));"
		"bound.extend(trip[i]);"
		"marker[i].setMap(map);"
		"}"
		"var flightPath = new google.maps.Polyline({"
		"path:trip, strokeColor:'#0000FF', strokeOpacity:0.8, strokeWeight:2 });"
		"flightPath.setMap(map);"
		"map.fitBounds(bound);";
	return googlemap(0, 0, 12, 1000, 740, ad);
}

string Winmain::googlemap(float lt, float ln, int z, int w, int h, string ad)
{
	string rt = "<!DOCTYPE html> <html> <head>"
		"<script src='http://maps.googleapis.com/maps/api/js'></script>"
		"<script>function initialize() {var mapProp = {"
		"center:new google.maps.LatLng(";
	rt += to_string(lt) + ',' + to_string(ln) + "), zoom:" + to_string(z) + ',';
	rt += "mapTypeId:google.maps.MapTypeId.ROADMAP};"
		"var map=new google.maps.Map(document.getElementById('googleMap'),mapProp);";
	rt += ad + "}google.maps.event.addDomListener(window, 'load', initialize);"
		"</script> </head> <body> <div id='googleMap' style='width:";
	rt += to_string(w) + "px;height:" + to_string(h) + "px;'> </div></body></html>";
	return rt;
}

int main(int c, char** v)
{
	auto app = Gtk::Application::create(c, v, "");
	Winmain window("/home/zezeon/Dropbox/Photos/6month");
	app->run(window);
}

