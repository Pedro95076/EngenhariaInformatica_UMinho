package data;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import buisness.Racing.*;

public class CircuitoDAO implements Map<String, Circuito>{
    private static CircuitoDAO instance = null;

    private CircuitoDAO() {
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "CREATE TABLE IF NOT EXISTS circuito ("
                + "id VARCHAR(255) NOT NULL,"
                + "nome VARCHAR(255) NOT NULL,"
                + "distancia INT NOT NULL,"
                + "voltas INT NOT NULL,"
                + "PRIMARY KEY (id))";
            stm.executeUpdate(sql);
            String sql2 = "CREATE TABLE IF NOT EXISTS seccao ("
                + "tipo INT NOT NULL,"
                + "gdu INT NOT NULL,"
                + "circuito_id VARCHAR(255) NOT NULL,"
                + "FOREIGN KEY(circuito_id) REFERENCES circuito(id))";
            stm.executeUpdate(sql2);
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
    }

    public static CircuitoDAO getInstance() {
        if (instance == null) {
            instance = new CircuitoDAO();
        }
        return instance;
    }

    @Override
    public int size() {
        int i = 0;
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM circuito";
            ResultSet rs = stm.executeQuery(sql);
            for (; rs.next(); i++);
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
            String sql = "SELECT * FROM circuito WHERE id = " + key;
            ResultSet rs = stm.executeQuery(sql);
            r = rs.next();
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return r;
    }

    @Override
    public boolean containsValue(Object value) {
        boolean r = false;
        if (value instanceof Circuito) {
            Circuito c = (Circuito) value;
            try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
                Statement stm = conn.createStatement()) {
                String sql = "SELECT * FROM circuito WHERE nome = '" + c.getNome() + "' AND distancia = " + c.getDistancia() + " AND voltas = " + c.getVoltas();
                ResultSet rs = stm.executeQuery(sql);
                r = rs.next();
            } catch (Exception e) {
                e.printStackTrace();
                throw new NullPointerException(e.getMessage());
            }
        }
        return r;
    }

    @Override
    public Circuito get(Object key) {
        Circuito c = null;
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM circuito WHERE id = " + key;
            ResultSet rs = stm.executeQuery(sql);
            if (rs.next()) {
                //obter as seccoes do circuito e adicionar ao circuito e meter num arraylist
                Statement stm2 = conn.createStatement();
                String sql2 = "SELECT * FROM seccao WHERE circuito_id = " + key;
                ResultSet rs2 = stm2.executeQuery(sql2);
                ArrayList <Seccao> seccoes = new ArrayList<>();
                for (; rs2.next();) {
                    seccoes.add(new Seccao(rs2.getInt("tipo"), rs2.getInt("gdu")));
                }
                c = new Circuito(rs.getString("nome"), rs.getInt("distancia"), rs.getInt("voltas"), seccoes);
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return c;
    }

    @Override
    public Circuito put(String key, Circuito value) {
        Circuito c = null;
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM circuito WHERE id='" + key + "'";
            try (ResultSet rs = stm.executeQuery(sql)) {
                if (rs.next()) {
                    c = get(key);
                    sql = "DELETE FROM circuito WHERE id='" + key + "'";
                    stm.executeUpdate(sql);
                    sql = "DELETE FROM seccao WHERE circuito_id='" + key + "'";
                    stm.executeUpdate(sql);
                }
            }
            String sql2 = "INSERT INTO circuito VALUES ('"
                + value.getNome() + "','"
                + value.getNome() + "','"
                + value.getDistancia() + "','"
                + value.getVoltas() + "')";
            stm.executeUpdate(sql2);
            for (Seccao s : value.getListaSeccoes()) {
                String sql4 = "INSERT INTO seccao (tipo, gdu, circuito_id) VALUES ("
                    + s.getTipo() + ", "
                    + s.getGDU() + ", '"
                    + value.getNome() + "')";
                System.out.println(sql4);
                stm.executeUpdate(sql4);
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return c;
    }

    @Override
    public Circuito remove(Object key) {
        Circuito c = this.get(key);
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "DELETE FROM seccao WHERE circuito_id = " + key;
            stm.executeUpdate(sql);
            String sql2 = "DELETE FROM circuito WHERE id = " + key;
            stm.executeUpdate(sql2);
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return c;
    }

    @Override
    public void putAll(Map<? extends String, ? extends Circuito> m) {
        for (Circuito c : m.values()) {
            this.put(c.getNome(), c);
        }
    }

    @Override
    public void clear() {
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "DELETE FROM seccao";
            stm.executeUpdate(sql);
            String sql2 = "DELETE FROM circuito";
            stm.executeUpdate(sql2);
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
            String sql = "SELECT * FROM circuito";
            ResultSet rs = stm.executeQuery(sql);
            for (; rs.next();) {
                set.add(rs.getString("id"));
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return set;
    }

    @Override
    public Collection<Circuito> values() {
        Collection<Circuito> col = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM circuito";
            ResultSet rs = stm.executeQuery(sql);
            for (; rs.next();) {
                Statement stm2 = conn.createStatement();
                String sql2 = "SELECT * FROM seccao WHERE circuito_id = " + rs.getInt("id");
                ResultSet rs2 = stm2.executeQuery(sql2);
                ArrayList <Seccao> seccoes = new ArrayList<>();
                for (; rs2.next();) {
                    seccoes.add(new Seccao(rs2.getInt("tipo"), rs2.getInt("gdu")));
                }
                col.add(new Circuito(rs.getString("nome"), rs.getInt("distancia"), rs.getInt("voltas"), seccoes));
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return col;
    }

    @Override
    public Set<Entry<String, Circuito>> entrySet() {
        Set<Entry<String, Circuito>> set = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM circuito";
            ResultSet rs = stm.executeQuery(sql);
            for (; rs.next();) {
                Statement stm2 = conn.createStatement();
                String sql2 = "SELECT * FROM seccao WHERE circuito_id = " + rs.getInt("id");
                ResultSet rs2 = stm2.executeQuery(sql2);
                ArrayList <Seccao> seccoes = new ArrayList<>();
                for (; rs2.next();) {
                    seccoes.add(new Seccao(rs2.getInt("tipo"), rs2.getInt("gdu")));
                }
                set.add(new AbstractMap.SimpleEntry<>(rs.getString("id"), new Circuito(rs.getString("nome"), rs.getInt("distancia"), rs.getInt("voltas"), seccoes)));
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return set;
    }

}