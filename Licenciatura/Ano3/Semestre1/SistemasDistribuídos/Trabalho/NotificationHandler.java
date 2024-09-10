import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class NotificationHandler implements Runnable {
    private List<Pos> pos;
    private ReadWriteLock lock;
    private Connection con;
    private RewardHandler rewardHandler;
    private ClientHandler clientHandler;

    public NotificationHandler(Connection c, RewardHandler rh, ClientHandler ch) {
        this.pos = new ArrayList<>();
        this.lock = new ReentrantReadWriteLock();
        this.con = c;
        this.rewardHandler = rh;
        this.clientHandler = ch;
    }

    @Override
    public void run() {
        while (this.clientHandler.isRunning()) {
            try {
                List<Reward>ret=this.rewardHandler.getListRewards(this);
                if (!ret.isEmpty()) {
                    System.out.println("Sending rewards to client");
                    Frame f = new Frame(7,true, ret);
                    this.con.send(f);
                }
            } catch (Exception e) {
                System.out.println("Error in NotificationHandler: " + e.getMessage());
            }
        }
    }

    public boolean toggleNotification(Pos p) {
        boolean onoff = false;
        this.lock.writeLock().lock();
        if (this.pos.contains(p)) {
            this.pos.remove(p);
        } else {
            this.pos.add(p);
            onoff = true;
        }
        this.lock.writeLock().unlock();
        return onoff;
    }

    public List<Pos> getDesiredPos() {
        List<Pos> ret = new ArrayList<>();
        this.lock.readLock().lock();
        for(Pos p : this.pos){
            for (Pos q : Pos.getRange(p)){
                ret.add(q);
            }
        }
        this.lock.readLock().unlock();
        return ret;
    }

    public void removePos(Pos p) {
        this.lock.writeLock().lock();
        this.pos.remove(p);
        this.lock.writeLock().unlock();
    }

}
