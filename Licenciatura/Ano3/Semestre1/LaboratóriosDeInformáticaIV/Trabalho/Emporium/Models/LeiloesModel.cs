using System.Data.SqlClient;
using System.Configuration;
using Emporium.Enum;


namespace Emporium.Models
{
    public class LeiloesModel
    {
        public List<Leilao> leiloes = new List<Leilao>();
        public PerfilEnum Perfil {get; set;}

        public void listaLeilao()
        {
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM Leilao", cnn);
            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                Leilao leilao = new Leilao();
                leilao.Id = Convert.ToInt32(reader["ID"]);
                leilao.Valor = (float)Convert.ToDecimal(reader["valor"]);
                leilao.Produto = reader["produto"].ToString();
                leilao.Data = reader["data_fim"].ToString();
                this.leiloes.Add(leilao);
            }
            reader.Close();
            cnn.Close();
        }


    }


}
