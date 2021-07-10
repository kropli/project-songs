//    dobavlenie texta
//    sohranenie texta

#include <cstring>
#include <string>
#include <string.h>
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

#define get(name) getline(cin, name)
#define ign cin.ignore(100, '\n')

// структура для будущих текстовых файлов
struct Song {                            
	string song_author;
	string song_name;
	string song_text;
};

// функция для ввода
void enter_info(Song *info) {                 
	cout << "Welcome to our audiolibrary! Please press Enter to continue";
	ign;
	cout << "enter the author of the song: ";get (info -> song_author);
	cout << "enter the name of the song: ";get (info -> song_name);
	cout << "enter text of the song: ";get (info -> song_text);
}

bool song_already_exists(string filename, string song_name) {
	string line = "";
	ifstream all_songs_read;
	all_songs_read.open(filename);
	if (all_songs_read.is_open())  cout << "file open" << endl;
	
	bool dublicate = false;

	while (!all_songs_read.eof()) { // цикл для проверки равности введеного названия песни с существующими 
		getline(all_songs_read, line);
		if (line == song_name) {
			dublicate = true;
			break;
		}
	}
	all_songs_read.close();
	return dublicate;
}

void save_song() {
	const string txt = ".txt";
	const string songs_filename = "all_songs.txt";
	string answer_continue = "";
	bool user_wants_to_continue = true;

	ofstream all_songs_write; // создание файла для названий всех песен

	while (user_wants_to_continue) {

		Song main_object; // создаем обьект для хранение данных про будущую песню
		enter_info(&main_object); // спрашиваем эти данные             

		if (song_already_exists(songs_filename, main_object.song_name)) {
			cout << "song is already created" << endl;        //если же введеное имя уже использовалось
		}
		else {
			all_songs_write.open(songs_filename, ios_base::app);
			//если введенное название новое
			all_songs_write << main_object.song_name << endl;

			string file_name = main_object.song_name;               //создаем новый файл для песни
			file_name += txt;
			ofstream file_write;
			file_write.open(file_name);

			file_write << main_object.song_author << endl;       //  перекидываем в файл автора
			file_write << main_object.song_text;                      //и текст
			file_write.close();
		}

		all_songs_write.close();

		cout << "you want to continue adding songs? (yes/no)"; cin >> answer_continue;
		user_wants_to_continue = (answer_continue != "yes");               //  спрашиваем нужно ли продолжать ввод
	}
}

int main() 
{
	save_song();
}