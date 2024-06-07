// program_START
#pragma once
#pragma optimize("", on)

// Descrizione programma ::
	/*                                                        |
	*  Strings ZP[4.1].cpp: il programma calcola singola e\o  |
	*  doppia scomposizione di alcuni interi in una stringa   |
	*  o il contrario, i numeri primi e scompone anche i      |
	*  polinomi e le frazioni algebriche                      |
	*/

// macro
#define _USE_MATH_DEFINES
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

// inclusioni
#include <chrono> // per le misurazioni di tempo
#include <cmath> // per i calcoli
#include <condition_variable> // per il multithreading
#include <conio.h> // per l'input avanzato
#include <deque>
#include <iomanip>
#include <iostream> // per l'output
#include <new> // per nothrow
#include <numeric> // per l'MCD
#include <ppl.h> // per la parallelizzazione
#include <queue>
#include <random> // per i generatori casuali
#include <regex> // per la convalidazione
#include <sstream>
#include <string>
#include <thread> // per il multithreading
#include <unordered_map> // per la conversione degli enum
#include <vector>
#include <Windows.h> // per hConsole

// namespace globali
using namespace std;
using namespace chrono;
using Concurrency::parallel_for;
using this_thread::sleep_for;

// oggetti windows
HANDLE hConsole { 
	GetStdHandle(STD_OUTPUT_HANDLE)
};
CONSOLE_CURSOR_INFO cursorInfo { 10, FALSE };
CONSOLE_CURSOR_INFO cursor { 10, TRUE };
CONSOLE_SCREEN_BUFFER_INFO csbi;

// variabili globali
const long long GLOBAL_CAP(pow(10, 10));
long long GlobalMax(pow(10, 10));
bool HAS_BEEN_PRINTED(0);

// strutture
struct MONOMIAL {
	int degree;
	int coefficient;
	bool operator == (const MONOMIAL &other) const {
		return coefficient == other.coefficient and
			degree == other.degree;
	}
};
struct Console {
	wstring Text;
	int Attribute;
};
typedef struct {
	vector <bool> is_prime;
	vector <int> list_primes;
} vector_t;
vector <Console> ConsoleText;
vector_t PrimeNumbers;

// variabili globali e atomiche
atomic <bool> GlobalInterr(0);
atomic <bool> interrupted(0);
atomic <bool> computing(0);
atomic <bool> is_done(0);
condition_variable cv, Cv;
mutex CoutMutex, mtx;
COORD Min { 25, 15 };

// strutture
struct compost {
	int factors;
	int exp;
};
struct divisor {
	size_t DivNumber;
	size_t DivSum;
	size_t DivProduct;
	string Div_pr;
};
struct data_t {
	int number;
	wstring code;
	int degree;
	vector <int> sequence;
	string expression;
	size_t Div_number;
	size_t Div_sum;
	size_t Div_product;
	string Divpr;
};
enum switchcase
{
	DoSimpleCode,
	DoComplexCode,
	DoSimpleFactor,
	DoComplexFactor,
	DoCodeFactor,
	DoAll,
	DebugSimpleCode,
	DebugComplexCode,
	DebugSimpleFactor,
	DebugComplexFactor,
	DebugCodeFactor,
	DebugAll,
	ConvertCodeInverse,
	FactorPolynomial,
	FactorFraction,
	Random, 
	NotAssigned
};
vector <wstring> commands {
	L"cc", L"ccc", L"cf",
	L"cff", L"ccf", L"ct",
	L"dc", L"dcc", L"df",
	L"dff", L"dcf", L"dt",
	L"ctn", L"pol", L"alg", 
	L"rnd"
};

// classi
static char charVariable('x');
class TestInputReader {
public:
	void enqueue(char c) { buffer.push(c); }
	char read() {
		if (size(buffer) == 0) buffer.push(_getch());
		char front = buffer.front();
		buffer.pop();
		return front;
	}
private: queue <char> buffer;
};
TestInputReader ObjectGetCh;

// namespace e funzioni
namespace EnumMod
{
	static unordered_map <wstring, switchcase> stringToEnumMap {
		{L"cc",  switchcase::DoSimpleCode       },
		{L"ccc", switchcase::DoComplexCode      },
		{L"cf",  switchcase::DoSimpleFactor     },
		{L"cff", switchcase::DoComplexFactor    },
		{L"ccf", switchcase::DoCodeFactor       },
		{L"ct",  switchcase::DoAll              },
		{L"dc",  switchcase::DebugSimpleCode    },
		{L"dcc", switchcase::DebugComplexCode   },
		{L"df",  switchcase::DebugSimpleFactor  },
		{L"dff", switchcase::DebugComplexFactor },
		{L"dcf", switchcase::DebugCodeFactor    },
		{L"dt",  switchcase::DebugAll           },
		{L"ctn", switchcase::ConvertCodeInverse },
		{L"pol", switchcase::FactorPolynomial   },
		{L"alg", switchcase::FactorFraction     },
		{L"rnd", switchcase::Random             }
	};
	static unordered_map <switchcase, wstring> enumToStringMap {
		{switchcase::DoSimpleCode,       L"cc" },
		{switchcase::DoComplexCode,      L"ccc"},
		{switchcase::DoSimpleFactor,     L"cf" },
		{switchcase::DoComplexFactor,    L"cff"},
		{switchcase::DoCodeFactor,       L"ccf"},
		{switchcase::DoAll,              L"ct" },
		{switchcase::DebugSimpleCode,    L"dc" },
		{switchcase::DebugComplexCode,   L"dcc"},
		{switchcase::DebugSimpleFactor,  L"df" },
		{switchcase::DebugComplexFactor, L"dff"},
		{switchcase::DebugCodeFactor,    L"dcf"},
		{switchcase::DebugAll,           L"dt" },
		{switchcase::ConvertCodeInverse, L"ctn"},
		{switchcase::FactorPolynomial,   L"pol"},
		{switchcase::FactorFraction,     L"alg"},
		{switchcase::Random,             L"rnd"}
	};
	static wstring ConvertEnumToWString(switchcase Enum) 
	{
		auto it = enumToStringMap.find(Enum);
		if (it != enumToStringMap.end()) return it->second;
	}
	static switchcase ConvertWStringToEnum(wstring str) 
	{
		auto it = stringToEnumMap.find(str);
		if (it != stringToEnumMap.end()) return it->second;
		else {
			stringToEnumMap.insert({ str , NotAssigned });
			it = stringToEnumMap.find(str);
			return it->second;
		}
	}
	static switchcase ReassigneEnum(switchcase option) 
	{
		if (option != Random) return option;
		random_device rng;
		mt19937 gen(rng());
		uniform_int_distribution<> dis(0, 15);
		switch (dis(gen)) {
		case 0:
			return DoSimpleCode;
			break;
		case 1:
			return DoComplexCode;
			break;
		case 2:
			return DoSimpleFactor;
			break;
		case 3:
			return DoComplexFactor;
			break;
		case 4:
			return DoCodeFactor;
			break;
		case 5:
			return DebugCodeFactor;
			break;
		case 6:
			return DoAll;
			break;
		case 7:
			return DebugSimpleCode;
			break;
		case 8:
			return DebugComplexCode;
			break;
		case 9:
			return DebugSimpleFactor;
			break;
		case 10:
			return DebugComplexFactor;
			break;
		case 11:
			return DebugComplexFactor;
			break;
		case 12:
			return DebugAll;
			break;
		case 13:
			return ConvertCodeInverse;
			break;
		case 14:
			return FactorPolynomial;
			break;
		case 15:
			return FactorFraction;
			break;
		}
	}
}
namespace Sort
{
	static void SortDeq(deque <MONOMIAL> &vect)
	{
		for (int i = 0; i < size(vect); i++)
			for (int j = i + 1; j < size(vect); j++)
				if (vect[i].degree < vect[j].degree) 
					swap(vect[i], vect[j]);
	}
	template <typename struct_t>
	static void Heapify(vector <struct_t>& vect, int n, int i) 
	{
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
	static vector <struct_t> HeapSort(vector <struct_t>& vect) 
	{
		int n = vect.size();
		for (int i = n / 2 - 1; i >= 0; i--) Heapify(vect, n, i);
		for (int i = n - 1; i > 0; i--) {
			swap(vect[0], vect[i]);
			Heapify(vect, i, 0);
		}
		return vect;
	}
}
namespace BasicPrints
{
	int RotAngle = 270, PolygDegree = 0, PolygonSides = 4;
	double DWidth = 1.9;
	int CircleCenterX, CircleCenterY;
	bool DecreaseAngle = 1, DecreaseWidth = 1;
	int CircleRotDegreeAngle = 0;
	const vector <int> spectrum { 9, 9, 9, 11, 11, 3, 3, 12, 4 };

