package buisness.Carro;

public interface IFacadeCarro {

    public Carro findCarro(String modelo) throws CarroInvalido;

    public String createCarro(String tipoCarro,String marca, String modelo, int cilindrada, int potencia, int pa, int motorE );

    public String garagemToString();

    public boolean addCarro(Carro c);

}