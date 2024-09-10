
package buisness.Racing;
import java.util.*;;
public interface IFacadeCorrida {

    public boolean addCircuito(String nome, int dist, int voltas, int n_retas, int n_chicanes);
    public boolean insertCampeonato(ArrayList<Circuito> listaCircuitos, String nomeProva);
    public void startCampeonato(Campeonato c);
    public Piloto findPiloto(String nome);
    public String listaPilotosStr();
    public String listaCircuitoString();
    public String listaCampeonatosString();
    public String listaLobbiesString();
    public String simularProximaCorrida(String nome_campeonato);
}