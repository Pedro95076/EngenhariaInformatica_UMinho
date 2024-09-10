package buisness.Carro;
public class C1 extends Carro {
	
	//aproximadamente 95% fiabilidade
	public C1()
	{
	super();
	}


	public C1(String a_marca, String o_modelo, int a_cilindrada, int a_potencia, float a_fiabilidade,float o_pa, estadoMotor o_estado, tipoPneu os_pneus, float a_downforce) {
		super(a_marca,o_modelo,a_cilindrada,a_potencia,a_fiabilidade,o_pa,o_estado,os_pneus,a_downforce);
	}


	public C1(String a_marca, String o_modelo, int a_cilindrada, int a_potencia,float o_pa) throws CarroInvalido
	{
		
		super(a_marca,o_modelo,a_cilindrada,a_potencia,o_pa);

		if(a_cilindrada != 6000 || a_potencia < 300 || a_potencia > 1000 || o_pa < 0f || o_pa > 1.00f)
			throw new CarroInvalido("Valores inválidos inseridos...");
		
		//fiabilidade entre 0.93 e 0.97
		// 		  vvvvvv
		this.setFiabilidade(1.0f - (0.000076f*a_potencia));
		this.setEstado(estadoMotor.NULL);
		this.setPneus(tipoPneu.NULL);

	}

	public C1(C1 p) {
		super(p.getMarca(),p.getModelo(),p.getCilindrada(),p.getPotencia(),p.getFiabilidade(),p.getPa(),p.getEstado(),p.getPneus(),p.getDownforce());
	}
	
	@Override
	public String toString()
	{
		return super.toString();
	}

	@Override
	public C1 clone() {
		return new C1(this);
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