//Calcolo stringhe e gradi.cpp, programma per scomporre i numeri

#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <vector>
#include <chrono>
#include <thread>
#include <ppl.h>
using namespace std;
using namespace chrono;

__int64 n = 2147483647;

/*class ResultPrinters {
	public:
		ResultPrinters() {
		}
		void Void(){}
};*/

// Funzione per creare una barra di progresso
void progress_Bar(double ratio, int barWidth) {
	cout << "[[";
	int pos = (int)(barWidth * ratio);
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) cout << "=";
		else if (i == pos) cout << ">";
		else cout << " ";
	}
	int ratio2 = (int)(ratio * 1000.0);
	double ratio3 = (double)ratio2 / 10;
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
int position_in_the_vector(int number, vector <int> vect) {
	for (int a = 0; a < size(vect); a++)
		if (vect[a] == number) return a;
}

// Funzione per trovare tutti i numeri primi fino a n
vector<int> crivelloEratostene() {
	vector<bool> isPrime(n + 1, true);
	vector<int> primes;
	int Barwidth = 80;

	for (int p = 2; pow(p, 2) <= n; p++) {
		if (isPrime[p]) {
			for (int i = pow(p, 2); i <= n; i += p)
				isPrime[i] = false;
		}
		if (n > 200000) {
			float progress = ((float)(pow(p, 2)) / n) + (float) 1/100;
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
	int deg;
} data_t;
typedef struct {
	int factors;
	int exp;
} compost_t;

// Funzione per ordinare un vettore di struct in ordine crescente
vector <data_t> SortData(vector <data_t> vect) {

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

// Funzione per scomporre un numero in fattori primi
vector <compost_t> decompose(int input, vector <int> PrimeNumber) {
	vector <compost_t> output;
	compost_t outelement;
	outelement.factors = 0;
	outelement.exp = 1;
	for (int i = 0; i < 15; i++) output.push_back(outelement);
	int index = 0;
	int d;

	//scomposizione in fattori primi
	for (d = 0; pow(PrimeNumber[d], 2) <= input; d++) {
		if (input != 1) {
			if (input % PrimeNumber[d] == 0) {
				if (output[index].factors == PrimeNumber[d])
					output[index].exp++;
				else output[index].factors = PrimeNumber[d];
				input /= PrimeNumber[d];
				if (input % PrimeNumber[d] != 0) {
					index++;
				}
				d--;
			}
		}
	}
	if (output[index].factors == input)
		output[index].exp++;
	else output[index].factors = input;
	input = 1;
	//

	return output;
}

// Funzione per creare la criptatura di un numero
string Algorithm(int input, vector <int> PrimeNumber) 
{
	//inizializzazione
	vector <compost_t> expfactors = decompose(input, PrimeNumber);
	int PrimeFactors[15];
	int exponents[15];
	int factors;
	bool tag2 = 1;
	for (int e = 0; e < 15; e++) {
		PrimeFactors[e] = expfactors[e].factors;
		exponents[e] = expfactors[e].exp;
		if (tag2 && (PrimeFactors[e] == 0)) {
			factors = e;
			tag2 = 0;
		}
	}
	int index = 0;
	int d;
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
				analyse = 1 + position_in_the_vector(analyse, PrimeNumber);
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
			if ((analyse != 1) && !prime(analyse)) {
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
int Convert(string input) 
{
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

	__int64 user_num;
	string check;
	do {
		bool error = 1;
		bool general_error = 0;
		cout << txt;
		cin >> check;
		if (check.size() > 10) user_num = 0;
		else {
			char digits[] = { '0','1','2','3','4','5','6','7','8','9' };
			for (int ch = 0; ch < check.size(); ch++) {
				for (int chi = 0; chi < 10; chi++) {
					if (check.at(ch) == digits[chi]) {
						error = 0;
					}
				}
				if (error) general_error = 1;
				error = 1;
			}
			if (general_error) user_num = 0;
			else user_num = stoull(check);
		}

	} while (user_num < lw || user_num > bound);

	return user_num;
}

// Funzione per stampare la fattorizzazione di un numero
string fact(int input, vector <int> PrimeNumber) {

	//inizializzazione
	vector <compost_t> expfactors = decompose(input, PrimeNumber);
	int PrimeFactors[15];
	int exponents[15];
	int factors;
	bool tag2 = 1;
	for (int e = 0; e < 15; e++) {
		PrimeFactors[e] = expfactors[e].factors;
		exponents[e] = expfactors[e].exp;
		if (tag2 && (PrimeFactors[e] == 0)) {
			factors = e;
			tag2 = 0;
		}
	}
	int index = 0;
	int d;
	//

	//costruzione dell'output
	string output = "";
	for (int i = 0; i < factors; i++) {
		if (exponents[i] != 1) {
			output = output + to_string(PrimeFactors[i]) + "^" + to_string(exponents[i]) + " * ";
		}
		else output = output + to_string(PrimeFactors[i]) + " * ";
	}
	output.erase(output.size() - 3);
	//

	return output;
}

// Algoritmo fondamentale della codifica
data_t coredegree(int set, vector <int> PrimeNumber) {
	data_t output;
	int counter = 0;
	int input = set;
	do {
		input = Convert(Algorithm(input, PrimeNumber));
		counter++;
		if (input < 4) output.deg = counter + input;

	} while (input != 1);
	input = set;
	output.number = input;
	output.code = Algorithm(input, PrimeNumber);
	return output;
}

// Algoritmo fondamentale della scomposizione
data_t corefactor(int set, vector <int> PrimeNumber) {
	data_t output;
	output.number = set;
	output.code = fact(set, PrimeNumber);
	output.deg = 0;
	return output;
}

// Funzione per ripetere un certo algoritmo
void repeater(vector <int> PrimeNumber, string message, 
	string message2, data_t nucleus(int input, vector <int> PrimeNumber))
{

	string n_ = to_string(n);
	int input;
	data_t result;
	cout << message << "\n\n";
	do {
		string txt = "inserire un numero tra 2 e " + n_ + " (1 = fine input)\n";
		input = get_user_num(txt, 1, n);
		if (input != 1) {
			result = nucleus(input, PrimeNumber);
			cout << message2 << " di " << result.number << " e' <"
				<< result.code << '>';
			if (result.deg != 0) {
				cout << ", il grado e' " << result.deg;
			}
			cout << '\n';
		}
	} while (input != 1);
}

// Funzione per ripetere su una serie un certo algoritmo
void loop(vector <int> PrimeNumber, string message, string messagecout, 
	      data_t nucleus(int set, vector <int> PrimeNumber))
{
	string n_ = to_string(n);
	vector <data_t> data;
	mutex mtx;
	int Barwidth = 60;
	int input;
	int change;
	cout << "debug::\n\n";
	cout << message << '\n';
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
	int datalenght = upper_bound - lower_bound;

	steady_clock::time_point begin = steady_clock::now();
	Concurrency::parallel_for(int(lower_bound + 1), upper_bound + 1, [&](int set) {

		data_t data_element = nucleus(set, PrimeNumber);
		mtx.lock();
		data.push_back(data_element);
		double Progress = (double)size(data) / datalenght;
		progress_Bar(Progress, Barwidth);
		mtx.unlock();

	});
	steady_clock::time_point end = steady_clock::now();

	//output
	data = SortData(data);
	for (int c = 0; c < Barwidth + 11; c++) cout << ' '; cout << '\n';
	for (int x = 0; x < size(data); ++x) {
		cout << messagecout << " di " << data[x].number << " e' <"
			 << data[x].code << '>';
		if (data[x].deg != 0) {
			cout << ", il grado e' " << data[x].deg;
		}
		cout << '\n';
	}
	cout << "\ntempo di calcolo = " << duration_cast<milliseconds>(end - begin).count()
		 << "[ms]" << '\n';
}

// Programma principale
int main()
{	
	string defact_message = "il programma calcola la fattorizzazione di una serie di numeri";
	string deg_message = "il programma calcola il codice e il grado di una serie di numeri";
	string fact_message = "il programma scompone un numero in fattori primi";
	string message = "il programma converte un numero nel corrispondente codice e ne calcola il grado";
	// ResultPrinters print;
	// print.Void();
	
	bool stop = 0;
	bool lock_prime_input = 0;
	vector <int> PrimeNumber;
	do {
		cout << "CALCOLATRICE::\n\n";
		bool skip = 0;
		string text;
		string vel;

		if (!lock_prime_input) {
			n = 2147483647;
			text = "fino a quale numero cercare i numeri primi?\n";
			text.append("un limite piu' alto comporta un tempo di attesa piu' lungo\n");
			n = get_user_num(text, 2, n);
		
			steady_clock::time_point begin = steady_clock::now();
			PrimeNumber = crivelloEratostene();
			steady_clock::time_point end = steady_clock::now();

			cout << "tempo di calcolo numeri primi = "
				 << duration_cast<milliseconds>(end - begin).count() - 1
				 << "[ms]" << "\n\n";
		}
		do {
			cout << "scegli opzioni::\n";
			cout << "inserire una stringa di almeno due caratteri seguendo le seguenti regole\n";
			cout << "primo carattere: \n";
			cout << "'0' = blocca input numeri primi\n";
			cout << "'1' = sblocca input numeri primi\n";
			cout << "'.' = fine programma\n";
			cout << "'c' = codifica e 'f' = scomposizione in fattori primi\n";
			cout << "secondo carattere: \n";
			cout << "'c' = calcolo e 'd' = debug\n";
			cin >> vel;

			if (vel.size() == 1) {
				switch (vel.at(0)) {
				case '0': lock_prime_input = 1;
					cout << "input numeri primi bloccato\n";
					skip = 1;
					break;
				case '1': lock_prime_input = 0;
					cout << "input numeri primi sbloccato\n";
					break;
				case '.': return 0;
					break;
				default: vel += ' ';
					break;
				}
			}
			if (vel.at(0) == '1') {
				do {
					skip = 0;
					cout << "scegli opzioni:: (...)\n";
					cin >> vel;
					if (vel.size() > 1) {
						stop = vel.at(1) != 'c' && vel.at(1) != 'd';
					}
					if (!stop) {
						stop = vel.at(0) != 'c' && vel.at(0) != 'f';
					}
				} while (stop);
			}
			stop = 0;
			if (!skip) switch (vel.at(0)) {
			case 'f': switch (vel.at(1)) {
						case 'c': repeater(PrimeNumber, fact_message
							, "la fattorizzazione", corefactor);
							break;
						case 'd': loop(PrimeNumber, defact_message,
							"la fattorizzazione", corefactor);
							break;
						default: cout << "non corretto\n";
							stop = 1;
							break;
						}
			break;
			case 'c': switch (vel.at(1)) {
						case 'c': repeater(PrimeNumber, message
							, "il codice", coredegree);
							break;
						case 'd': loop(PrimeNumber, deg_message,
							"il codice", coredegree);
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

	} while (0 == 0);
}
// FINE...