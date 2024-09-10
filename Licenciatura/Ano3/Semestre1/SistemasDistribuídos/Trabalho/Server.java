import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    
    private UserDB userDB;
    private ServerSocket serverSocket;
    private Grid grid;
    private RewardHandler rewardHandler;
    private boolean running;

    public Server() {
        try {
            this.serverSocket = new ServerSocket(ConfigGlobal.port);
            this.running = true;
            this.userDB = new UserDB();
            this.grid = new Grid(ConfigGlobal.amount);
            this.rewardHandler = new RewardHandler(grid);
            new Thread(rewardHandler).start();
            System.out.println(this.grid);
        } catch (Exception e) {
            System.err.println("Could not listen on port: "+ConfigGlobal.port);
            System.exit(1);
        }
    }

    public void acceptConnections() {
        while (running) {
            try {
                Socket clientSocket = serverSocket.accept();
                Connection con = new Connection(clientSocket);
                System.out.println("Connection from client accepted");
                ClientHandler client= new ClientHandler(con, userDB, grid, rewardHandler);
                NotificationHandler notificationHandler = new NotificationHandler(con, rewardHandler,client);
                client.setNotificationHandler(notificationHandler);
                new Thread(client).start();
                new Thread(notificationHandler).start();
            } catch (Exception e) {
                e.printStackTrace();
                running = false;
            }
        }
        try {
            this.serverSocket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
