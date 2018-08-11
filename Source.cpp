#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>
//#include <KnownFolders.h>
//#include <ShlObj.h>


using namespace std;
#define SDL_MAIN_HANDLED
//#include <simple2d.h>
const string path = "C:\\LSB Organ Catalog\\";
enum LSBCategory {ADVENT, CHRISTMAS, EPIPHANY, LENT, HOLYWEEK, EASTER, PENTECOST, HOLYTRINITY, ENDTIMES, FEASTSANDFESTIVALS,
	REDEEMER, JUSTIFICATION, THEWORDOFGOD, HOLYBAPTISM, BAPTISMALLIFE, CONFESSIONANDABSOLUTION, THELORDSSUPPER, THECHURCH,
	THECHURCHMILITANT, THECHURCHTRIUMPHANT, ORDINATIONINSTALLATION, SANCTIFICATION, TRUST, HOPEANDCOMFORT, PRAYER, STEWARDSHIP,
	PRAISEANDADORATION, MISSIONANDWITNESS, SOCIETY, VOCATION, MARRIAGE, CHRISTIANHOMEANDEDUCATION, MORNING, EVENING, 
	HARVESTANDTHANKSGIVING, NEWYEAR, BEGINNINGOFSERVICE, CLOSEOFSERVICE, BIBLICALCANTICLES, LITURGICALMUSIC, NATIONANDNATIONALSONGS, NOCATEGORY};
const string categoryList[42] = { "Advent", "Christmas", "Epiphany", "Lent", "Holy Week", "Easter", "Pentecost", "Holy Trinity", "End Times", "Feasts and Festivals",
		"Redeemer", "Justification", "The Word of God", "Holy Baptism", "Baptismal Life", "Confession and Absolution", "The Lord\'s Supper", "The Church",
		"The Church Militant", "The Church Triumphant", "Ordination, Installation", "Sanctification", "Trust", "Hope and Comfort", "Prayer", "Stewardship",
		"Praise and Adoration", "Mission and Witness", "Society", "Vocation", "Marriage", "Christian Home and Education", "Morning", "Evening",
		"Harvest and Thanksgiving", "New Year", "Beginning of Service", "Close of Service", "Biblical Canticles", "Liturgical Music", "Nation and National Songs", "No Category Specified"};
enum LSBKey { Ab, A, ASHARP, Bb, B, C, CSHARP, Db, D, DSHARP, Eb, E, F, FSHARP, Gb, G, GSHARP, NOKEY };
const string keyList[18] = { "A Flat", "A", "A Sharp", "B Flat", "B", "C", "C Sharp", "D Flat" , "D" , "D Sharp" , "E Flat" , "E" , "F" , "F Sharp" , "G Flat" , "G" , "G Sharp", "No Key Specified" };
int test = 0;
string textCenterer(string blahblahblah) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns = 0;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	columns = columns / 2;
	string whiteSpace((columns - (blahblahblah.size() / 2)), ' ');
	return (whiteSpace + blahblahblah);
} //end textCenterer

string printLSBCategory(int category) {
	return categoryList[category];
}
string printKey(int key) {
	return keyList[key];
}

class hymnEntry {
private:
	string tuneName = "";
	int noOfHymns = 0;
	vector<string> hymnNames = {};
	vector<unsigned short> LSBNumbers = {};
	vector<LSBCategory> category = {};
	vector<LSBKey> key = {};
	bool complete = true;

	void testForComplete() {
		if (tuneName == "") {
			complete = false;
			return;
		}
		if (noOfHymns == 0) {
			complete = false;
			return;
		}
		for (int q = 0; q < noOfHymns; q++) {
			if (hymnNames.at(q) == "") {
				complete = false;
				return;
			}
		}
		for (int w = 0; w < noOfHymns; w++) {
			if (LSBNumbers.at(w) == 0) {
				complete = false;
				return;
			}
		}
		for (int e = 0; e < noOfHymns; e++) {
			if (category.at(e) == NOCATEGORY) {
				complete = false;
				return;
			}
		}
		for (int f = 0; f < noOfHymns; f++) {
			if (key.at(f) == NOCATEGORY) {
				complete = false;
				return;
			}
		}
		return;
	}

public:

