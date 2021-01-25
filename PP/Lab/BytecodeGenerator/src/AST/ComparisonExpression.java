package AST;

import java.io.BufferedWriter;
import java.io.IOException;

public abstract class ComparisonExpression extends Expression
{
    private Expression left;
    private Expression right;
    private int op;
    private static final String[] opCode = {"JL", "JE", "JG"};

    public ComparisonExpression(Expression l, Expression r, int op)
    {
        left = l;
        right = r;
        this.op = op;
    }

    public void translate(BufferedWriter out)
            throws IOException
    {
        //comparison:
        left.translate(out);
        right.translate(out);
        left.genLoad("R1", out);
        right.genLoad("R2", out);
        out.write("\t" + opCode[op] + "\t\tR1, R2");
        out.newLine();

        //result:
        String endLabel = ASTNode.genLab();
        String trueLabel = ASTNode.genLab();
        //false
        out.write("\tMOV\t\tR1, " + 0);
        out.write("\tJMP\t" + endLabel);
        //true
        out.write(trueLabel + ":");
        out.newLine();
        out.write("\tMOV\t\tR1, " + 1);
        out.write(endLabel + ":");

        out.newLine();
    }
}
