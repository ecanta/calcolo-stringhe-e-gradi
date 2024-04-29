// program_START
#include <chrono>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <ppl.h>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace Concurrency;
using namespace std;
using namespace chrono;

long long GlobalMax = pow(10, 10);
typedef struct {
	vector <bool> is_prime;
	vector <int> list_primes;
} vector_t;
typedef struct {
	int number;
	string code;
	int degree;
	string expression;
} data_t;
typedef struct {
	int factors;
	int exp;
} compost_t;
vector_t PrimeNumbers;
mutex mtx;

namespace STATIC_Functions
{
	bool static prime(long long number) 
	{
		bool is_prime = 1;
		if (number == 1) return 0;
		else if (number < size(PrimeNumbers.is_prime)) {
			return PrimeNumbers.is_prime[number];
		}
		else {
			if (number == 1) is_prime = 0;
			for (int a = 2; a < number; a++)
				if (number % a == 0) is_prime = 0;
		}
		return is_prime;
	}

	double static IntegralLog(int N) 
	{
		double sum = 0;
		for (int x = 2; x <= N; x++) {
			sum += 1. / log(x);
		}
		return sum;
	}
	
	void static progress_Bar(double ratio, double barWidth) 
	{
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

	vector_t static Sieve_of_Erastothens(long long N, bool USE_pro_bar)
	{
		vector_t output;
		vector <bool> is_prime(N + 1, 1);
		vector <int> primes;
		vector <int> counter;
		const int SPEED = 75;
		const double BARWIDTH = 75;
		const double COEFF = 0.92;
		const int SQUARE = (int)sqrt(N) + 2;
		const double NOTPRIMESIZE = N - IntegralLog(N);
		int iter = 0;
		if (N >= 100 && USE_pro_bar) {
			parallel_for(int(2), SQUARE, [&](int p) {
				if (is_prime[p]) {
					for (int i = pow(p, 2); i <= N; i += p) {
						mtx.lock();
						is_prime[i] = 0;
						counter.push_back(0);
						mtx.unlock();
					}
				}
				if (iter % SPEED == 0) {
					mtx.lock();
					double progress = (double)size(counter) / NOTPRIMESIZE;
					if (progress > 1)
						progress = 1;
					progress_Bar(progress, BARWIDTH);
					mtx.unlock();
				}
				iter++;				
			});
		}
		else for (int p = 2; p < SQUARE; p++) {
			for (int i = pow(p, 2); i <= N; i += p) {
				is_prime[i] = 0;
			}
		}
		if (USE_pro_bar) {
			for (int i = 0; i < BARWIDTH + 11; i++)
				cout << ' ';
			cout << '\n';
		}
		cout << "attendere\r";
		for (long long p = 2; p < N + 1; p++)
			if (is_prime[p]) primes.push_back(p);
		output.is_prime = is_prime;
		output.list_primes = primes;
		return output;
	}

	vector <data_t> static SortData(vector <data_t> vect) 
	{
		for (int i = 0; i < size(vect); i++) {
			for (int j = 0; j < size(vect); j++) {
				if (vect[i].number < vect[j].number) {
					data_t transfert;
					transfert = vect[i];
					vect[i] = vect[j];
					vect[j] = transfert;
				}
			}
		}
		return vect;
	}

	vector <compost_t> static decompose_number(long long input) 
	{
		if (input > PrimeNumbers.list_primes[size(PrimeNumbers.list_primes) - 1]) {
			vector_t PrimeN = Sieve_of_Erastothens(input, 0);
			for (int i = size(PrimeNumbers.list_primes); i < size(PrimeN.list_primes); i++) {
				mtx.lock();
				PrimeNumbers.list_primes.push_back(PrimeN.list_primes[i]);
				mtx.unlock();
			}
		}
		vector <compost_t> output;
		compost_t output_element;
		output_element.factors = 0;
		output_element.exp = 1;
		for (int i = 0; i < 15; i++) output.push_back(output_element);
		int index = 0;

		for (int i = 0; pow(PrimeNumbers.list_primes[i], 2) <= input; i++) {
			if (input != 1) {
				if (input % PrimeNumbers.list_primes[i] == 0) {
					if (output[index].factors == PrimeNumbers.list_primes[i])
						output[index].exp++;
					else output[index].factors = PrimeNumbers.list_primes[i];
					input /= PrimeNumbers.list_primes[i];
					if (input % PrimeNumbers.list_primes[i] != 0) {
						index++;
					}
					i--;
				}
			}
		}
		if (output[index].factors == input)
			output[index].exp++;
		else output[index].factors = input;
		input = 1;

		return output;
	}

	string static Cript(long long input)
	{
		vector <compost_t> expfactors = decompose_number(input);
		long long PrimeFactors[15];
		int exponents[15];
		int factor_number;
		bool when_null = 1;
		for (int i = 0; i < 15; i++) {
			PrimeFactors[i] = expfactors[i].factors;
			exponents[i] = expfactors[i].exp;
			if (when_null && PrimeFactors[i] == 0) {
				factor_number = i;
				when_null = 0;
			}
		}

		string the_string, exp_verify, exp_string, prime_exp_string;
		int prime_exp, sizestring, presence;
		long long analyse;
		bool repeat;
		string monomials[15];
		for (int what_factor = 0; what_factor < factor_number; what_factor++) {
			repeat = 0;
			presence = 0;

			exp_verify = to_string(exponents[what_factor]);
			analyse = PrimeFactors[what_factor];
			string part_of1 = "(";
			string part_of2 = ")";
			if (exponents[what_factor] != 1 && exponents[what_factor] < 11) {
				part_of2.append(exp_verify);
				presence = 1;
			}
			else if (exponents[what_factor] > 10) {
				part_of2.append(".");
				part_of2.append(exp_verify);
				presence = 2;
			}
			string analyse_string = to_string(analyse);
			the_string = part_of1 + analyse_string + part_of2;

			do {
				while (prime(analyse)) {
					long long position = -1;
					int a = 1;
					do {
						if (PrimeNumbers.list_primes[a - 1] == analyse)
							position = a;
						a++;
					} while (position < 0);
					analyse = position;
					analyse_string = to_string(analyse);
					the_string.erase(0, the_string.find(')'));
					the_string = part_of1 + analyse_string + the_string;
					sizestring = the_string.size();

					if (presence == 1) {
						exp_string = string(1, the_string.at(sizestring - 1));
						the_string.erase(sizestring - 1);
						sizestring--;
					}
					else if (presence == 2) {
						exp_string = "." + string(1, the_string.at(sizestring - 2)) 
									+ string(1, the_string.at(sizestring - 1));
						the_string.erase(sizestring - 3);
						sizestring--;
					}
					if (repeat) {
						prime_exp_string = string(1, the_string.at(sizestring - 1));
						the_string.erase(sizestring - 1);
						prime_exp = stoi(prime_exp_string);
						prime_exp++;
						prime_exp_string = to_string(prime_exp);
						if (prime_exp > 10) {
							prime_exp_string = "." + prime_exp_string;
						}
						the_string.append(prime_exp_string);
					}
					else {
						the_string.append("1");
					}
					if (presence > 0) {
						the_string.append(exp_string);
					}
					repeat = 1;
				}
				if (analyse != 1 && !prime(analyse)) {
					analyse_string = Cript(analyse);
					the_string.erase(0, the_string.find(')'));
					the_string = part_of1 + analyse_string + the_string;
					analyse = 1;
				}

			} while (analyse != 1);
			monomials[what_factor] = the_string;
		}

		the_string = "";
		for (int i = 0; i < factor_number; i++) {
			the_string = the_string + "+" + monomials[i];
		}
		the_string.erase(0, 1);

		int position[15];
		int j = 0;
		for (int i = 0; i < (the_string.size() - 2); i++) {
			if ((the_string.at(i) == '(') && (the_string.at(i + 1) == '1') 
				&& (the_string.at(i + 2) == ')')) {
				position[j] = i;
				j++;
			}
		}
		for (int k = j - 1; k >= 0; k--)
			the_string.erase(position[k], 3);

		int l = 0;
		sizestring = the_string.size();
		if (sizestring > 4) {
			for (int m = 0; m < (the_string.size() - 3); m++) {
				if ((the_string.at(m) == '(') && (the_string.at(m + 3) == ')')) {
					position[l] = m;
					l++;
				}
			}
			for (int m = l - 1; m >= 0; m--) {
				the_string.erase(position[m] + 3, 1);
				the_string.erase(position[m], 1);
			}
		}

		return the_string;
	}

	vector <string> static fractioner(string polinomial) 
	{
		vector <string> monomials;
		string backup = polinomial;
		string temp;
		int parenthesis_balance = 0;
		int p_balance = 0;
		int find = 0;
		for (int i = 0; i < backup.size(); i++) {
			if (backup.at(i) == '(') parenthesis_balance++;
			if ((parenthesis_balance == 0) && (backup.at(i) == '+')) {
				temp = polinomial;
				for (int finder = 0; finder < temp.size(); finder++) {
					if (find == 0) {
						if (temp.at(finder) == '(') p_balance++;
						if ((p_balance == 0) && (temp.at(finder) == '+')) {
							find = finder;
						}
						if (temp.at(finder) == ')') p_balance--;
					}
				}
				temp.erase(find);
				monomials.push_back(temp);
				polinomial.erase(0, find + 1);
				find = 0;
			}
			if (backup.at(i) == ')') parenthesis_balance--;
		}
		monomials.push_back(polinomial);
		return monomials;
	}

	int static ExecuteStrings(string input)
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
		for (int i = 0; i < size(monomials); i++) {
			if (monomials[i].at(0) == '(') {
				for (int j = monomials[i].size() - 1; j >= 0; j--) {

					if ((presence) && (monomials[i].at(j) == ')')) {
						presence = 0;
						location = j;
					}
				}
				string temp = monomials[i];
				temp.erase(location);
				temp.erase(0, 1);
				monomials[i].erase(0, location + 1);
				values[i] = ExecuteStrings(temp) * (stoi(monomials[i]));
			}
			else {
				values[i] = stoi(monomials[i]);
			}
			presence = 1;
		}
		for (int end = 0; end < size(monomials); end++) output += values[end];
		return output;
	}

