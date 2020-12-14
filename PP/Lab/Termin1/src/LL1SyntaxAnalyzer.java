import java.io.FileReader;
import java.io.IOException;
import java.util.Stack;

public class LL1SyntaxAnalyzer
{
    class Neterminali
    {
        public final static int Statements = 0;
        public final static int StatementsPrim = 1;
        public final static int Statement = 2;
        public final static int WhileStatement = 3;
        public final static int RelExpression = 4;
        public final static int RelExpressionPrim = 5;
        public final static int Term = 6;
        public final static int Assignment = 7;
    }

    /*
     * Akcije:
     * Smene = 1 - 12
     * Greška = 13
     * Pop = 0
     * Acc = 14
     * */
    private static final int[][] sintaksnaTabela =
            {
                    {1, 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
                    {13, 13, 13, 13, 13, 2, 13, 13, 3, 13, 13, 3},
                    {5, 4, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
                    {6, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
                    {13, 7, 7, 13, 13, 13, 13, 13, 13, 13, 13, 13},
                    {13, 8, 8, 13, 13, 13, 13, 13, 13, 13, 9, 13},
                    {13, 10, 11, 13, 13, 13, 13, 13, 13, 13, 13, 13},
                    {13, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
                    {0, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
                    {13, 0, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
                    {13, 13, 0, 13, 13, 13, 13, 13, 13, 13, 13, 13},
                    {13, 13, 13, 0, 13, 13, 13, 13, 13, 13, 13, 13},
                    {13, 13, 13, 13, 0, 13, 13, 13, 13, 13, 13, 13},
                    {13, 13, 13, 13, 13, 0, 13, 13, 13, 13, 13, 13},
                    {13, 13, 13, 13, 13, 13, 0, 13, 13, 13, 13, 13},
                    {13, 13, 13, 13, 13, 13, 13, 0, 13, 13, 13, 13},
                    {13, 13, 13, 13, 13, 13, 13, 13, 0, 13, 13, 13},
                    {13, 13, 13, 13, 13, 13, 13, 13, 13, 0, 13, 13},
                    {13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 0, 13},
                    {13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14},
            };

    public static void main(String[] args)
    {
        MPLexer lexer;
        try
        {
            java.io.Reader testFile = new FileReader(args[0]);
            lexer = new MPLexer(testFile);


            startAnalyzer(lexer);
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    private static void startAnalyzer(MPLexer lexer) throws IOException
    {
        // inicijalizacija:
        Stack<Integer> magacin = new Stack<>();
        magacin.push(sym.EOF);
        magacin.push(Neterminali.Statements);
        boolean acc = false, error = false;

        int akcija = -1; // kod akcije iz sintaksne tabele koja treba da se izvrši
        // -1 ako treba da se uzme vrednost iz sintaksne tabele
        // (desio se pop)
        // sintaksna analiza:
        do
        {
            if (akcija == -1)
            {
                // novi token
                Yytoken token = lexer.next_token();
                if (token.m_index == sym.ERROR)
                {
                    System.out.println("ERROR on line: " + token.m_line);
                    System.out.println("This sequence doesn't match any token: " + token.m_text);

                    return; // ne nastavljamo nakon greške
                }

                akcija = sintaksnaTabela[magacin.peek()][token.m_index];
                switch (akcija)
                {
                    case 0:
                        pop(magacin);
                        akcija = -1;
                        break;
                    case 1:
                        smena1(magacin);
                        break;
                    case 2:
                        smena2(magacin);
                        break;
                    case 3:
                        smena3(magacin);
                        break;
                    case 4:
                        smena4(magacin);
                        break;
                    case 5:
                        smena5(magacin);
                        break;
                    case 6:
                        smena6(magacin);
                        break;
                    case 7:
                        smena7(magacin);
                        break;
                    case 8:
                        smena8(magacin);
                        break;
                    case 9:
                        smena9(magacin);
                        break;
                    case 10:
                        smena10(magacin);
                        break;
                    case 11:
                        smena11(magacin);
                        break;
                    case 12:
                        smena12(magacin);
                        break;
                    case 13:
                        errorPrint(magacin, token);
                        error = true;
                        break;
                    case 14:
                        accept(magacin);
                        acc = true;
                        break;
                }
            }


        } while (!(acc || error));
    }

    private static void accept(Stack<Integer> magacin)
    {
        System.out.println("Success");
    }

    private static void errorPrint(Stack<Integer> magacin, Yytoken token)
    {
        System.out.println("Error on line: " + token.m_line);
        System.out.println("'" + token.m_text + "'" + " doesn't exist in current context");
    }

    private static void smena12(Stack<Integer> magacin)
    {
        magacin.pop();
        magacin.push(Neterminali.Term);
        magacin.push(sym.ASSIGN);
        magacin.push(sym.ID);
    }

    private static void smena11(Stack<Integer> magacin)
    {
        magacin.pop();
        magacin.push(sym.CONST);
    }

    private static void smena10(Stack<Integer> magacin)
    {
        magacin.pop();
        magacin.push(sym.ID);
    }

    private static void smena9(Stack<Integer> magacin)
    {
        magacin.pop();
    }

    private static void smena8(Stack<Integer> magacin)
    {
        magacin.pop();
        magacin.push(Neterminali.Term);
        magacin.push(sym.LESS);
    }

    private static void smena7(Stack<Integer> magacin)
    {
        magacin.pop();
        magacin.push(Neterminali.RelExpressionPrim);
        magacin.push(Neterminali.Term);
    }

    private static void smena6(Stack<Integer> magacin)
    {
        magacin.pop();
        magacin.push(sym.RIGHTCURVEDPAR);
        magacin.push(Neterminali.Statements);
        magacin.push(sym.LEFTCURVEDPAR);
        magacin.push(sym.COLON);
        magacin.push(sym.RIGHTPAR);
        magacin.push(Neterminali.RelExpression);
        magacin.push(sym.LEFTPAR);
        magacin.push(sym.WHILE);
    }

    private static void smena5(Stack<Integer> magacin)
    {
        magacin.pop();
        magacin.push(Neterminali.WhileStatement);
    }

    private static void smena4(Stack<Integer> magacin)
    {
        magacin.pop();
        magacin.push(Neterminali.Assignment);
    }

    private static void smena3(Stack<Integer> magacin)
    {
        magacin.pop();
    }

    private static void smena2(Stack<Integer> magacin)
    {
        magacin.pop();
        magacin.push(Neterminali.StatementsPrim);
        magacin.push(Neterminali.Statement);
        magacin.push(sym.SEMICOLON + 8); // zato što se neterminali nalaze u donjem delu tabele
    }

    private static void smena1(Stack<Integer> magacin)
    {
        magacin.pop();
        magacin.push(Neterminali.StatementsPrim);
        magacin.push(Neterminali.Statement);
    }

    private static void pop(Stack<Integer> magacin)
    {
        magacin.pop();
    }
}
