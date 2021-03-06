# IVgod(zadaci, primeri, ...)

## Paralelni sistemi

### Lab

#### Termin1

<!--
	<img src="PS/Lab/Tekst zadataka/lab1.png">
-->
<!--
	Ne sme da ima blanko znak kod linka, %20 mora umesto blanko
	- InvisibleWolf: https://stackoverflow.com/questions/7653483/github-relative-link-in-markdown-file/46189724#46189724
-->
[Tekst zadataka](PS/Lab/Tekst%20zadataka/PRS_Domaci_zadatak%20CUDA.pdf)

#### Termin2

[Tekst zadataka za pripremu](PS/Lab/Tekst%20zadataka/PRS_Lab1_CUDA.pdf)

#### Termin3

[Tekst zadataka za pripremu](PS/Lab/Tekst%20zadataka/PRS_Lab_MPI.pdf)

[Uputstvo za podešavanja VS](PS/Lab/Tekst%20zadataka/Visual%20Studio%20i%20kompajliranje%20MS%20MPI%20programa)

[Uputstvo za pokretanje MPI](PS/Lab/Tekst%20zadataka/mpirun)

## Računarska grafika

### Lab

#### LV01 - GDI - TANGRAM - ZADATAK (18.11.2020 - 24.11.2020)

##### Zadatak:

Korišćenjem funkcija GDI-ja potrebno je iscrtati figuru kao na slici (dimenzija 500x500 piksela).
Implementirati fukcionalnost uključivanja/isključivanja iscrtavanja mreže (grid-a) na pritisak tastera po izboru
Za crtanje pravilnih mnogouglova koristiti jednačine: ***x=r\*cos(alfa); y=r\*sin(alfa)***

##### Napomena:

Pojedinačni delovi figure treba da se dodiruju ali ne smeju da se preklapaju
Nije dozvoljeno korišćenje funkcije FloodFill za ispunu unutrašnjosti pojedinačnih delova figure

<img src="RG/Lab/lab1.png">

#### LV02 - GDI - TRANSFORMACIJE - ZADATAK (28.11.2020 - 03.12.2020)

<img src="RG/Lab/lab2.png">

#### LV03 - GDI - BITMAPE - MONAPUZZLE - ZADATAK (05.12.2020 - 12.12.2020)

<img src="RG/Lab/lab3.png">

#### LV04 - OPENGL - TRANSFORMACIJE

<img src="RG/Lab/lab4.png">

#### LV05 - OPENGL - OSVETLJENJE

<img src="RG/Lab/lab5.png">

#### LV06 - OPENGL - TEKSTURE

<img src="RG/Lab/lab6.png">

### Priprema za ispit

#### Kolokvijum I 2018

<img src="RG/Priprema/Tekst/2018_Kol1_tekst1.png">
<img src="RG/Priprema/Tekst/2018_Kol1_tekst2.png">

#### Kolokvijum II 2018

<img src="RG/Priprema/Tekst/2018_Kol2_tekst1.png">
<img src="RG/Priprema/Tekst/2018_Kol2_tekst2.png">
<img src="RG/Priprema/Tekst/2018_Kol2_tekst3.png">


## Zaštita informacija

### Domaći

#### Zad A1, B1

ARC4, f-je za kriptovanje, dekriptovanje, upis i čitanje iz fajla

#### Zad A2, B2

Bifid, f-je za kriptovanje, dekriptovanje, 
upis i čitanje iz .bmp fajla

#### Zad A3, B3

RSA, f-je za kriptovanje, dekriptovanje, 
CRC za proveru validnosti, 
optimalnije čitanje iz fajla (fajlovi 100MB, kriptuju se blokovi)

#### Zad A4, B4

Primeniti CBC mod kodera na neki od prethodnih algoritama za kodiranje (ARC4),
Paralelizovati kodiranje, čitanje i upis

## Programski prevodioci

*Zad1-3 folder PP/Lab/Termin1*
*Dokumentacija: PP/Dokumenti*

### Lab

#### Zad1

**Grupa 6**

Kreirati **jflex** specifikaciju za generisanje leksičkog analizatora domenski-specifičnog jezika iz oblasti
upravljanja računarskim infrastrukturama koji je definisan datom gramatikom. **Task** je apstrakcija
zadatka koji obavlja neki **Server**, a **Mapping** je alokacija zadatka serveru. **Demand** izražava zahteve
zadatka za resursima, a **Capacity** izražava mogućnost servera da izvršava zadatke (koji imaju manji ili
jednak **Demand**). <br />

