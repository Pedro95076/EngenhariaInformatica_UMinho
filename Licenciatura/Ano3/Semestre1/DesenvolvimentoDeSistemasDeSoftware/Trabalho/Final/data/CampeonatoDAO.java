package data;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.AbstractMap;
import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.List;


import buisness.Carro.Carro;
import buisness.Racing.Campeonato;
import buisness.Racing.Circuito;
import buisness.Racing.Corrida;
import buisness.Racing.Participante;
import buisness.Racing.Piloto;
import buisness.Utilizador.Utilizador;

public class CampeonatoDAO implements Map<String, Campeonato> {
    private static CampeonatoDAO singleton = null;

    private CampeonatoDAO() {
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
        Statement stm = conn.createStatement()) {
                String sql = "CREATE TABLE IF NOT EXISTS Campeonato ("
                        + "idCampeonato VARCHAR(255) NOT NULL,"
                        + "nomeCampeonato VARCHAR(255) NOT NULL,"
                        + "numCorridas INTEGER NOT NULL,"
                        + "PRIMARY KEY (idCampeonato))";
                stm.executeUpdate(sql);
                String sql2 = "CREATE TABLE IF NOT EXISTS Participante ("
                        + "idParticipante VARCHAR(255) NOT NULL,"
                        + "idUtilizador VARCHAR(255) NOT NULL,"
                        + "idPiloto VARCHAR(255) NOT NULL,"
                        + "idCarro VARCHAR(255) NOT NULL,"
                        + "posicao INTEGER NOT NULL,"
                        + "timeDiff FLOAT NOT NULL,"
                        + "PRIMARY KEY (idParticipante),"
                        + "FOREIGN KEY (idUtilizador) REFERENCES Utilizador(idUtilizador),"
                        + "FOREIGN KEY (idPiloto) REFERENCES Piloto(idPiloto),"
                        + "FOREIGN KEY (idCarro) REFERENCES Carro(idCarro))";
                stm.executeUpdate(sql2);
                String sql3 = "CREATE TABLE IF NOT EXISTS Classificacao ("
                        + "idCampeonato VARCHAR(255) NOT NULL,"
                        + "idParticipante VARCHAR(255) NOT NULL,"
                        + "pontos INTEGER NOT NULL,"
                        + "PRIMARY KEY (idCampeonato, idParticipante),"
                        + "FOREIGN KEY (idCampeonato) REFERENCES Campeonato(idCampeonato),"
                        + "FOREIGN KEY (idParticipante) REFERENCES Participante(idParticipante))";
                stm.executeUpdate(sql3);
                String sql4 = "CREATE TABLE IF NOT EXISTS CircuitoCamp ("
                        + "idCampeonato VARCHAR(255) NOT NULL,"
                        + "idCircuito VARCHAR(255) NOT NULL,"
                        + "PRIMARY KEY (idCampeonato, idCircuito),"
                        + "FOREIGN KEY (idCampeonato) REFERENCES Campeonato(idCampeonato),"
                        + "FOREIGN KEY (idCircuito) REFERENCES Circuito(idCircuito))";
                stm.executeUpdate(sql4);
                String sql5 = "CREATE TABLE IF NOT EXISTS Corrida ("
                    + "idCorrida VARCHAR(255) NOT NULL,"
                    + "idCircuito VARCHAR(255) NOT NULL,"
                    + "clima INTEGER NOT NULL,"
                    + "tempo FLOAT NOT NULL,"
                    + "volta INTEGER NOT NULL,"
                    + "PRIMARY KEY (idCorrida),"
                    + "FOREIGN KEY (idCircuito) REFERENCES Circuito(idCircuito))";
                stm.executeUpdate(sql5);
                String sql6 = "CREATE TABLE IF NOT EXISTS dnf ("
                        + "idParticipante VARCHAR(255) NOT NULL,"
                        + "idCorrida VARCHAR(255) NOT NULL,"
                        + "dnf INTEGER NOT NULL,"
                        + "PRIMARY KEY (idParticipante, idCorrida),"
                        + "FOREIGN KEY (idParticipante) REFERENCES Participante(idParticipante),"
                        + "FOREIGN KEY (idCorrida) REFERENCES Corrida(idCorrida))";
                stm.executeUpdate(sql6);
                String sql7 = "CREATE TABLE IF NOT EXISTS ParticipanteCorrida ("
                        + "idParticipante VARCHAR(255) NOT NULL,"
                        + "idCorrida VARCHAR(255) NOT NULL,"
                        + "PRIMARY KEY (idParticipante, idCorrida),"
                        + "FOREIGN KEY (idParticipante) REFERENCES Participante(idParticipante),"
                        + "FOREIGN KEY (idCorrida) REFERENCES Corrida(idCorrida))";
                stm.executeUpdate(sql7);
                String sql8 = "CREATE TABLE IF NOT EXISTS CorridaCamp ("
                        + "idCampeonato VARCHAR(255) NOT NULL,"
                        + "idCorrida VARCHAR(255) NOT NULL,"
                        + "check BOOLEAN NOT NULL,"
                        + "PRIMARY KEY (idCampeonato, idCorrida),"
                        + "FOREIGN KEY (idCampeonato) REFERENCES Campeonato(idCampeonato),"
                        + "FOREIGN KEY (idCorrida) REFERENCES Corrida(idCorrida))";
                stm.executeUpdate(sql8);
            } catch (Exception e) {
                e.printStackTrace();
                throw new NullPointerException(e.getMessage());
            }   
        }

        public static CampeonatoDAO getInstance() {
            if (CampeonatoDAO.singleton == null) {
                CampeonatoDAO.singleton = new CampeonatoDAO();
            }
            return CampeonatoDAO.singleton;
        }

        @Override
        public int size() {
            int i = 0;
            try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
                String sql = "SELECT * FROM Campeonato";
                try (ResultSet rs = stm.executeQuery(sql)) {
                    for (; rs.next(); i++);
                }
            } catch (Exception e) {
                e.printStackTrace();
                throw new NullPointerException(e.getMessage());
            }
            return i;
        }

        @Override
        public boolean isEmpty() {
            return this.size() == 0;
        }

        @Override
        public boolean containsKey(Object key) {
            boolean r = false;
            try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
                String sql = "SELECT * FROM Campeonato WHERE idCampeonato='" + key + "'";
                try (ResultSet rs = stm.executeQuery(sql)) {
                    r = rs.next();
                }
            } catch (Exception e) {
                e.printStackTrace();
                throw new NullPointerException(e.getMessage());
            }
            return r;
        }

        @Override
        public boolean containsValue(Object value) {
            Campeonato c = (Campeonato) value;
            return this.containsKey(c.getProva());
        }
        
        @Override
        public Campeonato get(Object key) {
            Campeonato camp = null;
            try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
                String sql = "SELECT * FROM Campeonato WHERE idCampeonato='" + key + "'";
                try (ResultSet rs = stm.executeQuery(sql)) {
                    if (rs.next()) {
                        Map <String, Integer> classificacao = new HashMap<>();
                        String sql2 = "SELECT * FROM Classificacao WHERE idCampeonato='" + key + "'";
                        try (ResultSet rs2 = stm.executeQuery(sql2)) {
                            for (; rs2.next();) {
                                classificacao.put(rs2.getString("idParticipante"), rs2.getInt("pontos"));
                            }
                        }
                        Map <String, Participante> participantes = new HashMap<>();
                        String sql3 = "SELECT * FROM ParticipanteCamp WHERE idCampeonato='" + key + "'";
                        try (ResultSet rs3 = stm.executeQuery(sql3)) {
                            for (; rs3.next();) {
                                String sql4 = "SELECT * FROM Participante WHERE idParticipante='" + rs3.getString("idParticipante") + "'";
                                try (ResultSet rs4 = stm.executeQuery(sql4)) {
                                    if (rs4.next()) {
                                        Piloto piloto = PilotoDAO.getInstance().get(rs4.getString("idPiloto"));
                                        Carro carro = CarroDAO.getInstance().get(rs4.getString("idCarro"));
                                        Utilizador util = UtilizadorDAO.getInstance().get(rs4.getString("idUtilizador"));
                                        Participante part = new Participante(rs4.getInt("posicao"), piloto, carro, util,rs4.getFloat("timeDiff"));
                                        participantes.put(rs3.getString("idParticipante"), part);
                                    }
                                }
                            }
                        }
                        ArrayList <Circuito> circuitos = new ArrayList<>();
                        String sql5 = "SELECT * FROM CircuitoCamp WHERE idCampeonato='" + key + "'";
                        try (ResultSet rs5 = stm.executeQuery(sql5)) {
                            for (; rs5.next();) {
                                Circuito circ = CircuitoDAO.getInstance().get(rs5.getString("idCircuito"));
                                circuitos.add(circ);
                            }
                        }
                        Map<Corrida, Boolean> corridas = new HashMap<>();
                        String sql6 = "SELECT * FROM CorridaCamp WHERE idCampeonato='" + key + "'";
                        try (ResultSet rs6 = stm.executeQuery(sql6)) {
                            for (; rs6.next();) {
                                String sql7 = "SELECT * FROM Corrida WHERE idCorrida='" + rs6.getString("idCorrida") + "'";
                                try (ResultSet rs7 = stm.executeQuery(sql7)) {
                                    if (rs7.next()) {
                                        Circuito circ = CircuitoDAO.getInstance().get(rs7.getString("idCircuito"));
                                        Map<Participante, Integer> dnf = new HashMap<>();
                                        String sql8 = "SELECT * FROM ParticipanteCorrida WHERE idCorrida='" + rs6.getString("idCorrida") + "'";
                                        try (ResultSet rs8 = stm.executeQuery(sql8)) {
                                            for (; rs8.next();) {
                                                String sql9 = "SELECT * FROM Participante WHERE idParticipante='" + rs8.getString("idParticipante") + "'";
                                                try (ResultSet rs9 = stm.executeQuery(sql9)) {
                                                    if (rs9.next()) {
                                                        Piloto piloto = PilotoDAO.getInstance().get(rs9.getString("idPiloto"));
                                                        Carro carro = CarroDAO.getInstance().get(rs9.getString("idCarro"));
                                                        Utilizador util = UtilizadorDAO.getInstance().get(rs9.getString("idUtilizador"));
                                                        Participante part = new Participante(rs9.getInt("posicao"), piloto, carro, util,rs9.getFloat("timeDiff"));
                                                        dnf.put(part, rs8.getInt("dnf"));
                                                    }
                                                }
                                            }
                                        }
                                        List <Participante> part = new ArrayList<>();
                                        String sql10 = "SELECT * FROM ParticipanteCorrida WHERE idCorrida='" + rs6.getString("idCorrida") + "'";
                                        try (ResultSet rs10 = stm.executeQuery(sql10)) {
                                            for (; rs10.next();) {
                                                String sql11 = "SELECT * FROM Participante WHERE idParticipante='" + rs10.getString("idParticipante") + "'";
                                                try (ResultSet rs11 = stm.executeQuery(sql11)) {
                                                    if (rs11.next()) {
                                                        Piloto piloto = PilotoDAO.getInstance().get(rs11.getString("idPiloto"));
                                                        Carro carro = CarroDAO.getInstance().get(rs11.getString("idCarro"));
                                                        Utilizador util = UtilizadorDAO.getInstance().get(rs11.getString("idUtilizador"));
                                                        Participante p = new Participante(rs11.getInt("posicao"), piloto, carro, util,rs11.getFloat("timeDiff"));
                                                        part.add(p);
                                                    }
                                                }
                                            }
                                        }
                                        Corrida corrida = new Corrida(circ,dnf,rs7.getInt("clima"),rs7.getInt("tempo"),part,rs7.getInt("volta"));
                                        corridas.put(corrida, rs6.getBoolean("check"));
                                    }
                                }
                            }
                        camp = new Campeonato(rs.getString("nomeCampeonato"), circuitos, participantes, classificacao, rs.getInt("numCorridas"), corridas);
                        }
                    }
                }   
            } catch (Exception e) {
                e.printStackTrace();
                throw new NullPointerException(e.getMessage());
            }
            return camp;
        }

        @Override
        public Campeonato put(String key, Campeonato value) {
            Campeonato camp = null;
            try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
                Statement stm = conn.createStatement()) {
                String sql = "SELECT * FROM Campeonato WHERE idCampeonato='" + key + "'";
                    try (ResultSet rs = stm.executeQuery(sql)){
                        if (rs.next()) {
                            String sql2 = "DELETE FROM CorridaCamp WHERE idCampeonato='" + key + "'";
                            stm.executeUpdate(sql2);
                            String sql3 = "DELETE FROM CircuitoCamp WHERE idCampeonato='" + key + "'";
                            stm.executeUpdate(sql3);
                            String sql4 = "DELETE FROM ParticipanteCamp WHERE idCampeonato='" + key + "'";
                            stm.executeUpdate(sql4);
                            String sql5 = "DELETE FROM Classificacao WHERE idCampeonato='" + key + "'";
                            stm.executeUpdate(sql5);
                            String sql6 = "DELETE FROM Campeonato WHERE idCampeonato='" + key + "'";
                            stm.executeUpdate(sql6);
                        }
                    }
                String sql7 = "INSERT INTO Campeonato VALUES ('" + key + "','" + value.getProva() + "','" + value.getNumCorrida() + "')";
                stm.executeUpdate(sql7);
                for (Map.Entry<String,Integer> entry : value.getClassificacao().entrySet()) {
                    String sql8 = "INSERT INTO Classificacao VALUES ('" + key + "','" + entry.getKey() + "','" + entry.getValue() + "')";
                    stm.executeUpdate(sql8);
                }
                for(Map.Entry<String, Participante> entry : value.getListaPart().entrySet()) {
                    String sql9 = "INSERT INTO Participante VALUES ('" + entry.getKey() + "','" + entry.getValue().getpiloto().getNome() + "','" + entry.getValue().getCarro().getModelo() + "','" + entry.getValue().getUtilizador().getUser() + "','" + entry.getValue().getPosicao() + "','" + entry.getValue().getTimeDiff() + "')";
                    stm.executeUpdate(sql9);
                    String sql10 = "INSERT INTO ParticipanteCamp VALUES ('" + key + "','" + entry.getKey() + "')";
                    stm.executeUpdate(sql10);
                }
                for (Circuito c : value.getCircuitos()) {
                    String sql12 = "INSERT INTO CircuitoCamp VALUES ('" + key + "','" + c.getNome() + "')";
                    stm.executeUpdate(sql12);
                }
                for(Map.Entry<Corrida, Boolean> entry : value.getCorridas().entrySet()) {
                    String sql13 = "INSERT INTO Corrida VALUES ('" + entry.getKey().getCiruito().getNome() + "','" + entry.getKey().getCiruito().getNome() + "','" + entry.getKey().getClima() + "','" + entry.getKey().getTempos() + "','" + entry.getKey().getVolta() + "')";
                    stm.executeUpdate(sql13);
                    for(Participante p : entry.getKey().getParticipante()) {
                        String sql15 = "INSERT INTO Participante VALUES ('" + p.getpiloto().getNome() + "','" + p.getCarro().getModelo() + "','" + p.getUtilizador().getUser() + "','" + p.getPosicao() + "','" + p.getTimeDiff() + "')";
                        stm.executeUpdate(sql15);
                    }
                    for(Map.Entry<Participante, Integer> entry2 : entry.getKey().getDNF().entrySet()) {
                        String sql14 = "INSERT INTO ParticipanteCorrida VALUES ('" + entry2.getKey().getpiloto().getNome() + "','" + entry2.getKey().getCarro().getModelo() + "','" + entry2.getKey().getUtilizador().getUser() + "','" + entry2.getKey().getPosicao() + "','" + entry2.getKey().getTimeDiff() + "','" + entry2.getValue() + "')";
                        stm.executeUpdate(sql14);
                    }
                    String sql16 = "INSERT INTO CorridaCamp VALUES ('" + key + "','" + entry.getKey().getCiruito().getNome() + "','" + entry.getValue() + "')";
                    stm.executeUpdate(sql16);
                }
            } catch (Exception e) {
                e.printStackTrace();
                throw new NullPointerException(e.getMessage());
            }
            return camp;
        }

        @Override
        public Campeonato remove(Object key) {
            Campeonato camp = null;
            try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
                Statement stm = conn.createStatement()) {
                String sql = "SELECT * FROM Campeonato WHERE idCampeonato='" + key + "'";
                    try (ResultSet rs = stm.executeQuery(sql)){
                        if (rs.next()) {
                            String sql2 = "DELETE FROM CorridaCamp WHERE idCampeonato='" + key + "'";
                            stm.executeUpdate(sql2);
                            String sql3 = "DELETE FROM CircuitoCamp WHERE idCampeonato='" + key + "'";
                            stm.executeUpdate(sql3);
                            String sql4 = "DELETE FROM ParticipanteCamp WHERE idCampeonato='" + key + "'";
                            stm.executeUpdate(sql4);
                            String sql5 = "DELETE FROM Classificacao WHERE idCampeonato='" + key + "'";
                            stm.executeUpdate(sql5);
                            String sql6 = "DELETE FROM Campeonato WHERE idCampeonato='" + key + "'";
                            stm.executeUpdate(sql6);
                        }
                    }
            } catch (Exception e) {
                e.printStackTrace();
                throw new NullPointerException(e.getMessage());
            }
            return camp;
        }

        @Override
        public void putAll(Map<? extends String, ? extends Campeonato> m) {
            for (Campeonato camp : m.values()) {
                this.put(camp.getProva(), camp);
            }
        }

        @Override
        public void clear() {
            try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
                Statement stm = conn.createStatement()) {
                String sql = "DELETE FROM CorridaCamp";
                stm.executeUpdate(sql);
                String sql2 = "DELETE FROM CircuitoCamp";
                stm.executeUpdate(sql2);
                String sql3 = "DELETE FROM ParticipanteCamp";
                stm.executeUpdate(sql3);
                String sql4 = "DELETE FROM Classificacao";
                stm.executeUpdate(sql4);
                String sql5 = "DELETE FROM Campeonato";
                stm.executeUpdate(sql5);
            } catch (Exception e) {
                e.printStackTrace();
                throw new NullPointerException(e.getMessage());
            }
        }

        @Override
        public Set<String> keySet() {
            Set<String> set = new HashSet<>();
            try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
                Statement stm = conn.createStatement()) {
                String sql = "SELECT * FROM Campeonato";
                try (ResultSet rs = stm.executeQuery(sql)) {
                    while (rs.next()) {
                        set.add(rs.getString("idCampeonato"));
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
                throw new NullPointerException(e.getMessage());
            }
            return set;
        }

        @Override
        public Collection<Campeonato> values() {
            Collection<Campeonato> col = new HashSet<>();
            try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
                Statement stm = conn.createStatement()) {
                String sql = "SELECT * FROM Campeonato";
                try (ResultSet rs = stm.executeQuery(sql)) {
                    while (rs.next()) {
                        col.add(this.get(rs.getString("idCampeonato")));
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
                throw new NullPointerException(e.getMessage());
            }
            return col;
        }

        @Override
        public Set<Entry<String, Campeonato>> entrySet() {
            Set<Entry<String, Campeonato>> set = new HashSet<>();
            try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
                Statement stm = conn.createStatement()) {
                String sql = "SELECT * FROM Campeonato";
                try (ResultSet rs = stm.executeQuery(sql)) {
                    while (rs.next()) {
                        set.add(new AbstractMap.SimpleEntry<>(rs.getString("idCampeonato"), this.get(rs.getString("idCampeonato"))));
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
                throw new NullPointerException(e.getMessage());
            }
            return set;
        }
}
