import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.concurrent.locks.ReentrantLock;

public class Connection implements AutoCloseable {

    private Socket socket;
    private DataInputStream in;
    private DataOutputStream out;
    private ReentrantLock wlock;
    private ReentrantLock rlock;

    public Connection(Socket socket) throws IOException{
        this.socket = socket;
        this.in = new DataInputStream(socket.getInputStream());
        this.out = new DataOutputStream(socket.getOutputStream());
        this.wlock = new ReentrantLock();
        this.rlock = new ReentrantLock();
    }

    public void send(Frame f) throws IOException{
        wlock.lock();
        f.serialize(out);
        wlock.unlock();
    }

    public Frame receive() throws IOException, ClassNotFoundException{
        rlock.lock();
        Frame fr= Frame.deserialize(in);
        rlock.unlock();
        return fr;
    }

    public void close(){
        try {
            this.socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
