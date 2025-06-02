<h1>Calcolatore di Scomposizioni</h1>

Questo è un ampio progetto interamente realizzato in C++,
che include numerose classi e funzioni pensate per lavorare con **espressioni algebriche, numeri interi, matrici, frazioni**, e molto altro ancora.

<h2>Requisiti per la compilazione</h2>

+ Sistema operativo (`OS`): **Windows**
+ IDE: **Microsoft Visual Studio** (⚠️ *non* compatibile con Visual Studio Code, Dev-C++, né compilatori online)
+ Supporto per lo standard **C++20** (alcune funzionalità potrebbero essere adattabili a C++17 con modifiche)

<h2>Funzionalità</h2>

+ **Calcolo rapido dei numeri primi**: ad esempio, può calcolare tutti i numeri primi fino a 2.000.000.000 in circa un secondo su un buon PC.
+ **Barre di progresso** e **animazioni** durante i calcoli lunghi.
+ **Modalità di calcolo personalizzabili**, tra cui:
  + **Conversione di numeri in esadecimale**
  + **Ricerca del numero primo in posizione N** (es. 13° primo = 41)
  + **Scomposizione in fattori primi**
  + Codifica dei numeri in stringhe che rappresentano la loro scomposizione in modo compatto e simbolico
    *Esempio*: `234 = 2 * 3^2 * 13 = <1+22+(1+2)1>`. Qui `2 = <1>`, `3^2 = <2>^2 = <22>`, 13 è il 6° primo →
    `6 = 2 * 3 = <1>*<2> = <1+2> quindi 13 = <(1+2)1>`.)
  + Numero di iterazioni necessarie per ridurre un numero a 1, applicando ripetutamente la codifica
    *Esempio*: `1234 = <1+(1+2+3)2>` → `13 = <(1+2)1>` → `3` → `2` → `1` → 5 passi.
  + **Calcolo di numero, somma e prodotto dei divisori** di un numero.
+ **Elaborazione in intervalli**: tutte le funzioni sopra possono essere applicate a un intervallo di numeri,
  filtrandoli anche in base alle proprietà delle loro cifre.
+ **Espressioni costanti nei campi numerici**: è possibile inserire espressioni come `(x+1)^2 - x^2 - 2x - 1 + 34`,
  che viene valutata come 34 poiché il risultato è costante (cioè le variabili si semplificano e spariscono).
+ **Conversione inversa** da stringa codificata a numero. In caso di errore nella stringa, viene mostrato un messaggio dettagliato.
  È possibile usare caratteri `_` come jolly per cercare tutte le stringhe valide. Il calcolo può essere **interrotto in qualsiasi momento**.
+ **Navigazione tra modalità**: è possibile cambiare modalità scrivendo il nome desiderato.
  I nomi delle modalità sono elencati nella schermata principale (HOME) e possono essere completati automaticamente con il tasto **Tab**.
+ Codifica e manipolazione basata sulle **sequenze di Goodstein**, una forma alternativa di rappresentazione numerica.
+ Modalità **casuale**, che seleziona automaticamente un'opzione tra quelle disponibili.
+ **Scomposizione di polinomi** (anche multivariati), con supporto per:
  + Coefficienti frazionari e numeri complessi
  + Operazioni con numeri molto grandi
  + **Fast Fourier Transform (FFT)** per moltiplicazioni efficienti
+ **Interpretazione automatica degli esponenti** in formato *superscript*, anche prima dell'invio. Questa funzionalità è disattivabile.
+ **Scomposizione di matrici quadrate** (dimensioni da 2 a 7), con supporto per:
  + Operazioni tra matrici
  + Riempimento automatico con numeri casuali
  + Decomposizioni: **PLU**, **QR**, **Cholesky**, **SVD**
  + Calcolo di **determinante**, **autovalori** e **autovettori**
+ Supporto per **matrici con elementi frazionari**
+ **Calcolo della radice quadrata di un numero**, inserendolo nella diagonale principale di una matrice insieme ad altri numeri scelti;
  in alcune scomposizioni matriciali è possibile ricavare la radice quadrata del numero analizzando il risultato.
