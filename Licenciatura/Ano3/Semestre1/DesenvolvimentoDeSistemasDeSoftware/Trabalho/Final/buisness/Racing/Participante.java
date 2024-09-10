
package buisness.Racing;
import buisness.Carro.*;
import buisness.Utilizador.*;

public class Participante {

	private int posicao;
	private Piloto piloto;
	private Carro carro;
	private Utilizador user;
	private float timeDiff;
	
	public int getPosicao() {
		return this.posicao;
	}

	public void setPosicao(int posicao) {
		this.posicao = posicao;
	}

	public Utilizador getUtilizador(){
		return this.user;
	}

	public void setUtilizador(Utilizador user) throws ErroCampeonato {
		if(user instanceof Convidado)
				this.user = ((Convidado) user).clone();
		else if(user instanceof Jogador)
				this.user = ((Jogador) user).clone();
		else
			throw new ErroCampeonato("Administradores não podem participar em campeonatos...");
	}

	public Piloto getpiloto() {
		return this.piloto;
	}

	public void setPiloto(Piloto piloto) {
		this.piloto = piloto;
	}

	public Carro getCarro(){
		return this.carro;
	}

	public void setCarro(Carro carro) {
		this.carro= carro;
	}

	public float getTimeDiff(){
		return this.timeDiff;
	}

	public void setTimeDiff(float timeDiff){
		this.timeDiff=timeDiff;
	}

	public Participante() {
		this.user = null;
		this.piloto = null;
		this.carro = null;	
	}

	public Participante(Utilizador user, Piloto piloto, Carro carro) {
		this.user = user;
		this.piloto = piloto;
		this.carro = carro;
		if(carro.getClass().getSimpleName().equals("SC"))
		{
			float fiabilidade_piloto = 0.6f - (float)(0.1 * piloto.getAgressividade());
			carro.setFiabilidade(carro.getFiabilidade() + fiabilidade_piloto);
		}
		this.timeDiff = 0f;
		this.posicao = 1 + (int)(Math.random() * ((8 - 1) + 1)); // numero aleatorio entre 1 e 8
		
	}

	public Participante(int posicao, Piloto piloto, Carro carro, Utilizador user, float timeDiff) {
		this.posicao = posicao;
		this.piloto = piloto;
		this.carro = carro;
		this.user = user;
		this.timeDiff = timeDiff;
	}

	@Override
	public boolean equals(Object obj){
		if(this == obj)
			return true;
		if(obj == null || obj.getClass()!=this.getClass())
			return false;
		Participante p = (Participante) obj;
		return this.getUtilizador().getUser().equals(p.getUtilizador().getUser());
	}
	public String toString()
	{
		return ("===PARTICIPANTE===\n" + this.user.toString() + this.piloto.toString() + this.carro.toString());
	}



}