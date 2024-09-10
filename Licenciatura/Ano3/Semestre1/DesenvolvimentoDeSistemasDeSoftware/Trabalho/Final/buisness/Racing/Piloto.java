package buisness.Racing;
import java.io.*;
import buisness.Carro.*;

public class Piloto implements Serializable {

	/**
	 * Variaveis de instancia
	 */
	private String nome;
	private float chuvaVSseco;
	private float agressividade;

	public String getNome() {
		return this.nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public float getAgressividade() {
		return this.agressividade;
	}

	public void setAgressividade(float agressividade) {
		this.agressividade = agressividade;
	}

	public float getChuvaVSseco() {
		return this.chuvaVSseco;
	}

	public void setChuvaVSseco(float chuvaVSseco) {
		this.chuvaVSseco = chuvaVSseco;
	}

	public Piloto() {
		this.nome = "";
		this.agressividade = 0.5f;
		this.chuvaVSseco = 0.5f;
	}
	
	public Piloto(String nome, float chuvaVSseco, float agressividade) {
		this.nome = nome;
		this.chuvaVSseco = chuvaVSseco;
		this.agressividade = agressividade;
	}
	
	public Piloto(Piloto p) {
		this.nome = p.getNome();
		this.chuvaVSseco = p.getChuvaVSseco();
		this.agressividade = p.getAgressividade();
	}
	
	public String toString() {
		return ("===PILOTO===\nNome: " + this.getNome() + "\nAgressividade: " + this.getAgressividade()
									   + "\nChuva vs Tempo Seco: " + this.getChuvaVSseco() +"\n");
	}

	public Piloto clone() {
		return new Piloto(this);
	}

	public boolean equals(Object o) {
		if(this == o) return true;
		if(o == null || o.getClass() != this.getClass()) return false;

		Piloto p = (Piloto) o;
		return(this.nome.equals(p.getNome()) && this.getAgressividade() == (p.getAgressividade())
											 && this.getChuvaVSseco() == p.getChuvaVSseco());
	}

}