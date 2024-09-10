using Emporium.Models;
using System.Collections.Generic;

namespace Emporium.Repository{

    public interface IUserRepository{
        UsersModel BuscaLogin(string login);
        UsersModel Adicionar(UsersModel user);

        List<UsersModel> BuscaTodos();
        
        UsersModel BuscaPorId(int id);
        /*
        UsersModel Atualizar(UsersModel user);
        bool Apagar(int id);*/
    }

}