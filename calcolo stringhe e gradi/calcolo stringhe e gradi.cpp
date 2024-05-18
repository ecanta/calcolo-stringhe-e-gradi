// Descrizione ::
	/*														  |
	*	Strings ZP[2.2].cpp: il programma calcola singola e\o |
	*  doppia scomposizione di alcuni interi in una stringa   |
	*  o il contrario, e i numeri primi						  |
	*/
//

// program_START
#include <chrono> // per le misurazioni di tempo
#include <cmath> // per i calcoli
#include <condition_variable> // per il multithreading
#include <conio.h> // per l'input avanzato
#include <future> // per le interruzioni
#include <iomanip>
#include <iostream> // per l'output
#include <ppl.h> // per la parallelizzazione
#include <random> // per i generatori casuali
#include <regex> // per la convalidazione
#include <sstream>
#include <string>
#include <thread> // per il multithreading
#include <unordered_map> // per la conversione degli enum
#include <vector>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h> // per hConsole
using namespace std;
using namespace chrono;
using Concurrency::parallel_for;
using this_thread::sleep_for;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;
CONSOLE_CURSOR_INFO cursorInfo = { 10, FALSE };
CONSOLE_CURSOR_INFO cursor = { 10, TRUE };

// variabili globali
const double PI = 3.1415926535897932;
const long long GLOBAL_CAP = pow(10, 10);
long long GlobalMax = pow(10, 10);
atomic <bool> GlobalInterr(0);
atomic <bool> interrupted(0);
atomic <bool> computing(0);
atomic <bool> is_done(0);
condition_variable cv;
mutex coutMutex, mtx;

static char NotBlockingGetch() { return _getch(); }
typedef struct {
	vector <bool> is_prime;
	vector <int> list_primes;
} vector_t;
typedef struct {
	int factors;
	int exp;
} compost_t;
typedef struct {
	int DivNumber;
	int DivSum;
	int DivProduct;
	string Div_pr;
} divisor_t;
typedef struct {
	int number;
	wstring code;
	int degree;
	vector <int> sequence;
	string expression;
	int Div_number;
	int Div_sum;
	int Div_product;
	string Divpr;
} data_t;
enum switchcase {
	cc, ccc, cf,
	cff, ccf, ct,
	dc, dcc, df,
	dff, dcf, dt,
	ctn, rnd, r
};
vector_t PrimeNumbers;

