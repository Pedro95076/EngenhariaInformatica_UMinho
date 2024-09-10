import java.util.List;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class ClientHandler implements Runnable{
    //receive the socket from server and start the thread
    private Connection con;
    private boolean running;
    private UserDB userDB;
    private Grid grid;
    private RewardHandler rewardHandler;
    private NotificationHandler notificationHandler;
    private String current;
    private ReadWriteLock lock;

    public ClientHandler(Connection con, UserDB userDB, Grid grid, RewardHandler rewardHandler) {
        try {
            this.con = con;
            this.userDB = userDB;
            this.grid = grid;
            this.rewardHandler = rewardHandler;
            this.notificationHandler = null;
            this.running = true;
            this.current = null;
            this.lock = new ReentrantReadWriteLock();
        } catch (Exception e) {
            System.out.println("Error in ClientHandler constructor: " + e.getMessage());
        }
    }

    public void setNotificationHandler(NotificationHandler notificationHandler) {
        this.notificationHandler = notificationHandler;
    }

    @Override
    public void run() {
        while(this.isRunning()){
            try {
                Frame msg = con.receive();
                if (msg.getFrameType() == -1) {
                    this.lock.writeLock().lock();
                    running = false;
                    this.lock.writeLock().unlock();
                    if (this.current != null) {
                        this.userDB.logoff(this.current);
                        System.out.println("User " + this.current + " disconnected");
                    }
                    System.out.println("Connection closed by client");
                    return;
                }else if(msg.getFrameType() >= 0 && msg.getFrameType() <= 7){
                    this.handleQuery(msg);
                }
            }catch (Exception e) {
                con.close();
                if (this.current != null) {
                    this.userDB.logoff(this.current);
                    System.out.println("User " + this.current + " disconnected");
                }
                this.lock.writeLock().lock();
                this.running = false;
                this.lock.writeLock().unlock();
                System.out.println("Connection closed by client error");
                break;
            }
        }
        this.con.close();
        System.out.println("Server closed");

    }

    public void handleQuery(Frame f){
        System.out.println("Received: " + f.getFrameType());
        try {
            switch (f.getFrameType()){
                case 0:
                    User u1=(User)f.getData();
                    int newID=userDB.addUser(u1);
                    if (newID!=-1){
                        System.out.println("New user: " + u1.getName()+ " " + u1.getId());
                        this.current=u1.getName();
                    }
                    this.con.send(new Frame(0,true,newID));
                    break;
                case 1:
                    User u=(User)f.getData();
                    boolean login=userDB.login(u.getName(),u.getPassword());
                    if (login){
                        System.out.println("User logged in: " + u.getName());
                        this.current=u.getName();
                    }
                    this.con.send(new Frame(1,true,login));
                    break;
                case 2:
                    Pos p=(Pos)f.getData();
                    System.out.println("User " + this.current + " checked availability at " + p.getX() + " " + p.getY());
                    this.con.send(new Frame(2,true,grid.checkAvailability(p)));
                    break;
                case 3:
                    Pos st=(Pos)f.getData();
                    System.out.println("User " + this.current + " wants to check rewards at " + st.getX() + " " + st.getY());
                    List<Reward> rewards = this.rewardHandler.getRewards(st);
                    for(Reward r: rewards){
                        System.out.println("User " + this.current + " found reward at " + r.getStart() + " " + r.getEnd());
                    }
                    this.con.send(new Frame(3,true,rewards));
                    break;
                case 4:
                    Pos p1=(Pos)f.getData();
                    System.out.println("User " + this.current + " wants to book at " + p1.getX() + " " + p1.getY());
                    Reserve r = grid.rentScotter(p1);
                    this.rewardHandler.updateMap();
                    this.con.send(new Frame(4,true,r));
                    if (r == null) {
                        System.out.println("User " + this.current + " failed to book at " + p1.getX() + " " + p1.getY());
                    }else{
                        System.out.println("User " + this.current + " booked at " + p1.getX() + " " + p1.getY());
                    }
                    break;
                case 5:
                    Reserve r1=(Reserve)f.getData();
                    Double discount = this.rewardHandler.confirmReward(r1.getStart(), r1.getEnd());
                    System.out.println("User " + this.current + " wants to end reservation at " + r1.getEnd().getX() + " " + r1.getEnd().getY());
                    Price price = grid.returnScooter(r1,discount);
                    this.rewardHandler.updateMap();
                    this.con.send(new Frame(5,true,price));
                    System.out.println("User " + this.current + " owes " + price.getPrice() + " with discount of " + price.getDiscount() + "% (Total "+ price.getFinalPrice() + ")");
                    break;
                case 6:
                    Pos p2=(Pos)f.getData();
                    System.out.println("User " + this.current + " wants to toggle notifications at " + p2.getX() + " " + p2.getY());
                    boolean stat=this.notificationHandler.toggleNotification(p2);
                    this.con.send(new Frame(6,true,stat));
                    break;
            }

        } catch (Exception e) {
            System.out.println("Error in handleQuery: " + e.getMessage());
        }
        System.out.println("Sent: " + f.getFrameType());
    }

    public boolean isRunning(){
        this.lock.readLock().lock();
        boolean runs=this.running;
        this.lock.readLock().unlock();
        return runs;
    }
}

