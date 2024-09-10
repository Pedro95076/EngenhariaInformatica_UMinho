import java.net.Socket;
import java.util.List;

public class ClientMain {
    public static void main(String[] args) {
        UserAPI api;
        try{
            Socket socket = new Socket("localhost", ConfigGlobal.port);
            api = new UserAPI(socket);
            System.out.println("Conectado com o servidor");
        }catch(Exception e){
            System.err.println("Erro ao conectar com o servidor");
            return;
        }
        Menu menu = new Menu(api);
        boolean auth = menu.menuInicial();
        if(auth){
            new Thread(){
                @Override
                public void run() {
                    while(true){
                        try{
                            List<Reward> rlist = api.receive_notifications();
                            if(rlist != null){
                                System.out.println("\n\nNova notificação!\n"
                                                    +"Lista de recompensas disponiveis para as localizações assinaladas:");
                                for(Reward r : rlist){
                                    System.out.println(r);
                                }
                                System.out.println("\nFim de notificação!\n");
                            }
                        }catch(Exception e){
                            System.err.println("Erro ao receber mensagem");
                        }
                    }
                }
            }.start();
            menu.menu();
        }
    }
}
