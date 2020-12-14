public class sym
{

    /*
     * Simboli koji se koriste u sintaksnom analizatoru
     * */
    public final static int WHILE = 0;
    public final static int ID = 1;
    public final static int CONST = 2;
    public final static int LESS = 3;
    public final static int ASSIGN = 4;
    public final static int SEMICOLON = 5;
    public final static int COLON = 6;
    public final static int LEFTCURVEDPAR = 7;
    public final static int RIGHTCURVEDPAR = 8;
    public final static int LEFTPAR = 9;
    public final static int RIGHTPAR = 10;
    public final static int EOF = 11;


    /*
     * Simboli koji su se koristili u prvom zadatku
     * */

    public final static int PLUS = 12;
    public final static int MUL = 13;
    public final static int EQUAL = 14;
    public final static int GREATER = 15;
    public final static int INTEGER = 16;
    public final static int DOUBLE = 17;
    public final static int STRING = 18;
    public final static int DEPLOYMENT = 19;
    public final static int DEPLOYMENTEND = 20;
    public final static int SERVER = 21;
    public final static int SERVEREND = 22;
    public final static int SERVERID = 23;
    public final static int TASKID = 24;
    public final static int EXACUTEDON = 25;
    public final static int MODEL = 26;
    public final static int MODELEND = 27;
    public final static int TASK = 28;
    public final static int TASKEND = 29;
    public final static int COMMA = 30;
    public final static int DOT = 31;

    public final static int ERROR = 32; // da bi se zalo koja da je greška u leksičkom analizatoru

}
