using Microsoft.EntityFrameworkCore;
using Emporium.Models;

namespace Emporium.Data 
{
    public class FeiraContext : DbContext{

        public FeiraContext(DbContextOptions<FeiraContext> options) : base(options){

        }

        public DbSet<LeiloesModel> Leiloes { get; set; }

        public DbSet<LoginModel> Login {get; set;}

        public DbSet<UsersModel> Users {get; set;}

        

    }
}