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

import buisness.Racing.*;

public class PilotoDAO implements Map<String, Piloto>{
    private static PilotoDAO singleton = new PilotoDAO();

    private PilotoDAO() {
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "CREATE TABLE IF NOT EXISTS Piloto ("
                    + "idPiloto VARCHAR(255) NOT NULL,"
                    + "nome VARCHAR(255) NOT NULL,"
                    + "chuvaVSseco FLOAT(3,2) NOT NULL,"
                    + "agressividade FLOAT(3,2) NOT NULL,"
                    + "PRIMARY KEY (idPiloto))";
            stm.executeUpdate(sql);
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
    }

    public static PilotoDAO getInstance() {
        if (singleton == null) {
            singleton = new PilotoDAO();
        }
        return singleton;
    }

    @Override
    public int size() {
        int i = 0;
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT idPiloto FROM Piloto";
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
            String sql = "SELECT idPiloto FROM Piloto WHERE idPiloto='" + key + "'";
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
        Piloto p = (Piloto) value;
        return this.containsKey(p.getNome());
    }

    @Override
    public Piloto get(Object key) {
        Piloto p = null;
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM Piloto WHERE idPiloto='" + key + "'";
            try (ResultSet rs = stm.executeQuery(sql)) {
                if (rs.next()) {
                    p = new Piloto(rs.getString("nome"), rs.getFloat("chuvaVSseco"), rs.getFloat("agressividade"));
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return p;
    }

    @Override
    public Piloto put(String key, Piloto value) {
        Piloto p = null;
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM Piloto WHERE idPiloto='" + key + "'";
            try (ResultSet rs = stm.executeQuery(sql)) {
                if (rs.next()) {
                    p = new Piloto(rs.getString("nome"), rs.getFloat("chuvaVSseco"), rs.getFloat("agressividade"));
                    sql = "UPDATE Piloto SET nome='" + value.getNome() + "', chuvaVSseco=" + value.getChuvaVSseco() + ", agressividade=" + value.getAgressividade() + " WHERE idPiloto='" + key + "'";
                } else {
                    sql = "INSERT INTO Piloto (idPiloto, nome, chuvaVSseco, agressividade) VALUES ('" + key + "', '" + value.getNome() + "', " + value.getChuvaVSseco() + ", " + value.getAgressividade() + ")";
                }
                stm.executeUpdate(sql);
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return p;
    }

    @Override
    public Piloto remove(Object key) {
        Piloto p = this.get(key);
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "DELETE FROM Piloto WHERE idPiloto='" + key + "'";
            stm.executeUpdate(sql);
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return p;
    }

    @Override
    public void putAll(Map<? extends String, ? extends Piloto> m) {
        for (Piloto p : m.values()) {
            this.put(p.getNome(), p);
        }
    }

    @Override
    public void clear() {
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "DELETE FROM Piloto";
            stm.executeUpdate(sql);
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
            String sql = "SELECT idPiloto FROM Piloto";
            try (ResultSet rs = stm.executeQuery(sql)) {
                for (; rs.next();) {
                    set.add(rs.getString("idPiloto"));
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return set;
    }

    @Override
    public Collection<Piloto> values() {
        Collection<Piloto> col = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM Piloto";
            try (ResultSet rs = stm.executeQuery(sql)) {
                for (; rs.next();) {
                    col.add(new Piloto(rs.getString("nome"), rs.getFloat("chuvaVSseco"), rs.getFloat("agressividade")));
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return col;
    }

    @Override
    public Set<Entry<String, Piloto>> entrySet() {
        Set<Entry<String, Piloto>> set = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM Piloto";
            try (ResultSet rs = stm.executeQuery(sql)) {
                for (; rs.next();) {
                    set.add(new AbstractMap.SimpleEntry<>(rs.getString("idPiloto"), new Piloto(rs.getString("nome"), rs.getFloat("chuvaVSseco"), rs.getFloat("agressividade"))));
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return set;
    }

}
