import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.util.concurrent.locks.ReentrantLock;

public class User{
    
    private String name;
    private String password;
    private int id;
    private boolean loggedIn;
    private ReentrantLock lock;
    
    public User(String name, String password) {
        this.name = name;
        this.password = password;
        this.loggedIn = false;
        this.lock = new ReentrantLock();
        this.id = 0;
    }

    public User(String name, String password, int id) {
        this.name = name;
        this.password = password;
        this.loggedIn = false;
        this.lock = new ReentrantLock();
        this.id = id;
    }
    
    public String getName() {
        this.lock.lock();
        String name = this.name;
        this.lock.unlock();
        return name;
    }

    public int getId() {
        this.lock.lock();
        int id = this.id;
        this.lock.unlock();
        return id;
    }

    public void setId(int id) {
        this.lock.lock();
        this.id = id;
        this.lock.unlock();
    }

    public boolean login(String password){
        this.lock.lock();
        if (!this.loggedIn && this.password.equals(password)) {
            this.loggedIn = true;
            this.lock.unlock();
            return true;
        }
        return false;
    }

    public String getPassword() {
        this.lock.lock();
        String password = this.password;
        this.lock.unlock();
        return password;
    }

    public boolean getLoggedIn() {
        this.lock.lock();
        boolean loggedIn = this.loggedIn;
        this.lock.unlock();
        return loggedIn;
    }

    public void setLoggedIn(boolean loggedIn) {
        this.lock.lock();
        this.loggedIn = loggedIn;
        this.lock.unlock();
    }

    public static void serialize(User u, DataOutputStream out) throws IOException {
        out.writeUTF(u.getName());
        out.writeUTF(u.getPassword());
        out.writeInt(u.getId());
    }

    public static User deserialize(DataInputStream in) throws IOException {
        String name = in.readUTF();
        String password = in.readUTF();
        int id = in.readInt();
        User u = new User(name, password, id);
        return u;
    }
}
