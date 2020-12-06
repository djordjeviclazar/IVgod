import java.util.Hashtable;

public class KWTable {

    private Hashtable mTable;

    public KWTable() {
        // Inicijalizcaija hash tabele koja pamti kljucne reci
        mTable = new Hashtable();
        mTable.put("double", new Integer(sym.DOUBLE));
        mTable.put("string", new Integer(sym.STRING));
        mTable.put("int", new Integer(sym.INTEGER));
        mTable.put("while", new Integer(sym.WHILE));
        mTable.put("deployment", new Integer(sym.DEPLOYMENT));
        mTable.put("server", new Integer(sym.SERVER));
        mTable.put("task", new Integer(sym.TASK));
        mTable.put("serverId", new Integer(sym.SERVERID));
        mTable.put("task", new Integer(sym.TASKID));
        mTable.put("executedOn", new Integer(sym.EXACUTEDON));
        mTable.put("model", new Integer(sym.MODEL));
        mTable.put("comm", new Integer(sym.COMMENT));
    }

    /**
     * Vraca ID kljucne reci
     */
    public int find(String keyword) {
        Object symbol = mTable.get(keyword);
        if (symbol != null)
            return ((Integer) symbol).intValue();

        // Ako rec nije pronadjena u tabeli kljucnih reci radi se o identifikatoru
        return sym.ID;
    }


}