	string getTuneName() {
		return tuneName;
	}
	int getNoOfHymns() {
		return noOfHymns;
	}
	vector<string> getHymnNameVector() {
		return hymnNames;
	}
	string getHymnName(unsigned int No) {
		return hymnNames.at(No);
	}
	vector<unsigned short> getLSBNumberVector() {
		return LSBNumbers;
	}

	int getLSBNumber(unsigned int no) {
		return LSBNumbers.at(no);
	}
	LSBCategory getCategory(unsigned int nO) {
		return category.at(nO);
	}
	LSBKey getKey(unsigned int NOPE) {
		return key.at(NOPE);
	}
	bool getComplete() {
		return complete;
	}

	

	void saveHymnEntry() {
		//PWSTR path = NULL;
		//HRESULT hr = SHGetKnownFolderPath(FOLDERID_ProgramFiles, 0, NULL, &path);
		ofstream outputFile(path + tuneName + ".txt");

		outputFile << "<tuneName>" << tuneName << "<\\tuneName>\n<#>" << noOfHymns << "<\\#>\n";
		for (int i = 0; i < noOfHymns; i++) {
			outputFile << "<" << i << ">\n<hymnName>" << hymnNames.at(i) << "<\\hymnName><LSB#>" << LSBNumbers.at(i) << "<\\LSB#><category>" << category.at(i) << "<\\category><key>" << key.at(i) << "<\\key>\n<\\" << i << ">" << endl;

		}
		outputFile.close();
	}

	void setHymnEntry(string NO, bool edit) {
		if (!edit) {
			tuneName = NO;
			cout << "How many hymns does this tune cover? Required." << endl;
			cin >> noOfHymns;
			while (noOfHymns <= 0 || noOfHymns > 5) {
				cout << "Nope. Try again." << endl;
				cin >> noOfHymns;
			}
			hymnNames.resize(noOfHymns, "");
			LSBNumbers.resize(noOfHymns, 0);
			category.resize(noOfHymns, NOCATEGORY);
			key.resize(noOfHymns, NOKEY);
			cin.ignore(1000, '\n');
		}
		
		for (int i = 0; i < noOfHymns; i++) {
			string nullValueTest;
			cout << "Hymn Name?";
			if (edit) {
				cout << " Current is " << hymnNames.at(i);
			}
			cout << endl;
			getline(cin, hymnNames.at(i));
			cout << "LSB Number?";
			if (edit) {
				cout << " Current is " << LSBNumbers.at(i);
			}
			cout << endl;
			getline(cin, nullValueTest);
			if (nullValueTest == "") {
				LSBNumbers.at(i) = 0;
			}
			else
				LSBNumbers.at(i) = stoi(nullValueTest);
			cout << "Category? See legend.";
			if (edit) {
				cout << " Current is " << category.at(i) << ": " << printLSBCategory(category.at(i));
			}
			cout << endl;
			getline(cin, nullValueTest);
			if (nullValueTest == "") {
				category.at(i) = NOCATEGORY;
			}
			else
				category.at(i) = LSBCategory(stoi(nullValueTest)); 
			cout << "Key of the Hymn? See legend.";
			if (edit) {
				cout << " Current is " << key.at(i) << ": " << printKey(key.at(i));
			}
			cout << endl;
			getline(cin, nullValueTest);
			if (nullValueTest == "") {
				key.at(i) = NOKEY;
			}
			else
				key.at(i) = LSBKey(stoi(nullValueTest)); 
		}
		
		saveHymnEntry();
		testForComplete();
	}
	void load(string f) {
		int beginning = 0;
		int length = 0;
		 const string g[7] = { "tuneName", "#", "4","3","2","1","0" };
		 const string h[4] = { "hymnName", "LSB#", "category" , "key"};

		for (int i = 0; i < 7; i++) {
			beginning = f.find("<" + g[i] + ">") + g[i].size() + 2;
			length = f.find("<\\" + g[i] + ">") - beginning;
			switch (i) {
			case 0:
				tuneName = f.substr(beginning, length);
				break;
			case 1:
				noOfHymns = stoi(f.substr(beginning, length));
				hymnNames.resize(noOfHymns);
				LSBNumbers.resize(noOfHymns);
				category.resize(noOfHymns);
				key.resize(noOfHymns);
				i = 6 - noOfHymns;
				break;
			default:
				string smaller = f.substr(beginning, length);
				for (int a = 0; a < 4; a++) {
					int beginning1 = smaller.find("<" + h[a] + ">") + h[a].size() + 2;
					int length1 = smaller.find("<\\" + h[a] + ">") - beginning1;
					switch (a) {
					case 0:
						hymnNames.at(6 - i) = smaller.substr(beginning1, length1);
						break;
					case 1:
						LSBNumbers.at(6 - i) = stoi(smaller.substr(beginning1, length1));
						break;
					case 2:
						category.at(6 - i) = LSBCategory(stoi(smaller.substr(beginning1, length1)));
						break;
					case 3:
						key.at(6 - i) = LSBKey(stoi(smaller.substr(beginning1, length1)));
						break;

					}
				}
			}
		}
		testForComplete();
	}

