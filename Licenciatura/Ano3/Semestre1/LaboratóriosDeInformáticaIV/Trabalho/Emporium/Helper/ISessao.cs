using Emporium.Models;

namespace Emporium.Helper{

    public interface ISessao{
        void CriarSessaoUser(LoginModel user);
        void RemoverSessaoUser();
        LoginModel BuscaSessao();
    }
}