	static void ClearArea(COORD win_center)
	{
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		DWORD consoleSize = pow(2 * Min.X + 1, 2);
		DWORD written;
		COORD coord;

		coord.X = win_center.X - Min.X;
		coord.Y = win_center.Y - Min.Y;

		for (int y = win_center.Y; y <= win_center.Y + 2 * Min.Y; y++) {
			coord.Y = y - Min.Y;
			FillConsoleOutputCharacter
			(hConsole, ' ', 2 * Min.X + 1, coord, &written);
		}
	}
	static void PrintPFrame
	(double deg, int sides, double radius, COORD win_center)
	{
		SetConsoleTextAttribute(hConsole, 15);

		COORD coord;
		const double DIM = 1.9;
		const int centerX = win_center.X;
		const int centerY = win_center.Y;
		long double setX, setY;
		long double theta = 2 * M_PI / sides;

		// calcolo apotema e lato con la goniometria e le formule
		long double sidelenght = sqrt(2 * pow(radius, 2) * (1 - cos(theta)));
		long double apotem = sqrt(pow(radius, 2) - pow(sidelenght / 2, 2));

		// stringa dei caratteri per l'illuminazione del poligono
		string prints = "@$#/*!+=~;:-,.";

		for (double rad = 0; rad < 2 * M_PI; rad += theta) {
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
	static void DrawFrame
	(int arc, double __i, int centerX, int centerY, double DIM) 
	{
		COORD coord;
		int setX, setY;
		const double R = 8;

		for (int deg = 0; deg < arc; deg++) {
			// da gradi a radianti
			long double rad = (double)deg / 180 * M_PI;

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
			random_device Random;

			// generatore casuale colori
			mt19937 Gen(Random());
			uniform_int_distribution<> Dis(0, size(spectrum) - 1);
			int DisGen = Dis(Gen);

			// assegnazione colori
			for (int j = 0; j < size(spectrum); j++)
				if (DisGen == j) colour = spectrum[j];

			// stampa
			SetConsoleTextAttribute(hConsole, colour);
			cout << dis(gen);
		}
	}
	static void DrawCircleSquare(COORD circle_center) {

		// calcolo variabili
		COORD cursor { 0, circle_center.Y };
		cursor.Y -= Min.Y;
		const double SPEED = 50;
		const double GAP = 0.05;
		const int const_x = circle_center.X;
		const int const_y = circle_center.Y;
		const double R2 = 5;
		bool Skip_skipping = 1;

		for (CircleRotDegreeAngle;
			 CircleRotDegreeAngle % 2 < 2;
			 CircleRotDegreeAngle += 7) 
		{
			// termine funzione
			if (is_done.load() && !Skip_skipping) {
				ClearArea(circle_center);
				SetConsoleCursorPosition
				(hConsole, cursor);
				return;
			}
			Skip_skipping = 0;

			// variazione centro del cerchio principale
			// secondo lo spostamento su un secondo cerchio
			long double i = (double)CircleRotDegreeAngle / 180 * M_PI;
			CircleCenterX = const_x + R2 * cos(i);
			CircleCenterY = const_y + R2 * sin(i);

			// variazione dati cerchio
			if (DWidth <= 1 || DWidth >= 2.5) DecreaseWidth = !DecreaseWidth;
			if (RotAngle <= 0 || RotAngle >= 360) DecreaseAngle = !DecreaseAngle;

			// stampa cerchio
			DrawFrame(RotAngle, i, CircleCenterX, CircleCenterY, DWidth);

			// stampa poligono e cambio variabili
			DecreaseWidth ? DWidth -= GAP : DWidth += GAP;
			DecreaseAngle ? RotAngle -= SPEED * GAP : RotAngle += SPEED * GAP;
			PrintPFrame(PolygDegree * M_PI / 180, PolygonSides, 10, circle_center);
			PolygDegree += 2;

			// riassegnazione dei lati
			if (PolygDegree % 180 == 0)
				switch (PolygonSides) {
				case 4: PolygonSides = 6;
					break;
				case 6: PolygonSides = 8;
					break;
				case 8: PolygonSides = 4;
					break;
				}
			sleep_for(microseconds(1));
			ClearArea(circle_center);
		}
	}
}
namespace Print 
{
	using namespace BasicPrints;
	static void CS_CenterPrinter()
	{

		// assegnazione delle coordinate del centro
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		COORD win_center;
		if (csbi.dwSize.X / 2 < Min.X) win_center.X = Min.X;
		else win_center.X = csbi.dwSize.X / 2;
		if (csbi.dwSize.Y / 2 < Min.Y) win_center.Y = Min.Y;
		else win_center.Y = csbi.dwSize.Y / 2;

		// animazione
		DrawCircleSquare(win_center);
	}
	static void CS_CornerPrinter()
	{

		// lettura coordinate
		COORD win_center = Min;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		for (int i = 1; i < csbi.dwSize.Y; i++) cout << '\n';

		// animazione
		SetConsoleCursorPosition(hConsole, { 0, 0 });
		DrawCircleSquare(Min);
		
	}
	static void ProgressBar(double ratio, double barWidth)
	{
		if (barWidth <= 10) return;

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
		cout << "]] " << stream.str() << "%\r";
	}
	static void DataPrintF(data_t structure)
	{
		setlocale(1, "");
		SetConsoleOutputCP(CP_UTF8);
		wcout.imbue(locale(""));

		// stampa numero
		cout << "numero " << structure.number << ":\n";
		SetConsoleTextAttribute(hConsole, 2);
		cout << "in esadecimale è " << hex << uppercase;
	    cout << structure.number << "\n" << dec << nouppercase;

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
	static void WaitingScreen
	(steady_clock::time_point begin, steady_clock::time_point end)
	{
		system("cls");

		// calcolo dati
		double delta = duration_cast <milliseconds> (end - begin).count();
		double exception_delta = duration_cast <microseconds> (end - begin).count();
		stringstream output; 
		output << fixed << setprecision(1);

		// calcolo output
		if (delta <= 10) {
			output << "tempo di calcolo numeri primi = ";
			output << exception_delta;
			output << " microsecondi\n\n";
		}
		else if (delta > 10'000 && delta <= 600'000) {
			delta = delta / 1'000;
			output << "tempo di calcolo numeri primi = ";
			output << delta;
			output << " secondi\n\n";
		}
		else if (delta > 600'000) {
			delta = delta / 60'000;
			output << "tempo di calcolo numeri primi = ";
			output << delta;
			output << " minuti\n\n";
		}
		else {
			output << "tempo di calcolo numeri primi = ";
			output << delta;
			output << " millisecondi\n\n";
		}
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		SetConsoleTextAttribute(hConsole, 6);

		// output
		COORD Cursor;
		Cursor.X = (csbi.dwSize.X - output.str().size()) / 2 - 1;
		Cursor.Y = csbi.dwSize.Y / 2 - 1;
		SetConsoleCursorPosition(hConsole, Cursor);
		cout << output.str();
		sleep_for(seconds(1));
	}
}
namespace Input
{
	static wstring ElabExponents(wstring str, int &Size)
	{
		Size = 0;
		int J = 1;
		bool dobreak = 0;
		for (int I = 0; I < str.size(); I++) {
			int pointer = I + 1;
			if (str.at(I) == '^' && I != str.size() - 1) {
				while (isdigit(str.at(pointer))) 
				{
					// scelta carattere
					dobreak = 0;
					wstring replacer;
					switch (str.at(pointer)) {
					case '0': 
						if (J > 1) {
							replacer = L"⁰";
							Size--;
						}
						else dobreak = 1;
						break;
					case '1': replacer = L"¹";
						break;
					case '2': replacer = L"²";
						break;
					case '3': replacer = L"³";
						break;
					case '4': replacer = L"⁴";
						break;
					case '5': replacer = L"⁵";
						break;
					case '6': replacer = L"⁶";
						break;
					case '7': replacer = L"⁷";
						break;
					case '8': replacer = L"⁸";
						break;
					case '9': replacer = L"⁹";
						break;
					}
					if (dobreak) break;

					// cambio caratteri e ridimensionamento stringa
					str.replace(pointer, 1, replacer);
					if (I < str.size() - 2 && J == 1) str.erase(I, 1);
					if (HAS_BEEN_PRINTED) str.erase(I + J - 1, 1);
					else Size--;
					J++;
					pointer = HAS_BEEN_PRINTED? 
						I + J - 1 : I + 2 * (J - 1) + (J == 1);
					if (pointer >= str.size()) break;
				}
				J = 1;
			}
		}
		Size += str.size();
		return str;
	}
	static void GetFraction(wstring &numerator, wstring &denominator)
	{
		setlocale(1, "");
		SetConsoleOutputCP(CP_UTF8);
		wcout.imbue(locale(""));

		denominator = L"1";
		int i = 0, j = 0, k;
		wstring vel;
		bool cursor_at_start = 1;

		// aggiunta di spazio
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		COORD START = csbi.dwCursorPosition;
		for (int I = 0; I < 10; I++) cout << '\n';
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		if (csbi.dwCursorPosition.Y >= START.Y)
			START.Y -= 10 - csbi.dwCursorPosition.Y + START.Y;
		SetConsoleCursorPosition(hConsole, START);

		GetConsoleScreenBufferInfo(hConsole, &csbi);
		COORD start = csbi.dwCursorPosition;
		while (true) if (_kbhit) {
			
			char c = _getch();
			GetConsoleScreenBufferInfo(hConsole, &csbi);
			wstring S = wstring(csbi.dwSize.X, ' ') + L"\r";
			switch (c) {

				// '.' termina il programma
			case '.':
				numerator = L".";
				SetConsoleCursorPosition(hConsole, start);
				for (int a = 0; a < 4; a++) wcout << S << '\n';
				return;

				// '\r' termina l'input
			case '\r':
				start.Y += 4;
				SetConsoleCursorPosition(hConsole, start);
				if (denominator == L"") denominator = L"1";
				return;

				// backspace cancella
			case '\b':
				vel = cursor_at_start ? numerator : denominator;
				k = cursor_at_start ? i : j;
				if (k > 1) {
					vel.erase(k - 1);
					k--;
				} 
				else {
					vel = L"";
					k = 0;
					wcout << '\r' << wstring(csbi.dwSize.X, ' ');
				}
				if (cursor_at_start) {
					numerator = vel;
					i = k;
				} 
				else {
					denominator = vel;
					j = k;
				}
				break;

				// ctrl + '\b' cancella tutto
			case 127:
				if (cursor_at_start) {
					numerator = L"";
					i = 0;
				}
				else {
					denominator = L"";
					j = 0;
				}
				wcout << '\r' << wstring(csbi.dwSize.X, ' ');
				break;

				// altrimenti la stringa aumenta dimensione
			default:
				if ((c < 65 || c > 90) && c > 31 && c != ' ') {
					if (cursor_at_start) {
						numerator += c;
						i++;
					}
					else {
						denominator += c;
						j++;
					}
				}
			}

			// calcolo dimensione stringhe
			int sizenum, sizeden;
			wstring Num = ElabExponents(numerator, sizenum);
			wstring Den = ElabExponents(denominator, sizeden);
			int spaces = (sizenum - sizeden) / 2;
			spaces = abs(spaces);

			// stampa frazione algebrica
			SetConsoleCursorInfo(hConsole, &cursorInfo);
			if (sizenum > sizeden) {
				SetConsoleCursorPosition(hConsole, start);
				wcout << S << Num << '\n';
				wcout << S << wstring(sizenum, '-') << '\n';
				wcout << S << wstring(spaces, ' ') << Den;
			}
			else {
				SetConsoleCursorPosition(hConsole, start);
				wcout << S << wstring(spaces, ' ') << Num << '\n';
				wcout << S << wstring(sizeden, '-') << '\n';
				wcout << S << Den;
			}

			// reset riga
			if (c == 'H') cursor_at_start = 1;
			else if (c == 'P') cursor_at_start = 0;

			// reset cursore
			if (cursor_at_start) {
				start.X += sizenum;
				if (sizenum < sizeden) start.X += spaces;
				SetConsoleCursorPosition(hConsole, start);
				start.X -= sizenum;
				if (sizenum < sizeden) start.X -= spaces;
			}
			else {
				start.X += sizeden;
				if (sizenum > sizeden) start.X += spaces;
				start.Y += 2;
				SetConsoleCursorPosition(hConsole, start);
				if (sizenum > sizeden) start.X -= spaces;
				start.X -= sizeden;
				start.Y -= 2;
			}
			SetConsoleCursorInfo(hConsole, &cursor);
		}
	}
	static wstring GetLine(bool ShowSuggestions, int sizemax)
	{
		int i = 0;
		wstring command = L"rnd";
		wstring vel;
		bool script;
		while (true) if (_kbhit()) {
			char c = _getch();
			if (c == '\r') break;

			// ignora le lettere maiuscole
			// e i caratteri non stampabili eccetto '\b'
			bool cond = c == '\b' ||
						c == '\t' ||
				((c < 65 || c > 90) && c > 31);

			if (cond) switch (c) {

				// '.' termina il programma
			case '.': return L".";

				// termine input
			case '\r': break;

				// '\b' cancella
			case '\b':
				if (i > 1) {
					vel.erase(i - 1);
					i--;
				}
				else {
					vel = L"";
					i = 0;
					wcout << '\r' << wstring(sizemax, ' ');
				}
				break;

				// tab per scegliere il suggerimento
			case '\t':
				if (ShowSuggestions) {
					vel = command;
					i++;
				}
				break;

				// ctrl + '\b' cancella tutto
			case 127:
				vel = L"";
				i = 0;
				wcout << '\r' << wstring(sizemax, ' ');
				break;
			default:
				vel += c;
				i++;
			}
			int sizevel;
			wstring E_Vel = ElabExponents(vel, sizevel);

			// stampa dei caratteri immessi
			if (i > sizemax) {
				vel = L"";
				E_Vel = L"";
				sizevel = 0;
				i = 0;
				wcout << '\r' << wstring(sizemax, ' ');
			}
			script = 1;
			SetConsoleCursorInfo(hConsole, &cursorInfo);
			if (ShowSuggestions && sizevel > 0)

				// ricerca suggerimento giusto
				for (wstring comma : commands) {
					command = comma;
					wstring back = command;
					if (back.size() == sizevel) continue;
					if (back.size() > sizevel) back.erase(sizevel);
					if (back == E_Vel) {
						SetConsoleTextAttribute(hConsole, 6);
						wcout << '\r' << wstring(sizemax, ' ');
						wcout << '\r' << command;
						SetConsoleTextAttribute(hConsole, 15);

						wcout << '\r' << E_Vel;
						i = sizevel;
						script = 0;
						break;
					}
				}
			if (script) {
				wcout << '\r' << wstring(sizemax, ' ') << '\r' << E_Vel;
				i = sizevel;
			}
			SetConsoleCursorInfo(hConsole, &cursor);
		}
		return vel;
	}
	static wstring GetUserNum
	(wstring txt, int low, long long high, bool ShowSuggestions)
	{
		using namespace EnumMod;

		setlocale(1, "");
		SetConsoleOutputCP(CP_UTF8);
		wcout.imbue(locale(""));
		switchcase option;
		long long user_num;
		wstring check;
		do {

			// input
			bool error = 1;
			bool general_error = 0;
			wcout << txt;
			check = GetLine(ShowSuggestions, 10);
			cout << '\n';
			if (check == L"." || check.empty()) return check;
			option = ConvertWStringToEnum(check);
			option = ReassigneEnum(option);
			if (option != NotAssigned) return ConvertEnumToWString(option);

			// controllo
			wregex CheckDigits(L"\\D");
			if (regex_search(check, CheckDigits)) user_num = 0;
			else user_num = stoull(check);

		} while (user_num < low || user_num > high);
		return to_wstring(user_num);
	}
}
namespace Primitive
{
	static size_t Factorial(size_t n) 
	{
		if (n <= 1) return 1;
		else return n * Factorial(n - 1);
	}
	static long double IntegralLog(int N)
	{
		long double sum = 0;
		for (int x = 2; x <= N; x++)
			sum += 1 / log(x);
		return sum;
	}

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
	static void UserInputThread() 
	{
		while (computing) {

			// controllo
			char choice = ObjectGetCh.read();
			if (choice == 'S' || choice == 's') {
				GlobalInterr = 1;
				interrupted = 1;
				return;
			}

			// riduzione uso della CPU
			sleep_for(milliseconds(100));
		}
	}
	static vector_t SieveOfErastothens(long long N, bool USE_pro_bar)
	{
		using namespace Print;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		const int BARWIDTH = csbi.dwSize.X - 11;

		vector <bool> is_prime(N + 1, 1);
		vector <int> primes;
		vector <int> counter;
		int SPEED = 75;
		const double COEFF = 0.3;
		const int SQUARE = (int)sqrt(N) + 2;
		const double NOTPRIMESIZE = (N - IntegralLog(N)) / COEFF;
		int iter = 0;
		if (USE_pro_bar) system("cls");

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
					long double progress = (double)size(counter) / NOTPRIMESIZE;
					if (progress > 0.5) SPEED = 15;
					if (progress > 1) progress = 1;
					ProgressBar(progress, BARWIDTH);

					// calcolo tempo rimanente
					int time = duration_cast <milliseconds> (stop - begin).count();
					SetConsoleTextAttribute(hConsole, 15);
					long double time_rem = (time / progress) * (1 - progress);
					long double time_seconds = (double)time_rem / 1000;

					// calcolo cifre decimali
					stringstream stream;
					stream << fixed << setprecision(1) << time_seconds;
					cout << "\ntempo rimanente: " << stream.str() << " [secondi]  ";

					mtx.unlock();
				}
				iter++;
				});
			SetConsoleTextAttribute(hConsole, 15);
		}

