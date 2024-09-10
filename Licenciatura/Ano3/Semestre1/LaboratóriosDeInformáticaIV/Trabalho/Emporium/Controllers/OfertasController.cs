using Microsoft.AspNetCore.Mvc;
using Emporium.Filters;

namespace Emporium.Controllers
{
    [PaginaUserLogado]

    public class OfertasController : Controller
    {

        public IActionResult Entrar()
        {
            return View();
        }

        public IActionResult Comprar(){
            return View();
        }

        public IActionResult Recusar(){
            return View();
        }

        public IActionResult ContraProposta(){
            return View();
        }
    }
}
