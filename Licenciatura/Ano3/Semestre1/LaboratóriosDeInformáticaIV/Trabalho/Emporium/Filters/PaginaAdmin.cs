using Microsoft.AspNetCore.Mvc.Filters;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Routing;
using Emporium.Models;
using Newtonsoft.Json;

namespace Emporium.Filters{

    public class PaginaAdmin : ActionFilterAttribute{
        public override void OnActionExecuting(ActionExecutingContext context)
        {
            string sessaoUser = context.HttpContext.Session.GetString("sessaoUserLogado");
            if(string.IsNullOrEmpty(sessaoUser)){
                context.Result = new RedirectToRouteResult(new RouteValueDictionary{{"controller","Login"},{"action","Index"}});
            }
            else{
                UsersModel user = JsonConvert.DeserializeObject<UsersModel>(sessaoUser);
                if(user == null){
                    context.Result = new RedirectToRouteResult(new RouteValueDictionary{{"controller","Login"},{"action","Index"}});
                }

                if(user.Perfil != Enum.PerfilEnum.Admin){
                    context.Result = new RedirectToRouteResult(new RouteValueDictionary{{"controller","Restrito"},{"action","Index"}});
             
                }
            }
            base.OnActionExecuting(context);
        }
    }

}