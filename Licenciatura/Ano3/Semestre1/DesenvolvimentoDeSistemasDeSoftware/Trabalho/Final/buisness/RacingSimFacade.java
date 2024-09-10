package buisness;

import java.util.*;
import buisness.Carro.*;
import buisness.Racing.*;
import buisness.Utilizador.*;

public class RacingSimFacade implements IRacingSimFacade {
	//carros
	private FacadeCarro fCarro = new FacadeCarro();
	//corrida
	private FacadeCorrida fCorrida = new FacadeCorrida();
	//utilizador 
	private FacadeUtilizador fUtilizador = new FacadeUtilizador();
	//utilizador a usar o sistema
	private Utilizador you = null;

	
	public String addCircuito(String nome, int dist, int voltas, int n_retas, int n_chicanes){
		if (fCorrida.getMapCircuitos().containsKey(nome)) return "Failure";
		Circuito circ = new Circuito(); //criar objeto
		circ.createCircuito(nome, dist, voltas, n_retas, n_chicanes); //atribuir parametros
		fCorrida.getMapCircuitos().put(nome, circ);
		return "Success";
	}

	public String addCampeonato(ArrayList<String> circuitos, String nomeProva){
		ArrayList<Circuito> listaCircuitos = new ArrayList<>();
		for(String nome : circuitos){
			Circuito c = fCorrida.getMapCircuitos().get(nome);
			if(c!=null)
				listaCircuitos.add(c);
		}  
		return ( (fCorrida.insertCampeonato(listaCircuitos, nomeProva)) ? "Sucess" : "Failure");
	}

	//C1
		//c1 -> marca,modelo,potencia,cilindrada,pa
		//c1h -> marca,modelo,potencia,cilindarda,pa,potenciaE
		//c2 -> marca,modelo,potencia,cilindrada,pa,afinacao
		//c2h->marca,modelo,potencia,cilindrada,pa,afinacao,potenciaE
		//gt->marca,modelo,potencia,cilindrada,pa
		//gth->marca,modelo,potencia,cilindrada,pa,potenciaE
		//sc->marca,modelo,potencia,cilindrada,pa

