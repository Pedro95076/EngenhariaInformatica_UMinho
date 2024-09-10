package buisness.Utilizador;

public class Jogador extends Utilizador implements Comparable<Jogador> {

	private String password;
	private int points;
	private boolean isPremium;

	public int getPoints() {
		return this.points;
	}

	public void setPoints(int points) {
		this.points = points;
	}

	public String getPassword() {
		return this.password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public boolean getIsPremium() {
		return this.isPremium;
	}

	public void setIsPremium(boolean isPremium) {
		this.isPremium = isPremium;
	}

	public Jogador(String user,String password, int pontos, boolean premium) {
		super(user);
		this.password = password;
		this.points = pontos;
		this.isPremium = premium;
	}

	public Jogador(Jogador j) {
		super(j.getUser());
		this.password = j.getPassword();
		this.points = j.getPoints();
		this.isPremium = j.getIsPremium();
	}

	public String toString()
	{
		return("====JOGADOR====\n" + super.toString() + "\nPassword: " + this.getPassword() + "\nPontos: " + this.getPoints()
								+ "\nPremium: " + (this.getIsPremium() ? "SIM\n" : "NAO\n"));
	}

	public Jogador clone() {
		return new Jogador(this);
	}
	
	public int compareTo(Jogador j)
	{
		int myPoints = this.getPoints();
		int theirPoints = j.getPoints();

		if(myPoints != theirPoints)
			return(myPoints - theirPoints); //ordenar por pontos
		else 
			return this.getUser().compareTo(j.getUser()); //ordenar por username se pontos forem iguais

	}
}