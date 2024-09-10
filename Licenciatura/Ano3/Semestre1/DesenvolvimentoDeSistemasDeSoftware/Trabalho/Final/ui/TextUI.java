package ui;

import buisness.*;
import java.util.*;
import java.util.stream.Collectors;
import buisness.Racing.*;



/**
 * Exemplo de interface em modo texto.
 *
 * @author JFC
 * @version 20220919
 */
public class TextUI {
    // O model tem a 'lógica de negócio'.
    private RacingSimFacade model;

    // Menus da aplicação
    private Menu menuAdim;
    // Menus da aplicação
    private Menu menuUtilizador;
    // Menus da aplicação
    private Menu menuLogin;

    // Scanner para leitura
    private Scanner scin;

    /**
     * Construtor.
     *
     * Cria os menus e a camada de negócio.
     */
    public TextUI() {
        // Criar o menu
        this.menuAdim = new Menu(new String[]{
                "Adicionar Campeonato",
                "Adicionar Circuito",
                "Adicionar Carro",
                "Adicionar Piloto",
                "Editar Campeonato",
                "Editar Circuito",
                "Editar Carro",
                "Editar Piloto",
                "Remover Campeonato",
                "Remover Circuito",
                "Remover Carro",
                "Remover Piloto",
        });
        this.menuAdim.setHandler(1, this::adicionarCampeonato);
        this.menuAdim.setHandler(2, this::adicionarCircuito);
        this.menuAdim.setHandler(3, this::adicionarCarro);
        this.menuAdim.setHandler(4, this::adicionarPiloto);
        this.menuAdim.setHandler(5, this::editarCampeonato);
        this.menuAdim.setHandler(6, this::editarCircuito);
        this.menuAdim.setHandler(7, this::editarCarro);
        this.menuAdim.setHandler(8, this::editarPiloto);
        this.menuAdim.setHandler(9, this::removerCampeonato);
        this.menuAdim.setHandler(10, this::removerCircuito);
        this.menuAdim.setHandler(11, this::removerCarro);
        this.menuAdim.setHandler(12, this::removerPiloto);
        this.menuUtilizador = new Menu(new String[]{
            "Criar Lobby",
            "Juntar Campeonato",
            "Mostrar Pontos",
        });
        this.menuUtilizador.setHandler(1, this::criarLobby);
        this.menuUtilizador.setHandler(2, this::juntarCampeonato);
        this.menuUtilizador.setHandler(3, this::mostrarPontos);
        this.menuLogin = new Menu(new String[]{
            "Convidado",
            "Login",
            "Registar",
        });
        this.menuLogin.setHandler(1, this::convidado);
        this.menuLogin.setHandler(2, this::login);
        this.menuLogin.setHandler(3, this::registo);
        this.model = new RacingSimFacade();
        scin = new Scanner(System.in);
    }

    /**
     * Executa o menu principal e invoca o método correspondente à opção seleccionada.
     */
    public void run() {
        this.menuLogin.run();
        System.out.println("Até breve!...");
    }

    // Métodos auxiliares
    private void adicionarCampeonato() {
        try {
            System.out.println("Nome do Campeonato: ");
            String nomeCampeonato = scin.nextLine();
            if (!this.model.existeCampeonato(nomeCampeonato)) {
                ArrayList<String> listaCircuitos = new ArrayList<String>();
                System.out.println(this.model.getFacadeCorrida().listaCircuitoString());
                System.out.println("Circuitos a adicionar('F' para terminar)");
                String circuito = scin.nextLine();
                while(!(circuito.equals("f")) || !(circuito.equals("F"))){
                    listaCircuitos.add(circuito);
                    circuito = scin.nextLine();
                }
                this.model.addCampeonato(listaCircuitos, circuito);
            } else {
                System.out.println("Esse Campeonato já existe!");
            }
        }
        catch (NullPointerException e) {
            System.out.println(e.getMessage());
        }
    }

