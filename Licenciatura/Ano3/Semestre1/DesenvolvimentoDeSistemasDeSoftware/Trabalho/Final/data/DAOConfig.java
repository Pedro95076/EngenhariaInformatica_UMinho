package data;

public class DAOConfig {
    static final String USERNAME = "jfc";                       // Actualizar
    static final String PASSWORD = "jfc";                       // Actualizar
    private static final String DATABASE = "racingSim";          // Actualizar
    private static final String DRIVER = "jdbc:mariadb";        // Usar para MariaDB
    static final String URL = DRIVER+"://localhost:3306/"+DATABASE;
}