namespace EnumMod
{
	static unordered_map <wstring, switchcase> stringToEnumMap = {
		{L"cc", switchcase::cc},
		{L"ccc", switchcase::ccc},
		{L"cf", switchcase::cf},
		{L"cff", switchcase::cff},
		{L"ccf", switchcase::ccf},
		{L"ct", switchcase::ct},
		{L"dc", switchcase::dc},
		{L"dcc", switchcase::dcc},
		{L"df", switchcase::df},
		{L"dff", switchcase::dff},
		{L"dcf", switchcase::dcf},
		{L"dt", switchcase::dt},
		{L"ctn", switchcase::ctn},
		{L"rnd", switchcase::rnd}
	};
	static unordered_map <switchcase, wstring> enumToStringMap = {
		{switchcase::cc, L"cc"},
		{switchcase::ccc, L"ccc"},
		{switchcase::cf, L"cf"},
		{switchcase::cff, L"cff"},
		{switchcase::ccf, L"ccf"},
		{switchcase::ct, L"ct"},
		{switchcase::dc, L"dc"},
		{switchcase::dcc, L"dcc"},
		{switchcase::df, L"df"},
		{switchcase::dff, L"dff"},
		{switchcase::dcf, L"dcf"},
		{switchcase::dt, L"dt"},
		{switchcase::ctn, L"ctn"},
		{switchcase::rnd, L"rnd"}
	};
	static wstring ConvertEnumToWString(switchcase Enum) {
		auto it = enumToStringMap.find(Enum);
		if (it != enumToStringMap.end())
			return it->second;
	}
	static switchcase ConvertWStringToEnum(wstring str) {
		auto it = stringToEnumMap.find(str);
		if (it != stringToEnumMap.end())
			return it->second;
		else {
			stringToEnumMap.insert({ str , r });
			it = stringToEnumMap.find(str);
			return it->second;
		}
	}
	static switchcase ReassigneEnum(switchcase option) {
		if (option == rnd) {
			random_device rng;
			mt19937 gen(rng());
			uniform_int_distribution<> dis(0, 13);
			switch (dis(gen)) {
			case 0: return cc;
				break;
			case 1: return ccc;
				break;
			case 2: return cf;
				break;
			case 3: return cff;
				break;
			case 4: return ccf;
				break;
			case 5: return dcf;
				break;
			case 6: return ct;
				break;
			case 7: return dc;
				break;
			case 8: return dcc;
				break;
			case 9: return df;
				break;
			case 10: return dff;
				break;
			case 11: return dff;
				break;
			case 12: return dt;
				break;
			case 13: return ctn;
				break;
			}
		}
		else return option;
	}
}
namespace Sort
{
	template <typename struct_t>
	static void Heapify(vector <struct_t>& vect, int n, int i) {
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		if (left < n && vect[left].number > vect[largest].number)
			largest = left;
		if (right < n && vect[right].number > vect[largest].number)
			largest = right;
		if (largest != i) {
			swap(vect[i], vect[largest]);
			Heapify(vect, n, largest);
		}
	}
	template <typename struct_t>
	static vector <struct_t> HeapSort(vector <struct_t>& vect) {
		int n = vect.size();
		for (int i = n / 2 - 1; i >= 0; i--) Heapify(vect, n, i);
		for (int i = n - 1; i > 0; i--) {
			swap(vect[0], vect[i]);
			Heapify(vect, i, 0);
		}
		return vect;
	}
}
namespace Prints
{
	static void ProgressBar(double ratio, double barWidth)
	{
		// necessario per poter scrivere messaggi 
		// sotto alla barra di progresso
		SetConsoleCursorPosition(hConsole, { 0, 0 });

		// stampa della barra principale
		cout << "[[";
		int pos = (int)(barWidth * ratio);
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) cout << "=";
			else (i == pos) ? cout << ">" : cout << " ";
		}

		// calcolo della percentuale
		ratio *= 100.0;
		stringstream stream;
		stream << fixed << setprecision(1) << ratio;
		string s = stream.str();
		cout << "]] " << s << "%\r";
	}
	static void PrintPFrame(double deg
		, int sides, double radius, COORD win_center)
	{
		SetConsoleTextAttribute(hConsole, 15);

		COORD coord;
		const double DIM = 1.9;
		const int centerX = win_center.X;
		const int centerY = win_center.Y;
		double setX, setY;
		double theta = 2 * PI / sides;

		// calcolo apotema e lato con la goniometria e le formule
		double sidelenght = sqrt(2 * pow(radius, 2) * (1 - cos(theta)));
		double apotem = sqrt(pow(radius, 2) - pow(sidelenght / 2, 2));

		// stringa dei caratteri per l'illuminazione del poligono
		string prints = "@$#/*!+=~;:-,.";

		for (double rad = 0; rad < 2 * PI; rad += theta) {
			for (int i = 0; i < sidelenght; i++) {

				// calcolo punti del poligono
				setX = i - sidelenght / 2;
				setY = apotem;
				rad += deg;

				// rotazione punti
				coord.X = setX * cos(rad) - setY * sin(rad);
				coord.Y = setX * sin(rad) + setY * cos(rad);

				// traslazione e ridimensionamento X
				coord.X *= DIM;
				coord.X += centerX;
				coord.Y += centerY;

				rad -= deg;

				// illuminazione
				SetConsoleCursorPosition(hConsole, coord);
				int index = coord.Y - centerY + radius;
				index *= (double)prints.size() / (2 * radius);
				cout << prints[index];
			}
		}
	}
	static void PrintCircle()
	{
		system("cls");
		COORD coord;

		// assegnazione delle coordinate del centro
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		COORD win_center;
		COORD min = { 25, 15 };
		if (csbi.dwSize.X / 2 < min.X) win_center.X = min.X;
		else win_center.X = csbi.dwSize.X / 2;
		if (csbi.dwSize.Y / 2 < min.Y) win_center.Y = min.Y;
		else win_center.Y = csbi.dwSize.Y / 2;

		int arc = 270, square_radius = 0, sides = 4;
		const double SPEED = 50;
		const double GAP = 0.05;
		bool arc_decrease = 1, decrease = 1;
		const int const_x = win_center.X;
		const int const_y = win_center.Y;
		int centerX, centerY, setX, setY;
		double DIM = 1.9;
		const double R = 8;
		const double R2 = 5;

		// vettore dello spettro dei colori
		const vector <int> spectrum = { 9, 9, 9, 11, 11, 3, 3, 12, 4};

		for (int i = 0; i % 360 < 360; i += 3) {
			double __i = (double)i / 180 * PI;
			// variazione centro del cerchio principale
			// secondo lo spostamento su un secondo cerchio
			centerX = const_x + R2 * cos(__i);
			centerY = const_y + R2 * sin(__i);

			// variazione dati cerchio
			if (DIM <= 1 || DIM >= 2.5) decrease = !decrease;
			if (arc <= 0 || arc >= 360) arc_decrease = !arc_decrease;

			for (int deg = 0; deg < arc; deg++) {
				// da gradi a radianti
				double rad = (double)deg / 180 * PI;

				// calcolo punti della circonferenza del cerchio
				setX = R * cos(rad);
				setY = R * sin(rad);

				// rotazione punti
				coord.X = setX * cos(__i) - setY * sin(__i);
				coord.Y = setX * sin(__i) + setY * cos(__i);

				// ridimensionamento X
				coord.X *= DIM;

				// traslazione
				coord.X += centerX;
				coord.Y += centerY;

				SetConsoleCursorPosition(hConsole, coord);
				int colour;

				// generatore casuale numeri
				random_device rng;
				mt19937 gen(rng());
				uniform_int_distribution<> dis(0, 9);
				random_device rnd;

				// generatore casuale colori
				mt19937 Gen(rnd());
				uniform_int_distribution<> Dis(0, size(spectrum) - 1);
				int DisGen = Dis(Gen);

				// assegnazione colori
				for (int j = 0; j < size(spectrum); j++)
					if (DisGen == j) colour = spectrum[j];

				// stampa
				SetConsoleTextAttribute(hConsole, colour);
				cout << dis(gen);
			}

			// stampa poligono e cambio variabili
			decrease ? DIM -= GAP : DIM += GAP;
			arc_decrease ? arc -= SPEED * GAP : arc += SPEED * GAP;
			PrintPFrame(square_radius * PI / 180, sides, 10, win_center);
			square_radius += 2;

			// riassegnazione dei lati
			if (square_radius % 180 == 0) 
				switch (sides) {
				case 4: sides = 6;
					break;
				case 6: sides = 8;
					break;
				case 8: sides = 4;
					break;
				}
			if (is_done.load()) return;
			system("cls");
			SetConsoleCursorPosition(hConsole, { 0, 0 });
			cout << "attendere";
		}
	}
	static void DataPrintF(data_t structure)
	{
		setlocale(LC_ALL, "");

		// stampa numero
		cout << "numero " << structure.number << ":\n";

		// stampa stringa
		if (!structure.code.empty()) {
			SetConsoleTextAttribute(hConsole, 12);
			wcout << L"il codice è <" << structure.code << ">\n";
		}

		// stampa grado e sequenza
		if (structure.degree != 0) {
			SetConsoleTextAttribute(hConsole, 4);
			wcout << L"il grado è " << structure.degree << '\n';
			SetConsoleTextAttribute(hConsole, 3);
			wcout << L"la sequenza è :\n(";
			for (int i = 0; i < size(structure.sequence) - 1; i++)
				cout << structure.sequence[i] << ", ";
			cout << structure.sequence[size(structure.sequence) - 1] << ")\n";
		}

		if (!structure.expression.empty()) {
			// se il numero è primo
			if (PrimeNumbers.is_prime[structure.number]) {
				SetConsoleTextAttribute(hConsole, 240);
				wcout << L"il numero è primo";
				SetConsoleTextAttribute(hConsole, 15);
				cout << '\n';
			}
			// altrimenti stampa scomposizione
			else {
				SetConsoleTextAttribute(hConsole, 11);
				wcout << L"la fattorizzazione è ";
				cout << structure.expression << '\n';
				if (structure.Div_number != 1) {
					SetConsoleTextAttribute(hConsole, 8);

					// stampa numero divisori
					wcout << "il numero dei divisori è ";
					cout << structure.Div_number << '\n';

					// stampa somma divisori
					wcout << "la somma dei divisori è ";
					cout << structure.Div_sum << '\n';

					// stampa prodotto divisori
					wcout << "il prodotto dei divisori è ";
					if (structure.Div_product != 1)
						cout << structure.Div_product << '\n';
					else cout << structure.Divpr << '\n';
				}
			}
		}
		SetConsoleTextAttribute(hConsole, 15);
	}
}
namespace Input
{
	static wstring GetLine() {
		int i = 0, j = 0;
		wstring vel;
		while (true) if (_kbhit()) {
			char c = _getch();
			if (c == '\r') break;

			// ignora le lettere maiuscole
			// e i caratteri non stampabili eccetto '\b'
			bool cond = c == '\b' ||
				((c < 65 || c > 90) && c > 31);

			if (cond) switch (c) {

			// '.' termina il programma
			case '.': return L".";

			// termine input
			case '\r':
				break;
				break;

			// '\b' cancella
			case '\b':
				if (i > 1) {
					vel.erase(i - 1);
					i--;
				}
				else {
					vel = L"";
					i = 0;
					j = 0;
					wcout << '\r' << wstring(10, ' ');
				}
				break;

			// ctrl + '\b' cancella tutto
			case 127:
				vel = L"";
				i = 0;
				j = 0;
				wcout << '\r' << wstring(10, ' ');
				break;
			default:
				vel += c;
				i++;
				j++;
			}

			// stampa dei caratteri immessi
			if (i > 10) {
				vel = L"";
				i = 0;
				j = 0;
				wcout << '\r' << wstring(10, ' ');
			}
			wcout << '\r' << wstring(j, ' ') << '\r' << vel;
		}
		return vel;
	}
	static wstring GetUserNum(wstring txt, int low, long long high)
	{
		using namespace EnumMod;

		setlocale(LC_ALL, "");
		switchcase option;
		long long user_num;
		wstring check;
		do {
			bool error = 1;
			bool general_error = 0;
			wcout << txt;
			check = GetLine();
			cout << '\n';
			if (check == L"." || check.empty()) return check;
			option = ConvertWStringToEnum(check);
			option = ReassigneEnum(option);
			if (option != r) return ConvertEnumToWString(option);

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

		} while (user_num < low || user_num > high);
		return to_wstring(user_num);
	}
}
namespace Primitive
{
	static bool Prime(long long number)
	{
		// se is_prime è nell'intervallo
		bool is_prime = 1;
		if (number == 1) return 0;
		else if (number < size(PrimeNumbers.is_prime))
			return PrimeNumbers.is_prime[number];

		// metodo lento ma generale
		else {
			if (number == 1) is_prime = 0;
			for (int a = 2; a < number; a++)
				if (number % a == 0) is_prime = 0;
		}
		return is_prime;
	}
	static double IntegralLog(int N) {
		double sum = 0;
		for (int x = 2; x <= N; x++)
			sum += 1 / log(x);
		return sum;
	}
	static void UserInputThread() {
		while (computing) {

			// controllo pressione tasto
			char choice = ' ';
			future <char> result =
				async(launch::async, NotBlockingGetch);
			if (result.wait_for(seconds(1)) == future_status::ready)
				choice = result.get();
			else return;

			// controllo se è 's' oppure 'S'
			if (choice == 'S' || choice == 's') {
				GlobalInterr = 1;
				interrupted = 1;
				return;
			}

			// riduzione uso della CPU
			lock_guard <mutex> lock(coutMutex);
			sleep_for(milliseconds(100));
		}
	}
	static vector_t SieveOfErastothens(long long N, bool USE_pro_bar)
	{
		using namespace Prints;

		vector <bool> is_prime(N + 1, 1);
		vector <int> primes;
		vector <int> counter;
		int SPEED = 75;
		const double BARWIDTH = 75;
		const double COEFF = 0.3;
		const int SQUARE = (int)sqrt(N) + 2;
		const double NOTPRIMESIZE = (N - IntegralLog(N)) / COEFF;
		int iter = 0;
		system("cls");

		steady_clock::time_point begin = steady_clock::now();
		if (N >= 100'000 && USE_pro_bar) {
			parallel_for(int(2), SQUARE, [&](int p) {

				// calcolo numeri primi
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
					steady_clock::time_point stop = steady_clock::now();
					SetConsoleTextAttribute(hConsole, 112);

					// stampa della barra di avanzamento
					double progress = (double)size(counter) / NOTPRIMESIZE;
					if (progress > 0.5) SPEED = 15;
					if (progress > 1) progress = 1;
					ProgressBar(progress, BARWIDTH);

					// calcolo tempo rimanente
					int time = duration_cast <milliseconds> (stop - begin).count();
					SetConsoleTextAttribute(hConsole, 15);
					double time_rem = (time / progress) * (1 - progress);
					double time_seconds = (double)time_rem / 1000;

					// calcolo cifre decimali
					stringstream stream;
					stream << fixed << setprecision(1) << time_seconds;
					string s = stream.str();
					cout << "\ntempo rimanente: " << s << " [secondi]  ";

					mtx.unlock();
				}
				iter++;
				});
			SetConsoleTextAttribute(hConsole, 15);
		}