    private void adicionarCircuito() {
        try {
            //String nome, int dist, int voltas, int n_retas, int n_chicanes
            System.out.println("Nome do Circuito: ");
            String nomeCircuito = scin.nextLine();
            if (!this.model.existeCircuito(nomeCircuito)) {
                System.out.println("Distancia: ");
                int distancia = scin.nextInt();
                System.out.println("Numero de voltas: ");
                int numVoltas = scin.nextInt();
                System.out.println("Numero de retas: ");
                int numRetas = scin.nextInt();
                System.out.println("Numero de chicanas: ");
                int numChicanas = scin.nextInt();
                this.model.addCircuito(nomeCircuito, distancia, numVoltas, numRetas, numChicanas);
            } else {
                System.out.println("Esse Campeonato já existe!");
            }
        }
        catch (NullPointerException e) {
            System.out.println(e.getMessage());
        }
    }

    private void adicionarCarro() {
        System.out.println("tipo do Carro: ");
        System.out.println("C1 -> 1 ");
        System.out.println("C2 -> 2 ");
        System.out.println("GT -> 3 ");
        System.out.println("SC -> 4 ");
        try {
            int tipoCarro = scin.nextInt();
            System.out.println("Marca do Carro: ");
            String marcaCarro = scin.nextLine();
            System.out.println("Modelo do Carro: ");
            String modeloCarro = scin.nextLine();
            System.out.println("Hibrido: 0->sim; 1->nao");
            int hibrido = scin.nextInt();
            System.out.println("Potencia do Carro: ");
            int potencia = scin.nextInt();
            System.out.println("Perfil Aerodinamico do Carro(0 a 1): ");
            float pa = scin.nextFloat();
            int potenciaE = 0;
            if(hibrido==0){
                System.out.println("Potencia Motor Eletrico: ");
                potenciaE = scin.nextInt();
            }
            if(!this.model.existeCarro(modeloCarro)){
                switch(tipoCarro){
                    case(1):
                        int cilindrada = 6000;
                        if(hibrido==0)
                            this.model.addCarrohibridro(tipoCarro, marcaCarro, modeloCarro, cilindrada, potencia, pa, potenciaE);
                        else
                            this.model.addCarro(tipoCarro, marcaCarro, modeloCarro, cilindrada, potenciaE, pa);
                        break;
                    case(2):
                        System.out.println("Cilindrada: ");
                        cilindrada = scin.nextInt();
                        if(hibrido==0)
                            this.model.addCarrohibridro(tipoCarro, marcaCarro, modeloCarro, cilindrada, potencia, pa, potenciaE);
                        else
                            this.model.addCarro(tipoCarro, marcaCarro, modeloCarro, cilindrada, potenciaE, pa);
                        break;
                    case(3):
                        System.out.println("Cilindrada: ");
                        cilindrada = scin.nextInt();
                        if(hibrido==0)
                            this.model.addCarrohibridro(tipoCarro, marcaCarro, modeloCarro, cilindrada, potencia, pa, potenciaE);
                        else
                            this.model.addCarro(tipoCarro, marcaCarro, modeloCarro, cilindrada, potenciaE, pa);
                        break;
                    case(4):
                        cilindrada = 2500;
                        if(hibrido==0)
                            this.model.addCarrohibridro(tipoCarro, marcaCarro, modeloCarro, cilindrada, potencia, pa, potenciaE);
                        else
                            this.model.addCarro(tipoCarro, marcaCarro, modeloCarro, cilindrada, potenciaE, pa);
                        break;
                    default:
                        break;
                }
            }else{
                System.out.println("Esse Carro já existe!");
            }
        }catch(NullPointerException e)
        {
            e.printStackTrace();
        }
    }

    private void adicionarPiloto() {
        try {
            System.out.println("Nome do Piloto: ");
            String nomePiloto = scin.nextLine();
            if (!this.model.existePiloto(nomePiloto)) {
                System.out.println("chuva vs seco (0 a 1):\n0->bom em seco | 1->bom em chuva ");
                Float vs = scin.nextFloat();
                System.out.println("agressividade (0 a 1):\n0->conservador | 1->agressivo ");
                Float agressividade = scin.nextFloat();
                this.model.addPiloto(nomePiloto, vs, agressividade);
            } else {
                System.out.println("Esse Piloto já existe!");
            }
        }
        catch (NullPointerException e){
            System.out.println(e.getMessage());
        }
    }

