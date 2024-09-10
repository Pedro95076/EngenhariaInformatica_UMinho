using System.Data.SqlClient;
using System.Configuration;

namespace Emporium.Models
{
    public class ProdutoModel
    {
        public int Id;
        public string nome;
        public float preco;
        public int stock;
        public int IdUser;
        public int quantidade;
        public void retiraStock(int stock,int idProd) {
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            ProdutoModel produto = new ProdutoModel();
            SqlCommand cmd = new SqlCommand("UPDATE Produtos SET stock = "+ stock +" WHERE ID_produto =" + idProd, cnn);
            SqlDataReader reader = cmd.ExecuteReader();
            reader.Close();
            cnn.Close();
        }
        
        public void putist(int stock,int idProd,int idUser)
        {
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            ProdutoModel produto = new ProdutoModel();
            SqlCommand cmd = new SqlCommand("INSERT INTO ProdHist VALUES ("+idUser+","+idProd+","+stock+")", cnn);
            SqlDataReader reader = cmd.ExecuteReader();
            reader.Close();
            cnn.Close();
        }
        public ProdutoModel getProd(int h)
        {
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            ProdutoModel produto= new ProdutoModel();
            SqlCommand cmd = new SqlCommand("SELECT * FROM Produtos WHERE ID_produto = " + h, cnn);
            SqlDataReader reader = cmd.ExecuteReader();
            
            while (reader.Read())
            {
                produto.Id = Convert.ToInt32(reader["ID_produto"]);
                produto.nome = reader["nome"].ToString();
                produto.preco = (float)Convert.ToDecimal(reader["preco"]);
                produto.stock = Convert.ToInt32(reader["stock"]);
            }


            reader.Close();
            cnn.Close();

            return produto;

        }

        public void getProdCarrinho(int h)
        {
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM ProdCarrinho WHERE ID_prod = " + h, cnn);
            SqlDataReader reader = cmd.ExecuteReader();

            while (reader.Read())
            {
                this.quantidade = Convert.ToInt32(reader["quatidade"]);
            }
            Console.WriteLine("QUantidade:" + this.quantidade);
            reader.Close();
            cnn.Close();

        }

    }
}
