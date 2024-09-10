using System.Data.SqlClient;
using System.Configuration;


namespace Emporium.Models
{
    public class Feira
    {
        public int Id { get; set; }
        public string Nome { get; set; }
        public string Imagem { get; set; }
        public string Categoria { get; set; }

        public int IdUser { get; set; }
        public List<ProdutoModel> produtosFeira  = new List<ProdutoModel>();

        public void getFeira(int id)
        {

            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM Feiras WHERE id = " + id, cnn);
            SqlCommand cmd1 = new SqlCommand("SELECT * FROM Produtos WHERE ID_feira = " + id, cnn); 
            SqlDataReader reader1 = cmd1.ExecuteReader();
            while (reader1.Read())
            {
                ProdutoModel model = new ProdutoModel();
                model.preco = (float)Convert.ToDecimal(reader1["preco"]);
                model.Id = Convert.ToInt32(reader1["ID_feira"]);
                model.nome = reader1["nome"].ToString();
                model.stock = Convert.ToInt32(reader1["stock"]);
                this.produtosFeira.Add(model);
            }
            reader1.Close();
            SqlDataReader reader = cmd.ExecuteReader();
            if (reader.Read())
            {
                this.Id = Convert.ToInt32(reader["ID"]);
                this.Nome = reader["nome"].ToString();
                this.Imagem = reader["imagem"].ToString();
                this.Categoria = reader["categoria"].ToString();

            }
            reader.Close();
            cnn.Close();
        }
    }

    
}