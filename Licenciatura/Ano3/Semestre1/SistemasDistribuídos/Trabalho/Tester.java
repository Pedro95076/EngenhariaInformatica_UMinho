import java.io.IOException;
import java.net.Socket;

public class Tester {

    public static void main(String[] args) throws InterruptedException, IOException {

        // Variable Declarations 

        final int     TN = 2*Runtime.getRuntime().availableProcessors();  // RECOMENDED: 2*#CPUs | Threads 
		final int 	  OP = 500;									      // RECOMENDED: 1000000 | Operations per Thread 
    	final boolean V  = true;                                          // RECOMENDED: True    | Verbose
		final long startTime = System.nanoTime();                         // Global Clock: runtime start to finish of program
        long startTimeF, timeF;                                           // Function Clock: runtime start to finish of function

		//------------------------------------------------------------

        UserAPI api;
        try {
            Socket socket = new Socket("localhost", ConfigGlobal.port);
            api = new UserAPI(socket);
            System.out.println("Conectado com o servidor");
        } catch (Exception e) {
            System.err.println("Erro ao conectar com o servidor");
            return;
        }
        
		//------------------------------------------------------------
		
		//Register Test User 
        if (api.register("TestUser", "test1ng.")==-1){
            //Test User Already Registered
            api.login("TestUser", "test1ng.");
        }
		
		//------------------------------------------------------------
		
		//Check For Scooters In Random Positions
    	startTimeF = System.nanoTime();
		make_operations(api, TN, OP, 0, V);
    	timeF = System.nanoTime();
		System.out.println("[CLOCK] "+TN*OP+" operações 'Procurar Disponiveis' finalizadas em " + (timeF - startTimeF) / 1000000 + " ms");

        //------------------------------------------------------------

		//Check For Rewards In Random Positions
    	startTimeF = System.nanoTime();
		make_operations(api, TN, OP, 1, V);
    	timeF = System.nanoTime();
		System.out.println("[CLOCK] "+TN*OP+" operações 'Procurar Recompensas' finalizadas em " + (timeF - startTimeF) / 1000000 + " ms");

        //------------------------------------------------------------
        
		//Reserve and Return Scooters In Random Positions
    	startTimeF = System.nanoTime();
		make_operations(api, TN, OP, 2, V);
    	timeF = System.nanoTime();
		System.out.println("[CLOCK] "+TN*OP+" operações 'Reservar Trotinete' (realizando a operação 'Entregar Trotinete' quando tem sucesso na reserva) finalizadas em " + (timeF - startTimeF) / 1000000 + " ms");

        //------------------------------------------------------------

		//Test Random Operations
    	startTimeF = System.nanoTime();
		make_operations(api, TN, OP, -1, V);
    	timeF = System.nanoTime();
		System.out.println("[CLOCK] "+TN*OP+" operações aleatórias finalizadas em " + (timeF - startTimeF) / 1000000 + " ms");

        //------------------------------------------------------------

        //Exit
        api.close();

		//Print Results 
		System.out.println("[CLOCK] Testes finalizados em " + (System.nanoTime() - startTime) / 1000000 + " ms");
    }

    // Multi threaded operations on random accounts
	public static void make_operations(UserAPI u, int TN ,int OP, int mode, boolean V) throws InterruptedException{
        Thread[] tm = new Thread[TN];
       for (int j = 0; j < TN; j++) {
           tm[j] = new Thread(new TestWorker(u, OP, mode, V));
       }
       for (int j = 0; j < TN; j++) {
           tm[j].start();
       }
       for (int j = 0; j < TN; j++) {
           tm[j].join();
       }
   }
    
}
