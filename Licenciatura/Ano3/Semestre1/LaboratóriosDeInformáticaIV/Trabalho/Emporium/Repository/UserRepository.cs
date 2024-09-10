using Emporium.Models;
using Emporium.Data;


namespace Emporium.Repository{

    public class UserRepository : IUserRepository{

        private readonly FeiraContext _feiracontext;

        public UserRepository(FeiraContext feiraContext){
            _feiracontext = feiraContext;
        }        
        public UsersModel BuscaLogin(string login){
            return _feiracontext.Users.FirstOrDefault(x => x.Name.ToUpper() == login.ToUpper());
            //return null;
        }

        public UsersModel Adicionar(UsersModel user){
            user.SetSenhaHash();
            _feiracontext.Users.Add(user);
            _feiracontext.SaveChanges();
            return user;
        }

        public List<UsersModel> BuscaTodos(){
            return _feiracontext.Users.ToList();
        }

        public UsersModel BuscaPorId(int id){
            return _feiracontext.Users.FirstOrDefault(x => x.Id == id);
        }

    }
}