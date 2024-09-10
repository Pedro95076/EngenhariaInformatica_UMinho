import java.util.List;
import java.util.Random;

class TestWorker implements Runnable {
    UserAPI api; // Demultiplexer
    int am;      // Amount of operations
    int mode;    // -1 for random operations
    boolean v;   // Verbose
    int size=ConfigGlobal.size;

    // Constructor with Verbose option
    public TestWorker(UserAPI api, int am, int mode, boolean v) {
        this.api = api;
        this.am = am;
        this.mode = mode;
        this.v = v;
    }

    // Default Constructor
    public TestWorker(UserAPI api, int am, int mode) {
        this.api = api;
        this.am = am;
        this.mode = mode;
        this.v = false;
    }

    public void run() {
        int op=mode;
        Random rand = new Random();

        // Make 'am' number of random operations in random accounts
        for (int m = 0; m < am; m++) {
            if (mode==-1)
                op = rand.nextInt(3); // Random Operation

            // Operation Switch
            switch (op) {

                case 0:
                    Pos toCheck = new Pos(rand.nextInt(size), rand.nextInt(size));
                    if(v)System.out.println("[" + Thread.currentThread().getName().toUpperCase() + "] "+
                                       "Procurar trotinete perto de "+toCheck.toString()+"!");
                    List<Pos> l=api.get_available(toCheck);
                    if (v){
                        if(l.isEmpty()){
                            System.out.println("[" + Thread.currentThread().getName().toUpperCase() + "] "+
                                               "Nenuma trotinete encontrada para "+toCheck.toString()+"!" );
                        }else{
                            String plist = "";
                            for (Pos p : l) {
                                plist += p.toString() + " | ";
                            }
                            plist=plist.substring(0, plist.length()-3);
                            System.out.println("[" + Thread.currentThread().getName().toUpperCase() + "] "+
                                               "Trotinete encontradas para "+toCheck.toString()+" em "+plist+"!" );
                        }
                    }
                    break;

                // Balance
                case 1:
                    Pos toCheck2 = new Pos(rand.nextInt(size), rand.nextInt(size));
                    if(v)System.out.println("[" + Thread.currentThread().getName().toUpperCase() + "] "+
                                       "Procurar recompensa perto de "+toCheck2.toString()+"!");
                    List<Reward> l2=api.check_rewards(toCheck2);
                    if (v){
                        if(l2.isEmpty()){
                            System.out.println("[" + Thread.currentThread().getName().toUpperCase() + "] "+
                                               "Nenuma recompensa encontrada para "+toCheck2.toString()+"!" );
                        }else{
                            String plist = "";
                            for (Reward r : l2) {
                                plist += r.toString() + " | ";
                            }
                            plist=plist.substring(0, plist.length()-3);
                            System.out.println("[" + Thread.currentThread().getName().toUpperCase() + "] "+
                                               "Recompensas encontradas para "+toCheck2.toString()+" em "+plist+"!" );
                        }
                    }
                    break;
                case 2:
                    Pos toCheck3 = new Pos(rand.nextInt(size), rand.nextInt(size));
                    if(v)System.out.println("[" + Thread.currentThread().getName().toUpperCase() + "] "+
                                       "Tentar reservar perto de "+toCheck3.toString()+"!");
                    Reserve rev = api.reserve_scooter(toCheck3);
                    boolean rd = rev.getCode()==-1;
                    if(v){
                        if(rd){
                            System.out.println("[" + Thread.currentThread().getName().toUpperCase() + "] "+
                                               "Nenuma trotinete disponivel perto de "+toCheck3.toString()+"!" );
                        }else{
                            System.out.println("[" + Thread.currentThread().getName().toUpperCase() + "] "+
                                               "Trotinete reservada com sucesso em "+rev.getStart()+"!" );
                        }
                    }
                    if(!rd){
                        Pos toEnd = new Pos(rand.nextInt(size), rand.nextInt(size));
                        if(v)System.out.println("[" + Thread.currentThread().getName().toUpperCase() + "] "+
                                           "Terminar reserva em "+toEnd.toString()+"!");
                        rev.setEnd(toEnd);
                        Price pr = api.park_scooter(rev);
                        if(v){
                            System.out.println("[" + Thread.currentThread().getName().toUpperCase() + "] "+
                                               "Reserva terminada com "+pr.toString()+"!" );
                        }
                    }
                    break;
            }
        }
    }
}