+ Operazioni con **frazioni algebriche composte**, cioè frazioni con altre frazioni al numeratore o denominatore
+ **Storico degli input** inseriti (numeri, polinomi, matrici, frazioni)
+ **Trasferimento di espressioni** tra modalità, con possibilità di **sostituire variabili** o aggiungerne di nuove
+ Valutazione simultanea di più espressioni (es. sistemi di equazioni), anche **parametrici** o **non lineari**
+ **Scomposizione in frazioni parziali** delle frazioni algebriche (utile anche per l'integrazione)
+ **Risoluzione di disequazioni** (anche parametriche) associate a frazioni algebriche
+ **Visualizzazione grafica** delle funzioni (una o due variabili), inclusi:
  + Punti notevoli
  + Più funzioni contemporaneamente (solo grafico a una variabile)
  + Derivazione automatica (solo grafico a una variabile)
  + **Controllo tramite tastiera e mouse**
+ **Adattamento automatico della finestra della console** in base allo spazio disponibile

<h2>Utilizzo</h2>

Puoi compilare il programma direttamente in Visual Studio oppure eseguire l'eseguibile già compilato.
Tutte le istruzioni per l’utilizzo verranno mostrate nelle schermate varie del programma.

<h2>Libreria: funzioni e classi utili e come utilizzarle</h2>

In tensor.cpp:

contenuti del namespace `std_tensor`:

+ classe `tensor`:
 
  E' una versione ottimizzata e personalizzata di un vettore; contiene
  + metodo `resize` (protetto): cambia la dimensione del tensore
  + operatori `=` e metodo `assign` per l'assegnazione
  + metodi `Data`, `size`, `get_capacity` per ottenere rispettivamente array degli elementi, dimensione e capacità
  + metodo `empty` per verificare se il tensore è vuoto
  + operatore `[]` e metodo `at` per accedere agli elementi
  + metodo `last` per accedere all'ultimo elemento
  + metodo `clear` per svuotare il tensore
  + metodo `erase` per eliminare elementi secondo vari criteri
  + metodi `push_back` (= operatore `<<`) e `push_front` (= operatore `>>`) per aggiungere elementi alla fine o all'inizio del tensore
  + metodi `pop_back` (= operatore `--` posto dopo l'oggetto) e `pop_front` (= operatore `--` posto prima dell'oggetto) per rimuovere
    elementi alla fine o all'inizio del tensore
  + operatori `++` per aggiungere un elemento vuoto
  + operatore `-=` per rimuovere un numero prefissato di elementi dalla fine
  + operatore `()` per fissare la dimensione del tensore
  + operatori di confronto
  + operatori `+` e `+=` per concatenare due tensori
  + operatori di confronto con un intero (confrontano la dimensione del tensore con tale intero)
  + operatori `&&` (and), `||` (or) e `%` (xor) per confrontare le dimensioni tra due tensori
  + classe `iterator`: iteratore normalissimo
  + metodi `begin` e `end` che restituiscono tali iteratori
  + metodo `insert` per inserire dei valori a posizioni specifiche
  + metodo `remove` per rimuovere le occorrenze di un valore
  + metodo `str` per visualizzare i contenuti del tensore sotto forma di stringa
  + operatore `<<` di wostream
+ classe `tensor_t`:
  Contiene due tensori, uno per i numeri primi e l'altro per il crivello
<br>

In calcolo stringhe e gradi.cpp:

+ struttura `compost`: rappresenta un fattore primo di un numero con il suo esponente
+ struttura `divisor`: contiene i dati dei divisori di un numero
+ struttura `digitRatio`: contiene i dati delle cifre di un numero
+ struttura `coord`: `COORD` di Windows ma in virgola mobile

<br>

+ enum `switchcase`: è la lista di tutti gli indirizzi dei sottoprogrammi del programma principale
+ mappa `stringToEnumMap`: mappa le direttive con gli indirizzi
+ mappa `enumToStringMap`: mappa gli indirizzi con le direttive
+ mappa `ConvertFromSuperScript`: mappa gli apici con le cifre a cui corrispondono

<br>

+ stringa `Variables`: contiene l'ordine delle variabili in tutti i polinomi nel programma (è unico)
+ funzione `Smaller`: confronta due valori
+ funzione `BinarySearch`: ricerca un elemento in un tensore con la ricerca binaria

<br>

+ classe `complex`:

  Rappresenta un numero complesso; contiene:
  + metodo `norm` per calcolare il modulo
  + operatori di confronto che confrontano i moduli di due numeri complessi
  + metodo `conjugate` che calcola il coniugato complesso
  + metodo `opposite` per calcolare l'opposto del numero complesso
  + operatori aritmetici
  + metodo `str` per convertire in stringa
+ funzione `InitExponentialForm` per ottenere un numero complesso dalla forma esponenziale

<br>

+ funzione `FFT` per calcolare la trasformata di fourier e la trasformata inversa
+ classe `big`:

  Rappresenta numeri molto grandi; contiene
  + metodo `construct` (privato): elenca le cifre di un intero ed è usato nei costruttori
  + metodo `compare` (privato): confronta i valori assoluti di due numeri grandi
  + metodo `Add` (privato): esegue la somma dei valori assoluti
  + metodo `Sub` (privato): esegue la differenza dei valori assoluti
  + metodo `AlgebricOperation1` (privato): esegue l'addizione algebrica
  + metodo `FFT_Multiplication` (privato): esegue la moltiplicazione grazie alla FFT
  + metodo `Number` per convertire in un intero o in un numero in virgola mobile
  + operatore `=` per assegnare
  + operatori di confronto
  + operatori matematici compresi `%` e `^` (potenza)
  + operatori di shifting, che eseguono lo shifting in base 10
  + metodo `Size` per ottenere la dimensione del tensore di cifre
  + metodo `intg` per sapere se è intero
  + metodo `fabs` per ottenere il valore assoluto
  + metodo `floor` per ottenere la parte intera
  + metodo `ceil` per ottenere il ceiling
  + metodo `round` per arrotondare
  + metodo `invert` per invertire il numero
  + metodo `log` per calcolare il logaritmo
  + metodo `c_str` per convertire in wostringstream
  + metodo `str` per convertire in stringa
  + operatore `<<` di wostream
+ funzione `pow` per calcolare l'elevamento a potenza con base big

<br>

+ funzione `GeneralizedHeapify`: serve per l'heap sort
+ funzione `GeneralizedHeapSort`: ordina velocemente un tensore

<br>

+ classe `RadicalUnit`:

  E' un radicale semplice; contiene
  + metodo `GetCoefficient` per ottenere il coefficiente
  + metodo `SetCoefficient` per impostare il coefficiente
  + metodo `IncCoefficient` per incrementare il coefficiente
  + metodo `approximation` per convertire in virgola mobile
  + metodo `normalize` per eliminare eventuali errori interni
  + operatori `+`, `-`, `/` che restituiscono un valore in virgola mobile
  + operatori `*` e `*=` per calcolare il prodotto di due radicali semplici
  + operatori di confronto
  + metodo `negative` per determinare se è negativo
  + metodo `len` per calcolare l'estensione del radicale su console
  + metodo `write` per scrivere il radicale su console
  + metodo `str` per convertire in stringa e usato a scopi di debug
  + operatore `<<` di wostream

+ classe `RadicalExpr`:

  E' una somma di radicali semplici; contiene
  + metodo `unitary` per sapere se è un radicale semplice
  + metodo `intg` per capire se è un numero intero
  + metodo `approximation` per convertire in virgola mobile
  + metodo `normalize` per eliminare gli errori
  + metodo `NORMALIZE` per eliminare gli errori estensivamente
  + operatore `/` che restituisce un valore in virgola mobile
  + operatori `+`, `+=`, `-`, `-=`, `*`, `*=` che calcolano il risultato in radicali
  + operatori di confronto
  + metodo `len` che calcola l'estensione del radicale su console
  + metodo `write` per scrivere il radicale su console
  + metodo `str` per convertire in stringa e usato a scopi di debug
  + operatore `<<` di wostream

<h2>Autore</h2>

Programma realizzato interamente da **Emanuele Cantarelli**.