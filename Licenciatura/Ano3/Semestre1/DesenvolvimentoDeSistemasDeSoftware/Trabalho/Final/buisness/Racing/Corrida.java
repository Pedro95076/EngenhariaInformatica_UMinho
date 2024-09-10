package buisness.Racing;

import java.io.*;
import java.util.*;
import java.util.Random;
import buisness.Carro.*;
import buisness.Utilizador.*;


public class Corrida implements Serializable {
	
	private Circuito circuito;
	private Map<Participante, Integer> dnf;
	private int clima;
	private float Tempos;
	private List<Participante> participantes;
	private int volta = 0;
	
	public int getClima() {
		return this.clima;
	}

	public void setClima(int clima) {
		this.clima = clima;
	}

	public void setTempos(float tempos) {
		this.Tempos = tempos;
	}

	public int getVolta() {
		return this.volta;
	}

	public Corrida() {}

	public Corrida(Circuito circuito, Map<Participante, Integer> dnf, int clima, float tempos, List<Participante> participantes, int volta) {
		this.circuito = circuito;
		this.dnf = dnf;
		this.clima = clima;
		this.Tempos = tempos;
		this.participantes = participantes;
		this.volta = volta;
	}

	public Corrida(Circuito circuito, int clima, List<Participante> listaParticipantes) {
		this.circuito = circuito;
		this.dnf = new HashMap<Participante,Integer>();
		this.clima = clima;
		this.participantes = listaParticipantes;
		this.Tempos = 0;
	}

	public Circuito getCiruito()
	{
		return this.circuito.clone();
	}

	public float getTempos() {
		return this.Tempos;
	}

	public void setCircuito(Circuito c)
	{
		this.circuito = c;
	}


	//alterar para copiar listas valor a valor
	public Corrida(Corrida corrida) {
		this.circuito = corrida.circuito;
		this.dnf = corrida.dnf;
		this.Tempos = corrida.Tempos;
		this.clima = corrida.clima;
		this.participantes = corrida.participantes;
		this.volta = corrida.volta;
	}

	public java.util.Map<Participante, Integer> getDNF() {
		return this.dnf;
	}



	public Corrida clone() {
		return new Corrida(this);
	}

 // funçao que irá simular a corrida devolvendo a lista dos participantes
	public List<Participante>  simulaCorrida() {
		int num_voltas = circuito.getVoltas();
		for(int i = 0; i<num_voltas;i++){
			atualizarPosicoes();//simula o que vai acontecer a cada volta
			for(Participante p : this.participantes){
				if(!this.getDNF().containsKey(p)){//verifica se o participante já foi desqualificado
					Boolean falhou = verificaFalhaMotor(p, i+1);//verifica se o motor do participante falhou
					if(falhou){falhaMotor(p, i+1);}//se sim desqualifica o particante e a volta a que o motor falhou
				}
			}
			//print do estado da corrida a cada volta
			System.out.print("volta " + (i+1));
			System.out.print("\n--------------\n");
			System.out.print(printResultados());
			System.out.print("DNF\n");
			System.out.print(DNFtoString());
			System.out.print("--------------\n");
		}
		for (Participante participante : dnf.keySet()) {// para todos os participantes desqualificados
        	participante.setPosicao(0); //coloca a sua posiçao a 0
    	}
		return this.participantes;//devolve a lista dos participantes
	}

	//funçao para testes
	public String printResultados() {
		String str = "";
		for (Participante part : this.participantes){
            str += part.getPosicao() + "º: " + part.getUtilizador().getUser() + "\n"; 
        }
		return str;
	}

	
	//funçao para testes
	public String DNFtoString(){
		String str = "";
		for (Map.Entry<Participante, Integer> entry : dnf.entrySet()) {
			str += entry.getKey().getUtilizador().getUser() + ":volta " + entry.getValue() + "\n";
		}
		return str;
	}

	public java.util.List<Participante> getParticipante() {
		return this.participantes;
	}


