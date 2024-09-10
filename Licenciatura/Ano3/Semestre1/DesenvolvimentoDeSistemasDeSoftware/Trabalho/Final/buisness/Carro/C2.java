package buisness.Carro;
public class C2 extends Carro {

	private float afinacao = 0.5f;
	//aproximadamente 80% fiabilidade c/ downforce 0.5(NEUTRA)

	public float getAfinacao()
	{
		return this.afinacao;
	}

	//+ afinacao-> + potencia, - fiabilidade

	public void setAfinacao(float a_afinacao)
	{
		if(a_afinacao < 0f)
			this.afinacao = 0f;
		if(a_afinacao > 1f)
			this.afinacao = 1f;
		else
			this.afinacao = a_afinacao;
	}

	public C2()
	{
	super();
	this.afinacao = 0.5f;
	}

	public C2(String a_marca, String o_modelo, int a_cilindrada, int a_potencia, float a_fiabilidade,float o_pa, estadoMotor o_estado, tipoPneu os_pneus,float a_downforce,float a_afinacao) {
		super(a_marca,o_modelo,a_cilindrada,a_potencia,a_fiabilidade,o_pa,o_estado,os_pneus,a_downforce);
		this.afinacao = a_afinacao;
	}
	
	//Construtor default, a downforce fica sempre neutra até o carro ser selecionado para o campeonato.
	public C2(String a_marca, String o_modelo, int a_cilindrada, int a_potencia,float o_pa) throws CarroInvalido
	{
		super(a_marca,o_modelo,a_cilindrada,a_potencia,o_pa);
		if(a_cilindrada <3000 || a_cilindrada > 5000 || a_potencia < 300 || a_potencia > 900 || o_pa < 0f || o_pa > 1.00f)
			throw new CarroInvalido("Valores inválidos inseridos...");
		
		//fiabilidade entre 0.75 e 0.85
		//    vvvvvvv	
		this.setFiabilidade(0.85f - (float)(0.05 * (a_potencia - 300) / 600) - (float)(0.05 * (5000 - a_cilindrada) / 2000) );	
		this.setPneus(tipoPneu.NULL);
		this.setEstado(estadoMotor.NULL);
		this.setAfinacao(0.5f);

	}
	


	public C2(C2 p) {
		super(p.getMarca(),p.getModelo(),p.getCilindrada(),p.getPotencia(),p.getFiabilidade(),p.getPa(),p.getEstado(),p.getPneus(),p.getDownforce());
	}
	@Override
	public String toString()
	{
		return (super.toString() + "Afinacao: " + this.afinacao + "\n");
	}
	@Override
	public C2 clone() {
		return new C2(this);
	}

	@Override
	public boolean equals(Object o) {
	   if(this == o) 
       	return true;
       if(o == null || o.getClass() != this.getClass())
       	return false;
		return (super.equals(o));
	}

}