    private void editarCampeonato() {
        System.out.println(this.model.getFacadeCorrida().listaCampeonatosString());
        try {
            System.out.println("Nome do Campeonato a alterar: ");
            String nomeCampeonato = scin.nextLine();
            if (!this.model.existeCampeonato(nomeCampeonato)) {
                ArrayList<String> circuitos = new ArrayList<>();
                System.out.println("Adicionar Ciruitos->1 || Remover Circuitos->2");
                int opt = scin.nextInt();
                if(opt==1){
                    System.out.println(this.model.getFacadeCorrida().listaCircuitoString());
                    System.out.println("Circuitos a adicionar('F' para terminar):");
                    String circuito = scin.nextLine();
                    while(!(circuito.equals("f")) || !(circuito.equals("F"))){
                        circuitos.add(circuito);
                        circuito = scin.nextLine();
                    }
                }else if(opt==2){
                    System.out.println("Circuitos a remover('F' para terminar):");
                    String circuito = scin.nextLine();
                    while(!(circuito.equals("f")) || !(circuito.equals("F"))){
                        circuitos.add(circuito);
                        circuito = scin.nextLine();
                    }
                }
                this.model.editCampeonato(opt, nomeCampeonato, circuitos);
                
            } else {
                System.out.println("Esse Piloto já existe!");
            }
        }
        catch (NullPointerException e) {
            System.out.println(e.getMessage());
        }
    }

    private void editarCircuito() {
        try {
            System.out.println(this.model.getFacadeCorrida().listaCircuitoString());
            System.out.println("Nome do Circuito: ");
            String nomeCircuito = scin.nextLine();
            if (!this.model.existeCircuito(nomeCircuito)) {
                System.out.println("Novo numero de voltas: ");
                int voltas = scin.nextInt();
                System.out.println(this.model.editCircuito(nomeCircuito, voltas));
            } else {
                System.out.println("Esse Campeonato já existe!");
            }
        }
        catch (NullPointerException e) {
            System.out.println(e.getMessage());
        }
    }

    private void editarCarro() {
        System.out.println(this.model.getFacadeCarro().garagemToString());
        System.out.println("Modelo do Carro a alterar: ");
        try {
            String modeloCarro = scin.nextLine();
            if(this.model.existeCarro(modeloCarro)){
                System.out.println("Parametro a alterar:");
                System.out.println("1->Potencia || 2->Cilindrada || 3->Potencia Eletrica");
                int opt = scin.nextInt();
                System.out.println("Novo valor: ");
                int value = scin.nextInt();
                System.out.println(this.model.editCarro(modeloCarro, opt, value));
            }else {
                System.out.println("Esse Carro nao existe!");
            }
        }catch(NullPointerException e)
        {
            e.printStackTrace();
        }
    }

    private void editarPiloto() {
        try {
            System.out.println(this.model.getFacadeCorrida().listaPilotosStr());
            System.out.println("Nome do Piloto a alterar: ");
            String nomePiloto = scin.nextLine();
            if(this.model.existePiloto(nomePiloto)) {
                System.out.println("Parametro a alterar:");
                System.out.println("1->Agressividade || 2->chuvaVSseco");
                int opt = scin.nextInt();
                System.out.println("Novo valor: ");
                Float value = scin.nextFloat();
                this.model.editPiloto(nomePiloto, opt, value);
            } else {
                System.out.println("Esse Piloto nao existe!");
            }
        }
        catch (NullPointerException e) {
            System.out.println(e.getMessage());
        }
    }
    
    private void removerCampeonato() {
        try {
            System.out.println(this.model.getFacadeCorrida().listaCampeonatosString());
            System.out.println("Nome do Campeonato a remover: ");
            String nomeCampeonato = scin.nextLine();
            if (this.model.existeCampeonato(nomeCampeonato)) {
                System.out.println(this.model.delCampeonato(nomeCampeonato));
            } else {
                System.out.println("Esse Campeonato nao existe!");
            }
        }
        catch (NullPointerException e) {
            System.out.println(e.getMessage());
        }
    }