	void printDetails(int number) {
		cout << textCenterer("Result: " + to_string(number) + "  Tune Name: " + tuneName) << "\n\nHymns:\n";
		for (int o = 0; o < noOfHymns; o++) {
			cout << "  " << LSBNumbers.at(o) << "  " << hymnNames.at(o) << "  Category: " << printLSBCategory(category.at(o)) << "   Key: " << printKey(key.at(o)) << "\n" << endl;
		}
	}
	
};

class pageEntry {
private:
	string hymnTitle = "";
	string bookTitle = "";
	string composer = "";
	int pageNumber = 0;
	LSBKey key = NOKEY;


public:
	string getHymnTitle() {
		return hymnTitle;
	}

	string getBookTitle() {
		return bookTitle;
	}

	string getComposer() {
		return composer;
	}

	int getPageNumber() {
		return pageNumber;
	}
	LSBKey getKey() {
		return key;
	}

	void savePageEntry() {
		//PWSTR path = NULL;
		//HRESULT hr = SHGetKnownFolderPath(FOLDERID_ProgramFiles, 0, NULL, &path);
		ofstream outputFile(path + "User Catalog\\" + bookTitle + "_" + hymnTitle + ".txt");

		outputFile << "<hymnTitle>" << hymnTitle << "<\\hymnTitle>\n<bookTitle>" << bookTitle << "<\\bookTitle>\n<composer>" << composer << "<\\composer>\n<page#>" << pageNumber << "<\\page#>\n<key>" << key << "<\\key>" << endl;

		outputFile.close();
	}

	void setPageEntry(string NO, bool edit) {
		if (!edit) {
			hymnTitle = NO;
			cin.ignore(1000, '\n');
		}

		string nullValueTest;
	
		cout << "Book title?";
		if (edit) {
			cout << " Current is " << bookTitle;
		}
		cout << endl;
		getline(cin, bookTitle);

		cout << "Composer name?";
		if (edit) {
			cout << " Current is " << composer;
		}
		cout << endl;
		getline(cin, composer);

		cout << "Page number?";
		if (edit) {
			cout << " Current is " << pageNumber;
		}
		cout << endl;
		getline(cin, nullValueTest);
		if (nullValueTest == "") {
			pageNumber = 0;
		}
		else
			pageNumber = stoi(nullValueTest);


		cout << "Key of the piece? See legend.";
		if (edit) {
			cout << " Current is " << key << ": " << printKey(key);
		}
		cout << endl;
		getline(cin, nullValueTest);
		if (nullValueTest == "") {
			key = NOKEY;
		}
		else
			key = LSBKey(stoi(nullValueTest));


		savePageEntry();
	}
	void load(string f) {
		int beginning = 0;
		int length = 0;
		const string h[5] = { "hymnTitle", "bookTitle", "composer", "page#" , "key" };
		for (int a = 0; a < 5; a++) {
			int beginning = f.find("<" + h[a] + ">") + h[a].size() + 2;
			int length = f.find("<\\" + h[a] + ">") - beginning;
			switch (a) {
			case 0:
				hymnTitle = f.substr(beginning, length);
				break;
			case 1:
				bookTitle = f.substr(beginning, length);
				break;
			case 2:
				composer = f.substr(beginning, length);
				break;
			case 3:
				pageNumber = stoi(f.substr(beginning, length));
			case 4:
				key = LSBKey(stoi(f.substr(beginning, length)));
				break;

			}
		}
	}


	

