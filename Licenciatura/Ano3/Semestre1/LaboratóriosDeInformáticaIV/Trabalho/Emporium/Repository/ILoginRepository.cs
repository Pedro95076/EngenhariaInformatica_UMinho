using Emporium.Models;
using System.Collections.Generic;

namespace Emporium.Repository{

    public interface ILoginRepository{
        LoginModel BuscaLogin(string login);
        LoginModel Adicionar(LoginModel user);

        List<LoginModel> BuscaTodos();
        
        LoginModel BuscaPorId(int id);
        /*
        bool Apagar(int id);*/

        LoginModel BuscaPorEmail(string email, string login);
        LoginModel Atualizar(LoginModel user);

    }
}