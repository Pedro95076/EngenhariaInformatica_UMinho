public class ServerMain {
    public static void main(String[] args) {
        Server server = new Server();
        System.out.println("Server started");
        server.acceptConnections();
    }
}
