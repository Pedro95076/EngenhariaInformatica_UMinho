using System.Data.SqlClient;
using System.Configuration;

namespace Emporium.Models
{
    public class HomeModel
    {
        public int IdUser { get; set; }
        public List<Feira> Feiras = new List<Feira>();
        public List<string> categorias = new List<string>();

        public void getFeiras(){
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM Feiras", cnn);
            SqlDataReader reader1 = cmd.ExecuteReader();
            //tem de ser string
            while (reader1.Read())
            {
                this.categorias.Add(reader1["categoria"].ToString());
            }
            reader1.Close();
            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                Feira feira = new Feira();
                feira.Id = Convert.ToInt32(reader["id"]);
                feira.Nome = reader["nome"].ToString();
                feira.Imagem = reader["imagem"].ToString();
                feira.Categoria = reader["categoria"].ToString();
                this.Feiras.Add(feira);
            }
            reader.Close();
            cnn.Close();
        }

        public List<Feira> getFeirasByCategoria(int categoria){
            Console.WriteLine("Começou");
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM Feiras WHERE categoria = " + categoria, cnn);
            cmd.Parameters.AddWithValue("@categoria", categoria);
            SqlDataReader reader = cmd.ExecuteReader();
            List<Feira> feiras = new List<Feira>();
            while (reader.Read())
            {
                Feira feira = new Feira();
                feira.Id = Convert.ToInt32(reader["id"]);
                feira.Nome = reader["nome"].ToString();
                feira.Imagem = reader["imagem"].ToString();
                feira.Categoria = reader["categoria"].ToString();
                feiras.Add(feira);
                Console.WriteLine(feira.Nome);
            }
            reader.Close();
            cnn.Close();

            return feiras;
        }
    }
}
