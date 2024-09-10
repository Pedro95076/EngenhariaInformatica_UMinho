using Emporium.Filters;
using Microsoft.AspNetCore.Mvc;

namespace Emporium.Controllers{

    [PaginaUserLogado]
    public class RestritoController : Controller{
        public IActionResult Index(){
            return View();
        }
    }

}