	void printDetails(int number) {
		cout << textCenterer("Result: " + to_string(number) + "  Book Title: " + bookTitle)<<endl;
		
		cout << "  pg. " << pageNumber << "  " << hymnTitle << ",  by: " << composer << "   Key: " << printKey(key) << "\n" << endl;
		
	}

};
vector<hymnEntry> loadHymnEntry() {
	vector<hymnEntry> loading;
	_WIN32_FIND_DATAA thing;
	_WIN32_FIND_DATAA p;

	HANDLE h = FindFirstFileA("C:\\LSB Organ Catalog\\*.txt", &thing);
	
	int counter = 1;

	
	while (FindNextFileA(h, &p) != 0) {
		counter++;
	}
	loading.resize(counter);
	counter = 0;
	h = FindFirstFileA("C:\\LSB Organ Catalog\\*.txt", &thing);
	for (int r = 0; r < loading.size(); r++) {
		string txtFile;
		string s;
		string holder;
		holder = thing.cFileName;
		ifstream file(path + holder);

		while (!file.eof()) {
			getline(file, s);
			txtFile += s + "\n";

		}
		loading.at(counter++).load(txtFile);
		FindNextFileA(h, &thing);
	} 
	return loading;
}

vector<pageEntry> loadPageEntry() {
	vector<pageEntry> loading;
	_WIN32_FIND_DATAA thing;
	_WIN32_FIND_DATAA p;

	HANDLE h = FindFirstFileA("C:\\LSB Organ Catalog\\User Catalog\\*.txt", &thing);

	int counter = 1;


	while (FindNextFileA(h, &p) != 0) {
		counter++;
	}
	loading.resize(counter);
	counter = 0;
	h = FindFirstFileA("C:\\LSB Organ Catalog\\User Catalog\\*.txt", &thing);
	for (int r = 0; r < loading.size(); r++) {
		string txtFile;
		string s;
		string holder;
		holder = thing.cFileName;
		ifstream file(path + "User Catalog\\" + holder);

		while (!file.eof()) {
			getline(file, s);
			txtFile += s + "\n";

		}
		loading.at(counter++).load(txtFile);
		FindNextFileA(h, &thing);
	}
	return loading;
}
void update() {
	
}
/*void render() {
	int cornerLength = 150;
	S2D_DrawTriangle(
		0, 720-cornerLength, .965, .97, 1.0, .5,
		0, 720, 0, 0, 1.0, .5,
		cornerLength, 720, .965, .97, 1.0, .5
	);
	S2D_DrawTriangle(
		1280, 720-cornerLength, .965, .97, 1.0, .5,
		1280, 720, 1.0, .63, .28, .75,
		1280-cornerLength, 720, .965, .97, 1.0, .5
	);
	//S2D_Text *header = S2D_CreateText("vera.ttf", "Hello world!", 20);
	//S2D_DrawText(header);
}*/


