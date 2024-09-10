using Emporium.Models;
using Microsoft.AspNetCore.Http;
using Newtonsoft.Json;

namespace Emporium.Helper{
    public class Sessao : ISessao{
        private readonly IHttpContextAccessor _httpContext;

        public Sessao(IHttpContextAccessor httpContext){
            _httpContext = httpContext;
        }
        public void CriarSessaoUser(LoginModel user){
            string valor = JsonConvert.SerializeObject(user);
            _httpContext.HttpContext.Session.SetString("sessaoUserLogado",valor);
        }
        public void RemoverSessaoUser(){
            _httpContext.HttpContext.Session.Remove("sessaoUserLogado");
            
        }
        public LoginModel BuscaSessao(){
            string sessaoUser = _httpContext.HttpContext.Session.GetString("sessaoUserLogado");
            if(string.IsNullOrEmpty(sessaoUser)) return null;
            return JsonConvert.DeserializeObject<LoginModel>(sessaoUser);

        }
    }
}