    private void removerCircuito() {
        try {
            System.out.println(this.model.getFacadeCorrida().listaCircuitoString());
            System.out.println("Nome do Circuito a remover: ");
            String nomeCircuito = scin.nextLine();
            if(this.model.existeCircuito(nomeCircuito)) {
                System.out.println(this.model.delCircuito(nomeCircuito));
            } else {
                System.out.println("Esse Circuito nao existe!");
            }
        }
        catch (NullPointerException e) {
            System.out.println(e.getMessage());
        }
    }

    private void removerCarro() {
        try {
            System.out.println(this.model.getFacadeCarro().garagemToString());
            System.out.println("Nome do Modelo a remover: ");
            String nomeModelo = scin.nextLine();
            if(this.model.existeCarro(nomeModelo)) {
                System.out.println(this.model.delCarro(nomeModelo));
            } else {
                System.out.println("Esse Carro nao existe!");
            }
        }
        catch (NullPointerException e) {
            System.out.println(e.getMessage());
        }
    }
    
    private void removerPiloto() {
        try {
            System.out.println(this.model.getFacadeCorrida().listaPilotosStr());
            System.out.println("Nome do Piloto a remover: ");
            String nomePiloto = scin.nextLine();
            if(this.model.existeCarro(nomePiloto)) {
                System.out.println(this.model.delPiloto(nomePiloto));
            } else {
                System.out.println("Esse Piloto nao existe!");
            }
        }
        catch (NullPointerException e) {
            System.out.println(e.getMessage());
        }
    }

    private void criarLobby(){
        try {
            System.out.println(this.model.getFacadeCorrida().listaCampeonatosString());
            System.out.println("Nome do Campeonato a escolher: ");
            String nomeCampeonato = scin.nextLine();
            if (this.model.existeCampeonato(nomeCampeonato)) {
                int num_lobby = this.model.criarLobby(nomeCampeonato);
                System.out.println(this.model.getFacadeCarro().garagemToString());
                System.out.println("Modelo do Carro a usar ");
                String modeloCarro = scin.nextLine();
                System.out.println(this.model.getFacadeCorrida().listaPilotosStr());
                System.out.println("Piloto a usar ");
                String piloto = scin.nextLine();
                System.out.println(this.model.joinLobby(num_lobby, modeloCarro, piloto));
                int opt;
                while((opt = scin.nextInt()) != 2 || opt != 1)
                {
                    System.out.println("[NUM_LOBBY:" + num_lobby + "]  1->Comecar || 2->Proxima Corrida || 3-> particpantes || 4->resultados || 5-> sair");
                    if(opt== 1){ System.out.println(this.model.startLobby(num_lobby)); }
                    if(opt == 2){
                        System.out.println("Fazer alteracoes ao Carro: 0->sim || 1->nao");
                        int alteracoes = scin.nextInt();
                        if(alteracoes==0){
                            String tipo_carro = this.model.getTipoCarro(num_lobby);
                            System.out.println("Estado Motor(conservador | normal | agressivo) ");
                            String estadoMotor = scin.nextLine();
                            System.out.println("Tipo Pneus(macio | duro | chuva) ");
                            String tipoPneu = scin.nextLine();
                            System.out.println("Downforce(0 a 1): ");
                            float downforce = scin.nextFloat();
                            float afinacao = 0.5f;
                            if(tipo_carro.equals("C2") || tipo_carro.equals("C2H")){
                                System.out.println("Afinacao(0 a 1): ");
                                afinacao = scin.nextFloat();
                            }       
                            System.out.println(this.model.customizarCarro(num_lobby,tipo_carro,estadoMotor,tipoPneu,downforce,afinacao));
                            
                        }
                        System.out.print(this.model.proximaCorrida(num_lobby));
                        //verificar se ainda pode fazer alteraçoes
                        //fazer alteraçoes
                        //print proximaCorrida
                    }
                    if(opt == 3){ System.out.println(this.model.lobbyToString(num_lobby)); }
                } 
            } else {
                System.out.println("Esse Campeonato nao existe!");
            }
        }
        catch (NullPointerException e) {
            System.out.println(e.getMessage());
        }
    }
    
