import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class RewardHandler implements Runnable {
    
    private Map <Pos,List<Reward>> rewards;
    private ReadWriteLock lock;
    private Condition update;
    private Condition hasUpdate;
    private boolean isUpdated;
    private Grid grid;

    public RewardHandler(Grid grid) {
        this.rewards = new HashMap <Pos,List<Reward>>();
        this.lock = new ReentrantReadWriteLock();
        this.update = lock.writeLock().newCondition();
        this.hasUpdate = lock.writeLock().newCondition();
        this.grid = grid;
        this.generateRewards();
        this.isUpdated = true;
    }

    @Override
    public void run() {
        while (true) {
            lock.writeLock().lock();
            try {
                System.out.println("Waiting for update");
                update.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            this.generateRewards();
            this.isUpdated = true;
            this.hasUpdate.signalAll();
            System.out.println("Rewards updated");
            lock.writeLock().unlock();
        }
    }

    public void updateMap() {
        lock.writeLock().lock();
        this.isUpdated = false;
        update.signal();
        lock.writeLock().unlock();
    }

    public boolean isUpdated() {
        this.lock.readLock().lock();
        boolean up = isUpdated;
        this.lock.readLock().unlock();
        return up;
    }

    public List<Reward> getRewards(Pos start){

        int minx=start.getX()-ConfigGlobal.radius;
        if (minx < 0) minx = 0;
        int maxx=start.getX()+ConfigGlobal.radius;
        if (maxx >= ConfigGlobal.size) maxx = ConfigGlobal.size-1;
        int miny=start.getY()-ConfigGlobal.radius;
        if (miny < 0) miny = 0;
        int maxy=start.getY()+ConfigGlobal.radius;
        if (maxy >= ConfigGlobal.size) maxy = ConfigGlobal.size-1;
        
        List<Reward> ret = new ArrayList<Reward>();

    
        lock.readLock().lock();
        for (int i = miny; i <= maxy; i++){
            for (int j = minx; j <= maxx; j++){
                if (rewards.containsKey(new Pos(j, i)) && (Math.abs(i-start.getY()) + Math.abs(j-start.getX())) <= ConfigGlobal.radius){
                    ret.addAll(rewards.get(new Pos(j, i)));
                }
            }
        }
        lock.readLock().unlock();
        return ret;
    }

    public double confirmReward(Pos start, Pos end) {
        
        
        this.lock.readLock().lock();
        if (rewards.containsKey(start)) {
            for (Reward r : rewards.get(start)) {
                if (r.confirmReward(start, end)) {
                    rewards.get(start).remove(r);
                    this.lock.readLock().unlock();
                    this.updateMap();
                    return r.getDiscount();
                }
            }
        }
        this.lock.readLock().unlock();
        return 0.0;
    }

    public void generateRewards() {
        lock.writeLock().lock();
        rewards.clear();
        Pos start;
        for (int i = 0; i < ConfigGlobal.size; i++) {
            for (int j = 0; j < ConfigGlobal.size; j++) {
                start = new Pos(j, i);
                if (grid.getGrid()[i][j] > 1) {
                    for (int ii = 0; ii < ConfigGlobal.size; ii++) {
                        for (int jj = 0; jj < ConfigGlobal.size; jj++) {
                            if (grid.checkAvailability(new Pos(jj, ii)).isEmpty()) {
                                double d = calculateDiscount(jj,ii,j,i);
                                if (!rewards.containsKey(start))
                                    rewards.put(start, new ArrayList<Reward>());
                                rewards.get(start).add(new Reward(start, new Pos(jj, ii), d));
                            }
                        }
                    }
                }
            }
        }
        for (Pos p : rewards.keySet()) {
            for (Reward r : rewards.get(p)) {
                System.out.println(r);
            }
        }
        lock.writeLock().unlock();
    }

    public Double calculateDiscount(int xstart, int ystart, int xend, int yend){
        int dist=Math.abs(xstart-xend)+Math.abs(ystart-yend);
        return (dist*1.0/(ConfigGlobal.size*2.0));
    }

    public List<Reward> getListRewards(NotificationHandler nh){
        this.lock.writeLock().lock();
        try {
            this.hasUpdate.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        this.lock.writeLock().unlock();
        this.lock.readLock().lock();
        List<Reward> ret = new ArrayList<Reward>();
        System.out.println("Sending updated rewards");
        List<Pos> toCheck = nh.getDesiredPos();
        for (Pos p : toCheck) {
            if (rewards.containsKey(p)) {
                ret.addAll(rewards.get(p));
            }
        }
        this.lock.readLock().unlock();
        return ret;
    }
}
