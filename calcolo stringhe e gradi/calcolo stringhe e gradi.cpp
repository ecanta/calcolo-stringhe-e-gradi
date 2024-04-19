//Calcolo stringhe e gradi.cpp, programma per scomporre i numeri

//#define CODE_PARALLEL_FOR
#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <vector>
#include <chrono>
#include <thread>
#include <ppl.h>
using namespace std;
int n = 2147483647;

// Funzione per creare una barra di progresso
void progress_Bar(float ratio, int barWidth) {
	cout << "[[";
	int pos = (int)(barWidth * ratio);
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) cout << "=";
		else if (i == pos) cout << ">";
		else cout << " ";
	}
	int ratio2 = (int)(ratio * 1000.0);
	float ratio3 = (float)ratio2 / 10;
	cout << "]] " << ratio3 << "%\r";
	cout.flush();
}

// Funzione per controllare se un numero è primo
bool prime(int variable) {
	bool tag = 1;
	if (variable == 1) tag = 0;
	for (int a = 2; a < variable; a++)
		if (variable % a == 0) tag = 0;
	return tag;
}

// Funzione per trovare la posizione di un elemento in un vettore
int position_in_vector(int number, vector <int> vect) {
	for (int a = 0; a < size(vect); a++)
		if (vect[a] == number) return a;
}

// Funzione per trovare tutti i numeri primi fino a n
vector<int> crivelloEratostene() {
	vector<bool> isPrime(n + 1, true);
	vector<int> primes;
	int Barwidth = 80;

	for (int p = 2; p * p <= n; p++) {
		if (isPrime[p]) {
			for (int i = pow(p, 2); i <= n; i += p)
				isPrime[i] = false;
		}
		if (n > 150000) {
			float progress = ((float)(p * p) / n) + (float) 1/100;
			progress_Bar(progress, Barwidth);
		}
	}
	for (int c = 0; c < Barwidth + 11; c++) cout << ' '; cout << '\n';
	for (int p = 2; p <= n; p++)
		if (isPrime[p]) primes.push_back(p);

	return primes;
}

typedef struct {
	int number;
	string code;
} data_t;

typedef struct {
	int number;
	string code;
	int deg;
} codedata_t;

// Funzione per ordinare un vettore di data_t in ordine crescente
vector <data_t> SortData(vector <data_t> vect){

	for (int i = 0; i < size(vect); i++) {
		for (int j = 0; j < size(vect); j++) {
			if (vect[i].number < vect[j].number) {
				data_t change;
				change = vect[i];
				vect[i] = vect[j];
				vect[j] = change;
			}
		}
	}

	return vect;
}

// Funzione per ordinare un vettore di codedata_t in ordine crescente
vector <codedata_t> SortCData(vector <codedata_t> vect) {

	for (int i = 0; i < size(vect); i++) {
		for (int j = 0; j < size(vect); j++) {
			if (vect[i].number < vect[j].number) {
				codedata_t change;
				change = vect[i];
				vect[i] = vect[j];
				vect[j] = change;
			}
		}
	}

	return vect;
}

