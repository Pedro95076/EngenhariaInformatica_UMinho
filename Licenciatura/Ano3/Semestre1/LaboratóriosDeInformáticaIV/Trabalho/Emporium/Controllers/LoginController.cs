 using Microsoft.AspNetCore.Mvc;
using Emporium.Models;
using Emporium.Repository;
using Emporium.Helper;
using System.Data.SqlClient;
using Emporium.Enum;

namespace Emporium.Controllers
{
    public class LoginController : Controller
    {

        private readonly IUserRepository _userRepository;
        private readonly ILoginRepository _loginRepo;
        private readonly ISessao _sessao;
        private readonly IEmail _email;

        public LoginController(ILoginRepository login, ISessao sessao, IEmail mail) {
            _loginRepo = login;
            _sessao = sessao;
            _email = mail;
        }

        public IActionResult Index()
        {
            if (_sessao.BuscaSessao() != null) return RedirectToAction("EntrarHome", "Login");

            return View();
        }

        /*public IActionResult Registar(LoginModel loginModel){
            try{
                if(ModelState.IsValid){

                    UsersModel user = _userRepository.BuscaLogin(loginModel.Login);
                    if(user != null){
                        if(user.PassValida(loginModel.Password)){
                            _sessao.CriarSessaoUser(user);                       
                            return RedirectToAction("Registar","Home");
                        }
                        TempData["MensagemErro"] = $"Password Invalida";
                    }
                    
                    TempData["MensagemErro"] = $"Login Invalido";

                }
                return View("Registar");
            }
            catch(Exception erro){
                TempData["MensagemErro"] = $"Erro no login: {erro.Message}";
                return RedirectToAction("Registar");
            }
        }*/

        public IActionResult Registar(LoginModel loginModel) {
            try
            {
                if (ModelState.IsValid)
                {
                    SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");

                    SqlCommand cmd = new SqlCommand("INSERT INTO Login VALUES ('" + loginModel.Login + "','" + loginModel.Email + "','" + loginModel.Password + "'," + 1 + ")", cnn);
                    cnn.Open();
                    cmd.ExecuteNonQuery();
                    cnn.Close();
                    TempData["MensagemSucesso"] = $"Registo concluido";
                    return View("Index");
                }
                else
                {
                    Console.WriteLine("OI");
                    return View("Registar");
                }
            }
            catch (Exception erro)
            {
                TempData["MensagemErro"] = $"Erro no login: {erro.Message}";
                return RedirectToAction("Index");
            }
        }

        
        public IActionResult EntrarHistorico()
        {
            LoginModel s = _sessao.BuscaSessao();
            HistoricoModel h = new HistoricoModel();
            h.getHist(s.Id);
            return View(h);
        }

        public IActionResult EntrarHome()
        {
            LoginModel s = _sessao.BuscaSessao();
            HomeModel h = new HomeModel();
            h.getFeiras();
            h.IdUser = s.Id;
            return View(h);
        }

        public IActionResult EntrarCarrinho()
        {
            LoginModel s = _sessao.BuscaSessao();
            CarrinhoModel c = new CarrinhoModel();
            c.getProdutos(s.Id);
            c.IdUser = s.Id;
            return View(c);
        }

        [HttpPost]
        public IActionResult Entrar(LoginModel loginModel) {
            
            try
            {
                if (ModelState.IsValid)
                {
                    SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
                    cnn.Open();
                   
                    SqlCommand cmd = new SqlCommand("SELECT * FROM Login WHERE nome =  '" + loginModel.Login + "'", cnn);
                    SqlDataReader reader = cmd.ExecuteReader();
                    LoginModel oi = new LoginModel();
                    
                    while (reader.Read())
                    {
                        if (reader["nome"].ToString() == loginModel.Login)
                        {

                            oi.Login = reader["nome"].ToString();
                            oi.Email = reader["email"].ToString();
                            oi.Password = reader["pass"].ToString();
                            oi.Id = Convert.ToInt32(reader["perfil"]);
                        }
                    }
                    
                    reader.Close();
                    cnn.Close();
                    if (oi != null)
                    {
                        if (oi.PassValida(loginModel.Password))
                        {
                            _sessao.CriarSessaoUser(oi);
                            return RedirectToAction("EntrarHome", "Login");
                        }
                        TempData["MensagemErro"] = $"Login Invalido";

                    }
                    TempData["MensagemErro"] = $"Login Invalido";

                    /* if(loginModel.Login == "adm" && loginModel.Password == "123"){
                         return RedirectToAction("Index","Home");
                     }
                     TempData["MensagemErro"] = $"Login Invalido";*/


                    return View("Index");
                }
                else
                {
                    return View("Index");
                }
            }
            catch (Exception erro)
            {
                TempData["MensagemErro"] = $"Erro no login: {erro.Message}";
                return RedirectToAction("Index");
            }
        }

        public IActionResult Sair() {
            _sessao.RemoverSessaoUser();
            return RedirectToAction("Index", "Login");
        }

        public IActionResult RedefinirSenha() {
            return View();
        }

        [HttpPost]
        public IActionResult EnviarLink(RedefinirModel redef){
            try{
                if(ModelState.IsValid){

                    LoginModel user = _loginRepo.BuscaPorEmail(redef.Email,redef.Login);

                    if(user != null){
                        string novaSenha = user.GerarNovaSenha();
                        string mensagem = $"A sua nova senha é: {novaSenha}";
                        bool emailEnviado = _email.Enviar(user.Email, "Emporium - Nova Senha", mensagem);
                        if(emailEnviado){
                            _loginRepo.Atualizar(user);
                            TempData["MensagemSucesso"] = $"Enviamos para o seu e-mail uma nova senha.";

                        }
                        else{
                            TempData["MensagemErro"] = $"Não conseguimos enviar para o seu e-mail uma nova senha.";
                        }
                        return RedirectToAction("Index","Login");
                    }
                    TempData["MensagemErro"] = $"Não conseguimos redefinir sua senha";

                }
                return View("Index");
            }
            catch(Exception erro){
                TempData["MensagemErro"] = $"Erro na redefinição de senha: {erro.Message}";
                return RedirectToAction("Index");
            }


        }

    }
}
