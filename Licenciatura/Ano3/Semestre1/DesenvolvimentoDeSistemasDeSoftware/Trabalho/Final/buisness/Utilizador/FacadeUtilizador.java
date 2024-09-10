package buisness.Utilizador;

import java.util.HashMap;
import java.util.Map;

import data.UtilizadorDAO;

public class FacadeUtilizador implements IFacadeUtilizador {

	private HashMap<String,Convidado> mapConvidados = new HashMap<String,Convidado>(); //chave -> ("Convidado " + nº)
	private Map<String,Utilizador> mapUtilizadores = UtilizadorDAO.getInstance();

	public Map<String,Utilizador> getMapUtil()
	{
		return this.mapUtilizadores;
	}
	public HashMap<String,Convidado> getMapConvidados()
	{
		return this.mapConvidados;
	}

	//login devolve um utilizador(jogador/admin) a partir de um par username/password.
	//NULL -> email e password nao condizem
	//excecao -> username nao existe
	//Utilizador -> sucesso
	public Utilizador Login(String username, String password) throws UtilizadorInvalido
	{
		if(!this.getMapUtil().containsKey(username))
			throw new UtilizadorInvalido("Username nao existe, por favor registe-se.");
		else if(password.length()<8)
			throw new UtilizadorInvalido("Password demasiado curta.");
		else
		{
			if(this.getMapUtil().containsKey(username))
			{
				if(username.equals("admin")){
					String pw = ((Administrador) this.getMapUtil().get(username)).getPassword();
					return (pw.equals(password) ? this.getMapUtil().get(username) : null);
				}
				String pw = ((Jogador) this.getMapUtil().get(username)).getPassword();
				return (pw.equals(password) ? this.getMapUtil().get(username) : null);
			}
		}
		return null;
	}

	//login como convidado resulta sempre.
	public Convidado LoginConvidado()
	{
		String nome_convidado = "Convidado " + (this.getMapConvidados().size()+1);
		Convidado c = new Convidado (nome_convidado);
		this.getMapConvidados().put(nome_convidado, new Convidado (nome_convidado));
		return c;
	}

	//se nao acontece nada o registo teve sucesso. Se ocorreu a excecao, registo falhou.
	public void Registo(String username, String password, boolean isPremium) throws UtilizadorInvalido
	{
		if (this.getMapUtil().containsKey(username))
			throw new UtilizadorInvalido("Username já existe.");
		if(password.length() < 8)
			throw new UtilizadorInvalido("Password demasiado curta.");
		this.getMapUtil().put(username, new Jogador(username, password, 0, isPremium));
		return;
		
	}

	//funcao que usamos para adicionar os admins (hard coded), os utilizadores normais 
	//nao devem ter acesso a esta funcao
	public void RegistoAdmin(String username, String password) throws UtilizadorInvalido
	{
		if(this.getMapUtil().containsKey(username))
			throw new UtilizadorInvalido("Erro no registo, user já existe");
		else if(password.length() < 8)
			throw new UtilizadorInvalido("Password demasiado curta");
		else
			this.getMapUtil().put(username, new Administrador(username,password));

	}

	//funcoes que cada user tem



}