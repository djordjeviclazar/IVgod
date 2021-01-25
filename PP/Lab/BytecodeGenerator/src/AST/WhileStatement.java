package AST;

import java.io.BufferedWriter;
import java.io.IOException;

public class WhileStatement
{
    private Block iterationStmt;
    private Statement defaultStmt;
    private Expression conditionExp;

    public WhileStatement(Expression e, Block iterationS, Statement defaultS)
    {
        conditionExp = e;
        iterationStmt = iterationS;
        defaultStmt = defaultS;
    }

    public void translate(BufferedWriter out) throws IOException
    {
        String conditionLabel = ASTNode.genLab();
        out.write(conditionLabel + ":");
        out.newLine();

        conditionExp.translate(out);
        out.newLine();
        String defaultLabel = ASTNode.genLab();
        out.write("\tJZ\tR1, " + defaultLabel);
        out.newLine();

        //iteration:
        iterationStmt.translate(out);
        out.write("\tJMP\t" + conditionLabel);
        out.newLine();

        //default:
        out.write(defaultLabel + ":");
        out.newLine();
        defaultStmt.translate(out);
        out.newLine();
    }
}