	//funcao premium que simula todo o que irá acontecer numa dada seccao
	public void verificaUltrapassagemPrem(Seccao sec) {
		int index = 0;
		for(Participante p : participantes){
			if (!this.getDNF().containsKey(p)){//se o participante ainda estiver na corrida
				Carro carro = p.getCarro();
				Piloto piloto = p.getpiloto(); 
				int posicao = p.getPosicao();
				int gdu = sec.getGDU(); //grau de dificuldade da seccao
				boolean inTime = inTime(p,index); //verifica se o utilizador está perto o suficiente para tentar a ultrapassagem
				if(gdu != 3 && posicao>1 && inTime){
					Boolean ultrapassou = tentaUltrapassagem(carro, piloto, clima, gdu);//verifica se o part foi capaz de ultrapassar o carrro a sua frente
					if(ultrapassou){
						avancaUm(p);//participante avança uma posiçao
					}else{
						verificaCrash(p);//verifica se o participante teve um crash nessa seccao
					}
				}else{//casso n seja possivel fazer a ultrapassagem verifica se o participante se despistou ou nao 
					verificaCrash(p);
				}
				index++;//index para saber a posiçao da lista ordenada de participantes 
			}
		}
	}


	//funcao nao premium que simula todo o que irá acontecer numa dada seccao muito semelhante a anterior
	public void verificarUltrapassagem(Seccao sec) {
		for(Participante p : participantes){
			if (!this.getDNF().containsKey(p))//se o participante ainda estiver na corrida
			{	
				Carro carro = p.getCarro();
				Piloto piloto = p.getpiloto(); 
				int posicao = p.getPosicao();
				int gdu = sec.getGDU();
				if(gdu != 3 && posicao>1){
					Boolean tenta = tentaUltrapassagem(carro, piloto, clima, gdu);
					if(tenta){
						avancaUm(p);
					}else{
						verificaCrash(p);
					}
				}else{
					verificaCrash(p);
				}
			}
		}
		Collections.sort(this.getParticipante(), new StockComparator());
	}
	//funcao que itera por todas as seccoes de um determinado circuito determinando o que acontece em cada uma delas
	public void atualizarPosicoes() {
		ArrayList<Seccao> listaSeccoes = this.circuito.getListaSeccoes();
		if(haPremium()){//se houver um participante com premuim utiliza a funcao premium de ultrapassagem
			for(Seccao sec : listaSeccoes){
				calculaTimeDiff();//atualizar a diferenca dos participantes para o 1ª lugar
				verificaUltrapassagemPrem(sec);//verificar a ultrapassagem de modo premium
			}
		}else{//se nao utiliza a funcao default
			for(Seccao sec :listaSeccoes){
				calculaTimeDiff();//atualizar a diferenca dos participantes para o 1ª lugar
				verificarUltrapassagem(sec);//verificar a ultrapassagem de modo premium
			}
		} 
	}

	//funcao que com um conjunto de fatores verifica se o houve uma falha no motor do participante
	public Boolean verificaFalhaMotor(Participante participante, int voltas) {
		Carro carro = participante.getCarro();
		estadoMotor estado =  carro.getEstado();// valor do estado do motor do carro
		float fiabilidade = carro.getFiabilidade();// valor calculado previamente da probabilidade do motor falhar
		switch(estado){
			case CONSERVADOR: // se o motor estiver conservador diminui a prob de falhar
				fiabilidade += 0.05;
				break;
			case AGRESSIVO:// se o motor estiver agressivo aumenta a prob de falhar
				fiabilidade -= 0.05;
				break;
			default:
				break;
		}
		Random rand = new Random();
		float prob = rand.nextFloat();//valor aleotorio
		return(prob > fiabilidade);// ver se o motor falhou ou nao
	}

	//funcao que coloca o participante na lista de corredores que não irao acabar a corrida
	public void falhaMotor(Participante participante, int volta) {
		vaiUlt(participante);
		dnf.put(participante, volta);
	}
	//funcao que verifica se existem utilizadores premium na lista de participantes
	public boolean haPremium() {
		for(Participante p : this.getParticipante()){
			if (!this.getDNF().containsKey(p))//se o participante ainda estiver na corrida
			{	
				if (p.getUtilizador() instanceof Jogador){// verifica se o participante e um jogador registado
					Jogador j = (Jogador) p.getUtilizador();
					if(j.getIsPremium()){//verifica se o jogador tem premium
						return true;
					}
				} 
			}
		}
		return false;
	}