		// calcolo senza barra di progresso
		else for (int p = 2; p < SQUARE; p++)
			for (int i = pow(p, 2); i <= N; i += p) is_prime[i] = 0;
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
			thread t2(CS_CenterPrinter);
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
	static vector <compost> DecomposeNumber(long long input)
	{
		using Primitive::SieveOfErastothens;

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
		vector <compost> output;
		compost output_element = { 0, 1 };
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
					if (input % PrimeNumbers.list_primes[i] != 0) index++;
					i--;
				}
			}
		}
		// eccezione
		if (output[index].factors == input) output[index].exp++;
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

			// caso di seconda eccezione
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
		for (int space = ToEvaluate.size() - 1; space >= 0; space--)
			if (ToEvaluate.at(space) == ' ' || ToEvaluate.at(space) == '\t')
				ToEvaluate.erase(space, 1);

		return ToEvaluate;
	}
}
namespace Calc
{
	using namespace Operators;
	static wstring Cript(long long input)
	{
		using Primitive::Prime;
		int size_s = 0;
		int product = 1;

		// calcolo del limite di approssimazione
		do {
			product *= PrimeNumbers.list_primes[size_s];
			size_s++;
		} while (product < GlobalMax);

		vector <compost> expfactors = DecomposeNumber(input);
		while (expfactors[size(expfactors) - 1].factors == 0)
			expfactors.pop_back();
		wstring the_string, exp_verify, exp_string, prime_exp_string;
		int prime_exp, sizestring, presence;
		long long analyse;
		bool repeat;
		wstring monomials[15];

		// per ogni fattore primo
		for (int what_factor = 0; what_factor < size(expfactors); what_factor++)
		{
			repeat = 0;
			presence = 0;

			// esponente
			exp_verify = to_wstring(expfactors[what_factor].exp);
			analyse = expfactors[what_factor].factors;
			wstring part_of1 = L"(";
			wstring part_of2 = L")";

			// se l'esponente ha una cifra ed è maggiore di 1,
			if (expfactors[what_factor].exp != 1 && expfactors[what_factor].exp < 11)
			{
				part_of2.append(exp_verify);
				presence = 1;
			}

			// se l'esponente ha due cifre,
			else if (expfactors[what_factor].exp > 10) {
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
						if (prime_exp > 10) prime_exp_string = L"." + prime_exp_string;
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

		// unione dei monomi
		the_string = L"";
		for (int i = 0; i < size(expfactors); i++)
			the_string = the_string + L"+" + monomials[i];
		the_string.erase(0, 1);

		// rimozione basi
		int* position = new(nothrow) int[size_s];
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
		vector <compost> expfactors = DecomposeNumber(input);
		while (expfactors[size(expfactors) - 1].factors == 0)
			expfactors.pop_back();

		// unione dei monomi
		string output = "";
		for (int i = 0; i < size(expfactors); i++) {
			if (expfactors[i].exp != 1)
				output = output + to_string(expfactors[i].factors)
				+ "^" + to_string(expfactors[i].exp) + " * ";
			else output = output + to_string(expfactors[i].factors) + " * ";
		}

		// rimozione della fine
		output.erase(output.size() - 3);

		return output;
	}
	static int ExecuteStrings(wstring input)
	{
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
		int* values = new(nothrow) int[size_s];
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

		delete[] values;
		return output;
	}
	static divisor DivisorCounter(string factor)
	{
		divisor output = { 1, 1, 1, "" };
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
			size_t num = -1 + pow(values[i], exponents[i] + 1);
			size_t den = values[i] - 1;
			output.DivSum *= (num / den);
			x *= pow(values[i], exponents[i]);
		}

		// eccezione
		if (output.DivSum < 0) output.DivSum = -1;

		// calcolo del prodotto dei divisori
		if (output.DivNumber > 0) {
			double out = (double) output.DivNumber / 2;
			size_t y = pow(x, out);
			if (y > 0) output.DivProduct = y;

			// caso di overflow
			else if (output.DivNumber % 2 == 0)
				output.Div_pr = to_string(x) + "^" + to_string((size_t)out);

			// caso di un quadrato perfetto pari
			else output.Div_pr = to_string((size_t)sqrt(x))
				+ "^" + to_string((size_t)(out * 2));
		}

		// eccezione
		else {
			output.DivNumber = -1;
			output.DivProduct = -1;
		}

		return output;
	}
	static vector <int> DivisorCalculator(int num) 
	{

		// creazione dei vettori con i principali fattori
		vector <int> vec;
		vector <compost> expfact = DecomposeNumber(num);
		while (expfact[size(expfact) - 1].factors == 0) expfact.pop_back();

		vector <vector <int>> MainDiv;
		for (int i = 0; i < size(expfact); i++) {
			MainDiv.push_back({});
			int EFelement = 1;
			for (int j = 0; j <= expfact[i].exp; j++) {
				MainDiv[i].push_back(EFelement);
				EFelement *= expfact[i].factors;
			}
		}

		// prodotto cartesiano
		vector <int> temp;
		for (int i = size(MainDiv) - 1; i > 0; i--) {
			for (int a : MainDiv[i]) for (int b : MainDiv[i - 1]) 
					temp.push_back(a * b);
			MainDiv[i - 1] = temp;
			MainDiv.pop_back();
		}

		return MainDiv[0];
	}
}
namespace Execute
{
	using namespace Calc;
	static data_t ExecuteSimpledeg(long long input) 
	{
		data_t output = { input, Cript(input), 0, {}, "", 1, 1, 1, "" };
		return output;
	}
	static data_t ExecuteDegree(long long input) 
	{
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
	static data_t ExecuteSimpleFact(long long input) 
	{
		data_t output = { input, L"", 0, {}, FactNumber(input), 1, 1, 1, "" };
		return output;
	}
	static data_t ExecuteFactor(long long input) 
	{
		data_t output = { input, L"", 0, {}, "", 1, 1, 1, "" };
		output.expression = FactNumber(input);
		divisor D = DivisorCounter(output.expression);
		output.Div_product = D.DivProduct;
		output.Div_number = D.DivNumber;
		output.Div_sum = D.DivSum;
		output.Divpr = D.Div_pr;
		return output;
	}
	static data_t ExecuteSimpleDF(long long input) 
	{
		data_t output = { input, Cript(input), 0,
			{}, FactNumber(input), 1, 1, 1, "" };
		return output;
	}
	static data_t ExecuteDegFactor(long long input) 
	{
		data_t A = ExecuteDegree(input);
		data_t B = ExecuteFactor(input);
		data_t output = { input, A.code, A.degree, A.sequence,
			B.expression, B.Div_number, B.Div_sum, B.Div_product, B.Divpr };
		return output;
	}
}
namespace Convalid
{
	using namespace Operators;
	static bool Syntax(wstring polynomial)
	{
		if (polynomial.empty()) return 0;
		if (polynomial == L"0") return 1;
		bool error;
		bool assigne = 0;
		string charsAllowed = "0123456789+-^";

		// controllo caratteri
		for (char a : polynomial) {
			error = 1;
			for (char b : charsAllowed) if (a == b) error = 0;
			if (error) {
				if (assigne) return 0;
				charVariable = a;
				charsAllowed += charVariable;
				assigne = 1;
				if (charVariable < 97 || charVariable > 122) return 0;
			}
		}

		// controllo successione caratteri
		string sequence = "123456789+-";
		sequence += charVariable;
		bool is_an_exponent = 0;
		int i = 0;
		for (char a : polynomial) {
			error = 1;
			for (char b : sequence) if (a == b) error = 0;
			if (error) return 0;

			// riassegnazione dei caratteri ammessi
			if (a == charVariable) sequence = "+-^";
			else switch (a) {
			case '+':
				sequence = "123456789";
				sequence += charVariable;
				if (is_an_exponent) is_an_exponent = 0;
				break;
			case '-':
				sequence = "123456789";
				sequence += charVariable;
				if (is_an_exponent) is_an_exponent = 0;
				break;
			case '^':
				sequence = "123456789";
				is_an_exponent = 1;
				break;
			default:
				sequence = "0123456789+-";
				sequence += charVariable;
				if (is_an_exponent) i++;
				if (i > 2) return 0;
			}
		}

		// controllo al termine
		char end = polynomial.at(polynomial.size() - 1);
		if (end == '+' || end == '-' || end == '^') return 0;

		return 1;
	}
	static wstring SyntaxValidator(wstring ToEvaluate, bool NecBoundary)
	{
		if (ToEvaluate == L"f") return L"";
		vector <wstring> mono;
		string charsAllowed = "0123456789+(_).";
		bool local_error = 1, boolean = 1;
		int stable = 0;
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
		for (int space = ToEvaluate.size() - 1; space >= 0; space--)
			if (ToEvaluate.at(space) == ' ' || ToEvaluate.at(space) == '\t')
				ToEvaluate.erase(space, 1);

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
		wregex no_digits(L"[_\\d]\\.[_1-9][_\\d]");
		if (regex_search(ToEvaluate, excep_no_digits))
			if (!regex_search(ToEvaluate, no_digits))
				return L"MISSING_DIGITS";
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
						for (int j = stack.size() - 1; j > 0; j--)
							if (boolean && stack.at(j) == ')') {
								stackfinder = j - 1;
								boolean = 0;
							}
						boolean = 1;
						for (int k = stick.size() - 1; k > 0; k--)
							if (boolean && stick.at(k) == ')') {
								stickfinder = k - 1;
								boolean = 0;
							}

						// caso con solo un monomio dotato di parentesi
						if (stackfinder * stickfinder < 0) {
							if (stackfinder > 0) finder = stackfinder;
							else finder = stickfinder;
						}

						// caso con i monomi corrispondenti
						else if (stickfinder == stackfinder) {
							finder = stackfinder;
							for (int l = 0; l <= finder + 1; l++) 
								if (l < min.size())
									if (stick.at(l) != stack.at(l)) stop = 1;
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
									if (ciphr_min[l] != ciphr_max[l]) stop = 1;
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
								if (ciphr_min[l] != ciphr_max[l]) stop = 1;
							}
							else stop = 1;
						}
					}

					if (res % 2 == 1 && size(ciphr_max) - size(ciphr_min) == 1)
						return L"2";
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
				for (int checkplus = 1; checkplus < finder; checkplus++) 
					if (stack.at(checkplus) == '+') local_error = 0;
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

