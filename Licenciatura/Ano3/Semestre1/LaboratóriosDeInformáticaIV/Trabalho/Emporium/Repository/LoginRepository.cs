using Emporium.Models;
using Emporium.Data;
using System.Data.SqlClient;
using Emporium.Enum;

namespace Emporium.Repository{

    public class LoginRepository : ILoginRepository{

        private readonly FeiraContext _feiracontext;

        public LoginRepository(FeiraContext feiraContext){
            _feiracontext = feiraContext;
        }        
        public LoginModel BuscaLogin(string login){
            
            SqlConnection cnn = new SqlConnection(System.Configuration.ConfigurationManager.ConnectionStrings["Data Source=./;Initial Catalog=master;Integrated Security=True"].ConnectionString);
            cnn.Open();
            
            SqlCommand cmd = new SqlCommand("SELECT * FROM Login WHERE nome =  '"+ login+"'", cnn);
            SqlDataReader reader = cmd.ExecuteReader();
            LoginModel oi = new LoginModel();
            while (reader.Read())
            {
                if (reader["nome"].ToString() == login )
                {
                   
                    oi.Login = reader["nome"].ToString();
                    oi.Email = reader["email"].ToString();
                    oi.Password = reader["pass"].ToString();
                    if (Convert.ToInt32(reader["perfil"]) == 1)
                    {
                        oi.Perfil = PerfilEnum.Admin;
                    }
                    else if (Convert.ToInt32(reader["perfil"]) == 2)
                    {
                        oi.Perfil = PerfilEnum.Comerciante;
                    }
                    else
                    {
                        oi.Perfil = PerfilEnum.Client;
                    }
                }
            }
            reader.Close();
            cnn.Close();

            return oi;
        }

        public LoginModel Adicionar(LoginModel user){
            user.SetSenhaHash();
            _feiracontext.Login.Add(user);
            _feiracontext.SaveChanges();
            return user;
        }

        public LoginModel Atualizar(LoginModel user){
            LoginModel userDB = BuscaPorId(user.Id);
            if(userDB == null) throw new Exception("Erro na atualização");
            userDB.Login = user.Login;
            userDB.Email = user.Email;
            userDB.Password = user.Password; 
            userDB.Perfil = user.Perfil;

            _feiracontext.Login.Update(userDB);
            _feiracontext.SaveChanges();
            return userDB;
        }

        public List<LoginModel> BuscaTodos(){
            return _feiracontext.Login.ToList();
        }

        public LoginModel BuscaPorId(int id){
            return _feiracontext.Login.FirstOrDefault(x => x.Id == id);
        }

        public LoginModel BuscaPorEmail(string email, string login){
            return _feiracontext.Login.FirstOrDefault(x => x.Email.ToUpper() == email.ToUpper() && x.Login.ToUpper() == login.ToUpper());
        }


    }
}