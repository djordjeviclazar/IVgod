import java.io.FileReader;
import java.io.IOException;
import java.util.Stack;

public class LR1SyntaxAnalyzer
{
    class Neterminali
    {
        public final static int Statements = 12;
        public final static int Statement = 13;
        public final static int WhileStatement = 14;
        public final static int RelExpression = 15;
        public final static int Term = 16;
        public final static int Assignment = 17;
    }

    /*
     * Akcije:
     * Shift = 0 - 22
     * Greška = -1
     * Reduce = 23 - 32
     * Acc = 0
     * */
    private static final int[][] sintaksnaTabela =
            {
                    {6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 2, 4, -1, -1, 3}, //0
                    {-1, -1, -1, -1, -1, 7, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1}, //1
                    {-1, -1, -1, -1, -1, 24, -1, -1, 24, -1, -1, 24, -1, -1, -1, -1, -1, -1},//2
                    {-1, -1, -1, -1, -1, 25, -1, -1, 25, -1, -1, 25, -1, -1, -1, -1, -1, -1},//3
                    {-1, -1, -1, -1, -1, 26, -1, -1, 26, -1, -1, 26, -1, -1, -1, -1, -1, -1},//4
                    {-1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},//5
                    {-1, -1, -1, -1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},//6
                    {6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, 4, -1, -1, 3},//7
                    {-1, 12, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, -1},//8
                    {-1, 12, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14, -1, -1},//9
                    {-1, -1, -1, -1, -1, 23, -1, -1, 23, -1, -1, 23, -1, -1, -1, -1, -1, -1},//10
                    {-1, -1, -1, -1, -1, 32, -1, -1, 32, -1, -1, 32, -1, -1, -1, -1, -1, -1},//11
                    {-1, -1, -1, 30, -1, 30, -1, -1, 30, -1, 30, 30, -1, -1, -1, -1, -1, -1},//12
                    {-1, -1, -1, 31, -1, 31, -1, -1, 31, -1, 31, 31, -1, -1, -1, -1, -1, -1},//13
                    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16, -1, -1, -1, -1, -1, -1, -1},//14
                    {-1, -1, -1, 17, -1, 29, -1, -1, 29, -1, 29, 29, -1, -1, -1, -1, -1, -1},//15
                    {-1, -1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},//16
                    {-1, 12, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1},//17
                    {-1, -1, -1, -1, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},//18
                    {-1, -1, -1, -1, -1, 28, -1, -1, 28, -1, 28, 28, -1, -1, -1, -1, -1, -1},//19
                    {6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, 4, -1, -1, 3},//20
                    {-1, -1, -1, -1, -1, -1, -1, -1, 22, -1, -1, -1, -1, -1, -1, -1, -1, -1},//21
                    {-1, -1, -1, -1, -1, 27, -1, -1, 27, -1, -1, 27, -1, -1, -1, -1, -1, -1},//22
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
        magacin.push(0);
        boolean acc = false, error = false;

        /*Yytoken token = getNextToken(lexer);
        if (token == null)
        {
            return;
        }*/
        boolean firstIteration = true;
        Yytoken token = getNextToken(lexer);
        int akcija = 0; // kod akcije iz sintaksne tabele koja treba da se izvrši
        // -1 ako treba da se uzme vrednost iz sintaksne tabele


        // sintaksna analiza:
        do
        {
            akcija = sintaksnaTabela[magacin.peek()][token.m_index];// deo za akcije
            switch (akcija)
            {
                case -1:
                    errorPrint(magacin, token);
                    error = true;
                    break;
                case 0:
                    /*pop(magacin);

                    token = getNextToken(lexer);
                    if (token == null)
                    {
                        return;
                    }*/
                    accept(magacin);
                    acc = true;
                    break;

                default:
                    if (akcija >= 0 && akcija < 23)
                    {
                        // shift akcija:
                        magacin.push(token.m_index);
                        magacin.push(akcija);


                    } else
                    {
                        if (akcija <= 32)
                        {
                            reduce(magacin, akcija, token);
                        }
                    }

                    token = getNextToken(lexer);

                    break;
            }

            firstIteration = false;
        } while (!(acc || error));
    }

    private static Yytoken getNextToken(MPLexer lexer) throws IOException
    {
        Yytoken token = lexer.next_token();

        if (token.m_index == sym.ERROR)
        {
            System.out.println("ERROR on line: " + token.m_line);
            System.out.println("This sequence doesn't match any token: " + token.m_text);

            return null; // ne nastavljamo nakon greške
        }

        return token;
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

    private static void reduce(Stack<Integer> magacin, int akcija, Yytoken token)
    {
        int smena = akcija - 23;
        int length = rightLength(smena);// dužina desne strane
        for (int i = 0; i < 2 * length; i++)
        {
            magacin.pop();
        }

        int neterminalSmene = getNeterminal(smena);
        int prelaz = sintaksnaTabela[magacin.peek()][neterminalSmene];// gledamo deo za prelaze (GOTO)

        magacin.push(neterminalSmene);// ubacujemo levu stranu na stek
        magacin.push(prelaz);
    }

    private static int getNeterminal(int smena)
    {
        int res = 0;
        switch (smena)
        {
            case 1:
                res = Neterminali.Statements;
                break;
            case 2:
                res = Neterminali.Statements;
                break;
            case 3:
                res = Neterminali.Statement;
                break;
            case 4:
                res = Neterminali.Statement;
                break;
            case 5:
                res = Neterminali.WhileStatement;
                break;
            case 6:
                res = Neterminali.RelExpression;
                break;
            case 7:
                res = Neterminali.RelExpression;
                break;
            case 8:
                res = Neterminali.Term;
                break;
            case 9:
                res = Neterminali.Term;
                break;
            case 10:
                res = Neterminali.Assignment;
                break;

            default:
                break;
        }

        return res;
    }

    private static int rightLength(int smena)
    {
        int res = 0;
        switch (smena)
        {
            case 1:
                res = 3;
                break;
            case 2:
                res = 2;
                break;
            case 3:
                res = 1;
                break;
            case 4:
                res = 1;
                break;
            case 5:
                res = 8;
                break;
            case 6:
                res = 3;
                break;
            case 7:
                res = 1;
                break;
            case 8:
                res = 1;
                break;
            case 9:
                res = 1;
                break;
            case 10:
                res = 3;
                break;

            default:
                break;
        }

        return res;
    }
}