	static size_t NumberConverter(size_t root, wstring M)
	{
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
	static size_t StringConverter(wstring ToEvaluate)
	{
		size_t integer = 1;
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
	static void CodeConverter
	(wstring ToEvaluate, wstring message, bool ShowErrors, bool NecBoundary)
	{
		using Calc::Cript;

		setlocale(1, "");
		SetConsoleOutputCP(CP_UTF8);
		wcout.imbue(locale(""));
		long long number;
		if (ToEvaluate != L"f") {

			ToEvaluate = Standardize(ToEvaluate, NecBoundary);
			number = StringConverter(ToEvaluate);

			// caso normale
			if (ShowErrors || number > 0) {
				wstring text = L"codice <" + ToEvaluate + L"> :\n";
				ConsoleText.push_back({ text , 11});
			}

			// caso con overflow interno
			if (number < -2 && ShowErrors) {
				wstring text = L"ERR[413]: X_SUBSCRIPT_OUT_OF_RANGE\n";
				ConsoleText.push_back({ text , 12 });
			}

			// caso di comune overflow
			if (number == -1 && ShowErrors) {
				wstring text = L"ERR[413]: X_OUT_OF_RANGE\n";
				ConsoleText.push_back({ text , 12 });
			}

			// caso errato per esponente inutile
			if (number == -2 && ShowErrors) {
				wstring text = L"ERR[413]: USELESS_EXPONENT\n";
				ConsoleText.push_back({ text , 6 });
			}

			// caso errato con correzione
			if (!message.empty() && ShowErrors && number > 0) {

				wstring text = message == L"1" ?
					L"ERR[400]: EQUAL_MONOMIALS\n" :
					L"ERR[400]: SIMILIAR_MONOMIALS\n";
				ConsoleText.push_back({ text , 15 });

				text = L"codice corretto: <" + Cript(number) + L">\n";
				ConsoleText.push_back({ text , 2 });
			}

			// caso con errori nascosti per scelta utente
			if (number > 0) {
				wstring text = L"il numero corrispondente e' ";
				ConsoleText.push_back({ text , 15 });
				ConsoleText.push_back({ to_wstring(number) + L"\n" , 4 });
			}

		}
	}
	static void LongComputation
	(wstring ToEvaluate, wstring message, bool ShowErrors, bool NecBoundary)
	{
		using Print::CS_CornerPrinter;

		computing = 1;
		interrupted = 0;

		// conta dei caratteri '_' e archivio della posizione
		wstring backup = ToEvaluate;
		int counter = 0;
		vector <int> pos;
		for (int i = 0; i < size(ToEvaluate); i++)
			if (ToEvaluate.at(i) == '_') {
				pos.push_back(i);
				counter++;
			}

		// caso di stringa univoca
		lock_guard <mutex> lock(CoutMutex);
		if (counter == 0) {
			CodeConverter(ToEvaluate, message, ShowErrors, NecBoundary);
			for (Console a : ConsoleText) {
				SetConsoleTextAttribute(hConsole, a.Attribute);
				wcout << a.Text;
				SetConsoleTextAttribute(hConsole, 15);
			}
			ConsoleText = {};
		}

		// caso di stringa ripetuta
		else for (int i = 0; i < pow(10, counter); i++) {

			// passa variabili per indirizzo
			thread t1([&]() {

				string j = to_string(i);
				int zero_counter = counter - j.size();
				for (int k = 0; k < zero_counter; k++) j = "0" + j;
				for (int k = 0; k < j.size(); k++)
					backup.replace(pos[k], 1, wstring(1, j.at(k)));
				message = SyntaxValidator(backup, NecBoundary);

				// eventuale stampa degli errori
				lock_guard <mutex> lock(mtx);
				if (message.size() > 1 && ShowErrors) {

					wstring text = L"codice " + backup + L" :\n";
					ConsoleText.push_back({ text , 11 });

					text = L"ERR[404]: " + message + L"\n";
					ConsoleText.push_back({ text , 4 });
				}
				else CodeConverter(backup, message, ShowErrors, NecBoundary);
				if (interrupted) return;

				is_done = 1;
				cv.notify_one();
				});
			thread t2(CS_CornerPrinter);
			t1.join();
			t2.join();

			for (Console a : ConsoleText) {
				SetConsoleTextAttribute(hConsole, a.Attribute);
				wcout << a.Text;
				SetConsoleTextAttribute(hConsole, 15);
			}
			ConsoleText = {};
		}
		computing = 0;
		Cv.notify_one();
	}
}
namespace Traduce 
{
	static deque <MONOMIAL> GetMonomials(wstring polynomial)
	{
		deque <MONOMIAL> output;
		MONOMIAL output_element;

		for (int i = polynomial.size() - 1; i >= 0; i--)
			if (polynomial.at(i) == '+' ||
				polynomial.at(i) == '-' ||
				i == 0)
			{
				wstring mono = polynomial;
				wstring coeff = L"";
				mono.erase(0, i);
				int var_pos = -1;

				// calcolo del segno
				int sign = 1;
				if (mono.at(0) == '-') sign = -1;
				if (mono.at(0) == '+' || mono.at(0) == '-')
					mono.erase(0, 1);

				// se il coefficiente è sottinteso
				int j = 0;
				if (mono.at(0) == charVariable) {
					output_element.coefficient = 1;
					var_pos = 0;
				}

				// caso con il coefficiente
				else {
					for (int j = 0; j < mono.size(); j++) {
						if (mono.at(j) == charVariable) {
							var_pos = j;
							break;
						}
						coeff += wstring(1, mono.at(j));
					}
					if (coeff == mono) output_element.degree = 0;
					output_element.coefficient = stoi(coeff);
				}

				// caso di grado non nullo
				if (coeff != mono) {
					if (mono == wstring(1, charVariable))
						output_element.degree = 1;
					else if (mono.size() > var_pos + 1)
						if (mono.at(var_pos + 1) == '^') {
							mono.erase(0, var_pos + 2);
							output_element.degree = stoi(mono);
						}
						else output_element.degree = 1;
					else output_element.degree = 1;
				}

				// aggiunta
				output_element.coefficient *= sign;
				output.push_back(output_element);
				polynomial.erase(i);
			}

		return output;
	}
	static wstring GetFactor(deque <MONOMIAL> inp)
	{
		wstring output = L"";
		wstring xout;
		for (MONOMIAL x : inp) {
			xout = L"";

			// caso con coefficiente sottinteso
			if (x.coefficient != 1 && x.coefficient != -1)
				xout = to_wstring(x.coefficient);

			// caso con grado non nullo
			if (x.degree != 0) {
				xout.append(wstring(1, charVariable));
				if (x.degree != 1) xout += L"^" + to_wstring(x.degree);
			}
			else xout = to_wstring(x.coefficient);

			// aggiunta del segno
			if (x.coefficient < 0 && xout.at(0) != '-')
				xout = L"-" + xout;
			else if (x.coefficient > 0) xout = L"+" + xout;

			// aggiunta
			output += xout;
		}
		return output;
	}
	static wstring GetPolynomial(deque <deque <MONOMIAL>> inp, int &Size)
	{
		using Input::ElabExponents;

		wstring output = L"";
		bool set_modifier = 0;
		wstring exp;
		for (deque <MONOMIAL> T : inp) {

			// caso di monomio modificatore
			if (T[0].degree == -1) {
				exp = to_wstring(T[0].coefficient);
				set_modifier = 1;
				continue;
			}
			wstring xout = GetFactor(T);

			// caso con elevamento a potenza
			if (set_modifier) {
				xout = L"(" + xout + L")^" + exp;
				set_modifier = 0;
			}

			// caso comune
			else xout = L"(" + xout + L")";
			output += xout;
		}
		// caso nullo
		if (output.empty()) return L"0";

		return ElabExponents(output, Size);
	}
}
namespace HandPolynomials
{
	static void OpenPolynomial (deque <deque <MONOMIAL>> &vect)
	{
		for (int i = 0; i < size(vect); i++) {
			if (vect[i][0].degree == -1) {
				int repeat = vect[i][0].coefficient;
				vect.erase(vect.begin() + i);
				deque <MONOMIAL> push = vect[i];
				for (int j = 1; j < repeat; j++) vect.push_front(push);
			}
		}
	}
	static void ClosePolynomial (deque <deque <MONOMIAL>> &vect)
	{
		deque <MONOMIAL> CommonFactor;
		for (int i = 0; i < size(vect); i++)
			for (int j = size(vect) - 1; j > i; j--)
				if (vect[i] == vect[j]) {
					CommonFactor = vect[i];
					if (i > 0) {

						// caso con esponente
						if (size(vect[i - 1]) == 1 &&
							vect[i - 1][0].degree == -1) {
							vect[i - 1][0].coefficient++;
							vect.erase(vect.begin() + i + 1);
						}

						// caso senza esponente
						else {
							int setK;
							vect.insert(vect.begin(), { {-1, 2} });
							vect.erase(vect.begin() + i + 1);
							for (int k = 0; k < size(vect); k++)
								if (vect[k] == CommonFactor) setK = k;
							if (vect[i + 1] != CommonFactor)
								swap(vect[i + 1], vect[setK]);
						}
					}

					// caso di eccezione
					else {
						int setK = 0;
						vect.insert(vect.begin(), { {-1, 2} });
						vect.erase(vect.begin() + i + 1);
						for (int k = 0; k < size(vect); k++)
							if (vect[k] == CommonFactor) setK = k;
						if (vect[i + 1] != CommonFactor)
							swap(vect[i + 1], vect[setK]);
					}
				}
	}
	static deque <MONOMIAL> FillPolynomial(deque <MONOMIAL> vect, int s)
	{
		// riempimento buchi
		for (int i = size(vect) - 1; i > 0; i--)
			for (int j = 1; 
				j < vect[i - 1].degree - vect[i].degree; j++)
					vect.insert
						(vect.begin() + i, 
							{ vect[i - 1].degree - j, 0 }
						);

		// riempimento buchi agli estremi
		if (size(vect) == 0) {
			for (int i = 0; i < s; i++) vect.push_back({ i, 0 });
			return vect;
		}
		if (size(vect) < s) {
			while (vect[0].degree < s - 1)
				vect.push_front({ vect[0].degree + 1, 0 });
			while (vect[size(vect) - 1].degree > 0)
				vect.push_back(
					{vect[size(vect) - 1].degree - 1, 0});
		}

		return vect;
	}

	static deque <MONOMIAL> PolynomialSum(deque <MONOMIAL> inp)
	{

		// ricerca di monomi simili
		for (int i = size(inp) - 1; i >= 0; i--)
			for (int j = i - 1; j >= 0; j--)
				if (inp[i].degree >= 0 && inp[j].degree >= 0)
					if (inp[i].degree == inp[j].degree) {
						inp[i].coefficient += inp[j].coefficient;
						inp[j].coefficient = 0;
					}

		// marcamento dei monomi simili
		for (int i = size(inp) - 1; i >= 0; i--)
			if (inp[i].coefficient == 0) inp[i].degree = -1;

		// rimozione
		auto it = remove(inp.begin(), inp.end(), MONOMIAL{ -1, 0 });
		inp.erase(it, inp.end());

		return inp;
	}
	static deque <MONOMIAL> PolynomialMultiply
	(deque <deque <MONOMIAL>> Polynomial)
	{
		if (size(Polynomial) == 0) return { {0, 1} };
		OpenPolynomial(Polynomial);
		while (size(Polynomial) > 1) {

			MONOMIAL temp;
			deque <MONOMIAL> Temp;
			for (MONOMIAL A : Polynomial[0])
				for (MONOMIAL B : Polynomial[1]) {
					temp.coefficient = A.coefficient * B.coefficient;
					temp.degree = A.degree + B.degree;
					Temp.push_back(temp);
				}
			Polynomial.pop_front();
			Polynomial.pop_front();
			Polynomial.push_front(Temp);
		}
		return PolynomialSum(Polynomial[0]);
	}
	static void PolynomialDivide 
	(
		deque <MONOMIAL> dividend, 
		deque <MONOMIAL> divisor,
		deque <MONOMIAL> &quotient, 
		deque <MONOMIAL> &rest
	)
	{
		using Sort::SortDeq;

		// aggiustamento polinomi
		dividend = FillPolynomial(dividend, dividend[0].degree);
		divisor = FillPolynomial(divisor, divisor[0].degree);
		SortDeq(dividend);
		SortDeq(divisor);
		quotient = {};

		// divisione
		while (dividend[0].degree >= divisor[0].degree) {

			deque <MONOMIAL> divide = divisor;
			int deg = dividend[0].degree;
			int _deg = divisor[0].degree;
			int rest_element = dividend[0].coefficient;
			rest_element /= divisor[0].coefficient;
			for (int i = 0; i < size(divide); i++) {
				divide[i].coefficient *= -rest_element;
				divide[i].degree += deg - _deg;
			}
			for (int i = 0; i < size(dividend); i++)
				divide.insert(divide.begin() + i, dividend[i]);
			dividend = PolynomialSum(divide);
			dividend = FillPolynomial(dividend, deg);
			SortDeq(dividend);
			quotient.push_back({ deg - _deg, rest_element });
		}
		rest = dividend;
	}
}
namespace Techniques
{
	using Sort::SortDeq;
	static deque <deque <MONOMIAL>> Total(deque <MONOMIAL> inp)
	{
		deque <deque <MONOMIAL>> output;
		output.push_back(inp);
		int min;
		if (inp.empty()) return output;
		min = inp[0].degree;

		// calcolo massimo comune divisore numerico
		deque <MONOMIAL> termB = inp;
		int GCD = inp[0].coefficient;
		for (int i = 1; i < size(inp); i++) {
			GCD = gcd(GCD, termB[i].coefficient);
			if (GCD == 1) break;
		}

		// calcolo grado minimo e riscrittura
		for (MONOMIAL t : inp) if (t.degree < min) min = t.degree;
		if (min > 0 || GCD != 1) {
			output = {};
			output.push_back({ {min, GCD} });
			for (int i = 0; i < size(inp); i++) {
				inp[i].coefficient /= GCD;
				inp[i].degree -= min;
			}
		}

		// eventuale aggiunta oppure reset
		if (!(size(inp) == 1 && inp[0] == MONOMIAL{ 0, 1 })) {
			if (!(min > 0 || GCD != 1)) output = {};
			output.push_back(inp);
		}

		return output;
	}
	static deque <deque <MONOMIAL>> Partial(deque <MONOMIAL> inpt)
	{
		using HandPolynomials::PolynomialSum;

		// filtro vettori a quattro termini
		deque <deque <MONOMIAL>> outp;
		outp.push_back(inpt);
		if (size(inpt) != 4) return outp;

		// riassegnazione e dichiarazioni
		deque <MONOMIAL> part_1 = { inpt[0], inpt[1] };
		deque <MONOMIAL> part_2 = { inpt[2], inpt[3] };
		deque <deque <MONOMIAL>> Part1 = Total(part_1);
		deque <deque <MONOMIAL>> Part2 = Total(part_2);
		part_1 = Part1[size(Part1) - 1];
		part_2 = Part2[size(Part2) - 1];
		if (part_1 != part_2) return outp;
		outp = {};

		// riordinamento del totale
		deque <deque <MONOMIAL>> mon_1;
		deque <deque <MONOMIAL>> mon_2;
		if (size(Part1) == 1) mon_1.push_back({ MONOMIAL{ 0, 1 } });
		else mon_1.push_back(Part1[0]);
		if (size(Part2) == 1) mon_2.push_back({ MONOMIAL{ 0, 1 } });
		else mon_2.push_back(Part2[0]);
		mon_1.push_back(part_1);
		mon_2.push_back(part_2);

		// riordinamento del parziale
		outp.push_back(part_1);
		part_2 = mon_1[0];
		for (MONOMIAL a : mon_2[0])
			part_2.push_back(a);
		part_2 = PolynomialSum(part_2);

		outp.push_back(part_2);
		return outp;
	}
	static deque <deque <MONOMIAL>> Binomial(deque <MONOMIAL> InpT)
	{
		using Primitive::Factorial;

		// filtro per vettori con più di un termine
		deque <deque <MONOMIAL>> outp;
		outp.push_back(InpT);
		int exponent = size(InpT) - 1, sign = 1;
		if (exponent <= 1) return outp;
		bool reassigne = 0;
		SortDeq(InpT);

		MONOMIAL A = InpT[0];
		MONOMIAL B = InpT[size(InpT) - 1];

		// controllo per evitare radici impossibili da eseguire nei reali
		if (exponent % 2 == 0 && (A.coefficient < 0 || B.coefficient < 0))
			return outp;

		// calcolo delle radici
		double Sq_A, Sq_B;
		if (A.coefficient > 0) Sq_A = pow(A.coefficient, 1.0 / exponent);
		else Sq_A = -pow(-A.coefficient, 1.0 / exponent);
		if (B.coefficient > 0) Sq_B = pow(B.coefficient, 1.0 / exponent);
		else Sq_B = -pow(-B.coefficient, 1.0 / exponent);

		// controllo sulle potenze
		if (floor(Sq_A) != ceil(Sq_A)) return outp;
		if (floor(Sq_B) != ceil(Sq_B)) return outp;
		if (A.degree % exponent != 0) return outp;
		if (B.degree % exponent != 0) return outp;
		int Adeg = A.degree / exponent;
		int Bdeg = B.degree / exponent;

		for (int i = 1; i < exponent; i++) {

			// calcolo coefficiente
			if (InpT[i].degree != Adeg * (exponent - i) + Bdeg * i)
				return outp;
			int coeff = Factorial(exponent) / (Factorial(i) * Factorial(exponent - i));

			// caso con la sottrazione
			if (InpT[i].coefficient ==
				-coeff * (int)pow(Sq_A, exponent - i) * (int)pow(Sq_B, i)
				) {
				if (!reassigne) {
					sign = -1;
					reassigne = 1;
				}
				else if (sign == 1) return outp;
			}

			// caso con l'addizione
			else if (InpT[i].coefficient ==
				coeff * (int)pow(Sq_A, exponent - i) * (int)pow(Sq_B, i)
				) 
			{
				if (!reassigne) {
					sign = 1;
					reassigne = 1;
				}
				else if (sign == -1) return outp;
			}

			// caso non accettato
			else return outp;
		}

		// composizione della potenza di binomio
		outp = {};
		outp.push_back({ {-1, exponent} });
		outp.push_back(InpT);
		outp[1] = {};
		outp[1].push_back({ A.degree / exponent, (int)Sq_A });
		outp[1].push_back({ B.degree / exponent, sign * (int)Sq_B });

		return outp;
	}
	static deque <deque <MONOMIAL>> Trinomial(deque <MONOMIAL> InpT)
	{

		// filtro per vettori di tre termini
		deque <deque <MONOMIAL>> outp;
		outp.push_back(InpT);
		if (size(InpT) != 3) return outp;

		// calcolo termini ed esponente
		deque <MONOMIAL> terms;
		int A, B, C;
		for (int i = 0; i < size(InpT); i++) {
			if (InpT[i].degree != 0) terms.push_back(InpT[i]);
			else C = InpT[i].coefficient;
		}
		if (terms[0].degree > terms[1].degree)
			swap(terms[0], terms[1]);
		double exp = terms[1].degree / (terms[0].degree * 2);
		if (floor(exp) != ceil(exp)) return outp;
		A = terms[1].coefficient;
		B = terms[0].coefficient;

		// calcolo delle radici
		double firstX, secondX, delta;
		delta = pow(B, 2) - 4 * A * C;
		if (delta <= 0) return outp;
		if (floor(sqrt(delta)) != ceil(sqrt(delta))) return outp;
		firstX = (-B - sqrt(delta)) / (2 * A);
		secondX = (-B + sqrt(delta)) / (2 * A);
		if (floor(A * firstX * secondX) != ceil(A * firstX * secondX))
			return outp;
		outp = {};

		// calcolo dei coefficienti
		int I, J;
		for (I = 1; I <= abs(A); I++)
			if (floor(firstX * I) == ceil(firstX * I)) break;
		if (I == abs(A) + 1) I--;
		if (A < 0) I = -I;
		for (J = 1; J <= abs(A); J++)
			if (floor(secondX * J) == ceil(secondX * J)) break;
		if (J == abs(A) + 1) J--;

		// allocazione di memoria
		outp.push_back(terms);
		outp.push_back(terms);
		outp[0] = {};
		outp[1] = {};

		// composizione del trinomio scomposto
		outp[0].push_back(MONOMIAL{ (int)exp, I });
		outp[0].push_back(MONOMIAL{ 0, (int)(-I * firstX) });
		outp[1].push_back(MONOMIAL{ (int)exp, J });
		outp[1].push_back(MONOMIAL{ 0, (int)(-J * secondX) });

		return outp;
	}
	static deque <deque <MONOMIAL>> SquareDifference(deque <MONOMIAL> InpT)
	{
		// filtro per vettori di due termini
		deque <deque <MONOMIAL>> outp;
		outp.push_back(InpT);
		if (size(InpT) != 2) return outp;

		// controllo sui quadrati perfetti
		if (InpT[0].degree % 2 == 1) return outp;
		if (InpT[1].degree % 2 == 1) return outp;

		// riassegnazione se i segni non vanno bene
		bool Sign_A = InpT[0].coefficient > 0;
		bool Sign_B = InpT[1].coefficient > 0;
		if (Sign_A == Sign_B) return outp;
		if (Sign_A < 0) swap(InpT[0], InpT[1]);

		// calcolo radici
		double Sq_A = sqrt(abs(InpT[0].coefficient));
		double Sq_B = sqrt(abs(InpT[1].coefficient));
		if (floor(Sq_A) != ceil(Sq_A)) return outp;
		if (floor(Sq_B) != ceil(Sq_B)) return outp;

		// allocazione di memoria
		outp.push_back(InpT);
		outp[0] = {};
		outp[1] = {};

		// composizione di somma e differenza
		outp[0].push_back(MONOMIAL{ InpT[0].degree / 2, (int)Sq_A });
		outp[0].push_back(MONOMIAL{ InpT[1].degree / 2, (int)Sq_B });
		outp[1].push_back(MONOMIAL{ InpT[0].degree / 2, (int)Sq_A });
		outp[1].push_back(MONOMIAL{ InpT[1].degree / 2, -(int)Sq_B });

		return outp;
	}
	static deque <deque <MONOMIAL>> Ruffini(deque <MONOMIAL> vect)
	{
		using Calc::DivisorCalculator;
		using HandPolynomials::PolynomialSum;

		// filtro per vettori con più di un termine
		deque <deque <MONOMIAL>> VECT;
		VECT.push_back(vect);
		if (size(vect) < 2) return VECT;
		if (size(vect) == 2 && (vect[0].degree == 1 || vect[1].degree == 1))
			return VECT;
		SortDeq(vect);

		int DirectorTerm = vect[0].coefficient;
		int size_s = vect[0].degree;
		int KnownTerm = vect[size(vect) - 1].coefficient;
		if (abs(DirectorTerm) >= GlobalMax || abs(KnownTerm) >= GlobalMax) 
			return {};

		// calcolo divisori
		vector <int> P = DivisorCalculator(abs(KnownTerm));
		vector <int> Q = DivisorCalculator(abs(DirectorTerm));
		vector <int> PossibleRoots;

		// teorema delle radici razionali
		for (int p : P) for (int q : Q) PossibleRoots.push_back(p / q);
		int SetRoot = 0;
		int Root;
		
		deque <MONOMIAL> Try;
		bool assigne = 1;
		for (int n = 1; n < size_s; n++) {

			// riduzione del polinomio
			Try = vect;
			assigne = 1;
			for (int m = 0; m < size(Try); m++) {
				long double a = (double) Try[m].degree / n;
				if (floor(a) != ceil(a)) {
					assigne = 0;
					break;
				}
				Try[m].degree = a;
			}
			if (assigne) vect = Try;

			// eventuale aggiunta dei coefficienti nulli
			for (int i = 1; i < size(vect); i++)
				for (int j = 1; j < vect[i - 1].degree - vect[i].degree; j++)
					vect.insert(vect.begin() + i, { vect[i - 1].degree - j, 0 });

			// regola di ruffini
			deque <MONOMIAL> temp;
			for (int root : PossibleRoots) {
				Root = root;
				do {

					// divisione polinomio per binomio
					temp = vect;
					for (int i = 1; i < size(vect); i++) {
						temp[i].coefficient = Root * temp[i - 1].coefficient 
							+ temp[i].coefficient;
						temp[i].degree--;
					}

					// caso con resto nullo
					if (temp[size(temp) - 1].coefficient == 0) {
						temp[0].degree--;
						temp.pop_back();
						SetRoot = Root;
						vect = temp;
						break;
					}

					Root = -Root;
				} while (Root != root);
				if (SetRoot != 0) break;
			}
			vect = PolynomialSum(vect);

			// caso di polinomio scomposto
			if (SetRoot != 0) {
				for (int i = 0; i < size(vect); i++) vect[i].degree *= n;
				VECT = {};
				VECT.push_back({ {n, 1}, {0, -SetRoot} });
				VECT.push_back(vect);
				break;
			}

			// ripristino polinomio
			if (assigne) for (int i = 0; i < size(vect); i++) 
				vect[i].degree *= n;
		}
		
		return VECT;
	}
	static deque <deque <MONOMIAL>> CompleteTheSquare(deque <MONOMIAL> vect)
	{

		// filtro per vettori con tre termini
		deque <deque <MONOMIAL>> Vect;
		Vect.push_back(vect);
		if (size(vect) != 3) return Vect;
		SortDeq(vect);
		MONOMIAL A = vect[0];
		MONOMIAL B = vect[2];

		// calcolo delle radici
		if (A.coefficient < 0 || B.coefficient < 0) return Vect;
		double Sq_A = sqrt(A.coefficient);
		double Sq_B = sqrt(B.coefficient);

		// controllo sulle potenze
		if (floor(Sq_A) != ceil(Sq_A)) return Vect;
		if (floor(Sq_B) != ceil(Sq_B)) return Vect;

		// controllo sui gradi
		if (A.degree % 2 == 1 || A.degree / 2 == 1) return Vect;
		if (B.degree % 2 == 1 || B.degree / 2 == 1) return Vect;
		if (vect[1].degree != A.degree / 2 + B.degree / 2) return Vect;
		if (floor(A.degree / 4 + B.degree / 4) != 
			ceil(A.degree / 4 + B.degree / 4)) return Vect;

		// calcolo quadrato di differenza
		MONOMIAL DiffSquare, Diffneg;
		DiffSquare.degree = A.degree / 4 + B.degree / 4;
		int middleterm = 2 * (int)Sq_A * (int)Sq_B, sign;
		int CasePlus = middleterm - vect[1].coefficient;
		int CaseMinus = -middleterm - vect[1].coefficient;
		if (CasePlus < 0) return Vect;
		if (floor(sqrt(CasePlus)) == ceil(sqrt(CasePlus))) {
			DiffSquare.coefficient = sqrt(CasePlus);
			sign = 1;
		}
		else if (floor(sqrt(-CaseMinus)) == ceil(sqrt(-CaseMinus))) {
			DiffSquare.coefficient = sqrt(-CaseMinus);
			sign = -1;
		}
		else return Vect;
		Diffneg.coefficient = -DiffSquare.coefficient;
		Diffneg.degree = DiffSquare.degree;

		// composizione di somma e differenza
		Vect.push_back(vect);
		Vect[0] = {};
		Vect[1] = {};
		
		Vect[0].push_back({ A.degree / 2 , (int)Sq_A });
		Vect[0].push_back({ B.degree / 2 , (int)Sq_B });
		Vect[0].push_back(DiffSquare);
		Vect[1].push_back({ A.degree / 2 , (int)Sq_A });
		Vect[1].push_back({ B.degree / 2 , (int)Sq_B });
		Vect[1].push_back(Diffneg);

		return Vect;
	}

	static deque <deque <MONOMIAL>> GetDecomp(wstring polynomial)
	{
		using namespace Traduce;
		using HandPolynomials::PolynomialSum;
		setlocale(LC_ALL, "");

		// rimozione spazi
		deque <MONOMIAL> polydata;
		wstring POL;
		bool Xout = 0;
		for (int i = polynomial.size() - 1; i >= 0; i--)
			if (polynomial.at(i) == ' ' || polynomial.at(i) == '\t')
				polynomial.erase(i, 1);
		int sizep = polynomial.size();

		// somma e raccoglimento totale
		polydata = PolynomialSum(GetMonomials(polynomial));
		deque <deque <MONOMIAL>> BackT;
		deque <deque <MONOMIAL>> Back_T;
		deque <deque <MONOMIAL>> HT = Total(polydata);

		// raccoglimento parziale
		polydata = HT[size(HT) - 1];
		HT.pop_back();
		BackT = Partial(polydata);
		for (deque <MONOMIAL> a : BackT) HT.push_back(a);
		polynomial = GetPolynomial(HT, sizep);

		do {

			// potenza di binomio
			Back_T = HT;
			HT = {};
			for (deque <MONOMIAL> a : Back_T) {
				BackT = Binomial(a);
				for (deque <MONOMIAL> b : BackT)
					HT.push_back(b);
			}

			// trinomio speciale
			Back_T = HT;
			HT = {};
			for (deque <MONOMIAL> a : Back_T) {
				BackT = Trinomial(a);
				for (deque <MONOMIAL> b : BackT)
					HT.push_back(b);
			}

			// differenza di quadrati
			Back_T = HT;
			HT = {};
			int extend = 1;
			for (deque <MONOMIAL> a : Back_T) {
				if (a[0].degree == -1) {
					extend = a[0].coefficient;
					continue;
				}
				BackT = SquareDifference(a);
				for (deque <MONOMIAL> b : BackT) {
					if (extend > 1)
						HT.push_back({ {-1, extend} });
					HT.push_back(b);
				}
				extend = 1;
			}

			// scomposizione con ruffini
			Back_T = HT;
			POL = GetPolynomial(HT, sizep);
			HT = {};
			for (deque <MONOMIAL> a : Back_T) {
				BackT = Ruffini(a);
				if (size(a) > 0 && size(BackT) == 0) {
					Xout = 1;
					break;
				}
				for (deque <MONOMIAL> b : BackT)
					HT.push_back(b);
			}
			polynomial = GetPolynomial(HT, sizep);

			polynomial = GetPolynomial(HT, sizep);
		} while (polynomial != POL);

		// completamento del quadrato
		Back_T = HT;
		HT = {};
		for (deque <MONOMIAL> a : Back_T) {
			BackT = CompleteTheSquare(a);
			for (deque <MONOMIAL> b : BackT)
				HT.push_back(b);
		}

		if (Xout) return {};
		return HT;
	}
}
namespace Algebraic 
{
	static deque <MONOMIAL> Complementary
	(deque <deque <MONOMIAL>> Polynomial, deque <MONOMIAL> factor, int exp)
	{
		using HandPolynomials::PolynomialMultiply;

		// caso di eccezione
		if (Polynomial[0] == factor) Polynomial.pop_front();

		else for (int i = size(Polynomial) - 1; i > 0; i--)
			if (Polynomial[i] == factor) {

				// caso senza esponente
				if (Polynomial[i - 1][0].degree != -1) {
					Polynomial.erase(Polynomial.begin() + i);
					break;
				}

				// casi con esponente
				else if (Polynomial[i - 1][0].coefficient - exp > 1)
					Polynomial[i - 1][0].coefficient -= exp;
				else if (Polynomial[i - 1][0].coefficient - exp < 1) {
					Polynomial.erase(Polynomial.begin() + i);
					Polynomial.erase(Polynomial.begin() + i - 1);
				}
				else Polynomial.erase(Polynomial.begin() + i - 1);

			}

		return PolynomialMultiply(Polynomial);
	}

	static void Simplify(
		deque <deque <MONOMIAL>> &num, 
		deque <deque <MONOMIAL>> &den,
		int& ncoeff, int& dcoeff)
	{
		using namespace HandPolynomials;
		using Sort::SortDeq;
		OpenPolynomial(num);
		OpenPolynomial(den);
		for (int i = 0; i < size(num); i++) SortDeq(num[i]);
		for (int i = 0; i < size(den); i++) SortDeq(den[i]);

		// semplificazione fattori
		int sign = 1;
		for (int i = 0; i < size(num); i++) {

			// caso coefficiente
			if (size(num[i]) == 1 && num[i][0].degree == 0)
				continue;
			for (int j = 0; j < size(den); j++) {

				// caso coefficiente
				if (size(den[j]) == 1 && den[j][0].degree == 0) continue;

				// caso con polinomi uguali
				if (num[i] == den[j]) {
					num.erase(num.begin() + i);
					den.erase(den.begin() + j);
				}
				else {
					for (int k = 0; k < size(den[j]); k++)
						den[j][k].coefficient = -den[j][k].coefficient;

					// caso con polinomi opposti
					if (num[i] == den[j]) {
						num.erase(num.begin() + i);
						den.erase(den.begin() + j);
						sign = -sign;
					}
					else for (int k = 0; k < size(den[j]); k++)
						den[j][k].coefficient = -den[j][k].coefficient;
				}
			}
		}

		// ricerca coefficenti
		int FindN = -1, FindD = -1;
		for (int i = 0; i < size(num); i++)
			if (size(num[i]) == 1 && num[i][0].degree == 0) {
				ncoeff = num[i][0].coefficient * sign;
				FindN = i;
				num.erase(num.begin() + i);
			}
		for (int i = 0; i < size(den); i++)
			if (size(den[i]) == 1 && den[i][0].degree == 0) {
				dcoeff = den[i][0].coefficient;
				FindD = i;
				den.erase(den.begin() + i);
			}

		// semplificazione coefficienti
		int GCD = gcd(abs(ncoeff), abs(dcoeff));
		ncoeff /= GCD;
		dcoeff /= GCD;
		if (FindN > 0) num[FindN][0].coefficient = 1;
		if (FindD > 0) den[FindD][0].coefficient = 1;

		// compressione polinomi
		ClosePolynomial(num);
		ClosePolynomial(den);
	}

	static int Determinant(deque <deque <int>> mx)
	{
		int det = 0;
		int s = size(mx);

		// casi speciali
		if (s == 1) return mx[0][0];
		if (s == 2) return mx[0][0] * mx[1][1] - mx[0][1] * mx[1][0];
		
		// caso generico
		for (int i = 0; i < s; i++) {

			deque <deque <int>> MX;
			for (int a = 0; a < s - 1; a++) MX.push_back({});
			for (int I = 0; I < s - 1; I++) {
				for (int J = 0; J < s; J++) {
					if (i == J) continue;
					MX[I].push_back(mx[I + 1][J]);
				}
			}
			det += pow(-1, i) * mx[0][i] * Determinant(MX);
			
		}
		return det;
	}

	static void PrintFraction
	(int NC, int DC, double root, int &LINE, bool WritePlus,
		deque <deque <MONOMIAL>> denominator)
	{
		
		// aggiunta di spazio
		using Traduce::GetPolynomial;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		COORD start = csbi.dwCursorPosition;
		for (int i = 0; i < 10; i++) cout << '\n';
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		if (csbi.dwCursorPosition.Y > start.Y)
			start.Y -= 10 - csbi.dwCursorPosition.Y + start.Y;
		SetConsoleCursorPosition(hConsole, start);

		// calcolo coefficienti
		int I = 1;
		while (true) {
			if (floor(I * root) == ceil(I * root)) break;
			I++;
		}
		bool is_minus = 0;
		int Root = root * I;
		DC *= I;
		if (NC * Root < 0 && DC < 0) {
			NC = -NC;
			DC = -DC;
		}
		else if (NC * Root < 0) {
			NC = -NC;
			is_minus = 1;
		}
		else if (DC < 0) {
			DC = -DC;
			is_minus = 1;
		}

		// calcolo stringhe
		int sizeden;
		wstring den_;
		if (DC == 1) den_ = GetPolynomial(denominator, sizeden);
		else {
			den_ = to_wstring(DC) + GetPolynomial(denominator, sizeden);
			sizeden += to_wstring(DC).size();
		}
		wstring num_ = to_wstring(NC * Root);
		size_t Sizeden = sizeden;

		// calcolo dati
		int sizemax = max(num_.size(), Sizeden);
		int spacing = num_.size() - Sizeden;
		spacing = abs(spacing) / 2;
		if (num_.size() > Sizeden) den_ = wstring(spacing, ' ') + den_;
		else num_ = wstring(spacing, ' ') + num_;

		// caso di fine riga
		if (LINE + spacing + WritePlus * 2 > csbi.dwSize.X) {
			LINE = 0;
			start.Y += 4;
			SetConsoleCursorPosition(hConsole, start);
		}

		// output segno
		if (WritePlus || is_minus) {
			if (WritePlus) start.X++;
			start.Y++;
			SetConsoleCursorPosition(hConsole, start);
			is_minus ? cout << '-' : cout << '+';
			start.X += 2;
			start.Y--;
		}

		// output frazione
		SetConsoleCursorPosition(hConsole, start);
		wcout << num_;
		start.Y++;
		SetConsoleCursorPosition(hConsole, start);
		wcout << wstring(sizemax, '-');
		start.Y++;
		SetConsoleCursorPosition(hConsole, start);
		wcout << den_;
		start.Y -= 2;
		start.X += sizemax;
		SetConsoleCursorPosition(hConsole, start);

		// aggiornamento linea
		LINE += sizemax + WritePlus * 2 + 1;
	}
}
namespace Programs
{
	using namespace EnumMod;
	using namespace Print;
	using namespace Input;
	static switchcase CodeToNumber()
	{
		using Primitive::UserInputThread;
		using Operators::Standardize;
		using namespace Convalid;

		// scelta
		setlocale(1, "");
		SetConsoleOutputCP(CP_UTF8);
		wcout.imbue(locale(""));
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
				if (option != NotAssigned) {
					system("cls");
					LPCWSTR title = ToEvaluate.c_str();
					SetConsoleTitle(title);
					return option;
				}
				if (ToEvaluate == L".") return Random;

				// ammissione errori
				if (!ToEvaluate.empty()) {
					NecessaryBoundary = ToEvaluate.at(0) != '\\' && ToEvaluate.at(0) != '/';
					ShowErrors = ToEvaluate.at(0) != '$' && NecessaryBoundary;
					if (!NecessaryBoundary) ToEvaluate.erase(0, 1);
				}

				// individuazione degli errori
				message = SyntaxValidator(ToEvaluate, NecessaryBoundary);
				if (message.size() > 1) {
					lock_guard <mutex> lock(CoutMutex);
					SetConsoleTextAttribute(hConsole, 4);
					wcout << "ERR[404]: " << message << '\n';
					SetConsoleTextAttribute(hConsole, 15);
				}

			} while (message.size() > 1);

			// caso di fine input
			if (ToEvaluate == L"f") return NotAssigned;

			// aggiustamento della stringa immessa
			if (NecessaryBoundary) ToEvaluate = L"<" + Standardize(ToEvaluate, 1) + L">";
			else ToEvaluate = Standardize(ToEvaluate, 0);
			
			GlobalInterr = 0;
			computing = 1;
			interrupted = 0;

			ObjectGetCh.enqueue(' ');
			SetConsoleCursorInfo(hConsole, &cursorInfo);

			// dichiarazione dei thread
			thread ComputationThread([=]() {
				LongComputation(ToEvaluate, message, ShowErrors, NecessaryBoundary);
				});
			thread InputThread(UserInputThread);

			unique_lock <mutex> lock(CoutMutex);
			Cv.wait(lock, [] { return !computing; });

			if (ComputationThread.joinable()) ComputationThread.join();
			interrupted = 1;
			if (InputThread.joinable()) InputThread.join();

			// se il calcolo viene interrotto
			if (GlobalInterr) {
				SetConsoleTextAttribute(hConsole, 15);
				cout << '\n';
				SetConsoleTextAttribute(hConsole, 64);
				cout << "CALCOLO INTERROTTO!!!";
				SetConsoleTextAttribute(hConsole, 15);
				cout << "\n\n";
			}
			SetConsoleCursorInfo(hConsole, &cursor);
		}
	}
	static switchcase Repeater(string message, data_t CPU(long long input)) 
	{
		setlocale(1, "");
		SetConsoleOutputCP(CP_UTF8);
		wcout.imbue(locale(""));
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
			do Input = GetUserNum(txt, 1, GlobalMax, 1);
			while (Input.empty());
			if (Input == L".") return Random;
			option = ConvertWStringToEnum(Input);
			option = ReassigneEnum(option);
			if (option != NotAssigned) {
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

		return NotAssigned;
	}
	static switchcase Loop(string message, data_t CPU(long long input))
	{
		using Sort::HeapSort;
		using Print::CS_CenterPrinter;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		const int Barwidth = csbi.dwSize.X - 11;

		setlocale(1, "");
		SetConsoleOutputCP(CP_UTF8);
		wcout.imbue(locale(""));
		wstring n_ = to_wstring(GlobalMax), Input;
		wstring txt;
		switchcase option;
		vector <data_t> data;
		long long input;

		cout << "debug::\n\n";
		SetConsoleTextAttribute(hConsole, 14);
		cout << message << '\n';
		wcout << "gli estremi dell'intervallo devono essere compresi tra 1 e " << n_ << "\n\n";

		// input e controllo valore iniziale
		SetConsoleTextAttribute(hConsole, 15);
		txt = L"inserisci il valore di inizio della ricerca\n";
		do Input = GetUserNum(txt, 1, GlobalMax, 1);
		while (Input.empty());
		if (Input == L".") return Random;
		option = ConvertWStringToEnum(Input);
		option = ReassigneEnum(option);
		if (option != NotAssigned) {
			system("cls");
			LPCWSTR title = Input.c_str();
			SetConsoleTitle(title);
			return option;
		}
		long long lower_bound = stoull(Input) + 1;
		
		// input e controllo valore finale
		txt = L"inserisci il valore finale della ricerca\n";
		do Input = GetUserNum(txt, 1, GlobalMax, 1);
		while (Input.empty());
		if (Input == L".") return Random;
		option = ConvertWStringToEnum(Input);
		option = ReassigneEnum(option);
		if (option != NotAssigned) {
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
			atomic <long double> Progress = 0;
			steady_clock::time_point begin = steady_clock::now();
			parallel_for(long long(lower_bound), upper_bound, [&](long long set) {

				data_t data_element = CPU(set);
				mtx.lock();
				data.push_back(data_element);
				if (iter % 200 == 0) {

					// stampa della barra di avanzamento
					steady_clock::time_point stop = steady_clock::now();
					SetConsoleTextAttribute(hConsole, 112);
					Progress = (double)size(data) / datalenght;
					ProgressBar(Progress, Barwidth);

					// calcolo del tempo rimanente
					int time = duration_cast <milliseconds> (stop - begin).count();
					SetConsoleTextAttribute(hConsole, 15);
					long double time_rem = (time / Progress) * (1 - Progress);
					long double time_seconds = (double)time_rem / 1000;

					// calcolo cifre decimali
					stringstream stream;
					stream << fixed << setprecision(1) << time_seconds;
					cout << "\ntempo rimanente: " << stream.str() << " [secondi] ";
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
			thread t2(CS_CenterPrinter);
			t2.join();
			t1.join();
			system("cls");

			// stampa risultati
			SetConsoleCursorInfo(hConsole, &cursor);
			for (int x = 0; x < size(data); ++x) DataPrintF(data[x]);
			steady_clock::time_point end = steady_clock::now();
			cout << "\ntempo di calcolo = " << duration_cast <milliseconds> (end - begin).count();
			cout << "[ms]\n\n";
		}

		// caso con intervallo di dimensioni minori
		else {
			steady_clock::time_point begin = steady_clock::now();
			for (long long set = lower_bound; set < upper_bound; set++) {
				data_t data_element = CPU(set);
				DataPrintF(data_element);
			}
			steady_clock::time_point end = steady_clock::now();
			cout << "\ntempo di calcolo = " << duration_cast <milliseconds> (end - begin).count();
			cout << "[ms]\n\n\n";
		}

		// termine
		char null;
		cout << "premi un tasto per continuare\t\t";
		null = _getch();
		if (null == '.') return Random;
		else return NotAssigned;
	}

	using namespace Techniques;
	static switchcase DecompPolynomial()
	{
		using Convalid::Syntax;
		using namespace Traduce;
		using namespace HandPolynomials;
		setlocale(1, "");
		SetConsoleOutputCP(CP_UTF8);
		wcout.imbue(locale(""));
		SetConsoleTextAttribute(hConsole, 14);

		// variabili
		switchcase Option;
		deque <MONOMIAL> polydata, pdata;
		wstring polynomial, pol, POL;
		bool empty, Xout;

		cout << "il programma scompone i polinomi\n\n";
		SetConsoleTextAttribute(hConsole, 15);
		while (true) {
			empty = 1;
			Xout = 0;
			bool No;
			do {
				GetConsoleScreenBufferInfo(hConsole, &csbi);

				// input
				SetConsoleTextAttribute(hConsole, 15);
				cout << "inserisci un polinomio in una variabile"; 
				cout << " (0 = fine input)\n";
				do {
					polynomial = GetLine(1, csbi.dwSize.X);
					cout << '\n';
				} while (polynomial.empty());
				if (polynomial == L".") return Random;
				Option = ConvertWStringToEnum(polynomial);
				Option = ReassigneEnum(Option);
				if (Option != NotAssigned) {
					system("cls");
					LPCWSTR title = polynomial.c_str();
					SetConsoleTitle(title);
					return Option;
				}

				// rimozione spazi
				for (int i = polynomial.size() - 1; i >= 0; i--)
					if (polynomial.at(i) == ' ' || polynomial.at(i) == '\t')
						polynomial.erase(i, 1);

				// controllo
				No = !Syntax(polynomial);
				if (No) {
					SetConsoleTextAttribute(hConsole, 15);
					wcout << "quello non è un polinomio in una variabile\n";
				}

			} while (No);
			if (polynomial == L"0") break;

			// somma
			polydata = GetMonomials(polynomial);
			pdata = PolynomialSum(polydata);

			// risultato della somma
			polynomial = GetFactor(pdata);
			if (size(polydata) != size(pdata)) {
				SetConsoleTextAttribute(hConsole, 2);
				if (polynomial.empty()) polynomial = L"0";
				wcout << "qualche calcolo dopo: " << polynomial << '\n';
				empty = 0;
			}

			// raccoglimento totale
			polydata = pdata;
			deque <deque <MONOMIAL>> BackT;
			deque <deque <MONOMIAL>> Back_T;
			deque <deque <MONOMIAL>> HT = Total(polydata);
			int sizep;
			polynomial = GetPolynomial(HT, sizep);
			if (size(HT) != 1) {
				SetConsoleTextAttribute(hConsole, 12);
				wcout << "raccoglimento totale: " << polynomial << '\n';
				empty = 0;
			}

			// raccoglimento parziale
			polydata = HT[size(HT) - 1];
			HT.pop_back();
			BackT = Partial(polydata);
			for (deque <MONOMIAL> a : BackT) HT.push_back(a);
			pol = GetPolynomial(HT, sizep);
			if (pol != polynomial) {
				polynomial = pol;
				SetConsoleTextAttribute(hConsole, 4);
				wcout << "raccoglimento parziale: " << polynomial << '\n';
				empty = 0;
			}

			do {

				// potenza di binomio
				ClosePolynomial(HT);
				Back_T = HT;
				HT = {};
				for (deque <MONOMIAL> a : Back_T) {
					BackT = Binomial(a);
					for (deque <MONOMIAL> b : BackT) HT.push_back(b);
				}
				ClosePolynomial(HT);
				pol = GetPolynomial(HT, sizep);
				if (pol != polynomial && !Xout) {
					polynomial = pol;
					SetConsoleTextAttribute(hConsole, 3);
					wcout << "potenza di binomio scomposta: ";
					wcout << polynomial << '\n';
					empty = 0;
				}

				// trinomio speciale
				Back_T = HT;
				HT = {};
				for (deque <MONOMIAL> a : Back_T) {
					BackT = Trinomial(a);
					for (deque <MONOMIAL> b : BackT) HT.push_back(b);
				}
				ClosePolynomial(HT);
				pol = GetPolynomial(HT, sizep);
				if (pol != polynomial && !Xout) {
					polynomial = pol;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "trinomio speciale scomposto: ";
					wcout << polynomial << '\n';
					empty = 0;
				}

				// differenza di quadrati
				Back_T = HT;
				HT = {};
				int extend = 1;
				for (deque <MONOMIAL> a : Back_T) {
					if (a[0].degree == -1) {
						extend = a[0].coefficient;
						continue;
					}
					BackT = SquareDifference(a);
					for (deque <MONOMIAL> b : BackT) {
						if (extend > 1)
							HT.push_back({ {-1, extend} });
						HT.push_back(b);
					}
					extend = 1;
				}
				ClosePolynomial(HT);
				pol = GetPolynomial(HT, sizep);

				// somma per differenza
				if (pol != polynomial && !Xout) {
					polynomial = pol;
					SetConsoleTextAttribute(hConsole, 5);
					wcout << "differenza di quadrati scomposta: ";
					wcout << polynomial << '\n';
					empty = 0;
				}

				// scomposizione con ruffini
				Back_T = HT;
				POL = GetPolynomial(HT, sizep);
				HT = {};
				for (deque <MONOMIAL> a : Back_T) {
					BackT = Ruffini(a);
					if (size(a) > 0 && size(BackT) == 0) {
						Xout = 1;
						break;
					}
					for (deque <MONOMIAL> b : BackT) HT.push_back(b);
				}

				// ruffini
				ClosePolynomial(HT);
				pol = GetPolynomial(HT, sizep);
				if (pol != polynomial && !Xout) {
					polynomial = pol;
					SetConsoleTextAttribute(hConsole, 6);
					wcout << "applicazione della regola di ruffini: ";
					wcout << polynomial << '\n';
					empty = 0;
				}
			} while (pol != POL);

			// completamento del quadrato
			Back_T = HT;
			HT = {};
			for (deque <MONOMIAL> a : Back_T) {
				BackT = CompleteTheSquare(a);
				for (deque <MONOMIAL> b : BackT) HT.push_back(b);
			}
			ClosePolynomial(HT);
			pol = GetPolynomial(HT, sizep);
			if (pol != polynomial && !Xout) {
				polynomial = pol;
				SetConsoleTextAttribute(hConsole, 79);
				wcout << "completamento del quadrato: " << polynomial;
				SetConsoleTextAttribute(hConsole, 15);
				cout << '\n';
				empty = 0;
			}

			// caso vuoto
			if (empty && !Xout) {
				SetConsoleTextAttribute(hConsole, 15);
				wcout << "il polinomio non è scomponibile";
				wcout << " con i metodi standard\n";
			}

			// caso impossibile
			if (Xout) {
				SetConsoleTextAttribute(hConsole, 64);
				cout << "X_OUT_OF_RANGE";
				SetConsoleTextAttribute(hConsole, 15);
				cout << '\n';
			}
		}

		return NotAssigned;
	}

	using namespace Algebraic;
	static switchcase DecompAlgebraic()
	{
		using Convalid::Syntax;
		using Traduce::GetPolynomial;
		using namespace HandPolynomials;
		setlocale(1, "");
		SetConsoleOutputCP(CP_UTF8);
		wcout.imbue(locale(""));
		switchcase Option;
		
		SetConsoleTextAttribute(hConsole, 14);
		cout << "il programma scompone le frazioni algebriche\n";

		while (true) {

			// input della frazione algebrica
			wstring numerator, denominator;
			bool No1, No2, skip = 0;
			do {

				// input
				SetConsoleTextAttribute(hConsole, 15);
				cout << "\ninserisci una frazione algebrica";
				cout << " (0 = fine input)\n\n";
				do GetFraction(numerator, denominator);
				while (numerator.empty());
				HAS_BEEN_PRINTED = 1;

				if (numerator == L".") return Random;
				Option = ConvertWStringToEnum(numerator);
				Option = ReassigneEnum(Option);
				if (Option != NotAssigned) {
					system("cls");
					LPCWSTR title = numerator.c_str();
					SetConsoleTitle(title);
					return Option;
				}

				// controllo
				No1 = !Syntax(numerator);
				No2 = !Syntax(denominator) || denominator == L"0";
				if (No1 || No2) {
					SetConsoleTextAttribute(hConsole, 10);
					wcout << "quella non e' una frazione algebrica\n";
					SetConsoleTextAttribute(hConsole, 15);
				}

			} while (No1 || No2);
			if (numerator == L"0") break;

			// semplificazione fattori
			deque <deque <MONOMIAL>> NScomp = GetDecomp(numerator);
			deque <deque <MONOMIAL>> DScomp = GetDecomp(denominator);
			ClosePolynomial(DScomp);
			if (size(NScomp) == 0 || size(DScomp) == 0)
				skip = 1;
			int NCOEFF = 1, DCOEFF = 1;
			if (!skip) Simplify(NScomp, DScomp, NCOEFF, DCOEFF);
			if (size(DScomp) == 1) skip = 1;
			if (!skip) for (deque <MONOMIAL> a : DScomp) 
				for (MONOMIAL b : a) 
					if (size(a) != 1 && b.degree > 1) skip = 1;

			// calcolo denominatori
			bool is_modifier = 0;
			deque <deque <deque <MONOMIAL>>> denominators;
			deque <deque <MONOMIAL>> complementaries;
			int index = 0;
			if (!skip) for (int i = 0; i < size(DScomp); i++) {
				if (DScomp[i][0].degree == -1) {
					is_modifier = 1;
					continue;
				}

				// caso con le potenze
				if (is_modifier)
					for (int j = DScomp[i - 1][0].coefficient; j > 0; j--)
					{
						denominators.push_back({});
						if (j > 1)
							denominators[index].push_back({ {-1, j} });
						denominators[index].push_back(DScomp[i]);
						index++;
						complementaries.push_back(
							Complementary(DScomp, DScomp[i], j)
						);
					}
				else if (size(DScomp[i]) == 1)

					// caso con le potenze della variabile
					for (int j = DScomp[i][0].degree; j > 0; j--)
					{
						denominators.push_back({});
						denominators[index].push_back({ {j, 1} });
						index++;
						deque <deque <MONOMIAL>> NewScomp = DScomp;
						NewScomp.erase(NewScomp.begin() + i);
						NewScomp.insert(NewScomp.begin() + i, { {1, 1} });
						NewScomp.insert(NewScomp.begin() + i, { 
							{-1, DScomp[i][0].degree} }
						);
						complementaries.push_back(
							Complementary(NewScomp, NewScomp[i + 1], j)
						);
					}

				// caso senza potenze
				else {
					denominators.push_back({});
					denominators[index].push_back(DScomp[i]);
					index++;
					complementaries.push_back(
						Complementary(DScomp, DScomp[i], 1)
					);
				}
				is_modifier = 0;
			}
			if (!skip) for (int i = 0; i < size(complementaries); i++)
				complementaries[i] = FillPolynomial
						(complementaries[i], size(complementaries));
			
			// inizializzazione matrice
			deque <deque <int>> Matrix;
			if (!skip) for (int i = 0; i < size(complementaries); i++)
				Matrix.push_back({});
			if (!skip) for (int i = 0; i < size(complementaries); i++)
				for (int j = 0; j < size(complementaries); j++)
					Matrix[i].push_back(complementaries[i][j].coefficient);

			// calcolo determinanti
			deque <MONOMIAL> Results;
			deque <int> results;
			deque <double> roots;
			int Det;
			deque <MONOMIAL> Quotient;
			deque <MONOMIAL> Rest;
			if (!skip) {

				// divisione polinomi
				if (size(results) != size(complementaries)) {
					Results = PolynomialMultiply(NScomp);
					Results = FillPolynomial(Results, size(complementaries));
					PolynomialDivide(
						Results,
						PolynomialMultiply(DScomp),
						Quotient,
						Rest
					);
				}
				Results = FillPolynomial(Rest, size(complementaries));
				SortDeq(Results);
				for (MONOMIAL R : Results) results.push_back(R.coefficient);
				Det = Determinant(Matrix);
			}
			if (!skip) for (int i = 0; i < size(results); i++) {
				deque <deque <int>> MX = Matrix;
				MX[i] = results;
				roots.push_back((double) Determinant(MX) / Det);
			}

			// eliminazione degli zeri
			for (int i = size(denominators) - 1; i >= 0; i--)
				if (roots[i] == 0) {
					denominators.erase(denominators.begin() + i);
					roots.erase(roots.begin() + i);
				}
			if (size(roots) == 0) skip = 1;

			// output frazioni
			if (!skip) {
				SetConsoleTextAttribute(hConsole, 10);
				wcout << L"\nla scomposizione e' \n\n";
				SetConsoleTextAttribute(hConsole, 12);
			}
			bool ShowPlus = 0;
			int lines = 0;
			if (!skip) for (int i = 0; i < size(denominators); i++) {
				PrintFraction
				(NCOEFF, DCOEFF, roots[i], lines, ShowPlus, denominators[i]);
				ShowPlus = 1;
			}

			// reset cursore
			GetConsoleScreenBufferInfo(hConsole, &csbi);
			COORD cursorPos = csbi.dwCursorPosition;
			cursorPos.X++;
			cursorPos.Y++;
			SetConsoleCursorPosition(hConsole, cursorPos);

			// output polinomio di resto
			if (!skip) for (MONOMIAL a : Quotient) {
				int size_s = 0;
				wstring pol = GetPolynomial({ {a} }, size_s);
				pol.erase(pol.size() - 1);
				pol.erase(0, 1);
				bool is_minus = 0;
				if (pol.at(0) == '-') {
					pol.erase(0, 1);
					is_minus = 1;
				}
				else if (pol.at(0) == '+') pol.erase(0, 1);
				is_minus ? cout << "- " : cout << "+ ";
				wcout << pol << ' ';
			}
			cout << "\n\n";

			// caso impossibile
			if (skip) {

				// reset cursore
				GetConsoleScreenBufferInfo(hConsole, &csbi);
				COORD cursorPos = csbi.dwCursorPosition;
				cursorPos.Y -= 2;
				SetConsoleCursorPosition(hConsole, cursorPos);

				// messaggio di errore
				SetConsoleTextAttribute(hConsole, 64);
				cout << "NON E' POSSIBILE SCOMPORRE!!";
				SetConsoleTextAttribute(hConsole, 15);
				cout << '\n';
			}
		}

		return NotAssigned;
	}
}

// programma principale
int main()
{
	setlocale(1, "");
	SetConsoleOutputCP(CP_UTF8);
	wcout.imbue(locale(""));

	using namespace EnumMod;
	using Print::WaitingScreen;
	using namespace Input;
	using Primitive::SieveOfErastothens;
	using namespace Execute;
	using namespace Programs;
	
	// dichiarazione stringhe
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
				wstring G = GetUserNum(text, 0, GLOBAL_CAP, 0);
				if (ConvertWStringToEnum(G) != NotAssigned) redo = 1;
				else if (G.empty()) redo = 1;

				// termine programma
				else if (G == L".") goto End;

				// casi 0 e 1
				else global = stoi(G);
				if (global == 1) redo = 1;
				if (global == 0) {
					lock_prime_input = 1;
					if (start) redo = 1;
				}
			} while (redo);
			SetConsoleTextAttribute(hConsole, 15);

			// output del tempo
			if (global != 0 or start) {
				steady_clock::time_point begin = steady_clock::now();
				GlobalMax = global;
				SetConsoleCursorInfo(hConsole, &cursorInfo);
				PrimeNumbers = SieveOfErastothens(GlobalMax, 1);
				steady_clock::time_point end = steady_clock::now();
				WaitingScreen(begin, end);
				SetConsoleTextAttribute(hConsole, 15);
				SetConsoleCursorInfo(hConsole, &cursor);
				start = 0;
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
		cout << "\t\"ctn\" = da codice a numero\n";
		cout << "\t\"pol\" = scomposizione polinomi\n";
		cout << "\t\"alg\" = scomposizione frazioni algebriche\v";
		SetConsoleTextAttribute(hConsole, 11);
		cout << "oppure:\n";
		cout << "primo carattere:\n";
		cout << "\t'c' = calcolo\n";
		cout << "\t'd' = debug\n";
		cout << "caratteri seguenti:\n";
		cout << "\t'c' = solo codifica\n";
		cout << "\t'f' = scomposizione in fattori primi\n";
		cout << "\t\"cc\" = codifica, sequenza e grado\n";
		cout << "\t\"ff\" = fattoizzazione e dati dei divisori\n";
		cout << "\t\"cf\" = codifica e fattorizzazione\n";
		cout << "\t\"t\" = tutti i dati\n";
		cout << "selezionando più operazioni, il tempo di calcolo aumenta\v";

		SetConsoleTextAttribute(hConsole, 15);
		vel = GetLine(1, 10);
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
				case '.': goto End;
					break;
				default: vel += ' ';
				}
			}

			// caso input non assegnato correttamente
			if (option == NotAssigned) do {
				skip = 0;
				cout << "scegli opzioni:: (...)\n";
				vel = GetLine(1, 10);
				if (vel.size() == 1) {
					stop = vel.at(0) != '0'
						and vel.at(0) != '1' and vel.at(0) != '.';
				}
				else {
					option = ConvertWStringToEnum(vel);
					stop = option == NotAssigned;
					skip = option != NotAssigned;
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
			case DoSimpleCode:
				option = Repeater(simpledeg, ExecuteSimpledeg);
				break;
			case DoComplexCode:
				option = Repeater(message, ExecuteDegree);
				break;
			case DoSimpleFactor:
				option = Repeater(simplefact, ExecuteSimpleFact);
				break;
			case DoComplexFactor:
				option = Repeater(fact_message, ExecuteFactor);
				break;
			case DoCodeFactor:
				option = Repeater(def_sct, ExecuteSimpleDF);
				break;
			case DoAll:
				option = Repeater(AllMessage, ExecuteDegFactor);
				break;
			case DebugSimpleCode:
				option = Loop(desimpledeg, ExecuteSimpledeg);
				break;
			case DebugComplexCode:
				option = Loop(deg_message, ExecuteDegree);
				break;
			case DebugSimpleFactor:
				option = Loop(desimplefact, ExecuteSimpleFact);
				break;
			case DebugComplexFactor:
				option = Loop(defact_message, ExecuteFactor);
				break;
			case DebugCodeFactor:
				option = Loop(def_sct, ExecuteSimpleDF);
				break;
			case DebugAll:
				option = Loop(AllMessage, ExecuteDegFactor);
				break;
			case ConvertCodeInverse:
				option = CodeToNumber();
				break;
			case FactorPolynomial:
				option = DecompPolynomial();
				break;
			case FactorFraction:
				option = DecompAlgebraic();
				break;
			}
			if (option == Random) goto End;

		} while (option != NotAssigned);
	}

// fine del programma
End:
	system("cls");
	SetConsoleTextAttribute(hConsole, 4);
	return 0;
}
// program_END