// Funzione per creare la criptatura di un numero
string Algorithm(int input, vector <int> PrimeNumber) {

	int PrimeFactors[15];
	for (int e = 0; e < 15; e++)
		PrimeFactors[e] = 0;
	int exponents[15];
	for (int f = 0; f < 15; f++)
		exponents[f] = 1;
	int index = 0;
	int d;

	//scomposizione in fattori primi
	for (d = 0; pow(PrimeNumber[d], 2) <= input; d++) {
		if (input != 1) {
			if (input % PrimeNumber[d] == 0) {
				if (PrimeFactors[index] == PrimeNumber[d])
					exponents[index]++;
				else PrimeFactors[index] = PrimeNumber[d];
				input /= PrimeNumber[d];
				if (input % PrimeNumber[d] != 0) {
					index++;
				}
				d--;
			}
		}
	}
	if (PrimeFactors[index] == input)
		exponents[index]++;
	else PrimeFactors[index] = input;
	input = 1;
	//

	//conta dei fattori primi
	int factors;
	bool tag2 = 1;
	for (int count = 0; count < 15; count++) {
		if (tag2) {
			if (PrimeFactors[count] == 0) {
				factors = count;
				tag2 = 0;
			}
		}
	}
	//

	//calcolo dei monomi
	string thenumber;
	string iso_i;
	string iso_g;
	string iso_h;
	int iso_hh;
	int analyse;
	int sizenumber;
	int size0;
	bool repeat;
	int presence;

	int bound;
	int bound_while;
	string monomials[15];
	for (int WhatFactor = 0; WhatFactor < factors; WhatFactor++) {
		repeat = 0;
		presence = 0;

		iso_i = to_string(exponents[WhatFactor]);
		analyse = PrimeFactors[WhatFactor];
		string the_n1 = "(";
		string the_n2 = ")";
		if ((exponents[WhatFactor] != 1) && (exponents[WhatFactor] < 11)) {
			the_n2.append(iso_i);
			presence = 1;
		}
		else if (exponents[WhatFactor] > 10) {
			the_n2.append(".");
			the_n2.append(iso_i);
			presence = 2;
		}
		string iso_analyse = to_string(analyse);
		thenumber = the_n1 + iso_analyse + the_n2;

		do {
			while (prime(analyse)) {
				analyse = 1 + position_in_vector(analyse, PrimeNumber);
				iso_analyse = to_string(analyse);
				bound_while = thenumber.find(')');
				thenumber.erase(0, bound_while);
				thenumber = the_n1 + iso_analyse + thenumber;
				sizenumber = thenumber.size();
				size0 = sizenumber - 1;

				if (presence == 1) {
					iso_g = string(1, thenumber.at(size0));
					thenumber.erase(size0);
					sizenumber--;
					size0--;
				}
				else if (presence == 2) {
					iso_g = "." + string(1, thenumber.at(size0 - 1)) + string(1, thenumber.at(size0));
					thenumber.erase(size0 - 2);
					sizenumber--;
					size0--;
				}
				if (repeat) {
					iso_h = string(1, thenumber.at(size0));
					thenumber.erase(size0);
					iso_hh = stoi(iso_h);
					iso_hh++;
					iso_h = to_string(iso_hh);
					if (iso_hh > 9) {
						iso_h = "." + iso_h;
					}
					thenumber.append(iso_h);
				}
				else {
					thenumber.append("1");
				}
				if (presence > 0) {
					thenumber.append(iso_g);
				}
				repeat = 1;
			}
			if ((analyse != 1) && (prime(analyse) == 0)) {
				iso_analyse = Algorithm(analyse, PrimeNumber);
				bound = thenumber.find(')');
				thenumber.erase(0, bound);
				thenumber = the_n1 + iso_analyse + thenumber;
				analyse = 1;
			}

		} while (analyse != 1);
		monomials[WhatFactor] = thenumber;
	}
	//

	//unione dei monomi
	thenumber = "";
	for (int s = 0; s < factors; s++) {
		thenumber = thenumber + "+" + monomials[s];
	}
	thenumber.erase(0, 1);
	//

	//rimozione basi
	int position[15];
	int j = 0;
	for (int i1 = 0; i1 < (thenumber.size() - 2); i1++) {
		if ((thenumber.at(i1) == '(') && (thenumber.at(i1 + 1) == '1') && (thenumber.at(i1 + 2) == ')')) {
			position[j] = i1;
			j++;
		}
	}
	for (int i2 = j - 1; i2 >= 0; i2--)
		thenumber.erase(position[i2], 3);
	//

	//rimozione parentesi in più
	int j2 = 0;
	sizenumber = thenumber.size();
	if (sizenumber > 4) {
		for (int i3 = 0; i3 < (thenumber.size() - 3); i3++) {
			if ((thenumber.at(i3) == '(') && (thenumber.at(i3 + 3) == ')')) {
				position[j2] = i3;
				j2++;
			}
		}
		for (int i3 = j2 - 1; i3 >= 0; i3--) {
			thenumber.erase(position[i3] + 3, 1);
			thenumber.erase(position[i3], 1);
		}
	}
	//

	return thenumber;
}

