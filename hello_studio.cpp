#include<filesystem>
#include<iostream>
#include<string>
using namespace std;
namespace fs = std::filesystem;

void file_search(const fs::path& file,string &ext,vector<string> &files)
{
	try {
		fs::directory_iterator item(file,fs::directory_options::skip_permission_denied), end;
		while(item!=end) {
			if ((fs::status(item->path()).permissions() & fs::perms::owner_read) != fs::perms::none) {
				if (fs::is_regular_file(item->symlink_status()) == true && item->path().extension() == ext)
				{
					files.push_back(item->path().string());
				}
				if (fs::is_directory(item->symlink_status()) == true)
				{
					fs::path df(fs::path(item->path()));
					//cout << "Folder:" << p.path() << endl;
					file_search(df,ext,files);
				}
			}
			item++;
		}
	}
	catch (fs::filesystem_error e)
	{
		//cout << e.what() << endl;
	}
}



int main()
{

	string ext;
	cout << "Enter the type of file you want to search in D : ";
	getline(cin, ext);
	ext = "." + ext;
	//cout << ext << endl;
	//fs::path file_C("C:\\");
	//file_search(file_C,ext);
	vector<string> files;
	fs::path file_D("D:\\");
	file_search(file_D,ext,files);
	fs::path file_C("C:\\Users");
	file_search(file_C, ext,files);
	//cout << "Press enter to close.......";
	//cin.get();
	string fg;
	int n;
	for (auto& i : files)
	{
		string s = "";
		for (int j = 0; j < i.length(); j++)
		{
			string s1 = ""; int flag = 0;
			while (j<i.length() && i[j] != '\\') {
				if (i[j] == ' ')
					flag = 1;
				s1 += i[j];
				j++;
			}
			if (flag == 1 && j!=i.length())
				s += "\"" + s1 + "\"\\";
			else if(flag == 1)
				s += "\"" + s1 + "\"";
			else if (j!=i.length())
				s += s1 + "\\";
			else
				s += s1;
		}
		i = s;
	}
	for (int i = 0; i < files.size(); i++)
		cout << i << ". " << files[i] << endl;
	while (1)
	{
		cout << "Enter the index to play or -1 to exit:";
		cin >> n;
		if (n == -1)
			break;
		else if (n > files.size())
			cout << "Enter a proper index" << endl;
		else
		{
			fg = "start " + files[n];
			system(fg.c_str());
		}
			
	}
	return 0;
}