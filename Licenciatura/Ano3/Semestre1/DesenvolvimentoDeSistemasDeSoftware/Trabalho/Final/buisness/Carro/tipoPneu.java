package buisness.Carro;


public enum tipoPneu{
MACIO,
DURO,
CHUVA,
NULL;
    public static tipoPneu fromString(String str)
    {
	 switch (str)
	 	{
		case("macio"):
			return MACIO;
		case("duro"):
			return DURO;
		case("chuva"):
			return CHUVA;
		default:
			return NULL;	
		}
    }
	public static String toStr(tipoPneu pneus)
	{
	 switch(pneus)
		{
		case MACIO:
			return "macio";
		case DURO:
			return "duro";
		case CHUVA:
			return "chuva";
		default:
			return "s/ tipo pneus";
		}
	}

	
}