// Funzione per sommare la criptatura
int Convert(string input) {

	int output = 0;

	//rimozione punti
	string monomials[15];
	int values[15];
	for (int i = 0; i < input.size(); i++) {
		if (input.at(i) == '.') {
			input.erase(i, 1);
		}
	}
	//

	//scomposizione dell'input
	string backup = input;
	string temp;
	int noparenthesis = 0;
	int nop = 0;
	int find = 0;
	int index = 0;
	for (int j = 0; j < backup.size(); j++) {
		if (backup.at(j) == '(') noparenthesis++;
		if ((noparenthesis == 0) && (backup.at(j) == '+')) {
			temp = input;
			for (int finder = 0; finder < temp.size(); finder++) {
				if (find == 0) {
					if (temp.at(finder) == '(') nop++;
					if ((nop == 0) && (temp.at(finder) == '+')) {
						find = finder;
					}
					if (temp.at(finder) == ')') nop--;
				}
			}
			temp.erase(find);
			monomials[index] = temp;
			index++;
			input.erase(0, find + 1);
			find = 0;
		}
		if (backup.at(j) == ')') noparenthesis--;
	}
	monomials[index] = input;
	//

	//elaborazione monomi
	int location;
	bool presence = 1;
	for (int A = 0; A <= index; A++) {
		if (monomials[A].at(0) == '(') {
			for (int B = monomials[A].size() - 1; B >= 0; B--) {

				if ((presence) && (monomials[A].at(B) == ')')) {
					presence = 0;
					location = B;
				}
			}
			temp = monomials[A];
			temp.erase(location);
			temp.erase(0, 1);
			monomials[A].erase(0, location + 1);
			values[A] = Convert(temp) * (stoi(monomials[A]));
		}
		else {
			values[A] = stoi(monomials[A]);
		}
		presence = 1;
	}
	//

	//somma monomi
	for (int end = 0; end <= index; end++) {
		output += values[end];
	}
	//

	return output;
}

// Funzione per ottenere l'input controllato
int get_user_num(string txt, int lw, int bound) {

	int user_num;
	string check;
	do {
		bool error = 1;
		bool general_error = 0;
		cout << txt;
		cin >> check;

		char digits[] = { '0','1','2','3','4','5','6','7','8','9' };
		for (int ch = 0; ch < check.size(); ch++) {
			for (int chi = 0; chi < 10; chi++) {
				if (check.at(ch) == digits[chi]) error = 0;
			}
			if (error) general_error = 1;
			error = 1;
		}
		if (general_error) user_num = 0;
		else user_num = stoi(check);

	} while (user_num < lw || user_num > bound);

	return user_num;
}

// Funzione per calcolare il grado di un numero
void degree(vector <int> PrimeNumber) {

	string n_ = to_string(n);
	int input;
	cout << "il programma converte un numero nel corrispondente codice e ne calcola il grado\n\n";

	do {
		string txt = "inserire un numero tra 2 e " + n_ + " (1 = fine input)\n";
		input = get_user_num(txt, 1, n);

		//calcolo
		if (input != 1) {
			string ALGO = Algorithm(input, PrimeNumber);
			cout << "il codice di " << input << " e' " << '<' << ALGO << '>' << '\n';

			int counter = 1;
			do {

				input = Convert(Algorithm(input, PrimeNumber));
				counter++;
				if (input == 1) cout << "il grado e' " << counter << '\n';

			} while (input != 1);
			input = 0;
		}
	} while (input != 1);
}

