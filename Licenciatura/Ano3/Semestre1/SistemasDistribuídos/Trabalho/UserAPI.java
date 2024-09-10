import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

/* API CALL GUIDE:
 * -1 -> close() -> void
 *  0 -> register(User user) -> int
 *  1 -> login(User) -> Boolean
 *  2 -> get_available(Pos current) -> List<Pos>
 *  3 -> check_rewards(Pos current) -> List<Reward>
 *  4 -> reserve_scooter(Pos start) -> Reserve
 *  5 -> park_scooter(Reserve) -> Price
 *  6 -> set_notifications(Pos desired) -> Boolean
 *  7 -> receive_notifications() -> Reward
 */

public class UserAPI {

    private Connection con;
    private Demultiplexer demultiplexer;

    public UserAPI(Socket s) throws IOException{
        this.con = new Connection(s);
        this.demultiplexer=new Demultiplexer(this.con);
        new Thread(this.demultiplexer).start();
        System.out.println("Connection established");
    }

    public int register(String username, String password) {
        
        // Create a frame with frameType 0 and send it trough the demultiplexer
        User user = new User(username, password);
        Frame request = new Frame(0, false,user);
        if (1==demultiplexer.send(request)){
            return -1;
        }
        
        try {
            // Receive a frame from the demultiplexer
            Frame response = demultiplexer.receive(0);
            // Parse the response value
            return (Integer)response.getData();
        } catch (Exception e) {
            return -1;
        }
    }

    public Boolean login(String username, String password) {
        
        // Create a frame with frameType 1 and send it trough the demultiplexer
        User user = new User(username, password);
        Frame request = new Frame(1, false, user);
        if (1==demultiplexer.send(request)){
            return false;
        }

        try {
            // Receive a frame from the demultiplexer
            Frame response = demultiplexer.receive(1);

            // Parse the response value
            return (Boolean)response.getData();
        } catch (Exception e) {
            return false;
        }
    }

    public List<Pos> get_available(Pos current){
        
        // Create a frame with frameType 2 and send it trough the demultiplexer
        Frame request = new Frame(2, false, current);
        if (1==demultiplexer.send(request)){
            return null;
        }

        // Receive a frame from the demultiplexer
        try {
            Frame response = demultiplexer.receive(2);
            // Return list of available positions
            List<?> avail =(List<?>)response.getData();
            List<Pos> list = new ArrayList<Pos>();
            for (Object o : avail) {
                list.add((Pos)o);
            }
            return list;
        } catch (Exception e) {
            return null;
        }

    }

    public List<Reward> check_rewards(Pos current){
        // Create a frame with frameType 3 and send it trough the demultiplexer
        Frame request = new Frame(3, false, current);
        if (1 == demultiplexer.send(request)) {
            return null;
        }

        // Receive a frame from the demultiplexer
        try {
            Frame response = demultiplexer.receive(3);
            // Return list of available positions
            List<?> avail = (List<?>) response.getData();
            List<Reward> list = new ArrayList<Reward>();
            for (Object o : avail) {
                list.add((Reward) o);
            }
            return list;
        } catch (Exception e) {
            return null;
        }
    }

    public Reserve reserve_scooter(Pos start){
        
        // Create a frame with frameType 4 and send it trough the demultiplexer
        Frame request = new Frame(4, false, start);
        if (1==demultiplexer.send(request)){
            return null;
        }

        // Receive a frame from the demultiplexer
        try {
            Frame response = demultiplexer.receive(4);
            return (Reserve)response.getData();
        } catch (Exception e) {
            return null;
        }
    }

    public Price park_scooter(Reserve res){
        
        // Create a frame with frameType 5 and send it trough the demultiplexer
        Frame request = new Frame(5, false, res);
        if (1 == demultiplexer.send(request)) {
            return null;
        }

        // Receive a frame from the demultiplexer
        try {
            Frame response = demultiplexer.receive(5);
            return (Price)response.getData();
        } catch (Exception e) {
            return null;
        }
    }

    public boolean set_notifications(Pos desired){
            
        // Create a frame with frameType 6 and send it trough the demultiplexer
        Frame request = new Frame(6, false, desired);
        if (1==demultiplexer.send(request)){
            return false;
        }

        // Receive a frame from the demultiplexer
        try {
            Frame response = demultiplexer.receive(6);
            return (Boolean)response.getData();
        } catch (Exception e) {
            return false;
        }
    }

    public List<Reward> receive_notifications(){
            
        try {
            Frame response= demultiplexer.receive(7);
            // Return list of available positions
            List<?> avail = (List<?>) response.getData();
            List<Reward> list = new ArrayList<Reward>();
            for (Object o : avail) {
                list.add((Reward) o);
            }
            return list;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return null;
    }

    public void close() throws IOException{
        demultiplexer.send(new Frame(-1, false, null));
        demultiplexer.close();
    }

    public boolean isRunning() {
        return demultiplexer.isRunning();
    }
}