	//funcao que muda as posicoes de 2 participantes depois de uma ultrapassagem
	public void avancaUm(Participante participante) {
		System.out.println("FUNCAO AVNAÇA UM");
		int indexInFront = participante.getPosicao()-2;//ir buscar o index do participante a frente
		Participante inFront = this.participantes.get(indexInFront);//participante a frente
		System.out.println("participante que ultrapassou: " + participante.getUtilizador().getUser() + " posicao inicial " + participante.getPosicao());
		System.out.println("posicao carro a frente: " + inFront.getUtilizador().getUser() + " posicao inicial " + inFront.getPosicao());
		inFront.setPosicao(indexInFront+2);//mudar a posicao do participante acabado de ultrapassar para a posicao um valor acima
		participante.setPosicao(indexInFront+1);//mudar a posicao do participante que ultrapassou para a posicao um valor abaixo
		System.out.println("participante que ultrapassou: " + participante.getUtilizador().getUser() + " posicao final " + participante.getPosicao());
		System.out.println("posicao carro a frente: " + inFront.getUtilizador().getUser() + " posicao final " + inFront.getPosicao());
		Collections.sort(this.getParticipante(), new StockComparator());//dar sort ao array por posicao do participante
	}

	//funcao que coloca o participante na ultima posicao dos particantes ainda na corrida
	public void vaiUlt(Participante participante) {
		System.out.println("FUNCAO VAIULT");
		System.out.println(participante.getUtilizador().getUser()+ " CRASHOU");
		int posAtual = participante.getPosicao();//posicao initial do participante
		int numParticipantes = this.getParticipante().size();//num da lista de participantes
		int	numDNF = dnf.size();//num de participantes que abandonaram a corrida
		int lastPos = numParticipantes-numDNF;//ultimo lugar dos participantes ainda na corrida
		participante.setPosicao(lastPos);// colocar o participante em ultimo dos participantes ainda na corrida 
		for(Participante p : this.getParticipante()){
			if (!this.getDNF().containsKey(p))//se o participante ainda estiver na corrida
			{	
				int posicao = p.getPosicao();//buscar a posicao do particpante em questao
				System.out.println("participante que ultrapassou: " + p.getUtilizador().getUser() + " posicao inicial " + posicao);
				if(!(p.equals(participante)) && posicao>posAtual)//se nao for o participante que se despistou e a sua posicao for superior 
					p.setPosicao(posicao-1);//decrementa a sua posicao
				System.out.println("participante que ultrapassou: " + p.getUtilizador().getUser() + " posicao final " + p.getPosicao());
			}
		}
		//Collections.sort(this.getParticipante(), new StockComparator());
	}


	//calcula a probabilidade de um participante se despistar
	public boolean calculaCrash(float agrPiloto, tipoPneu pneus, int clima, float vsPiloto, int volta){
		Random rand = new Random();
		float limite = rand.nextFloat();//valor aleatoria 
		//float probPneus = probPneus(pneus, clima, volta);// valor em que o tipo de pneu afeta a prob de se despistar
		float prob = probClima(pneus, clima, volta,vsPiloto);// calcula a prob de se dispistar considerando o clima, os pneus, o piloto e a volta correntr
		//float prob = (probPneus*probClima);// probabilidade do participante se despistar
		prob += 0.05 + (-0.1*agrPiloto);//quanto mais agressivo o piloto maior a prob de se despitar
		return(limite>prob);//se o valor aleatorio for maior que a prob calculada o participante despista se
	}

	public float probClima(tipoPneu pneus, int clima, int volta, float vsPiloto){
		float probInicial = 1;
		switch(pneus){
			case MACIO:
				probInicial -= (0.0033*volta);//pneus macios desgastam-se mais facilmente
				break;
			case DURO:
				probInicial -= (0.0025*volta);//pneus duros demoram mais a desgastar
				break;
			case CHUVA:
				if(clima == 1) //caso esteja a chuver
					probInicial -= (0.0028*volta);	
				else // caso esteja sol, penaliza de forma severa o participante.
					probInicial -= (0.025*volta); 
				break;
			default:
				probInicial -= (0.003*volta);
				break;
		}
		if(clima == 0)
			probInicial += -0.05 + (0.1*vsPiloto);// pilotos melhores em seco sao recompensados 
		else
			probInicial += 0.05 + (-0.1*vsPiloto);// pilotos melhores em chuva sao recompensados 
		return probInicial;
	}



	//funcao que ira atribui valores aleatorios para a dif de tempo para o 1ª lugar
	public void calculaTimeDiff() {
		Collections.sort(this.getParticipante(), new StockComparator());//garantir que a lista está ordenada
		int size = this.participantes.size();//num de participantes
		Random random = new Random();
		float time = random.nextFloat();//valor que irá ser usado como diferenca
		this.participantes.get(0).setTimeDiff(0);//participante em 1º lugar tem tempo a zero
		for(int i = 1; i<size;i++){//percorrer a lista para alterar os valores
			Participante p = this.participantes.get(i);
			if(!this.getDNF().containsKey(p)){//se o participante ainda estiver na corrida
				float inFront = this.participantes.get(i-1).getTimeDiff();//vai buscar o tempo do participante a sua frente
				this.participantes.get(i).setTimeDiff(inFront+(time*10));//soma ao valor anterior o tempo criado 
			}
		}
	}

