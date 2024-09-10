using System.Data.SqlClient;
using System.Configuration;

namespace Emporium.Models
{
    public class CarrinhoModel
    {
        public int Id;
        public int IdUser;
        public List<ProdutoModel> produtos = new List<ProdutoModel>();
        public void removeCarrinho(int idUser) {
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            SqlCommand cmd = new SqlCommand("DELETE FROM ProdCarrinho WHERE ID_carr = " + idUser, cnn);
            cmd.ExecuteNonQuery();
            cnn.Close();
        } // remove os produtos do carrinho quando compra concluida

        public void atualizaHist(int idUser)
        {
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM ProdCarrinho WHERE ID_carr = " + idUser, cnn);
            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                ProdutoModel p = new ProdutoModel();
                p = p.getProd(Convert.ToInt32(reader["ID_prod"]));
                p.putist(Convert.ToInt32(reader["quatidade"]), Convert.ToInt32(reader["ID_prod"]),idUser);
            }
            reader.Close();
            cnn.Close();
        }
        public void removeStock(int idUser)
        {
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM ProdCarrinho WHERE ID_carr = " + idUser, cnn);
            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                ProdutoModel p = new ProdutoModel(); 
                p = p.getProd(Convert.ToInt32(reader["ID_prod"]));
                p.retiraStock(p.stock - Convert.ToInt32(reader["quatidade"]), Convert.ToInt32(reader["ID_prod"]));
            }
            reader.Close();
            cnn.Close();
        } 

        public void getProdutos(int user) { //função que recebe id de user e dá lista de compras no carrinho
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM ProdCarrinho WHERE ID_carr = " +user, cnn);
            SqlDataReader reader = cmd.ExecuteReader();
            List<int> produtosAux = new List<int>();
            while (reader.Read())
            {
                produtosAux.Add(Convert.ToInt32(reader["ID_prod"]));
            }

            foreach (int idprod in produtosAux)
            {
                ProdutoModel p = new ProdutoModel();
                p = p.getProd(idprod);
                    p.getProdCarrinho(idprod);
                this.produtos.Add(p);
            }

            reader.Close();
            cnn.Close();

        }

        public void addProd(int numberProd, int idProd,int idUser) {
            Console.WriteLine("n produtos:" +numberProd);
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM Produtos WHERE ID_produto = " + idProd, cnn);
            SqlDataReader reader = cmd.ExecuteReader();

            while (reader.Read())
            {
                ProdutoModel produto = new ProdutoModel();
                produto.Id = Convert.ToInt32(reader["ID_produto"]);
                produto.nome = reader["nome"].ToString();
                produto.preco = (float)Convert.ToDecimal(reader["preco"]);
                produto.stock = Convert.ToInt32(reader["stock"]);
                produto.quantidade = numberProd;
                this.produtos.Add(produto);
            }
            reader.Close();
            SqlCommand cmd1 = new SqlCommand("INSERT INTO ProdCarrinho VALUES(" + idUser + "," + idProd + "," + numberProd + ")", cnn);
            cmd1.ExecuteReader();
            cnn.Close();
        }
    }
}
