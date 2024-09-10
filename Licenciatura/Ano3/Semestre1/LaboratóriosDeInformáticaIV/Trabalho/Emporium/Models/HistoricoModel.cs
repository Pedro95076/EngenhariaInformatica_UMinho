using System.Data.SqlClient;
using System.Configuration;

namespace Emporium.Models
{
    public class HistoricoModel
    {
        public int Id { get; set; }
        public List<ProdutoModel> Produtos = new List<ProdutoModel>();

        public void getHist(int idUser) // provavelmente teremos de dar o user para ligar
        {
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM ProdHist", cnn);
            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                ProdutoModel p = new ProdutoModel();
                p = p.getProd(Convert.ToInt32(reader["ID_prod"]));
                p.quantidade = (Convert.ToInt32(reader["quantidade"]));
                Console.WriteLine(p.quantidade);
                this.Produtos.Add(p);
            }
            reader.Close();
            cnn.Close();
        }
    }
}
