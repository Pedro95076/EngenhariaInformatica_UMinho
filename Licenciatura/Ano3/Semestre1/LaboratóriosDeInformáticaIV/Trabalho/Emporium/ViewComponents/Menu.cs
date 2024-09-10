using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;
using Emporium.Models;
using Newtonsoft.Json;


namespace Emporium.ViewComponents{
    public class Menu : ViewComponent {
        public async Task<IViewComponentResult> InvokeAsync(){
            string sessaoUser = HttpContext.Session.GetString("sessaoUserLogado");
            if(string.IsNullOrEmpty(sessaoUser)) return View();
            LoginModel user = JsonConvert.DeserializeObject<LoginModel>(sessaoUser);
            return View(user);
        }
    }

}