package buisness.Utilizador;

public class UtilizadorInvalido extends Exception{

      public UtilizadorInvalido() {
		super();
	}

    public UtilizadorInvalido(String mensagem) {
		super(mensagem);
	}
}
