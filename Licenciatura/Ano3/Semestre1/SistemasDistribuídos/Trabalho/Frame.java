import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;

public class Frame{
    private int frameType;
    private boolean response;
    private Object data;

    public Frame(int frameType, boolean response, Object data) {
        this.frameType = frameType;
        this.response = response;
        this.data = data;
    }

    public int getFrameType() {
        return frameType;
    }

    public Object getData() {
        return data;
    }

    public void serialize(DataOutputStream out) throws IOException {
        out.writeInt(frameType);
        out.writeBoolean(response);
        switch (frameType) {
            case 0:
                if (response) {
                    out.writeInt((int) data);
                } else {
                    User.serialize((User)data, out);
                }
                break;
            case 1:
                if (response) {
                    out.writeBoolean((boolean) data);
                } else {
                    User.serialize((User) data, out);
                }
                break;
            case 2:
                if (response) {
                    List<?> list = (List<?>) data;
                    out.writeInt(list.size());
                    for (Object o : list) {
                        Pos.serialize((Pos)o, out);
                    }
                } else {
                    Pos.serialize((Pos) data, out);
                }
                break;
            case 3:
                if (response) {
                    List<?> list = (List<?>) data;
                    out.writeInt(list.size());
                    for (Object o : list) {
                        Reward.serialize((Reward)o, out);
                    }
                } else {
                    Pos.serialize((Pos) data, out);
                }
                break;
            case 4:
                if (response) {
                    Reserve.serialize((Reserve) data, out);
                } else {
                    Pos.serialize((Pos) data, out);
                }
                break;
            case 5:
                if (response) {
                    Price.serialize((Price) data, out);
                } else {
                    Reserve.serialize((Reserve) data, out);
                }
                break;
            case 6:
                if (response) {
                    out.writeBoolean((boolean) data);
                } else {
                    Pos.serialize((Pos) data, out);
                }
                break;
            case 7:
                if (response) {
                    List<?> list = (List<?>) data;
                    out.writeInt(list.size());
                    for (Object o : list) {
                        Reward.serialize((Reward) o, out);
                    }
                }
                break;
        }
    }

    public static Frame deserialize(DataInputStream in) throws IOException{
        int frameType = in.readInt();
        boolean response = in.readBoolean();
        Object data = null;
        switch (frameType) {
            case 0:
                if (response) {
                    data = in.readInt();
                } else {
                    data = User.deserialize(in);
                }
                break;
            case 1:
                if (response) {
                    data = in.readBoolean();
                } else {
                    data = User.deserialize(in);
                }
                break;
            case 2:
                if (response) {
                    int size = in.readInt();
                    List<Pos> l = new ArrayList<Pos>();
                    for (int i = 0; i < size; i++) {
                        l.add(Pos.deserialize(in));
                    }
                    data=l;
                } else {
                    data = Pos.deserialize(in);
                }
                break;
            case 3:
                if (response) {
                    int size = in.readInt();
                    List<Reward> l = new ArrayList<Reward>();
                    for (int i = 0; i < size; i++) {
                        l.add(Reward.deserialize(in));
                    }
                    data=l;
                } else {
                    data = Pos.deserialize(in);
                }
                break;
            case 4:
                if (response) {
                    data = Reserve.deserialize(in);
                } else {
                    data = Pos.deserialize(in);
                }
                break;
            case 5:
                if (response) {
                    data = Price.deserialize(in);
                } else {
                    data = Reserve.deserialize(in);
                }
                break;
            case 6:
                if (response) {
                    data = in.readBoolean();
                } else {
                    data = Pos.deserialize(in);
                }
                break;
            case 7:
                if (response) {
                    int size = in.readInt();
                    List<Reward> l = new ArrayList<Reward>();
                    for (int i = 0; i < size; i++) {
                        l.add(Reward.deserialize(in));
                    }
                    data = l;
                }
                break;
        }
        return new Frame(frameType, response, data);
    }
}