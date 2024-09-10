package buisness.Racing;
import java.io.*;
import java.util.ArrayList;
import buisness.Carro.*;


public class Circuito implements Serializable {

	private String nome;
	private int distancia;
	private int voltas;
	private ArrayList<Seccao> listaSeccoes;

	public String getNome() {
		return this.nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public int getDistancia() {
		return this.distancia;
	}

	public void setDistancia(int distancia) {
		this.distancia = distancia;
	}

	public int getVoltas() {
		return this.voltas;
	}

	public void setVoltas(int voltas) {
		this.voltas = voltas;
	}

	public void setListaSeccoes(ArrayList<Seccao> listaSeccoes) {
		this.listaSeccoes = listaSeccoes;
	}

	public ArrayList<Seccao> getListaSeccoes() {
		return this.listaSeccoes;
	}

	public Circuito() {
		this.nome = "";
		this.distancia = 0;
		this.voltas = 0;
		this.listaSeccoes = new ArrayList<>();
	}

	public Circuito(String nome, int distancia, int voltas, ArrayList<Seccao> listaSeccoes) {
		this.nome = nome;
		this.distancia = distancia;
		this.voltas = voltas;
		this.listaSeccoes = new ArrayList<>();
		for (Seccao seccao : listaSeccoes) {
			this.listaSeccoes.add(seccao.clone());
		}
	}

	public Circuito(Circuito c) {
		this.nome = c.getNome();
		this.distancia = c.getDistancia();
		this.voltas = c.getVoltas();
		for (Seccao s : c.getListaSeccoes()) {
			this.listaSeccoes.add(s.clone());
		}
	}

	public void createCircuito(String nome, int dist, int voltas, int n_retas, int n_chicanes) {
		this.setNome(nome);
		this.setDistancia(dist);
		this.setVoltas(voltas);
		int curvas = (n_retas + n_chicanes) / 2;
		for (int i = 0; i < n_retas ; i++) {
			this.getListaSeccoes().add(new Seccao(1));
		}
		for (int i = 0; i < curvas ; i++) {
			this.getListaSeccoes().add(new Seccao(0));
		}
		for (int i = 0; i < n_chicanes ; i++) {
			this.getListaSeccoes().add(new Seccao(2));
		}
	}

	public Circuito clone() {
		return new Circuito(this);
	}
	
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("Nome: ").append(this.nome).append("\n");
		sb.append("Distancia: ").append(this.distancia).append("\n");
		sb.append("Voltas: ").append(this.voltas).append("\n");
		sb.append("Seccoes: ").append(this.listaSeccoes).append("\n");
		return sb.toString();
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;

		Circuito circuito = (Circuito) o;

		return this.getNome().equals(circuito.getNome());
	}

}