package buisness.Carro;

public class C2H extends C2 {

	private int motor_eletrico;
	
	public C2H()
	{
	super();
	this.motor_eletrico = 0;
	}

	public C2H(String a_marca, String o_modelo, int a_cilindrada, int a_potencia, float a_fiabilidade,float o_pa, estadoMotor o_estado, tipoPneu os_pneus,float a_downforce, float a_afinacao, int o_motor_eletrico) {
		super(a_marca,o_modelo,a_cilindrada,a_potencia,a_fiabilidade,o_pa,o_estado,os_pneus,a_downforce,a_afinacao);
		this.motor_eletrico = o_motor_eletrico;
	}

	public C2H(String a_marca, String o_modelo, int a_cilindrada, int a_potencia,float o_pa, int o_motorE) throws CarroInvalido
	{
		super(a_marca,o_modelo,a_cilindrada,a_potencia,o_pa);
		if(o_motorE < 50 || o_motorE > 150)
		throw new CarroInvalido("Valores incorretos inseridos...");
	 
	 //penalidade de fiabilidade entre 0.05 e 0.15
	 this.setFiabilidade(this.getFiabilidade() - (float)(0.001 * o_motorE));
	 this.motor_eletrico = o_motorE;
	}

	public int getMotorEletrico()
	{
		return this.motor_eletrico;
	}

	public void setMotorEletrico(int o_motor)
	{
		this.motor_eletrico = o_motor;
	}
	
	public C2H(C2H p) {
		super(p.getMarca(),p.getModelo(),p.getCilindrada(),p.getPotencia(),p.getFiabilidade(),p.getPa(),p.getEstado(),p.getPneus(),p.getDownforce(),p.getAfinacao());
		this.motor_eletrico = p.getMotorEletrico();
	}
	@Override
	public String toString()
	{
		String s =  super.toString();
		return(s + "Motor Eletrico: " + this.getMotorEletrico() + "\n" );
	}
	@Override
	public C2H clone() {
		return new C2H(this);
	}

	@Override
	public boolean equals(Object o) {
	   if(this == o) 
       	return true;
       if(o == null || o.getClass() != this.getClass())
       	return false;
		C2H c = (C2H) o;
		return (c.getMotorEletrico() == this.getMotorEletrico() && super.equals(o));
	}

}