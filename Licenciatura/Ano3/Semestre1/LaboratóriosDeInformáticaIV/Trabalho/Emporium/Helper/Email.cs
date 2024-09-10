using Emporium.Helper;
using Microsoft.Extensions.Configuration;
using System.Net.Mail;
using System.Net;
namespace Emporium.Helper{
    public class Email : IEmail {

        private readonly IConfiguration _config;

        public Email(IConfiguration config){
            _config = config;
        }

        public bool Enviar(string email, string assunto, string mensagem){
            try{
                string host = _config.GetValue<string>("SMTP:Host");
                string nome = _config.GetValue<string>("SMTP:Nome");
                string username = _config.GetValue<string>("SMTP:UserName");
                string senha = _config.GetValue<string>("SMTP:Senha");
                int porta = _config.GetValue<int>("SMTP:Porta");

                MailMessage mail = new MailMessage(){
                    From = new MailAddress(username,nome)
                };

                mail.To.Add(email);
                mail.Subject = assunto;
                mail.Body = mensagem;
                mail.IsBodyHtml = true;
                mail.Priority = MailPriority.High;

                using(SmtpClient smtp = new SmtpClient(host,porta)){
                    smtp.Credentials = new NetworkCredential(username,senha);
                    smtp.EnableSsl = true;
                    smtp.Send(mail);
                    return true;
                }
            }catch(System.Exception ex){
                return false;
            }
        }

    }
}