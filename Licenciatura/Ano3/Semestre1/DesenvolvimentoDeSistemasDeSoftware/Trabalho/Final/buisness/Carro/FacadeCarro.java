package buisness.Carro;
import java.util.*;

import data.CarroDAO;


public class FacadeCarro implements IFacadeCarro {

    private Map<String,Carro> mapCarros = CarroDAO.getInstance();   //modelo(key) -> carro

    public Map<String,Carro> getGaragem()
    {
        return this.mapCarros;
    }

    //para os participantes tirarem uma "copia" do carro da garagem. quando os admins querem aceder a um
    //carro para o alterar, nao usam esta funcao.
    public Carro findCarro(String modelo) throws CarroInvalido
    {
        if(!this.mapCarros.containsKey(modelo)) return null;
        else 
        {
            Carro c = this.mapCarros.get(modelo);    
            String tipoCarro = c.getClass().getSimpleName();
            switch(tipoCarro)
            {
                case "C1":
                    C1 new_c1  = (C1) c;
                    return new_c1.clone();
                case "C1H":
                    C1H new_c1h = (C1H) c;
                    return new_c1h.clone();
                case "C2":
                    C2 new_c2 = (C2) c;
                    return new_c2.clone();
                case "C2H":
                    C2H new_c2h = (C2H) c;
                    return new_c2h.clone();
                case "GT":
                    GT new_gt = (GT) c;
                    return new_gt.clone();
                case "GTH":
                    GTH new_gth = (GTH) c;
                    return new_gth.clone();
                case "SC":
                    SC new_sc = (SC) c;
                    return new_sc.clone();
                default:
                    throw new CarroInvalido("Erro a retirar o carro da garagem, modelo de carro inválido");
            }
        }
    }
    //                              "SC","C1",...                                                                (-1 caso nao hibrido)
    //                                  vvv                                                                             vvv
    public String createCarro(String tipoCarro,String marca, String modelo, int cilindrada, int potencia, int pa, int motorE )
    {
        Carro c = null;
        String resposta = "";
        try
        {
            switch(tipoCarro)
            {
                case "C1":
                    c = new C1(marca,modelo,cilindrada,potencia,pa);
                    break;
                case "C1H":
                    c = new C1H(marca,modelo,cilindrada,potencia,pa,motorE);
                    break;
                case "C2":
                    c = new C2(marca,modelo,cilindrada,potencia,pa);
                    break;
                case "C2H":
                    c = new C2H(marca,modelo,cilindrada,potencia,pa,motorE);
                    break;
                case "GT":
                    c = new GT(marca,modelo,cilindrada,potencia,pa);
                    break;
                case "GTH":
                    c = new GTH(marca,modelo,cilindrada,potencia,pa,motorE);
                    break;
                case "SC":
                    c = new SC(marca,modelo,cilindrada,potencia,pa);
                    break;
                default:
                    break;
            }
                if (c == null) //se nao foi inserido um tipo de carro valido
                    resposta = "Tipo de carro invalido, operação abortada";
                
                resposta = (this.addCarro(c) ? "Carro inserido com sucesso!" :
                                               "Já existe um carro com esse modelo na garagem...");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return resposta;
    }

    public boolean addCarrohibridro(int tipo, String marca, String modelo,int cilindrada, int potencia, float pa, int potenciaE){
        try
			{
				switch (tipo)
				{
					case 1:
						C1H c1 = new C1H(marca,modelo,cilindrada,potencia,pa,potenciaE);
						return this.addCarro(c1) ;
					case 2:
						C2H c2 = new C2H(marca,modelo,cilindrada,potencia,pa,potenciaE);
						return this.addCarro(c2) ;
					case 3:
						GTH gt = new GTH(marca,modelo,cilindrada,potencia,pa,potenciaE);
						return this.addCarro(gt) ;
					default:
						break;		
				}
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
        return true;
    }


    public boolean addCarro(Carro c)
    {
        String key = c.getModelo();
        if(this.getGaragem().containsKey(key))
            return false;
        else
            {
                this.getGaragem().put(key,c);
                return true;
            }
    }

    public String garagemToString()
    {
        String s = "====================\nGARAGEM DO SIMULADOR\n====================\n\n";
        for(Map.Entry<String,Carro> pair : this.mapCarros.entrySet())
                s += pair.getValue().toString();
        return s;

    }






}