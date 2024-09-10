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

import buisness.Utilizador.*;

public class UtilizadorDAO implements Map<String, Utilizador>{
    private static UtilizadorDAO singleton = null;
    
    private UtilizadorDAO() {
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "CREATE TABLE IF NOT EXISTS utilizador ("
                    + "id VARCHAR(255) PRIMARY KEY,"
                    + "user VARCHAR(255) NOT NULL,"
                    + "password VARCHAR(255) NOT NULL,"
                    + "points INTEGER NOT NULL,"
                    + "isPremium BOOLEAN NOT NULL,"
                    + "type VARCHAR(255) NOT NULL"
                    + ")";
            stm.executeUpdate(sql);
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
    }

    public static UtilizadorDAO getInstance() {
        if (UtilizadorDAO.singleton == null) {
            UtilizadorDAO.singleton = new UtilizadorDAO();
        }
        return UtilizadorDAO.singleton;
    }

    @Override
    public int size() {
        int i = 0;
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM utilizador";
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
            String sql = "SELECT * FROM utilizador WHERE id='" + key + "'";
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
        boolean r = false;
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM utilizador WHERE user='" + ((Utilizador) value).getUser() + "'";
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
    public Utilizador get(Object key) {
        Utilizador u = null;
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM utilizador WHERE id='" + key + "'";
            try (ResultSet rs = stm.executeQuery(sql)) {
                if (rs.next()) {
                    if (rs.getString("type").equals("Administrador")) {
                        u = new Administrador(rs.getString("user"), rs.getString("password"));
                    } else if (rs.getString("type").equals("Jogador")) {
                        boolean b = false;
                        if (rs.getInt("isPremium") == 1) {
                            b = true;
                        }
                        u = new Jogador(rs.getString("user"), rs.getString("password"), rs.getInt("points"), b);
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return u;
    }

    @Override
    public Utilizador put(String key, Utilizador value) {
        Utilizador u = null;
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM utilizador WHERE id='" + key + "'";
            try (ResultSet rs = stm.executeQuery(sql)) {
                if (rs.next()) {
                    u = get(key);
                    sql = "DELETE FROM utilizador WHERE id='" + key + "'";
                    stm.executeUpdate(sql);
                }
            }
            if (value instanceof Administrador) {
                sql = "INSERT INTO utilizador VALUES("
                        + "'" + key + "',"
                        + "'" + value.getUser() + "',"
                        + "'" + ((Administrador) value).getPassword() + "',"
                        + "'" + "Administrador" + "'"
                        + ")";
                stm.executeUpdate(sql);
            } else if (value instanceof Jogador) {
                int b = 0;
                if(((Jogador) value).getIsPremium())
                    b = 1;
                sql = "INSERT INTO utilizador VALUES("
                        + "'" + key + "',"
                        + "'" + value.getUser() + "',"
                        + "'" + ((Jogador) value).getPassword() + "',"
                        + "'" + ((Jogador) value).getPoints() + "',"
                        + "'" + b + "',"
                        + "'" + "Jogador" + "'"
                        + ")";
                stm.executeUpdate(sql);
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return u;
    }

    @Override
    public Utilizador remove(Object key) {
        Utilizador u = this.get(key);
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "DELETE FROM utilizador WHERE id='" + key + "'";
            stm.executeUpdate(sql);
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return u;
    }

    @Override
    public void putAll(Map<? extends String, ? extends Utilizador> m) {
        for (Utilizador u : m.values()) {
            this.put(u.getUser(), u);
        }
    }

    @Override
    public void clear() {
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "DELETE FROM utilizador";
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
            String sql = "SELECT * FROM utilizador";
            try (ResultSet rs = stm.executeQuery(sql)) {
                for (; rs.next();) {
                    set.add(rs.getString("id"));
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return set;
    }
    
    @Override
    public Collection<Utilizador> values() {
        Collection<Utilizador> col = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM utilizador";
            try (ResultSet rs = stm.executeQuery(sql)) {
                for (; rs.next();) {
                    if (rs.getString("type").equals("Administrador")) {
                        col.add(new Administrador(rs.getString("user"), rs.getString("password")));
                    } else if (rs.getString("type").equals("Jogador")) {
                        col.add(new Jogador(rs.getString("user"), rs.getString("password"), rs.getInt("points"), rs.getBoolean("isPremium")));
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return col;
    }

    @Override
    public Set<Entry<String, Utilizador>> entrySet() {
        Set<Entry<String, Utilizador>> set = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOConfig.URL, DAOConfig.USERNAME, DAOConfig.PASSWORD);
            Statement stm = conn.createStatement()) {
            String sql = "SELECT * FROM utilizador";
            try (ResultSet rs = stm.executeQuery(sql)) {
                for (; rs.next();) {
                    if (rs.getString("type").equals("Administrador")) {
                        set.add(new AbstractMap.SimpleEntry<>(rs.getString("id"), new Administrador(rs.getString("user"), rs.getString("password"))));
                    } else if (rs.getString("type").equals("Jogador")) {
                        set.add(new AbstractMap.SimpleEntry<>(rs.getString("id"), new Jogador(rs.getString("user"), rs.getString("password"), rs.getInt("points"), rs.getBoolean("isPremium"))));
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return set;
    }

}

