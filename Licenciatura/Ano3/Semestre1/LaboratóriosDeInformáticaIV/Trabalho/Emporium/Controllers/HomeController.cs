using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using Emporium.Models;
using Emporium.Filters;
using System.Data.SqlClient;

namespace Emporium.Controllers{

[PaginaUserLogado]

public class HomeController : Controller
{

    
    public IActionResult entrarFeira(int h,int idUser)
    {
        Feira f = new Feira();  
        f.getFeira(h);
        f.IdUser= idUser;
            return View(f);
    }

    public IActionResult entrarProduto(int h,int idUser)
    {
        ProdutoModel prod = new ProdutoModel();
            prod = prod.getProd(h);
            prod.IdUser= idUser;
            return View(prod);
    }
        
    
    public IActionResult AddCarrinho(int h) // h será a quantidade do prod a adicionar
    {
            return View();
    }

    [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
    public IActionResult Error()
    {
        return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
    }
}
}

