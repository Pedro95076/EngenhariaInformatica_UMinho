import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.io.IOException;

public class Reserve{
    
    private int code;
    private Pos start;
    private Pos end;
    private String datetimeStart;
    private String datetimeEnd;

    public Reserve(int code, Pos start) {
        this.code = code;
        this.start = start;
        this.datetimeStart = ConfigGlobal.getDateTime();
        this.end = null;
        this.datetimeEnd = null;
    }

    public Reserve(int code, Pos start, String datetimeStart) {
        this.code = code;
        this.start = start;
        this.datetimeStart = datetimeStart;
        this.end = null;
        this.datetimeEnd = null;
    }
    
    public Reserve(int code, Pos start, String datetimeStart, Pos end, String datetimeEnd) {
        this.code = code;
        this.start = start;
        this.datetimeStart = datetimeStart;
        this.end = end;
        this.datetimeEnd = datetimeEnd;
    }

    public void setEnd(Pos end){
        this.end = end;
        this.datetimeEnd = ConfigGlobal.getDateTime();
    }

    public void setEnd(Pos end, String datetimeEnd){
        this.end = end;
        this.datetimeEnd = datetimeEnd;
    }

    public int getCode() {
        return code;
    }

    public Pos getStart() {
        return start;
    }

    public Pos getEnd() {
        return end;
    }

    public String getTimeStart() {
        return datetimeStart;
    }

    public String getTimeEnd() {
        return datetimeEnd;
    }

    public int getDuration(){
        return ConfigGlobal.calculateDifference(datetimeStart, datetimeEnd);
    }

    public boolean isFinished(){
        return end != null;
    }

    public int getDistance(){
        return Math.abs(start.getX() - end.getX()) + Math.abs(start.getY() - end.getY());
    }

    public String toString() {
        String s = "Reserve: \n";
        s += "   Code: " + code + "\n";
        s += "   Start: " + start + "\n";
        s += "   End: " + end + "\n";
        s += "   Initial time: " + datetimeStart + "\n";
        s += "   End time: " + datetimeEnd + "\n";
        return s;
    }

    public static void serialize(Reserve r, DataOutputStream out) throws IOException {
        out.writeInt(r.getCode());
        Pos p1 = r.getStart();
        out.writeInt(p1.getX());
        out.writeInt(p1.getY());
        Pos p2 = r.getEnd();
        if (p2 == null){
            out.writeInt(-1);
            out.writeInt(-1);
        } else {
            out.writeInt(p2.getX());
            out.writeInt(p2.getY());
        }
        out.writeUTF(r.getTimeStart());
        if(r.getTimeEnd() != null)
            out.writeUTF(r.getTimeEnd());
        else
            out.writeUTF("");
    } 


	public static Reserve deserialize(DataInputStream in) throws IOException {
        int code = in.readInt();
        int x1 = in.readInt();
        int y1 = in.readInt();
        int x2 = in.readInt();
        int y2 = in.readInt();
        String datetimeStart = in.readUTF();
        String datetimeEnd = in.readUTF();
        Reserve r = new Reserve(code, new Pos(x1, y1), datetimeStart);
        if (x2 != -1 && y2 != -1){
            r.setEnd(new Pos(x2, y2), datetimeEnd);
        }
        return r;
    }
}
