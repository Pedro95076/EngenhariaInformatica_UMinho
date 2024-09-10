package buisness.Racing;
import java.io.*;
import java.security.KeyStore.Entry;
import buisness.Carro.*;


import java.util.*;

public class Campeonato implements Serializable {

	private Map<String, Integer> classificacao;
	private int numCorrida;
	private String prova;
	private Map<String, Participante> participantes;
	private ArrayList<Circuito> circuitos; //
	private Map<Corrida,Boolean> corridas; //vazio até o campeonato começar
	
	public void setNumCorrida(int numCorrida) {
		this.numCorrida = numCorrida;
	}

	public int getNumCorrida() {
		return this.numCorrida;
	}

	public String getProva() {
		return this.prova;
	}

	public void setProva(String prova) {
		this.prova = prova;
	}

	public Map<String, Integer> getClassificacao() {
		return this.classificacao;
	}

	public Map<String, Participante> getListaPart(){
		return this.participantes;
	}

	public void setListaPart(Map<String, Participante> listaP){
		this.participantes = listaP;
	}

	public ArrayList<Circuito> getCircuitos(){
		return this.circuitos;
	}

	public void setCircuitos(ArrayList<Circuito> lcir){
		this.circuitos = lcir;
	}

	public Participante getParticipante(String part){
		return this.participantes.get(part);
	}

	public Map<Corrida,Boolean> getCorridas()
	{
		return this.corridas;
	}

	public void setCorridas(Map<Corrida,Boolean> lcorr)
	{
		this.corridas = lcorr;
	}
	/**
	 *
	 */
	public void addParticipante(Participante participante) {
		String nomeU = participante.getUtilizador().getUser();
		System.out.println(nomeU);
		this.participantes.put(nomeU, participante);
		this.classificacao.put(nomeU,0);
	}

	/**
	 * incrementa a cada prova realizada (aponta para a prova a realizar)
	 */
	public Campeonato() {
	}

	/**
	 * 
	 * @param circuitos os circuitos a utilizar neste campeonato
	 * @param prova nome do campeonato
	 */
	public Campeonato(ArrayList<Circuito> circuitos, String prova) {
		this.circuitos = circuitos;
		this.prova = prova;
		this.participantes = new HashMap<String,Participante>();
		this.classificacao = new HashMap<String,Integer>();	
		this.numCorrida = 0;
		this.corridas = new HashMap<Corrida,Boolean>();	
	}

	public Campeonato(String prova, ArrayList<Circuito> circuitos, Map<String, Participante> participantes, Map<String, Integer> classificacao, int numCorrida, Map<Corrida,Boolean> corridas) {
		this.prova = prova;
		this.circuitos = circuitos;
		this.participantes = participantes;
		this.classificacao = classificacao;
		this.numCorrida = numCorrida;
		this.corridas = corridas;
	}

	//alterar para copiar listas valor a valor
	public Campeonato(Campeonato c) {
		this.circuitos = c.circuitos;
		this.corridas = c.corridas;
		this.classificacao = c.classificacao;
		this.corridas = c.corridas;
		this.numCorrida = c.numCorrida;
		this.participantes = c.participantes;
		this.prova = c.prova;
	}

	@Override
	public Campeonato clone(){
		return new Campeonato(this);
	}

	public String toString()
	{
		String s1 = "==PARTICIPANTE(S)==\n";
		String s2 = "==CIRCUITO(S)==\n";
		for(Map.Entry<String,Participante> pair : participantes.entrySet())
			s1+=pair.getValue().toString();
		for(Circuito c : circuitos)
			s2+=c.toString();
		
		return (s1 + s2);
	}	

	/**
	 * Adicionar corrida ao campeonato
	 * @param c circuito a adicionar
	 */
	public void addCircuito(Circuito c) {
		circuitos.add(c.clone());
	} 

	/**
	 * Atualizar classificacao campeonato
	 */
	public void atualizarClassificacao(List<Participante> participantes){
		int max = 12;
		for(Participante p : participantes){
			int points = this.classificacao.get(p.getUtilizador().getUser());
			int pos = p.getPosicao();
			switch(pos){
				case 0:
					points +=0;
					break;
				case 1:
					points += max;
					break;
				case 2:
					points += max-2;
					break;
				default:
					points += max -(pos+1);
			}
		 this.classificacao.replace(p.getUtilizador().getUser(), points);
		}
	}

	public String simulaProximaCorrida(Circuito cir){
		List<Participante> part = new ArrayList<Participante>();
		int i = 1;
		for(Participante p : this.participantes.values()){
			p.setPosicao(i);
			part.add(p);
			i++;
		}
		Corrida corrida = new Corrida(cir, 2, part);
		List<Participante> listaPart = corrida.simulaCorrida();
		atualizarClassificacao(listaPart);
		ArrayList<Map.Entry<String, Integer>> camp = ordenaClassificacao(this.classificacao);
		String strClassificacoes = "";
		int lugar = 0;
		for(Map.Entry<String, Integer> entry : camp){
			lugar++;
			String str =entry.getKey()+ " lugar->" + lugar + "º | pontos-> " + entry.getValue() +  "\n";
			strClassificacoes += str; 
		}
		return strClassificacoes;
	}

	public String separaClassificacoes(ArrayList<Map.Entry<String, Integer>> classificacoes){
		String c1 = "";
		String c2 = "";
		String gt = "";
		String sc = "";
		for(Map.Entry<String, Integer> entry : classificacoes){
			Participante p = participantes.get(entry.getKey());
			Carro carro = p.getCarro();
			if(carro instanceof C1H){
				c1 += "valor";
			} else if (carro instanceof C2H){
				c2 += "valor";
			} else if (carro instanceof GTH){
				gt += "valor";
			} else if (carro instanceof C1){
				c1 += "valor";
			} else if (carro instanceof C2){
				c2 += "valor";
			} else if (carro instanceof GT){
				gt += "valor";
			} else if (carro instanceof SC){
				sc += "valor";
			}
		}
		String result = "C1: \n" + c1 + "C2: \n" + c2 + "GT: \n" + gt + "SC: \n" + sc;
		return result;
	}

	public ArrayList<Map.Entry<String, Integer>> ordenaClassificacao(Map<String, Integer> classificacao) {
		ArrayList<Map.Entry<String, Integer>> lista = new ArrayList<Map.Entry<String, Integer>>();
		for (String key : classificacao.keySet()) {
			Map.Entry<String,Integer> entry = new AbstractMap.SimpleEntry<String, Integer>(key, classificacao.get(key));
			lista.add(entry);
		}
		Collections.sort(lista, new StockComparator());
		return lista;
}


class StockComparator implements Comparator<Map.Entry<String, Integer>> {
	@Override
	public int compare(Map.Entry<String, Integer> p1, Map.Entry<String, Integer> p2)
	{
		if (p1.getValue() == p2.getValue())
		return 0;
		else if (p1.getValue() < p2.getValue()) // se p1 tiver menos pontos que p2
		return 1;
		else
		return -1;
	}
}
}