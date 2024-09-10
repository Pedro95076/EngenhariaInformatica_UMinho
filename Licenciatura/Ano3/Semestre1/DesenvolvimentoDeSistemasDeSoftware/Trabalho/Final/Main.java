import buisness.Utilizador.Administrador;
import ui.TextUI;

public class Main {

    public static void main(String[] args) {
        try {
            new TextUI().run();
        }
        catch (Exception e) {
            System.out.println("Não foi possível arrancar: "+e.getMessage());
        }
    }


}