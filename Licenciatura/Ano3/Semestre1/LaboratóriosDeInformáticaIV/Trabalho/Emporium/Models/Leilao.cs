using System.Data.SqlClient;

namespace Emporium.Models
{
    public class Leilao
    {
        public int Id;
        public string Produto;
        public string Data;
        public float Valor;

        public void getLeilao(int id)
        {
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM Leilao WHERE ID ="+id, cnn);
            SqlDataReader reader = cmd.ExecuteReader();
            //tem de ser string
            while (reader.Read())
            {
                this.Id = Convert.ToInt32(reader["ID"]);
                this.Produto = reader["produto"].ToString();
                this.Data = reader["data_fim"].ToString();
                this.Valor = (float)Convert.ToDecimal(reader["valor"]);
            }
            reader.Close();
            cnn.Close();
        }
    }
}