// Funzione per calcolare il grado di una serie di numeri
void loop_degree(vector <int> PrimeNumber) {

	string n_ = to_string(n);
	vector<codedata_t> codedata;
	mutex mtx;
	int Barwidth = 60;

	int input;
	int change;
	cout << "debug::\n\n";
	cout << "il programma calcola il codice e il grado di una serie di numeri\n";
	cout << "gli estremi dell'intervallo devono essere compresi tra 1 e " << n_ << "\n\n";

	string txt = "inserisci il valore di inizio della ricerca\n";
	int lower_bound = get_user_num(txt, 1, n);

	txt = "inserisci il valore finale della ricerca\n";
	int upper_bound = get_user_num(txt, 1, n);

	if (upper_bound < lower_bound) {
		change = upper_bound;
		upper_bound = lower_bound;
		lower_bound = change;
	}
	int codedatalenght = upper_bound - lower_bound;

	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
#ifdef CODE_PARALLEL_FOR
	Concurrency::parallel_for(int(lower_bound + 1), upper_bound + 1, [&](int set) {
#else
	for (int set = lower_bound + 1; set < upper_bound + 1; set++) {
#endif
		input = set;

		//calcolo
		codedata_t codedata_element;
		int counter = 0;
		do {
			input = Convert(Algorithm(input, PrimeNumber));
			counter++;
			if (input < 4) codedata_element.deg = counter + input;

		} while (input != 1);
		input = set;

		codedata_element.number = input;
		codedata_element.code = Algorithm(input, PrimeNumber);
		mtx.lock();
		codedata.push_back(codedata_element);
		float Progress = (float)size(codedata) / codedatalenght;
		progress_Bar(Progress, Barwidth);
		mtx.unlock();

#ifdef CODE_PARALLEL_FOR
		});
#else
}
#endif
	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	//output
	SortCData(codedata);
	for (int c = 0; c < Barwidth + 11; c++) cout << ' '; cout << '\n';
	for (int x = 0; x < size(codedata); ++x) {
		cout << "il codice di " << codedata[x].number << " e' " 
			 << codedata[x].code << ", il grado e' " << codedata[x].deg << '\n';
	}
	cout << "\ntempo di calcolo = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() 
		 << "[ms]" << '\n';
}

// Funzione di scomposizione
string fact(int input, vector <int> PrimeNumber) {
	int PrimeFactors[15];
	for (int e = 0; e < 15; e++)
		PrimeFactors[e] = 0;
	int exponents[15];
	for (int f = 0; f < 15; f++)
		exponents[f] = 1;
	int index = 0;
	int d;

	//scomposizione in fattori primi
	for (d = 0; pow(PrimeNumber[d], 2) <= input; d++) {
		if (input != 1) {
			if (input % PrimeNumber[d] == 0) {
				if (PrimeFactors[index] == PrimeNumber[d])
					exponents[index]++;
				else PrimeFactors[index] = PrimeNumber[d];
				input /= PrimeNumber[d];
				if (input % PrimeNumber[d] != 0) {
					index++;
				}
				d--;
			}
		}
	}
	if (PrimeFactors[index] == input)
		exponents[index]++;
	else PrimeFactors[index] = input;
	input = 1;
	//

	//conta dei fattori primi
	int factors;
	bool tag2 = 1;
	for (int count = 0; count < 15; count++) {
		if (tag2) {
			if (PrimeFactors[count] == 0) {
				factors = count;
				tag2 = 0;
			}
		}
	}
	//

	//costruzione dell'output
	string output = "";
	for (int i = 0; i < factors; i++) {
		if (exponents[i] != 1) {
			output = output + to_string(PrimeFactors[i]) + "^" + to_string(exponents[i]) + " * ";
		}
		else output = output + to_string(PrimeFactors[i]) + " * ";
	}
	output.erase(output.size() - 2);
	//

	return output;
}