    private void juntarCampeonato(){
        System.out.println(this.model.getFacadeCorrida().listaLobbiesString());
        System.out.println("Lobbie a juntar: ");
        try{
            int idLobbie = scin.nextInt();
            if(this.model.existeLobbie(idLobbie)){
                System.out.println(this.model.lobbyToString(idLobbie));
                System.out.println(this.model.getFacadeCarro().garagemToString());
                System.out.println("Modelo do Carro a usar ");
                String modeloCarro = scin.nextLine();
                System.out.println(this.model.getFacadeCorrida().listaPilotosStr());
                System.out.println("Piloto a usar ");
                String piloto = scin.nextLine();
                System.out.println(this.model.joinLobby(idLobbie, modeloCarro, piloto));
                int opt;
                while((opt = scin.nextInt()) != 2 || opt != 1)
                {
                    System.out.println("[NUM_LOBBY:" + idLobbie + "]  1->Comecar || 2->Proxima Corrida || 3-> particpantes");
                    if(opt== 1){ System.out.println(this.model.startLobby(idLobbie)); }
                    if(opt == 2){
                        System.out.println("Fazer alteracoes ao Carro: 0->sim || 1->nao");
                        int alteracoes = scin.nextInt();
                        if(alteracoes==0){
                            String tipo_carro = this.model.getTipoCarro(idLobbie);
                            System.out.println("Estado Motor(conservador | normal | agressivo) ");
                            String estadoMotor = scin.nextLine();
                            System.out.println("Tipo Pneus(macio | duro | chuva) ");
                            String tipoPneu = scin.nextLine();
                            System.out.println("Downforce(0 a 1): ");
                            float downforce = scin.nextFloat();
                            float afinacao = 0.5f;
                            if(tipo_carro.equals("C2") || tipo_carro.equals("C2H")){
                                System.out.println("Afinacao(0 a 1): ");
                                afinacao = scin.nextFloat();
                            }       
                            System.out.println(this.model.customizarCarro(idLobbie,tipo_carro,estadoMotor,tipoPneu,downforce,afinacao));
                            
                        }
                        System.out.print(this.model.proximaCorrida(idLobbie));
                        
                        //questiona se quer fazer alteraçoes
                        //get campeonato
                        //verificar se ainda pode fazer alteraçoes
                        //fazer alteraçoes
                        //print proximaCorrida
                    }
                    if(opt == 3){ System.out.println(this.model.lobbyToString(idLobbie)); }
                } 
            }else{
                System.out.println("Esse Lobbie nao existe!");
            }
        }catch (NullPointerException e) {
            System.out.println(e.getMessage());
        }
    }

    private void mostrarPontos(){
        System.out.print(this.model.mostrar_pontos());
    }

    private void login(){
        System.out.println("Nome de utilizador: ");
        String username = scin.nextLine();
        System.out.println("Password: ");
        String password = scin.nextLine();
        int check = this.model.login(username, password);
        if(check == 1){
            System.out.println("Login efetuado com sucesso!");
            this.menuAdim.run();
            
        } else if (check == 0){
            System.out.println("Login efetuado com sucesso!");
            this.menuUtilizador.run();
        } else {
            System.out.println("Login falhou!");
        }
    }

    private void registo(){
        System.out.println("Nome de utilizador: ");
        String username = scin.nextLine();
        System.out.println("Password: ");
        String password = scin.nextLine();
        String r = this.model.registo(username, password);
        System.out.println(r);
        if(r.equals("Registado com sucesso e login efetuado - " + username))
            this.menuUtilizador.run();
    }

    private void convidado(){
        System.out.println(this.model.loginConvidado());
        this.menuUtilizador.run();
    }

    
}