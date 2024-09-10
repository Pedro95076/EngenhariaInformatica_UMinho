package buisness;

import java.util.*;

public interface IRacingSimFacade {

	//=====ADMIN=====
	

	public String addCircuito(String nome, int dist, int voltas, int n_retas, int n_chicanes); //admin
	public String addCampeonato(ArrayList<String> circuitos, String nomeProva); //admin
	public String addCarro(int tipo, String marca, String modelo, int cilindrada, int potencia, float pa); //admin
	public String addCarrohibridro(int tipo, String marca, String modelo,int cilindrada, int potencia, float pa, int potenciaE); //admin
	public String addPiloto(String nome, float chuvaVSseco, float  agressividade); //admin


	public String editCarro(String modelo,int opt, int value); //admin
	public String editCampeonato(int opt, String nome_campeonato, List<String> circuitos); //admin
	public String editCircuito(String nome_circuito, int n_voltas); //admin
	public String editPiloto(String nome_piloto,int opt, float valor); //admin


	public String delCircuito(String nome_circuito); //admin
	public String delCampeonato(String nome_campeonato); //admin
	public String delCarro(String nome_carro); //admin
	public String delPiloto(String nome_piloto); //admin

	//=====GLOBAL=====

	public boolean existeCarro(String modelo); //user
	public boolean existePiloto(String nomePiloto); //user
	public boolean existeCircuito(String nomeCircuito); //user
	public boolean existeCampeonato(String nomeCampeonato); //user

	//===JOGADORES/CONVIDADOS(LOBBYS E SIMULACOES)====

	public int criarLobby(String nomeCampeonato); //jogador ou convidado(host)
	public String lobbyToString(int num_lobby); 
	public String joinLobby(int num_lobby, String modelo_carro, String nome_piloto); //jogador ou convidado
	public String startLobby(int num_lobby); //jogador ou convidado(host)
	public String proximaCorrida(int num_lobby); //jogador ou convidado(host)

	public String getTipoCarro(int num_lobby); //jogador ou convidado
	public String customizarCarro(int num_lobby, String tipo_carro, String estado_motor, String tipo_pneu,
								  float downforce, float afinacao); //jogador ou convidado



	public String mostrar_pontos(); //jogador
	public String loginConvidado(); //convidado
	public int login(String user, String password); //user
	public String registo(String user,String password); //jogador 
	//public String registoAdmin(String user, String password); //nao na Interface, admins sao adicionados por nos ("hard coded") 
}