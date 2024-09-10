using Microsoft.AspNetCore.Mvc;
using Emporium.Repository;
using Emporium.Models;
using Emporium.Filters;

namespace Emporium.Controllers
{
    [PaginaUserLogado]

    public class ProdutoController : Controller
    {

        public IActionResult Index (){

            return View();
        }

        public IActionResult Comprar(){
            
            return View();
        }

    }
}