int main() {

	string tester;
	cout << "Welcome, loading..." << endl;

	vector <hymnEntry> hymnDB;
	hymnDB = loadHymnEntry();
	vector <pageEntry> pageDB;
	pageDB = loadPageEntry();
	/*if (!CreateDirectory("C:\\Program Files\\Music Catalog", NULL))
		std::cout << "Creating failed";
	else
		std::cout << "Success!";*/

		/*S2D_Window *window = S2D_CreateWindow(
			"LSB Organ Catalog", 1280, 720, NULL, render, 0
		);
		window->background.r = 0.965;
		window->background.g = 0.97;
		window->background.b = 1.0;
		window->background.a = 1.0;
		//S2D_Show(window);*/


	cout << "Developer options?" << endl;

	cin >> tester;

	if (tester == "24601") {
		while (true) {
			cout << "Enter 1 for add hymnal entry\n2 for update existing entry\n3 for search\n0 to quit" << endl;
			int testing = 0;
			cin >> testing;
			cin.ignore(1000, '\n');
			if (testing == 0) {
				break;
			}
			switch (testing) {
			case 1: {
				string tuneName;

				cout << "Hymn tune? Required." << endl;

				getline(cin, tuneName);
				//string path = ("C:\\Users\\Student\\Documents\\LSB Organ Catalog\\" + tuneName + ".org");
				//ofstream outputFile(path);
				//outputFile << tuneName;
				hymnDB.resize(hymnDB.size() + 1);
				hymnDB.at(hymnDB.size() - 1).setHymnEntry(tuneName, false);
				break;
			}
			case 2: {
				string search;
			RESTART:
				cout << "Please enter tune name: ";
				getline(cin, search);
				for (int q = 0; q < hymnDB.size(); q++) {
					if (hymnDB.at(q).getTuneName() == search) {
						hymnDB.at(q).printDetails(1);
						cout << "Is this the correct hymn to update? y or n.";
						cin >> tester;
						cin.ignore(1000, '\n');
						if (tester == "y") {
							hymnDB.at(q).setHymnEntry("", true);
							goto ENDEDIT;
						}
						else { goto RESTART; }
					}
				}
				cout << "No hymn found with that title." << endl;
				goto RESTART;

			ENDEDIT:
				break;
			}

			case 3: {
				int counter = 1;
				int testinglicious = 0;
				string search;
				cout << "Search by what?\n1 for tune name\n2 for LSB number\n3 for hymn name\n4 by category\n5 by key\n6 for list of incomplete entries (ignore search term)" << endl;
				cin >> testinglicious;
				cin.ignore(1000, '\n');
				cout << "Please enter the search term:" << endl;
				getline(cin, search);
				for (int q = 0; q < hymnDB.size(); q++) {
					switch (testinglicious) {
					case 1:
						if (hymnDB.at(q).getTuneName().find(search) != string::npos) {
							hymnDB.at(q).printDetails(counter++);
						}
						break;
					case 2:
						for (int u = 0; u < hymnDB.at(q).getNoOfHymns(); u++) {
							if (hymnDB.at(q).getLSBNumber(u) == stoi(search)) {
								hymnDB.at(q).printDetails(counter++);
								break;
							}
						}break;
					case 3:
						for (int u = 0; u < hymnDB.at(q).getNoOfHymns(); u++) {
							if (hymnDB.at(q).getHymnName(u).find(search) != string::npos) {
								hymnDB.at(q).printDetails(counter++);
								break;
							}
						}break;
					case 4:
						for (int u = 0; u < hymnDB.at(q).getNoOfHymns(); u++) {
							if (hymnDB.at(q).getCategory(u) == stoi(search)) {
								hymnDB.at(q).printDetails(counter++);
								break;
							}
						}break;
					case 5:
						for (int u = 0; u < hymnDB.at(q).getNoOfHymns(); u++) {
							if (hymnDB.at(q).getKey(u) == stoi(search)) {
								hymnDB.at(q).printDetails(counter++);
								break;
							}
						}break;
					case 6:
						if (!hymnDB.at(q).getComplete()) {
							hymnDB.at(q).printDetails(counter++);
						}
						break;
					default:
						break;
					}
				}
				break;
			}
			}
		}





	}  // end developer options
	else {
	START:
		while (true) {
			cout << "Enter 1 to add an entry to the catalog.\nEnter 2 to edit an existing entry.\nEnter 3 to search the hymnal database.\nEnter 4 to search hymnal database (linked to book catalog).\nEnter 5 to search book catalog separately\nEnter 0 to quit" << endl;
			int testing = 0;
			cin >> testing;
			cin.ignore(1000, '\n');
			vector<hymnEntry> searchVector = {};
			string thingaling;
			if (testing == 0)
				break;

			switch (testing) {
			case 1:
			case 2:
				while (true) {
					int counter1 = 1;
					cout << "Enter hymn tune: ";
					getline(cin, thingaling);
					for (int q = 0; q < hymnDB.size(); q++) {
						if (hymnDB.at(q).getTuneName().find(thingaling) != string::npos) {
							hymnDB.at(q).printDetails(counter1++);
							searchVector.push_back(hymnDB.at(q));
						}
					}
					if (searchVector.size() > 0) {
						while (true) {
							cout << "Enter which result you would like to create an entry for: ";
							cin >> counter1;
							try {
								thingaling = searchVector.at(counter1 - 1).getTuneName();
							}
							catch (const out_of_range& oor) {
								cout << "That is not a valid option. Please try again." << endl;
								continue;
							}
							pageDB.resize(pageDB.size() + 1);
							if (testing == 1) {
								pageDB.at(pageDB.size() - 1).setPageEntry(thingaling, false);
							//	cout << "Continue with the same book? y or n.";
								//string blarg;
								//cin >> blarg;
								//if (blarg == "y") {

								//}
							}
							else {
								pageDB.at(pageDB.size() - 1).setPageEntry(thingaling, true);
							}
							break;
						}
						break;
					}
					else {
						cout << "No tune found containing this in its title. Please try again." << endl;
					}
				}

				break;

			case 3:
			case 4:
			{
				int counter3 = 1;
				int testinglicious = 0;

				cout << "Search by what?\nEnter 1 for tune name\n2 for LSB number\n3 for hymn name\n4 for category\n5 for key" << endl;
				cin >> testinglicious;
				cin.ignore(1000, '\n');
				cout << "Please enter the search term:" << endl;
				getline(cin, thingaling);
				for (int q = 0; q < hymnDB.size(); q++) {
					switch (testinglicious) {
					case 1:
						if (hymnDB.at(q).getTuneName().find(thingaling) != string::npos) {
							hymnDB.at(q).printDetails(counter3++);
							searchVector.push_back(hymnDB.at(q));

						}
						break;
					case 2:
						for (int u = 0; u < hymnDB.at(q).getNoOfHymns(); u++) {
							if (hymnDB.at(q).getLSBNumber(u) == stoi(thingaling)) {
								hymnDB.at(q).printDetails(counter3++);
								searchVector.push_back(hymnDB.at(q));
								break;
							}
						}break;
					case 3:
						for (int u = 0; u < hymnDB.at(q).getNoOfHymns(); u++) {
							if (hymnDB.at(q).getHymnName(u).find(thingaling) != string::npos) {
								hymnDB.at(q).printDetails(counter3++);
								searchVector.push_back(hymnDB.at(q));
								break;
							}
						}break;
					case 4:
						for (int u = 0; u < hymnDB.at(q).getNoOfHymns(); u++) {
							if (hymnDB.at(q).getCategory(u) == stoi(thingaling)) {
								hymnDB.at(q).printDetails(counter3++);
								searchVector.push_back(hymnDB.at(q));
								break;
							}
						}break;
					case 5:
						for (int u = 0; u < hymnDB.at(q).getNoOfHymns(); u++) {
							if (hymnDB.at(q).getKey(u) == stoi(thingaling)) {
								hymnDB.at(q).printDetails(counter3++);
								searchVector.push_back(hymnDB.at(q));
								break;
							}
						}break;

					default:
						cout << "That is not a valid option. Please try again.";
						goto START;
					}

				}
				if (testing == 4) {
					while (true) {
						cout << "Enter which result you would like search for additional music: ";
						cin >> counter3;
						try {
							thingaling = searchVector.at(counter3 - 1).getTuneName();
						}
						catch (const out_of_range& oor) {
							cout << "That is not a valid option. Please try again." << endl;
							continue;
						}
						int aldfjkl = 1;
						for (int h = 0; h < pageDB.size(); h++) {
							if (pageDB.at(h).getHymnTitle() == thingaling) {
								pageDB.at(h).printDetails(aldfjkl++);
							}
						}
						break;
					}
				} //end testing == 4
				break; }
			case 5:
				//vector<pageEntry> searchVector 2 etc., do later
				int counter4 = 1;
				int testinglicious = 0;
				string search;
				cout << "Search by what?\nEnter 1 for tune name\n2 for book title \n3 for composer\n4 for key" << endl;
				cin >> testinglicious;
				cin.ignore(1000, '\n');
				cout << "Please enter the search term:" << endl;
				getline(cin, search);
				for (int q = 0; q < pageDB.size(); q++) {
					switch (testinglicious) {
					case 1:
						if (pageDB.at(q).getHymnTitle().find(search) != string::npos) {
							pageDB.at(q).printDetails(counter4++);
							//searchVector.push_back(pageDB.at(q));

						}
						break;
					case 2:
						if (pageDB.at(q).getBookTitle().find(search) != string::npos) {
							pageDB.at(q).printDetails(counter4++);
							//searchVector.push_back(pageDB.at(q));

						}
							break;
					case 3:
						if (pageDB.at(q).getComposer().find(search) != string::npos) {
							pageDB.at(q).printDetails(counter4++);
							//searchVector.push_back(pageDB.at(q));

						}
							break;

					case 4:
						if (pageDB.at(q).getKey() == stoi(search)) {
							pageDB.at(q).printDetails(counter4++);
							//searchVector.push_back(pageDB.at(q));


						}
							break;

					default:
						cout << "That is not a valid option. Please try again.";
						goto START;
					}

				}
			} //end switch
			//S2D_FreeWindow(window);
			

		}//end while(true) loop
	}//end non-developer options
	return 0;
}