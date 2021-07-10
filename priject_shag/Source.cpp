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
void save_song(string songs_filename, Song song) {
	ofstream all_songs_write; // создание файла для названий всех песен
	all_songs_write.open(songs_filename, ios_base::app);
	//если введенное название новое
	all_songs_write << song.song_name << endl;
	all_songs_write.close();

	string file_name = song.song_name;               //создаем новый файл для песни
	file_name += ".txt";
	ofstream file_write;
	file_write.open(file_name);

	file_write << song.song_author << endl;       //  перекидываем в файл автора
	file_write << song.song_text;                      //и текст
	file_write.close();
}

bool user_wants_to_continue() {
	string answer = "";
	//  спрашиваем нужно ли продолжать ввод
	cout << "you want to continue adding songs? (yes/no)";
	cin >> answer;
	return answer == "yes" || answer == "y";
}

void add_songs() {
	const string songs_filename = "all_songs.txt";
	do {
		Song song; // создаем обьект для хранение данных про будущую песню
		enter_info(&song); // спрашиваем эти данные             

		if (song_already_exists(songs_filename, song.song_name)) {
			cout << "song is already created" << endl;        //если же введеное имя уже использовалось
		}
		else {
			save_song(songs_filename, song);
		}
	} while (user_wants_to_continue());
}

int main() 
{
	add_songs();
}