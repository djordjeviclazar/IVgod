// import sekcija

%%

// sekcija opcija i deklaracija
%class MPLexer
%function next_token
%line
%column
%debug
%type Yytoken

%eofval{
return new Yytoken( sym.EOF, null, yyline, yycolumn);
%eofval}

%{
//dodatni clanovi generisane klase
KWTable kwTable = new KWTable();
Yytoken getKW()
{
	return new Yytoken( kwTable.find( yytext() ),
	yytext(), yyline, yycolumn );
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
\( { return new Yytoken( sym.LEFTPAR, yytext(), yyline, yycolumn ); }
\) { return new Yytoken( sym.RIGHTPAR, yytext(), yyline, yycolumn ); }

//operatori
\+ { return new Yytoken( sym.PLUS,yytext(), yyline, yycolumn ); }
\* { return new Yytoken( sym.MUL,yytext(), yyline, yycolumn ); }
"less" { return new Yytoken( sym.LESS, yytext(), yyline, yycolumn); }
"greater" { return new Yytoken( sym.GREATER, yytext(), yyline, yycolumn); }
"equal" { return new Yytoken( sym.EQUAL, yytext(), yyline, yycolumn); }
//separatori
; { return new Yytoken( sym.SEMICOLON, yytext(), yyline, yycolumn ); }
: { return new Yytoken( sym.COLON, yytext(), yyline, yycolumn ); }
, { return new Yytoken( sym.COMMA, yytext(), yyline, yycolumn ); }
\. { return new Yytoken( sym.DOT, yytext(), yyline, yycolumn ); }
:= { return new Yytoken( sym.ASSIGN, yytext(), yyline, yycolumn ); }
\{ { return new Yytoken( sym.LEFTCURVEDPAR, yytext(), yyline, yycolumn ); }
\} { return new Yytoken( sym.RIGHTCURVEDPAR, yytext(), yyline, yycolumn ); }


//identifikatori
{velikoSlovo}({velikoSlovo}|{cifra})* { return new Yytoken(sym.ID, yytext(),yyline, yycolumn ); }

//kljucne reci
\~?{slovo}+ {
              Yytoken a = getKW();
              if (a.m_index >= 0)
                { return a; }
              System.out.println( "ERROR: " + yytext() );
              return new Yytoken( sym.ERROR, yytext(), yyline, yycolumn );
            }

//konstante
{cifra}+ { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }
\".*\" { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }
-?[0-9]+\.[0-9]+ { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }

//obrada gresaka
. { 
    if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: " + yytext() );
    
    return new Yytoken( sym.ERROR, yytext(), yyline, yycolumn ); 
  }