	//Hibridos				 //1 -> 3  
		public String addCarrohibridro(int tipo, String marca, String modelo,int cilindrada, int potencia, float pa, int potenciaE) {
			boolean deuCerto = fCarro.addCarrohibridro(tipo, marca, modelo, cilindrada, potencia, pa, potenciaE);
			//try
			//{
			//	switch (tipo)
			//	{
			//		case 1:
			//			C1H c1 = new C1H(marca,modelo,cilindrada,potencia,pa,potenciaE);
			//			deuCerto = ( (fCarro.addCarro(c1)) ?  true :  false);
			//			break;
			//		case 2:
			//			C2H c2 = new C2H(marca,modelo,cilindrada,potencia,pa,potenciaE);
			//			deuCerto = ( (fCarro.addCarro(c2)) ?  true :  false);
			//			break;
			//		case 3:
			//			GTH gt = new GTH(marca,modelo,cilindrada,potencia,pa,potenciaE);
			//			deuCerto = ( (fCarro.addCarro(gt)) ?  true :  false);
			//			break;
			//		default:
			//			break;		
			//	}
			//}
			//catch(Exception e)
			//{
			//	e.printStackTrace();
			//}
			return (deuCerto ? "Success" : "Failure");

	}
	//Nao hibridos				//1->4 
		public String addCarro(int tipo, String marca, String modelo, int cilindrada, int potencia, float pa) {
				boolean deuCerto = false;
			try
			{
				switch (tipo)
				{
					case 1:
						C1 c1 = new C1(marca,modelo,cilindrada,potencia,pa);
						deuCerto = ( (fCarro.addCarro(c1)) ?  true :  false);
						break;
					case 2:
						C2 c2 = new C2(marca,modelo,cilindrada,potencia,pa);
						deuCerto = ( (fCarro.addCarro(c2)) ?  true :  false);
						break;
					case 3:
						GT gt = new GT(marca,modelo,cilindrada,potencia,pa);
						deuCerto = ( (fCarro.addCarro(gt)) ?  true :  false);
						break;
					case 4:
						SC sc = new SC(marca,modelo,cilindrada,potencia,pa);
						deuCerto = ( (fCarro.addCarro(sc)) ?  true :  false);
						break;
					default:
						break;		
				}
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
			return (deuCerto ? "Success" : "Failure");
	}

	public String customizarCarro(int num_lobby, String tipo_carro, String estado_motor, String tipo_pneu, float downforce, float afinacao)
	{
		tipoPneu p = tipoPneu.fromString(tipo_pneu);
		estadoMotor e  = estadoMotor.fromString(estado_motor);
		fCorrida.getMapLobbys().get(num_lobby).getListaPart().get(you.getUser()).getCarro().setDownforce(downforce);
		fCorrida.getMapLobbys().get(num_lobby).getListaPart().get(you.getUser()).getCarro().setEstado(e);
		fCorrida.getMapLobbys().get(num_lobby).getListaPart().get(you.getUser()).getCarro().setPneus(p);
		if(tipo_carro.equals("C2"))
			{
				C2 c2 = (C2) fCorrida.getMapLobbys().get(num_lobby).getListaPart().get(you.getUser()).getCarro();
				c2.setAfinacao(afinacao);
				fCorrida.getMapLobbys().get(num_lobby).getListaPart().get(you.getUser()).setCarro(c2);
			} 
		if(tipo_carro.equals("C2H"))
			{
				C2H c2h = (C2H) fCorrida.getMapLobbys().get(num_lobby).getListaPart().get(you.getUser()).getCarro();
				c2h.setAfinacao(afinacao);
				fCorrida.getMapLobbys().get(num_lobby).getListaPart().get(you.getUser()).setCarro(c2h);
			} 
		return "Sucess - carro customizado";
	}

	//pode alterar a cilindrada ou a potencia de um carro (1-> potencia 2 -> cilindrada 3 -> motor eletrico)
	public String editCarro(String modelo,int opt, int value) {
		try
		{
		if(fCarro.getGaragem().containsKey(modelo))
			 return "Failure";
			
		String classe = fCarro.getGaragem().get(modelo).getClass().getSimpleName();
		//editar potencia
		if(opt == 1)
		{
				fCarro.getGaragem().get(modelo).setPotencia(value);
				return "Sucess";
		}
		//editar cilindrada
		if (opt == 2 && (classe.equals("C2") || classe.equals("C2H") || classe.equals("C2H") || classe.equals("GTH")) )
		{
				fCarro.getGaragem().get(modelo).setCilindrada(value);
				return "Sucess";
		}
		//editar motor eletrico
		if(opt == 3 && (classe.equals("C1H") || classe.equals("C2H") || classe.equals("GTH")) )
		{
			switch(classe)
			{
				case("C1H"):
					C1H copia1 = (C1H)fCarro.getGaragem().get(modelo);
					copia1.setMotorEletrico(value);
					fCarro.getGaragem().replace(modelo,copia1);
					return "Sucess";
				case("C2H"):
					C2H copia2 = (C2H)fCarro.getGaragem().get(modelo);
					copia2.setMotorEletrico(value);
					fCarro.getGaragem().replace(modelo,copia2);
					return "Sucess";
				case("GTH"):
					GTH copia3 = (GTH)fCarro.getGaragem().get(modelo);
					copia3.setMotorEletrico(value);
					fCarro.getGaragem().replace(modelo,copia3);
					return "Sucess";
				default:
					return "Failure";
			}	
		}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		return "Failure";
	}


	public String addPiloto(String nome, float chuvaVSseco, float  agressividade) {
		if(fCorrida.getMapPilotos().containsKey(nome)) return "Failure";
		Piloto p = new Piloto(nome, chuvaVSseco, agressividade);
		fCorrida.getMapPilotos().put(nome,p);
		return "Sucess";
	}

	//1 -> add 2 -> remover
	public String editCampeonato(int opt, String nome_campeonato, List<String> circuitos) {
		if(opt == 1)
		{
			for (String s : circuitos)
				fCorrida.getMapCampeonatos().get(nome_campeonato).
						 addCircuito( fCorrida.getMapCircuitos().get(s).clone() );
			return "Sucess";
		}
		if(opt == 2)
		{
			for(String s : circuitos)
				{
					fCorrida.getMapCampeonatos().get(nome_campeonato).getCircuitos().
							 remove( fCorrida.getMapCircuitos().get(s).clone() );
				}
			return "Sucess";
		}
		else
			return "Failure";
	}

	public String editCircuito(String nome_circuito, int n_voltas) {
		if(!fCorrida.getMapCircuitos().containsKey(nome_circuito)) return "Failure";
		fCorrida.getMapCircuitos().get(nome_circuito).setVoltas(n_voltas);
		return "Sucess";
	}


	public String editPiloto(String nome_piloto,int opt, float valor) {
		if(!fCorrida.getMapPilotos().containsKey(nome_piloto)) return "Failure";
		if(opt == 1)
		{
			fCorrida.getMapPilotos().get(nome_piloto).setAgressividade(valor);
			return "Sucess";
		}
		if(opt == 2)
		{
			fCorrida.getMapPilotos().get(nome_piloto).setChuvaVSseco(valor);
			return "Sucess";
		}
		return "Failure";
	}		

	public String delCircuito(String nome_circuito) {
		if(!fCorrida.getMapCircuitos().containsKey(nome_circuito)) return "Failure";
		Circuito c = fCorrida.getMapCircuitos().get(nome_circuito);
		for(Map.Entry<String,Campeonato> pair : fCorrida.getMapCampeonatos().entrySet())
			{
				pair.getValue().getCircuitos().remove(c);
			}
		fCorrida.getMapCircuitos().remove(nome_circuito);
		return "Sucess";
	}

	public String delCampeonato(String nome_campeonato) {
		if(!fCorrida.getMapCampeonatos().containsKey(nome_campeonato)) return "Failure";
		fCorrida.getMapCampeonatos().remove(nome_campeonato);
		return "Sucess";
	}

	public String delCarro(String nome_carro) {
		if(!fCarro.getGaragem().containsKey(nome_carro)) return "Failure";
		fCarro.getGaragem().remove(nome_carro);
		return "Sucess";
	}

	public String delPiloto(String nome_piloto) {
		if(!fCorrida.getMapPilotos().containsKey(nome_piloto)) return "Failure";
		fCorrida.getMapPilotos().remove(nome_piloto);
		return "Sucess";
	}

	public boolean existeCampeonato(String nomeCampeonato){
		return fCorrida.getMapCampeonatos().containsKey(nomeCampeonato);
	}
	
	public boolean existeCircuito(String nomeCircuito){
		return fCorrida.getMapCircuitos().containsKey(nomeCircuito);
	}

	public boolean existePiloto(String nomePiloto){
		return fCorrida.getMapPilotos().containsKey(nomePiloto);
	}

	public boolean existeCarro(String modelo){
		boolean res = false;
		try{
			if(!(fCarro.findCarro(modelo) == null))
				res = true;
		}catch(Exception e){
			e.printStackTrace();
		}
		return res;
	}

	public boolean existeLobbie(int idLobbie){
		return fCorrida.getMapLobbys().containsKey(idLobbie);
	}

	public FacadeCorrida getFacadeCorrida(){
		return this.fCorrida;
	}

	public FacadeCarro getFacadeCarro(){
		return this.fCarro;
	}

	//um utilizador utiliza uma "template" que ja esta no sistema(e que foi adicionada pelo administrador) para criar um lobby
	public int criarLobby(String nomeCampeonato){
		Campeonato campeonato = fCorrida.getMapCampeonatos().get(nomeCampeonato).clone();
		int num_lobby = fCorrida.getMapLobbys().size();
		fCorrida.getMapLobbys().put((num_lobby+1), campeonato);
		return num_lobby+1;
	}

	public String lobbyToString(int num_lobby)
	{
		if(!fCorrida.getMapLobbys().containsKey(num_lobby)) return "Failure - Campeonato Inexistente";
		return fCorrida.getMapLobbys().get(num_lobby).toString();

	}

	//listalobbysString
	//scanner -> numlobby
	//print(lobbytoString(num_lobby))
	//garagemtoString
	//scanner -> digaCarro
	//pilotostoString
	//scanner -> digaPiloto
	//joinlobby(num_lobby, modelo_carro,nome_piloto)
	//customizar carro




	//entrar no lobby de um user 
	public String joinLobby(int num_lobby, String modelo_carro, String nome_piloto)
	{
		if(you == null || this.getClass().getSimpleName().equals("Administrador")) return "Failure";// sem login/registo ou é admin
		
		if(!fCorrida.getMapLobbys().containsKey(num_lobby)) //lobby nao existe
			return "Failure";
		
		Carro c = null;
		Piloto p = null;
		try 
		{
			c = fCarro.findCarro(modelo_carro);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		p = fCorrida.findPiloto(nome_piloto);
		if(p == null || c == null)
			return "Failure";

		Participante participante = new Participante(you,p,c);
		
		fCorrida.getMapLobbys().get(num_lobby).addParticipante(participante);
		
		return "Sucess";
	}

	public String startLobby(int num_lobby)
	{
		Campeonato campeonato = fCorrida.getMapLobbys().get(num_lobby);
		fCorrida.startCampeonato(campeonato);
		return "Sucesso - Corridas foram criadas a partir dos circuitos e participantes!";
	}

	public String proximaCorrida(int num_lobby){
		Campeonato campeonato = fCorrida.getMapLobbys().get(num_lobby);
		return(fCorrida.simularProximaCorrida(campeonato.getProva()));
	}

	public String getTipoCarro(int num_lobby)
	{
		return fCorrida.getMapLobbys().
						get(num_lobby).getListaPart().get(you.getUser()).
						getCarro().getClass().getSimpleName();
	}


	public String mostrar_pontos()
	{
		if(you == null || you.getClass().getSimpleName().equals("Administrador") )return "Failure";
		if(you.getClass().getSimpleName().equals("Convidado")) return "Convidados não teem pontos";
		Jogador j = (Jogador) you;
		String pontos = "PONTOS :" + j.getPoints() +"!!";
		return pontos;
	}

	public String loginConvidado()
	{
		you = fUtilizador.LoginConvidado();
		return "Sucess - " + you.getUser();
	}


	public int login(String user, String password)
	{
		try 
		{
			you = fUtilizador.Login(user, password);
			System.out.println(user);
			System.out.println(you.getUser());
			if(user.equals("admin")) return 1;
			return 0;
		}
		catch(Exception e)
		{
			return -1;
		}

	}

	public String registo(String user,String password)
	{
		try
		{
			fUtilizador.Registo(user, password, false);
			you = fUtilizador.Login(user,password);

			return "Registado com sucesso e login efetuado - " + user;
		}
		catch(Exception e)
		{
			return "Algo correu mal";
		}
	}





	/*
		//UI
		System.out.println(fCorrida.listaPilotosStr());
		System.out.println("Digite o piloto que quer usar(Nome do Piloto");
			p = fCorrida.findPiloto(nome_piloto);
		//customizacao do carro
		
		String tipo_carro = c.getClass().getSimpleName();

		//funcoes para o UI//
		System.out.println("Mudar downforce?(0.00 - 1.00 || VALOR DEFAULT -> 0.50)");
		float df = sc.nextFloat();

		c.setDownforce(df);

		System.out.println("Escolha tipo de pneus(duro/macio/chuva)");
		tipoPneu pneu = tipoPneu.fromString(sc.nextLine());
		c.setPneus(pneu); 

		System.out.println("Escolha tipo de pneus(conservador/normal/agressivo)");
		estadoMotor estado = estadoMotor.fromString(sc.nextLine());
		c.setEstado(estado);
		//criar participante
		Participante participante = null;

		if(tipo_carro.equals("C2"))
		{
			
			System.out.println("Mudar afinacao?(0.00 - 1.00 || VALOR DEFAULT -> 0.50)");
			float afinacao = sc.nextFloat();
			C2 c2 = (C2)c;
			c2.setAfinacao(afinacao);
			participante = new Participante(you,p,c2);
			
		}
		*/



}