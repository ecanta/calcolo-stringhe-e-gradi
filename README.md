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

In questa sezione verranno documentate le classi e funzioni principali del progetto, con esempi su come integrarle in altri progetti.

<h2>Autore</h2>

Programma realizzato interamente da **Emanuele Cantarelli**.
