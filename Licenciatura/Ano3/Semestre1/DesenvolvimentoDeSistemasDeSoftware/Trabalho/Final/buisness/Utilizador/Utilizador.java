package buisness.Utilizador;

public abstract class Utilizador {

	private String user;
	
	public String getUser() {
		return this.user;
	}

	public void setUser(String user) {
		this.user = user;
	}

	public Utilizador(String user) {
			this.user = user;
	}

	public Utilizador()
	{
		this.user = "";
	}

	public Utilizador(Utilizador u) {
		this.user = u.getUser();
	}


	public String toString() {
		return ("Username: " + this.getUser());
	}

	public boolean equals(Object o) {
		if (this == o) return true;
		if(o == null || this.getClass() != o.getClass()) return false;
		Utilizador u = (Utilizador) o;
		return(this.getUser().equals(u.getUser()));
	}

}