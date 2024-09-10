using System.Data.SqlClient;
using System.Configuration;

namespace Emporium.Models
{
    public class FeiraModel
    {

        public int Id { get; set; }
        public string Nome { get; set; }
        public string Imagem { get; set; }
        public int Categoria { get; set; }
        
        public List<Feira> getFeirasByNome(string nome){
            SqlConnection cnn= new SqlConnection(System.Configuration.ConfigurationManager.ConnectionStrings["_____________"].ConnectionString);
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM Feira WHERE nome LIKE @nome", cnn);
            cmd.Parameters.AddWithValue("@nome", "%" + nome + "%");
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
            }
            reader.Close();
            cnn.Close();

            return feiras;
        }

        public List<Feira> getFeirasById(int id){
            SqlConnection cnn= new SqlConnection(System.Configuration.ConfigurationManager.ConnectionStrings["_____________"].ConnectionString);
            cnn.Open();
            SqlCommand cmd = new SqlCommand("SELECT * FROM Feira WHERE id = @id", cnn);
            cmd.Parameters.AddWithValue("@id", id);
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
            }
            reader.Close();
            cnn.Close();

            return feiras;
        }
    }
}