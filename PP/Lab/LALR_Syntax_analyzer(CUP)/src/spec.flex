// import sekcija

%%

// sekcija opcija i deklaracija
%class MPLexer  

//%cup
%implements java_cup.runtime.Scanner
%function next_token
%type java_cup.runtime.Symbol

%function next_token
%line
%column
%debug
%type Symbol

%eofval{
return new Symbol( sym.EOF);
%eofval}

%{
//dodatni clanovi generisane klase
KWTable kwTable = new KWTable();
Symbol getKW()
{
	return new Symbol( kwTable.find( yytext()));
}

int getLine()
{
    return yyline;
}
%}

//stanja
%xstate KOMENTAR

//makroi
slovo = [a-zA-Z]
velikoSlovo = [A-Z]
cifra = [0-9]

%%

// pravila
"comm" { yybegin( KOMENTAR ); }
<KOMENTAR>~"~comm" { yybegin( YYINITIAL ); }

[\t\n\r ] { ; }
\( { return new Symbol( sym.LEFTPAR); }
\) { return new Symbol( sym.RIGHTPAR); }

//operatori
\+ { return new Symbol( sym.PLUS); }
\* { return new Symbol( sym.MUL); }
"less" { return new Symbol( sym.LESS); }
"greater" { return new Symbol( sym.GREATER); }
"equal" { return new Symbol( sym.EQUAL); }

//separatori
; { return new Symbol( sym.SEMICOLON); }
: { return new Symbol( sym.COLON); }
, { return new Symbol( sym.COMMA); }
:= { return new Symbol( sym.ASSIGN); }
\{ { return new Symbol( sym.LEFTCURVEDPAR); }
\} { return new Symbol( sym.RIGHTCURVEDPAR); }


//identifikatori
{velikoSlovo}({velikoSlovo}|{cifra})* { return new Symbol(sym.ID, yyline, yytext()); }

//kljucne reci
\~?{slovo}+ {
              Symbol a = getKW();
              if (a.sym >= 0)
                { return a; }
              System.out.println( "error: " + yytext() );
              return new Symbol( sym.error);
            }

//konstante
{cifra}+ { return new Symbol( sym.CONST, yyline, new Integer(yytext())); }
\".*\" { return new Symbol( sym.CONST, yyline, new String(yytext())); }
-?[0-9]+\.[0-9]+ { return new Symbol( sym.CONST, yyline, new Double(yytext())); }

//obrada gresaka
. { 
    if (yytext() != null && yytext().length() > 0) System.out.println( "error: " + yytext() );
    
    return new Symbol( sym.error); 
  }