		// calcolo senza barra di progresso
		else for (int p = 2; p < SQUARE; p++) {
			for (int i = pow(p, 2); i <= N; i += p)
				is_prime[i] = 0;
		}
		if (USE_pro_bar) cout << string(BARWIDTH + 11, '\\') << "\n\nattendere\r";

		// multithreading
		if (N >= 100'000 && USE_pro_bar) {
			thread t1([&primes, &is_prime, &N]() {
				for (long long p = 2; p < N + 1; p++)
					if (is_prime[p]) primes.push_back(p);
				lock_guard <mutex> lock(mtx);
				is_done = 1;
				cv.notify_one();
				});
			thread t2(PrintCircle);
			t1.join();
			t2.join();
		}

		else for (long long p = 2; p < N + 1; p++)
			if (is_prime[p]) primes.push_back(p);
		vector_t output = { is_prime, primes };
		return output;
	}
}
namespace Operators
{
	static vector <compost_t> DecomposeNumber(long long input)
	{
		using namespace Primitive;

		// correzione intervallo di PrimeNumbers
		if (input > PrimeNumbers.list_primes[size(PrimeNumbers.list_primes) - 1]) 
		{
			vector_t PrimeN = SieveOfErastothens(input, 0);

			// riassegnazione
			for (int i = size(PrimeNumbers.list_primes);
				i < size(PrimeN.list_primes); i++) {
				mtx.lock();
				PrimeNumbers.list_primes.push_back(PrimeN.list_primes[i]);
				mtx.unlock();
			}
		}
		int size = 0;
		int product = 1;

		// calcolo limite di approssimazione
		do {
			product *= PrimeNumbers.list_primes[size];
			size++;
		} while (product < GlobalMax);
		vector <compost_t> output;
		compost_t output_element = { 0, 1 };
		for (int i = 0; i < size; i++) output.push_back(output_element);
		int index = 0;

		// scomposizione
		for (int i = 0; pow(PrimeNumbers.list_primes[i], 2) <= input; i++) 
		{
			if (input != 1) {
				if (input % PrimeNumbers.list_primes[i] == 0) {

					// se un fattore è gia presente, incrementa l'esponente
					if (output[index].factors == PrimeNumbers.list_primes[i])
						output[index].exp++;

					// altrimenti aggiungi il fattore alla lista
					else output[index].factors = PrimeNumbers.list_primes[i];
					input /= PrimeNumbers.list_primes[i];

					// incrementa l'indice
					if (input % PrimeNumbers.list_primes[i] != 0)
						index++;
					i--;
				}
			}
		}
		// eccezione
		if (output[index].factors == input)
			output[index].exp++;
		else output[index].factors = input;

		return output;
	}
	static vector <wstring> Fractioner(wstring polinomial)
	{
		vector <wstring> monomials;
		wstring backup = polinomial;
		wstring temp;
		int parenthesis_balance = 0;
		int p_balance = 0;
		int find = 0;
		for (int i = 0; i < backup.size(); i++) {
			if (backup.at(i) == '(') parenthesis_balance++;

			// solo in caso di bilancio tra le parentesi e carattere '+'
			if ((parenthesis_balance == 0) && (backup.at(i) == '+')) {
				temp = polinomial;
				for (int finder = 0; finder < temp.size(); finder++) {

					// scomposizione in monomi
					if (find == 0) {
						if (temp.at(finder) == '(') p_balance++;
						if ((p_balance == 0) && (temp.at(finder) == '+'))
							find = finder;
						if (temp.at(finder) == ')') p_balance--;
					}
				}

				// aggiunta dei monomi alla lista
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
	static vector <int> DecomposeStrings(wstring Terminal) 
	{
		int pass = 0;
		int ciphres_element;
		vector <int> ciphres;
		for (int i = 0; i < Terminal.size(); i++) {

			// salta se pass è vero
			while (pass != 0) {
				i++;
				pass--;
			}

			// eccezioni
			if (i >= Terminal.size()) return ciphres;
			if (i == Terminal.size() - 1)
				ciphres_element = Terminal.at(i) - '0';

			// caso di seconda eccezone
			else if (i > Terminal.size() - 3) {
				if (Terminal.at(i + 1) == '0') {
					ciphres_element = 10 * (Terminal.at(i) - '0');
					pass = 1;
				}
				else ciphres_element = Terminal.at(i) - '0';
			}

			// caso con '.'
			else if (Terminal.at(i) == '.') {
				ciphres_element = 10 * (Terminal.at(i + 1) - '0')
					+ (Terminal.at(i + 2) - '0');
				pass = 2;
			}

			// caso con gli zeri
			else {
				if (Terminal.at(i + 1) == '0') {
					ciphres_element = 10 * (Terminal.at(i) - '0');
					pass = 1;
				}

				// caso comune
				else ciphres_element = Terminal.at(i) - '0';
			}

			// aggiunta
			ciphres.push_back(ciphres_element);
		}

		return ciphres;
	}
	static wstring Standardize(wstring ToEvaluate, bool NecBoundary)
	{
		int start = -1, end = -1, count = 0;
		int size_of = ToEvaluate.size();
		if (NecBoundary) {

			// cerca limiti se sono necessari
			for (int find = 0; find < ToEvaluate.size(); find++) {
				switch (ToEvaluate.at(find)) {
				case '<': start = find + 1;
					break;
				case '>': end = find;
					break;
				}
				if (end != -1) break;
			}
			ToEvaluate.erase(end);
			ToEvaluate.erase(0, start);
		}

		// altrimenti cancellali
		else for (int i = 0; i < size_of; i++) {
			if (ToEvaluate.at(count) == '<' || ToEvaluate.at(count) == '>')
				ToEvaluate.erase(count, 1);
			else count++;
		}

		// eliminazione spazi
		for (int space = ToEvaluate.size() - 1; space >= 0; space--) {
			if (ToEvaluate.at(space) == ' ' || ToEvaluate.at(space) == '\t')
				ToEvaluate.erase(space, 1);
		}

		return ToEvaluate;
	}
}
namespace Calc
{
	static wstring Cript(long long input)
	{
		using namespace Primitive;
		using namespace Operators;

		int size = 0;
		int product = 1;

		// calcolo del limite di approssimazione
		do {
			product *= PrimeNumbers.list_primes[size];
			size++;
		} while (product < GlobalMax);

		vector <compost_t> expfactors = DecomposeNumber(input);
		long long* PrimeFactors = new long long[size];
		int* exponents = new int[size];
		int factor_number = 0;
		bool when_null = 1;

		// inizializzazione della scomposizione
		for (int i = 0; i < size; i++) {
			PrimeFactors[i] = expfactors[i].factors;
			exponents[i] = expfactors[i].exp;
			if (when_null && PrimeFactors[i] == 0) {
				factor_number = i;
				when_null = 0;
			}
		}

		wstring the_string, exp_verify, exp_string, prime_exp_string;
		int prime_exp, sizestring, presence;
		long long analyse;
		bool repeat;
		wstring monomials[15];

		// per ogni fattore primo
		for (int what_factor = 0; what_factor < factor_number; what_factor++)
		{
			repeat = 0;
			presence = 0;

			// esponente
			exp_verify = to_wstring(exponents[what_factor]);
			analyse = PrimeFactors[what_factor];
			wstring part_of1 = L"(";
			wstring part_of2 = L")";

			// se l'esponente ha una cifra ed è maggiore di 1,
			if (exponents[what_factor] != 1 && exponents[what_factor] < 11) 
			{
				part_of2.append(exp_verify);
				presence = 1;
			}

			// se l'esponente ha due cifre,
			else if (exponents[what_factor] > 10) {
				part_of2.append(L".");
				part_of2.append(exp_verify);
				presence = 2;
			}

			// si esclude il caso di un esponente a tre cifre
			wstring analyse_string = to_wstring(analyse);
			the_string = part_of1 + analyse_string + part_of2;

			do {
				// caso con argomento primo
				while (Prime(analyse)) {

					// riduzione dell'argomento
					long long position = -1;
					int a = 1;
					do {
						if (PrimeNumbers.list_primes[a - 1] == analyse)
							position = a;
						a++;
					} while (position < 0);
					analyse = position;
					analyse_string = to_wstring(analyse);
					the_string.erase(0, the_string.find(')'));
					the_string = part_of1 + analyse_string + the_string;

					// temporanea eliminazione dell'esponente normale
					switch (presence) {
					case 1:
						exp_string = wstring(1, the_string.at(the_string.size() - 1));
						the_string.erase(the_string.size() - 1);
						break;
					case 2:
						exp_string = L"." + wstring(1, the_string.at(the_string.size() - 2))
							+ wstring(1, the_string.at(the_string.size() - 1));
						the_string.erase(the_string.size() - 3);
						break;
					}

					// aggiunta dell'esponente primo
					if (repeat) {
						prime_exp_string = wstring(1, the_string.at(the_string.size() - 1));
						the_string.erase(the_string.size() - 1);
						prime_exp = stoi(prime_exp_string);
						prime_exp++;
						prime_exp_string = to_wstring(prime_exp);
						if (prime_exp > 10)
							prime_exp_string = L"." + prime_exp_string;
						the_string.append(prime_exp_string);
					}

					// riaggiunta dell'esponente normale
					else the_string.append(L"1");
					if (presence > 0) the_string.append(exp_string);
					repeat = 1;
				}
				// caso con argomento composto
				if (analyse != 1 && !Prime(analyse)) {
					analyse_string = Cript(analyse);
					the_string.erase(0, the_string.find(')'));
					the_string = part_of1 + analyse_string + the_string;
					analyse = 1;
				}

			} while (analyse != 1);
			monomials[what_factor] = the_string;
		}
		delete[] PrimeFactors;
		delete[] exponents;

		// unione dei monomi
		the_string = L"";
		for (int i = 0; i < factor_number; i++)
			the_string = the_string + L"+" + monomials[i];
		the_string.erase(0, 1);

		// rimozione basi
		int* position = new int[size];
		int j = 0;
		for (int i = 0; i < (the_string.size() - 2); i++) {
			if ((the_string.at(i) == '(') && (the_string.at(i + 1) == '1')
				&& (the_string.at(i + 2) == ')')) {
				position[j] = i;
				j++;
			}
		}
		for (int k = j - 1; k >= 0; k--) the_string.erase(position[k], 3);

		// eliminazione parentesi in più
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
		delete[] position;

		return the_string;
	}
	static string FactNumber(long long input)
	{
		using namespace Operators;

		// calcolo del limite di approssimazione
		int size = 0;
		int product = 1;
		do {
			product *= PrimeNumbers.list_primes[size];
			size++;
		} while (product < GlobalMax);

		vector <compost_t> expfactors = DecomposeNumber(input);
		long long* PrimeFactors = new long long[size];
		int* exponents = new int[size];
		int factor_number = 0;
		bool when_null = 1;

		// inizializzazione della scomposizione
		for (int i = 0; i < size; i++) {
			PrimeFactors[i] = expfactors[i].factors;
			exponents[i] = expfactors[i].exp;
			if (when_null && (PrimeFactors[i] == 0)) {
				factor_number = i;
				when_null = 0;
			}
		}

		// unione dei monomi
		string output = "";
		for (int i = 0; i < factor_number; i++) {
			if (exponents[i] != 1)
				output = output + to_string(PrimeFactors[i])
				+ "^" + to_string(exponents[i]) + " * ";
			else output = output + to_string(PrimeFactors[i]) + " * ";
		}
		delete[] PrimeFactors;
		delete[] exponents;

		// rimozione della fine
		output.erase(output.size() - 3);

		return output;
	}
	static int ExecuteStrings(wstring input)
	{
		using namespace Operators;

		int size_s = 0;
		int product = 1;

		// calcolo del limite di approssimazione
		do {
			product *= PrimeNumbers.list_primes[size_s];
			size_s++;
		} while (product < GlobalMax);

		int output = 0;
		int location = 0;
		bool presence = 1;
		int* values = new int[size_s];
		for (int i = 0; i < input.size(); i++)
			if (input.at(i) == '.') input.erase(i, 1);
		vector <wstring> monomials = Fractioner(input);

		for (int i = 0; i < size(monomials); i++) 
		{
			// caso con le parentesi
			if (monomials[i].at(0) == '(') {

				// acquisizione dati
				for (int j = monomials[i].size() - 1; j >= 0; j--) {
					if ((presence) && (monomials[i].at(j) == ')')) {
						presence = 0;
						location = j;
					}
				}

				// calcolo risultato
				wstring temp = monomials[i];
				temp.erase(location);
				temp.erase(0, 1);
				monomials[i].erase(0, location + 1);
				values[i] = ExecuteStrings(temp) * (stoi(monomials[i]));
			}

			// caso senza parentesi
			else values[i] = stoi(monomials[i]);
			presence = 1;
		}

		// somma dei monomi
		for (int end = 0; end < size(monomials); end++) output += values[end];

		return output;
	}
	static divisor_t DivisorCalculator(string factor)
	{
		divisor_t output = { 1, 1, 1, "" };
		vector <string> monomials;
		vector <long long> values;
		vector <int> exponents;
		bool pow_presence = 0;

		// scompozizione in monomi
		for (int i = factor.size() - 1; i >= 0; i--) {
			if (factor.at(i) == '*') {
				string backup = factor;
				backup.erase(0, i + 2);
				if (backup.at(backup.size() - 1) == ' ')
					backup.erase(backup.size() - 1);
				monomials.push_back(backup);
				factor.erase(i);
			}
		}

		// eccezione
		if (factor.at(factor.size() - 1) == ' ')
			factor.erase(factor.size() - 1);
		monomials.push_back(factor);

		// ricavo della scomposizione
		for (int i = 0; i < size(monomials); i++) {
			long long value = -1;
			int exp = 1;
			for (int j = 1; j < monomials[i].size(); j++) {

				// caso con le potenze
				if (monomials[i].at(j) == '^') {
					string first = monomials[i];
					string second = monomials[i];
					first.erase(j);
					second.erase(0, j + 1);
					value = stoi(first);
					exp = stoi(second);
					pow_presence = 1;
				}

				// caso senza potenze
				if (!pow_presence) value = stoi(monomials[i]);
			}
			if (value == -1) value = stoi(monomials[i]);
			values.push_back(value);
			exponents.push_back(exp);
		}

		// calcolo del numero dei divisori
		for (int i = 0; i < size(monomials); i++)
			output.DivNumber *= exponents[i] + 1;

		// calcolo del numero risultato
		// e della sua somma dei divisori
		int x = 1;
		for (int i = 0; i < size(monomials); i++) {
			long long num = -1 + pow(values[i], exponents[i] + 1);
			long long den = values[i] - 1;
			output.DivSum *= (num / den);
			x *= pow(values[i], exponents[i]);
		}

		// eccezione
		if (output.DivSum < 0) output.DivSum = -1;

		// calcolo del prodotto dei divisori
		if (output.DivNumber > 0) {
			double out = (double) output.DivNumber / 2;
			int y = pow(x, out);
			if (y > 0) output.DivProduct = y;

			// caso di overflow
			else if (output.DivNumber % 2 == 0)
				output.Div_pr = to_string(x) + "^" + to_string((int)out);

			// caso di un quadrato perfetto pari
			else output.Div_pr = to_string((int)sqrt(x)) 
				+ "^" + to_string((int)(out * 2));
		}

		// eccezione
		else {
			output.DivNumber = -1;
			output.DivProduct = -1;
		}

		return output;
	}
}
namespace Execute
{
	static data_t ExecuteSimpledeg(long long input) {
		using namespace Calc;

		data_t output = { input, Cript(input), 0, {}, "", 1, 1, 1, "" };
		return output;
	}
	static data_t ExecuteDegree(long long input) {
		using namespace Calc;

		data_t output = { input, Cript(input), 0, {}, "", 1, 1, 1, "" };
		int counter = 0;
		int copy = input;

		// iterazione per ottenere grado e sequenza
		do {
			output.sequence.push_back(copy);
			copy = ExecuteStrings(Cript(copy));
			counter++;
			if (copy < 4) output.degree = counter + copy;
		} while (copy != 1);

		output.sequence.push_back(1);
		copy = input;
		return output;
	}
	static data_t ExecuteSimpleFact(long long input) {
		using namespace Calc;

		data_t output = { input, L"", 0, {}, FactNumber(input), 1, 1, 1, "" };
		return output;
	}
	static data_t ExecuteFactor(long long input) {
		using namespace Calc;

		data_t output = { input, L"", 0, {}, "", 1, 1, 1, "" };
		output.expression = FactNumber(input);
		divisor_t D = DivisorCalculator(output.expression);
		output.Div_product = D.DivProduct;
		output.Div_number = D.DivNumber;
		output.Div_sum = D.DivSum;
		output.Divpr = D.Div_pr;
		return output;
	}
	static data_t ExecuteSimpleDF(long long input) {
		using namespace Calc;

		data_t output = { input, Cript(input), 0,
			{}, FactNumber(input), 1, 1, 1, "" };
		return output;
	}
	static data_t ExecuteDegFactor(long long input) {
		data_t A = ExecuteDegree(input);
		data_t B = ExecuteFactor(input);
		data_t output = { input, A.code, A.degree, A.sequence,
			B.expression, B.Div_number, B.Div_sum, B.Div_product, B.Divpr };
		return output;
	}
}
namespace Convalid
{
	static wstring SyntaxValidator(wstring ToEvaluate, bool NecBoundary)
	{
		using namespace Operators;

		if (ToEvaluate == L"f") return L"";
		vector <wstring> mono;
		string charsAllowed = "0123456789+(_).";
		bool local_error = 1, boolean = 1, stable = 0;
		int start = -1, end = -1, parenthesis_balance = 0;
		int size_of = ToEvaluate.size(), count = 0;

		// ricerca dei limiti se sono necessari
		if (NecBoundary) {
			for (int find = 0; find < size_of; find++) {
				switch (ToEvaluate.at(find)) {
				case '<': start = find + 1;
					break;
				case '>': end = find;
					break;
				}
				if (end != -1) break;
			}
			if (start == -1 || end == -1) return L"NO_BOUNDARY";
			if (end < start) return L"BOUNDARY_INVERSION";
			ToEvaluate.erase(end);
			ToEvaluate.erase(0, start);
		}

		// rimozione altrimenti
		else for (int i = 0; i < size_of; i++) {
			if (ToEvaluate.at(count) == '<' || ToEvaluate.at(count) == '>')
				ToEvaluate.erase(count, 1);
			else count++;
		}

		// eliminazione degli spazi e dei tab
		for (int space = ToEvaluate.size() - 1; space >= 0; space--) {
			if (ToEvaluate.at(space) == ' ' || ToEvaluate.at(space) == '\t')
				ToEvaluate.erase(space, 1);
		}

		// ricerca del bilancio tra le parentesi
		for (int i = 0; i < ToEvaluate.size(); i++) {
			if (ToEvaluate.at(i) == '(') {
				parenthesis_balance++;
				stable++;
			}
			if (ToEvaluate.at(i) == ')') parenthesis_balance--;
		}
		if (parenthesis_balance != 0) return L"UNBALANCED_BRACKETS";

		// se la stringa è vuota
		if (ToEvaluate.empty()) return L"EMPTY_IMPUT";

		// se la stringa contiene caratteri non ammessi
		wregex unallowed_chars(L"[^\\d+()._]");
		if (regex_search(ToEvaluate, unallowed_chars))
			return L"UNALLOWED_CHARACTERS";

		// controllo sugli estremi
		if (ToEvaluate.at(0) == '+') return L"NO_START_STRING";
		if (ToEvaluate.at(0) == '0') return L"NULL_DIGIT";
		if (ToEvaluate.at(0) == ')') return L"INVERTED_BRACKETS";
		if (ToEvaluate.at(ToEvaluate.size() - 1) == '+')
			return L"NO_END_STRING";

		// controllo sulla non consecutività dei '+'
		wregex no_monomial_(L"\\+{2,}");
		if (regex_search(ToEvaluate, no_monomial_))
			return L"MISSING_MONOMIAL";

		// controlli sugli zeri
		wregex cons_null_digits(L"0{2,}");
		if (regex_search(ToEvaluate, cons_null_digits))
			return L"CONSECUTIVE_NULL_DIGITS";
		wregex excep_no_digits(L"\\.");
		wregex no_digits(L"\\d\\.\\d{2,}");
		if (regex_search(ToEvaluate, excep_no_digits)) {
			if (!regex_search(ToEvaluate, no_digits))
				return L"MISSING_DIGITS";
		}
		wregex s_null_digits(L"[\\r\\D]0");
		if (regex_search(ToEvaluate, s_null_digits))
			return L"NULL_DIGITS";

		mono = Fractioner(ToEvaluate);

		// per ogni monomio
		for (int monomial = 0; monomial < size(mono); monomial++) {
			int stackfinder = -1, stickfinder = -1, finder = -1;
			bool stop = 0, pass = 0;
			int res = 0;
			vector <int> min_ciphres, max_ciphres;
			vector <int> ciphr_min, ciphr_max;
			wstring min, max;
			wstring stack = mono[monomial];

			// per ogni secondo monomio
			for (int second = 1; second < size(mono); second++) {
				if (monomial != second) {
					if (mono[monomial] == mono[second]) return L"1";
					wstring stick = mono[second];

					// paragone tra le dimensioni dei monomi
					if (stack.size() < stick.size()) {
						min = stack;
						max = stick;
					} else {
						min = stick;
						max = stack;
					}

					// caso con le parentesi
					if (stack.at(0) == '(' || stick.at(0) == ')') {

						// ricerca delle parentesi
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

						// caso con solo un monomio dotato di parentesi
						if (stackfinder * stickfinder < 0) {
							if (stackfinder > 0) finder = stackfinder;
							else finder = stickfinder;
						}

						// caso con i monomi corrispondenti
						else if (stickfinder == stackfinder) {
							finder = stackfinder;
							for (int l = 0; l <= finder + 1; l++) {
								if (l < min.size()) {
									if (stick.at(l) != stack.at(l))
										stop = 1;
								}
							}
							wstring min_backup = min;
							wstring max_backup = max;
							min_backup.erase(0, finder + 2);
							max_backup.erase(0, finder + 2);
							min_ciphres = DecomposeStrings(min_backup);
							max_ciphres = DecomposeStrings(max_backup);
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

						// paragone tra il numero dei fattori
						min_ciphres = DecomposeStrings(min);
						max_ciphres = DecomposeStrings(max);
						if (size(min_ciphres) < size(max_ciphres)) {
							ciphr_min = min_ciphres;
							ciphr_max = max_ciphres;
						} else {
							ciphr_min = max_ciphres;
							ciphr_max = min_ciphres;
						}

						// conta delle ripetizioni
						for (int l = 0; l < size(ciphr_min); l++) {
							if (!stop && ciphr_min[l] == ciphr_max[l]) {
								res++;
								if (ciphr_min[l] != ciphr_max[l])
									stop = 1;
							}
							else stop = 1;
						}
					}

					if (res % 2 == 1) return L"2";
				}
			}

			// // controlli sugli oggetti adiacenti alle parentesi
			boolean = 1;
			for (int j = stack.size() - 1; j > 0; j--) {
				if (boolean && stack.at(j) == ')') {
					finder = j - 1;
					boolean = 0;
				}
			}
			if (stack.at(stack.size() - 1) == ')')
				return L"MISSING_OBJECT";
			if (stack.at(stack.size() - 1) == '(')
				return L"INVERTED_BRACKETS";
			if (stack.at(0) == '(') {
				local_error = 1;

				// controllo sulla necessità delle parentesi
				for (int checkplus = 1; checkplus < finder; checkplus++) {
					if (stack.at(checkplus) == '+') local_error = 0;
				}
				if (local_error) return L"USELESS_BRACKETS";

				stack.erase(0, 1);
				stack.erase(finder);
				wstring message = SyntaxValidator(stack, 0);
				if (!message.empty()) return message;
			}
			else if (mono[monomial].at(0) == ')') return L"INVERTED_BRACKETS";
			else for (int check = 1; check < mono[monomial].size(); check++) {
				if (mono[monomial].at(check) == '(') return L"WRONG_OBJECT";
				if (mono[monomial].at(check) == ')') return L"WRONG_OBJECT";
			}
			// //
		}

		return L"";
	}
	static long long NumberConverter(long long root, wstring M)
	{
		using namespace Operators;

		bool WhichWay = 1, XOutOfRange = 0;
		bool UselessExponent = 0, pass = 0;
		bool XSubscriptOutOfRange = 0;
		int sizeP = size(PrimeNumbers.list_primes), nums;
		vector <int> ciphres = DecomposeStrings(M);

		// per ogni cifra
		for (int iter = 0; iter < size(ciphres); iter++) {

			WhichWay = !WhichWay;
			nums = ciphres[iter];

			// caso esponente
			if (!XOutOfRange && WhichWay) {
				UselessExponent = nums == 1;
				root = pow(root, nums);
			}

			// caso esponente primo
			else {
				do {
					if (!XOutOfRange && root < sizeP) {
						if (root > 0)
							root = PrimeNumbers.list_primes[root - 1];
						else XSubscriptOutOfRange = 1;
						nums--;
					}
					else XOutOfRange = 1;
				} while (XSubscriptOutOfRange != 1 && XOutOfRange != 1 && nums != 0);
			}
		}

		// eccezioni
		if (XSubscriptOutOfRange) return -3;
		if (UselessExponent) return -2;
		if (XOutOfRange) return -1;

		return root;
	}
	static long long StringConverter(wstring ToEvaluate)
	{
		using namespace Operators;

		long long integer = 1;
		wstring backup, back;
		vector <wstring> mono = Fractioner(ToEvaluate);
		int sizeP = size(PrimeNumbers.list_primes);
		int finder = -1;
		bool boolean = 1;

		// per ogni monomio
		for (int monomial = 0; monomial < size(mono); monomial++) {
			wstring M = mono[monomial];
			long long root;
			bool WhichWay = 0;
			if (M.at(0) != '(') root = NumberConverter(1, M);
			else {

				// ricerca preliminare
				boolean = 1;
				for (int i = M.size() - 1; i > 0; i--) {
					if (boolean && M.at(i) == ')') {
						finder = i + 1;
						boolean = 0;
					}
				}

				// calcolo preciso
				back = M;
				backup = M;
				backup.erase(0, finder);
				back.erase(finder - 1);
				back.erase(0, 1);
				root = StringConverter(back);
				root = NumberConverter(root, backup);
			}
			if (root < 0) return root; // eccezione
			else integer *= root; // caso comune
		}

		return integer;
	}
	static void CodeConverter(wstring ToEvaluate
		, wstring message, bool ShowErrors, bool NecBoundary)
	{
		using namespace Operators;
		using namespace Calc;

		setlocale(LC_ALL, "");
		long long number;
		if (ToEvaluate != L"f") {

			ToEvaluate = Standardize(ToEvaluate, NecBoundary);
			number = StringConverter(ToEvaluate);

			// caso normale
			if (ShowErrors || number > 0) {
				SetConsoleTextAttribute(hConsole, 11);
				wcout << "codice <" << ToEvaluate << "> :\n";
				SetConsoleTextAttribute(hConsole, 15);
			}

			// caso con overflow interno
			if (number < -2 && ShowErrors) {
				SetConsoleTextAttribute(hConsole, 12);
				cout << "ERR[413]: X_SUBSCRIPT_OUT_OF_RANGE\n";
				SetConsoleTextAttribute(hConsole, 15);
			}

			// caso di comune overflow
			if (number == -1 && ShowErrors) {
				SetConsoleTextAttribute(hConsole, 12);
				cout << "ERR[413]: X_OUT_OF_RANGE\n";
				SetConsoleTextAttribute(hConsole, 15);
			}

			// caso errato per esponente inutile
			if (number == -2 && ShowErrors) {
				SetConsoleTextAttribute(hConsole, 6);
				cout << "ERR[413]: USELESS_EXPONENT\n";
				SetConsoleTextAttribute(hConsole, 15);
			}

			// caso errato con correzione
			if (!message.empty() && ShowErrors && number > 0) {
				cout << "ERR[400]: ";
				message == L"1" ? cout << "EQUAL_MONOMIALS\n" : cout << "SIMILIAR_MONOMIALS\n";
				SetConsoleTextAttribute(hConsole, 2);
				wcout << "codice corretto: <" << Cript(number) << ">\n";
				SetConsoleTextAttribute(hConsole, 15);
			}

			// caso con errori nascosti per scelta utente
			if (number > 0) {
				cout << "il numero corrispondente e' ";
				SetConsoleTextAttribute(hConsole, 4);
				cout << number << '\n';
				SetConsoleTextAttribute(hConsole, 15);
			}

		}
	}
	static void LongComputation(wstring ToEvaluate
		, wstring message, bool ShowErrors, bool NecBoundary)
	{
		computing = 1;
		interrupted = 0;

		// conta dei caratteri '_' e archivio della posizione
		wstring backup = ToEvaluate;
		int counter = 0;
		vector <int> pos;
		for (int i = 0; i < size(ToEvaluate); i++) {
			if (ToEvaluate.at(i) == '_') {
				pos.push_back(i);
				counter++;
			}
		}

		// caso di stringa univoca
		lock_guard <mutex> lock(coutMutex);
		if (counter == 0) CodeConverter(ToEvaluate, message, ShowErrors, NecBoundary);

		// caso di stringa ripetuta
		else for (int i = 0; i < pow(10, counter); i++) {
			string j = to_string(i);
			int zero_counter = counter - j.size();
			for (int k = 0; k < zero_counter; k++) j = "0" + j;
			for (int k = 0; k < j.size(); k++)
				backup.replace(pos[k], 1, wstring(1, j.at(k)));
			message = SyntaxValidator(backup, NecBoundary);

			// eventuale stampa degli errori
			if (message.size() > 1 && ShowErrors) {
				SetConsoleTextAttribute(hConsole, 11);
				wcout << "codice " << backup << " :\n";
				SetConsoleTextAttribute(hConsole, 4);
				wcout << "ERR[404]: " << message << '\n';
				SetConsoleTextAttribute(hConsole, 15);
			}
			else CodeConverter(backup, message, ShowErrors, NecBoundary);
			if (interrupted) break;
		}
		computing = 0;
	}
}
namespace Evaluator
{
	static switchcase CodeToNumber()
	{
		using namespace EnumMod;
		using namespace Primitive;
		using namespace Operators;
		using namespace Convalid;

		// scelta
		setlocale(LC_ALL, "");
		wstring ToEvaluate, message;
		switchcase option;
		bool ShowErrors = 1, NecessaryBoundary = 1;
		cout << "il programma traduce una stringa di codice\n";
		cout << "il codice non deve avere errori o saranno segnalati\n";
		cout << "il codice deve essere compreso tra <>\n";
		cout << "se sono presenti piu' caratteri '<', '>',\n";
		cout << "verranno considerati solo quelli che compaiono prima\n";
		cout << "unici caratteri non numerici ammessi: '(', ')', '+', '.' \n";
		SetConsoleTextAttribute(hConsole, 9);
		cout << "si indichino le cifre incognite con caratteri '_'\n";
		cout << "aggiungendo '$' come primo carattere\n";
		cout << "oppure '\\' o '/' senza <> non vengono mostrati gli errori\n\n";
		SetConsoleTextAttribute(hConsole, 15);

		while (true) {
			do {

				// input e controllo
				cout << "inserire una stringa (f = fine input)\n";
				cout << "per fermare il calcolo premere s\\S\n";
				getline(wcin, ToEvaluate);
				option = ConvertWStringToEnum(ToEvaluate);
				option = ReassigneEnum(option);
				if (option != r) {
					system("cls");
					LPCWSTR title = ToEvaluate.c_str();
					SetConsoleTitle(title);
					return option;
				}
				if (ToEvaluate == L".") return rnd;

				// ammissione errori
				if (!ToEvaluate.empty()) {
					NecessaryBoundary = ToEvaluate.at(0) != '\\' && ToEvaluate.at(0) != '/';
					ShowErrors = ToEvaluate.at(0) != '$' && NecessaryBoundary;
					if (!NecessaryBoundary) ToEvaluate.erase(0, 1);
				}

				// individuazione degli errori
				message = SyntaxValidator(ToEvaluate, NecessaryBoundary);
				if (message.size() > 1) {
					lock_guard <mutex> lock(coutMutex);
					SetConsoleTextAttribute(hConsole, 4);
					wcout << "ERR[404]: " << message << '\n';
					SetConsoleTextAttribute(hConsole, 15);
				}

			} while (message.size() > 1);

			// caso di fine input
			if (ToEvaluate == L"f") return r;

			// aggiustamento della stringa immessa
			if (NecessaryBoundary) ToEvaluate = L"<" + Standardize(ToEvaluate, 1) + L">";
			else ToEvaluate = Standardize(ToEvaluate, 0);
			
			// multithreading per consentire l'eventuale interruzione
			thread ComputationThread([=]() {
				LongComputation(ToEvaluate, message,
				ShowErrors, NecessaryBoundary);
				});
			thread InputThread(UserInputThread);

			ComputationThread.join();
			interrupted = 1;
			InputThread.join();

			if (GlobalInterr) {
				lock_guard <mutex> lock(coutMutex);
				SetConsoleTextAttribute(hConsole, 15);
				cout << '\n';
				SetConsoleTextAttribute(hConsole, 64);
				cout << "CALCOLO INTERROTTO!!!";
				SetConsoleTextAttribute(hConsole, 15);
				cout << "\n\n";
			}
		}
	}
	static switchcase Repeater(string message, data_t CPU(long long input)) 
	{
		using namespace EnumMod;
		using namespace Prints;
		using Input::GetUserNum;

		setlocale(LC_ALL, "");
		wstring n_ = to_wstring(GlobalMax), Input;
		switchcase option;
		long long input;
		data_t result;
		SetConsoleTextAttribute(hConsole, 14);
		cout << message << "\n\n";
		SetConsoleTextAttribute(hConsole, 15);
		do {

			// input e controllo
			SetConsoleTextAttribute(hConsole, 14);
			wstring txt = L"inserire un numero tra 2 e " + n_ + L" (1 = fine input)\n";
			SetConsoleTextAttribute(hConsole, 15);
			do Input = GetUserNum(txt, 1, GlobalMax);
			while (Input.empty());
			if (Input == L".") return rnd;
			option = ConvertWStringToEnum(Input);
			option = ReassigneEnum(option);
			if (option != r) {
				system("cls");
				LPCWSTR title = Input.c_str();
				SetConsoleTitle(title);
				return option;
			}
			input = stoull(Input);

			// calcolo e stampa dei risultati
			if (input != 1) {
				result = CPU(input);
				DataPrintF(result);
			}

		} while (input != 1);

		return r;
	}
	static switchcase Loop(string message, data_t CPU(long long input))
	{
		using namespace EnumMod;
		using Sort::HeapSort;
		using namespace Prints;
		using Input::GetUserNum;

		setlocale(LC_ALL, "");
		wstring n_ = to_wstring(GlobalMax), Input;
		wstring txt;
		switchcase option;
		vector <data_t> data;
		const double Barwidth = 60;
		long long input;

		cout << "debug::\n\n";
		SetConsoleTextAttribute(hConsole, 14);
		cout << message << '\n';
		wcout << "gli estremi dell'intervallo devono essere compresi tra 1 e " << n_ << "\n\n";

		// input e controllo valore iniziale
		SetConsoleTextAttribute(hConsole, 15);
		txt = L"inserisci il valore di inizio della ricerca\n";
		do Input = GetUserNum(txt, 1, GlobalMax);
		while (Input.empty());
		if (Input == L".") return rnd;
		option = ConvertWStringToEnum(Input);
		option = ReassigneEnum(option);
		if (option != r) {
			system("cls");
			LPCWSTR title = Input.c_str();
			SetConsoleTitle(title);
			return option;
		}
		long long lower_bound = stoull(Input) + 1;
		
		// input e controllo valore finale
		txt = L"inserisci il valore finale della ricerca\n";
		do Input = GetUserNum(txt, 1, GlobalMax);
		while (Input.empty());
		if (Input == L".") return rnd;
		option = ConvertWStringToEnum(Input);
		option = ReassigneEnum(option);
		if (option != r) {
			system("cls");
			LPCWSTR title = Input.c_str();
			SetConsoleTitle(title);
			return option;
		}
		long long upper_bound = stoull(Input) + 1;

		if (upper_bound < lower_bound) swap(lower_bound, upper_bound);
		long long datalenght = upper_bound - lower_bound;

		// calcolo e parallelizzazione
		system("cls");
		SetConsoleCursorInfo(hConsole, &cursorInfo);
		if (datalenght >= 1000) {
			int iter = 0;
			atomic <double> Progress = 0;
			steady_clock::time_point begin = steady_clock::now();
			parallel_for(long long(lower_bound), upper_bound, [&](long long set) {

				data_t data_element = CPU(set);
				mtx.lock();
				data.push_back(data_element);
				if (iter % 200 == 0) {

					// stampa della barra di avanzamento
					steady_clock::time_point stop = steady_clock::now();
					SetConsoleTextAttribute(hConsole, 112);
					double Progress = (double)size(data) / datalenght;
					ProgressBar(Progress, Barwidth);

					// calcolo del tempo rimanente
					int time = duration_cast <milliseconds> (stop - begin).count();
					SetConsoleTextAttribute(hConsole, 15);
					double time_rem = (time / Progress) * (1 - Progress);
					double time_seconds = (double)time_rem / 1000;

					// calcolo cifre decimali
					stringstream stream;
					stream << fixed << setprecision(1) << time_seconds;
					string s = stream.str();
					cout << "\ntempo rimanente: " << s << " [secondi] ";
				}
				iter++;
				mtx.unlock();

				});
			cout << string(Barwidth + 11, '\\') << '\n';

			// multithreading
			thread t1([&data]() {
				data = HeapSort(data);
				lock_guard <mutex> lock(mtx);
				is_done = 1;
				cv.notify_one();
				});
			thread t2(PrintCircle);
			t2.join();
			t1.join();
			system("cls");

			// stampa risultati
			SetConsoleCursorInfo(hConsole, &cursor);
			for (int x = 0; x < size(data); ++x) DataPrintF(data[x]);
			steady_clock::time_point end = steady_clock::now();
			cout << "\ntempo di calcolo = " << duration_cast <milliseconds> (end - begin).count()
				<< "[ms]\n\n";
		}

		// caso con intervallo di dimensioni minori
		else {
			steady_clock::time_point begin = steady_clock::now();
			for (long long set = lower_bound; set < upper_bound; set++) {
				data_t data_element = CPU(set);
				DataPrintF(data_element);
			}
			steady_clock::time_point end = steady_clock::now();
			cout << "\ntempo di calcolo = " << duration_cast <milliseconds> (end - begin).count()
				<< "[ms]\n\n\n";
		}

		// termine
		char null;
		cout << "premere un tasto per continuare\t\t";
		null = _getch();
		if (null == '.') return rnd;
		else return r;
	}
}

int main()
{
	using namespace Input;
	using Primitive::SieveOfErastothens;
	using namespace EnumMod;
	using namespace Execute;
	using namespace Evaluator;

	// scelta
	setlocale(LC_ALL, "");
	string simpledeg = "il programma calcola solo la codifica di un intero";
	string simplefact = "il programma calcola solo la fattorizzazione di un intero";
	string def_sct = "il programma calcola solo codifica e fattorizzazione";
	string desimpledeg = "il programma calcola solo la codifica di una serie";
	string desimplefact = "il programma calcola solo la fattorizzazione di una serie";
	string defact_message = "il programma calcola la fattorizzazione di una serie";
	defact_message.append("\ne numero, somma e prodotto dei divisori");
	string deg_message = "il programma calcola codice, sequenza e grado di una serie";
	string fact_message = "il programma calcola la fattorizzazione di un intero";
	fact_message.append("\ne numero, somma e prodotto dei divisori");
	string message = "il programma calcola codice, sequenza e grado di un intero";
	string AllMessage = "il programma calcola \"tutti\" i dati di alcuni interi";
	wstring vel = L"";
	wstring text;
	switchcase option;

	bool start = 1;
	bool lock_prime_input = 0;
	long long global = 1;
	while (true) 
	{
		bool stop = 0;
		bool skip = 1;
		bool redo = 0;

		if (!lock_prime_input) {
			do {

				// output e input controllato
				redo = 0;
				system("cls");
				SetConsoleTitle(TEXT("START"));
				SetConsoleTextAttribute(hConsole, 10);
				cout << "CALCOLATRICE::\n\n";
				text = L"fino a quale numero cercare i numeri primi?\n";
				text.append(L"un limite più alto comporta un tempo di attesa più lungo\n");
				text.append(L"ES.: 22'500'000 = 1 minuto di attesa circa\n");
				wstring G = GetUserNum(text, 0, GLOBAL_CAP);
				if (ConvertWStringToEnum(G) != r) redo = 1;
				else if (G.empty()) redo = 1;

				// termine programma
				else if (G == L".") {
					system("cls");
					SetConsoleTextAttribute(hConsole, 4);
					return 0;
				}

				// casi 0 e 1
				else global = stoi(G);
				if (global == 1) redo = 1;
				if (global == 0) {
					lock_prime_input = 1;
					if (start) redo = 1;
				}
			} while (redo);
			SetConsoleTextAttribute(hConsole, 15);

			// stampa del tempo
			if (global != 0 || start) {
				steady_clock::time_point begin = steady_clock::now();
				GlobalMax = global;
				SetConsoleCursorInfo(hConsole, &cursorInfo);
				PrimeNumbers = SieveOfErastothens(GlobalMax, 1);
				steady_clock::time_point end = steady_clock::now();
				int delta = duration_cast <milliseconds> (end - begin).count();
				int exception_delta = duration_cast <microseconds> (end - begin).count();
				system("cls");
				SetConsoleTextAttribute(hConsole, 6);
				SetConsoleCursorPosition(hConsole, { 20, 10 });
				if (delta <= 10) {
					cout << "tempo di calcolo numeri primi = "
						<< exception_delta << " microsecondi\n\n";
				}
				else if (delta > 10'000 && delta <= 600'000) {
					delta = delta / 1000;
					cout << "tempo di calcolo numeri primi = " << delta << " secondi\n\n";
				}
				else if (delta > 600'000) {
					delta = delta / 60'000;
					cout << "tempo di calcolo numeri primi = " << delta << " minuti\n\n";
				}
				else cout << "tempo di calcolo numeri primi = " << delta << " millisecondi\n\n";
				start = 0;
				sleep_for(seconds(1));
				SetConsoleTextAttribute(hConsole, 15);
				SetConsoleCursorInfo(hConsole, &cursor);
			}
		}

		// scelta
		system("cls");
		SetConsoleTitle(TEXT("switchcase scegli le opzioni"));
		cout << "scegli opzioni::\v";
		SetConsoleTextAttribute(hConsole, 4);
		cout << "se stringa di un carattere:\n";
		cout << "\t'0' = blocca input numeri primi ~[~sempre]\n";
		cout << "\t'1' = sblocca input numeri primi\n";
		cout << "\t'.' = fine programma [sempre]\v";
		SetConsoleTextAttribute(hConsole, 9);
		cout << "altrimenti:\n";
		cout << "\t\"rnd\" = casuale\n";
		cout << "\t\"ctn\" = da codice a numero\v";
		SetConsoleTextAttribute(hConsole, 11);
		cout << "oppure:\n";
		cout << "primo carattere:\n";
		cout << "\t'c' = calcolo\n";
		cout << "\t'd' = debug\n";
		cout << "caratteri seguenti:\n";
		cout << "\t'c' = solo codifica\n";
		cout << "\t\"cc\" = codifica, sequenza e grado\n";
		cout << "\t'f' = scomposizione in fattori primi\n";
		cout << "\t\"ff\" = fattoizzazione e dati dei divisori\n";
		cout << "\t\"cf\" = codifica e fattorizzazione\n";
		cout << "\t\"t\" = tutti i dati\n";
		cout << "selezionando più operazioni, il tempo di calcolo aumenta\v";

		SetConsoleTextAttribute(hConsole, 15);
		vel = GetLine();
		option = ConvertWStringToEnum(vel);
		cout << '\n';
		do {

			// input numeri primi
			if (vel.size() == 1) {
				skip = 0;
				switch (vel.at(0)) {
				case '0':
					lock_prime_input = 1;
					cout << "\ninput numeri primi bloccato\n";
					break;
				case '1':
					lock_prime_input = 0;
					cout << "\ninput numeri primi sbloccato\n";
					break;
				case '.':
					system("cls");
					SetConsoleTextAttribute(hConsole, 4);
					return 0;
					break;
				default: vel += ' ';
				}
			}

			// caso input non assegnato correttamente
			if (option == r) do {
				skip = 0;
				cout << "scegli opzioni:: (...)\n";
				vel = GetLine();
				if (vel.size() == 1) {
					stop = vel.at(0) != '0'
						&& vel.at(0) != '1' && vel.at(0) != '.';
				}
				else {
					option = ConvertWStringToEnum(vel);
					stop = option == r;
					skip = option != r;
				}
				if (stop) {
					cout << '\n';
					SetConsoleTextAttribute(hConsole, 64);
					cout << "NON CORRETTO !!";
					SetConsoleTextAttribute(hConsole, 4);
					cout << '\n';
				}
			} while (stop);
			SetConsoleTextAttribute(hConsole, 15);
			stop = 0;
		} while (!skip);
		cout << "\n\n";
		option = ReassigneEnum(option);
		wstring wtitle = ConvertEnumToWString(option);

		// cambio titolo
		system("cls");
		LPCWSTR title = wtitle.c_str();
		SetConsoleTitle(title);
		
		// scelta funzioni e opzioni
		do {
			switch (option) 
			{
			case cc: option = Repeater(simpledeg, ExecuteSimpledeg);
				break;
			case ccc: option = Repeater(message, ExecuteDegree);
				break;
			case cf: option = Repeater(simplefact, ExecuteSimpleFact);
				break;
			case cff: option = Repeater(fact_message, ExecuteFactor);
				break;
			case ccf: option = Repeater(def_sct, ExecuteSimpleDF);
				break;
			case ct: option = Repeater(AllMessage, ExecuteDegFactor);
				break;
			case dc: option = Loop(desimpledeg, ExecuteSimpledeg);
				break;
			case dcc: option = Loop(deg_message, ExecuteDegree);
				break;
			case df: option = Loop(desimplefact, ExecuteSimpleFact);
				break;
			case dff: option = Loop(defact_message, ExecuteFactor);
				break;
			case dcf: option = Loop(def_sct, ExecuteSimpleDF);
				break;
			case dt: option = Loop(AllMessage, ExecuteDegFactor);
				break;
			case ctn: option = CodeToNumber();
				break;
			}
			if (option == rnd) {
				system("cls");
				SetConsoleTextAttribute(hConsole, 4);
				return 0;
			}
		} while (option != r);
	}
}
// program_END