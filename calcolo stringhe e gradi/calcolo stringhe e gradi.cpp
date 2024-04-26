// program_START
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <ppl.h>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
using namespace Concurrency;
using namespace chrono;

long long Global_N = pow(10, 10);
vector <bool> IsPrime;
vector <int> PrimeNumber;
mutex mtx;

namespace FUNCTIONS {

	bool prime(int variable) {
		bool tag = 1;
		if (variable == 1) return 0;
		else if (variable < size(IsPrime)) {
			return IsPrime[variable];
		}
		else {
			if (variable == 1) tag = 0;
			for (int a = 2; a < variable; a++)
				if (variable % a == 0) tag = 0;
		}
		return tag;
	}

	void progress_Bar(double ratio, double barWidth) {
		cout << "[[";
		int pos = (int)(barWidth * ratio);
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) cout << "=";
			else (i == pos) ? cout << ">" : cout << " ";
		}
		ratio *= 100.0;
		stringstream stream;
		stream << fixed << setprecision(1) << ratio;
		string s = stream.str();

		cout << "]] " << s << "%\r";
	}

	vector <bool> Sieve(long long N, bool USE_pro_bar) {
		vector<bool> isPrime(N + 1, 1);
		vector<int> primes;
		double Barwidth = 80;

		for (int p = 2; pow(p, 2) <= N; p++) {
			if (isPrime[p]) {
				for (int i = pow(p, 2); i <= N; i += p)
					isPrime[i] = 0;
			}
			if (N > 200000 && USE_pro_bar) {
				double progress = ((double)(pow(p, 2)) / N);
				progress_Bar(progress, Barwidth);
			}
		}
		if (USE_pro_bar) {
			for (int c = 0; c < Barwidth + 11; c++) 
				cout << ' '; 
			cout << '\n';
		}		
		return isPrime;
	}

	vector <int> Sieve_of_Erastothens(vector <bool> isPrime, long long N) {
		vector <int> primes;
		for (int p = 2; p <= N; p++)
			if (isPrime[p]) primes.push_back(p);
		return primes;
	}

	typedef struct {
		int number;
		string code;
		int deg;
		string expression;
	} data_t;
	typedef struct {
		int factors;
		int exp;
	} compost_t;

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

	vector <compost_t> decompose(int input) {
		
		if (input > PrimeNumber[size(PrimeNumber) - 1]) {
			vector <int> PrimeN = Sieve_of_Erastothens(Sieve(input, 0), input);
			for (int a = size(PrimeNumber); a < size(PrimeN); a++) {
				mtx.lock();
				PrimeNumber.push_back(PrimeN[a]);
				mtx.unlock();
			}
		}
		vector <compost_t> output;
		compost_t outelement;
		outelement.factors = 0;
		outelement.exp = 1;
		for (int i = 0; i < 15; i++) output.push_back(outelement);
		int index = 0;
		int d;

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

		return output;
	}

	string Algorithm(int input)
	{
		vector <compost_t> expfactors = decompose(input);
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

		string thenumber, iso_i, iso_g, iso_h;
		int iso_hh, analyse, sizenumber;
		bool repeat;

		int presence, bound, bound_while;
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
					int position = -1;
					int a = 1;
					do {
						if (PrimeNumber[a - 1] == analyse)
							position = a;
						a++;
					} while (position < 0);
					analyse = position;
					iso_analyse = to_string(analyse);
					bound_while = thenumber.find(')');
					thenumber.erase(0, bound_while);
					thenumber = the_n1 + iso_analyse + thenumber;
					sizenumber = thenumber.size();

					if (presence == 1) {
						iso_g = string(1, thenumber.at(sizenumber - 1));
						thenumber.erase(sizenumber - 1);
						sizenumber--;
					}
					else if (presence == 2) {
						iso_g = "." + string(1, thenumber.at(sizenumber - 2)) 
									+ string(1, thenumber.at(sizenumber - 1));
						thenumber.erase(sizenumber - 3);
						sizenumber--;
					}
					if (repeat) {
						iso_h = string(1, thenumber.at(sizenumber - 1));
						thenumber.erase(sizenumber - 1);
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
					iso_analyse = Algorithm(analyse);
					bound = thenumber.find(')');
					thenumber.erase(0, bound);
					thenumber = the_n1 + iso_analyse + thenumber;
					analyse = 1;
				}

			} while (analyse != 1);
			monomials[WhatFactor] = thenumber;
		}

		thenumber = "";
		for (int s = 0; s < factors; s++) {
			thenumber = thenumber + "+" + monomials[s];
		}
		thenumber.erase(0, 1);

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

		return thenumber;
	}

	vector <string> fractioner(string polynomial) {
		vector <string> monomials;
		string backup = polynomial;
		string temp;
		int noparenthesis = 0;
		int nop = 0;
		int find = 0;
		for (int j = 0; j < backup.size(); j++) {
			if (backup.at(j) == '(') noparenthesis++;
			if ((noparenthesis == 0) && (backup.at(j) == '+')) {
				temp = polynomial;
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
				monomials.push_back(temp);
				polynomial.erase(0, find + 1);
				find = 0;
			}
			if (backup.at(j) == ')') noparenthesis--;
		}
		monomials.push_back(polynomial);
		return monomials;
	}

	int Convert(string input)
	{
		int output = 0;
		int values[15];
		for (int i = 0; i < input.size(); i++) {
			if (input.at(i) == '.') {
				input.erase(i, 1);
			}
		}
		vector <string> monomials = fractioner(input);

		int location;
		bool presence = 1;
		for (int A = 0; A < size(monomials); A++) {
			if (monomials[A].at(0) == '(') {
				for (int B = monomials[A].size() - 1; B >= 0; B--) {

					if ((presence) && (monomials[A].at(B) == ')')) {
						presence = 0;
						location = B;
					}
				}
				string temp = monomials[A];
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
		for (int end = 0; end < size(monomials); end++) output += values[end];
		return output;
	}

	long long get_user_num(string txt, int lw, long long bound) {

		long long user_num;
		string check;
		do {
			bool error = 1;
			bool general_error = 0;
			cout << txt;
			getline(cin, check);
			if (check.empty()) user_num = lw - 1;
			else if (check.size() > 10) user_num = lw - 1;
			else {
				string digits = "0123456789";
				for (int ch = 0; ch < check.size(); ch++) {
					for (int chi = 0; chi < digits.size(); chi++) {
						if (check.at(ch) == digits.at(chi))
							error = 0;
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

	string fact(int input) {

		vector <compost_t> expfactors = decompose(input);
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

		string output = "";
		for (int i = 0; i < factors; i++) {
			if (exponents[i] != 1) {
				output = output + to_string(PrimeFactors[i]) + "^" + to_string(exponents[i]) + " * ";
			}
			else output = output + to_string(PrimeFactors[i]) + " * ";
		}
		output.erase(output.size() - 3);

		return output;
	}

	data_t coredegree(int set) {
		data_t output;
		int counter = 0;
		int input = set;
		do {
			input = Convert(Algorithm(input));
			counter++;
			if (input < 4) output.deg = counter + input;

		} while (input != 1);
		input = set;
		output.number = input;
		output.code = Algorithm(input);
		output.expression = "";
		return output;
	}

	data_t corefactor(int set) {
		data_t output;
		output.number = set;
		output.code = "";
		output.deg = 0;
		output.expression = fact(set);
		return output;
	}

	data_t NucleusAll(int set) {
		data_t A = coredegree(set);
		data_t B = corefactor(set);
		data_t output;
		output.number = set;
		output.code = A.code;
		output.deg = A.deg;
		output.expression = B.expression;
		return output;
	}

	string Grammarly(string ToEvaluate) {
		vector <string> mono;
		string charsAllowed = "0123456789()+";
		bool local_error = 1, TAG = 1, stable = 0;
		int start = -1, end = -1, noparenthesis = 0;
		for (int find = 0; find < ToEvaluate.size(); find++) {
			if (ToEvaluate.at(find) == '<') start = find + 1;
			else if (ToEvaluate.at(find) == '>') end = find;
		}
		if (start == -1 || end == -1) return "NoBoundary";
		if (end < start) return "BoundaryInversion";
		ToEvaluate.erase(end);
		ToEvaluate.erase(0, start);
		for (int ch = 0; ch < ToEvaluate.size(); ch++) {
			if (ToEvaluate.at(ch) == '(') {
				noparenthesis++;
				stable++;
			}
			if (ToEvaluate.at(ch) == ')') noparenthesis--;
		}
		if (noparenthesis != 0) return "UnbalancedBrackets";
		for (int space = ToEvaluate.size() - 1; space >= 0; space--) {
			if (ToEvaluate.at(space) == ' ')
				ToEvaluate.erase(space, 1);
		}
		if (ToEvaluate.empty()) return "EmptyInput";
		for (int chi = 0; chi < ToEvaluate.size(); chi++) {
			for (int ch_i = 0; ch_i < charsAllowed.size(); ch_i++) {
				if (ToEvaluate.at(chi) == charsAllowed.at(ch_i))
					local_error = 0;
			}
			if (local_error) return "UnallowedCharacters";
			local_error = 1;
		}
		if (ToEvaluate.at(0) == '+') return "'+'AtStart";
		if (ToEvaluate.at(0) == ')') return "InvertedBrackets";
		if (ToEvaluate.at(ToEvaluate.size() - 1) == '+')
			return "'+'AtEnd";
		for (int std = 0; std < ToEvaluate.size() - 1; std++) {
			if (ToEvaluate.at(std) == '+' && ToEvaluate.at(std + 1) == '+')
				return "Double'+'";
		}
		mono = fractioner(ToEvaluate);
		for (int monomial = 0; monomial < size(mono); monomial++) {
			int stackfinder = -1, stickfinder = -1, finder;
			bool stop = 0;
			int res = 0;
			string stack = mono[monomial];
			for (int second = 1; second < size(mono); second++) {
				if (monomial != second) {
					if (mono[monomial] == mono[second]) return "EqualMonomials";
					string stick = mono[second];
					int size_st;
					if (stack.size() < stick.size()) size_st = stack.size();
					else size_st = stick.size();
					if (stack.at(0) == '(' || stick.at(0) == ')') {
						TAG = 1;
						for (int j = stack.size() - 1; j > 0; j--) {
							if (TAG && stack.at(j) == ')') {
								stackfinder = j - 1;
								TAG = 0;
							}
						}
						TAG = 1;
						for (int k = stick.size() - 1; k > 0; k--) {
							if (TAG && stick.at(k) == ')') {
								stickfinder = k - 1;
								TAG = 0;
							}
						}
						if (stackfinder * stickfinder < 0) {
							if (stackfinder > 0) finder = stackfinder;
							else finder = stickfinder;
						}
						else if (stickfinder == stackfinder) {
							finder = stackfinder;
							for (int l = 0; l <= finder + 1; l++) {
								if (l < size_st) {
									if (stick.at(l) != stack.at(l))
										stop = 1;
								}
							}
							for (int l = finder + 2; l < size_st; l++) {
								if (!stop && stick.at(l) == stack.at(l)) {
									res++;
									if (stick.at(l) != stack.at(l))
										stop = 1;
								}
								else stop = 1;
							}
						}
					}
					else for (int m = 0; m < size_st; m++) {
						if (!stop && stick.at(m) == stack.at(m)) {
							res++;
							if (stick.at(m) != stack.at(m))
								stop = 1;
						}
						else stop = 1;
					}
					if (res % 2 == 1) return "SimiliarMonomials";
				}
			}
			TAG = 1;
			for (int j = stack.size() - 1; j > 0; j--) {
				if (TAG && stack.at(j) == ')') {
					finder = j - 1;
					TAG = 0;
				}
			}
			if (stack.at(stack.size() - 1) == ')')
				return "MissingObject";
			if (stack.at(stack.size() - 1) == '(')
				return "InvertedBrackets";
			if (stack.at(0) == '(') {
				local_error = 1;
				for (int checkplus = 1; checkplus < finder; checkplus++) {
					if (stack.at(checkplus) == '+') local_error = 0;
				}
				if (local_error) return "UselessBrackets";
				stack.erase(0, 1);
				stack.erase(finder);
				string message = Grammarly("<" + stack + ">"); 
				if (!message.empty()) return message;
			}
			else if (mono[monomial].at(0) == ')') return "InvertedBrackets";
			else for (int check = 1; check < mono[monomial].size(); check++) {
				if (mono[monomial].at(check) == '(') return "MissingObject";
				if (mono[monomial].at(check) == ')') return "InvertedObject";
			}
		}
		return "";
	}

	long long Simplifier(long long root, string M) {
		bool WhichWay = 1;
		bool XOutOfRange = 0;
		int sizeP = size(PrimeNumber);
		if (!XOutOfRange) for (int iter = 0; iter < M.size(); iter++) {
			WhichWay = !WhichWay;
			if (WhichWay) root = pow(root, M.at(iter) - '0');
			else {
				int nums = M.at(iter) - '0';
				do {
					if (root < sizeP) {
						root = PrimeNumber[root - 1];
						nums--;
					}
					else XOutOfRange = 1;
				} while (XOutOfRange != 1 && nums != 0);
			}
		}
		if (XOutOfRange) return -1;
		return root;
	}

	long long Converter(string ToEvaluate) {
		long long integer = 1;
		string backup, back;
		vector <string> mono = fractioner(ToEvaluate);
		int sizeP = size(PrimeNumber);
		int finder;
		bool TAG = 1;
		for (int monomial = 0; monomial < size(mono); monomial++) {
			string M = mono[monomial];
			long long root;
			bool WhichWay = 0;
			if (M.at(0) != '(') root = Simplifier(1, M);
			else {
				TAG = 1;
				for (int i = M.size() - 1; i > 0; i--) {
					if (TAG && M.at(i) == ')') {
						finder = i + 1;
						TAG = 0;
					}
				}
				back = M;
				backup = M;
				backup.erase(0, finder);
				back.erase(finder - 1);
				back.erase(0, 1);
				root = Converter(back);
				root = Simplifier(root, backup);
			}
			if (root == -1) return -1;
			else integer *= root;
		}
		return integer;
	}

	void CodeToNumber() {
		string ToEvaluate, message;
		vector <string> mono;
		long long NUMBER;
		cout << "il programma traduce una stringa di codice\n";
		cout << "il codice deve essere compreso tra <>\n";
		cout << "unici caratteri non numerici ammessi: '(', ')', '+' \n\n";
		do {
			do {
				cout << "inserire una stringa (0 = fine input)\n";
				getline(cin, ToEvaluate);
				message = Grammarly(ToEvaluate);
				if (!message.empty())
					cout << "ERROR-404: " << message << '\n';
			} while (!message.empty());
			int start = 0;
			int end = 0;
			for (int find = 0; find < ToEvaluate.size(); find++) {
				if (ToEvaluate.at(find) == '<') start = find + 1;
				else if (ToEvaluate.at(find) == '>') end = find;
			}
			ToEvaluate.erase(end);
			ToEvaluate.erase(0, start);
			for (int space = ToEvaluate.size() - 1; space >= 0; space--) {
				if (ToEvaluate.at(space) == ' ')
					ToEvaluate.erase(space, 1);
			}
			if (ToEvaluate != "0") {
				NUMBER = Converter(ToEvaluate);
				if (NUMBER == -1) cout << "ERROR-413: XOutOfRange\n";
				else cout << "il numero corrispondente e' " << NUMBER << '\n';
			}
		} while (ToEvaluate != "0");
	} 
	
	void printf(data_t structure) {
		cout << "numero " << structure.number << ":\n";
		if (!structure.code.empty()) {
			cout << "il codice e' <" << structure.code << ">\n";
		}
		if (structure.deg != 0) {
			cout << "il grado e' " << structure.deg << '\n';
		}
		if (!structure.expression.empty()) {
			if (IsPrime[structure.number]) cout << "il numero e' primo\n";
			else {
				cout << "la fattorizzazione e' " << structure.expression << '\n';
			}
		}
	}

	void repeater(string message, data_t nucleus(int input))
	{
		string n_ = to_string(Global_N);
		int input;
		data_t result;
		cout << message << "\n\n";
		do {
			string txt = "inserire un numero tra 2 e " + n_ + " (1 = fine input)\n";
			input = get_user_num(txt, 1, Global_N);
			if (input != 1) {
				result = nucleus(input);
				printf(result);
			}
		} while (input != 1);
	}

	void loop(string message, data_t nucleus(int set))
	{
		string n_ = to_string(Global_N);
		vector <data_t> data;
		vector <thread> threads;
		
		double Barwidth = 60;
		int input, change;
		cout << "debug::\n\n";
		cout << message << '\n';
		cout << "gli estremi dell'intervallo devono essere compresi tra 1 e " << n_ << "\n\n";

		string txt = "inserisci il valore di inizio della ricerca\n";
		int lower_bound = get_user_num(txt, 1, Global_N) + 1;

		txt = "inserisci il valore finale della ricerca\n";
		int upper_bound = get_user_num(txt, 1, Global_N) + 1;

		if (upper_bound < lower_bound) {
			change = upper_bound;
			upper_bound = lower_bound;
			lower_bound = change;
		}
		int datalenght = upper_bound - lower_bound;

		string choice;
		cout << "vuoi utilizzare la ricerca veloce (non stampa direttamente i numeri)\n";
		cout << "immetti s = si oppure n = no  ";
		getline(cin, choice);
		cout << '\n';

		if (choice == "s") {
			int iter = 0;
			atomic <double> Progress = 0;
			steady_clock::time_point begin = steady_clock::now();
			parallel_for(int(lower_bound), upper_bound, [&](int set) {

				data_t data_element = nucleus(set);
				mtx.lock();
				data.push_back(data_element);
				if (iter % 100 == 0) {
					double Progress = (double)size(data) / datalenght;
					progress_Bar(Progress, Barwidth);
				}
				iter++;
				mtx.unlock();

			});
			steady_clock::time_point end = steady_clock::now();
			cout << "\ntempo di calcolo = " << duration_cast <milliseconds> (end - begin).count()
				 << "[ms]" << '\n';

			data = SortData(data);
			for (int c = 0; c < Barwidth + 11; c++) cout << ' '; cout << '\n';
			for (int x = 0; x < size(data); ++x) printf(data[x]);
		}
		else {
			steady_clock::time_point begin = steady_clock::now();
			for (int set = lower_bound; set < upper_bound; set++) {
				data_t data_element = nucleus(set);
				printf(data_element);
			}
			steady_clock::time_point end = steady_clock::now();
			cout << "\ntempo di calcolo = " << duration_cast<milliseconds>(end - begin).count()
				 << "[ms]" << '\n';
		}
	}

	enum switchcase { cc, cf, ccf, dc, df, dcf, ctn, rnd, r };
	static unordered_map<string, switchcase> stringToEnumMap = {
		{"cc", switchcase::cc},
		{"cf", switchcase::cf},
		{"ccf", switchcase::ccf},
		{"dc", switchcase::dc },
		{"df", switchcase::df},
		{"dcf", switchcase::dcf},
		{"ctn", switchcase::ctn},
		{"rnd", switchcase::rnd}
	};
	switchcase convertStringToEnum(string& str) {
		auto it = stringToEnumMap.find(str);
		if (it != stringToEnumMap.end())
			return it->second;
		else {
			stringToEnumMap.insert({ str , r });
			it = stringToEnumMap.find(str);
			return it->second;
		}
	}
}

int main()
{	
	using namespace FUNCTIONS;
	string defact_message = "il programma calcola la fattorizzazione di una serie di numeri";
	string deg_message = "il programma calcola il codice e il grado di una serie di numeri";
	string fact_message = "il programma scompone un numero in fattori primi";
	string message = "il programma converte un numero nel corrispondente codice e ne calcola il grado";
	string AllMessage = "il programma calcola factor, codice e grado";

	bool lock_prime_input = 0;
	do {
		cout << "CALCOLATRICE::\n\n";
		bool stop = 0;
		bool skip = 1;
		string text, vel;
		switchcase option;

		if (!lock_prime_input) {
			Global_N = pow(10, 10);
			text = "fino a quale numero cercare i numeri primi?\n";
			text.append("un limite piu' alto comporta un tempo di attesa piu' lungo\n");
			Global_N = get_user_num(text, 2, Global_N);

			steady_clock::time_point begin = steady_clock::now();
			IsPrime = Sieve(Global_N, 1);
			PrimeNumber = Sieve_of_Erastothens(IsPrime, Global_N);
			steady_clock::time_point end = steady_clock::now();
			int delta = duration_cast <milliseconds> (end - begin).count();
			int exception_delta = duration_cast <microseconds> (end - begin).count();
			if (delta <= 10) {
				cout << "tempo di calcolo numeri primi = " << exception_delta 
					 << " microsecondi" << "\n\n";
			}
			else cout << "tempo di calcolo numeri primi = " << delta << "[ms]" << "\n\n";
		}
		cout << "scegli opzioni::\n";
		cout << "se stringa di un carattere:\n";
		cout << "'0' = blocca input numeri primi\n";
		cout << "'1' = sblocca input numeri primi\n";
		cout << "'.' = fine programma\n";
		cout << "altrimenti:\n";
		cout << "'rnd' = casuale\n";
		cout << "'ctn' = da codice a numero\n";
		cout << "oppure:\n";
		cout << "primo carattere:\n";
		cout << "'c' = calcolo\n";
		cout << "'d' = debug\n";
		cout << "caratteri seguenti:\n";
		cout << "'c' = codifica\n";
		cout << "'f' = scomposizione in fattori primi\n";
		cout << "'cf' = codifica e scomposizione (impiega piu' tempo)\n";
		getline(cin, vel);
		option = convertStringToEnum(vel);
		do {
			if (vel.size() == 1) {
				skip = 0;
				switch (vel.at(0)) {
				case '0':
					lock_prime_input = 1;
					cout << "input numeri primi bloccato\n";
					break;
				case '1':
					lock_prime_input = 0;
					cout << "input numeri primi sbloccato\n";
					break;
				case '.': return 0;
					break;
				default: vel += ' ';
					break;
				}
			}
			if (option == r) do {
				skip = 0;
				cout << "scegli opzioni:: (...)\n";
				getline(cin, vel);
				if (vel.size() == 1) {
					stop = vel.at(0) != '0'
						&& vel.at(0) != '1' && vel.at(0) != '.';
				}
				else {
					option = convertStringToEnum(vel);
					stop = option == r;
					skip = option != r;
				}
				if (stop) cout << "non corretto\n";
			} while (stop);
			stop = 0;
		} while (!skip);
		cout << "\n\n";
		if (option == rnd) {
			random_device rng;
			mt19937 gen(rng());
			uniform_int_distribution<> dis(0, 6);
			switch (dis(gen)) {
			case 0: option = cc;
				break;
			case 1: option = cf;
				break;
			case 2: option = ccf;
				break;
			case 3: option = dc;
				break;
			case 4: option = df;
				break;
			case 5: option = dcf;
				break;
			case 6: option = ctn;
				break;
			}
		}
		switch (option) {
		case cc: repeater(message, coredegree);
			break;
		case cf: repeater(fact_message, corefactor);
			break;
		case ccf: repeater(AllMessage, NucleusAll);
			break;
		case dc: loop(deg_message, coredegree);
			break;
		case df: loop(defact_message, corefactor);
			break;
		case dcf: loop(AllMessage, NucleusAll);
			break;
		case ctn: CodeToNumber();
			break;
		}
	} while (0 == 0);
}
// program_END