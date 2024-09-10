using Emporium.Enum;
using Emporium.Helper;

namespace Emporium.Models
{
    public class UsersModel
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Email { get; set; }
        public string Password { get; set; }
        public bool PassValida(string pass){
            return Password == pass.GerarHash();
        }
        public PerfilEnum Perfil {get; set;}
        
         public void SetSenhaHash(){
             Password = Password.GerarHash();
         }

    }
}
