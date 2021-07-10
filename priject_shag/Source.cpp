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

struct Song {                            // структура для будущих текстовых файлов
	string song_author;
	string song_name;
	string song_text;
};

void enter_info(Song *info) {                 //           фунция для ввода
	ign;
	cout << "enter the author of the song: ";get (info -> song_author);
	cout << "enter the name of the song: ";get (info -> song_name);
	cout << "enter text of the song: ";get (info -> song_text);
	
}
void save_song() {
	string txt = ".txt";
	string answer_end = "";
	bool answer = false;

	ofstream all_songs_write;                     // создание файла для названий всех песен

	while (!answer) {
		string line = "";
		bool dublicate = false;

		Song main_object;                        //     содаем обьект для хранение данных про будующую песню
		enter_info(&main_object);                   //  спрашиваем эти данные             

		ifstream all_songs_read;
		all_songs_read.open("all_songs.txt");
		if (all_songs_read.is_open())  cout << "file open" << endl;

		while (!all_songs_read.eof()) {      // цыкл для проверки равности введеного названия песни с существующими 
			getline(all_songs_read, line);
			if (line == main_object.song_name) {
				dublicate = true;
				break;
			}
		}

		all_songs_write.open("all_songs.txt", ios_base::app);

		if (!dublicate) {		                                           //   если введенное название новое
			all_songs_write << main_object.song_name << endl;

			string file_name = main_object.song_name;               //     создаем новый файл для песни
			file_name += txt;
			ofstream file_write;
			file_write.open(file_name);

			file_write << main_object.song_author << endl;             //  перекидываем в файл автора
			file_write << main_object.song_text;                       //     и текст
			file_write.close();
		}
		else cout << "song is already created" << endl;        // если же введеное имя уже использовалось

		all_songs_write.close();
		all_songs_read.close();

		cout << "you want to end adding songs ?(yes/no)"; cin >> answer_end;
		answer = (answer_end == "yes");               //  спрашиваем нужно ли продолжать ввод
	}
	
}

int main() {
	save_song();
}