package buisness.Utilizador;

public class Administrador extends Utilizador {

	private String password;

	public Administrador(String n, String pass) {
		super(n);
		this.password = pass;
	}

	public Administrador(Administrador a) {
		super(a);
		this.password = a.getPassword();
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getPassword() {
		return this.password;
	}

	public Administrador clone() {
		return new Administrador(this);
	}

}