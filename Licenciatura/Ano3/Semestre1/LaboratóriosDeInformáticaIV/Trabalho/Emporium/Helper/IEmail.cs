
namespace Emporium.Helper{

    public interface IEmail{
        bool Enviar(string email, string assunto, string mensagem){
            return true;
        }
    }
}