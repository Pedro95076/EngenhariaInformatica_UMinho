package buisness.Racing;

import java.util.Random;
import buisness.Carro.*;

public class Seccao {

	private static final int CURVA = 0;
	private static final int RETA = 1;
	private static final int SHICANE = 2;

	private static final int IMPOSSIVEL = 3;
	private static final int POSSIVEL = 4;
	private static final int DIFICIL = 5;

	private int tipo;
	private int gdu;

	public int getGDU() {
		return this.gdu;
	}

	public void setGDU(int gdu) {
		this.gdu = gdu;
	}

	public int getTipo() {
		return this.tipo;
	}

	public void setTipo(int tipo) {
		this.tipo = tipo;
	}

	public Seccao(int tipo) {

		this.tipo = tipo;
		this.gdu = new Random().nextInt(3);
	}

	public Seccao(int tipo, int gdu) {
		this.tipo = tipo;
		this.gdu = gdu;
	}

	public Seccao(Seccao seccao) {
		this.tipo = seccao.getTipo();
		this.gdu = seccao.getGDU();
	}

	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("Tipo: ");
		switch (this.tipo) {
		case 0:
			sb.append("Curva");
			break;
		case 1:
			sb.append("Reta");
			break;
		case 2:
			sb.append("Shicane");
			break;
		}
		sb.append(" GDU: ");
		sb.append(this.gdu);
		return sb.toString();
	}

	@Override
	public boolean equals(Object o) {
		if (o == this)
			return true;
		if (o == null || o.getClass() != this.getClass())
			return false;
		Seccao s = (Seccao) o;
		return s.getTipo() == this.tipo && s.getGDU() == this.gdu;
	}

	public Seccao clone()
	{
		return new Seccao(this);
	}

}