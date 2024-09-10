package buisness.Carro;

public class GT extends Carro {


	
	private float taxa_fiabilidade; // valor baixo que é subtraído à fiabilidade com o desenrolar da corrida. Calculado quando o carro é construido

	public GT()
	{
	super();
	}

	public GT(String a_marca, String o_modelo, int a_cilindrada, int a_potencia, float a_fiabilidade,float o_pa, estadoMotor o_estado, tipoPneu os_pneus,float a_downforce,float a_taxa) {
		super(a_marca,o_modelo,a_cilindrada,a_potencia,a_fiabilidade,o_pa,o_estado,os_pneus,a_downforce);
		this.taxa_fiabilidade = a_taxa;
	}


	//construtor dos GT usado para os campeonatos
	public GT(String a_marca, String o_modelo, int a_cilindrada, int a_potencia,float o_pa) throws CarroInvalido
	{
		
		super(a_marca,o_modelo,a_cilindrada,a_potencia,o_pa);

		if(a_cilindrada <2000 || a_cilindrada > 4000 || a_potencia < 300 || a_potencia > 800 || o_pa < 0f || o_pa > 1.00f)
			throw new CarroInvalido("Valores inválidos inseridos...");

		//taxa de fiabilidade entre 0.05 e 0.075
		// 			vvvvvv
		this.setTaxa_fiabilidade(
			(float)(0.0375 - (a_cilindrada - 4000) * (0.0375 - 0.025) / (2000 - 4000)) + 
			(float)(0.025 + (a_potencia - 300) * (0.0375 - 0.025) / (800 - 300))
		);
		this.setTaxa_fiabilidade(this.getTaxa_fiabilidade() / 10);

		//fiabilidade começa a 0.75, dependendo do numero de voltas(no campeonato) e da taxa vai diminuindo
		// 		  vvvvvv
		this.setFiabilidade(0.75f);
		
		this.setEstado(estadoMotor.NULL);
		this.setPneus(tipoPneu.NULL);

	}

	public float getTaxa_fiabilidade(){
		return this.taxa_fiabilidade;
	}

	public void setTaxa_fiabilidade(float uma_taxa){
		this.taxa_fiabilidade = uma_taxa;
	}

	public GT(GT p) {
		super(p.getMarca(),p.getModelo(),p.getCilindrada(),p.getPotencia(),p.getFiabilidade(),p.getPa(),p.getEstado(),p.getPneus(),p.getDownforce());
		this.taxa_fiabilidade = p.getTaxa_fiabilidade();
	}
	@Override
	public String toString(){
		return (super.toString() + "Taxa de Fiabilidade: " + this.getTaxa_fiabilidade() + "\n");
	}
	@Override
	public GT clone() {
		return new GT(this);
	}

	@Override
	public boolean equals(Object o) {
	   if(this == o) 
       	return true;
       if(o == null || o.getClass() != this.getClass())
       	return false;
		GT c = (GT) o;
		return (super.equals(o) && this.getTaxa_fiabilidade() == c.getTaxa_fiabilidade());
	}

}