import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class UserDB {
    private Map <String,User> users;
    private int nextId;
    private ReadWriteLock lock;

    public UserDB() {
        this.users = new HashMap <String,User>();
        this.nextId = 0;
        this.lock = new ReentrantReadWriteLock();
    }

    public int addUser(User u) {
        String username = u.getName();
        lock.writeLock().lock();
        if (users.containsKey(username)) {
            lock.writeLock().unlock();
            return -1;
        }
        int id = nextId++;
        u.setId(id);
        u.setLoggedIn(true);
        users.put(u.getName(),u);
        lock.writeLock().unlock();
        return id;
    }

    public User getUser(String username) {
        lock.readLock().lock();
        try {
            return users.get(username);
        } finally {
            lock.readLock().unlock();
        }
    }

    public boolean login(String username, String pass) {
        lock.readLock().lock();
        if (!users.containsKey(username)) {
            lock.readLock().unlock();
            return false;
        }
        User u = users.get(username);
        lock.readLock().unlock();
        return u.login(pass);
    }

    public void logoff(String username) {
        lock.readLock().lock();
        if (!users.containsKey(username)) {
            lock.readLock().unlock();
            return;
        }
        User u = users.get(username);
        lock.readLock().unlock();
        u.setLoggedIn(false);
    }
}