// Funzione per scomporre un numero in fattori primi
void factor(vector <int> PrimeNumber) {

	string n_ = to_string(n);

	int input = 0;
	cout << "il programma scompone un numero in fattori primi\n\n";

	do {
		string txt = "inserire un numero tra 2 e " + n_ + " (1 = fine input)\n";
		input = get_user_num(txt, 1, n);

		//calcolo
		if (input != 1) {
			string ALGO = fact(input, PrimeNumber);
			cout << input << " = " << ALGO << '\n';
		}

	} while (input != 1);
}

// Funzione per scomporre una serie di numeri in fattori primi
void loop_factor(vector <int> PrimeNumber) {
	string n_ = to_string(n);
	vector <data_t> data;
	mutex mtx;
	int Barwidth = 60;

	int input;
	int change;
	cout << "debug::\n\n";
	cout << "il programma calcola la fattorizzazione di una serie di numeri\n";
	cout << "gli estremi dell'intervallo devono essere compresi tra 1 e " << n_ << "\n\n";

	string txt = "inserisci il valore iniziale della ricerca\n";
	int lower_bound = get_user_num(txt, 1, n);

	txt = "inserisci il valore finale della ricerca\n";
	int upper_bound = get_user_num(txt, 1, n);

	if (upper_bound < lower_bound) {
		change = upper_bound;
		upper_bound = lower_bound;
		lower_bound = change;
	}
	int datalenght = upper_bound - lower_bound;

	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	Concurrency::parallel_for(int(lower_bound + 1), upper_bound + 1, [&](int set) {
		
		//calcolo
		input = set;
		data_t data_element;
		data_element.number = input;
		data_element.code = fact(input, PrimeNumber);
		mtx.lock();
		data.push_back(data_element);
		float progress = (float)size(data) / datalenght;
		progress_Bar(progress, Barwidth);
		mtx.unlock();
		
		});

	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	//output
	data = SortData(data);
	for (int c = 0; c < Barwidth + 11; c++) cout << ' '; cout << '\n';
	for (int x = 0; x < size(data); ++x) {
		cout << data[x].number << " = " << data[x].code << '\n';
	}
	cout << "\ntempo di calcolo = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count()
		 << "[ms]" << '\n';
}

// Programma principale
int main()
{
	cout << "CALCOLATRICE::\n\n";
	bool stop = 0;
	string text;
	string vel;

	text = "fino a quale numero cercare i numeri primi?\n";
	text.append("un limite piu' alto comporta un tempo di attesa piu' lungo\n");
	n = get_user_num(text, 2, n);

	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	vector <int> PrimeNumber = crivelloEratostene();
	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	cout << "tempo di calcolo numeri primi = " 
		 << chrono::duration_cast<chrono::milliseconds>(end - begin).count()
		 << "[ms]" << "\n\n";

	do {
		cout << "inserire una stringa di due caratteri seguendo le seguenti regole\n";
		cout << "primo carattere: \n";
		cout << "'c' = codifica e 'f' = scomposizione in fattori primi\n";
		cout << "secondo carattere: \n";
		cout << "'c' = calcolo e 'd' = debug\n";
		cin >> vel;
		if (vel.size() == 1) vel += ' ';

		switch (vel.at(0)) {
		case 'f': switch (vel.at(1)) {
					case 'c': factor(PrimeNumber);
						break;
					case 'd': loop_factor(PrimeNumber);
						break;
					default: cout << "non corretto\n";
						stop = 1;
						break;
					}
		break;
		case 'c': switch (vel.at(1)) {
					case 'c': degree(PrimeNumber);
						break;
					case 'd': loop_degree(PrimeNumber);
						break;
					default: cout << "non corretto\n";
						stop = 1;
						break;
					}
		break;
		default: cout << "non corretto\n";
			stop = 1;
			break;
		}
	} while (stop);
	return 0;
}