	public boolean inTime(Participante participante, int index){
		//calcula a diferenca de tempos entre o participante e o carro a sua frente
		float timeDiff = participante.getTimeDiff() - this.participantes.get(index-1).getTimeDiff();
		if(timeDiff>2)// se esta diferenca for maior que 2 nunca pode tentar a ultrapassagem
			return false;
		else{
			Carro carro = participante.getCarro();
			String classeCarro = carro.getClass().getSimpleName();//classe do carro do participante
			Carro carroInFront = this.participantes.get(index).getCarro();
			String classInFront = carroInFront.getClass().getSimpleName();//classe do carro na posiçao em frente
			//dependendo da classe verifica se existe possibilidade de ultrapassar ou nao
			return classDif(classeCarro, classInFront, timeDiff);
		}		
	}


	public boolean tentaUltrapassagem(Carro carro, Piloto piloto, int clima, int gdu) {
		float probInicial = 1;
		estadoMotor estado = carro.getEstado();
		float agressividade = piloto.getAgressividade();
		Random random = new Random();
		float limite = random.nextFloat();
		if (clima == 1)// caso esteja a chover prob de ultrapassar diminui
			probInicial -= 0.05;
		if(gdu == 5){//caso o GDU seja dificiil
			probInicial -=0.1;
		}
		probInicial += -0.05 + (0.1*agressividade);
		switch(estado){
			case CONSERVADOR:
				probInicial -= 0.05;
				break;
			case AGRESSIVO:
				probInicial += 0.05;
				break;
			default:
				break;
		}
		if(limite>probInicial)
			return true;
		else
			return false;
	}

	public boolean verificaCrash(Participante p){
		float agressividade = p.getpiloto().getAgressividade();
		float vs = p.getpiloto().getChuvaVSseco();
		tipoPneu pneus = p.getCarro().getPneus();
		if(calculaCrash(agressividade, pneus, clima, vs, volta)){
			vaiUlt(p);
		}
		return true;
	}

	public boolean classDif(String classeCarro, String classInFront, float timeDiff){
		if(classeCarro.equals(classInFront)){
			if(timeDiff<1)
				return true;
			else
				return false;
		}
		switch(classeCarro){
			case("C1H"):
				if(timeDiff<2)
					return true;
				else 
					return false;
			case("C1"):
				if(classInFront.equals("C1H")){
					if(timeDiff<0.5f)
						return true;
					else 
						return false;
				}else{
					if(timeDiff<2)
						return true;
					else 
						return false;
				}
			case("C2H"):
				if(classInFront.equals("C1H") || classInFront.equals("C1") ){
					if(timeDiff<0.5f)
						return true;
					else 
						return false;
				}else{
					if(timeDiff<2)
						return true;
					else 
						return false;
				}
			case("C2"):
				if(classInFront.equals("C1H") || classInFront.equals("C1") || classInFront.equals("C2H")){
					if(timeDiff<0.5f)
						return true;
					else 
						return false;
				}else{
					if(timeDiff<2)
						return true;
					else 
						return false;
				}
			case("GTH"):
				if(classInFront.equals("GT") || classInFront.equals("SC")){
					if(timeDiff<2)
						return true;
					else 
						return false;
				}else{
					if(timeDiff<0.5f)
						return true;
					else 
						return false;
				}
			case("GT"):
				if(classInFront.equals("SC")){
					if(timeDiff<2)
						return true;
					else 
						return false;
				}else{
					if(timeDiff<0.5f)
						return true;
					else 
						return false;
				}
			case("SC"):
				if(timeDiff<0.5f)
					return true;
				else 
					return false;
			default:
				return false;
		}
	}

	class StockComparator implements Comparator<Participante> {
		@Override
		public int compare(Participante p1, Participante p2)
		{
			if (p1.getPosicao() == p2.getPosicao())
			return 0;
			else if (p1.getPosicao() > p2.getPosicao()) // se p1 estiver a frente de p2
			return 1;
			else
			return -1;
		}
	}

}