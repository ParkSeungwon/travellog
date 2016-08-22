#include<iostream>
using namespace std;

int main(int c, char** v)
{
	char buf[40];
	FILE* f = popen("exiv2 -pc /home/zezeon/Dropbox/Photos/6month/2014-08-13/11-24-57.JPG", "r"); 
	fgets(buf, sizeof(buf), f);
	pclose(f);
	string s(buf);
	s = s.substr(s.find(' ') + 1);
	cout << stof(s) << endl;
}