Model → **model** Body **~model** <br />
Body → Declarations Statements Deployment <br />
Declarations → VariableDeclaration <br />
VariableDeclaration → VariableDeclaration **;** Variable | Variable <br />
Variable → **ID** ∶ Type **;** <br />
Type → **int** | **double** | **string** <br />
Statements → Statements **;** Statement | Statement <br />
Statement → Assignment | WhileStatement <br />
WhileStatement → **while** **(** RelExpression **)** **:** Statements <br />
RelExpression → Term RelOp Term | Term <br />
Term → **ID** | **CONST** <br />
RelOp → **less** | **equal** | **greater** <br />
Assignment → **ID** ∶= Expression <br />
Deployment → **deployment** TaskList ServerList **~deployment** <br />
ServerList → ServerList **;** ServerDef | ServerDef <br />
ServerDef → **server** ServerName **,** Capacity **~server** <br />
ServerName → **serverId ID** <br />
Capacity → Term <br />
TaskList → TaskList **;** TaskDef | TaskDef <br />
TaskDef → **task** TaskName **,** Demand **,** Mapping **~task** <br />
TaskName → **taskId ID** <br />
Demand → Term <br />
Mapping → **executedOn ID** <br />
Expression → Expression **+** Term | Expression **\*** Term | Term <br />

Terminalni simbol **ID** u ovom programskom jeziku označava identifikator (niz velikih slova i cifara u
kojem prvi znak ne može da bude cifra), a konstante mogu biti: <br />
\4. Konstante tipa **int**: <br />
<niz_cifara> <br />
\5. Konstante tipa **double**: <br />
\[−]<niz_cifara>.<niz_cifara> <br />
\6. Konstante tipa **string**: <br />
''<niz_znakova>'' <br />
Komentari u ovom programskom jeziku počinju simbolom **comm** i završavaju se simbolom
**~comm**

#### Zad2

<img src="PP/Lab/Tekst zadataka/lab2.png">

**Grupa 6**


Statements → Statements **;** Statement | Statement
Statement → Assignment | WhileStatement
WhileStatement → **while (** RelExpression **) : {** Statements **}**
RelExpression → Term **less** Term | Term
Term → **ID | CONST**
Assignment → **ID :=** Term

#### Zad3

<img src="PP/Lab/Tekst zadataka/lab3.png">

<img src="PP/Lab/Tekst zadataka/lab3_grupa6.png">

#### Zad4

<img src="PP/Lab/Tekst zadataka/lab4.png">

#### Zad5

<img src="PP/Lab/Tekst zadataka/lab5.png">

#### Zad6

<img src="PP/Lab/Tekst zadataka/lab6a.png">

<img src="PP/Lab/Tekst zadataka/lab6b.png">

## Veštačka inteligencija

### Lab

#### Pripema1 (Examples/lab1/EasyFunctionsLab1Examples)

#### Pripema2 (Examples/lab2/Lab2Examples)

#### Termin1

Napisati funkciju koja svaki od prvih n elemenata liste atoma uvećava za 1, a preostale umanjuje za \1. Zadatak realizovati u okviru jedne funkcije.

Zaglavlje funkcije: (**promeni** n lista)

Primeri poziva: (**promeni** *’4 ’(5 8 3 8 1 8 6 7 9)*) => *(6 9 4 9 0 7 5 6 8)*

#### Termin2

Definisati funkcije:

a. list_oduzimanje, za oduzimanje elemenata 2 liste, tako da se od prvog elementa prve liste oduzima poslednji element druge liste i tako redom.

(**list_oduzimanje** *'(4 5 6) '(1 2 3)*) -> *(1 3 5)*



b. min, koja pronalazi najmanji element prave liste.

(**min** *'(3 6 1 8 9)*) -> *1*

(**min** *'(((5 6) 9) 3 6 4 (7 1))*) -> *1*

Zadatke je potrebno rešiti rekurzijom. Svaki zadatak realizovati u okviru jedne funkcije.

#### Termin3

<img src="VI/Lab/Tekst zadataka/lab3.png">

*Napomena: za heuristiku misli se na broj grana od početnog čvora (prosleđenog kao argument) do čvora do kog smo stigli prilikom obilaska*

#### Termin4

<img src="VI/Lab/Tekst zadataka/lab4.png">

*Napomena: Rezultat je lista poteza koji dovode do ciljnog stanja, fajl nazvati Ime_Prezime_br.indeksa, obavezno pozvati f-je koje su implementirane u fajlu*
