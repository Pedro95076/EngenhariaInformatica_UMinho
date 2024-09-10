import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Pos {
    
    private int x;
    private int y;

    public Pos(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof Pos) {
            Pos p = (Pos) o;
            return this.x == p.x && this.y == p.y;
        }
        return false;
    }

    public static void serialize(Pos p,DataOutputStream out) throws IOException {
        out.writeInt(p.getX());
        out.writeInt(p.getY());
    }

    public static Pos deserialize(DataInputStream in) throws IOException {
        int x = in.readInt();
        int y = in.readInt();
        return new Pos(x, y);
    }

    public String toString() {
        return "Pos " + "(" + x + "," + y + ")";
    }

    public static List<Pos> getRange(Pos start) {

        int minx = start.getX() - ConfigGlobal.radius;
        if (minx < 0) minx = 0;
        int maxx = start.getX() + ConfigGlobal.radius;
        if (maxx >= ConfigGlobal.size) maxx = ConfigGlobal.size - 1;
        int miny = start.getY() - ConfigGlobal.radius;
        if (miny < 0) miny = 0;
        int maxy = start.getY() + ConfigGlobal.radius;
        if (maxy >= ConfigGlobal.size) maxy = ConfigGlobal.size - 1;
        List<Pos> posList = new ArrayList<Pos>();

        for (int i = miny; i <= maxy; i++) {
            for (int j = minx; j <= maxx; j++) {
                if (Math.abs(i - start.getY()) + Math.abs(j - start.getX()) <= ConfigGlobal.radius) {
                    posList.add(new Pos(j, i));
                }
            }
        }
        return posList;
    }

    @Override
    public int hashCode() {
        return (int) x*1000 + y;
    }
}