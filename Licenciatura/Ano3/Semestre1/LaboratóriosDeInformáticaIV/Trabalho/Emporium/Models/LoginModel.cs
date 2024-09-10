using System.ComponentModel.DataAnnotations;
using Emporium.Enum;
using System.Configuration;
using System.Data.SqlClient;
using Emporium.Helper;

namespace Emporium.Models
{
    public class LoginModel
    {
        public int Id {get; set;}
        //[Required(ErrorMessage = "Digite o email")]

        public int Idcarrinho = 0;
        public int Idhistorico = 0;
        public string Login { get; set; }
        //[Required(ErrorMessage = "Digite a password")]
        public string Password { get; set;}
        public string Email ="pedro";

        public PerfilEnum Perfil = PerfilEnum.Admin;

        public bool existeUser(String nome, String pass)
        {
            SqlConnection cnn = new SqlConnection(System.Configuration.ConfigurationManager.ConnectionStrings["Data Source=localhost;Initial Catalog=master;Integrated Security=True"].ConnectionString);
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM User", cnn);
            SqlDataReader reader = cmd.ExecuteReader();
            bool res = false;
            while (reader.Read() && !res)
            {
                if(reader["username"].ToString() == nome && reader["password"].ToString() == pass) {
                    res = true;
                }
            }
            reader.Close();
            cnn.Close();

            return res;
        }

        /*public void getProd()
        {
            SqlConnection cnn = new SqlConnection(System.Configuration.ConfigurationManager.ConnectionStrings["Data Source=localhost;Initial Catalog=master;Integrated Security=True"].ConnectionString);
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM Feira WHERE categoria = @categoria", cnn); //pega no id do carrinho
            SqlDataReader reader = cmd.ExecuteReader();
            SqlCommand cmd2 = new SqlCommand("SELECT * FROM Feira WHERE categoria = @categoria", cnn); //pega na lista de produtos do carrinho
            SqlDataReader reader2 = cmd2.ExecuteReader();
            if (reader.Read())
            {
                this.Id = Convert.ToInt32(reader["id"]);
            }
            while (reader2.Read())
            {
                ProdutoModel prod = new ProdutoModel();
                prod.Id = Convert.ToInt32(reader["id"]);
                prod.nome = reader["nome"].ToString();
                prod.preco = (float)Convert.ToDecimal(reader["preco"]);
                prod.stock = Convert.ToInt32(reader["categoria"]);
                this.produtos.Add(prod);
            }
            reader.Close();
            cnn.Close();
        }*/

        public bool PassValida(string pass){
            return Password == pass;
        }

        public void SetSenhaHash(){
            Password = Password.GerarHash();
        }

        public string GerarNovaSenha(){
            string novaSenha = Guid.NewGuid().ToString().Substring(0,8);
            Password = novaSenha.GerarHash();
            return novaSenha;
        }


    }
}