	long long static get_user_num(string txt, int lw, long long Bound) 
	{
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

		} while (user_num < lw || user_num > Bound);

		return user_num;
	}

	string static Fact_Number(long long input)
	{
		vector <compost_t> expfactors = decompose_number(input);
		int PrimeFactors[15];
		int exponents[15];
		int factors;
		bool tag2 = 1;
		for (int i = 0; i < 15; i++) {
			PrimeFactors[i] = expfactors[i].factors;
			exponents[i] = expfactors[i].exp;
			if (tag2 && (PrimeFactors[i] == 0)) {
				factors = i;
				tag2 = 0;
			}
		}

		string output = "";
		for (int i = 0; i < factors; i++) {
			if (exponents[i] != 1) {
				output = output + to_string(PrimeFactors[i]) 
					+ "^" + to_string(exponents[i]) + " * ";
			}
			else output = output + to_string(PrimeFactors[i]) + " * ";
		}
		output.erase(output.size() - 3);

		return output;
	}

	data_t static coredegree(long long input)
	{
		data_t output;
		int counter = 0;
		int copy = input;
		do {
			copy = ExecuteStrings(Cript(copy));
			counter++;
			if (copy < 4) output.degree = counter + copy;

		} while (copy != 1);
		copy = input;
		output.number = copy;
		output.code = Cript(copy);
		output.expression = "";
		return output;
	}

	data_t static corefactor(long long input)
	{
		data_t output;
		output.number = input;
		output.code = "";
		output.degree = 0;
		output.expression = Fact_Number(input);
		return output;
	}

	data_t static coredegfactor(long long input)
	{
		data_t A = coredegree(input);
		data_t B = corefactor(input);
		data_t output;
		output.number = input;
		output.code = A.code;
		output.degree = A.degree;
		output.expression = B.expression;
		return output;
	}

	vector <int> static decompose_string(string Terminal) {
		int pass = 0;
		int ciphres_element;
		vector <int> ciphres;
		for (int i = 0; i < Terminal.size(); i++) {
			while (pass != 0) {
				i++;
				pass--;
			}
			if (i >= Terminal.size()) return ciphres;
			if (i == Terminal.size() - 1)
				ciphres_element = Terminal.at(i) - '0';
			else if (i > Terminal.size() - 3) {
				if (Terminal.at(i + 1) == '0') {
					ciphres_element = 10 * (Terminal.at(i) - '0');
					pass = 1;
				}
				else ciphres_element = Terminal.at(i) - '0';
			}
			else if (Terminal.at(i) == '.') {
				ciphres_element = 10 * (Terminal.at(i + 1) - '0')
									 + (Terminal.at(i + 2) - '0');
				pass = 2;
			}
			else {
				if (Terminal.at(i + 1) == '0') {
					ciphres_element = 10 * (Terminal.at(i) - '0');
					pass = 1;
				}
				else ciphres_element = Terminal.at(i) - '0';
			}
			ciphres.push_back(ciphres_element);
		}
		return ciphres;
	}

	string static Syntax_Validator(string ToEvaluate) 
	{	
		if (ToEvaluate == "f") return "";
		vector <string> mono;
		string charsAllowed = "0123456789+(.)";
		bool local_error = 1, boolean = 1, stable = 0;
		int start = -1, end = -1, parenthesis_balance = 0;
		for (int find = 0; find < ToEvaluate.size(); find++) {
			if (ToEvaluate.at(find) == '<') start = find + 1;
			else if (ToEvaluate.at(find) == '>') end = find;
		}
		if (start == -1 || end == -1) return "NO_BOUNDARY";
		if (end < start) return "BOUNDARY_INVERSION";
		ToEvaluate.erase(end);
		ToEvaluate.erase(0, start);
		for (int i = 0; i < ToEvaluate.size(); i++) {
			if (ToEvaluate.at(i) == '(') {
				parenthesis_balance++;
				stable++;
			}
			if (ToEvaluate.at(i) == ')') parenthesis_balance--;
		}
		if (parenthesis_balance != 0) return "UNBALANCED_BRACKETS";
		for (int space = ToEvaluate.size() - 1; space >= 0; space--) {
			if (ToEvaluate.at(space) == ' ')
				ToEvaluate.erase(space, 1);
		}
		if (ToEvaluate.empty()) return "EMPTY_IMPUT";
		for (int i = 0; i < ToEvaluate.size(); i++) {
			for (int j = 0; j < charsAllowed.size(); j++) {
				if (ToEvaluate.at(i) == charsAllowed.at(j))
					local_error = 0;
			}
			if (local_error) return "UNALLOWED_CHARACTERS";
			local_error = 1;
		}
		if (ToEvaluate.at(0) == '+') return "NO_START_STRING";
		if (ToEvaluate.at(0) == '0') return "NULL_DIGIT";
		if (ToEvaluate.at(0) == ')') return "INVERTED_BRACKETS";
		if (ToEvaluate.at(ToEvaluate.size() - 1) == '+')
			return "NO_END_STRING";
		for (int i = 0; i < ToEvaluate.size() - 1; i++) {
			if (ToEvaluate.at(i) == '+' && ToEvaluate.at(i + 1) == '+')
				return "MISSING_MONOMIAL";
		}
		for (int i = 0; i < ToEvaluate.size() - 1; i++) {
			if (ToEvaluate.at(i) == '0' && ToEvaluate.at(i + 1) == '0')
				return "CONSECUTIVE_NULL_DIGITS";
		}
		for (int i = 0; i < ToEvaluate.size(); i++) {
			if (ToEvaluate.size() == 1) {
				if (ToEvaluate.at(0) == '.')
					return "MISSING_DIGITS";
			}
			else if (i >= (ToEvaluate.size() - 2)) {
				if (ToEvaluate.at(i) == '.')
					return "MISSING_DIGITS";
			}
			else {
				char short_1 = ToEvaluate.at(i + 1);
				bool short_2 = short_1 == '+' || short_1 == ')'
					|| short_1 == '(' || short_1 == '0';
				char short_3 = ToEvaluate.at(i + 2);
				bool short_4 = short_3 == '+' || short_3 == ')'
					|| short_3 == '(' || short_3 == '0';
				if (ToEvaluate.at(i) == '.' && short_2 && short_4)
					return "MISSING_DIGITS";
			}
		}
		for (int i = 1; i < ToEvaluate.size(); i++) {
			char short_1 = ToEvaluate.at(i - 1);
			bool short_2 = short_1 == '+' || short_1 == ')' || short_1 == '(';
			if (ToEvaluate.at(i) == '0' && short_2)
				return "NULL_DIGITS";
		}
		mono = fractioner(ToEvaluate);
		for (int monomial = 0; monomial < size(mono); monomial++) {
			int stackfinder = -1, stickfinder = -1, finder;
			bool stop = 0, pass = 0;
			int res = 0;
			string min, max;
			vector <int> min_ciphres, max_ciphres;
			vector <int> ciphr_min, ciphr_max;
			string stack = mono[monomial];
			for (int second = 1; second < size(mono); second++) {
				if (monomial != second) {
					if (mono[monomial] == mono[second]) return "EQUAL_MONOMIALS";
					string stick = mono[second];
					if (stack.size() < stick.size()) {
						min = stack;
						max = stick;
					}
					else {
						min = stick;
						max = stack;
					}
					if (stack.at(0) == '(' || stick.at(0) == ')') {
						boolean = 1;
						for (int j = stack.size() - 1; j > 0; j--) {
							if (boolean && stack.at(j) == ')') {
								stackfinder = j - 1;
								boolean = 0;
							}
						}
						boolean = 1;
						for (int k = stick.size() - 1; k > 0; k--) {
							if (boolean && stick.at(k) == ')') {
								stickfinder = k - 1;
								boolean = 0;
							}
						}
						if (stackfinder * stickfinder < 0) {
							if (stackfinder > 0) finder = stackfinder;
							else finder = stickfinder;
						}
						else if (stickfinder == stackfinder) {
							finder = stackfinder;
							for (int l = 0; l <= finder + 1; l++) {
								if (l < min.size()) {
									if (stick.at(l) != stack.at(l))
										stop = 1;
								}
							}
							string min_backup = min;
							string max_backup = max;
							min_backup.erase(0, finder + 2);
							max_backup.erase(0, finder + 2);
							min_ciphres = decompose_string(min_backup);
							max_ciphres = decompose_string(max_backup);
							if (size(min_ciphres) < size(max_ciphres)) {
								ciphr_min = min_ciphres;
								ciphr_max = max_ciphres;
							}
							else {
								ciphr_min = max_ciphres;
								ciphr_max = min_ciphres;
							}
							for (int l = 0; l < size(ciphr_min); l++) {
								if (!stop && ciphr_min[l] == ciphr_max[l]) {
									res++;
									if (ciphr_min[l] != ciphr_max[l])
										stop = 1;
								}
								else stop = 1;
							}
						}
					}
					else {
						min_ciphres = decompose_string(min);
						max_ciphres = decompose_string(max);
						if (size(min_ciphres) < size(max_ciphres)) {
							ciphr_min = min_ciphres;
							ciphr_max = max_ciphres;
						}
						else {
							ciphr_min = max_ciphres;
							ciphr_max = min_ciphres;
						}
						for (int l = 0; l < size(ciphr_min); l++) {
							if (!stop && ciphr_min[l] == ciphr_max[l]) {
								res++;
								if (ciphr_min[l] != ciphr_max[l])
									stop = 1;
							}
							else stop = 1;
						}
					}
					if (res % 2 == 1) return "SIMILIAR_MONOMIALS";
				}
			}
			boolean = 1;
			for (int j = stack.size() - 1; j > 0; j--) {
				if (boolean && stack.at(j) == ')') {
					finder = j - 1;
					boolean = 0;
				}
			}
			if (stack.at(stack.size() - 1) == ')')
				return "MISSING_OBJECT";
			if (stack.at(stack.size() - 1) == '(')
				return "INVERTED_BRACKETS";
			if (stack.at(0) == '(') {
				local_error = 1;
				for (int checkplus = 1; checkplus < finder; checkplus++) {
					if (stack.at(checkplus) == '+') local_error = 0;
				}
				if (local_error) return "USELESS_BRACKETS";
				stack.erase(0, 1);
				stack.erase(finder);
				string message = Syntax_Validator("<" + stack + ">"); 
				if (!message.empty()) return message;
			}
			else if (mono[monomial].at(0) == ')') return "INVERTED_BRACKETS";
			else for (int check = 1; check < mono[monomial].size(); check++) {
				if (mono[monomial].at(check) == '(') return "WRONG_OBJECT";
				if (mono[monomial].at(check) == ')') return "WRONG_OBJECT";
			}
		}
		return "";
	}

	long long static NumberConverter(long long root, string M) 
	{
		bool WhichWay = 1, XOutOfRange = 0;
		bool UselessExponent = 0, pass = 0;
		int sizeP = size(PrimeNumbers.list_primes), nums;
		vector <int> ciphres = decompose_string(M);
		for (int iter = 0; iter < size(ciphres); iter++) {
			WhichWay = !WhichWay;
			nums = ciphres[iter];
			if (!XOutOfRange && WhichWay) {
				UselessExponent = nums == 1;
				root = pow(root, nums);
			}
			else {
				do {
					if (!XOutOfRange && root < sizeP) {
						root = PrimeNumbers.list_primes[root - 1];
						nums--;
					}
					else XOutOfRange = 1;
				} while (XOutOfRange != 1 && nums != 0);
			}
		}
		if (UselessExponent) return -2;
		if (XOutOfRange) return -1;
		return root;
	}

	long long static StringConverter(string ToEvaluate) 
	{
		long long integer = 1;
		string backup, back;
		vector <string> mono = fractioner(ToEvaluate);
		int sizeP = size(PrimeNumbers.list_primes);
		int finder;
		bool TAG = 1;
		for (int monomial = 0; monomial < size(mono); monomial++) {
			string M = mono[monomial];
			long long root;
			bool WhichWay = 0;
			if (M.at(0) != '(') root = NumberConverter(1, M);
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
				root = StringConverter(back);
				root = NumberConverter(root, backup);
			}
			if (root < 0) return root;
			else integer *= root;
		}
		return integer;
	}

	void static CodeToNumber() 
	{
		string ToEvaluate, message;
		vector <string> mono;
		long long number;
		cout << "il programma traduce una stringa di codice\n";
		cout << "il codice non deve avere errori o saranno segnalati\n";
		cout << "il codice deve essere compreso tra <>\n";
		cout << "se sono presenti più caratteri '<', '>',\n";
		cout << "verranno considerati solo quelli che compaiono prima\n";
		cout << "unici caratteri non numerici ammessi: '(', ')', '+', '.' \n\n";
		do {
			do {
				cout << "inserire una stringa (f = fine input)\n";
				getline(cin, ToEvaluate);
				message = Syntax_Validator(ToEvaluate);
				if (!message.empty())
					cout << "ERR[404]: " << message << '\n';
			} while (!message.empty());
			int start = 0;
			int end = 0;
			
			if (ToEvaluate != "f") {
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
				number = StringConverter(ToEvaluate);
				if (number == -1) cout << "ERR[413]: XOutOfRange\n";
				if (number == -2) cout << "ERR[413]: UselessExponent\n";
				if (number > 0) 
					cout << "il numero corrispondente e' " << number << '\n';
			}
		} while (ToEvaluate != "f");
	} 
	
	void static printf(data_t structure) 
	{
		cout << "numero " << structure.number << ":\n";
		if (!structure.code.empty()) {
			cout << "il codice e' <" << structure.code << ">\n";
		}
		if (structure.degree != 0) {
			cout << "il grado e' " << structure.degree << '\n';
		}
		if (!structure.expression.empty()) {
			if (PrimeNumbers.is_prime[structure.number]) cout << "il numero e' primo\n";
			else {
				cout << "la fattorizzazione e' " << structure.expression << '\n';
			}
		}
	}

	void static repeater(string message, data_t nucleus(long long input))
	{
		string n_ = to_string(GlobalMax);
		long long input;
		data_t result;
		cout << message << "\n\n";
		do {
			string txt = "inserire un numero tra 2 e " + n_ + " (1 = fine input)\n";
			input = get_user_num(txt, 1, GlobalMax);
			if (input != 1) {
				result = nucleus(input);
				printf(result);
			}
		} while (input != 1);
	}

	void static loop(string message, data_t nucleus(long long input))
	{
		string n_ = to_string(GlobalMax);
		vector <data_t> data;
		double Barwidth = 60;
		long long input, change;
		cout << "debug::\n\n";
		cout << message << '\n';
		cout << "gli estremi dell'intervallo devono essere compresi tra 1 e " << n_ << "\n\n";

		string txt = "inserisci il valore di inizio della ricerca\n";
		long long lower_bound = get_user_num(txt, 1, GlobalMax) + 1;

		txt = "inserisci il valore finale della ricerca\n";
		long long upper_bound = get_user_num(txt, 1, GlobalMax) + 1;

		if (upper_bound < lower_bound) {
			change = upper_bound;
			upper_bound = lower_bound;
			lower_bound = change;
		}
		long long datalenght = upper_bound - lower_bound;

		string choice;
		cout << "vuoi utilizzare la ricerca veloce (non stampa direttamente i numeri)\n";
		cout << "immetti s = si oppure n = no  ";
		getline(cin, choice);
		cout << '\n';

		if (choice == "s") {
			int iter = 0;
			atomic <double> Progress = 0;
			steady_clock::time_point begin = steady_clock::now();
			parallel_for(long long(lower_bound), upper_bound, [&](long long set) {

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
			for (long long set = lower_bound; set < upper_bound; set++) {
				data_t data_element = nucleus(set);
				printf(data_element);
			}
			steady_clock::time_point end = steady_clock::now();
			cout << "\ntempo di calcolo = " << duration_cast <milliseconds> (end - begin).count()
				 << "[ms]" << '\n';
		}
	}

	enum switchcase { cc, cf, ccf, dc, df, dcf, ctn, rnd, r };
	static unordered_map <string, switchcase> stringToEnumMap = {
		{"cc", switchcase::cc},
		{"cf", switchcase::cf},
		{"ccf", switchcase::ccf},
		{"dc", switchcase::dc },
		{"df", switchcase::df},
		{"dcf", switchcase::dcf},
		{"ctn", switchcase::ctn},
		{"rnd", switchcase::rnd}
	};
	switchcase static ConvertStringToEnum(string str) {
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
	using namespace STATIC_Functions;
	cout << "CALCOLATRICE::\n\n";
	string defact_message = "il programma calcola la fattorizzazione di una serie di numeri";
	string deg_message = "il programma calcola il codice e il grado di una serie di numeri";
	string fact_message = "il programma scompone un numero in fattori primi";
	string message = "il programma converte un numero nel corrispondente codice e ne calcola il grado";
	string AllMessage = "il programma calcola factor, codice e grado";

	bool lock_prime_input = 0;
	do {
		bool stop = 0;
		bool skip = 1;
		string text, vel;
		switchcase option;

		if (!lock_prime_input) {
			GlobalMax = pow(10, 10);
			text = "fino a quale numero cercare i numeri primi?\n";
			text.append("un limite piu' alto comporta un tempo di attesa piu' lungo\n");
			text.append("ES.: 30.000.000 = 1 minuto di attesa circa\n");
			GlobalMax = get_user_num(text, 2, GlobalMax);

			steady_clock::time_point begin = steady_clock::now();
			PrimeNumbers = Sieve_of_Erastothens(GlobalMax, 1);
			steady_clock::time_point end = steady_clock::now();
			int delta = duration_cast <milliseconds> (end - begin).count();
			int exception_delta = duration_cast <microseconds> (end - begin).count();
			if (delta <= 10) {
				cout << "tempo di calcolo numeri primi = " << exception_delta 
					 << " microsecondi" << "\n\n";
			}
			else if (delta > 10'000 && delta <= 600'000) {
				delta = delta / 1000;
				cout << "tempo di calcolo numeri primi = " << delta << " secondi" << "\n\n";
			}
			else if (delta > 600'000) {
				delta = delta / 60'000;
				cout << "tempo di calcolo numeri primi = " << delta << " minuti" << "\n\n";
			}
			else {
				cout << "tempo di calcolo numeri primi = " << delta
					 << " millisecondi" << "\n\n";
			}
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
		option = ConvertStringToEnum(vel);
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
					option = ConvertStringToEnum(vel);
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
		case ccf: repeater(AllMessage, coredegfactor);
			break;
		case dc: loop(deg_message, coredegree);
			break;
		case df: loop(defact_message, corefactor);
			break;
		case dcf: loop(AllMessage, coredegfactor);
			break;
		case ctn: CodeToNumber();
			break;
		}
	} while (0 == 0);
}
// program_END