package buisness.Carro;


public enum estadoMotor{
CONSERVADOR,
NORMAL,
AGRESSIVO,
NULL;

    public static estadoMotor fromString(String str)
    {
	 switch (str)
	 	{
		case("conservador"):
			return CONSERVADOR;
		case("normal"):
			return NORMAL;
		case("agressivo"):
			return AGRESSIVO;
		default:
			return NULL;	
		}
    }
	public static String toStr(estadoMotor estado)
	{
	 switch(estado)
		{
		case CONSERVADOR:
			return "conservador";
		case NORMAL:
			return "normal";
		case AGRESSIVO:
			return "agressivo";
		default:
			return "s/ estado";
		}
	}

}