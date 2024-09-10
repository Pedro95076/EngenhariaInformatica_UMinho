package buisness.Carro;

public class SC extends Carro {

	//FIABILIDADE DO SC -> 75% CARRO(48.5%<fiabilidade_carro<60%) + 25% PILOTO(16.25%<fiabilidade_piloto<20%)
	//FIABILIDADE TOTAL DO SC -> Entre 65% e 80%

	public SC()
	{
	super();
	}

	public SC(String a_marca, String o_modelo, int a_cilindrada, int a_potencia, float a_fiabilidade,float o_pa, estadoMotor o_estado, tipoPneu os_pneus,float a_downforce) {
		super(a_marca,o_modelo,a_cilindrada,a_potencia,a_fiabilidade,o_pa,o_estado,os_pneus,a_downforce);
	}

	//construtor default dos SCs, para usar em campeonato
	public SC(String a_marca, String o_modelo, int a_cilindrada, int a_potencia,float o_pa) throws CarroInvalido
	{
		super(a_marca,o_modelo,a_cilindrada,a_potencia,o_pa);

		if(a_cilindrada != 2500|| a_potencia < 100 || a_potencia > 600 || o_pa < 0f || o_pa > 1.00f)
			throw new CarroInvalido("Valores inválidos inseridos...");
		
		//fiabilidade começa a um valor entre 20 e 30%. Depois quando o piloto for escolhido, aumenta 50-60%
		//dependendo do tipo de piloto escolhido
		// 	    vvvvvv
		this.setFiabilidade(0.25f + (float)(-0.05 + (0.1 * (a_potencia - 100)) / 500));
		this.setEstado(estadoMotor.NULL);
		this.setPneus(tipoPneu.NULL);

	}
	
	public SC(SC p) {
		super(p.getMarca(),p.getModelo(),p.getCilindrada(),p.getPotencia(),p.getFiabilidade(),p.getPa(),p.getEstado(),p.getPneus(),p.getDownforce());
	}
	@Override
	public String toString()
	{
		return super.toString();
	}
	@Override
	public SC clone() {
		return new SC(this);
	}

	@Override
	public boolean equals(Object o) {
	   if(this == o) 
       	return true;
       if(o == null || o.getClass() != this.getClass())
       	return false;
		
		return super.equals(o);
	}

}