package buisness.Racing;

import java.util.*;
import buisness.Carro.*;
import data.CircuitoDAO;
import data.PilotoDAO;
public class FacadeCorrida implements IFacadeCorrida {

	private HashMap<String, Campeonato> mapCampeonatos = new HashMap<String, Campeonato>(); // "campeonato1" -> c1
	private HashMap<Integer, Campeonato> mapLobbys = new HashMap<Integer, Campeonato>();  // 1 -> c1
	private Map<String, Piloto> mapPilotos = PilotoDAO.getInstance();
	private HashMap<String, Participante> mapParticipantes = new HashMap<String, Participante>();
	private Map<String, Circuito> mapCircuitos = CircuitoDAO.getInstance();
	private HashMap<String, Seccao> mapSeccoes = new HashMap<String, Seccao>();



	public HashMap<String, Campeonato> getMapCampeonatos() {
		return this.mapCampeonatos;
	}

	public HashMap<Integer, Campeonato> getMapLobbys() {
		return this.mapLobbys;
	}

	public Map<String, Piloto> getMapPilotos() {
		return this.mapPilotos;
	}

	HashMap<String, Participante> getMapParticipantes() {
		return this.mapParticipantes;
	}

	public HashMap<String, Seccao> getMapSeccoes() {
		return this.mapSeccoes;
	}

	public Map<String, Circuito> getMapCircuitos() {
		return this.mapCircuitos;
	}


	//funcao exclusiva do admin
	public boolean insertCampeonato(ArrayList<Circuito> listaCircuitos, String nomeProva) {
		if (this.mapCampeonatos.containsKey(nomeProva))
			return false;// incapaz de criar um novo campeonato pois este já existe
		else {
			Campeonato campeonato = new Campeonato(listaCircuitos, nomeProva);
			this.mapCampeonatos.put(nomeProva, campeonato);
			return true;// campeonato criado com sucesso
		}
	}


	//para que é que isto serve???? - Eduardo
	public boolean addCircuito(String nome, int dist, int voltas, int n_retas, int n_chicanes) {
		return true;
	}

	public void startCampeonato(Campeonato c) {
		ArrayList<Participante> participantes = new ArrayList<>(c.getListaPart().values());
		for (Circuito circ : c.getCircuitos()) {
			Corrida corr = new Corrida(circ.clone(), (int) Math.round(Math.random()), participantes);
			c.getCorridas().put(corr, false);
		}
		//simulacao
		System.out.println(simularProximaCorrida(c.getProva()));
		//reset ao campeonato
		c.setListaPart(new HashMap<String, Participante>()); //ja nao ha participantres
		c.setCorridas(new HashMap<Corrida, Boolean>()); // ja nao ha corridas
	}


	public Piloto findPiloto(String nome) {
		if (!mapPilotos.containsKey(nome)) return null;
		return mapPilotos.get(nome).clone();
	}

	public String listaPilotosStr() {
		String s = "Pilotos:\n";
		for (Map.Entry<String, Piloto> pair : mapPilotos.entrySet())
			s += pair.getValue().toString();
		return s;

	}
	public String listaCircuitoString()
	{
		String c = "Circuitos:\n";
		for (Map.Entry<String, Circuito> pair : mapCircuitos.entrySet())
		{
			c+=pair.getValue().toString();
		}
		return c;
	}

	public String listaCampeonatosString()
	{
		String camp = "==Campeonatos:==\n";
		for (Map.Entry<String,Campeonato> pair: mapCampeonatos.entrySet())
		{
			camp += ("Nome->: " + pair.getValue().getProva() + "\nCircuitos");
			for (Circuito c : pair.getValue().getCircuitos())
				camp += c.toString();
		}
		return camp;
	}

	public String listaLobbiesString()
	{
		String camp = "";
		for (Map.Entry<Integer,Campeonato> pair: mapLobbys.entrySet())
		{
			camp += ("ID lobbie->: " + pair.getKey() + "Campeonato" + pair.getValue());
		}
		return camp;
	}



	public String simularProximaCorrida(String nome_campeonato) {
	String resultado_corrida = null;
	Campeonato camp = this.mapCampeonatos.get(nome_campeonato);
	for (Map.Entry<Corrida, Boolean> pair : camp.getCorridas().entrySet())
		if (!pair.getValue()) {
			resultado_corrida = camp.simulaProximaCorrida(pair.getKey().getCiruito());
			pair.setValue(false);
			break;
		}
		return resultado_corrida;
	}

}